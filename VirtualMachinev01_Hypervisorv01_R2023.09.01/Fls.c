#include "Fls.hpp"
#include "rh850_Types.hpp"

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#include "r_fdl.hpp"
#include "r_fdl_global.hpp"
#endif

#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#include "r_fcl.hpp"
#include "fcl_cfg.hpp"
#include "r_fcl_env.hpp"
#endif

#include "Fls_Internal.hpp"
#include "Fls_Ram.hpp"

#if(FLS_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
#endif

#include "Dem.hpp"

#include "Fls_Cbk.hpp"
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Fls.hpp"
#endif

#if(FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)
#define FLS_C_AR_RELEASE_MAJOR_VERSION     FLS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLS_C_AR_RELEASE_MINOR_VERSION     FLS_AR_RELEASE_MINOR_VERSION_VALUE
#define FLS_C_AR_RELEASE_REVISION_VERSION  FLS_AR_RELEASE_REVISION_VERSION_VALUE
#elif(FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
#define FLS_C_AR_MAJOR_VERSION     FLS_AR_MAJOR_VERSION_VALUE
#define FLS_C_AR_MINOR_VERSION     FLS_AR_MINOR_VERSION_VALUE
#define FLS_C_AR_PATCH_VERSION     FLS_AR_PATCH_VERSION_VALUE
#endif

#define FLS_C_SW_MAJOR_VERSION      1
#define FLS_C_SW_MINOR_VERSION      3

#if(FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)

#if(FLS_AR_RELEASE_MAJOR_VERSION != FLS_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fls.c : Mismatch in Release Major Version"
#endif

#if(FLS_AR_RELEASE_MINOR_VERSION != FLS_C_AR_RELEASE_MINOR_VERSION)
  #error "Fls.c : Mismatch in Release Minor Version"
#endif

#if(FLS_AR_RELEASE_REVISION_VERSION != FLS_C_AR_RELEASE_REVISION_VERSION)
  #error "Fls.c : Mismatch in Release Revision Version"
#endif

#elif(FLS_AR_VERSION == FLS_AR_LOWER_VERSION)

#if(FLS_AR_MAJOR_VERSION != FLS_C_AR_MAJOR_VERSION)
  #error "Fls.c : Mismatch in Specification Major Version"
#endif

#if(FLS_AR_MINOR_VERSION != FLS_C_AR_MINOR_VERSION)
  #error "Fls.c : Mismatch in Specification Minor Version"
#endif

#if(FLS_AR_PATCH_VERSION != FLS_C_AR_PATCH_VERSION)
  #error "Fls.c : Mismatch in Specification Patch Version"
#endif
#endif

#if(FLS_SW_MAJOR_VERSION != FLS_C_SW_MAJOR_VERSION)
  #error "Fls.c : Mismatch in Software Major Version"
#endif

#if(FLS_SW_MINOR_VERSION != FLS_C_SW_MINOR_VERSION)
  #error "Fls.c : Mismatch in Software Minor Version"
#endif

#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"

FUNC(void, FLS_PUBLIC_CODE) Fls_Init
(
   P2CONST(Fls_ConfigType, AUTOMATIC, FLS_APPL_CONST) ConfigPtr){
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  P2VAR(r_fcl_request_t,  AUTOMATIC, FLS_APPL_DATA) LpFclReqCmd;
  r_fcl_status_t LenFCLStatus;
#if(FLS_FLMD_REGS == SUPPORTED)
  uint32 Luldelay;
#endif
  boolean LblCFAccessFlag;
#endif

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  P2VAR(r_fdl_request_t,  AUTOMATIC, FLS_APPL_DATA) LpFdlReqCmd;
  r_fdl_status_t LenFDLStatus;
  boolean LblDFAccessFlag;
#endif

#if(FLS_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LenReturnValue;
#endif

#if(FLS_DEV_ERROR_DETECT == STD_ON)
  LenReturnValue = E_OK;
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  Fls_GstVar.GstfdlRequest.status_enu = R_FDL_ERR_REJECTED;
  Fls_GstVar.GucDFStatus = R_FDL_ERR_REJECTED;

  Fls_GstVar.GstfdlNewRequest.status_enu = R_FDL_ERR_REJECTED;
#endif

#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  Fls_GstVar.GstfclRequest.status_enu = R_FCL_ERR_FLOW;
  Fls_GstVar.GucCFStatus = R_FCL_ERR_FLOW;
#endif

  Fls_GulTimeout = FLS_ISR_TIMEOUT_VALUE;
  if(NULL_PTR == ConfigPtr){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                           FLS_INIT_SID, FLS_E_PARAM_CONFIG);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
  if(E_OK == LenReturnValue)
#endif
  {
      if(FLS_DBTOC_VALUE == (ConfigPtr->ulStartOfDbToc)){
      Fls_GpConfigPtr = ConfigPtr;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      if(MEMIF_BUSY == Fls_GVar.Fls_GenState){
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                                    FLS_INIT_SID, FLS_E_BUSY);
      }
      else
#endif
      {
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        LblCFAccessFlag = FLS_FALSE;
        R_FCL_DEVICE_SPECIFIC_INIT
        LenFCLStatus = R_FCL_Init(&sampleApp_fclConfig_enu);
        if(R_FCL_OK == LenFCLStatus){
          LenFCLStatus = R_FCL_CopySections();
        }
        else{
#if(FLS_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                           FLS_INIT_SID, FLS_E_UNINIT);
#endif
        }
        if(R_FCL_OK == LenFCLStatus){
#if(R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER)
          Fls_GpRFclExecute = (void(*)(r_fcl_request_t *))
                            R_FCL_CalcFctAddr((uint32_t)(void *)R_FCL_Execute);
          Fls_GpRFclHandler = (void(*)(void))
                            R_FCL_CalcFctAddr((uint32_t)(void *)R_FCL_Handler);
#endif
#if(FLS_FLMD_REGS == SUPPORTED)
          Fls_SetFLMD0(FLS_FLMD0_PROTECTION_OFF);
          for(Luldelay = FLS_ZERO; Luldelay < FLS_FLMD0_P_OFF_WAIT_CONSTANT;
                                                                  Luldelay++){
            ASM_NOP();
          }
#endif
          LpFclReqCmd = &Fls_GstVar.GstfclRequest;
          LpFclReqCmd->command_enu = R_FCL_CMD_PREPARE_ENV;
          Fls_GpRFclExecute (LpFclReqCmd);
#if(R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER)
          while(R_FCL_BUSY == LpFclReqCmd->status_enu){
            Fls_GpRFclHandler();
          }
#endif
          LenFCLStatus = LpFclReqCmd->status_enu;
#if(FLS_FLMD_REGS == SUPPORTED)
          Fls_SetFLMD0(FLS_FLMD0_PROTECTION_ON);
          for(Luldelay = FLS_ZERO; Luldelay < FLS_FLMD0_P_ON_WAIT_CONSTANT;
                                                                 Luldelay++){
            ASM_NOP();
          }
#endif
        }
        else{
        }
        if(R_FCL_OK == LenFCLStatus){
#if(FLS_FLMD_REGS == SUPPORTED)
          Fls_GVar.Fls_GblFlashEnable = FLS_FALSE;
#endif
          LblCFAccessFlag = FLS_TRUE;
        }
        else{
        }
#endif
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        LblDFAccessFlag = FLS_FALSE;
        R_FDL_DEVICE_SPECIFIC_INIT
        LenFDLStatus = R_FDL_Init(&sampleApp_fdlConfig_enu);
            if(R_FDL_OK == LenFDLStatus){
          LpFdlReqCmd = &Fls_GstVar.GstfdlRequest;
          LpFdlReqCmd->command_enu = R_FDL_CMD_PREPARE_ENV;
          LpFdlReqCmd->idx_u32 = FLS_ZERO;
          LpFdlReqCmd->cnt_u16 = FLS_ZERO;
          LpFdlReqCmd->accessType_enu = R_FDL_ACCESS_NONE;
          R_FDL_Execute(LpFdlReqCmd);
               while(R_FDL_BUSY == LpFdlReqCmd->status_enu){
            R_FDL_Handler();
          }
               if(R_FDL_OK == LpFdlReqCmd->status_enu){
            Fls_GVar.Fls_GucOffset = FLS_ZERO;
            Fls_GVar.Fls_ReadType = FLS_MISALIGNED_READ;
            LblDFAccessFlag = FLS_TRUE;
            Fls_GVar.Fls_MutexFlag = FLS_ZERO;
            Fls_GVar.Fls_GenBackUpCmd = FLS_COMMAND_NONE;
          }
          else{
#if(FLS_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                           FLS_INIT_SID, FLS_E_UNINIT);
#endif
          }
        }
        else{
#if(FLS_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                           FLS_INIT_SID, FLS_E_UNINIT);
#endif
        }
#endif
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)
        if(FLS_TRUE == LblDFAccessFlag)
        #elif(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)
        if(FLS_TRUE == LblCFAccessFlag)
#else
        if((FLS_TRUE == LblCFAccessFlag) && (FLS_TRUE == LblDFAccessFlag))
#endif
        {
          Fls_GVar.Fls_GenState = MEMIF_IDLE;
          Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;
          Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;
          Fls_GVar.Fls_GulRequestedLength = FLS_ZERO;
          Fls_GVar.Fls_GulCurrentLength = FLS_ZERO;
          Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
          Fls_GVar.Fls_GblProcessContinue = FLS_FALSE;
          Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
#if(FLS_FHVE_REGS == SUPPORTED)
          Fls_GVar.Fls_GblFlashEnable = FLS_FALSE;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
#if(FLS_TIMEOUT_MONITORING == STD_ON)
          Fls_GVar.Fls_GblTimeOutMonitor = FLS_FALSE;
#endif
          Fls_GblInitStatus = FLS_INITIALIZED;
#endif
        }
        else{
        }
      }
   }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   else{
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                  FLS_INIT_SID, FLS_E_INVALID_DATABASE);
   }
