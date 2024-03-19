/*
 * Copyright (c) 2021- ThunderSoft
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/**
 * @file    rnc_ams_apl_control.c
 * @brief   rnc_ams_apl_control.
 * @details  rnc_ams_apl_control init ams for rnc loopback
 * @version 1.0
 * @author  gaochengbo
 * @date    2023-04-13
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2023-02-16               gaochengbo         Create it.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

//#include "sysctrl_i.h"
//#include "err_proc.h"
#include "ams.h"
//#include "ams_util.h"
//#include "logger_utils.h"
//#include "dll_utils_i.h"
//#include "dsp_ams_passthrough.h"
//#include "dsp_ams_delay.h"
#include "rnc_ams_apl_control.h"
#include "rnc_ams_struct.h"
#include "rnc_ams_log.h"
#include "audio_expander.h"
#include "csd2_oem_types.h"
static ams_session_t ams_session = NULL;
static ams_graph_basic_params_t g_param;
static ams_graph_handle_t graph_handle[AMS_RNC_UC_MAX] = {NULL};
static ams_operate_dev_t ams_operate_dev[AMS_OPERATE_DEV_NUM_MAX] = {
    {FALSE, CSD2_DEVICE_PRI_CLK, 48000, 16},
    {FALSE, CSD2_DEVICE_QUIN_CLK, 48000, 16},
};
static int ams_usecase = 0;

static int ams_tdm_operate(bool en);
static int ams_set_expander(audio_source_t source);
static int set_usecase(int usecase);
static int ams_rnc_graph_init();
static int ams_open_graph_func();
static int ams_start_graph_func();
static int ams_stop_graph_func();
static int ams_close_graph_func();
static int ams_destroy_graph_func();
static int ams_set_param_func(uint8_t type, set_tuningtool_param_t param_value);
static int ams_get_param_func(uint8_t type, get_tuningtool_param_t param_value);
static int ams_get_port_timestamp(void);

ams_rnc_interface_t ams_rnc_interface = {
    //.select_output = ams_set_expander,
    .set_usecase = set_usecase,
    .graph_init = ams_rnc_graph_init,
    .graph_open = ams_open_graph_func,
    .graph_start = ams_start_graph_func,
    .graph_stop = ams_stop_graph_func,
    .graph_close = ams_close_graph_func,
    .graph_destroy = ams_destroy_graph_func,
    .set_param = ams_set_param_func,
    .get_param = ams_get_param_func,
    .get_current_timestamp = ams_get_port_timestamp,
};

void ams_ssr_user_cb_func(ams_event_id_t e, void *data)
{
    ams_status_t r = 0;
    ams_graph_handle_t *pgh = data;
    uint32_t i;
    
    switch (e)
    {
        case AMS_EVENT_SSR_STARTED:
            break;

        case AMS_EVENT_SSR_COMPLETED:
            fflush(stdout);
            usleep(10 * 1000000);
            int32_t cnt = 0;
            printf("operate flag: %d\n", ams_operate_dev[0].en);
            ams_tdm_operate(TRUE);
            for (i = 0; i < AMS_RNC_UC_MAX; i++)
            {
                if (pgh[i])
                {
                    r = ams_open_graph(ams_session, pgh[i]);
                    RNC_WRAPPER_LIB_LOGD("AMS_EVENT_SSR_COMPLETED: i = %d, ams_open_graph(0x%lx) return 0x%x\n", i, (uintptr_t)pgh[i], r);
                    fflush(stdout);
                    if (!r)
                    {
                        r = ams_start_graph(ams_session, pgh[i]);
                        RNC_WRAPPER_LIB_LOGD("AMS_EVENT_SSR_COMPLETED: i = %d, ams_start_graph(0x%lx) return 0x%x\n", i, (uintptr_t)pgh[i], r);
                        fflush(stdout);
                    }
                    cnt++;
                }
            }
            break;

        default:
            RNC_WRAPPER_LIB_LOGD("AMS SSR callback => default event received");
            break;
    }
    fflush(stdout);
}

static int ams_tdm_operate(bool en){
    uint32_t i, state;
    int rc;
    
    for (i = 0; i < AMS_OPERATE_DEV_NUM_MAX; i++)
    {
        if( ams_operate_dev[i].en ){
            printf("operate flag: %d\n", en);
            rc = ams_operate_device(ams_session, en, ams_operate_dev[i].dev_id, ams_operate_dev[i].sample_rate, ams_operate_dev[i].sample_width);
            printf("Set dev %d to enable=%d ret %d\n", ams_operate_dev[i].dev_id, en, rc);
            rc |= ams_query_device(ams_session, ams_operate_dev[i].dev_id, &state);
            printf("device %d status %d queried back\n", ams_operate_dev[i].dev_id, state);
        }
    }
    
    return 0;
}

//EIC
#if 0
static int ams_set_expander(audio_source_t source)
{
    uint32_t rc = 0;
    uint32_t io_handle = 0;
    audio_expander_init_config_t init_cfg = {0,};
    switch_source_payload_t switch_source_t = {0, };

    init_cfg.i2c_device = 4; /*/dev/i2c4 for QUP21 required*/
    init_cfg.i2c_addr = 0x77;

    rc = audio_expander_init(&init_cfg);
    if (AMS_STATUS_SUCCESS != rc)
        return rc;
    rc = audio_expander_open(&io_handle);
    if (AMS_STATUS_SUCCESS != rc)
    {
        audio_expander_deinit();
        return rc;
    }
 
    switch_source_t.src = source;
    rc = audio_expander_ioctl(io_handle, CMD_SET_SWITCH_SOURCE, 
        &switch_source_t, sizeof(switch_source_t));

    RNC_WRAPPER_LIB_LOGD("ams_rnc_app: audio output to %s rc %d", (source == SOC_AUDIO) ? "DAC" : "Mercury", rc);

    audio_expander_close(io_handle);
    audio_expander_deinit();
    return rc;
}
#endif

