

#ifndef FLS_TYPES_H
#define FLS_TYPES_H

#include "Std_Types.hpp"

#include "Fls_PBTypes.hpp"
#include "r_typedefs.hpp"
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#include "r_fcl_types.hpp"
#endif
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#include "r_fdl_types.hpp"
#endif

#if(FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)

#define FLS_TYPES_AR_RELEASE_MAJOR_VERSION    FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_TYPES_AR_RELEASE_MINOR_VERSION    FLS_AR_RELEASE_MINOR_VERSION
#define FLS_TYPES_AR_RELEASE_REVISION_VERSION \
                                     FLS_AR_RELEASE_REVISION_VERSION

#elif(FLS_AR_VERSION == FLS_AR_LOWER_VERSION)

#define FLS_TYPES_AR_MAJOR_VERSION  FLS_AR_MAJOR_VERSION_VALUE
#define FLS_TYPES_AR_MINOR_VERSION  FLS_AR_MINOR_VERSION_VALUE
#define FLS_TYPES_AR_PATCH_VERSION  FLS_AR_PATCH_VERSION_VALUE
#endif

#define FLS_TYPES_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION
#define FLS_TYPES_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION

typedef struct STag_Fls_ConfigType{
  uint32 ulStartOfDbToc;

  P2FUNC (void, FLS_APPL_CODE, pJobEndNotificationPointer)(void);

  P2FUNC (void, FLS_APPL_CODE, pJobErrorNotificationPointer)(void);
  #if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

  P2FUNC (void, FLS_APPL_CODE, pEccSEDNotificationPointer)(uint32);

  P2FUNC (void, FLS_APPL_CODE, pEccDEDNotificationPointer)(uint32);

  uint32 ulFlsDFMaxReadBytes;

  uint32 ulFlsDFReadTimeoutValue;

  uint32 ulFlsDFBlankCheckReadTimeoutValue;
  #if(FLS_SUSPEND_API == STD_ON)

  uint32 ulFlsDFSuspendTimeoutValue;
  #endif
  #if(FLS_CANCEL_API == STD_ON)

  uint32 ulFlsDFCancelTimeoutValue;
  #endif
  #if(FLS_INTERRUPT_MODE == STD_ON)

  P2VAR(uint16, AUTOMATIC, FLS_CONFIG_DATA)pFlEndImrAddress;

  uint16 usFlEndImrMask;
  #endif
  #endif
  #if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

  uint32 ulFlsCFMaxReadBytes;

  uint32 ulFlsCFReadTimeoutValue;

  uint32 ulFlsCFCancelTimeoutValue;
  #endif
}Fls_ConfigType;

typedef struct STag_Fls_GVarProperties
{
  P2CONST(uint8, AUTOMATIC, FLS_INIT_DATA) pBufferAddress;

  P2CONST(uint8, AUTOMATIC, FLS_INIT_DATA) pTempBufferAddress;

  uint32 Fls_GulSrcDestAddress;

  uint32 Fls_GulReadAddress;

  uint32 Fls_EraseStartAddress;

  uint32 Fls_EraseEndAddress;

  uint32 Fls_GulCurrentLength;

  uint32 Fls_GulRequestedLength;
  #if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

  uint8 Fls_GucOffset;

  Fls_FlashReadType Fls_ReadType;

  uint8 Fls_MutexFlag;

  Fls_CommandType Fls_GenBackUpCmd;
  #endif

  Fls_CommandType Fls_GenCommand;
  Fls_FlashType Fls_AccessType;

  MemIf_JobResultType Fls_GenJobResult;

  MemIf_StatusType Fls_GenState;

  boolean Fls_GblCommandInitiated;
  #if(FLS_FHVE_REGS == SUPPORTED)

  boolean Fls_GblFlashEnable;
  #else
  #if(FLS_FLMD_REGS == SUPPORTED)
  #if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                           (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

  boolean Fls_GblFlashEnable;
  #endif
  #endif
  #endif

  boolean Fls_GblProcessContinue;
  #if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))

  boolean Fls_GblTimeOutMonitor;
  #endif
}Fls_GVarProperties;

typedef struct STag_Fls_GstVar
{
  #if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

  VAR(r_fcl_request_t, FLS_INIT_DATA) GstfclRequest;

  VAR(r_fcl_status_t, FLS_INIT_DATA) GucCFStatus;
  #endif
  #if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

  VAR(r_fdl_request_t, FLS_INIT_DATA) GstfdlRequest;

  VAR(r_fdl_request_t, FLS_INIT_DATA) GstfdlNewRequest;

  VAR(r_fdl_status_t, FLS_INIT_DATA) GucDFStatus;
  #endif

}Fls_GstVariable;

#endif