#endif
  }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  else{
  }
#endif
}

FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Erase
(
   Fls_AddressType TargetAddress,
   Fls_LengthType Length){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                        (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  P2VAR(r_fdl_request_t,  AUTOMATIC, FLS_APPL_DATA) LpFdlReqCmd;
  uint32 LulStartBlock;
  uint32 LulTotalBlocks;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  uint32 LulFlsBaseAddress;
  uint32 LulFlsTotalSize;
#endif
  uint32 LulFlsBlockSize;
  Std_ReturnType LenReturnValue;
  LenReturnValue = E_OK;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                               FLS_ERASE_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
#endif

#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif

   if(MEMIF_IDLE != Fls_GVar.Fls_GenState){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   if(MEMIF_BUSY == Fls_GVar.Fls_GenState){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_ERASE_SID, FLS_E_BUSY);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
#endif
  }
#if(FLS_DEV_ERROR_DETECT == STD_OFF)
   else if(FLS_ZERO == Length){
    LenReturnValue = E_NOT_OK;
  }
#endif
  else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)
    TargetAddress = TargetAddress - FLS_CF_OFFSET_VALUE;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LulFlsBaseAddress = FLS_CF_SMALLBLOCK_BASE_ADDRESS;
    LulFlsTotalSize = FLS_CF_TOTAL_SIZE;
#endif
   if(TargetAddress < FLS_CF_NORMALBLOCK_BASE_ADDRESS){
      LulFlsBlockSize = FLS_CF_SMALLBLOCK_SIZE;
   }
   else{
      LulFlsBlockSize = FLS_CF_NORMALBLOCK_SIZE;
   }
    Fls_GVar.Fls_AccessType = FLS_CF_ACCESS;
    #elif(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LulFlsBaseAddress = FLS_DF_SECTOR_START_ADDRESS;
    LulFlsTotalSize = FLS_DF_TOTAL_SIZE;
#endif
    LulFlsBlockSize = FLS_DF_BLOCK_SIZE;
    TargetAddress = TargetAddress + FLS_DF_BASE_ADDRESS;
    Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
#else
   if(FLS_CF_OFFSET_VALUE > TargetAddress){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      LulFlsBaseAddress = FLS_DF_SECTOR_START_ADDRESS;
      LulFlsTotalSize = FLS_DF_TOTAL_SIZE;
#endif
      LulFlsBlockSize = FLS_DF_BLOCK_SIZE;
      TargetAddress = TargetAddress + FLS_DF_BASE_ADDRESS;
      Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
   }
   else{
      TargetAddress = TargetAddress - FLS_CF_OFFSET_VALUE;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      LulFlsBaseAddress = FLS_CF_SMALLBLOCK_BASE_ADDRESS;
      LulFlsTotalSize = FLS_CF_TOTAL_SIZE;
#endif
      if(FLS_CF_NORMALBLOCK_BASE_ADDRESS > TargetAddress){
        LulFlsBlockSize = FLS_CF_SMALLBLOCK_SIZE;
      }
      else{
        LulFlsBlockSize = FLS_CF_NORMALBLOCK_SIZE;
      }
      Fls_GVar.Fls_AccessType = FLS_CF_ACCESS;
   }
#endif
    Fls_GVar.Fls_EraseStartAddress = TargetAddress;
    Fls_GVar.Fls_EraseEndAddress = (TargetAddress + Length) - FLS_ONE;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LenReturnValue = E_OK;
   if((FLS_ZERO !=
       (Fls_GVar.Fls_EraseStartAddress & (LulFlsBlockSize - FLS_ONE))) ||
       (Fls_GVar.Fls_EraseStartAddress < LulFlsBaseAddress) ||
           ((Fls_GVar.Fls_EraseStartAddress - LulFlsBaseAddress) >
           (LulFlsTotalSize - FLS_ONE))){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                       FLS_ERASE_SID, FLS_E_PARAM_ADDRESS);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
   if(FLS_CF_ACCESS == Fls_GVar.Fls_AccessType){
      if(FLS_CF_NORMALBLOCK_BASE_ADDRESS > Fls_GVar.Fls_EraseEndAddress){
        LulFlsBlockSize = FLS_CF_SMALLBLOCK_SIZE;
      }
      else{
        LulFlsBlockSize = FLS_CF_NORMALBLOCK_SIZE;
      }
   }
   else{
   }
#endif

   if((FLS_ZERO == Length) || ((Fls_GVar.Fls_EraseEndAddress &
          (LulFlsBlockSize - FLS_ONE)) != (LulFlsBlockSize - FLS_ONE)) ||
          ((Fls_GVar.Fls_EraseEndAddress - LulFlsBaseAddress)
          > LulFlsTotalSize)){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                          FLS_ERASE_SID, FLS_E_PARAM_LENGTH);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if(E_OK == LenReturnValue)
#endif
   {
#if(FLS_DEV_ERROR_DETECT == STD_OFF)
         if(FLS_ZERO != (Length & (LulFlsBlockSize - FLS_ONE ))){
        Length = (Length + (LulFlsBlockSize - FLS_ONE)) &
                                (~(LulFlsBlockSize - FLS_ONE));
        Fls_GVar.Fls_EraseEndAddress = (TargetAddress + Length) - FLS_ONE;
      }
      else{
      }
#endif
         if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        LulStartBlock = ((TargetAddress - FLS_DF_BASE_ADDRESS)
                                                   / FLS_DF_BLOCK_SIZE);
        LulTotalBlocks = (Length / FLS_DF_BLOCK_SIZE);
#if(FLS_INTERRUPT_MODE == STD_ON)
        RH850_SV_MODE_IMR_AND(16, (Fls_GpConfigPtr->pFlEndImrAddress)
   ,                                  (Fls_GpConfigPtr->usFlEndImrMask));
#endif

        LpFdlReqCmd = &Fls_GstVar.GstfdlRequest;
        LpFdlReqCmd->command_enu = R_FDL_CMD_ERASE;
        LpFdlReqCmd->idx_u32 = LulStartBlock;
        LpFdlReqCmd->cnt_u16 = (uint16)LulTotalBlocks;
        LpFdlReqCmd->accessType_enu = R_FDL_ACCESS_USER;
#if(FLS_FHVE_REGS == SUPPORTED)
            if(FLS_FALSE == Fls_GVar.Fls_GblFlashEnable){
          Fls_SetFHVE(FLS_FLASH_PROTECTION_OFF);
          Fls_GVar.Fls_GblFlashEnable = FLS_TRUE;
        }
        else{
        }
#endif
        R_FDL_Execute (LpFdlReqCmd);
        Fls_GVar.Fls_GulCurrentLength = Length;
#endif
      }
      else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        Fls_CFProcessEraseCommand();
#endif
      }
      Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
      Fls_GVar.Fls_GblProcessContinue = FLS_FALSE;
      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_PENDING;
      Fls_GVar.Fls_GenState = MEMIF_BUSY;
      Fls_GVar.Fls_GenCommand = FLS_COMMAND_ERASE;
   }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   else{
   }
