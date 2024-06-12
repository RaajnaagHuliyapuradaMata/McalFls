#include "Fls.hpp"
#include "Fls_Internal.hpp"
#include "Fls_Types.hpp"

#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#include "CfgMcalFls_Fcl.hpp"
#endif

#include "Fls_Ram.hpp"

#include "CfgApplFls.hpp"
#if(FLS_DEV_ERROR_DETECT == STD_ON)

#include "SwcServiceDet.hpp"
#endif

#include "SwcServiceDem.hpp"
#include "r_typedefs.hpp"
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#include "r_fcl_env.hpp"
#include "r_fcl_global.hpp"
#endif
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#include "r_fdl_global.hpp"
#endif

#if(FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)

#define FLS_INTERNAL_C_AR_RELEASE_MAJOR_VERSION \
                                        FLS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLS_INTERNAL_C_AR_RELEASE_MINOR_VERSION \
                                        FLS_AR_RELEASE_MINOR_VERSION_VALUE
#define FLS_INTERNAL_C_AR_RELEASE_REVISION_VERSION \
                                     FLS_AR_RELEASE_REVISION_VERSION_VALUE
#elif(FLS_AR_VERSION == FLS_AR_LOWER_VERSION)

#define FLS_INTERNAL_C_AR_MAJOR_VERSION     FLS_AR_MAJOR_VERSION_VALUE
#define FLS_INTERNAL_C_AR_MINOR_VERSION     FLS_AR_MINOR_VERSION_VALUE
#define FLS_INTERNAL_C_AR_PATCH_VERSION     FLS_AR_PATCH_VERSION_VALUE
#endif

#define FLS_INTERNAL_C_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION_VALUE
#define FLS_INTERNAL_C_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION_VALUE

#if(FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)

#if(FLS_INTERNAL_AR_RELEASE_MAJOR_VERSION != \
                                       FLS_INTERNAL_C_AR_RELEASE_MAJOR_VERSION)
#error "Fls_Internal.c : Mismatch in Release Major Version"
#endif
#if(FLS_INTERNAL_AR_RELEASE_MINOR_VERSION != \
                                       FLS_INTERNAL_C_AR_RELEASE_MINOR_VERSION)
#error "Fls_Internal.c : Mismatch in Release Minor Version"
#endif
#if(FLS_INTERNAL_AR_RELEASE_REVISION_VERSION != \
                                    FLS_INTERNAL_C_AR_RELEASE_REVISION_VERSION)
#error "Fls_Internal.c : Mismatch in Release Revision Version"
#endif
#elif(FLS_AR_VERSION == FLS_AR_LOWER_VERSION)

#if(FLS_INTERNAL_AR_MAJOR_VERSION != FLS_INTERNAL_C_AR_MAJOR_VERSION)
#error "Fls_Internal.c : Mismatch in Specification Major Version"
#endif

#if(FLS_INTERNAL_AR_MINOR_VERSION != FLS_INTERNAL_C_AR_MINOR_VERSION)
#error "Fls_Internal.c : Mismatch in Specification Minor Version"
#endif

#if(FLS_INTERNAL_AR_PATCH_VERSION != FLS_INTERNAL_C_AR_PATCH_VERSION)
#error "Fls_Internal.c : Mismatch in Specification Patch Version"
#endif
#endif
#if(FLS_INTERNAL_SW_MAJOR_VERSION != FLS_INTERNAL_C_SW_MAJOR_VERSION)
#error "Fls_Internal.c : Mismatch in Software Major Version"
#endif
#if(FLS_INTERNAL_SW_MINOR_VERSION != FLS_INTERNAL_C_SW_MINOR_VERSION)
#error "Fls_Internal.c : Mismatch in Software Minor Version"
#endif

#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(void, FLS_PRIVATE_CODE)Fls_CFProcessEraseCommand(void){
  P2VAR(r_fcl_request_t,  AUTOMATIC, FLS_APPL_DATA) LpFclReqCmd;

  uint32 LulStartBlock;
  uint32 LulTotalBlocks;
  if(FLS_CF_NORMALBLOCK_BASE_ADDRESS > Fls_GVar.Fls_EraseStartAddress){
    LulStartBlock = (Fls_GVar.Fls_EraseStartAddress / FLS_CF_SMALLBLOCK_SIZE);
    if(FLS_CF_NORMALBLOCK_BASE_ADDRESS > Fls_GVar.Fls_EraseEndAddress){
      LulTotalBlocks = (((Fls_GVar.Fls_EraseEndAddress -
                          Fls_GVar.Fls_EraseStartAddress) + FLS_ONE)
                                     / FLS_CF_SMALLBLOCK_SIZE);
    }
    else{
      LulTotalBlocks = ((((Fls_GVar.Fls_EraseEndAddress -
                       FLS_CF_NORMALBLOCK_BASE_ADDRESS) + FLS_ONE) /
                       FLS_CF_NORMALBLOCK_SIZE) +
                     ((FLS_CF_NORMALBLOCK_BASE_ADDRESS -
                    Fls_GVar.Fls_EraseStartAddress) / FLS_CF_SMALLBLOCK_SIZE));
    }
  }
  else{
    LulStartBlock = ((Fls_GVar.Fls_EraseStartAddress -
                      FLS_CF_NORMALBLOCK_BASE_ADDRESS) /
                      FLS_CF_NORMALBLOCK_SIZE) + FLS_CF_TOTAL_SMALLBLOCKS;

    LulTotalBlocks = (((Fls_GVar.Fls_EraseEndAddress -
                        Fls_GVar.Fls_EraseStartAddress) + FLS_ONE)
                        / FLS_CF_NORMALBLOCK_SIZE);
  }
  if(FLS_FALSE == Fls_GVar.Fls_GblFlashEnable){
#if(FLS_FLMD_REGS == SUPPORTED)

    Fls_SetFLMD0(FLS_FLMD0_PROTECTION_OFF);
#endif
#if(FLS_FHVE_REGS == SUPPORTED)

    Fls_SetFHVE(FLS_FLASH_PROTECTION_OFF);
#endif
    Fls_GVar.Fls_GblFlashEnable = FLS_TRUE;
  }
  else{
  }

  LpFclReqCmd = &Fls_GstVar.GstfclRequest;
  LpFclReqCmd->command_enu = R_FCL_CMD_ERASE;
  LpFclReqCmd->idx_u32 = LulStartBlock;
  LpFclReqCmd->cnt_u16 = (uint16)LulTotalBlocks;

  Fls_GpRFclExecute (LpFclReqCmd);
}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif

#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(void, FLS_PRIVATE_CODE)Fls_CFProcessWriteCommand(void){
  P2VAR(r_fcl_request_t,  AUTOMATIC, FLS_APPL_DATA) LpFclReqCmd;
  if(FLS_FALSE == Fls_GVar.Fls_GblFlashEnable){
#if(FLS_FLMD_REGS == SUPPORTED)

    Fls_SetFLMD0(FLS_FLMD0_PROTECTION_OFF);
#endif
#if(FLS_FHVE_REGS == SUPPORTED)

    Fls_SetFHVE(FLS_FLASH_PROTECTION_OFF);
#endif
    Fls_GVar.Fls_GblFlashEnable = FLS_TRUE;
  }
  else{
  }

  LpFclReqCmd = &Fls_GstVar.GstfclRequest;
  LpFclReqCmd->command_enu = R_FCL_CMD_WRITE;

  LpFclReqCmd->bufferAdd_u32 = (uint32)Fls_GVar.pBufferAddress;

  LpFclReqCmd->idx_u32 = Fls_GVar.Fls_GulSrcDestAddress;
  LpFclReqCmd->cnt_u16 = (uint16)(Fls_GVar.Fls_GulCurrentLength /
                                                       R_FLI_MIN_WRITESIZE);

  Fls_GpRFclExecute (LpFclReqCmd);

  Fls_GVar.Fls_GblCommandInitiated = FLS_TRUE;
}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif

#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(r_fcl_status_t, FLS_PRIVATE_CODE)Fls_CFProcessReadCommand(void){
  r_fcl_status_t LenFCLStatus;

  uint32 LulFCLLength ;
  uint8 LucReadData;

  uint32 LulReadStatus;

  uint32 LulReadStartAddress;
  uint32 LulReadEndAddress;

  uint32 LulMaxReadBytes;
  LulMaxReadBytes = Fls_GpConfigPtr->ulFlsCFMaxReadBytes;

  if(Fls_GVar.Fls_GulCurrentLength > LulMaxReadBytes){
    LulFCLLength = LulMaxReadBytes;

    Fls_GVar.Fls_GulCurrentLength = Fls_GVar.Fls_GulCurrentLength -
                                    LulMaxReadBytes;

    Fls_GVar.Fls_GblProcessContinue = FLS_TRUE;
  }
  else{
    LulFCLLength = Fls_GVar.Fls_GulCurrentLength;

    Fls_GVar.Fls_GblProcessContinue = FLS_FALSE;
  }
#if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))

  Fls_GulTimeout = Fls_GpConfigPtr->ulFlsCFReadTimeoutValue;