ams_graph_handle_t *ams_get_graph_handle_func(int uc)
{
    ams_graph_handle_t *pgh = NULL;

    if ((uc > AMS_RNC_UC_MAX) || (uc < AMS_RNC_UC_MIN))
    {
        goto exit;
    }
    pgh = &graph_handle[uc - 1];

exit:
    return pgh;
}

int ams_graph_add_endpoint_func(ams_session_t ams_session, ams_graph_handle_t *pgh, ams_endpoint_t *e, int nums)
{
    ams_status_t rc = 0;
    for (int i = 0; i < nums; i++)
    {
        rc |= ams_graph_add_endpont(ams_session, *pgh, (e + i));
    }
    return rc;
}

int ams_graph_add_module_func(ams_session_t ams_session, ams_graph_handle_t *pgh, ams_module_t *m, int nums)
{
    ams_status_t rc = 0;
    for (int i = 0; i < nums; i++)
    {
        rc |= ams_graph_add_module(ams_session, *pgh, (m + i));
    }
    return rc;
}

int ams_graph_add_connection_func(ams_session_t ams_session, ams_graph_handle_t *pgh, ams_connection_t *c, int nums)
{
    ams_status_t rc = 0;
    for (int i = 0; i < nums; i++)
    {
        rc |= ams_graph_add_connection(ams_session, *pgh, (c + i));
    }
    return rc;
}

int ams_graph_set_prop_func(ams_session_t ams_session, ams_graph_handle_t *pgh, ams_graph_property_t *prop, int nums)
{
    ams_status_t rc = 0;
    for (int i = 0; i < nums; i++)
    {
        rc |= ams_graph_set_property(ams_session, *pgh, (prop + i));
    }
    return rc;
}

int ams_set_endpoint_channel_type_func(graph_config_t *graph_config)
{
    ams_status_t rc = 0;

    if (!graph_config->ch_mapping_manual)
    {
        for (int i = 0; i < graph_config->endpoint_nums; i++)
        {
            memset(&graph_config->endpoint[i].channel_type, 0, sizeof(graph_config->endpoint[i].channel_type));
            for (int j = 0; j < graph_config->endpoint[i].tdm_params.num_channels; j++)
            {
                graph_config->endpoint[i].channel_type[j] = j + 1;
            }
        }
        RNC_WRAPPER_LIB_LOGD("ams_rnc: config channel mappings automatically \n");
    }
    else
    {
        RNC_WRAPPER_LIB_LOGD("ams_rnc: config channel mappings manually \n");
    }
    return rc;
}