#endif
  }
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  return(LenReturnValue);
}

FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Write
(Fls_AddressType TargetAddress,
P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) SourceAddressPtr,
   Fls_LengthType Length){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  P2VAR(r_fdl_request_t,  AUTOMATIC, FLS_APPL_DATA) LpFdlReqCmd;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  uint32 LulFlsBaseAddress;
  uint32 LulFlsTotalSize;
#endif
  Std_ReturnType LenReturnValue;
  LenReturnValue = E_OK;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_WRITE_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
#endif

#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
   if(MEMIF_IDLE != Fls_GVar.Fls_GenState){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   if(MEMIF_BUSY == Fls_GVar.Fls_GenState){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_WRITE_SID, FLS_E_BUSY);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
#endif
  }
#if(FLS_DEV_ERROR_DETECT == STD_OFF)
   else if(FLS_ZERO == Length){
    LenReturnValue = E_NOT_OK;
  }
#endif
  else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LulFlsBaseAddress = FLS_CF_SMALLBLOCK_BASE_ADDRESS;
    LulFlsTotalSize = FLS_CF_TOTAL_SIZE;
#endif
    TargetAddress = TargetAddress - FLS_CF_OFFSET_VALUE;
    Fls_GVar.Fls_AccessType = FLS_CF_ACCESS;
    #elif(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LulFlsBaseAddress = FLS_DF_SECTOR_START_ADDRESS;
    LulFlsTotalSize = FLS_DF_TOTAL_SIZE;
#endif
    TargetAddress = TargetAddress + FLS_DF_BASE_ADDRESS;
    Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
#else
   if(FLS_CF_OFFSET_VALUE > TargetAddress){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      LulFlsBaseAddress = FLS_DF_SECTOR_START_ADDRESS;
      LulFlsTotalSize = FLS_DF_TOTAL_SIZE;
#endif
      TargetAddress = TargetAddress + FLS_DF_BASE_ADDRESS;
      Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
   }
   else{
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      LulFlsBaseAddress = FLS_CF_SMALLBLOCK_BASE_ADDRESS;
      LulFlsTotalSize = FLS_CF_TOTAL_SIZE;
#endif
      TargetAddress = TargetAddress - FLS_CF_OFFSET_VALUE;
      Fls_GVar.Fls_AccessType = FLS_CF_ACCESS;
   }
#endif

    Fls_GVar.Fls_GulSrcDestAddress = TargetAddress;
    Fls_GVar.Fls_GulRequestedLength = Length;
    Fls_GVar.Fls_GulCurrentLength = Length;
    Fls_GVar.pBufferAddress = SourceAddressPtr;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LenReturnValue = E_OK;
   if((FLS_ZERO != (TargetAddress & (FLS_PAGE_SIZE - FLS_ONE))) ||
         (TargetAddress < LulFlsBaseAddress) ||
         ((TargetAddress - LulFlsBaseAddress) > (LulFlsTotalSize - FLS_ONE))){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                        FLS_WRITE_SID, FLS_E_PARAM_ADDRESS);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
      if((Length == FLS_ZERO) || (((TargetAddress + Length)
           & (FLS_PAGE_SIZE - FLS_ONE)) != FLS_ZERO) ||
             (((TargetAddress - LulFlsBaseAddress) + Length) > LulFlsTotalSize)
             ){
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                        FLS_WRITE_SID, FLS_E_PARAM_LENGTH);
        LenReturnValue = E_NOT_OK;
      }
      else{
      }
   }
   else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
      if((FLS_ZERO == Length) || (((TargetAddress + Length)
           & (FLS_PAGE_SIZE - FLS_ONE)) != FLS_ZERO) ||
         (((TargetAddress - LulFlsBaseAddress) + Length) > LulFlsTotalSize) ||
         (((TargetAddress + Length) & (R_FLI_MIN_WRITESIZE - FLS_ONE))
           != FLS_ZERO)){
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                          FLS_WRITE_SID, FLS_E_PARAM_LENGTH);
        LenReturnValue = E_NOT_OK;
      }
      else{
      }
#endif
   }
   if(NULL_PTR == SourceAddressPtr){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_WRITE_SID, FLS_E_PARAM_DATA);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if(E_OK == LenReturnValue)
#endif
   {
         if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_INTERRUPT_MODE == STD_ON)
        RH850_SV_MODE_IMR_AND(16, (Fls_GpConfigPtr->pFlEndImrAddress)
   ,                                  (Fls_GpConfigPtr->usFlEndImrMask));
#endif
            if(R_FDL_SUSPENDED == Fls_GstVar.GstfdlRequest.status_enu){
          LpFdlReqCmd = &Fls_GstVar.GstfdlNewRequest;
        }
        else{
          LpFdlReqCmd = &Fls_GstVar.GstfdlRequest;
        }
        LpFdlReqCmd->command_enu = R_FDL_CMD_WRITE;
        LpFdlReqCmd->bufAddr_u32 = (uint32)SourceAddressPtr;
        LpFdlReqCmd->idx_u32 = (TargetAddress - FLS_DF_BASE_ADDRESS);
        LpFdlReqCmd->cnt_u16 = (uint16)(Length / FLS_FOUR);
        LpFdlReqCmd->accessType_enu = R_FDL_ACCESS_USER;