#endif

  LulReadStartAddress = Fls_GVar.Fls_GulReadAddress;
  LulReadEndAddress = (LulReadStartAddress + LulFCLLength) - FLS_ONE;
  do
  {
    LucReadData = Fls_CF_read_memory_u08(LulReadStartAddress);

    Fls_CF_write_memory_u08((uint32)Fls_GVar.pBufferAddress, LucReadData);

    LulReadStartAddress++;

    Fls_GVar.pBufferAddress++;

  } while(LulReadStartAddress <= LulReadEndAddress);
  LulReadStatus = Fls_CF_read_memory_u32(R_FPSYS_REGADD_FSTATR_U32);

  if(R_FPSYS_REGBIT_FSTATR_RESET != (LulReadStatus &
     (R_FPSYS_REGBIT_FSTATR_ERSERR + R_FPSYS_REGBIT_FSTATR_PRGERR +
      R_FPSYS_REGBIT_FSTATR_ILGERR))){
    Fls_CF_write_memory_u08(R_FPSYS_FLASH_ACCESS_AREA_BASE
   ,                                      R_FPSYS_FLASH_ACCESS_CMD_CLEARSTAT);
    LenFCLStatus = R_FCL_ERR_INTERNAL;
  }
  else{
    LenFCLStatus = R_FCL_OK;
  }

  Fls_GVar.Fls_GblCommandInitiated = FLS_TRUE;

  return(LenFCLStatus);
}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(r_fdl_status_t, FLS_PRIVATE_CODE)Fls_DFProcessReadCommand(void){
  P2VAR(r_fdl_request_t,  AUTOMATIC, FLS_APPL_DATA) LpFdlReqCmd;

  P2VAR(volatile uint32, AUTOMATIC, FLS_APPL_DATA) LpReadAddress;

  r_fdl_status_t LenFDLStatus;

  boolean LblSECError ;

  uint32 LulFDLLength ;

  uint32 LulWordCnt;

  uint32 LulMaxReadBytes;

  LblSECError = FLS_FALSE;

  LulWordCnt = (R_FDL_WRITE_SIZE / FLS_FOUR);
  LulMaxReadBytes = Fls_GpConfigPtr->ulFlsDFMaxReadBytes;

  if(Fls_GVar.Fls_GulCurrentLength > LulMaxReadBytes){
    LulFDLLength = (LulMaxReadBytes / FLS_FOUR);

    Fls_GVar.Fls_GulCurrentLength = Fls_GVar.Fls_GulCurrentLength -
                                                               LulMaxReadBytes;
    Fls_GVar.Fls_GulRequestedLength = Fls_GVar.Fls_GulRequestedLength -
                                    (LulMaxReadBytes - Fls_GVar.Fls_GucOffset);

    Fls_GVar.Fls_GblProcessContinue = FLS_TRUE;
  }
  else{
    LulFDLLength = (Fls_GVar.Fls_GulCurrentLength / FLS_FOUR);

    Fls_GVar.Fls_GblProcessContinue = FLS_FALSE;
  }
#if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))

  Fls_GulTimeout = Fls_GpConfigPtr->ulFlsDFBlankCheckReadTimeoutValue;

  Fls_GVar.Fls_GblTimeOutMonitor = FLS_TRUE;
#endif
  if(R_FDL_SUSPENDED == Fls_GstVar.GstfdlRequest.status_enu){
    LpFdlReqCmd = &Fls_GstVar.GstfdlNewRequest;
  }
  else{
    LpFdlReqCmd = &Fls_GstVar.GstfdlRequest;
  }
#if(FLS_FHVE_REGS == SUPPORTED)
  if(FLS_FALSE == Fls_GVar.Fls_GblFlashEnable){
    Fls_SetFHVE(FLS_FLASH_PROTECTION_OFF);
    Fls_GVar.Fls_GblFlashEnable = FLS_TRUE;
  }
  else{
  }
#endif

  do
  {
    LpFdlReqCmd->command_enu = R_FDL_CMD_BLANKCHECK;
    LpFdlReqCmd->idx_u32 = Fls_GVar.Fls_GulReadAddress - FLS_DF_BASE_ADDRESS;
    LpFdlReqCmd->cnt_u16 = (uint16)LulWordCnt;
    LpFdlReqCmd->accessType_enu = R_FDL_ACCESS_USER;

    R_FDL_Execute (LpFdlReqCmd);

    do
    {
      R_FDL_Handler();
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                           (FLS_TIMEOUT_MONITORING == STD_ON))
      Fls_GulTimeout--;
#endif
    }
#if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))
    while((LpFdlReqCmd->status_enu == R_FDL_BUSY) &&
                              (Fls_GulTimeout > FLS_ZERO));
#else
    while(LpFdlReqCmd->status_enu == R_FDL_BUSY);
#endif
    LenFDLStatus = LpFdlReqCmd->status_enu;
    if(R_FDL_OK == LenFDLStatus){
      *((uint32 *) Fls_GVar.pTempBufferAddress) = FLS_ERASED_VALUE;

    }
    else if(R_FDL_ERR_BLANKCHECK == LenFDLStatus){
      LpReadAddress = (volatile uint32 *)(&(LpFdlReqCmd->idx_u32));

      LenFDLStatus = R_FDL_FCUFct_ReadOperation (LpReadAddress
   ,                    (uint32)Fls_GVar.pTempBufferAddress, LulWordCnt);

      if(R_FDL_ERR_ECC_SED == LenFDLStatus)
      {
        Fls_GVar.Fls_GulSrcDestAddress = Fls_GVar.Fls_GulReadAddress;

        LblSECError = FLS_TRUE;
      }
      else
      {
      }
    }
    else{
    }

    Fls_GVar.pTempBufferAddress = Fls_GVar.pTempBufferAddress +
                                                    R_FDL_WRITE_SIZE;

    LulFDLLength--;
    Fls_GVar.Fls_GulReadAddress = Fls_GVar.Fls_GulReadAddress +
                                                    R_FDL_WRITE_SIZE;
  } while((LulFDLLength > FLS_ZERO) &&
          ((LenFDLStatus == R_FDL_OK) || (LenFDLStatus == R_FDL_ERR_ECC_SED)));

  if(R_FDL_ERR_ECC_DED == LenFDLStatus){
    Fls_GVar.Fls_GulSrcDestAddress = Fls_GVar.Fls_GulReadAddress -
                                                           R_FDL_WRITE_SIZE;
  }
  else if(FLS_TRUE == LblSECError){
    LenFDLStatus = R_FDL_ERR_ECC_SED;
  }
  else{
  }

  Fls_GVar.Fls_GblCommandInitiated = FLS_TRUE;

  return(LenFDLStatus);
}
#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_READIMMEDIATE_API == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(r_fdl_status_t, FLS_PRIVATE_CODE)Fls_DFProcessReadImmCommand(void){
  r_fdl_status_t LenFDLStatus;

  uint32 LulFDLLength ;

  uint32 LulMaxReadBytes;

  uint32 LulReadStartAddress;
  uint32 LulReadEndAddress;

  uint32 LulDFERStatus;

  uint8 LucDFERInt;
  uint8 LucReadData;
  uint16 LusReadData;
  uint32 LulReadData;
  uint8 LucLenOffset = FLS_ZERO;

  uint32 LulErrorStatus = FLS_ZERO;

  uint8 LucErrorType = FLS_ZERO;
  LulMaxReadBytes = Fls_GpConfigPtr->ulFlsDFMaxReadBytes;

  if(Fls_GVar.Fls_GulCurrentLength > LulMaxReadBytes){
    LulFDLLength = LulMaxReadBytes;

    Fls_GVar.Fls_GulCurrentLength = Fls_GVar.Fls_GulCurrentLength -
                                                             LulMaxReadBytes;
    if(FLS_MISALIGNED_READ == Fls_GVar.Fls_ReadType){
      Fls_GVar.Fls_GulRequestedLength = Fls_GVar.Fls_GulRequestedLength -
                                    (LulMaxReadBytes - Fls_GVar.Fls_GucOffset);
    }
    else{
    }

    Fls_GVar.Fls_GblProcessContinue = FLS_TRUE;
  }
  else{
    if(FLS_MISALIGNED_READ != Fls_GVar.Fls_ReadType){
      LucLenOffset = (uint8)Fls_GVar.Fls_GulCurrentLength &
                                             (FLS_PAGE_SIZE - FLS_ONE);

      LulFDLLength = Fls_GVar.Fls_GulCurrentLength - LucLenOffset;
    }
    else{
      LulFDLLength = Fls_GVar.Fls_GulCurrentLength;
    }

    Fls_GVar.Fls_GblProcessContinue = FLS_FALSE;
  }

  LulReadStartAddress = Fls_GVar.Fls_GulReadAddress;
  LulReadEndAddress = (LulReadStartAddress + LulFDLLength) - FLS_ONE;

  Fls_DF_write_memory_u08 (R_FCU_REGADD_DFERSTC_U08
   ,                                             R_FCU_REGBIT_DFERSTC_ERRCLR);

  LucDFERInt = Fls_DF_read_memory_u08 (R_FCU_REGADD_DFERINT_U08);
  Fls_DF_write_memory_u08(R_FCU_REGADD_DFERINT_U08, R_FCU_REGVAL_DFERINT_NOINT);
  if(FLS_MISALIGNED_READ == Fls_GVar.Fls_ReadType){
    do
    {
      LulReadData = Fls_DF_read_memory_u32(LulReadStartAddress);

      Fls_DF_write_memory_u32((uint32)Fls_GVar.pTempBufferAddress, LulReadData);

      LulDFERStatus = Fls_DF_read_memory_u32 (R_FCU_REGADD_DFERSTR_U32);
      if(R_FCU_REGVAL_DFERSTR_NOERR != LulDFERStatus)
      {
        if(R_FCU_REGBIT_DFERSTR_DEDF ==
                                   (R_FCU_REGBIT_DFERSTR_DEDF & LulDFERStatus))
        {
          LucErrorType = FLS_ONE;
          LenFDLStatus = R_FDL_ERR_ECC_DED;
        }
        else
        {
          LenFDLStatus = R_FDL_ERR_ECC_SED;
        }

        if((R_FDL_ERR_ECC_DED == LenFDLStatus) ||
           ((R_FDL_ERR_ECC_SED == LenFDLStatus) && (FLS_ZERO == LucErrorType)))

        {
          Fls_GVar.Fls_GulSrcDestAddress = LulReadStartAddress;

          LulErrorStatus = LulDFERStatus;
        }
        else
        {
        }

        Fls_DF_write_memory_u08(R_FCU_REGADD_DFERSTC_U08
   ,                                            R_FCU_REGBIT_DFERSTC_ERRCLR);
      }
      else
      {
      }

      LulReadStartAddress = LulReadStartAddress + R_FDL_WRITE_SIZE;

      Fls_GVar.pTempBufferAddress = Fls_GVar.pTempBufferAddress +
                                                          R_FDL_WRITE_SIZE;

    } while(LulReadStartAddress <= LulReadEndAddress);

    Fls_GVar.Fls_GulSrcDestAddress = LulReadStartAddress - R_FDL_WRITE_SIZE;
  }
  else{
    while(LulReadStartAddress <= LulReadEndAddress){
      LulReadData = Fls_DF_read_memory_u32(LulReadStartAddress);

      Fls_DF_write_memory_u32((uint32)Fls_GVar.pBufferAddress, LulReadData);

      Fls_GVar.pBufferAddress = Fls_GVar.pBufferAddress + R_FDL_WRITE_SIZE;

      LulDFERStatus = Fls_DF_read_memory_u32 (R_FCU_REGADD_DFERSTR_U32);
      if(R_FCU_REGVAL_DFERSTR_NOERR != LulDFERStatus)
      {
        if(R_FCU_REGBIT_DFERSTR_DEDF ==
                                   (R_FCU_REGBIT_DFERSTR_DEDF & LulDFERStatus))
        {
          LucErrorType = FLS_ONE;
          LenFDLStatus = R_FDL_ERR_ECC_DED;
        }
        else
        {
          LenFDLStatus = R_FDL_ERR_ECC_SED;
        }

        if((R_FDL_ERR_ECC_DED == LenFDLStatus) ||
           ((R_FDL_ERR_ECC_SED == LenFDLStatus) && (FLS_ZERO == LucErrorType)))

        {
          Fls_GVar.Fls_GulSrcDestAddress = LulReadStartAddress;
          LulErrorStatus = LulDFERStatus;
        }
        else
        {
        }

        Fls_DF_write_memory_u08(R_FCU_REGADD_DFERSTC_U08
   ,                                            R_FCU_REGBIT_DFERSTC_ERRCLR);
      }
      else
      {
      }
      LulReadStartAddress = LulReadStartAddress + R_FDL_WRITE_SIZE;
    }
    switch(LucLenOffset){
      case FLS_ONE:

        LucReadData = Fls_DF_read_memory_u08(LulReadStartAddress);

        Fls_DF_write_memory_u08((uint32)Fls_GVar.pBufferAddress, LucReadData);

      break;
      case FLS_TWO:

        LusReadData = Fls_DF_read_memory_u16(LulReadStartAddress);

        Fls_DF_write_memory_u16((uint32)Fls_GVar.pBufferAddress, LusReadData);

      break;
      case FLS_THREE:

        LusReadData = Fls_DF_read_memory_u16(LulReadStartAddress);

        Fls_DF_write_memory_u16((uint32)Fls_GVar.pBufferAddress, LusReadData);

        Fls_GVar.pBufferAddress = Fls_GVar.pBufferAddress + FLS_TWO;

        LulReadStartAddress = LulReadStartAddress + FLS_TWO;

        LucReadData = Fls_DF_read_memory_u08(LulReadStartAddress);

        Fls_DF_write_memory_u08((uint32)Fls_GVar.pBufferAddress, LucReadData);

        LucLenOffset = FLS_ONE;
      break;
      default:
      break;
    }

    Fls_GVar.pBufferAddress = Fls_GVar.pBufferAddress + LucLenOffset;

    LulReadStartAddress = LulReadStartAddress + LucLenOffset;
  }

  Fls_GVar.Fls_GulReadAddress = LulReadStartAddress;
  if(R_FCU_REGVAL_DFERSTR_NOERR != LulErrorStatus){
    if(R_FCU_REGBIT_DFERSTR_DEDF ==
                              (R_FCU_REGBIT_DFERSTR_DEDF & LulErrorStatus)){
      LenFDLStatus = R_FDL_ERR_ECC_DED;
    }
    else{
      LenFDLStatus = R_FDL_ERR_ECC_SED;
    }
  }
  else{
    LenFDLStatus = R_FDL_OK;
  }

  Fls_DF_write_memory_u08 (R_FCU_REGADD_DFERINT_U08, LucDFERInt);

  Fls_GVar.Fls_GblCommandInitiated = FLS_TRUE;

  return(LenFDLStatus);
}
#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif
#endif

