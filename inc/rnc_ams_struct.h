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
 * @file    rnc_ams_struct.c
 * @brief   rnc_ams_struct.
 * @details  rnc_ams_struct configuration header
 * @version 1.0
 * @author  gaochengbo
 * @date    2023-04-13
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2023-02-16               gaochengbo         Create it.
 */

#ifndef _RNC_AMS_STRUCT_H_
#define _RNC_AMS_STRUCT_H_

#include <stdint.h>
#include "ams.h"
//#include "ams_util.h"
#include "dsp_audio_micro_service.h"

#define STATIC_RNC_MODULE_ID 0x170010A6
#define DYNAMIC_RNC_MODULE_ID 0x1000B600
#define STATIC_PASSTHRU_MODULE_ID 0x00013378
#define DYNAMIC_PASSTHRU_MODULE_ID 0x070010A7
#define DYNAMIC_GAIN_MODULE_ID  0x10015656
#define DYNAMIC_CTRL_MODULE_ID  0x10015658

#define MAX_ENDPOINT_NUM 5
#define MAX_MODULE_NUM 5
#define MAX_CONNECTION_NUM 20
#define MAX_PROP_NUM 5
#define MAX_MSG_LINK_NUM 2

typedef enum
{
    ENDPOINT_1 = 1,
    ENDPOINT_2,
    MODULE_1,
    CONNECTION_1,
    CONNECTION_2,
	MODULE_2,
} graph1_id_e;

typedef struct
{
    uint8_t endpoint_nums;
    uint8_t module_nums;
    uint8_t connection_nums;
    uint8_t prop_nums;
    bool ch_mapping_manual;
    ams_msg_link_connection_t msg_link[MAX_MSG_LINK_NUM];
    ams_endpoint_t endpoint[MAX_ENDPOINT_NUM];
    ams_module_t module[MAX_MODULE_NUM];
    ams_connection_t connection[MAX_CONNECTION_NUM];
    ams_graph_property_t graph_prop[MAX_PROP_NUM];
} graph_config_t;

graph_config_t *get_graph_config(int use_case);

#define CHANNEL_MAPPING_GENERAL \
    .ch_mapping_manual = false,

#define CHANNEL_MAPPING_MANUAL \
    .ch_mapping_manual = true,

#define STATIC_PASSTHRU_MODULE                             \
    .module[0].id = MODULE_1,                              \
    .module[0].flags = AMS_INLINE_PROCESSING_MODE,         \
    .module[0].capiv2_info.id = STATIC_PASSTHRU_MODULE_ID, \
    .module[0].capiv2_info.tag = "",                       \
    .module[0].capiv2_info.shared_obj_filename = "",

#define DYNAMIC_PASSTHRU_MODULE                             \
    .module[0].id = MODULE_1,                               \
    .module[0].flags = AMS_INLINE_PROCESSING_MODE,          \
    .module[0].capiv2_info.id = DYNAMIC_GAIN_MODULE_ID, \
    .module[0].capiv2_info.tag = "capi_gain",           \
    .module[0].capiv2_info.shared_obj_filename = "capi_gain.so",

#define STATIC_SAMPLE_MODULE                          \
    .module[0].id = MODULE_1,                         \
    .module[0].flags = AMS_INLINE_PROCESSING_MODE,    \
    .module[0].capiv2_info.id = STATIC_RNC_MODULE_ID, \
    .module[0].capiv2_info.tag = "",                  \
    .module[0].capiv2_info.shared_obj_filename = "",

#define DYNAMIC_SAMPLE_MODULE                          \
    .module[0].id = MODULE_1,                          \
    .module[0].flags = AMS_INLINE_PROCESSING_MODE,     \
    .module[0].capiv2_info.id = DYNAMIC_RNC_MODULE_ID, \
    .module[0].capiv2_info.tag = "capi_rnc",           \
    .module[0].capiv2_info.shared_obj_filename = "capi_rnc.so",

#define DYNAMIC_GAIN_MODULE                                 \
    .module[0].id = MODULE_1,                               \
    .module[0].flags = AMS_INLINE_PROCESSING_MODE,          \
    .module[0].capiv2_info.id = DYNAMIC_GAIN_MODULE_ID, \
    .module[0].capiv2_info.tag = "capi_gain",               \
    .module[0].capiv2_info.shared_obj_filename = "capi_gain.so",

