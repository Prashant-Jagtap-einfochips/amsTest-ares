# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)
# include $(AMSS_ROOT)/amss_defs.mk


INSTALL_ROOT_nto = $(BSP_ROOT)/install
USE_INSTALL_ROOT=1

#===== Macros for install directory and library naming
NAME=ams2_rnc_lib
ifndef AUDIO_DRIVER_INC_AR
AUDIO_DRIVER_INC_AR= $(PROJECT_ROOT)/../inc
endif

#===== USEFILE - the file containing the usage message for the application.
USEFILE=

#===== PINFO - the file containing the packaging information for the application.
define PINFO
PINFO DESCRIPTION=AMS2 rnc app
endef

#===== CCFLAGS - add the flags to the C compiler command line.
CCFLAGS+=-Werror

ifeq (__TOOLCHAIN_$(qnx_toolchain)__ , __TOOLCHAIN_HYP710__)
#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH+= \
				$(PROJECT_ROOT)/src \
                $(PROJECT_ROOT)

#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
EXTRA_INCVPATH+=\
                $(PROJECT_ROOT)/../public/amss/multimedia/audio_driver_ar/      \
                $(AUDIO_DRIVER_INC_AR) \
                $(PROJECT_ROOT)/inc \
                $(PROJECT_ROOT)/src \
                $(AUDIO_DRIVER_INC_AR)/../ams2_lib/inc \
                $(AUDIO_DRIVER_INC_AR)/../ams2_lib/src \
                $(AUDIO_DRIVER_INC_AR)/../csd2/osal/inc \
                $(AUDIO_DRIVER_INC_AR)/../csd2_ipc/csd2IpcClient/inc \
                $(AUDIO_DRIVER_INC_AR)/../csd2_ipc/csd2IpcClient \
                $(AUDIO_DRIVER_INC_AR)/../audio_reach/ar_osal/api \
                $(AUDIO_DRIVER_INC_AR)/../audio_reach/spf/api/modules \
                $(AUDIO_DRIVER_INC_AR)/../audio_reach/gpr/api \
                $(INSTALL_ROOT_nto)/usr/include/amss/core \
                $(INSTALL_ROOT_nto)/usr/include/amss \
                $(INSTALL_ROOT_nto)/usr/include/amss/core \
                $(INSTALL_ROOT_nto)/usr/include/amss/multimedia/audio_driver_ar \
                $(INSTALL_ROOT_nto)/usr/include/amss/multimedia/protected/common \
                $(AUDIO_DRIVER_INC_AR)/../../../audio_common/audio_expander/inc \
                $(AMSS_ROOT)/platform/qal/clients/i2c_client/public/amss \
                $(AMSS_INC) \
                $(AMSS_ROOT)/inc \
                $(AMSS_ROOT)/multimedia/common/source/qnx/osabstraction/protected




# LIBS+= acdb ar_osal ar_util amfs2 avmm_lib audio_utils bmetrics csd2IpcClient ^commonUtils ^diag_lsm gpr gsl glink ^libstd mmap_peer ^OSAbstraction ^pmem_client pmemext pps smmu_client ^slog2 ^ssr ss_drv_utilS ^sysctrlS tzbsplib uhab

LIBS+= ams2 bmetrics ^csd2IpcClient diag_lsm ^dll_utilsS ^glinkS libstd ^mmap_peerS ^pmem_client pps ^OSAbstraction ^slog2 ^smemS ssr ss_drv_utilS ^sysctrlS tzbsplib audio_expanderS i2c_client

# LDFLAGS+=-Wl,--whole-archive -Bstatic \
#          -lacdbS \
#          -laudio_log_utilS \
#          -lar_osalS \
#          -lar_utilS \
#          -lamfs2S \
#          -lavmm_libS \
#          -laudio_utilsS\
#          -lcommonUtilsS\
#          -lgprS \
#          -lgslS \
#          -lsmmu_clientS
endif

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)
include $(MKFILES_ROOT)/qtargets.mk

ifndef MULTIMEDIA_INSTALLDIR_ROOT
#include ../../../installdir.mk
endif

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))
