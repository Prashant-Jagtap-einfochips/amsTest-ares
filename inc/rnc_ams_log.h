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
 * @file    rnc_ams_log.c
 * @brief   rnc_ams_log.
 * @details  rnc_ams_log header
 * @version 1.0
 * @author  gaochengbo
 * @date    2023-04-13
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2021-12-24               zhanghuizhen         Create it.
 */

#ifndef _RNC_AMS_LOG_H
#define _RNC_AMS_LOG_H

#include <stdio.h>
#include <string.h>
#include <pthread.h>

unsigned int rnc_ams_control_log_enable = 1;
unsigned int rnc_ams_control_log_dbg_lvl = 1; // 0 - only errors, 1 - info, >1 -all
unsigned int rnc_ams_control_log_show_tid = 0;

#define RNC_WRAPPER_LOG_SKIP_THREAD_ID (1)

#ifndef __QNX__
#define RNC_WRAPPER_LIB_LOGE(format, ...)                                                                                   \
    {                                                                                                                       \
        if (rnc_ams_control_log_enable)                                                                                     \
        {                                                                                                                   \
            if (rnc_ams_control_log_show_tid)                                                                               \
            {                                                                                                               \
                uint32_t tid = 0;                                                                                           \
                pthread_t self;                                                                                             \
                self = pthread_self();                                                                                      \
                tid = (uint32_t)self;                                                                                       \
                printf("E:tid=%u:%s:%s,line %d : " format "\n", tid, "rnc_wrapper_lib", __func__, __LINE__, ##__VA_ARGS__); \
            }                                                                                                               \
            else                                                                                                            \
            {                                                                                                               \
                printf("E:%s:%s,line %d : " format "\n", "rnc_wrapper_lib", __func__, __LINE__, ##__VA_ARGS__);             \
            }                                                                                                               \
        }                                                                                                                   \
    }
#define RNC_WRAPPER_LIB_LOGI(format, ...)                                                                                  \
    {                                                                                                                      \
        if (rnc_ams_control_log_enable && rnc_ams_control_log_dbg_lvl >= 1)                                                \
        {                                                                                                                  \
            if (rnc_ams_control_log_show_tid)                                                                              \
            {                                                                                                              \
                uint32_t tid = 0;                                                                                          \
                pthread_t self;                                                                                            \
                self = pthread_self();                                                                                     \
                tid = (uint32_t)self;                                                                                      \
                printf("I:tid=%u:%s:%s,line %d: " format "\n", tid, "rnc_wrapper_lib", __func__, __LINE__, ##__VA_ARGS__); \
            }                                                                                                              \
            else                                                                                                           \
            {                                                                                                              \
                printf("I:%s:%s,line %d: " format "\n", "rnc_wrapper_lib", __func__, __LINE__, ##__VA_ARGS__);             \
            }                                                                                                              \
        }                                                                                                                  \
    }

#define RNC_WRAPPER_LIB_LOGD(format, ...)                                                                                 \
    {                                                                                                                     \
        if (rnc_ams_control_log_enable && rnc_ams_control_log_dbg_lvl > 1)                                                \
        {                                                                                                                 \
            if (rnc_ams_control_log_show_tid)                                                                             \
            {                                                                                                             \
                uint32_t tid = 0;                                                                                         \
                pthread_t self;                                                                                           \
                self = pthread_self();                                                                                    \
                tid = (uint32_t)self;                                                                                     \
                printf("D:tid=%u:%s:%s,line %d " format "\n", tid, "rnc_wrapper_lib", __func__, __LINE__, ##__VA_ARGS__); \
            }                                                                                                             \
            else                                                                                                          \
            {                                                                                                             \
                printf("D:%s:%s,line %d " format "\n", "rnc_wrapper_lib", __func__, __LINE__, ##__VA_ARGS__);             \
            }                                                                                                             \
        }                                                                                                                 \
    }

#else
// #include "msg.h"
//#include "logger_utils.h"

// #define AMS_LIB_LOGE(format, ...)

// #define AMS_LIB_LOGI(format, ...)

// #define AMS_LIB_LOGD(format, ...)
#define RNC_WRAPPER_LIB_LOGE(xx_fmt, ...)                                                                                 \
    {                                                                                                                     \
        if (rnc_ams_control_log_enable)                                                                                   \
        {                                                                                                                 \
            if (rnc_ams_control_log_show_tid)                                                                             \
            {                                                                                                             \
                uint32_t tid = 0;                                                                                         \
                pthread_t self;                                                                                           \
                self = pthread_self();                                                                                    \
                tid = (uint32_t)self;                                                                                     \
                logger_log(QCLOG_AMSS_MM_APPS_CAD, 0, _SLOG_ERROR, "%s:tid=%u:E: " xx_fmt, __func__, tid, ##__VA_ARGS__); \
            }                                                                                                             \
            else                                                                                                          \
            {                                                                                                             \
                logger_log(QCLOG_AMSS_MM_APPS_CAD, 0, _SLOG_ERROR, "%s:E: " xx_fmt, __func__, ##__VA_ARGS__);             \
            }                                                                                                             \
        }                                                                                                                 \
    }
#define RNC_WRAPPER_LIB_LOGI(xx_fmt, ...)                                                                                 \
    {                                                                                                                     \
        if (rnc_ams_control_log_enable && rnc_ams_control_log_dbg_lvl >= 1)                                               \
        {                                                                                                                 \
            if (rnc_ams_control_log_show_tid)                                                                             \
            {                                                                                                             \
                uint32_t tid = 0;                                                                                         \
                pthread_t self;                                                                                           \
                self = pthread_self();                                                                                    \
                tid = (uint32_t)self;                                                                                     \
                logger_log(QCLOG_AMSS_MM_APPS_CAD, 0, _SLOG_ERROR, "%s:tid=%u:I: " xx_fmt, __func__, tid, ##__VA_ARGS__); \
            }                                                                                                             \
            else                                                                                                          \
            {                                                                                                             \
                logger_log(QCLOG_AMSS_MM_APPS_CAD, 0, _SLOG_ERROR, "%s:I: " xx_fmt, __func__, ##__VA_ARGS__);             \
            }                                                                                                             \
        }                                                                                                                 \
    }

#define RNC_WRAPPER_LIB_LOGD(xx_fmt, ...)                                                                                 \
    {                                                                                                                     \
        if (rnc_ams_control_log_enable && rnc_ams_control_log_dbg_lvl > 1)                                                \
        {                                                                                                                 \
            if (rnc_ams_control_log_show_tid)                                                                             \
            {                                                                                                             \
                uint32_t tid = 0;                                                                                         \
                pthread_t self;                                                                                           \
                self = pthread_self();                                                                                    \
                tid = (uint32_t)self;                                                                                     \
            }                                                                                                             \
            else                                                                                                          \
            {                                                                                                             \
            }                                                                                                             \
        }                                                                                                                 \
    }
#endif

#define RNC_WRAPPER_LIB_TEST_ASSERT(cond)          \
    {                                              \
        if (!(cond))                               \
        {                                          \
            printf("%s:TEST FAILED \n", __func__); \
        }                                          \
        else                                       \
        {                                          \
            printf("%s:TEST OK \n", __func__);     \
        }                                          \
    }

#endif