#define DYNAMIC_CTRL_MODULE                                 \
	.module[0].id = MODULE_1,                               \
	.module[0].flags = AMS_INLINE_PROCESSING_MODE,          \
	.module[0].capiv2_info.id = DYNAMIC_GAIN_MODULE_ID, \
	.module[0].capiv2_info.tag = "capi_gain",               \
	.module[0].capiv2_info.shared_obj_filename = "capi_gain.so",  \
    .module[1].id = MODULE_2,                               \
    .module[1].flags = AMS_INLINE_PROCESSING_MODE,          \
    .module[1].capiv2_info.id = DYNAMIC_CTRL_MODULE_ID, \
    .module[1].capiv2_info.tag = "capi_control_tx",               \
    .module[1].capiv2_info.shared_obj_filename = "capi_control_tx.so",

#define A2B_PROP_CONFIG                                                             \
    .endpoint_nums = 2,                                                             \
    .module_nums = 1,                                                               \
    .connection_nums = 2,                                                           \
    .prop_nums = 3,                                                                 \
                                                                                    \
    .endpoint[0].id = ENDPOINT_1,                                                   \
    .endpoint[0].type = AMS_ENDPOINT_TYPE_SINK,                                     \
    .endpoint[0].channel_mask = 0xFF,                                               \
    .endpoint[0].q_factor = 31,                                                     \
    .endpoint[0].flags = AMS_ENDPOINT_EXCLUSIVE,                                    \
    .endpoint[0].tdm_params.hw_interface_id = AMS_HW_INTERFACE_TDM4,                \
    .endpoint[0].tdm_params.num_channels = 8,                                       \
    .endpoint[0].tdm_params.bit_width = 16,                                         \
    .endpoint[0].tdm_params.data_format = AMS_TDM_LINEAR_PCM_DATA,                  \
    .endpoint[0].tdm_params.sync_mode = AMS_TDM_LONG_SYNC_MODE,                     \
    .endpoint[0].tdm_params.sync_src = AMS_TDM_SYNC_SRC_INTERNAL,                   \
    .endpoint[0].tdm_params.nslots_per_frame = 16,                                  \
    .endpoint[0].tdm_params.ctrl_data_out_enable = AMS_TDM_CTRL_DATA_OE_DISABLE,    \
    .endpoint[0].tdm_params.ctrl_invert_sync_pulse = AMS_TDM_SYNC_NORMAL,           \
    .endpoint[0].tdm_params.ctrl_sync_data_delay = AMS_TDM_DATA_DELAY_0_BCLK_CYCLE, \
    .endpoint[0].tdm_params.slot_width = 32,                                        \
    .endpoint[0].tdm_params.slot_mask = 0xF,                                        \
                                                                                    \
    .endpoint[1].id = ENDPOINT_2,                                                   \
    .endpoint[1].type = AMS_ENDPOINT_TYPE_SOURCE,                                   \
    .endpoint[1].channel_mask = 0xFF,                                               \
    .endpoint[1].q_factor = 31,                                                     \
    .endpoint[1].flags = AMS_ENDPOINT_EXCLUSIVE,                                    \
    .endpoint[1].tdm_params.hw_interface_id = AMS_HW_INTERFACE_TDM4,                \
    .endpoint[1].tdm_params.num_channels = 8,                                       \
    .endpoint[1].tdm_params.bit_width = 16,                                         \
    .endpoint[1].tdm_params.data_format = AMS_TDM_LINEAR_PCM_DATA,                  \
    .endpoint[1].tdm_params.sync_mode = AMS_TDM_LONG_SYNC_MODE,                     \
    .endpoint[1].tdm_params.sync_src = AMS_TDM_SYNC_SRC_INTERNAL,                   \
    .endpoint[1].tdm_params.nslots_per_frame = 16,                                  \
    .endpoint[1].tdm_params.ctrl_data_out_enable = AMS_TDM_CTRL_DATA_OE_DISABLE,    \
    .endpoint[1].tdm_params.ctrl_invert_sync_pulse = AMS_TDM_SYNC_NORMAL,           \
    .endpoint[1].tdm_params.ctrl_sync_data_delay = AMS_TDM_DATA_DELAY_0_BCLK_CYCLE, \
    .endpoint[1].tdm_params.slot_width = 32,                                        \
    .endpoint[1].tdm_params.slot_mask = 0xF,                                        \
                                                                                    \
    .connection[0].num_channels = 8,                                                \
    .connection[0].bit_width = 16,                                                  \
    .connection[0].source.type = AMS_CONNECTION_ELEMENT_TYPE_ENDPOINT,              \
    .connection[0].source.endpoint.id = ENDPOINT_2,                                 \
    .connection[0].destination.type = AMS_CONNECTION_ELEMENT_TYPE_MODULE,           \
    .connection[0].destination.module.id = MODULE_1,                                \
    .connection[0].destination.module.port_index = 0,                               \
                                                                                    \
    .connection[1].num_channels = 8,                                                \
    .connection[1].bit_width = 16,                                                  \
    .connection[1].source.type = AMS_CONNECTION_ELEMENT_TYPE_MODULE,                \
    .connection[1].source.module.id = MODULE_1,                                     \
    .connection[1].source.module.port_index = 0,                                    \
    .connection[1].destination.type = AMS_CONNECTION_ELEMENT_TYPE_ENDPOINT,         \
    .connection[1].destination.endpoint.id = ENDPOINT_1,                            \
                                                                                    \
    .graph_prop[0].prop_id = AMS_GRAPH_PROPERTY_ID_EXCLV_EP_TDM_LANE_CFG,           \
    .graph_prop[0].appy_after_start = 0,                                            \
    .graph_prop[0].u.exclv_ep_tdm_lane_cfg.hw_interface_id = AMS_HW_INTERFACE_TDM4, \
    .graph_prop[0].u.exclv_ep_tdm_lane_cfg.type = DSP_AMS_ENDPOINT_TYPE_SOURCE,     \
    .graph_prop[0].u.exclv_ep_tdm_lane_cfg.lane_mask = 5,                           \
                                                                                    \
    .graph_prop[1].prop_id = AMS_GRAPH_PROPERTY_ID_EXCLV_EP_TDM_LANE_CFG,           \
    .graph_prop[1].appy_after_start = 0,                                            \
    .graph_prop[1].u.exclv_ep_tdm_lane_cfg.hw_interface_id = AMS_HW_INTERFACE_TDM4, \
    .graph_prop[1].u.exclv_ep_tdm_lane_cfg.type = DSP_AMS_ENDPOINT_TYPE_SINK,       \
    .graph_prop[1].u.exclv_ep_tdm_lane_cfg.lane_mask = 10,

