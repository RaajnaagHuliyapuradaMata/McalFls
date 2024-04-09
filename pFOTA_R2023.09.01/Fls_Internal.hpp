

#ifndef FLS_INTERNAL_H
#define FLS_INTERNAL_H

#include "Fls.hpp"
#include "Fls_Types.hpp"
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#include "r_fcl.hpp"
#endif
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#include "r_fdl.hpp"
#endif

#if(FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)

#define FLS_INTERNAL_AR_RELEASE_MAJOR_VERSION    FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_INTERNAL_AR_RELEASE_MINOR_VERSION    FLS_AR_RELEASE_MINOR_VERSION
#define FLS_INTERNAL_AR_RELEASE_REVISION_VERSION \
                                     FLS_AR_RELEASE_REVISION_VERSION

#elif(FLS_AR_VERSION == FLS_AR_LOWER_VERSION)

#define FLS_INTERNAL_AR_MAJOR_VERSION  FLS_AR_MAJOR_VERSION_VALUE
#define FLS_INTERNAL_AR_MINOR_VERSION  FLS_AR_MINOR_VERSION_VALUE
#define FLS_INTERNAL_AR_PATCH_VERSION  FLS_AR_PATCH_VERSION_VALUE
#endif

#define FLS_INTERNAL_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION
#define FLS_INTERNAL_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_COMPARE_API == STD_ON)
extern FUNC(r_fdl_status_t, FLS_PRIVATE_CODE)Fls_DFProcessCompareCommand(void);
#endif
extern FUNC(r_fdl_status_t, FLS_PRIVATE_CODE)Fls_DFProcessReadCommand(void);
#if(FLS_READIMMEDIATE_API == STD_ON)
extern FUNC(r_fdl_status_t, FLS_PRIVATE_CODE) Fls_DFProcessReadImmCommand(void);
#endif

extern FUNC(uint32, FLS_PRIVATE_CODE)Fls_DF_read_memory_u32(uint32 address);
extern FUNC(void, FLS_PRIVATE_CODE)Fls_DF_write_memory_u32(uint32 address
   ,                                                               uint32 value);

extern FUNC(uint16, FLS_PRIVATE_CODE)Fls_DF_read_memory_u16(uint32 address);
extern FUNC(void, FLS_PRIVATE_CODE)Fls_DF_write_memory_u16(uint32 address,
uint16 value);
extern FUNC(uint8, FLS_PRIVATE_CODE)Fls_DF_read_memory_u08(uint32 address);
extern FUNC(void, FLS_PRIVATE_CODE)Fls_DF_write_memory_u08(uint32 address,
uint8 value);
#endif
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_COMPARE_API == STD_ON)
extern FUNC(r_fcl_status_t, FLS_PRIVATE_CODE)Fls_CFProcessCompareCommand(void);
#endif
extern FUNC(void, FLS_PRIVATE_CODE)Fls_CFProcessEraseCommand(void);
extern FUNC(r_fcl_status_t, FLS_PRIVATE_CODE)Fls_CFProcessReadCommand(void);
extern FUNC(void, FLS_PRIVATE_CODE)Fls_CFProcessWriteCommand(void);
#if(FLS_FLMD_REGS == SUPPORTED)
extern FUNC(void, FLS_PRIVATE_CODE)Fls_SetFLMD0(uint8 value);
#endif
extern FUNC(uint8, FLS_PRIVATE_CODE)
                                 Fls_CF_read_memory_u08(const uint32 address);
extern FUNC(uint32, FLS_PRIVATE_CODE)
                                 Fls_CF_read_memory_u32(const uint32 address);
extern FUNC(void, FLS_PRIVATE_CODE)Fls_CF_write_memory_u08(const uint32 address,
const uint8 value);
#endif
#if(FLS_FHVE_REGS == SUPPORTED)
extern FUNC(void, FLS_PRIVATE_CODE)Fls_SetFHVE(uint8 value);
#endif

extern FUNC(void, FLS_PRIVATE_CODE)Fls_EndJobProcess(void);

#endif

