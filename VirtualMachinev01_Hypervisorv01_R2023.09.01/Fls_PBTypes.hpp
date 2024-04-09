

#ifndef FLS_PBTYPES_H
#define FLS_PBTYPES_H

//#include "Fls.hpp" RST Test commented out -> circel including, because fls.h includes fls_types.h includes fls_pbtypes.h

#if(FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)

#define FLS_PBTYPES_AR_RELEASE_MAJOR_VERSION  FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_PBTYPES_AR_RELEASE_MINOR_VERSION  FLS_AR_RELEASE_MINOR_VERSION
#define FLS_PBTYPES_AR_RELEASE_REVISION_VERSION \
                                            FLS_AR_RELEASE_REVISION_VERSION

#elif(FLS_AR_VERSION == FLS_AR_LOWER_VERSION)

#define FLS_PBTYPES_AR_MAJOR_VERSION  FLS_AR_MAJOR_VERSION_VALUE
#define FLS_PBTYPES_AR_MINOR_VERSION  FLS_AR_MINOR_VERSION_VALUE
#define FLS_PBTYPES_AR_PATCH_VERSION  FLS_AR_PATCH_VERSION_VALUE
#endif

#define FLS_PBTYPES_SW_MAJOR_VERSION  FLS_SW_MAJOR_VERSION
#define FLS_PBTYPES_SW_MINOR_VERSION  FLS_SW_MINOR_VERSION

#define FLS_DBTOC_VALUE                 ((FLS_VENDOR_ID_VALUE << 22) | \
                                          (FLS_MODULE_ID_VALUE << 14) | \
                                          (FLS_SW_MAJOR_VERSION_VALUE << 8) | \
                                          (FLS_SW_MINOR_VERSION_VALUE << 3))

#define FLS_INITIALIZED               (boolean)1
#define FLS_UNINITIALIZED             (boolean)0

#define FLS_ZERO                               (uint8)0
#define FLS_ONE                                (uint8)1
#define FLS_TWO                                (uint8)2
#define FLS_THREE                              (uint8)3
#define FLS_FOUR                               (uint8)4

#define FLS_FALSE                             (boolean)0
#define FLS_TRUE                              (boolean)1

#define SUPPORTED                              0
#define NOT_SUPPORTED                          1

#if(FLS_FLMD_REGS == SUPPORTED)

#define FLS_FLMD0_PROTECTION_ON                (uint8)0

#define FLS_FLMD0_PROTECTION_OFF               (uint8)1

#define FLS_FLMD0_PCMD_CONSTANT                (uint8)0xa5
#endif

#if(FLS_FHVE_REGS == SUPPORTED)

#define FLS_FLASH_PROTECTION_ON                (uint8)0

#define FLS_FLASH_PROTECTION_OFF               (uint8)1
#endif

#define FDL_SUPPORTED                          0
#define FDL_NOT_SUPPORTED                      1

#define FLS_DATAFLASH_ACCESS                   0
#define FLS_CODEFLASH_ACCESS                   1
#define FLS_CFDF_ACCESS                        2
#define FLS_ISR_TIMEOUT_VALUE                  0x000000FFUL

#if(FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)

#define FLS_ENTER_CRITICAL_SECTION(Exclusive_Area) \
                                   SchM_Enter_Fls_##Exclusive_Area();
#define FLS_EXIT_CRITICAL_SECTION(Exclusive_Area) \
                                   SchM_Exit_Fls_##Exclusive_Area();

#elif(FLS_AR_VERSION == FLS_AR_LOWER_VERSION)

#define FLS_ENTER_CRITICAL_SECTION(Exclusive_Area) \
                                                  SchM_Enter_Fls(Exclusive_Area);
#define FLS_EXIT_CRITICAL_SECTION(Exclusive_Area) SchM_Exit_Fls(Exclusive_Area);

#endif

typedef enum ETag_Fls_FlashType
{
  FLS_DF_ACCESS = 0
   ,  FLS_CF_ACCESS
}Fls_FlashType;

typedef enum ETag_Fls_FlashReadType
{
  FLS_MISALIGNED_READ = 0
   ,  FLS_ALIGNED_READ
}Fls_FlashReadType;

typedef enum ETag_Fls_CommandType
{
  FLS_COMMAND_NONE = 0
   ,  FLS_COMMAND_ERASE
   ,  FLS_COMMAND_WRITE
   ,  FLS_COMMAND_READ
   ,  FLS_COMMAND_COMPARE
   ,  FLS_COMMAND_BLANKCHECK
   ,  FLS_COMMAND_READ_IMM
}Fls_CommandType;

#define FLS_START_SEC_BUFFER_CODE
#include "MemMap.hpp"

extern VAR(uint32, AUTOMATIC)Fls_GulTempBuffer[];

#define FLS_STOP_SEC_BUFFER_CODE
#include "MemMap.hpp"

#endif