#define ANALOG_PROP_CONFIG                                                          \
    .endpoint_nums = 2,                                                             \
    .module_nums = 1,                                                               \
    .connection_nums = 2,                                                           \
    .prop_nums = 2,                                                                 \
                                                                                    \
    .endpoint[0].id = ENDPOINT_1,                                                   \
    .endpoint[0].type = AMS_ENDPOINT_TYPE_SINK,                                     \
    .endpoint[0].channel_mask = 0xFF,                                               \
    .endpoint[0].q_factor = 31,                                                     \
    .endpoint[0].flags = AMS_ENDPOINT_EXCLUSIVE,                                    \
    .endpoint[0].tdm_params.hw_interface_id = AMS_HW_INTERFACE_TDM1,                \
    .endpoint[0].tdm_params.num_channels = 8,                                       \
    .endpoint[0].tdm_params.bit_width = 16,                                         \
    .endpoint[0].tdm_params.data_format = AMS_TDM_LINEAR_PCM_DATA,                  \
    .endpoint[0].tdm_params.sync_mode = AMS_TDM_LONG_SYNC_MODE,                     \
    .endpoint[0].tdm_params.sync_src = AMS_TDM_SYNC_SRC_INTERNAL,                   \
    .endpoint[0].tdm_params.nslots_per_frame = 8,                                   \
    .endpoint[0].tdm_params.ctrl_data_out_enable = AMS_TDM_CTRL_DATA_OE_DISABLE,    \
    .endpoint[0].tdm_params.ctrl_invert_sync_pulse = AMS_TDM_SYNC_NORMAL,           \
    .endpoint[0].tdm_params.ctrl_sync_data_delay = AMS_TDM_DATA_DELAY_1_BCLK_CYCLE, \
    .endpoint[0].tdm_params.slot_width = 32,                                        \
    .endpoint[0].tdm_params.slot_mask = 0xFF,                                       \
                                                                                    \
    .endpoint[1].id = ENDPOINT_2,                                                   \
    .endpoint[1].type = AMS_ENDPOINT_TYPE_SOURCE,                                   \
    .endpoint[1].channel_mask = 0xFF,                                               \
    .endpoint[1].q_factor = 31,                                                     \
    .endpoint[1].flags = AMS_ENDPOINT_EXCLUSIVE,                                    \
    .endpoint[1].tdm_params.hw_interface_id = AMS_HW_INTERFACE_TDM3,                \
    .endpoint[1].tdm_params.num_channels = 8,                                       \
    .endpoint[1].tdm_params.bit_width = 16,                                         \
    .endpoint[1].tdm_params.data_format = AMS_TDM_LINEAR_PCM_DATA,                  \
    .endpoint[1].tdm_params.sync_mode = AMS_TDM_LONG_SYNC_MODE,                     \
    .endpoint[1].tdm_params.sync_src = AMS_TDM_SYNC_SRC_EXTERNAL,                   \
    .endpoint[1].tdm_params.nslots_per_frame = 8,                                   \
    .endpoint[1].tdm_params.ctrl_data_out_enable = AMS_TDM_CTRL_DATA_OE_DISABLE,    \
    .endpoint[1].tdm_params.ctrl_invert_sync_pulse = AMS_TDM_SYNC_NORMAL,           \
    .endpoint[1].tdm_params.ctrl_sync_data_delay = AMS_TDM_DATA_DELAY_0_BCLK_CYCLE, \
    .endpoint[1].tdm_params.slot_width = 32,                                        \
    .endpoint[1].tdm_params.slot_mask = 0xFF,                                       \
                                                                                    \
    .connection[0].num_channels = 8,                                                \
    .connection[0].bit_width = 16,                                                  \
    .connection[0].source.type = AMS_CONNECTION_ELEMENT_TYPE_ENDPOINT,              \
    .connection[0].source.endpoint.id = ENDPOINT_2,                                 \
    .connection[0].destination.type = AMS_CONNECTION_ELEMENT_TYPE_MODULE,           \
    .connection[0].destination.module.id = MODULE_1,                                \
    .connection[0].destination.module.port_index = 0,                               \
                                                                                    \
    .connection[1].num_channels = 8,                                                \
    .connection[1].bit_width = 16,                                                  \
    .connection[1].source.type = AMS_CONNECTION_ELEMENT_TYPE_MODULE,                \
    .connection[1].source.module.id = MODULE_1,                                     \
    .connection[1].source.module.port_index = 0,                                    \
    .connection[1].destination.type = AMS_CONNECTION_ELEMENT_TYPE_ENDPOINT,         \
    .connection[1].destination.endpoint.id = ENDPOINT_1,                            \
                                                                                    \
    .graph_prop[0].prop_id = AMS_GRAPH_PROPERTY_ID_EXCLV_EP_CLK_ATTR,               \
    .graph_prop[0].u.exclv_ep_clk_attr.exclv_ep_id = AMS_HW_INTERFACE_TDM1,         \
    .graph_prop[0].u.exclv_ep_clk_attr.clk_invert = 4,                              \
    .graph_prop[0].appy_after_start = 0,

