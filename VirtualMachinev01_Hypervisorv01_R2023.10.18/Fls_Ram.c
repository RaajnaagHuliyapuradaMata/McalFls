#include "Std_Types.hpp"

#include "Fls.hpp"

#include "Fls_Ram.hpp"

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)
#define FLS_RAM_C_AR_RELEASE_MAJOR_VERSION    FLS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLS_RAM_C_AR_RELEASE_MINOR_VERSION    FLS_AR_RELEASE_MINOR_VERSION_VALUE
#define FLS_RAM_C_AR_RELEASE_REVISION_VERSION \
                                           FLS_AR_RELEASE_REVISION_VERSION_VALUE
#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#define FLS_RAM_C_AR_MAJOR_VERSION    FLS_AR_MAJOR_VERSION_VALUE
#define FLS_RAM_C_AR_MINOR_VERSION    FLS_AR_MINOR_VERSION_VALUE
#define FLS_RAM_C_AR_PATCH_VERSION    FLS_AR_PATCH_VERSION_VALUE
#endif

#define FLS_RAM_C_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION_VALUE
#define FLS_RAM_C_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION_VALUE

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)
#if(FLS_RAM_AR_RELEASE_MAJOR_VERSION != FLS_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fls_Ram.c : Mismatch in Release Major Version"
#endif

#if(FLS_RAM_AR_RELEASE_MINOR_VERSION != FLS_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Fls_Ram.c : Mismatch in Release Minor Version"
#endif

#if(FLS_RAM_AR_RELEASE_REVISION_VERSION != \
                                          FLS_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Fls_Ram.c : Mismatch in Release Revision Version"
#endif

#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)
#if(FLS_RAM_AR_MAJOR_VERSION != FLS_RAM_C_AR_MAJOR_VERSION)
  #error "Fls_Ram.c : Mismatch in Specification Major Version"
#endif

#if(FLS_RAM_AR_MINOR_VERSION != FLS_RAM_C_AR_MINOR_VERSION)
  #error "Fls_Ram.c : Mismatch in Specification Minor Version"
#endif

#if(FLS_RAM_AR_PATCH_VERSION != FLS_RAM_C_AR_PATCH_VERSION)
  #error "Fls_Ram.c : Mismatch in Specification Patch Version"
#endif
#endif

#if(FLS_RAM_SW_MAJOR_VERSION != FLS_RAM_C_SW_MAJOR_VERSION)
  #error "Fls_Ram.c : Mismatch in Software Major Version"
#endif

#if(FLS_RAM_SW_MINOR_VERSION != FLS_RAM_C_SW_MINOR_VERSION)
  #error "Fls_Ram.c : Mismatch in Software Minor Version"
#endif

#define FLS_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"

P2CONST(Fls_ConfigType, FLS_VAR, FLS_CONFIG_CONST) Fls_GpConfigPtr;

#define FLS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"

#define FLS_START_SEC_VAR_UNSPECIFIED
#include "MemMap.hpp"

VAR(Fls_GstVariable, FLS_INIT_DATA) Fls_GstVar;

VAR(Fls_GVarProperties, FLS_INIT_DATA) Fls_GVar = {FLS_ZERO};

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

VAR(boolean, FLS_INIT_DATA) Fls_GblInitStatus = FLS_UNINITIALIZED;

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

VAR(uint32, FLS_NOINIT_DATA) Fls_GulTimeout;

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
P2FUNC(void, AUTOMATIC, Fls_GpRFclExecute) (r_fcl_request_t *);
P2FUNC(void, AUTOMATIC, Fls_GpRFclHandler) (void);

#endif

#define FLS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.hpp"
#endif

