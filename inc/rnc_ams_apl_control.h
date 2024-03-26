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
 * @file    rnc_ams_apl_control.h
 * @brief   rnc ams apl control.
 * @details  rnc ams control
 * @version 1.0
 * @author  zhanghuizhen
 * @date    2021-12-24
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2021-12-24               zhanghuizhen         Create it.
 * 2023-02-16               gaochengbo           Optimized it.
 */

#ifndef _RNC_AMS_WRAPPER_CONTROL_H_
#define _RNC_AMS_WRAPPER_CONTROL_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
//#include "mmdefs.h"
#include "audio_expander.h"

#define AMS_GRAPH_FLAGS 0
#define AMS_BLOCK_SIZE 24
#define AMS_PROCESSOR_ID 0
#define AMS_SAMPLE_RATE 48000

#define AMS_RNC_UC_MIN 1
#define AMS_RNC_UC_MAX 10
#define AMS_OPERATE_DEV_NUM_MAX 5

#define DSP_AMS_TS_PAIR 10
#define DSP_AMS_TS_PORT 2

typedef struct opt_args
{
    int block_size;
    int expander_type;
} opt_args_t;

typedef struct set_tuningtool_param
{
    uint32_t data;
} set_tuningtool_param_t;

typedef struct get_tuningtool_param
{
    uint32_t data;
} get_tuningtool_param_t;

typedef struct 
{
    uint32_t en;
    uint32_t dev_id;
    uint32_t sample_rate;
    uint32_t sample_width;
}ams_operate_dev_t;

typedef struct ams_rnc_interface
{
    //int (*select_output)(audio_source_t source);
    int (*set_usecase)(int usecase);
    int (*graph_init)();
    int (*graph_open)();
    int (*graph_start)();
    int (*graph_stop)();
    int (*graph_close)();
    int (*graph_destroy)();
    int (*set_param)(uint8_t type, set_tuningtool_param_t param_value);
    int (*get_param)(uint8_t type, get_tuningtool_param_t param_value);
    int (*get_current_timestamp)(void);
    int (*graph_query_info)(void);
} ams_rnc_interface_t;

typedef struct ams_rnc_timestamp
{
    uint64_t input_ts[DSP_AMS_TS_PAIR];
    uint64_t output_ts[DSP_AMS_TS_PAIR];
} ams_rnc_timestamp_t;

ams_rnc_interface_t ams_rnc_interface;
opt_args_t opt_args;

#endif /* RNC_AMS_WRAPPER_CONTROL_H_ */