#define ANALOG_PROP_CONFIG_2                                                        \
	.endpoint_nums = 2,                                                             \
	.module_nums = 1,                                                               \
	.connection_nums = 2,                                                           \
	.prop_nums = 2,                                                                 \
																					\
	.endpoint[0].id = ENDPOINT_1,                                                   \
	.endpoint[0].type = AMS_ENDPOINT_TYPE_SINK,                                     \
	.endpoint[0].channel_mask = 0xFF,                                               \
	.endpoint[0].q_factor = 31,                                                     \
	.endpoint[0].flags = AMS_ENDPOINT_EXCLUSIVE,                                    \
	.endpoint[0].tdm_params.hw_interface_id = AMS_HW_INTERFACE_TDM1,                \
	.endpoint[0].tdm_params.num_channels = 8,                                       \
	.endpoint[0].tdm_params.bit_width = 16,                                         \
	.endpoint[0].tdm_params.data_format = AMS_TDM_LINEAR_PCM_DATA,                  \
	.endpoint[0].tdm_params.sync_mode = AMS_TDM_LONG_SYNC_MODE,                     \
	.endpoint[0].tdm_params.sync_src = AMS_TDM_SYNC_SRC_INTERNAL,                   \
	.endpoint[0].tdm_params.nslots_per_frame = 8,                                   \
	.endpoint[0].tdm_params.ctrl_data_out_enable = AMS_TDM_CTRL_DATA_OE_DISABLE,    \
	.endpoint[0].tdm_params.ctrl_invert_sync_pulse = AMS_TDM_SYNC_NORMAL,           \
	.endpoint[0].tdm_params.ctrl_sync_data_delay = AMS_TDM_DATA_DELAY_1_BCLK_CYCLE, \
	.endpoint[0].tdm_params.slot_width = 32,                                        \
	.endpoint[0].tdm_params.slot_mask = 0xFF,                                       \
																					\
	.endpoint[1].id = ENDPOINT_2,                                                   \
	.endpoint[1].type = AMS_ENDPOINT_TYPE_SOURCE,                                   \
	.endpoint[1].channel_mask = 0xFF,                                               \
	.endpoint[1].q_factor = 31,                                                     \
	.endpoint[1].flags = AMS_ENDPOINT_EXCLUSIVE,                                    \
	.endpoint[1].tdm_params.hw_interface_id = AMS_HW_INTERFACE_TDM3,                \
	.endpoint[1].tdm_params.num_channels = 8,                                       \
	.endpoint[1].tdm_params.bit_width = 16,                                         \
	.endpoint[1].tdm_params.data_format = AMS_TDM_LINEAR_PCM_DATA,                  \
	.endpoint[1].tdm_params.sync_mode = AMS_TDM_LONG_SYNC_MODE,                     \
	.endpoint[1].tdm_params.sync_src = AMS_TDM_SYNC_SRC_EXTERNAL,                   \
	.endpoint[1].tdm_params.nslots_per_frame = 8,                                   \
	.endpoint[1].tdm_params.ctrl_data_out_enable = AMS_TDM_CTRL_DATA_OE_DISABLE,    \
	.endpoint[1].tdm_params.ctrl_invert_sync_pulse = AMS_TDM_SYNC_NORMAL,           \
	.endpoint[1].tdm_params.ctrl_sync_data_delay = AMS_TDM_DATA_DELAY_0_BCLK_CYCLE, \
	.endpoint[1].tdm_params.slot_width = 32,                                        \
	.endpoint[1].tdm_params.slot_mask = 0xFF,                                       \
																					\
	.connection[0].num_channels = 8,                                                \
	.connection[0].bit_width = 16,                                                  \
	.connection[0].source.type = AMS_CONNECTION_ELEMENT_TYPE_ENDPOINT,              \
	.connection[0].source.endpoint.id = ENDPOINT_2,                                 \
	.connection[0].destination.type = AMS_CONNECTION_ELEMENT_TYPE_MODULE,           \
	.connection[0].destination.module.id = MODULE_1,                                \
	.connection[0].destination.module.port_index = 0,                               \
																					\
	.connection[1].num_channels = 8,                                                \
	.connection[1].bit_width = 16,                                                  \
	.connection[1].source.type = AMS_CONNECTION_ELEMENT_TYPE_MODULE,                \
	.connection[1].source.module.id = MODULE_1,                                     \
	.connection[1].source.module.port_index = 0,                                    \
	.connection[1].destination.type = AMS_CONNECTION_ELEMENT_TYPE_ENDPOINT,         \
	.connection[1].destination.endpoint.id = ENDPOINT_1,                            \
																					\
	.graph_prop[0].prop_id = AMS_GRAPH_PROPERTY_ID_EXCLV_EP_CLK_ATTR,               \
	.graph_prop[0].u.exclv_ep_clk_attr.exclv_ep_id = AMS_HW_INTERFACE_TDM1,         \
	.graph_prop[0].u.exclv_ep_clk_attr.clk_invert = 4,                              \
    .graph_prop[0].appy_after_start = 0,