#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                         (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_COMPARE_API == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(r_fcl_status_t, FLS_PRIVATE_CODE)Fls_CFProcessCompareCommand(void){
  r_fcl_status_t LenFCLStatus;

  uint32 LulFCLLength ;
  uint8 LucReadData;

  uint32 LulReadStatus;

  uint32 LulReadStartAddress;
  uint32 LulReadEndAddress;

  uint32 LulMaxReadBytes;
  LulMaxReadBytes = Fls_GpConfigPtr->ulFlsCFMaxReadBytes;

  if(Fls_GVar.Fls_GulCurrentLength > LulMaxReadBytes){
    LulFCLLength = LulMaxReadBytes;

    Fls_GVar.Fls_GulCurrentLength = Fls_GVar.Fls_GulCurrentLength -
                                                             LulMaxReadBytes;

    Fls_GVar.Fls_GblProcessContinue = FLS_TRUE;
  }
  else{
    LulFCLLength = Fls_GVar.Fls_GulCurrentLength;

    Fls_GVar.Fls_GblProcessContinue = FLS_FALSE;
  }
#if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))

  Fls_GulTimeout = Fls_GpConfigPtr->ulFlsCFReadTimeoutValue;
#endif

  LulReadStartAddress = Fls_GVar.Fls_GulSrcDestAddress;
  LulReadEndAddress = (LulReadStartAddress + LulFCLLength) - FLS_ONE;
  do
  {
    LucReadData = Fls_CF_read_memory_u08(LulReadStartAddress);

    Fls_CF_write_memory_u08((uint32)Fls_GVar.pTempBufferAddress, LucReadData);

    LulReadStartAddress++;

    Fls_GVar.pTempBufferAddress++;

  } while(LulReadStartAddress <= LulReadEndAddress);

  Fls_GVar.Fls_GulSrcDestAddress = LulReadStartAddress;
  LulReadStatus = Fls_CF_read_memory_u32(R_FPSYS_REGADD_FSTATR_U32);

  if(R_FPSYS_REGBIT_FSTATR_RESET != (LulReadStatus &
     (R_FPSYS_REGBIT_FSTATR_ERSERR + R_FPSYS_REGBIT_FSTATR_PRGERR +
      R_FPSYS_REGBIT_FSTATR_ILGERR))){
    Fls_CF_write_memory_u08(R_FPSYS_FLASH_ACCESS_AREA_BASE
   ,                                      R_FPSYS_FLASH_ACCESS_CMD_CLEARSTAT);
    LenFCLStatus = R_FCL_ERR_INTERNAL;
  }
  else{
    LenFCLStatus = R_FCL_OK;
  }

  Fls_GVar.pTempBufferAddress = Fls_GVar.pTempBufferAddress - LulFCLLength;

  Fls_GVar.Fls_GblCommandInitiated = FLS_TRUE;

  return(LenFCLStatus);
}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif
#endif

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_COMPARE_API == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(r_fdl_status_t, FLS_PRIVATE_CODE)Fls_DFProcessCompareCommand(void){
  P2VAR(r_fdl_request_t,  AUTOMATIC, FLS_APPL_DATA) LpFdlReqCmd;

  uint32 LulFDLLength ;

  uint32 LulMaxReadBytes;
  LulMaxReadBytes = Fls_GpConfigPtr->ulFlsDFMaxReadBytes;

  if(Fls_GVar.Fls_GulCurrentLength > LulMaxReadBytes){
    LulFDLLength = (LulMaxReadBytes / FLS_FOUR);

    Fls_GVar.Fls_GulCurrentLength = Fls_GVar.Fls_GulCurrentLength -
                                                               LulMaxReadBytes;
    Fls_GVar.Fls_GulRequestedLength = Fls_GVar.Fls_GulRequestedLength -
                                    (LulMaxReadBytes - Fls_GVar.Fls_GucOffset);

    Fls_GVar.Fls_GblProcessContinue = FLS_TRUE;
  }
  else{
     LulFDLLength = (Fls_GVar.Fls_GulCurrentLength / FLS_FOUR);

     Fls_GVar.Fls_GblProcessContinue = FLS_FALSE;
  }
#if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))

  Fls_GulTimeout = Fls_GpConfigPtr->ulFlsDFReadTimeoutValue;

  Fls_GVar.Fls_GblTimeOutMonitor = FLS_TRUE;
#endif

  LpFdlReqCmd = &Fls_GstVar.GstfdlRequest;
  LpFdlReqCmd->command_enu = R_FDL_CMD_READ;

  LpFdlReqCmd->bufAddr_u32 = (uint32)Fls_GVar.pTempBufferAddress;

  LpFdlReqCmd->idx_u32 = (Fls_GVar.Fls_GulSrcDestAddress - FLS_DF_BASE_ADDRESS);
  LpFdlReqCmd->cnt_u16 = (uint16)LulFDLLength;
  LpFdlReqCmd->accessType_enu = R_FDL_ACCESS_USER;

  R_FDL_Execute (LpFdlReqCmd);

  do
  {
    R_FDL_Handler();
#if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))
    Fls_GulTimeout--;
#endif
  }
#if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))
  while((LpFdlReqCmd->status_enu == R_FDL_BUSY) &&
                              (Fls_GulTimeout > FLS_ZERO));
#else
  while(LpFdlReqCmd->status_enu == R_FDL_BUSY);
#endif

  Fls_GVar.Fls_GblCommandInitiated = FLS_TRUE;

  return(LpFdlReqCmd->status_enu);
}
#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif
#endif

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"
FUNC(void, FLS_PRIVATE_CODE)Fls_EndJobProcess(void){
  uint32 LulBytesProcessed;

  uint32 LddLoopCount;

  boolean LblJobNotification;
  boolean LblFlashStatus;

  uint32 LulMaxReadBytes;
#if(FLS_COMPARE_API == STD_ON)

  Std_ReturnType LddReturnValue;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)

  Std_ReturnType LenReturnValue;
  LenReturnValue = E_OK;
