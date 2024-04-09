

#ifndef FLS_RAM_H
#define FLS_RAM_H

#include "Fls_Types.hpp"
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#include "r_fcl.hpp"
#endif

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#define FLS_RAM_AR_RELEASE_MAJOR_VERSION      FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_RAM_AR_RELEASE_MINOR_VERSION      FLS_AR_RELEASE_MINOR_VERSION
#define FLS_RAM_AR_RELEASE_REVISION_VERSION   FLS_AR_RELEASE_REVISION_VERSION
#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#define FLS_RAM_AR_MAJOR_VERSION   FLS_AR_MAJOR_VERSION_VALUE
#define FLS_RAM_AR_MINOR_VERSION   FLS_AR_MINOR_VERSION_VALUE
#define FLS_RAM_AR_PATCH_VERSION   FLS_AR_PATCH_VERSION_VALUE
#endif

#define FLS_RAM_SW_MAJOR_VERSION   FLS_SW_MAJOR_VERSION
#define FLS_RAM_SW_MINOR_VERSION   FLS_SW_MINOR_VERSION

#define FLS_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"

extern P2CONST(Fls_ConfigType, FLS_VAR, FLS_CONFIG_CONST) Fls_GpConfigPtr;

#define FLS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"

#define FLS_START_SEC_VAR_UNSPECIFIED
#include "MemMap.hpp"

extern VAR(Fls_GstVariable, FLS_INIT_DATA) Fls_GstVar;

extern VAR(Fls_GVarProperties, FLS_INIT_DATA) Fls_GVar;

#define FLS_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.hpp"

#if(FLS_DEV_ERROR_DETECT == STD_ON)
#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#define FLS_START_SEC_VAR_BOOLEAN
#include "MemMap.hpp"

#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#define FLS_START_SEC_VAR_1BIT
#include "MemMap.hpp"
#endif

extern VAR(boolean, FLS_INIT_DATA) Fls_GblInitStatus;

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#define FLS_STOP_SEC_VAR_BOOLEAN
#include "MemMap.hpp"

#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#define FLS_STOP_SEC_VAR_1BIT
#include "MemMap.hpp"
#endif

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#define FLS_START_SEC_VAR_NOINIT_32
#include "MemMap.hpp"

#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#define FLS_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.hpp"
#endif

extern VAR(uint32, FLS_NOINIT_DATA) Fls_GulTimeout;

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#define FLS_STOP_SEC_VAR_NOINIT_32
#include "MemMap.hpp"

#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#define FLS_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.hpp"
#endif

#endif

#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#define FLS_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"

#if(R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER)
extern P2FUNC(void, AUTOMATIC, Fls_GpRFclExecute) (r_fcl_request_t *);

extern P2FUNC(void, AUTOMATIC, Fls_GpRFclHandler) (void);
#endif

#define FLS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"
#endif

#endif

