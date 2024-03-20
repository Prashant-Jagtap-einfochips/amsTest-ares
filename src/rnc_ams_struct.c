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
 * @brief   rnc ams struct.
 * @details  rnc ams struct is used to config tdm endpoint, connections and modules
 * @version 1.0
 * @author  gaochengbo
 * @date    2023-02-16
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2023-02-16               gaochengbo         Create it.
 */

#include "rnc_ams_struct.h"

// TDM3 -> PASSTHROUGH(Static) -> TDM3
static graph_config_t graph_1 = {
    ANALOG_PROP_CONFIG
    STATIC_PASSTHRU_MODULE
};

// TDM3 -> PASSTHROUGH(Dynamic) -> TDM3
static graph_config_t graph_2 = {
    ANALOG_PROP_CONFIG
    DYNAMIC_PASSTHRU_MODULE
};

// TDM3 -> SAMPLE(Static) -> TDM3
static graph_config_t graph_3 = {
    ANALOG_PROP_CONFIG
    STATIC_SAMPLE_MODULE
};

// TDM3 -> SAMPLE(Dynamic) -> TDM3
static graph_config_t graph_4 = {
    ANALOG_PROP_CONFIG
    DYNAMIC_SAMPLE_MODULE
};

// TDM4 -> PASSTHROUGH(Static) -> TDM4
static graph_config_t graph_5 = {
    A2B_PROP_CONFIG
    STATIC_PASSTHRU_MODULE
};

// TDM4 -> PASSTHROUGH(Dynamic) -> TDM4
static graph_config_t graph_6 = {
    A2B_PROP_CONFIG
    DYNAMIC_PASSTHRU_MODULE
};

// TDM4 -> SAMPLE(Static) -> TDM4
static graph_config_t graph_7 = {
    A2B_PROP_CONFIG
    STATIC_SAMPLE_MODULE
};

// TDM4 -> SAMPLE(Dynamic) -> TDM4
static graph_config_t graph_8 = {
    A2B_PROP_CONFIG
    DYNAMIC_SAMPLE_MODULE
};

// ADSP -> GAIN(Dynamic) -> TDM1
static graph_config_t graph_9 = {
	ADSP_PROP_CONFIG
    DYNAMIC_GAIN_MODULE
};

int set_msg_link_connections(graph_config_t *gh_cfg)
{

    ams_msg_link_connection_t *msg_link = gh_cfg->msg_link;

    msg_link[0].source.hw_interface_id = gh_cfg->endpoint[1].tdm_params.hw_interface_id;
    msg_link[0].source.type = AMS_ENDPOINT_TYPE_SOURCE;
    msg_link[0].destination.id = gh_cfg->module[0].id;
    msg_link[0].destination.module_id = gh_cfg->module[0].capiv2_info.id;
    msg_link[0].destination.port_type = AMS_MODULE_INPUT_PORT;
    msg_link[0].destination.port_index = 0;

    msg_link[1].source.hw_interface_id = gh_cfg->endpoint[0].tdm_params.hw_interface_id;
    msg_link[1].source.type = AMS_ENDPOINT_TYPE_SINK;
    msg_link[1].destination.id = gh_cfg->module[0].id;
    msg_link[1].destination.module_id = gh_cfg->module[0].capiv2_info.id;
    msg_link[1].destination.port_type = AMS_MODULE_OUTPUT_PORT;
    msg_link[1].destination.port_index = 0;

    gh_cfg->graph_prop[gh_cfg->prop_nums - 1].prop_id = AMS_GRAPH_PROPERTY_ID_TIMESTAMP_MESSAGE_LINK_BUILD;
    gh_cfg->graph_prop[gh_cfg->prop_nums - 1].u.ams_build_msg_link.num_link = MAX_MSG_LINK_NUM;
    gh_cfg->graph_prop[gh_cfg->prop_nums - 1].u.ams_build_msg_link.msg_link_ptr = msg_link;
    gh_cfg->graph_prop[gh_cfg->prop_nums - 1].appy_after_start = 0;

    return 0;
}

graph_config_t *get_graph_config(int use_case)
{
    //graph_config_t *ret_graph = NULL;
    graph_config_t *ret_graph ;
    switch (use_case)
    {
    case 1:
        ret_graph = &graph_1;
        break;
    case 2:
        ret_graph = &graph_2;
        break;
    case 3:
        ret_graph = &graph_3;
        break;
    case 4:
        ret_graph = &graph_4;
        break;
    case 5:
        ret_graph = &graph_5;
        break;
    case 6:
        ret_graph = &graph_6;
        break;
    case 7:
        ret_graph = &graph_7;
        break;
    case 8:
        ret_graph = &graph_8;
        break;
    case 9:
		ret_graph = &graph_9;
		break;
    default:
        break;
    }

    set_msg_link_connections(ret_graph);

    return ret_graph;
}