#if(FLS_TIMEOUT_MONITORING == STD_ON)

  Fls_GVar.Fls_GblTimeOutMonitor = FLS_FALSE;
#endif
#endif
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)
  LulMaxReadBytes = Fls_GpConfigPtr->ulFlsDFMaxReadBytes;
#elif(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)
  LulMaxReadBytes = Fls_GpConfigPtr->ulFlsCFMaxReadBytes;
#else
  if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
    LulMaxReadBytes = Fls_GpConfigPtr->ulFlsDFMaxReadBytes;
  }
  else{
    LulMaxReadBytes = Fls_GpConfigPtr->ulFlsCFMaxReadBytes;
  }
#endif
#if(FLS_COMPARE_API == STD_ON)
  LddReturnValue = E_OK;
#endif
  LddLoopCount = FLS_ZERO;

  LblJobNotification = FLS_FALSE;

  if(FLS_COMMAND_ERASE == Fls_GVar.Fls_GenCommand){
    if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
      if(R_FDL_OK == Fls_GstVar.GucDFStatus)
      {
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
             (FLS_BLANK_CHECK == FDL_SUPPORTED))

        Fls_GVar.Fls_GenCommand = FLS_COMMAND_BLANKCHECK;

        Fls_GVar.Fls_GblCommandInitiated = FLS_TRUE;

        Fls_GVar.Fls_GblProcessContinue = FLS_TRUE;

        Fls_GVar.Fls_GenState = MEMIF_BUSY;

        LblJobNotification = FLS_FALSE;
#else

        Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

        Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;

        Fls_GVar.Fls_GenState = MEMIF_IDLE;

        LblJobNotification = FLS_TRUE;
#endif
      }
      else
      {
#ifdef ETAS_OS
        Dem_ReportErrorStatus(FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif

        Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;

        Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

        if(R_FDL_ERR_INTERNAL == Fls_GstVar.GucDFStatus)
        {
          Fls_GVar.Fls_GenState = MEMIF_UNINIT;
        }
        else
        {
          Fls_GVar.Fls_GenState = MEMIF_IDLE;
        }

        LblJobNotification = FLS_TRUE;
      }
#endif
    }
    else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
      if(R_FCL_OK == Fls_GstVar.GucCFStatus)
      {
        Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

        Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;

        Fls_GVar.Fls_GenState = MEMIF_IDLE;

        LblJobNotification = FLS_TRUE;
      }
      else
      {
#ifdef ETAS_OS
        Dem_ReportErrorStatus(FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif

        Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;

        Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

        LblJobNotification = FLS_TRUE;
        if(R_FCL_ERR_INTERNAL == Fls_GstVar.GucCFStatus)
        {
          Fls_GVar.Fls_GenState = MEMIF_UNINIT;
        }
        else
        {
          Fls_GVar.Fls_GenState = MEMIF_IDLE;
        }
      }
#endif
    }
  }
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if((FLS_BLANKCHECK_API == STD_ON) || ((FLS_DEV_ERROR_DETECT == STD_ON) \
                                 && (FLS_BLANK_CHECK == FDL_SUPPORTED)))

  else if(FLS_COMMAND_BLANKCHECK == Fls_GVar.Fls_GenCommand){
    if(R_FDL_OK == Fls_GstVar.GucDFStatus){
      Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;

      Fls_GVar.Fls_GenState = MEMIF_IDLE;

      LblJobNotification = FLS_TRUE;
    }
    else{
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                  (FLS_BLANK_CHECK == FDL_SUPPORTED))
      if(FLS_TRUE == Fls_GVar.Fls_GblCommandInitiated)
      {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                         FLS_MAINFUNCTION_SID, FLS_E_VERIFY_ERASE_FAILED);
      }
      else
      {
      }
#endif
      switch(Fls_GstVar.GucDFStatus)
      {
        case R_FDL_ERR_INTERNAL:

             Fls_GVar.Fls_GenState = MEMIF_UNINIT;

             Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;
        break;

        case R_FDL_ERR_BLANKCHECK:

             Fls_GVar.Fls_GenState = MEMIF_IDLE;
             if(FLS_TRUE == Fls_GVar.Fls_GblCommandInitiated)
             {
               Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;
             }
             else
             {
               Fls_GVar.Fls_GenJobResult = MEMIF_BLOCK_INCONSISTENT;
             }
        break;
        default:

             Fls_GVar.Fls_GenState = MEMIF_IDLE;

             Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;
        break;
      }

      Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

      LblJobNotification = FLS_TRUE;
    }

    Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
  }