#if(FLS_FHVE_REGS == SUPPORTED)
            if(FLS_FALSE == Fls_GVar.Fls_GblFlashEnable){
          Fls_SetFHVE(FLS_FLASH_PROTECTION_OFF);
          Fls_GVar.Fls_GblFlashEnable = FLS_TRUE;
        }
        else{
        }
#endif
        R_FDL_Execute (LpFdlReqCmd);
#endif
      }
      else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
        Fls_CFProcessWriteCommand();
#endif
      }
      Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_PENDING;
      Fls_GVar.Fls_GenState = MEMIF_BUSY;
      Fls_GVar.Fls_GenCommand = FLS_COMMAND_WRITE;
   }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   else{
   }
#endif
  }
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  return(LenReturnValue);
}

#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"

#if(FLS_CANCEL_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"
FUNC(void, FLS_PUBLIC_CODE)Fls_Cancel(void){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  volatile r_fdl_status_t LenFDLStatus;
#endif

#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  volatile r_fcl_status_t LenFCLStatus;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LenReturnValue;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  LenReturnValue = E_OK;
   if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                                FLS_CANCEL_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
  if(E_OK == LenReturnValue)
#endif
  {
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif

#if(FLS_INTERRUPT_MODE == STD_ON)
#if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))
    Fls_GulTimeout = FLS_ISR_TIMEOUT_VALUE;
   while((Fls_GVar.Fls_MutexFlag == FLS_ONE) && (Fls_GulTimeout > FLS_ZERO))
#else

   while(Fls_GVar.Fls_MutexFlag == FLS_ONE)
#endif
   {
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                        (FLS_TIMEOUT_MONITORING == STD_ON))
      Fls_GulTimeout--;
#endif
   }
#endif

      if(MEMIF_JOB_PENDING == Fls_GVar.Fls_GenJobResult){
         if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_INTERRUPT_MODE == STD_ON)

        RH850_SV_MODE_IMR_OR(16, (Fls_GpConfigPtr->pFlEndImrAddress)
   ,                                  ~(Fls_GpConfigPtr->usFlEndImrMask));

#endif
            switch(Fls_GVar.Fls_GenCommand){
          case FLS_COMMAND_ERASE:
          case FLS_COMMAND_WRITE:
          case FLS_COMMAND_BLANKCHECK:
               LenFDLStatus = R_FDL_CancelRequest();
               if(R_FDL_OK == LenFDLStatus){
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                        (FLS_TIMEOUT_MONITORING == STD_ON))
                 Fls_GulTimeout = Fls_GpConfigPtr->ulFlsDFCancelTimeoutValue;
#endif
                  do{
                   R_FDL_Handler();
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                           (FLS_TIMEOUT_MONITORING == STD_ON))
                   Fls_GulTimeout--;
#endif
                 }
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                           (FLS_TIMEOUT_MONITORING == STD_ON))
                 while((R_FDL_CANCELLED != Fls_GstVar.GstfdlRequest.status_enu)
                                            && (Fls_GulTimeout > FLS_ZERO));
#else
                 while(R_FDL_CANCELLED != Fls_GstVar.GstfdlRequest.status_enu);
#endif
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                        (FLS_TIMEOUT_MONITORING == STD_ON))
                  if(FLS_ZERO == Fls_GulTimeout){
                   (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                          FLS_CANCEL_SID, FLS_E_TIMEOUT);
                 }
                  else{
                 }
#endif
                  if(Fls_GstVar.GstfdlRequest.status_enu == R_FDL_CANCELLED){
                   Fls_GVar.Fls_GenJobResult = MEMIF_JOB_CANCELED;
                   Fls_GVar.Fls_GenState = MEMIF_IDLE;
                   Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;
                   Fls_GstVar.GucDFStatus= R_FDL_CANCELLED;
                   Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
#if(FLS_JOB_NOTIF_CONFIG == STD_ON)
                   Fls_GpConfigPtr->pJobErrorNotificationPointer();
#endif
                 }
                  else{
                 }
               }
               else{
               }
          break;
          case FLS_COMMAND_READ:
          case FLS_COMMAND_COMPARE:
          case FLS_COMMAND_READ_IMM:
               Fls_GVar.Fls_GenJobResult = MEMIF_JOB_CANCELED;
               Fls_GVar.Fls_GenState = MEMIF_IDLE;
               Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;
               Fls_GstVar.GucDFStatus= R_FDL_CANCELLED;
               Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
#if(FLS_JOB_NOTIF_CONFIG == STD_ON)
               Fls_GpConfigPtr->pJobErrorNotificationPointer();
#endif
          break;
          default:
          break;
        }
#endif
      }
      else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
            switch(Fls_GVar.Fls_GenCommand){
          case FLS_COMMAND_ERASE:
          case FLS_COMMAND_WRITE:
          LenFCLStatus = R_FCL_CancelRequest();
               if(R_FCL_OK == LenFCLStatus){
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                  (FLS_TIMEOUT_MONITORING == STD_ON))

              Fls_GulTimeout = Fls_GpConfigPtr->ulFlsCFCancelTimeoutValue;
#endif
                  do{
                R_FCL_Handler();
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                         (FLS_TIMEOUT_MONITORING == STD_ON))
                Fls_GulTimeout--;
#endif
              }
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                      (FLS_TIMEOUT_MONITORING == STD_ON))
              while((R_FCL_CANCELLED != Fls_GstVar.GstfclRequest.status_enu)
                                        && (Fls_GulTimeout > FLS_ZERO));
#else
              while(R_FCL_CANCELLED != Fls_GstVar.GstfclRequest.status_enu);
#endif
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                        (FLS_TIMEOUT_MONITORING == STD_ON))
                  if(FLS_ZERO == Fls_GulTimeout){
                 (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                      FLS_CANCEL_SID, FLS_E_TIMEOUT);
               }
               else{
               }
#endif
                  if(Fls_GstVar.GstfclRequest.status_enu == R_FCL_CANCELLED){
                   Fls_GVar.Fls_GenJobResult = MEMIF_JOB_CANCELED;
                   Fls_GVar.Fls_GenState = MEMIF_IDLE;
                   Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;
                   Fls_GstVar.GucCFStatus= R_FCL_CANCELLED;
                   Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
#if(FLS_JOB_NOTIF_CONFIG == STD_ON)
                   Fls_GpConfigPtr->pJobErrorNotificationPointer();
#endif
                }
                else{
                }
          }
          else{
          }
          break;
          case FLS_COMMAND_READ:
          case FLS_COMMAND_COMPARE:
               Fls_GVar.Fls_GenJobResult = MEMIF_JOB_CANCELED;
               Fls_GVar.Fls_GenState = MEMIF_IDLE;
               Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;
               Fls_GstVar.GucCFStatus= R_FCL_CANCELLED;
               Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
#if(FLS_JOB_NOTIF_CONFIG == STD_ON)
               Fls_GpConfigPtr->pJobErrorNotificationPointer();
#endif
          break;
          default:
          break;
        }
#endif
      }
   }
   else{
   }

#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  else{
  }
#endif
}
#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"
#endif

#if(FLS_GET_STATUS_API == STD_ON)

#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"

