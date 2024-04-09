

#ifndef FLS_H
#define FLS_H

#define FLS_AR_FOUR_ZERO_THREE    403
#define FLS_AR_THREE_TWO_TWO      322

#define FLS_AR_HIGHER_VERSION     FLS_AR_FOUR_ZERO_THREE
#define FLS_AR_LOWER_VERSION      FLS_AR_THREE_TWO_TWO

#include "Std_Types.hpp"

#include "CfgMcalFls.hpp"

#include "Fls_Types.hpp"
#if(FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)
#if(FLS_DEV_ERROR_DETECT == STD_ON)

#include "Fls_Debug.hpp"
#endif
#endif
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#include "fcl_descriptor.hpp"
#endif
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#include "fdl_descriptor.hpp"
#endif

#define FLS_VENDOR_ID              FLS_VENDOR_ID_VALUE
#define FLS_MODULE_ID              FLS_MODULE_ID_VALUE
#define FLS_INSTANCE_ID            FLS_INSTANCE_ID_VALUE

#if(FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)

#define FLS_AR_RELEASE_MAJOR_VERSION    4
#define FLS_AR_RELEASE_MINOR_VERSION    0
#define FLS_AR_RELEASE_REVISION_VERSION 3

#elif(FLS_AR_VERSION == FLS_AR_LOWER_VERSION)

#define FLS_AR_MAJOR_VERSION    2
#define FLS_AR_MINOR_VERSION    4
#define FLS_AR_PATCH_VERSION    0

#endif

#define FLS_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION_VALUE
#define FLS_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION_VALUE
#define FLS_SW_PATCH_VERSION    FLS_SW_PATCH_VERSION_VALUE

#define FLS_INIT_SID                        (uint8)0x00

#define FLS_ERASE_SID                       (uint8)0x01

#define FLS_WRITE_SID                       (uint8)0x02

#define FLS_CANCEL_SID                      (uint8)0x03

#define FLS_GET_STATUS_SID                  (uint8)0x04

#define FLS_GET_JOB_RESULT_SID              (uint8)0x05

#define FLS_MAINFUNCTION_SID                (uint8)0x06

#define FLS_READ_SID                        (uint8)0x07

#define FLS_COMPARE_SID                     (uint8)0x08

#define FLS_SET_MODE_SID                    (uint8)0x09

#define FLS_GET_VERSION_INFO_SID            (uint8)0x10

#define FLS_READ_IMM_SID                    (uint8)0x11

#define FLS_BLANK_CHECK_SID                 (uint8)0x12

#define FLS_SUSPEND_SID                     (uint8)0x13

#define FLS_RESUME_SID                      (uint8)0x14

#define FLS_E_PARAM_CONFIG                  (uint8)0x01

#define FLS_E_PARAM_ADDRESS                 (uint8)0x02

#define FLS_E_PARAM_LENGTH                  (uint8)0x03

#define FLS_E_PARAM_DATA                    (uint8)0x04

#define FLS_E_UNINIT                        (uint8)0x05

#define FLS_E_BUSY                          (uint8)0x06

#define FLS_E_VERIFY_ERASE_FAILED           (uint8)0x07

#define FLS_E_VERIFY_WRITE_FAILED           (uint8)0x08

#define FLS_E_TIMEOUT                       (uint8)0x09

#define FLS_E_PARAM_POINTER                 (uint8)0x0A

#define FLS_E_INVALID_DATABASE              (uint8)0xEF

typedef uint32 Fls_AddressType;

typedef uint32 Fls_LengthType;

#if(FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
#define MEMIF_JOB_CANCELED MEMIF_JOB_CANCELLED
#endif

#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"

extern FUNC(void, FLS_PUBLIC_CODE) Fls_Init
(P2CONST(Fls_ConfigType, AUTOMATIC, FLS_APPL_CONST) ConfigPtr);

extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Erase
(Fls_AddressType TargetAddress, Fls_LengthType Length);

extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Write
(Fls_AddressType TargetAddress,
P2CONST(uint8, AUTOMATIC, FLS_APPL_DATA) SourceAddressPtr,
Fls_LengthType Length);

#if(FLS_CANCEL_API == STD_ON)
extern FUNC(void, FLS_PUBLIC_CODE) Fls_Cancel(void);
#endif

#if(FLS_GET_STATUS_API == STD_ON)
extern FUNC(MemIf_StatusType, FLS_PUBLIC_CODE) Fls_GetStatus(void);
#endif

#if(FLS_GET_JOB_RESULT_API == STD_ON)
extern FUNC(MemIf_JobResultType, FLS_PUBLIC_CODE) Fls_GetJobResult(void);
#endif

extern FUNC(void, FLS_PUBLIC_CODE) Fls_MainFunction(void);

extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Read
(Fls_AddressType SourceAddress,
P2CONST(uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr,
Fls_LengthType Length);

#if(FLS_COMPARE_API == STD_ON)
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Compare
(Fls_AddressType SourceAddress,
P2CONST(uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr,
Fls_LengthType Length);
#endif

#if(FLS_SET_MODE_API == STD_ON)
extern FUNC(void, FLS_PUBLIC_CODE) Fls_SetMode (MemIf_ModeType Mode);
#endif

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_READIMMEDIATE_API == STD_ON)
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_ReadImmediate
(Fls_AddressType SourceAddress,
P2CONST(uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr,
Fls_LengthType Length);
#endif
#if(FLS_BLANKCHECK_API == STD_ON)
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_BlankCheck
(Fls_AddressType TargetAddress, Fls_LengthType Length);
#endif

#if(FLS_SUSPEND_API == STD_ON)
extern FUNC(void, FLS_PUBLIC_CODE) Fls_Suspend(void);
#endif

#if(FLS_RESUME_API == STD_ON)
extern FUNC(void, FLS_PUBLIC_CODE) Fls_Resume(void);
#endif

#endif
extern FUNC(void, FLS_PUBLIC_CODE)Fls_GetVersionInfo
(P2VAR(Std_VersionInfoType, AUTOMATIC, FLS_APPL_DATA) VersioninfoPtr);

#if(FLS_VERSION_INFO_API == STD_ON)
#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#define Fls_GetVersionInfo(VersioninfoPtr)\
 { \
   (VersioninfoPtr)->vendorID = (uint16)FLS_VENDOR_ID; \
   (VersioninfoPtr)->moduleID = (uint16)FLS_MODULE_ID; \
   (VersioninfoPtr)->sw_major_version = FLS_SW_MAJOR_VERSION; \
   (VersioninfoPtr)->sw_minor_version = FLS_SW_MINOR_VERSION; \
   (VersioninfoPtr)->sw_patch_version = FLS_SW_PATCH_VERSION; \
 }
#else
#define Fls_GetVersionInfo(VersioninfoPtr)\
 { \
   (VersioninfoPtr)->vendorID = (uint16)FLS_VENDOR_ID; \
   (VersioninfoPtr)->moduleID = (uint16)FLS_MODULE_ID; \
   (VersioninfoPtr)->instanceID = (uint8)FLS_INSTANCE_ID; \
   (VersioninfoPtr)->sw_major_version = FLS_SW_MAJOR_VERSION; \
   (VersioninfoPtr)->sw_minor_version = FLS_SW_MINOR_VERSION; \
   (VersioninfoPtr)->sw_patch_version = FLS_SW_PATCH_VERSION; \
 }

#endif
#endif

#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"

#define FLS_START_SEC_DBTOC_DATA_UNSPECIFIED
#include "MemMap.hpp"

extern CONST(Fls_ConfigType, FLS_CONST) Fls_GstConfiguration[];

#define FLS_STOP_SEC_DBTOC_DATA_UNSPECIFIED
#include "MemMap.hpp"

#endif