#endif

#if(FLS_READIMMEDIATE_API == STD_ON)

  else if(FLS_COMMAND_READ_IMM == Fls_GVar.Fls_GenCommand){
    if((R_FDL_OK == Fls_GstVar.GucDFStatus) ||
             (R_FDL_ERR_ECC_SED == Fls_GstVar.GucDFStatus)){
      if(FLS_MISALIGNED_READ == Fls_GVar.Fls_ReadType)
      {
        if(FLS_TRUE == Fls_GVar.Fls_GblProcessContinue)
        {
          LulBytesProcessed = LulMaxReadBytes;

          Fls_GVar.pTempBufferAddress = (Fls_GVar.pTempBufferAddress +
                                   Fls_GVar.Fls_GucOffset) - LulBytesProcessed;

        }
        else
        {
          LulBytesProcessed = Fls_GVar.Fls_GulCurrentLength;

          Fls_GVar.pTempBufferAddress = (Fls_GVar.pTempBufferAddress +
                                   Fls_GVar.Fls_GucOffset) - LulBytesProcessed;

          LulBytesProcessed = Fls_GVar.Fls_GulRequestedLength;

          Fls_GVar.Fls_GucOffset = FLS_ZERO;
        }

        while(LddLoopCount < (LulBytesProcessed - Fls_GVar.Fls_GucOffset))
        {
          *((uint8 *) Fls_GVar.pBufferAddress) =
                                   *((uint8 *)Fls_GVar.pTempBufferAddress);

          LddLoopCount++;

          Fls_GVar.pBufferAddress++;

          Fls_GVar.pTempBufferAddress++;

        }

        Fls_GVar.pTempBufferAddress = Fls_GVar.pTempBufferAddress -
                                                           LulBytesProcessed;

        Fls_GVar.Fls_GucOffset = FLS_ZERO;
      }
      else
      {
      }

      if(R_FDL_ERR_ECC_SED == Fls_GstVar.GucDFStatus)
      {
        if(NULL_PTR != Fls_GpConfigPtr->pEccSEDNotificationPointer)
        {
          Fls_GpConfigPtr->pEccSEDNotificationPointer
                                             (Fls_GVar.Fls_GulSrcDestAddress);
        }
        else
        {
        }
      }
      else
      {
      }

      if(FLS_TRUE != Fls_GVar.Fls_GblProcessContinue)
      {
        Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;

        Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

        Fls_GVar.Fls_GenState = MEMIF_IDLE;

        LblJobNotification = FLS_TRUE;
      }
      else
      {
      }
    }
    else{
      if(R_FDL_ERR_ECC_DED == Fls_GstVar.GucDFStatus)
      {
#ifdef ETAS_OS
        Dem_ReportErrorStatus(FLS_E_READ_FAILED_DED, DEM_EVENT_STATUS_FAILED);
#endif

        if(NULL_PTR != Fls_GpConfigPtr->pEccDEDNotificationPointer)
        {
          Fls_GpConfigPtr->pEccDEDNotificationPointer
                                               (Fls_GVar.Fls_GulSrcDestAddress);
        }
        else
        {
        }
      }
      else
      {
#ifdef ETAS_OS
        Dem_ReportErrorStatus(FLS_E_READ_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
      }

      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;

      Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

      Fls_GVar.Fls_GenState = MEMIF_IDLE;

      LblJobNotification = FLS_TRUE;
    }
  }
#endif
#endif

  else if(FLS_COMMAND_READ == Fls_GVar.Fls_GenCommand){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)

    if((R_FDL_OK == Fls_GstVar.GucDFStatus) ||
                                (R_FDL_ERR_ECC_SED == Fls_GstVar.GucDFStatus))
#elif(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)

    if(R_FCL_OK == Fls_GstVar.GucCFStatus)
#else

    if(((R_FDL_OK == Fls_GstVar.GucDFStatus) ||
           (R_FDL_ERR_ECC_SED == Fls_GstVar.GucDFStatus)) ||
                                   (R_FCL_OK == Fls_GstVar.GucCFStatus))
#endif
    {
      LblFlashStatus = FLS_TRUE;
    }
    else{
      LblFlashStatus = FLS_FALSE;
    }
    if(FLS_TRUE == LblFlashStatus){
      if(FLS_TRUE == Fls_GVar.Fls_GblProcessContinue)
      {
        LulBytesProcessed = LulMaxReadBytes;
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType)
        {
          LulBytesProcessed = (LulBytesProcessed - Fls_GVar.Fls_GucOffset);

          Fls_GVar.pTempBufferAddress = (Fls_GVar.pTempBufferAddress -
                                                            LulBytesProcessed);

        }
        else
        {
        }
#endif
      }
      else
      {
        LulBytesProcessed = Fls_GVar.Fls_GulCurrentLength;
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType)
        {
          Fls_GVar.pTempBufferAddress = (Fls_GVar.pTempBufferAddress +
                                   Fls_GVar.Fls_GucOffset) - LulBytesProcessed;

          LulBytesProcessed = Fls_GVar.Fls_GulRequestedLength;
        }
        else
        {
        }
#endif
      }
      if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType)
      {
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

        while(LddLoopCount < LulBytesProcessed)
        {
          *((uint8 *) Fls_GVar.pBufferAddress) =
                                   *((uint8 *)Fls_GVar.pTempBufferAddress);

          LddLoopCount++;

          Fls_GVar.pBufferAddress++;

          Fls_GVar.pTempBufferAddress++;

        }

        Fls_GVar.pTempBufferAddress = Fls_GVar.pTempBufferAddress -
                                   (Fls_GVar.Fls_GucOffset + LulBytesProcessed);

        Fls_GVar.Fls_GucOffset = FLS_ZERO;

        if(R_FDL_ERR_ECC_SED == Fls_GstVar.GucDFStatus)
        {
          if(NULL_PTR != Fls_GpConfigPtr->pEccSEDNotificationPointer)
          {
            Fls_GpConfigPtr->pEccSEDNotificationPointer
                                               (Fls_GVar.Fls_GulSrcDestAddress);
          }
          else
          {
          }
        }
        else
        {
        }
#endif
      }
      else
      {
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

        Fls_GVar.Fls_GulReadAddress = Fls_GVar.Fls_GulReadAddress +
                                                       LulBytesProcessed;
#endif
      }

      if(FLS_TRUE != Fls_GVar.Fls_GblProcessContinue)
      {
        Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;

        Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

        Fls_GVar.Fls_GenState = MEMIF_IDLE;

        LblJobNotification = FLS_TRUE;
      }
      else
      {
      }
    }
    else{
      if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType)
      {
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        if(R_FDL_ERR_ECC_DED == Fls_GstVar.GucDFStatus)
        {
#ifdef ETAS_OS
          Dem_ReportErrorStatus(FLS_E_READ_FAILED_DED, DEM_EVENT_STATUS_FAILED);
#endif

          if(NULL_PTR != Fls_GpConfigPtr->pEccDEDNotificationPointer)
          {
            Fls_GpConfigPtr->pEccDEDNotificationPointer
                                               (Fls_GVar.Fls_GulSrcDestAddress);
          }
          else
          {
          }
        }
        else
        {
#ifdef ETAS_OS
          Dem_ReportErrorStatus(FLS_E_READ_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
        }
#endif
      }
      else
      {
#ifdef ETAS_OS
        Dem_ReportErrorStatus(FLS_E_READ_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
      }

      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;

      Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;
      if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType)
      {
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

        if(R_FDL_ERR_INTERNAL == Fls_GstVar.GucDFStatus)
        {
          Fls_GVar.Fls_GenState = MEMIF_UNINIT;
        }
        else
        {
          Fls_GVar.Fls_GenState = MEMIF_IDLE;
        }
#endif
      }
      else
      {
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
          if((FLS_CF_ACCESS == Fls_GVar.Fls_AccessType) && (R_FCL_ERR_INTERNAL == Fls_GstVar.GucCFStatus))
          {
            Fls_GVar.Fls_GenState = MEMIF_UNINIT;
          }
          else
          {
            Fls_GVar.Fls_GenState = MEMIF_IDLE;
          }
#else

          Fls_GVar.Fls_GenState = MEMIF_IDLE;
#endif
      }

      LblJobNotification = FLS_TRUE;
    }
  }