FUNC(MemIf_StatusType, FLS_PUBLIC_CODE)Fls_GetStatus(void){
  MemIf_StatusType LenStatus;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LenReturnValue;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  LenStatus = MEMIF_UNINIT;
  LenReturnValue = E_OK;
   if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                           FLS_GET_STATUS_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
  if(LenReturnValue == E_OK)
#endif
  {
    LenStatus = Fls_GVar.Fls_GenState;
  }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  else{
  }
#endif
  return(LenStatus);
}

#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"
#endif

#if(FLS_GET_JOB_RESULT_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"
FUNC(MemIf_JobResultType, FLS_PUBLIC_CODE)Fls_GetJobResult(void){
  MemIf_JobResultType LenJobResult;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LenReturnValue;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  LenJobResult = MEMIF_JOB_FAILED;
  LenReturnValue = E_OK;
   if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                        FLS_GET_JOB_RESULT_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
  if(E_OK == LenReturnValue)
#endif
  {
    LenJobResult = Fls_GVar.Fls_GenJobResult;
  }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  else{
  }
#endif

  return(LenJobResult);
}
#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"
#endif

#define FLS_START_SEC_SCHEDULER_CODE
#include "MemMap.hpp"
FUNC(void, FLS_PUBLIC_CODE)Fls_MainFunction(void){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if((FLS_BLANKCHECK_API == STD_ON) || ((FLS_DEV_ERROR_DETECT == STD_ON) \
                                 && (FLS_BLANK_CHECK == FDL_SUPPORTED)))
  P2VAR(r_fdl_request_t,  AUTOMATIC, FLS_APPL_DATA) LpFdlReqCmd;
#endif
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LenReturnValue;
  LenReturnValue = E_OK;
#endif
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  Fls_GstVar.GucCFStatus = R_FCL_ERR_REJECTED;
#endif
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  Fls_GstVar.GucDFStatus = R_FDL_ERR_REJECTED;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                          FLS_MAINFUNCTION_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
  if(E_OK == LenReturnValue)
#endif
  {
      if(MEMIF_BUSY == Fls_GVar.Fls_GenState){
         if(FLS_COMMAND_ERASE == Fls_GVar.Fls_GenCommand){
            if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_INTERRUPT_MODE == STD_OFF)
          R_FDL_Handler();
          Fls_GstVar.GucDFStatus = Fls_GstVar.GstfdlRequest.status_enu;
#endif
#endif
        }
        else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
          Fls_GpRFclHandler();
          Fls_GstVar.GucCFStatus = Fls_GstVar.GstfclRequest.status_enu;
#endif
        }
      }
         else if(FLS_COMMAND_WRITE == Fls_GVar.Fls_GenCommand){
            if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_INTERRUPT_MODE == STD_OFF)
          R_FDL_Handler();
               if(R_FDL_SUSPENDED == Fls_GstVar.GstfdlRequest.status_enu){
            Fls_GstVar.GucDFStatus = Fls_GstVar.GstfdlNewRequest.status_enu;
          }
          else{
            Fls_GstVar.GucDFStatus = Fls_GstVar.GstfdlRequest.status_enu;
          }
#endif
#endif
        }
        else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)

          Fls_GpRFclHandler();
          Fls_GstVar.GucCFStatus = Fls_GstVar.GstfclRequest.status_enu;
#endif
        }
      }
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
         else if(FLS_COMMAND_BLANKCHECK == Fls_GVar.Fls_GenCommand){
#if((FLS_BLANKCHECK_API == STD_ON) || \
        ((FLS_DEV_ERROR_DETECT == STD_ON) \
        && (FLS_BLANK_CHECK == FDL_SUPPORTED)))
        if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
          if(FLS_TRUE == Fls_GVar.Fls_GblProcessContinue){
            LpFdlReqCmd = &Fls_GstVar.GstfdlRequest;
            LpFdlReqCmd->command_enu = R_FDL_CMD_BLANKCHECK;
            LpFdlReqCmd->idx_u32 = Fls_GVar.Fls_EraseStartAddress -
                                                     FLS_DF_BASE_ADDRESS;
            LpFdlReqCmd->cnt_u16 = (uint16)(Fls_GVar.Fls_GulCurrentLength
                                                                 / FLS_FOUR);
            LpFdlReqCmd->accessType_enu = R_FDL_ACCESS_USER;
            R_FDL_Execute (LpFdlReqCmd);
            Fls_GVar.Fls_GblProcessContinue = FLS_FALSE;
          }
          else{
          }
          R_FDL_Handler();
          Fls_GstVar.GucDFStatus = Fls_GstVar.GstfdlRequest.status_enu;
        }
        else{
        }
#endif
      }
#endif
         else if(FLS_COMMAND_READ == Fls_GVar.Fls_GenCommand){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)
        Fls_GstVar.GucDFStatus = Fls_DFProcessReadCommand();
        #elif(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)
        Fls_GstVar.GucCFStatus = Fls_CFProcessReadCommand();
#else
        if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
          Fls_GstVar.GucDFStatus = Fls_DFProcessReadCommand();
        }
        else{
          Fls_GstVar.GucCFStatus = Fls_CFProcessReadCommand();
        }
#endif
      }
#if(FLS_COMPARE_API == STD_ON)
      else if(FLS_COMMAND_COMPARE == Fls_GVar.Fls_GenCommand){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)
        Fls_GstVar.GucDFStatus = Fls_DFProcessCompareCommand();
        #elif(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)
        Fls_GstVar.GucCFStatus = Fls_CFProcessCompareCommand();
#else
        if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
          Fls_GstVar.GucDFStatus = Fls_DFProcessCompareCommand();
        }
        else{
          Fls_GstVar.GucCFStatus = Fls_CFProcessCompareCommand();
        }
#endif
      }
#endif
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_READIMMEDIATE_API == STD_ON)
      else if(FLS_COMMAND_READ_IMM == Fls_GVar.Fls_GenCommand){
        Fls_GstVar.GucDFStatus = Fls_DFProcessReadImmCommand();
      }
#endif
#endif
      else{
      }
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                     (FLS_TIMEOUT_MONITORING == STD_ON))
      if((FLS_ZERO == Fls_GulTimeout) &&
                                  (FLS_TRUE == Fls_GVar.Fls_GblTimeOutMonitor)){
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                          FLS_MAINFUNCTION_SID, FLS_E_TIMEOUT);
        Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;
        Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;
        Fls_GVar.Fls_GenState = MEMIF_IDLE;
        Fls_GVar.Fls_GblTimeOutMonitor = FLS_FALSE;
#if(FLS_JOB_NOTIF_CONFIG == STD_ON)
        Fls_GpConfigPtr->pJobErrorNotificationPointer();
#endif
      }
      else{
      }
#endif
   }
   else{
   }
      if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                         (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
         switch(Fls_GVar.Fls_GenCommand){
        case FLS_COMMAND_READ:
        case FLS_COMMAND_COMPARE:
        case FLS_COMMAND_BLANKCHECK:
        case FLS_COMMAND_READ_IMM:
#if(FLS_INTERRUPT_MODE == STD_OFF)
        case FLS_COMMAND_ERASE:
        case FLS_COMMAND_WRITE:
#endif
             if((R_FDL_BUSY != Fls_GstVar.GucDFStatus) &&
                                (MEMIF_IDLE != Fls_GVar.Fls_GenState)){
               Fls_EndJobProcess();
             }
             else{
             }
        break;
#if(FLS_INTERRUPT_MODE == STD_ON)
        case FLS_COMMAND_ERASE:
        case FLS_COMMAND_WRITE:
#endif
        case FLS_COMMAND_NONE:
        default:
        break;
      }
#endif
   }
   else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
      if((R_FCL_BUSY != Fls_GstVar.GucCFStatus) &&
                                        (MEMIF_IDLE != Fls_GVar.Fls_GenState)){
        Fls_EndJobProcess();
      }
      else{
      }
