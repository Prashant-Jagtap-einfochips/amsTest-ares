#ifndef _AUDIO_EXPANDER_H_
#define _AUDIO_EXPANDER_H_
/**
  @file      audio_expander.h
  @brief
  Contains structure and APIs for audio_expander control
  /
 *===========================================================================
OTE: The @brief description and any detailed descriptions above do not appear
in the PDF.

The CSD_mainpage.dox file contains all file/group descriptions that are
in the output PDF generated using Doxygen and LaTeX. To edit or update
any of the file/group text in the PDF, edit the CSD_mainpage.dox file or
contact Tech Pubs.
===========================================================================*/

/*-----------------------------------------------------------------------------
  Copyright (C) 2020-2021 Qualcomm Technologies Incorporated.
  All rights reserved.
  Qualcomm Confidential and Proprietary.
  -----------------------------------------------------------------------------*/
/*=============================================================================
  EDIT HISTORY FOR MODULE
  This section contains comments describing changes made to this module.
  Notice that changes are listed in reverse chronological order.

  when		who			what, where, why
  --------	-----		---------------------------------------------------
  2020/12/14 congt  initial implementation for audio_expander module for BRAC
  =============================================================================*/
#include "mmdefs.h"

/*DAC ENABLE signal to DAC PCM1681*/
#define CMD_SET_DAC_ENABLE 	0x2001

/*Select Audio Source for DAC*/
#define CMD_SET_SWITCH_SOURCE 	0x2002

/*Enable Audio Source Switch self*/
#define CMD_SET_SWITCH_ENABLE 	0x2003

/**
  @brief dac enable payload
  AUDIO_Expander provides DAC_ENABLE signal to power on DAC
  */
typedef struct dac_enable_payload {
    bool_t enable; /*0, disable; 1 , enable*/
} dac_enable_t;

/**
  @brief switch enable payload
  AUDIO_Expander provides TDM_MUX_EN signal to power on Switch
  */
typedef struct switch_enable_payload {
    bool_t enable; /*0, disable; 1 , enable */
} switch_enable_t;

/**
  @brief enum definition for Switch audio source
  audio source can be SoC MI2S0 or Mercury output
  */
typedef enum switch_audio_source {
    SOC_AUDIO = 0x1000, 	    /*SoC MI2S0 output*/
    MERCURY_AUDIO,	    /*Mercury TDM output*/
} audio_source_t;

/**
  @brief switch source cfg payload
  set Switch audio source
  */
typedef struct switch_source_payload {
    audio_source_t src; /*see audio_source_t definition*/
} switch_source_payload_t;

typedef struct audio_expander_init_config {
    uint16_t i2c_device; /*/dev/i2c* */
    uint16_t i2c_addr; /*i2c slave address*/
} audio_expander_init_config_t;

/**
 * init io expander module
 *
 * @return    0 for success, otherwise error code
 */
int32_t audio_expander_init(audio_expander_init_config_t *init_cfg);

/**
 * Open handle to control audio_expander in BRAC.
 *
 * @param[in] io_handle pointer to the audio_expander module
 * @return    0 for success, otherwis	    e error code
 */
int32_t audio_expander_open(uint32_t *handle);
/**
 * Control parameters from ioctl cmd.
 * @param[in] handle      Pointer to the audio_expander module
 * @param[in] cmd         See macro CMD_* mentioned above
 * @param[in] params      Pointer to payload
 * @param[in] length      Payload length
 * @return    0 for success, otherwise error code
 */
int32_t audio_expander_ioctl(uint32_t handle, uint32_t cmd, void *param, size_t length);

/**
 * Close io expander handle
 *
 * @param[in] audio_expander handle Pointer to the audio_expander module
 * @return    0 for success, otherwise error code
 */
int32_t audio_expander_close(uint32_t io_handle);

/**
 * deinit io expander module
 *
 * @return    0 for success, otherwise error code
 */
int32_t audio_expander_deinit(void);
#endif