#if(FLS_COMPARE_API == STD_ON)
  else if(FLS_COMMAND_COMPARE == Fls_GVar.Fls_GenCommand){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)

    if((R_FDL_OK == Fls_GstVar.GucDFStatus) ||
           (R_FDL_ERR_ECC_SED == Fls_GstVar.GucDFStatus))
#elif(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)

    if(R_FCL_OK == Fls_GstVar.GucCFStatus)
#else

    if(((R_FDL_OK == Fls_GstVar.GucDFStatus) ||
           (R_FDL_ERR_ECC_SED == Fls_GstVar.GucDFStatus)) ||
                                       (R_FCL_OK == Fls_GstVar.GucCFStatus))
#endif
    {
      LblFlashStatus = FLS_TRUE;
    }
    else{
      LblFlashStatus = FLS_FALSE;
    }
    if(FLS_TRUE == LblFlashStatus){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

      if((FLS_DF_ACCESS == Fls_GVar.Fls_AccessType) &&
                         (R_FDL_ERR_ECC_SED == Fls_GstVar.GucDFStatus))
      {
        if(NULL_PTR != Fls_GpConfigPtr->pEccSEDNotificationPointer)
        {
          Fls_GpConfigPtr->pEccSEDNotificationPointer(FLS_ZERO);
        }
        else
        {
        }
      }
      else
      {
      }
#endif

      if(FLS_TRUE == Fls_GVar.Fls_GblProcessContinue)
      {
        LulBytesProcessed = LulMaxReadBytes;
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType)
        {
          LulBytesProcessed = (LulBytesProcessed - Fls_GVar.Fls_GucOffset);

          Fls_GVar.pTempBufferAddress = (Fls_GVar.pTempBufferAddress +
                                                       Fls_GVar.Fls_GucOffset);

        }
        else
        {
        }
#endif
      }
      else
      {
        LulBytesProcessed = Fls_GVar.Fls_GulCurrentLength;
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType)
        {
          Fls_GVar.pTempBufferAddress = (Fls_GVar.pTempBufferAddress +
                                                     Fls_GVar.Fls_GucOffset);

          LulBytesProcessed = Fls_GVar.Fls_GulRequestedLength;
        }
        else
        {
        }
#endif
      }

      while(LddLoopCount < LulBytesProcessed)
      {
        if(*(Fls_GVar.pBufferAddress) !=
                                    *(Fls_GVar.pTempBufferAddress))
        {
          LddLoopCount = LulBytesProcessed;
          LddReturnValue = E_NOT_OK;
        }
        else
        {
        }

        LddLoopCount++;

        Fls_GVar.pBufferAddress++;

        Fls_GVar.pTempBufferAddress++;

      }
      if(E_OK == LddReturnValue)
      {
        if(FLS_TRUE == Fls_GVar.Fls_GblProcessContinue)
        {
          if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType)
          {
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

            Fls_GVar.pTempBufferAddress = Fls_GVar.pTempBufferAddress -
                                   (Fls_GVar.Fls_GucOffset + LulBytesProcessed);

            Fls_GVar.Fls_GulSrcDestAddress = Fls_GVar.Fls_GulSrcDestAddress +
                                   (Fls_GVar.Fls_GucOffset + LulBytesProcessed);

            Fls_GVar.Fls_GucOffset = FLS_ZERO;
#endif
          }
          else
          {
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                        (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

            Fls_GVar.pTempBufferAddress = Fls_GVar.pTempBufferAddress -
                                                             LulBytesProcessed;

#endif
          }
        }
        else
        {
          Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;

          Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

          Fls_GVar.Fls_GenState = MEMIF_IDLE;

          LblJobNotification = FLS_TRUE;
        }
      }
      else
      {
        Fls_GVar.Fls_GenJobResult = MEMIF_BLOCK_INCONSISTENT;

        Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

        Fls_GVar.Fls_GenState = MEMIF_IDLE;

        LblJobNotification = FLS_TRUE;
      }
    }
    else{
      if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType)
      {
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        if(R_FDL_ERR_ECC_DED == Fls_GstVar.GucDFStatus)
        {
#ifdef ETAS_OS
          Dem_ReportErrorStatus(FLS_E_READ_FAILED_DED, DEM_EVENT_STATUS_FAILED);
#endif

          if(NULL_PTR != Fls_GpConfigPtr->pEccDEDNotificationPointer)
          {
            Fls_GpConfigPtr->pEccDEDNotificationPointer(FLS_ZERO);
          }
          else
          {
          }
        }
        else
        {
#ifdef ETAS_OS
          Dem_ReportErrorStatus(FLS_E_COMPARE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
        }
#endif
      }
      else
      {
#ifdef ETAS_OS
        Dem_ReportErrorStatus(FLS_E_COMPARE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
      }

      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;

      Fls_GVar.Fls_GenState = MEMIF_IDLE;

      Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

      LblJobNotification = FLS_TRUE;
    }
  }
#endif

  else if(FLS_COMMAND_WRITE == Fls_GVar.Fls_GenCommand){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)

    if(R_FDL_OK == Fls_GstVar.GucDFStatus)
#elif(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)

    if(R_FCL_OK == Fls_GstVar.GucCFStatus)
#else

    if((R_FDL_OK == Fls_GstVar.GucDFStatus) ||
                                       (R_FCL_OK == Fls_GstVar.GucCFStatus))