#define ANALOG_PROP_CONFIG_3                                                        \
	.endpoint_nums = 2,                                                             \
	.module_nums = 2,                                                               \
	.connection_nums = 3,                                                           \
	.prop_nums = 2,                                                                 \
																					\
	.endpoint[0].id = ENDPOINT_1,                                                   \
	.endpoint[0].type = AMS_ENDPOINT_TYPE_SINK,                                     \
	.endpoint[0].channel_mask = 0xFF,                                               \
	.endpoint[0].q_factor = 31,                                                     \
	.endpoint[0].flags = AMS_ENDPOINT_EXCLUSIVE,                                    \
	.endpoint[0].tdm_params.hw_interface_id = AMS_HW_INTERFACE_TDM1,                \
	.endpoint[0].tdm_params.num_channels = 8,                                       \
	.endpoint[0].tdm_params.bit_width = 16,                                         \
	.endpoint[0].tdm_params.data_format = AMS_TDM_LINEAR_PCM_DATA,                  \
	.endpoint[0].tdm_params.sync_mode = AMS_TDM_LONG_SYNC_MODE,                     \
	.endpoint[0].tdm_params.sync_src = AMS_TDM_SYNC_SRC_INTERNAL,                   \
	.endpoint[0].tdm_params.nslots_per_frame = 8,                                   \
	.endpoint[0].tdm_params.ctrl_data_out_enable = AMS_TDM_CTRL_DATA_OE_DISABLE,    \
	.endpoint[0].tdm_params.ctrl_invert_sync_pulse = AMS_TDM_SYNC_NORMAL,           \
	.endpoint[0].tdm_params.ctrl_sync_data_delay = AMS_TDM_DATA_DELAY_1_BCLK_CYCLE, \
	.endpoint[0].tdm_params.slot_width = 32,                                        \
	.endpoint[0].tdm_params.slot_mask = 0xFF,                                       \
																					\
	.endpoint[1].id = ENDPOINT_2,                                                   \
	.endpoint[1].type = AMS_ENDPOINT_TYPE_SOURCE,                                   \
	.endpoint[1].channel_mask = 0xFF,                                               \
	.endpoint[1].q_factor = 31,                                                     \
	.endpoint[1].flags = AMS_ENDPOINT_EXCLUSIVE,                                    \
	.endpoint[1].tdm_params.hw_interface_id = AMS_HW_INTERFACE_TDM3,                \
	.endpoint[1].tdm_params.num_channels = 8,                                       \
	.endpoint[1].tdm_params.bit_width = 16,                                         \
	.endpoint[1].tdm_params.data_format = AMS_TDM_LINEAR_PCM_DATA,                  \
	.endpoint[1].tdm_params.sync_mode = AMS_TDM_LONG_SYNC_MODE,                     \
	.endpoint[1].tdm_params.sync_src = AMS_TDM_SYNC_SRC_EXTERNAL,                   \
	.endpoint[1].tdm_params.nslots_per_frame = 8,                                   \
	.endpoint[1].tdm_params.ctrl_data_out_enable = AMS_TDM_CTRL_DATA_OE_DISABLE,    \
	.endpoint[1].tdm_params.ctrl_invert_sync_pulse = AMS_TDM_SYNC_NORMAL,           \
	.endpoint[1].tdm_params.ctrl_sync_data_delay = AMS_TDM_DATA_DELAY_0_BCLK_CYCLE, \
	.endpoint[1].tdm_params.slot_width = 32,                                        \
	.endpoint[1].tdm_params.slot_mask = 0xFF,                                       \
																					\
	.connection[0].num_channels = 8,                                                \
	.connection[0].bit_width = 16,                                                  \
	.connection[0].source.type = AMS_CONNECTION_ELEMENT_TYPE_ENDPOINT,              \
	.connection[0].source.endpoint.id = ENDPOINT_2,                                 \
	.connection[0].destination.type = AMS_CONNECTION_ELEMENT_TYPE_MODULE,           \
	.connection[0].destination.module.id = MODULE_1,                                \
	.connection[0].destination.module.port_index = 0,                               \
																					\
	.connection[1].num_channels = 8,                                                \
	.connection[1].bit_width = 16,                                                  \
	.connection[1].source.type = AMS_CONNECTION_ELEMENT_TYPE_MODULE,                \
	.connection[1].source.module.id = MODULE_1,                                     \
	.connection[1].source.module.port_index = 0,                                    \
	.connection[1].destination.type = AMS_CONNECTION_ELEMENT_TYPE_ENDPOINT,         \
	.connection[1].destination.endpoint.id = ENDPOINT_1,                            \
	                                                                                \
    .connection[2].num_channels = 8,                                                \
	.connection[2].bit_width = 16,                                                  \
	.connection[2].source.type = AMS_CONNECTION_ELEMENT_TYPE_MODULE,                \
	.connection[2].source.module.id = MODULE_2,                                     \
	.connection[2].source.module.port_index = 0,                                    \
	.connection[2].destination.type = AMS_CONNECTION_ELEMENT_TYPE_MODULE,           \
	.connection[2].destination.endpoint.id = MODULE_1,                              \
	.connection[2].destination.module.port_index = 1,                               \
																					\
	.graph_prop[0].prop_id = AMS_GRAPH_PROPERTY_ID_EXCLV_EP_CLK_ATTR,               \
	.graph_prop[0].u.exclv_ep_clk_attr.exclv_ep_id = AMS_HW_INTERFACE_TDM1,         \
	.graph_prop[0].u.exclv_ep_clk_attr.clk_invert = 4,                              \
	.graph_prop[0].appy_after_start = 0,

#endif