#endif
   }
  }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  else{
  }
#endif
}

#define FLS_STOP_SEC_SCHEDULER_CODE
#include "MemMap.hpp"

#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"

FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Read
(Fls_AddressType SourceAddress,
P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
   Fls_LengthType Length){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  uint32 LulFlsBaseAddress;
  uint32 LulFlsTotalSize;
#endif
  Std_ReturnType LenReturnValue;
  LenReturnValue = E_OK;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_READ_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
#endif
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
   if(MEMIF_IDLE != Fls_GVar.Fls_GenState){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   if(MEMIF_BUSY == Fls_GVar.Fls_GenState){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_READ_SID, FLS_E_BUSY);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
#endif
  }
#if(FLS_DEV_ERROR_DETECT == STD_OFF)
   else if(FLS_ZERO == Length){
    LenReturnValue = E_NOT_OK;
  }
#endif
  else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LulFlsBaseAddress = FLS_CF_SMALLBLOCK_BASE_ADDRESS;
    LulFlsTotalSize = FLS_CF_TOTAL_SIZE;
#endif
    SourceAddress = SourceAddress - FLS_CF_OFFSET_VALUE;
    Fls_GVar.Fls_AccessType = FLS_CF_ACCESS;
    #elif(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)
    SourceAddress = SourceAddress + FLS_DF_BASE_ADDRESS;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LulFlsBaseAddress = FLS_DF_SECTOR_START_ADDRESS;
    LulFlsTotalSize = FLS_DF_TOTAL_SIZE;
#endif
    Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
#else
   if(FLS_CF_OFFSET_VALUE > SourceAddress){
      SourceAddress = SourceAddress + FLS_DF_BASE_ADDRESS;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      LulFlsBaseAddress = FLS_DF_SECTOR_START_ADDRESS;
      LulFlsTotalSize = FLS_DF_TOTAL_SIZE;
#endif
      Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
   }
   else{
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      LulFlsBaseAddress = FLS_CF_SMALLBLOCK_BASE_ADDRESS;
      LulFlsTotalSize = FLS_CF_TOTAL_SIZE;
#endif
      SourceAddress = SourceAddress - FLS_CF_OFFSET_VALUE;
      Fls_GVar.Fls_AccessType = FLS_CF_ACCESS;
   }
#endif

    Fls_GVar.Fls_GulReadAddress = SourceAddress;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   if((SourceAddress < LulFlsBaseAddress) ||
          ((SourceAddress - LulFlsBaseAddress) > (LulFlsTotalSize - FLS_ONE))){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                           FLS_READ_SID, FLS_E_PARAM_ADDRESS);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if((FLS_ZERO == Length) ||
          (((Fls_GVar.Fls_GulReadAddress - LulFlsBaseAddress) + Length)
          > LulFlsTotalSize)){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                            FLS_READ_SID, FLS_E_PARAM_LENGTH);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if(NULL_PTR == TargetAddressPtr){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_READ_SID, FLS_E_PARAM_DATA);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }

   if(E_OK == LenReturnValue)
#endif
   {
      Fls_GVar.Fls_GulRequestedLength = Length;
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                         (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
         if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
        Fls_GVar.Fls_GucOffset = (uint8)(SourceAddress &
                                          (FLS_PAGE_SIZE - FLS_ONE));
            if(FLS_ZERO != Fls_GVar.Fls_GucOffset){
          Fls_GVar.Fls_GulReadAddress = SourceAddress - Fls_GVar.Fls_GucOffset;
          Length = Length + Fls_GVar.Fls_GucOffset;
        }
        else{
        }
            if(FLS_ZERO != (Length & (FLS_PAGE_SIZE - FLS_ONE ))){
          Length = Length + (FLS_PAGE_SIZE -
                             (Length & (FLS_PAGE_SIZE - FLS_ONE)));
        }
        else{
        }
        Fls_GVar.pTempBufferAddress = (const uint8 *) &
                                             Fls_GulTempBuffer[FLS_ZERO];
      }
      else{
      }
#endif
      Fls_GVar.pBufferAddress = TargetAddressPtr;
      Fls_GVar.Fls_GulCurrentLength = Length;
      Fls_GVar.Fls_GenCommand = FLS_COMMAND_READ;
      Fls_GVar.Fls_GenState = MEMIF_BUSY;
      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_PENDING;
      Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
   }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   else{
   }
#endif
  }
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  return(LenReturnValue);
}
#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"

#if(FLS_COMPARE_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Compare
(Fls_AddressType SourceAddress,
P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
Fls_LengthType Length){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  uint32 LulFlsBaseAddress;
  uint32 LulFlsTotalSize;
#endif
  Std_ReturnType LenReturnValue;
  LenReturnValue = E_OK;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_COMPARE_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
#endif
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  if(MEMIF_IDLE != Fls_GVar.Fls_GenState){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   if(MEMIF_BUSY == Fls_GVar.Fls_GenState){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_COMPARE_SID, FLS_E_BUSY);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
#endif
  }
#if(FLS_DEV_ERROR_DETECT == STD_OFF)
  else if(FLS_ZERO == Length){
    LenReturnValue = E_NOT_OK;
  }
#endif
  else{
#if(FLS_FLASH_ACCESS == FLS_CODEFLASH_ACCESS)
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LulFlsBaseAddress = FLS_CF_SMALLBLOCK_BASE_ADDRESS;
    LulFlsTotalSize = FLS_CF_TOTAL_SIZE;
#endif
    SourceAddress = SourceAddress - FLS_CF_OFFSET_VALUE;
    Fls_GVar.Fls_AccessType = FLS_CF_ACCESS;
    #elif(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS)
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LulFlsBaseAddress = FLS_DF_SECTOR_START_ADDRESS;
    LulFlsTotalSize = FLS_DF_TOTAL_SIZE;
#endif
    SourceAddress = SourceAddress + FLS_DF_BASE_ADDRESS;
    Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
#else
   if(FLS_CF_OFFSET_VALUE > SourceAddress){
      SourceAddress = SourceAddress + FLS_DF_BASE_ADDRESS;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      LulFlsBaseAddress = FLS_DF_SECTOR_START_ADDRESS;
      LulFlsTotalSize = FLS_DF_TOTAL_SIZE;
#endif
      Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
   }
   else{
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      LulFlsBaseAddress = FLS_CF_SMALLBLOCK_BASE_ADDRESS;
      LulFlsTotalSize = FLS_CF_TOTAL_SIZE;
#endif
      SourceAddress = SourceAddress - FLS_CF_OFFSET_VALUE;
      Fls_GVar.Fls_AccessType = FLS_CF_ACCESS;
   }
#endif
    Fls_GVar.Fls_GulSrcDestAddress = SourceAddress;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   if((SourceAddress < LulFlsBaseAddress) ||
         ((SourceAddress - LulFlsBaseAddress) > (LulFlsTotalSize - FLS_ONE))){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                        FLS_COMPARE_SID, FLS_E_PARAM_ADDRESS);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if((FLS_ZERO == Length) ||
          (((SourceAddress - LulFlsBaseAddress) + Length) > LulFlsTotalSize)){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                         FLS_COMPARE_SID, FLS_E_PARAM_LENGTH);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if(NULL_PTR == TargetAddressPtr){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                           FLS_COMPARE_SID, FLS_E_PARAM_DATA);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if(E_OK == LenReturnValue)
#endif
   {
      Fls_GVar.Fls_GulRequestedLength = Length;
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                         (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
      if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
        Fls_GVar.Fls_GucOffset = (uint8)(SourceAddress &
                                          (FLS_PAGE_SIZE - FLS_ONE));
        if(FLS_ZERO != Fls_GVar.Fls_GucOffset){
          Fls_GVar.Fls_GulSrcDestAddress = SourceAddress -
                                                    Fls_GVar.Fls_GucOffset;
          Length = Length + Fls_GVar.Fls_GucOffset;
        }
        else{
        }
        if(FLS_ZERO != (Length & (FLS_PAGE_SIZE - FLS_ONE))){
          Length = Length + (FLS_PAGE_SIZE -
                             (Length & (FLS_PAGE_SIZE - FLS_ONE)));
        }
        else{
        }
      }
      else{
      }
#endif
      Fls_GVar.pTempBufferAddress = (const uint8 *) &
                                             Fls_GulTempBuffer[FLS_ZERO];
      Fls_GVar.pBufferAddress = TargetAddressPtr;
      Fls_GVar.Fls_GulCurrentLength = Length;
      Fls_GVar.Fls_GenCommand = FLS_COMMAND_COMPARE;
      Fls_GVar.Fls_GenState = MEMIF_BUSY;
      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_PENDING;
      Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
   }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   else{
   }
#endif
  }
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  return(LenReturnValue);
}
#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"