#endif
    {
      LblFlashStatus = FLS_TRUE;
    }
    else{
      LblFlashStatus = FLS_FALSE;
    }
    if(FLS_TRUE == LblFlashStatus){
#if(FLS_DEV_ERROR_DETECT == STD_ON)

      Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;

      Fls_GVar.Fls_GulCurrentLength = FLS_ZERO;
#else

      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;

      Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

      Fls_GVar.Fls_GenState = MEMIF_IDLE;

      LblJobNotification = FLS_TRUE;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      if(FLS_TRUE != Fls_GVar.Fls_GblCommandInitiated)
      {
        while(Fls_GVar.Fls_GulCurrentLength < Fls_GVar.Fls_GulRequestedLength)
        {
          if(*(Fls_GVar.pBufferAddress) !=
                                     *((uint8 *)Fls_GVar.Fls_GulSrcDestAddress))

          {
            Fls_GVar.Fls_GulCurrentLength = Fls_GVar.Fls_GulRequestedLength;

            (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                              FLS_MAINFUNCTION_SID, FLS_E_VERIFY_WRITE_FAILED);

            LenReturnValue = E_NOT_OK;
          }
          else
          {
            Fls_GVar.pBufferAddress++;

            Fls_GVar.Fls_GulSrcDestAddress++;

            Fls_GVar.Fls_GulCurrentLength++;
          }
        }

        if(E_OK == LenReturnValue)
        {
          Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;

          Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

          Fls_GVar.Fls_GenState = MEMIF_IDLE;

          LblJobNotification = FLS_TRUE;
        }
        else
        {
          Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;

          Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;

          Fls_GVar.Fls_GenState = MEMIF_IDLE;

          LblJobNotification = FLS_TRUE;
        }
      }
      else
      {
      }
#endif
    }
    else{
#ifdef ETAS_OS
      Dem_ReportErrorStatus(FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif

      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;

      Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;
      if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType)
      {
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

         if(R_FDL_ERR_INTERNAL == Fls_GstVar.GucDFStatus)
         {
           Fls_GVar.Fls_GenState = MEMIF_UNINIT;
         }
         else
         {
           Fls_GVar.Fls_GenState = MEMIF_IDLE;
         }
#endif
      }
      else if(FLS_CF_ACCESS == Fls_GVar.Fls_AccessType)
      {
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
         if(R_FCL_ERR_INTERNAL == Fls_GstVar.GucCFStatus)
         {
           Fls_GVar.Fls_GenState = MEMIF_UNINIT;
         }
         else
         {
           Fls_GVar.Fls_GenState = MEMIF_IDLE;
         }
#endif
      }
      else
      {
        Fls_GVar.Fls_GenState = MEMIF_IDLE;
      }

      LblJobNotification = FLS_TRUE;
    }
  }
  else{
  }

  if(FLS_TRUE == LblJobNotification){
    if(FLS_CF_ACCESS == Fls_GVar.Fls_AccessType){
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                           (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
      if(FLS_TRUE == Fls_GVar.Fls_GblFlashEnable)
      {
#if(FLS_FLMD_REGS == SUPPORTED)

        Fls_SetFLMD0(FLS_FLMD0_PROTECTION_ON);
#endif
#if(FLS_FHVE_REGS == SUPPORTED)

        Fls_SetFHVE(FLS_FLASH_PROTECTION_ON);
#endif
        Fls_GVar.Fls_GblFlashEnable = FLS_FALSE;
      }
      else
      {
      }
#endif
    }
    else{
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_FHVE_REGS == SUPPORTED)
      if(FLS_TRUE == Fls_GVar.Fls_GblFlashEnable)
      {
        Fls_SetFHVE(FLS_FLASH_PROTECTION_ON);
        Fls_GVar.Fls_GblFlashEnable = FLS_FALSE;
      }
      else
      {
      }
#endif
#endif
    }
#if(FLS_JOB_NOTIF_CONFIG == STD_ON)
    if(MEMIF_JOB_OK == Fls_GVar.Fls_GenJobResult){
      Fls_GpConfigPtr->pJobEndNotificationPointer();
    }
    else{
      Fls_GpConfigPtr->pJobErrorNotificationPointer();
    }
#endif
  }
  else{
  }
}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#if(FLS_FLMD_REGS == SUPPORTED)
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(void, FLS_PRIVATE_CODE)Fls_SetFLMD0(uint8 value){
  FLS_FLMDPCMD = FLS_FLMD0_PCMD_CONSTANT;

  FLS_FLMDCNT = value;

  FLS_FLMDCNT = ~value;

  FLS_FLMDCNT = value;

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif
#endif

#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(uint32, FLS_PRIVATE_CODE)Fls_CF_read_memory_u32(const uint32 address){
  return (*((volatile uint32 *)(address)));

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(uint8, FLS_PRIVATE_CODE)Fls_CF_read_memory_u08(const uint32 address){
  return (*((volatile uint8 *)(address)));

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(void, FLS_PRIVATE_CODE)Fls_CF_write_memory_u08(const uint32 address,
const uint8 value){
  (*((volatile uint8 *)(address))) = value;

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif
#if(FLS_FHVE_REGS == SUPPORTED)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(void, FLS_PRIVATE_CODE)Fls_SetFHVE(uint8 value){
#if(FLS_FLMD_REGS == SUPPORTED)
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                           (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

  uint32 Luldelay;

  for(Luldelay = FLS_ZERO; Luldelay < FLS_FLMD0_P_OFF_WAIT_CONSTANT;
                                                          Luldelay++){
    ASM_NOP();
  }
#endif
#endif

  FLS_FHVE3 = value;
  FLS_FHVE15 = value;

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(uint8, FLS_PRIVATE_CODE)Fls_DF_read_memory_u08(uint32 address){
  return (*((volatile uint8 *)(address)));

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(void, FLS_PRIVATE_CODE)Fls_DF_write_memory_u08(uint32 address,
uint8 value){
  (*((volatile uint8 *)(address))) = value;

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(uint16, FLS_PRIVATE_CODE)Fls_DF_read_memory_u16(uint32 address){
  return (*((volatile uint16 *)(address)));

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(void, FLS_PRIVATE_CODE)Fls_DF_write_memory_u16(uint32 address,
uint16 value){
  (*((volatile uint16 *)(address))) = value;

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(uint32, FLS_PRIVATE_CODE)Fls_DF_read_memory_u32(uint32 address){
  return (*((volatile uint32 *)(address)));

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"

#define FLS_START_SEC_PRIVATE_CODE
#include "MemMap.hpp"

FUNC(void, FLS_PRIVATE_CODE)Fls_DF_write_memory_u32(uint32 address,
uint32 value){
  (*((volatile uint32 *)(address))) = value;

}

#define FLS_STOP_SEC_PRIVATE_CODE
#include "MemMap.hpp"
#endif