int ams_create_graph_func(ams_session_t ams_session, ams_graph_basic_params_t *param, ams_graph_handle_t *pgh)
{
    ams_status_t rc = 0;

    graph_config_t *graph_config;

    graph_config = get_graph_config(ams_usecase);

    rc |= ams_set_endpoint_channel_type_func(graph_config);

    rc |= ams_create_graph(ams_session, param, pgh);

    rc |= ams_graph_add_endpoint_func(ams_session, *pgh, graph_config->endpoint, graph_config->endpoint_nums);

    rc |= ams_graph_add_module_func(ams_session, *pgh, graph_config->module, graph_config->module_nums);

    rc |= ams_graph_add_connection_func(ams_session, *pgh, graph_config->connection, graph_config->connection_nums);

    rc |= ams_graph_set_prop_func(ams_session, *pgh, graph_config->graph_prop, graph_config->prop_nums);

    return rc;
}

static int ams_rnc_graph_init()
{
    int rc = AMS_STATUS_SUCCESS;
    ams_graph_handle_t *pgh = NULL;

    if (opt_args.block_size != 0)
    {
        g_param.block_size = opt_args.block_size;
    }
    else
    {
        g_param.block_size = AMS_BLOCK_SIZE;
    }

    ams_tdm_operate(TRUE);

    g_param.flags = AMS_GRAPH_FLAGS;
    g_param.processor_id = AMS_PROCESSOR_ID;
    g_param.sample_rate = AMS_SAMPLE_RATE;

    if (ams_session == NULL)
    {
        rc = ams_init(&ams_session);
        RNC_WRAPPER_LIB_LOGD("ams_rnc : init returned value : 0x%x\n", rc);
        rc = ams_register_callback(ams_session, ams_ssr_user_cb_func, (void *)graph_handle);
        RNC_WRAPPER_LIB_LOGD("ams_rnc : register cb returned value : 0x%x\n", rc);
    }

    pgh = ams_get_graph_handle_func(ams_usecase);

    if (!pgh)
    {
        RNC_WRAPPER_LIB_LOGD("Unknown usecase : %d!\n", ams_usecase);
    }
    rc = ams_create_graph_func(ams_session, &g_param, pgh);
    return rc;
}

static int set_usecase(int usecase)
{
    ams_usecase = usecase;
    return 0;
}

static int ams_open_graph_func()
{
    int rc = ams_open_graph(ams_session, *ams_get_graph_handle_func(ams_usecase));
    RNC_WRAPPER_LIB_LOGD("ams_rnc : open graph returned value 0x%x\n", rc);
    return rc;
}

static int ams_start_graph_func()
{
    int rc = ams_start_graph(ams_session, *ams_get_graph_handle_func(ams_usecase));
    RNC_WRAPPER_LIB_LOGD("ams_rnc : start graph returned value 0x%x\n", rc);
    return rc;
}

static int ams_stop_graph_func(void)
{
    ams_status_t rc;
    rc = ams_stop_graph(ams_session, *ams_get_graph_handle_func(ams_usecase));
    RNC_WRAPPER_LIB_LOGD("ams_rnc : stop graph failed 0x%x\n", rc);
    return rc;
}

static int ams_close_graph_func(void)
{
    ams_status_t rc;
    rc = ams_close_graph(ams_session, *ams_get_graph_handle_func(ams_usecase));
    RNC_WRAPPER_LIB_LOGD("ams_rnc : close graph failed 0x%x\n", rc);
    return rc;
}

