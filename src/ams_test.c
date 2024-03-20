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
 * @file    rnc_demo_test.c
 * @brief   rnc_demo_test.
 * @details  rnc_demo_test app
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
#include <getopt.h>

#include "dlfcn.h"
//#include "sysctrl_i.h"
#include "ams.h"
//#include "ams_util.h"
#include "dll_utils_i.h"
#include "rnc_ams_apl_control.h"
#include "rnc_ams_struct.h"
#include "audio_expander.h"


#define BUFFERSIZE 3

//EIC
static int show_options(void)
{
    printf("ams_rnc_app: AMS test app options \n");
    printf("0: Show test opt \n");
    printf("1: Set usecase \n");
    printf("2: Create graph \n");
    printf("3: Open graph \n");
    printf("4: Start graph \n");
    printf("5: Start A2B \n");
    printf("6: Stop graph \n");
    printf("7: Close graph \n");
    printf("8: Destroy graph \n");
    printf("a: Set param \n");
    printf("b: Get param \n");
    printf("c: Get current module timestamp \n");
    return 0;
}

static int show_graph(void)
{
    printf("Enter usecase id (min=%d, max = %d):\n", AMS_RNC_UC_MIN, AMS_RNC_UC_MAX);

    printf("************* TDM3->TDM1 / Mercury ************\n");
    printf("1: ANALOG  -->  PASSTHRU(Static)   --> ANALOG\n");
    printf("2: ANALOG  -->  PASSTHRU(Dynamic)  --> ANALOG\n");
    printf("3: ANALOG  -->  SAMPLE(Static)     --> ANALOG\n");
    printf("4: ANALOG  -->  RNC(Dynamic)       --> ANALOG\n");
    printf("\n");
    printf("*****************   TDM4 / A2B   **************\n");
    printf("5: A2B     -->  PASSTHRU(Static)   --> A2B\n");
    printf("6: A2B     -->  PASSTHRU(Dynamic)  --> A2B\n");
    printf("7: A2B     -->  SAMPLE(Static)     --> A2B\n");
    printf("8: A2B     -->  RNC(Dynamic)       --> A2B\n");
    printf("**********   ADSP->TDM1 / Mercury   **********\n");
    printf("9: ADSP    -->  GAIN(Dynamic)      --> ANALOG\n");
    return 0;
}

static struct option long_options[] =
{
    {"block_size", required_argument, 0, 's'},
    {"path_select", required_argument, 0, 'p'},
    {0, 0, 0, 0}
};

int main(int argc, char **argv)
{
    int cnt = 0;
    char buffer[BUFFERSIZE];
    char char_buf[BUFFERSIZE];
    int select = 0;
    int opt;
    int option_index = 0;
    ams_status_t rc = 0;
    set_tuningtool_param_t set_param_value;
    get_tuningtool_param_t get_param_value;
    printf("ams_rnc_app: (Waiting for /dev/audio_service)\n");
    Resource_BlockWait("/dev/audio_service");
    printf("ams_rnc_app: (Done waiting for /dev/audio_service)\n");

    //EIC
#if 0
    while ((opt = getopt_long(argc, argv, "s:p:", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 's':
        {
            opt_args.block_size = atoi(optarg);
            printf("ams_rnc_app: Block size has been set to %d\n", opt_args.block_size);
            break;
        }
        case 'p':
        {
            opt_args.expander_type = atoi(optarg);
            rc = ams_rnc_interface.select_output(opt_args.expander_type + SOC_AUDIO);
            printf("ams_rnc_app: audio output to %s rc %d\n", (opt_args.expander_type + SOC_AUDIO == SOC_AUDIO) ? "DAC" : "Mercury", rc);
            break;
        }
        default:
        {
            printf("Unknown option: %c\n", opt);
            break;
        }
        }
    }
#endif

    show_options();
    while (1)
    {
        while (fgets(buffer, BUFFERSIZE, stdin))
        {
            cnt++;
            switch (buffer[0])
            {
            case '0':
                rc = show_options();
                printf("%s\n", (rc == 0 ? "OK" : "NOK"));
                break;
            case '1':
                rc = show_graph();
                fgets(char_buf, BUFFERSIZE, stdin);
                select = char_buf[0] - '0';
                if (select > AMS_RNC_UC_MAX || select < AMS_RNC_UC_MIN)
                {
                    printf("Invalid Usecase :%d\n", select);
                    break;
                }
                if ((opt_args.block_size == 12) && (select == 3 || select == 7))
                {
                    printf("The current module does not support 12 frame size.\n");
                    printf("Please reselect options.\n");
                    show_options();
                    break;
                }
                rc = ams_rnc_interface.set_usecase(select);
                printf("RNC Set usecase %d %s\n", select, (rc == 0 ? "OK" : "NOK"));
                break;
            case '2':
                rc = ams_rnc_interface.graph_init();
                printf("RNC create graph %s\n", rc == 0 ? "OK" : "NOK");
                break;
            case '3':
                rc = ams_rnc_interface.graph_open();
                printf("RNC open graph %s\n", rc == 0 ? "OK" : "NOK");
                break;
            case '4':
                rc = ams_rnc_interface.graph_start();
                printf("RNC start graph %s\n", rc == 0 ? "OK" : "NOK");
                break;
            case '5':
                rc = system("a2b-app -p /data/adi_a2b_busconfig.dat &");
                break;
            case '6':
                rc = ams_rnc_interface.graph_stop();
                printf("RNC stop graph %s\n", rc == 0 ? "OK" : "NOK");
                break;
            case '7':
                rc = ams_rnc_interface.graph_close();
                printf("RNC close graph %s\n", rc == 0 ? "OK" : "NOK");
                break;
            case '8':
                rc = ams_rnc_interface.graph_destroy();
                printf("RNC destroy graph %s\n", rc == 0 ? "OK" : "NOK");
                break;
            case 'a':
                if (select == 1 || select == 2 || select == 5 || select == 6)
                {
                    printf("Passthru module's set/get functions no longer supported .\n");
                    break;
                }
                printf("Enter data value: ");
                fgets(char_buf, BUFFERSIZE, stdin);
                int num = char_buf[0] - '0';
                set_param_value.data = num;
                rc = ams_rnc_interface.set_param(1, set_param_value);
                printf("RNC set module value %s\n", rc == 0 ? "OK" : "NOK");
                break;
            case 'b':
                if (select == 1 || select == 2 || select == 5 || select == 6)
                {
                    printf("Passthru module's set/get functions no longer supported .\n");
                    break;
                }
                rc = ams_rnc_interface.get_param(1, get_param_value);
                printf("RNC get module value %s\n", rc == 0 ? "OK" : "NOK");
                break;
            case 'c':
                rc = ams_rnc_interface.get_current_timestamp();
                printf("RNC current module timestamp %s\n", rc == 0 ? "OK" : "NOK");
                break;
            default:
                break;
            }
        }
    }
}