#endif

#if(FLS_SET_MODE_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"
FUNC(void, FLS_PUBLIC_CODE) Fls_SetMode (MemIf_ModeType Mode){
}
#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"
#endif

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                      (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_READIMMEDIATE_API == STD_ON)

#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_ReadImmediate
(Fls_AddressType SourceAddress,
P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
Fls_LengthType Length){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  uint32 LulFlsBaseAddress;
  uint32 LulFlsTotalSize;
#endif
  uint8 LucOffset;
  Std_ReturnType LenReturnValue;
  LenReturnValue = E_OK;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_READ_IMM_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
#endif
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  if(MEMIF_IDLE != Fls_GVar.Fls_GenState){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   if(MEMIF_BUSY == Fls_GVar.Fls_GenState){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_READ_IMM_SID, FLS_E_BUSY);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
#endif
  }
  else{
    Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
    SourceAddress = SourceAddress + FLS_DF_BASE_ADDRESS;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LulFlsBaseAddress = FLS_DF_SECTOR_START_ADDRESS;
    LulFlsTotalSize = FLS_DF_TOTAL_SIZE;
#endif
    Fls_GVar.Fls_GulReadAddress = SourceAddress;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   if((SourceAddress < LulFlsBaseAddress) ||
          ((SourceAddress - LulFlsBaseAddress) > (LulFlsTotalSize - FLS_ONE)))
   {
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                       FLS_READ_IMM_SID, FLS_E_PARAM_ADDRESS);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if((FLS_ZERO == Length) ||
          (((Fls_GVar.Fls_GulReadAddress - LulFlsBaseAddress) + Length)
          > LulFlsTotalSize)){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                       FLS_READ_IMM_SID, FLS_E_PARAM_LENGTH);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if(NULL_PTR == TargetAddressPtr){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                         FLS_READ_IMM_SID, FLS_E_PARAM_DATA);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if(E_OK == LenReturnValue)
#endif
   {
      if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
        Fls_GVar.Fls_ReadType = FLS_MISALIGNED_READ;
        Fls_GVar.Fls_GucOffset = (uint8)(SourceAddress &
                                          (FLS_PAGE_SIZE - FLS_ONE));
        if(FLS_ZERO != Fls_GVar.Fls_GucOffset){
          Fls_GVar.Fls_GulRequestedLength = Length;
          Fls_GVar.Fls_GulReadAddress = SourceAddress - Fls_GVar.Fls_GucOffset;
          Length = Length + Fls_GVar.Fls_GucOffset;
          if(FLS_ZERO != (Length & (FLS_PAGE_SIZE - FLS_ONE))){
            Length = Length + (FLS_PAGE_SIZE -
                             (Length & (FLS_PAGE_SIZE - FLS_ONE)));
          }
          else{
          }
          Fls_GVar.pTempBufferAddress = (const uint8 *) &
                                             Fls_GulTempBuffer[FLS_ZERO];
        }
        else{
          LucOffset = (uint8)((uint32)TargetAddressPtr &
                                          (FLS_PAGE_SIZE - FLS_ONE));
          if(FLS_ZERO == LucOffset){
            Fls_GVar.Fls_ReadType = FLS_ALIGNED_READ;
          }
          else{
            Fls_GVar.Fls_GulRequestedLength = Length;
            Fls_GVar.pTempBufferAddress = (const uint8 *) &
                                             Fls_GulTempBuffer[FLS_ZERO];
            if(FLS_ZERO != (Length & (FLS_PAGE_SIZE - FLS_ONE))){
              Length = Length + (FLS_PAGE_SIZE -
                             (Length & (FLS_PAGE_SIZE - FLS_ONE)));
            }
            else{
            }
          }
        }
      }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
      else{
      }
#endif
      Fls_GVar.pBufferAddress = TargetAddressPtr;
      Fls_GVar.Fls_GulCurrentLength = Length;
      Fls_GVar.Fls_GenCommand = FLS_COMMAND_READ_IMM;
      Fls_GVar.Fls_GenState = MEMIF_BUSY;
      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_PENDING;
      Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
   }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   else{
   }
#endif
  }
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  return(LenReturnValue);
}
#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"
#endif
#endif

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_BLANKCHECK_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_BlankCheck
(Fls_AddressType TargetAddress, Fls_LengthType Length){
  P2VAR(r_fdl_request_t,  AUTOMATIC, FLS_APPL_DATA) LpFdlReqCmd;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  uint32 LulFlsBaseAddress;
  uint32 LulFlsTotalSize;
#endif
  Std_ReturnType LenReturnValue;
  LenReturnValue = E_OK;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                          FLS_BLANK_CHECK_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
#endif
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  if(MEMIF_IDLE != Fls_GVar.Fls_GenState){
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   if(MEMIF_BUSY == Fls_GVar.Fls_GenState){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                             FLS_BLANK_CHECK_SID, FLS_E_BUSY);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
#endif
  }
  else{
    Fls_GVar.Fls_AccessType = FLS_DF_ACCESS;
    TargetAddress = TargetAddress + FLS_DF_BASE_ADDRESS;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
    LulFlsBaseAddress = FLS_DF_SECTOR_START_ADDRESS;
    LulFlsTotalSize = FLS_DF_TOTAL_SIZE;
#endif
    Fls_GVar.Fls_GulSrcDestAddress = TargetAddress;
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   if((TargetAddress < LulFlsBaseAddress) ||
          ((TargetAddress - LulFlsBaseAddress) > (LulFlsTotalSize - FLS_ONE))){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                   FLS_BLANK_CHECK_SID, FLS_E_PARAM_ADDRESS);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if((FLS_ZERO == Length) ||
          (((Fls_GVar.Fls_GulSrcDestAddress - LulFlsBaseAddress) + Length)
          > LulFlsTotalSize)){
      (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                   FLS_BLANK_CHECK_SID, FLS_E_PARAM_LENGTH);
      LenReturnValue = E_NOT_OK;
   }
   else{
   }
   if(E_OK == LenReturnValue)
#endif
   {
      Fls_GVar.Fls_GulCurrentLength = Length;
      LpFdlReqCmd = &Fls_GstVar.GstfdlRequest;
      LpFdlReqCmd->command_enu = R_FDL_CMD_BLANKCHECK;
      LpFdlReqCmd->idx_u32 = Fls_GVar.Fls_GulSrcDestAddress -
                                                        FLS_DF_BASE_ADDRESS;
      LpFdlReqCmd->cnt_u16 = (uint16)(Fls_GVar.Fls_GulCurrentLength / FLS_FOUR);
      LpFdlReqCmd->accessType_enu = R_FDL_ACCESS_USER;
#if(FLS_FHVE_REGS == SUPPORTED)
      if(FLS_FALSE == Fls_GVar.Fls_GblFlashEnable){
        Fls_SetFHVE(FLS_FLASH_PROTECTION_OFF);
        Fls_GVar.Fls_GblFlashEnable = FLS_TRUE;
      }
      else{
      }
#endif
      R_FDL_Execute (LpFdlReqCmd);
      Fls_GVar.Fls_GenCommand = FLS_COMMAND_BLANKCHECK;
      Fls_GVar.Fls_GenState = MEMIF_BUSY;
      Fls_GVar.Fls_GenJobResult = MEMIF_JOB_PENDING;
      Fls_GVar.Fls_GblCommandInitiated = FLS_FALSE;
      Fls_GVar.Fls_GblProcessContinue = FLS_FALSE;
   }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
   else{
   }
#endif
  }
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  return(LenReturnValue);
}
#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"
#endif
#endif

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_SUSPEND_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"