static int ams_set_param_func(uint8_t type, set_tuningtool_param_t param_value)
{
    ams_status_t rc = 0;
    ams_graph_handle_t *pgh;
    graph_config_t *graph_config;

    graph_config = get_graph_config(ams_usecase);
    pgh = ams_get_graph_handle_func(ams_usecase);

    switch (type)
    {
    case 1:
        rc = ams_set_param(ams_session, *pgh, graph_config->module[0].id, graph_config->module[0].capiv2_info.id + 1, sizeof(param_value), &param_value);
        printf("module id: %d, module param id: 0x%x \n", graph_config->module[0].id, graph_config->module[0].capiv2_info.id + 1);
        RNC_WRAPPER_LIB_LOGD("ams_rnc : set param returned value 0x%x\n", rc);
        break;
    default:
        RNC_WRAPPER_LIB_LOGD("ams_rnc : set param type failed\n");
        break;
    }
    return rc;
}

static int ams_get_param_func(uint8_t type, get_tuningtool_param_t param_value)
{
    ams_status_t rc = 0;
    ams_graph_handle_t *pgh;
    graph_config_t *graph_config;
    uint32_t param_size = 0;

    graph_config = get_graph_config(ams_usecase);
    pgh = ams_get_graph_handle_func(ams_usecase);

    switch (type)
    {
    case 1:
        param_size = sizeof(param_value);
        rc = ams_get_param(ams_session, *pgh, graph_config->module[0].id, graph_config->module[0].capiv2_info.id + 1, &param_size, &param_value);
        printf("module id: %d, module param id: 0x%x, module param value: %d \n", graph_config->module[0].id, graph_config->module[0].capiv2_info.id + 1, param_value.data);
        RNC_WRAPPER_LIB_LOGD("ams_rnc : get param returned value 0x%x\n", rc);
        break;
    default:
        RNC_WRAPPER_LIB_LOGD("ams_rnc : get param type failed\n");
        break;
    }
    return rc;
}

static int ams_destroy_graph_func(void)
{
    ams_graph_handle_t *pgh;
    int rc;

    for (int i = 0; i < AMS_RNC_UC_MAX; i++)
    {
        pgh = &graph_handle[i];
        if (*pgh)
        {
            rc = ams_destroy_graph(ams_session, pgh);
            RNC_WRAPPER_LIB_LOGD("ams_rnc : destroy graph UC %d returned value : 0x%x\n", i, rc);
            //ams_deregister_callback
            rc |= ams_deregister_callback(ams_session, ams_ssr_user_cb_func);
            RNC_WRAPPER_LIB_LOGD("ams_rnc : ams_deregister_callback : 0x%x\n", rc);
        }
        ams_tdm_operate(FALSE);
    }
    rc |= ams_deinit(&ams_session);
    return 0;
}

static int ams_get_port_timestamp(void)
{
    int rc;
    uint32_t diff_value, input_value, output_value;
    ams_rnc_timestamp_t cur_ts;
    ams_graph_handle_t *pgh;
    graph_config_t *graph_config;
    uint32_t param_size = sizeof(ams_rnc_timestamp_t);
    diff_value = input_value = output_value = 0;

    graph_config = get_graph_config(ams_usecase);
    pgh = ams_get_graph_handle_func(ams_usecase);

    memset((void *)&cur_ts, 0, sizeof(ams_rnc_timestamp_t));
    rc = ams_get_param(ams_session, *pgh, graph_config->module[0].id, graph_config->module[0].capiv2_info.id + 2, &param_size, &cur_ts);

    if (rc != 0)
    {
        return rc;
    }
    for (int i = 0; i < DSP_AMS_TS_PAIR; i++)
    {
        if (cur_ts.input_ts[i] != 0 && input_value == 0)
        {
            input_value = cur_ts.input_ts[i];
        }
        if (cur_ts.output_ts[i] != 0 && output_value == 0)
        {
            output_value = cur_ts.output_ts[i];
        }
        printf("capture: %d times: latency of input: %lu us, output: %lu us\n", i, cur_ts.input_ts[i], cur_ts.output_ts[i]);
    }
    diff_value = output_value - input_value + ((g_param.block_size/12) * 500);
    printf("input ouput diff: %u us \n", diff_value);

    return rc;
}