FUNC(void, FLS_PUBLIC_CODE) Fls_Suspend(void){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  volatile r_fdl_status_t LenFDLStatus;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LenReturnValue;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  LenReturnValue = E_OK;
  if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                                FLS_SUSPEND_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
  if(E_OK == LenReturnValue)
#endif
  {
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
#if(FLS_INTERRUPT_MODE == STD_ON)
#if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))
    Fls_GulTimeout = FLS_ISR_TIMEOUT_VALUE;
   while((Fls_GVar.Fls_MutexFlag == FLS_ONE) && (Fls_GulTimeout > FLS_ZERO))
#else

   while(Fls_GVar.Fls_MutexFlag == FLS_ONE)
#endif
   {
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                        (FLS_TIMEOUT_MONITORING == STD_ON))
      Fls_GulTimeout--;
#endif
   }
#endif
   if(MEMIF_IDLE != Fls_GVar.Fls_GenState){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
      if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
        if(R_FDL_SUSPENDED != Fls_GstVar.GstfdlRequest.status_enu){
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                        (FLS_TIMEOUT_MONITORING == STD_ON))
          Fls_GulTimeout = Fls_GpConfigPtr->ulFlsDFSuspendTimeoutValue;
#endif
#if(FLS_INTERRUPT_MODE == STD_ON)
          Fls_GVar.Fls_MutexFlag = FLS_ONE;
#endif
          LenFDLStatus = R_FDL_SuspendRequest();
          if(R_FDL_OK == LenFDLStatus){
            do{
              R_FDL_Handler();
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                   (FLS_TIMEOUT_MONITORING == STD_ON))
              Fls_GulTimeout--;
#endif
            }
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                         (FLS_TIMEOUT_MONITORING == STD_ON))
            while((Fls_GstVar.GstfdlRequest.status_enu == R_FDL_BUSY) &&
                                                 (Fls_GulTimeout > FLS_ZERO));
#else
            while(Fls_GstVar.GstfdlRequest.status_enu == R_FDL_BUSY);
#endif
#if(FLS_INTERRUPT_MODE == STD_ON)
            RH850_SV_MODE_IMR_OR(16, (Fls_GpConfigPtr->pFlEndImrAddress)
   ,                                  ~(Fls_GpConfigPtr->usFlEndImrMask));
#endif
            Fls_GVar.Fls_GenBackUpCmd = Fls_GVar.Fls_GenCommand;
            Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;
            Fls_GVar.Fls_GenState = MEMIF_IDLE;
            Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;
          }
          else{
          }
        }
        else{
        }
#if(FLS_INTERRUPT_MODE == STD_ON)
        Fls_GVar.Fls_MutexFlag = FLS_ZERO;
#endif
      }
      else{
      }
#endif
   }
   else{
   }
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  else{
  }
#endif
}
#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"
#endif
#endif

#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
#if(FLS_RESUME_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include "MemMap.hpp"
FUNC(void, FLS_PUBLIC_CODE) Fls_Resume(void){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                          (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
  volatile r_fdl_status_t LenFDLStatus;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LenReturnValue;
#endif
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  LenReturnValue = E_OK;
  if(FLS_UNINITIALIZED == Fls_GblInitStatus){
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID
   ,                                                FLS_RESUME_SID, FLS_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else{
  }
  if(E_OK == LenReturnValue)
#endif
  {
#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    FLS_ENTER_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
#if(FLS_INTERRUPT_MODE == STD_ON)
#if((FLS_DEV_ERROR_DETECT == STD_ON) && (FLS_TIMEOUT_MONITORING == STD_ON))
    Fls_GulTimeout = FLS_ISR_TIMEOUT_VALUE;
   while((Fls_GVar.Fls_MutexFlag == FLS_ONE) && (Fls_GulTimeout > FLS_ZERO))
#else
   while(Fls_GVar.Fls_MutexFlag == FLS_ONE)
#endif
   {
#if((FLS_DEV_ERROR_DETECT == STD_ON) && \
                                        (FLS_TIMEOUT_MONITORING == STD_ON))
      Fls_GulTimeout--;
#endif
   }
#endif
   if(MEMIF_IDLE == Fls_GVar.Fls_GenState){
#if(FLS_FLASH_ACCESS == FLS_DATAFLASH_ACCESS) || \
                                       (FLS_FLASH_ACCESS == FLS_CFDF_ACCESS)
      if(FLS_DF_ACCESS == Fls_GVar.Fls_AccessType){
        LenFDLStatus = R_FDL_ResumeRequest();
        if(R_FDL_OK == LenFDLStatus){
#if(FLS_INTERRUPT_MODE == STD_ON)
          RH850_SV_MODE_IMR_AND(16, (Fls_GpConfigPtr->pFlEndImrAddress)
   ,                                    (Fls_GpConfigPtr->usFlEndImrMask));
#endif
          R_FDL_Handler();
          Fls_GVar.Fls_GenCommand = Fls_GVar.Fls_GenBackUpCmd;
          Fls_GVar.Fls_GenBackUpCmd = FLS_COMMAND_NONE;
          Fls_GVar.Fls_GenState = MEMIF_BUSY;
          Fls_GVar.Fls_GenJobResult = MEMIF_JOB_PENDING;
        }
        else{
        }
      }
      else{
      }
#endif
   }
   else{
   }

#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    FLS_EXIT_CRITICAL_SECTION(DRIVERSTATE_DATA_PROTECTION);
#endif
  }
#if(FLS_DEV_ERROR_DETECT == STD_ON)
  else{
  }
#endif
}
#define FLS_STOP_SEC_PUBLIC_CODE
#include "MemMap.hpp"
#endif
#endif

