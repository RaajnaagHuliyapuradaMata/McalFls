#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_ON 0292
#endif

#include "r_typedefs.hpp"
#include "CfgMcalFls_Fcl.hpp"
#include "r_fcl_types.hpp"
#include "r_fcl_global.hpp"
#include "r_fcl_env.hpp"

#if(defined FCL_TEST_PATCH)
    TestPatch_t TestPatch;
#endif

R_FCL_STATIC uint8_t        R_FCL_I_read_memory_u08            (const uint32_t addr_u32);
R_FCL_STATIC uint16_t       R_FCL_I_read_memory_u16            (const uint32_t addr_u32);
R_FCL_STATIC uint32_t       R_FCL_I_read_memory_u32            (const uint32_t addr_u32);
R_FCL_STATIC void           R_FCL_I_write_memory_u16           (const uint32_t addr_u32, const uint16_t val_u16);
R_FCL_STATIC void           R_FCL_I_write_memory_u32           (const uint32_t addr_u32, const uint32_t val_u32);
R_FCL_STATIC void           R_FCL_I_write_unaligned_memory_u32 (const uint32_t addr_u32, const uint32_t val_u32);
R_FCL_STATIC uint32_t       R_FCL_I_GetCPUCorePid              (void);
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_Clear_Cache           (void);
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_Chk_DBFull            (void);
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_ForcedStop            (void);
R_FCL_STATIC void           R_FCL_FCUFct_RestoreLastState      (void);
R_FCL_STATIC void           R_FCL_FCUFct_ClearStatus           (void);
R_FCL_STATIC void           R_FCL_FCUFct_GetDeviceInfo         (void);
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_VerifyID              (void);
#ifdef R_FCL_INNER_NO_FCU_COPY
#else
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_VerifyChecksum        (void);
#endif
R_FCL_STATIC void           R_FCL_FCUFct_SetFrequency          (void);
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_GetResult             (r_fcl_flag_t cmdSpdExec_enu);
R_FCL_STATIC r_fcl_flag_t   R_FCL_FCUFct_ChkSuspended          (void);
R_FCL_STATIC void           R_FCL_FCUFct_HandleMultiOperation_IntErr (r_fcl_op_status_t opState);
R_FCL_STATIC void           R_FCL_FCUFct_PrepareEnvironment_IntErr (r_fcl_op_status_t opState);

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC uint32_t R_FCL_I_read_memory_u32 (const uint32_t addr_u32){
    #if(defined FCL_TEST_PATCH)
        return (test_cb_read_u32 (addr_u32));
    #else
        return ( *( (volatile uint32_t *)(addr_u32) ) );
    #endif
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC uint16_t R_FCL_I_read_memory_u16 (const uint32_t addr_u32){
    #if(defined FCL_TEST_PATCH)
        return (test_cb_read_u16 (addr_u32));
    #else
        return ( *( (volatile uint16_t *)(addr_u32) ) );
    #endif
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC uint8_t R_FCL_I_read_memory_u08 (const uint32_t addr_u32){
    #if(defined FCL_TEST_PATCH)
        return (test_cb_read_u8 (addr_u32));
    #else
        return ( *( (volatile uint8_t *)(addr_u32) ) );
    #endif
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC void R_FCL_I_write_unaligned_memory_u32 (const uint32_t addr_u32, const uint32_t val_u32){
    R_FCL_I_write_memory_u08 (addr_u32,       (uint8_t)val_u32);
    R_FCL_I_write_memory_u08 ((addr_u32 + 1), (uint8_t)(val_u32 >> 8));
    R_FCL_I_write_memory_u08 ((addr_u32 + 2), (uint8_t)(val_u32 >> 16));
    R_FCL_I_write_memory_u08 ((addr_u32 + 3), (uint8_t)(val_u32 >> 24));
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC void R_FCL_I_write_memory_u32 (const uint32_t addr_u32, const uint32_t val_u32){
    #if(defined FCL_TEST_PATCH)
        test_cb_write_u32 (addr_u32, val_u32);
    #else
        ( *( (volatile uint32_t *)(addr_u32) ) ) = val_u32;
    #endif
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC void R_FCL_I_write_memory_u16 (const uint32_t addr_u32, const uint16_t val_u16){
    #if(defined FCL_TEST_PATCH)
        test_cb_write_u16 (addr_u32, val_u16);
    #else
        ( *( (volatile uint16_t *)(addr_u32) ) ) = val_u16;
    #endif
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
void R_FCL_I_write_memory_u08 (const uint32_t addr_u32, const uint8_t val_u08){
    #if(defined FCL_TEST_PATCH)
        test_cb_write_u8 (addr_u32, val_u08);
    #else
        ( *( (volatile uint8_t *)(addr_u32) ) ) = val_u08;
    #endif
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC uint32_t R_FCL_I_GetCPUCorePid (void){
    uint32_t pid;

    #if R_FCL_COMPILER == R_FCL_COMP_GHS
        pid = (uint32_t)__STSR(R_SYSTEM_REGISTER_PID);
    #elif R_FCL_COMPILER == R_FCL_COMP_IAR
        pid = (uint32_t)__STSR(R_SYSTEM_REGISTER_PID);
    #elif R_FCL_COMPILER == R_FCL_COMP_REC
        pid = (uint32_t)__stsr_rh(R_SYSTEM_REGISTER_PID);
    #endif

    pid &= R_PID_CORE_MASK;

    return (pid);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_Fct_CallFromRAM (void){
    if(R_FCL_NULL != g_fcl_data_str.executionPtr_p){
        (*g_fcl_data_str.executionPtr_p)();
    }
    else{
        R_FCL_FCUFct_GetConfigArea ();
    }
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_VerifyID ( void ){
    uint32_t       result;
    r_fcl_status_t ret;

    ret = R_FCL_OK;

    R_FCL_I_write_memory_u32 (R_FPSYS_REGADD_AUTH_ID0_U32, (g_fcl_data_str.RTCfg_pstr->id_au32[0]));
    R_FCL_I_write_memory_u32 (R_FPSYS_REGADD_AUTH_ID1_U32, (g_fcl_data_str.RTCfg_pstr->id_au32[1]));
    R_FCL_I_write_memory_u32 (R_FPSYS_REGADD_AUTH_ID2_U32, (g_fcl_data_str.RTCfg_pstr->id_au32[2]));
    R_FCL_I_write_memory_u32 (R_FPSYS_REGADD_AUTH_ID3_U32, (g_fcl_data_str.RTCfg_pstr->id_au32[3]));

    (void) R_FCL_I_read_memory_u32 (R_FPSYS_REGADD_AUTH_ID3_U32);

    result = R_FCL_I_read_memory_u32 (R_FPSYS_REGADD_AUTH_STATUS_U32);
    if(R_FPSYS_REGBIT_AUTH_STATUS_LOCKED == result){
        ret = R_FCL_ERR_PROTECTION;
    }

    return (ret);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_Clear_Cache (void){
    uint32_t bwc;
    uint32_t pid;
    uint32_t res;
    r_fcl_status_t ret;

    pid = R_FCL_I_GetCPUCorePid ();

    if(R_PID_CORE_G3K == pid){
        bwc = R_BWCBUF_G3K_ADD;
    }

    else if(R_PID_CORE_G3KH == pid){
        bwc = R_BWCBUF_G3KH_ADD;
    }

    else{
        bwc = 0x00000000uL;
    }

    ret = R_FCL_OK;
    res = R_FCL_FCUFct_Clear_Cache_Asm (bwc, R_FCL_TIMEOUT_CC);
    if(0x00000000uL != res){
        ret = R_FCL_ERR_INTERNAL;
    }

    return (ret);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_Chk_DBFull (void){
    r_fcl_status_t ret;
    uint32_t res;

    res = R_FCL_FCUFct_ChkReg (R_FPSYS_REGADD_FSTATR_U32,
                               R_FPSYS_REGBIT_FSTATR_DBFULL,
                               0x00000000uL,
                               R_FCL_TIMEOUT_CHKREG);

    if(0x00000000uL == res){
        ret = R_FCL_OK;
    }

    else{
        ret = R_FCL_ERR_INTERNAL;
    }

    return (ret);
}

#ifdef R_FCL_INNER_NO_FCU_COPY
#else

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_VerifyChecksum  (void){
    uint32_t startAddr;
    uint32_t endAddr;
    uint32_t chkSum;
    uint32_t chkSumCmp;
    r_fcl_status_t ret;
    r_fcl_status_t ret1;

    R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FCURAME_U16, R_FPSYS_REGBIT_FCURAME_FCRME +
                              R_FPSYS_REGBIT_FCURAME_KEY);

    #ifdef R_FCL_INNER_NO_BFA_SWITCH
        ret = R_FCL_OK;
    #else
        R_FCL_FCUFct_Switch_BFlash (0x01u);
        ret = R_FCL_FCUFct_Clear_Cache ();
    #endif

    endAddr   = R_FCL_I_read_memory_u32 (R_FPSYS_FCURAM_AREA_CHKSUM_END);
    chkSumCmp = R_FCL_I_read_memory_u32 (R_FPSYS_FCURAM_AREA_CHKSUM);

    #ifdef R_FCL_INNER_NO_BFA_SWITCH
        ret1 = R_FCL_OK;
    #else
        R_FCL_FCUFct_Switch_BFlash (0x00u);
        ret1 = R_FCL_FCUFct_Clear_Cache ();
    #endif

    if(R_FCL_OK == ret){
        ret = ret1;
    }

    if(R_FCL_OK == ret){
        endAddr <<= 2;
        endAddr += R_FPSYS_FCURAM_AREA_BASE;
        chkSum  = 0x00000000uL;
        for (startAddr = R_FPSYS_FCURAM_AREA_BASE; startAddr < endAddr; startAddr +=2)
        {
            chkSum += (uint32_t)(R_FCL_I_read_memory_u16 (startAddr));
        }

        R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FCURAME_U16,
                                  R_FPSYS_REGBIT_FCURAME_RESET + R_FPSYS_REGBIT_FCURAME_KEY);

        if(chkSum != chkSumCmp)
        {
            ret = R_FCL_ERR_INTERNAL;
        }
    }

    return (ret);
}

#endif

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC void R_FCL_FCUFct_SetFrequency  (void){
    uint16_t       ffcu;

    if(g_fcl_data_str.deviceInfo_str.fVersion_u8 != 0xff){
        ffcu = g_fcl_data_str.RTCfg_pstr->frequencyCpuMHz_u16;

        if((g_fcl_data_str.deviceInfo_str.fMin_u16 > ffcu) ||
            (g_fcl_data_str.deviceInfo_str.fMax_u16 < ffcu))
        {
            g_fcl_data_str.opVar_str.opResult_enu = R_FCL_ERR_PARAMETER;
        }
        else
        {
            if(g_fcl_data_str.deviceInfo_str.fDivider_u8 == 0xFF)
            {
                ffcu = g_fcl_data_str.deviceInfo_str.fPClk_u16;
            }
            else
            {
                if(g_fcl_data_str.deviceInfo_str.fDivider_u8 > 0)
                {
                    ffcu = ( (ffcu + g_fcl_data_str.deviceInfo_str.fDivider_u8) - 1) /
                            g_fcl_data_str.deviceInfo_str.fDivider_u8;
                }
            }

            R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_PCKAR_U16, R_FPSYS_REGBIT_PCKAR_KEY + (uint16_t)ffcu);
            g_fcl_data_str.opVar_str.opResult_enu = R_FCL_OK;
        }
    }

    else{
        g_fcl_data_str.opVar_str.opResult_enu = R_FCL_OK;
    }
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
r_fcl_status_t R_FCL_FCUFct_SwitchMode_Start (r_fcl_mode_t mode_enu){
    r_fcl_status_t ret;
    uint32_t       regFSTATR;
    uint16_t       regFENTRYR;

    ret = R_FCL_OK;

    if(R_FCL_READ_MODE == mode_enu){
        regFSTATR = R_FCL_I_read_memory_u32 (R_FPSYS_REGADD_FSTATR_U32);

        if(R_FPSYS_REGBIT_FSTATR_RESET != ( regFSTATR & (R_FPSYS_REGBIT_FSTATR_ERSERR +
                                                          R_FPSYS_REGBIT_FSTATR_PRGERR +
                                                          R_FPSYS_REGBIT_FSTATR_ILGERR)))
        {
            R_FCL_FCUFct_ClearStatus ();
        }
    }
    else{
        regFENTRYR = R_FCL_I_read_memory_u16 (R_FPSYS_REGADD_FENTRYR_U16);

        if((uint16_t)(regFENTRYR & R_FPSYS_MODE_DPE) == R_FPSYS_MODE_DPE)
        {
            ret = R_FCL_ERR_REJECTED;
        }

        else if((uint16_t)(regFENTRYR & 0x00FF) == mode_enu)
        {
            ret = R_FCL_ERR_REJECTED;
        }
        else
        {
            R_FCL_I_write_memory_u32 (R_FPSYS_REGADD_FSADR_U32, 0x00000000uL);
            R_FCL_I_write_memory_u32 (R_FPSYS_REGADD_FEADR_U32, 0x00000000uL);
        }
    }

    if(R_FCL_OK == ret){
        R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FENTRYR_U16, (uint16_t)(mode_enu) + R_FPSYS_REGBIT_FENTRY_KEY);
        g_fcl_data_str.flashMode_enu = mode_enu;
    }

    return (ret);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
r_fcl_status_t R_FCL_FCUFct_SwitchMode_Check ( void ){
    r_fcl_status_t ret;
    uint16_t       regFENTRYR;

    ret = R_FCL_BUSY;

    regFENTRYR = R_FCL_I_read_memory_u16 (R_FPSYS_REGADD_FENTRYR_U16);
    regFENTRYR &= (R_FPSYS_MODE_DPE + R_FPSYS_MODE_CPE);
    if((uint16_t)g_fcl_data_str.flashMode_enu == regFENTRYR){
        ret = R_FCL_OK;
    }

    return (ret);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_ForcedStop (void){
    r_fcl_status_t ret;
    uint32_t res;

    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_FORCED_STOP);

    res = R_FCL_FCUFct_ChkReg (R_FPSYS_REGADD_FSTATR_U32,
                               R_FPSYS_REGBIT_FSTATR_FRDY,
                               R_FPSYS_REGBIT_FSTATR_FRDY,
                               R_FCL_TIMEOUT_CHKREG);

    if(0x00000000uL == res){
        ret = R_FCL_OK;
    }

    else{
        ret = R_FCL_ERR_INTERNAL;
    }

    return (ret);

}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC r_fcl_flag_t R_FCL_FCUFct_ChkSuspended (void){
    uint32_t        regFSTATR;
    r_fcl_flag_t    ret;

    ret = R_FCL_FALSE;

    regFSTATR = R_FCL_I_read_memory_u32 (R_FPSYS_REGADD_FSTATR_U32);
    if((R_FPSYS_REGBIT_FSTATR_PRGSPD == (regFSTATR & R_FPSYS_REGBIT_FSTATR_PRGSPD)) ||
        (R_FPSYS_REGBIT_FSTATR_ERSSPD == (regFSTATR & R_FPSYS_REGBIT_FSTATR_ERSSPD))){
        ret = R_FCL_TRUE;
    }

    return ret;
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC void R_FCL_FCUFct_ClearStatus (void){
    uint32_t res32;
    uint8_t  res8;

    res32 = R_FCL_I_read_memory_u32 (R_FPSYS_REGADD_FSTATR_U32);

    if(R_FPSYS_REGBIT_FSTATR_ILGERR == (R_FPSYS_REGBIT_FSTATR_ILGERR & res32)){
        res8 = R_FCL_I_read_memory_u08 (R_FPSYS_REGADD_FASTAT_U8);

        if(R_FPSYS_REGBIT_FASTAT_CMDLK != res8)
        {
            R_FCL_I_write_memory_u08 (R_FPSYS_REGADD_FASTAT_U8, R_FPSYS_REGBIT_FASTAT_CMDLK);
        }
    }

    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_CLEARSTAT);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC void R_FCL_FCUFct_RestoreLastState (void){
    if(g_fcl_data_str.suspendInfo_str.flagSuspended_enu == R_FCL_FALSE){
        g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_PREPARED;
    }
    else{
        g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_SUSPENDED;
    }
}

#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_HandleResume (void){
    uint32_t regFSTATR;

    if(R_FCL_TRUE == g_fcl_data_str.waitAckModeSwitch_enu){
        if(R_FCL_OK == R_FCL_FCUFct_SwitchMode_Check())
        {
            R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FMATSELC_U16,
                                      g_fcl_data_str.suspendInfo_str.matSel_u16 + R_FPSYS_REGBIT_FMATSELC_KEY);

            g_fcl_data_str.reqInt_pstr            = g_fcl_data_str.suspendInfo_str.reqSuspend_pstr;
            g_fcl_data_str.opVar_str.opAddr_u32   = g_fcl_data_str.suspendInfo_str.opSuspend_str.opAddr_u32;
            g_fcl_data_str.opVar_str.opCnt_u16    = g_fcl_data_str.suspendInfo_str.opSuspend_str.opCnt_u16;
            g_fcl_data_str.opVar_str.opStatus_enu = g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu;
            g_fcl_data_str.opVar_str.opResult_enu = g_fcl_data_str.suspendInfo_str.opSuspend_str.opResult_enu;

            g_fcl_data_str.suspendInfo_str.reqSuspend_pstr            = R_FCL_REQUEST_POINTER_UNDEFINED;
            g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu = R_FCL_OP_IDLE_STATE;
            g_fcl_data_str.suspendInfo_str.spdResRequest_enu          = R_FCL_FALSE;
            g_fcl_data_str.suspendInfo_str.flagSuspended_enu          = R_FCL_FALSE;

            g_fcl_data_str.deviceInfo_str.matSel_u16 = g_fcl_data_str.suspendInfo_str.matSel_u16;

            regFSTATR = R_FCL_I_read_memory_u32 (R_FPSYS_REGADD_FSTATR_U32);
            if((R_FPSYS_REGBIT_FSTATR_PRGSPD == (regFSTATR & R_FPSYS_REGBIT_FSTATR_PRGSPD)) ||
                (R_FPSYS_REGBIT_FSTATR_ERSSPD == (regFSTATR & R_FPSYS_REGBIT_FSTATR_ERSSPD)))
            {
                R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_RESUME);
            }
            g_fcl_data_str.intStatus_enu           = R_FCL_ISTAT_BUSY;
            g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_BUSY;
            g_fcl_data_str.waitAckModeSwitch_enu   = R_FCL_FALSE;
        }
    }
    else{
        if( g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu != R_FCL_OP_FINISHED_STATE)
        {
            R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FMATSELC_U16,
                                      g_fcl_data_str.suspendInfo_str.matSel_u16 + R_FPSYS_REGBIT_FMATSELC_KEY);
        }

        g_fcl_data_str.reqInt_pstr             = g_fcl_data_str.suspendInfo_str.reqSuspend_pstr;
        g_fcl_data_str.opVar_str.opAddr_u32    = g_fcl_data_str.suspendInfo_str.opSuspend_str.opAddr_u32;
        g_fcl_data_str.opVar_str.opCnt_u16     = g_fcl_data_str.suspendInfo_str.opSuspend_str.opCnt_u16;
        g_fcl_data_str.opVar_str.opStatus_enu  = g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu;
        g_fcl_data_str.opVar_str.opResult_enu  = g_fcl_data_str.suspendInfo_str.opSuspend_str.opResult_enu;
        g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_BUSY;

        g_fcl_data_str.deviceInfo_str.matSel_u16 = g_fcl_data_str.suspendInfo_str.matSel_u16;

        g_fcl_data_str.suspendInfo_str.reqSuspend_pstr            = R_FCL_REQUEST_POINTER_UNDEFINED;
        g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu = R_FCL_OP_IDLE_STATE;
        g_fcl_data_str.suspendInfo_str.spdResRequest_enu          = R_FCL_FALSE;
        g_fcl_data_str.suspendInfo_str.flagSuspended_enu          = R_FCL_FALSE;
        g_fcl_data_str.intStatus_enu                              = R_FCL_ISTAT_BUSY;
    }
}

#endif

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
r_fcl_flag_t R_FCL_FCUFct_CheckMode (void){
    r_fcl_flag_t ret;
    uint8_t      regVal;

    ret = R_FCL_FALSE;

    regVal = R_FCL_I_read_memory_u08 (R_FPSYS_REGADD_FPMON_U8);
    if(R_FPSYS_REGBIT_SFWE == (regVal & R_FPSYS_REGBIT_SFWE)){
        ret = R_FCL_TRUE;
    }

    return (ret);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC r_fcl_status_t R_FCL_FCUFct_GetResult (r_fcl_flag_t cmdSpdExec_enu){
    r_fcl_status_t ret;
    uint32_t       regFSTATR;
    uint16_t       regFPESTAT;

    regFSTATR = R_FCL_I_read_memory_u32 (R_FPSYS_REGADD_FSTATR_U32);

    if(R_FPSYS_REGBIT_FSTATR_FRDY == (regFSTATR & R_FPSYS_REGBIT_FSTATR_FRDY)){
        #if(defined FCL_TEST_PATCH)
            if(0 != TestPatch.status_patch_active)
            {
                regFSTATR = TestPatch.status_patch_value;
                if(UINT32_MAX != TestPatch.status_patch_active)
                {
                    TestPatch.status_patch_active--;
                }
            }
        #endif

        if((R_FPSYS_REGBIT_FSTATR_FCURAMERR == (regFSTATR & R_FPSYS_REGBIT_FSTATR_FCURAMERR)) ||
            (R_FPSYS_REGBIT_FSTATR_TBLDERR   == (regFSTATR & R_FPSYS_REGBIT_FSTATR_TBLDERR))   ||
            (R_FPSYS_REGBIT_FSTATR_CONFDERR  == (regFSTATR & R_FPSYS_REGBIT_FSTATR_CONFDERR))  ||
            (R_FPSYS_REGBIT_FSTATR_FCUERR    == (regFSTATR & R_FPSYS_REGBIT_FSTATR_FCUERR))    ||
            (R_FPSYS_REGBIT_FSTATR_OTPDERR   == (regFSTATR & R_FPSYS_REGBIT_FSTATR_OTPDERR)))
        {
            ret = R_FCL_ERR_INTERNAL;
        }

        else if(R_FPSYS_REGBIT_FSTATR_ILGERR == (regFSTATR & R_FPSYS_REGBIT_FSTATR_ILGERR))
        {
            if(R_FCL_FALSE == cmdSpdExec_enu)
            {
                ret = R_FCL_ERR_INTERNAL;
            }
            else
            {
                ret = R_FCL_ERR_SUSPEND_FAILED;
            }
        }

        else if(R_FPSYS_REGBIT_FSTATR_FHVEERR == (regFSTATR & R_FPSYS_REGBIT_FSTATR_FHVEERR))
        {
            ret = R_FCL_ERR_PROTECTION;
        }

        else if(R_FPSYS_REGBIT_FSTATR_ERSERR == (regFSTATR & R_FPSYS_REGBIT_FSTATR_ERSERR))
        {
            regFPESTAT = R_FCL_I_read_memory_u16 (R_FPSYS_REGADD_FPESTAT_U16);
            if(R_FPSYS_REGBIT_FPESTAT_ERASELOCK != (regFPESTAT & R_FPSYS_REGBIT_FPESTAT_ERASELOCK))
            {
                ret = R_FCL_ERR_ERASE;
            }
            else
            {
                ret = R_FCL_ERR_PROTECTION;
            }

        }

        else if(R_FPSYS_REGBIT_FSTATR_PRGERR == (regFSTATR & R_FPSYS_REGBIT_FSTATR_PRGERR))
        {
            regFPESTAT = R_FCL_I_read_memory_u16 (R_FPSYS_REGADD_FPESTAT_U16);
            if(R_FPSYS_REGBIT_FPESTAT_WRITELOCK != (regFPESTAT & R_FPSYS_REGBIT_FPESTAT_WRITELOCK))
            {
                ret = R_FCL_ERR_WRITE;
            }
            else
            {
                ret = R_FCL_ERR_PROTECTION;
            }
        }

        else
        {
            ret = R_FCL_OK;
        }
    }

    else{
        ret = R_FCL_BUSY;
    }

    return (ret);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
void R_FCL_FCUFct_GetConfigArea (void){
    uint16_t data;
    uint16_t i;
    uint32_t bufAddr;
    uint32_t readAddr;
    uint32_t cnt;
    r_fcl_status_t ret;
    r_fcl_status_t ret1;

    R_FCL_FCUFct_Switch_BFlash (0x01u);
    ret = R_FCL_FCUFct_Clear_Cache ();

    if(R_FCL_OK == ret){
        if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_OPB)
        {
            readAddr = R_FPSYS_CONFIG_AREA_OPTIONBYTES;
            cnt = R_PRG_CFG_TRANSFERSIZE_OPB;
        }
        else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_ID)
        {
            readAddr = R_FPSYS_CONFIG_AREA_OCD;
            cnt = R_PRG_CFG_TRANSFERSIZE_OCD;
        }
        else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_OTP)
        {
            readAddr = g_fcl_data_str.opVar_str.opAddr_u32;
            cnt = R_PRG_CFG_TRANSFERSIZE_OTP;
        }

        else
        {
            readAddr = R_FPSYS_CONFIG_AREA_RESET;
            cnt = R_PRG_CFG_TRANSFERSIZE_RESET;
        }

        bufAddr = g_fcl_data_str.reqInt_pstr->bufferAdd_u32;

        for (i = 0; i < (2 * cnt); i++)
        {
            data = R_FCL_I_read_memory_u08 (readAddr);
            R_FCL_I_write_memory_u08 (bufAddr, (uint8_t)data);
            bufAddr++;
            readAddr++;
        }
    }

    R_FCL_FCUFct_Switch_BFlash (0x00u);
    ret1 = R_FCL_FCUFct_Clear_Cache ();

    if(R_FCL_OK == ret){
        ret = ret1;
    }

    if(R_FCL_OK != ret){
        g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_NOINIT;
    }

    g_fcl_data_str.reqInt_pstr->status_enu = ret;
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_SetConfigArea (void){
    uint32_t flag;
    uint8_t  i;

    if(R_FCL_FCUFct_CheckMode () == R_FCL_FALSE){
        g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_FLMD0;
    }
    else{
        if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_OPB)
        {
            g_fcl_data_str.opVar_str.buffAddr_u32 = g_fcl_data_str.reqInt_pstr->bufferAdd_u32;
            g_fcl_data_str.opVar_str.opAddr_u32   = R_FPSYS_CONFIG_AREA_OPTIONBYTES;
            g_fcl_data_str.opVar_str.opCnt_u16    = R_PRG_CFG_TRANSFERSIZE_OPB;
        }
        else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_OTP)
        {
            g_fcl_data_str.opVar_str.opCnt_u16 = R_PRG_CFG_TRANSFERSIZE_OTP;
        }
        else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_ID)
        {
            g_fcl_data_str.opVar_str.buffAddr_u32 = g_fcl_data_str.reqInt_pstr->bufferAdd_u32;
            g_fcl_data_str.opVar_str.opAddr_u32   = R_FPSYS_CONFIG_AREA_OCD;
            g_fcl_data_str.opVar_str.opCnt_u16    = R_PRG_CFG_TRANSFERSIZE_OCD;
        }
        else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_RESET_VECTOR)
        {
            g_fcl_data_str.opVar_str.buffAddr_u32 = g_fcl_data_str.reqInt_pstr->bufferAdd_u32;
            g_fcl_data_str.opVar_str.opAddr_u32   = R_FPSYS_CONFIG_AREA_RESET;
            g_fcl_data_str.opVar_str.opCnt_u16    = R_PRG_CFG_TRANSFERSIZE_RESET;
        }

        else
        {
            flag = g_fcl_data_str.deviceInfo_str.secureData_u32;
            g_fcl_data_str.opVar_str.opAddr_u32 = R_FPSYS_CONFIG_AREA_SEC_FLAGS;
            g_fcl_data_str.opVar_str.opCnt_u16  = R_PRG_CFG_TRANSFERSIZE;

            if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_READ_PROTECT_FLAG)
            {
                flag = flag & ~(1u << R_RDPR_FLAG_SHIFT);
            }
            else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_WRITE_PROTECT_FLAG)
            {
                flag = flag & ~(1u << R_WRPR_FLAG_SHIFT);
            }
            else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_ERASE_PROTECT_FLAG)
            {
                flag = flag & ~(1u << R_SEPR_FLAG_SHIFT);
            }
            else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_SERIAL_PROG_DISABLED)
            {
                flag = flag & ~(1u << R_SPD_FLAG_SHIFT);
            }
            else
            {
                flag = flag & ~(1u << R_RDPR_FLAG_SHIFT);
                flag = flag & ~(1u << R_SEPR_FLAG_SHIFT);
                flag = flag & ~(1u << R_WRPR_FLAG_SHIFT);
                flag = flag & ~(1u << R_SPIE_FLAG_SHIFT);
            }
            flag = flag & 0xfffffff0u;

            g_fcl_data_str.intBuf_au08[0] = (uint8_t)flag;
            g_fcl_data_str.intBuf_au08[1] = (uint8_t)(flag >> 8u);
            g_fcl_data_str.intBuf_au08[2] = (uint8_t)(flag >> 16u);
            g_fcl_data_str.intBuf_au08[3] = (uint8_t)(flag >> 24u);
            for (i = 4; i < (2*R_PRG_CFG_TRANSFERSIZE); i++)
            {
                g_fcl_data_str.intBuf_au08[i] = (uint8_t)0xffu;
            }
            g_fcl_data_str.opVar_str.buffAddr_u32 = (uint32_t)(&g_fcl_data_str.intBuf_au08[0]);
        }
        g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_BUSY;
        g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_PREPARE_STATE;
    }
}

#ifdef R_FCL_SUPPORT_SECURITYFLAGS

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_GetSecurityFlag (void){
    uint32_t data;

    if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_READ_PROTECT_FLAG){
        data = (((~g_fcl_data_str.deviceInfo_str.secureData_u32) & R_RDPR_FLAG_MASK) >> R_RDPR_FLAG_SHIFT);
    }
    else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_WRITE_PROTECT_FLAG){
        data = (((~g_fcl_data_str.deviceInfo_str.secureData_u32) & R_WRPR_FLAG_MASK) >> R_WRPR_FLAG_SHIFT);
    }
    else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_ERASE_PROTECT_FLAG){
        data = (((~g_fcl_data_str.deviceInfo_str.secureData_u32) & R_SEPR_FLAG_MASK) >> R_SEPR_FLAG_SHIFT);
    }
    else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_SERIAL_PROG_DISABLED){
        data = (((~g_fcl_data_str.deviceInfo_str.secureData_u32) & R_SPD_FLAG_MASK) >> R_SPD_FLAG_SHIFT);
    }
    else{
        data = (((~g_fcl_data_str.deviceInfo_str.secureData_u32) & R_SPIE_FLAG_MASK) >> R_SPIE_FLAG_SHIFT);
    }

    R_FCL_I_write_unaligned_memory_u32 (g_fcl_data_str.reqInt_pstr->bufferAdd_u32, data);

    g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_OK;
}

#endif

#ifdef R_FCL_SUPPORT_BLOCKCNT

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_GetBlockCnt (void){
    R_FCL_I_write_unaligned_memory_u32 (g_fcl_data_str.reqInt_pstr->bufferAdd_u32,
                                        g_fcl_data_str.deviceInfo_str.blkCnt_u16);

    g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_OK;
}

#endif

#ifdef R_FCL_SUPPORT_DEVICENAME

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_GetDeviceName (void){
    uint32_t bufAddr;
    uint8_t  i;

    bufAddr = g_fcl_data_str.reqInt_pstr->bufferAdd_u32;

    for (i = 0; i < 16; i++){
        R_FCL_I_write_memory_u08 (bufAddr, g_fcl_data_str.deviceInfo_str.deviceName_au08[i]);
        bufAddr += 1;
    }
    g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_OK;
}

#endif

#ifdef R_FCL_SUPPORT_BLOCKENDADDR

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_GetBlockEndAddr (void){
    uint32_t blk;
    uint32_t data;

    if(R_FCL_USERBOOT_AREA_SELECT == (g_fcl_data_str.reqInt_pstr->idx_u32 & R_FCL_USERBOOT_AREA_SELECT)){
        if( ((g_fcl_data_str.reqInt_pstr->idx_u32 & R_FLI_USERBOOT_AREA_MASK) <
               g_fcl_data_str.deviceInfo_str.usrBlkCnt32kB_u32)
           && (g_fcl_data_str.deviceInfo_str.accessExtendedUserArea_enu != R_FCL_FALSE) )
        {
            blk = ((g_fcl_data_str.reqInt_pstr->idx_u32 & R_FLI_USERBOOT_AREA_MASK) + 1);
            data = (blk * R_FLI_BLOCK_SIZE) - 1;
            data = data + R_FLI_USERBOOT_AREA_START;
            R_FCL_I_write_unaligned_memory_u32 (g_fcl_data_str.reqInt_pstr->bufferAdd_u32, data);
            g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_OK;
        }
        else
        {
            g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
        }
    }

    else{
        if(g_fcl_data_str.reqInt_pstr->idx_u32 < g_fcl_data_str.deviceInfo_str.blkCnt_u16)
        {
            if(g_fcl_data_str.reqInt_pstr->idx_u32 < g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8)
            {
                blk = (g_fcl_data_str.reqInt_pstr->idx_u32 + 1);
                data = (blk * R_FLI_SMALL_BLOCK_SIZE) - 1;
                R_FCL_I_write_unaligned_memory_u32 (g_fcl_data_str.reqInt_pstr->bufferAdd_u32, data);
            }

            else
            {
                if(g_fcl_data_str.reqInt_pstr->idx_u32 <
                   (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 +
                    g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32))
                {
                    blk  = (g_fcl_data_str.reqInt_pstr->idx_u32 + 1) -
                             g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8;
                    data = ((g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 * R_FLI_SMALL_BLOCK_SIZE) +
                            (blk * R_FLI_BLOCK_SIZE)) - 1;
                    R_FCL_I_write_unaligned_memory_u32 (g_fcl_data_str.reqInt_pstr->bufferAdd_u32, data);
                }
                else
                {
                    blk  = (g_fcl_data_str.reqInt_pstr->idx_u32 + 1) -
                            (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 +
                             g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32);
                    data = (R_FLI_CFLASH2_START + (blk * R_FLI_BLOCK_SIZE)) - 1;
                    R_FCL_I_write_unaligned_memory_u32 (g_fcl_data_str.reqInt_pstr->bufferAdd_u32, data);
                }
            }
            g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_OK;
        }
        else
        {
            g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
        }
    }
}

#endif

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC void R_FCL_FCUFct_PrepareEnvironment_IntErr (r_fcl_op_status_t opState){
    R_FCL_I_write_memory_u08 (R_FPSYS_REGADD_FAEINT_U8, R_FPSYS_REGVAL_FAEINT_ENABLE);

    g_fcl_data_str.opVar_str.opStatus_enu = opState;
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
void R_FCL_FCUFct_PrepareEnvironment (void){
    r_fcl_status_t ret;
    uint16_t regFENTRYR;

    if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_OP_PREPARE_STATE){
        regFENTRYR = R_FCL_I_read_memory_u16 (R_FPSYS_REGADD_FENTRYR_U16);
        if(R_FPSYS_REGBIT_FENTRY_OFF == regFENTRYR)
        {
            g_fcl_data_str.opVar_str.opResult_enu = R_FCL_BUSY;

            R_FCL_I_write_memory_u08 (R_FPSYS_REGADD_FAEINT_U8, R_FPSYS_REGVAL_FAEINT_DISABLE);

            R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FCURAME_U16, R_FPSYS_REGBIT_FCURAME_FCRME +
                                      R_FPSYS_REGBIT_FCURAME_FRAMTRAN + R_FPSYS_REGBIT_FCURAME_KEY);

            #ifdef R_FCL_INNER_NO_BFA_SWITCH

                R_FCL_FCUFct_GetDeviceInfo ();
            #endif

            R_FCL_FCUFct_Switch_BFlash (0x01u);
            ret = R_FCL_FCUFct_Clear_Cache ();

            #ifdef R_FCL_INNER_NO_BFA_SWITCH
            #else

                R_FCL_FCUFct_GetDeviceInfo ();
            #endif

            if(R_FCL_OK != ret)
            {
                R_FCL_FCUFct_Switch_BFlash (0x00u);
                (void)R_FCL_FCUFct_Clear_Cache ();

                R_FCL_FCUFct_PrepareEnvironment_IntErr (R_FCL_OP_INTERNAL_ERROR_STATE);
            }
            else
            {
                g_fcl_data_str.deviceInfo_str.secureData_u32 = R_FCL_I_read_memory_u32 (R_FPSYS_CONFIG_AREA_SEC_FLAGS);

                #ifdef R_FCL_INNER_NO_FCU_COPY

                    g_fcl_data_str.fcuramAddr_u32 = (R_FPSYS_FCURAM_AREA_BASE + R_FPSYS_FCURAM_AREA_SIZE);
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_PREP_COPY_FW_STATE;

                #else
                    ret = R_FCL_OK;
                    #ifdef R_FCL_INNER_NO_BFA_SWITCH

                        R_FCL_FCUFct_Switch_BFlash (0x00u);
                        ret = R_FCL_FCUFct_Clear_Cache ();

                        if(R_FCL_OK != ret)
                        {
                            R_FCL_FCUFct_PrepareEnvironment_IntErr (R_FCL_OP_INTERNAL_ERROR_STATE);
                        }
                    #endif
                    if(R_FCL_OK == ret)
                    {
                        g_fcl_data_str.fcuramAddr_u32 = R_FPSYS_FCURAM_AREA_BASE;
                        g_fcl_data_str.firmAddr_u32 = R_FPSYS_FCURAM_AREA_RAM_ADD;

                        (void)R_FCL_Fct_Copy_Code (g_fcl_data_str.firmAddr_u32, g_fcl_data_str.fcuramAddr_u32,
                                                   R_FPSYS_FCURAM_AREA_COPY_SIZE);
                        g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_PREP_COPY_FW_STATE;
                    }

                #endif

            }
        }
        else
        {
            g_fcl_data_str.opVar_str.opResult_enu = R_FCL_ERR_REJECTED;
            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_FINISHED_STATE;
        }
    }

    else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_PREP_COPY_FW_STATE){
        #ifdef R_FCL_INNER_NO_FCU_COPY
        #else
            g_fcl_data_str.fcuramAddr_u32 = g_fcl_data_str.fcuramAddr_u32 + R_FPSYS_FCURAM_AREA_COPY_SIZE;
            g_fcl_data_str.firmAddr_u32   = g_fcl_data_str.firmAddr_u32 + R_FPSYS_FCURAM_AREA_COPY_SIZE;
        #endif

        if(g_fcl_data_str.fcuramAddr_u32 >= (R_FPSYS_FCURAM_AREA_BASE + R_FPSYS_FCURAM_AREA_SIZE))
        {
            R_FCL_FCUFct_Switch_BFlash (0x00u);
            ret = R_FCL_FCUFct_Clear_Cache ();

            if(R_FCL_OK != ret)
            {
                R_FCL_FCUFct_PrepareEnvironment_IntErr (R_FCL_OP_INTERNAL_ERROR_STATE);
            }

            else
            {
                R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FCURAME_U16,
                                          R_FPSYS_REGBIT_FCURAME_RESET + R_FPSYS_REGBIT_FCURAME_KEY);

                ret = R_FCL_FCUFct_SwitchMode_Start (R_FCL_CFG_WRITE_MODE);

                if(R_FCL_OK == ret)
                {
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_PREP_RESET_FCU_STATE;
                }
                else
                {
                    R_FCL_I_write_memory_u08 (R_FPSYS_REGADD_FAEINT_U8, R_FPSYS_REGVAL_FAEINT_ENABLE);

                    g_fcl_data_str.opVar_str.opResult_enu = ret;
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_FINISHED_STATE;
                }
            }
        }
        else
        {
            (void)R_FCL_Fct_Copy_Code (g_fcl_data_str.firmAddr_u32, g_fcl_data_str.fcuramAddr_u32,
                                       R_FPSYS_FCURAM_AREA_COPY_SIZE);
        }
    }

    else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_PREP_RESET_FCU_STATE){
        ret = R_FCL_FCUFct_SwitchMode_Check ();
        if(R_FCL_OK == ret)
        {
            ret = R_FCL_FCUFct_ForcedStop ();

            if(R_FCL_OK != ret)
            {
                R_FCL_FCUFct_PrepareEnvironment_IntErr (R_FCL_OP_INTERNAL_ERROR_SWITCH_READ_STATE);
            }
            else
            {
                R_FCL_FCUFct_ClearStatus ();

                (void)R_FCL_FCUFct_SwitchMode_Start (R_FCL_READ_MODE);

                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_PREP_FCURAM_CHKSUM_STATE;
            }

            R_FCL_I_write_memory_u08 (R_FPSYS_REGADD_FAEINT_U8, R_FPSYS_REGVAL_FAEINT_ENABLE);
        }
    }

    else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_PREP_FCURAM_CHKSUM_STATE){
        ret = R_FCL_FCUFct_SwitchMode_Check ();
        if(R_FCL_OK == ret)
        {
            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_PREP_ID_CHECK_FREQ_SET_STATE;

            #ifdef R_FCL_INNER_NO_FCU_COPY
            #else
                ret = R_FCL_FCUFct_VerifyChecksum ();

                if(R_FCL_OK != ret)
                {
                    R_FCL_FCUFct_PrepareEnvironment_IntErr (R_FCL_OP_INTERNAL_ERROR_STATE);
                }
            #endif
        }
    }

    else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_PREP_ID_CHECK_FREQ_SET_STATE){
        ret = R_FCL_FCUFct_VerifyID ();
        if(R_FCL_OK == ret)
        {
            R_FCL_FCUFct_SetFrequency ();
        }
        else
        {
            g_fcl_data_str.opVar_str.opResult_enu = ret;
        }
        g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_FINISHED_STATE;
    }

    else{
        g_fcl_data_str.reqInt_pstr->status_enu = g_fcl_data_str.opVar_str.opResult_enu;
        if(g_fcl_data_str.reqInt_pstr->status_enu == R_FCL_OK)
        {
            g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_PREPARED;
        }
        else
        {
            g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_INIT;
        }
        g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_IDLE_STATE;

        g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu = R_FCL_OP_IDLE_STATE;
        g_fcl_data_str.suspendInfo_str.reqSuspend_pstr = R_FCL_REQUEST_POINTER_UNDEFINED;
        g_fcl_data_str.suspendInfo_str.flagSuspended_enu = R_FCL_FALSE;
        g_fcl_data_str.cancelReq_enu = R_FCL_FALSE;
    }
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC void R_FCL_FCUFct_GetDeviceInfo (void){
    uint32_t data;
    uint32_t dataAddr;

    g_fcl_data_str.deviceInfo_str.accessExtendedUserArea_enu = R_FCL_TRUE;

    g_fcl_data_str.deviceInfo_str.fVersion_u8 = R_FCL_I_read_memory_u08 (R_FPSYS_EXTRA3_AREA_FPVER_U08);

    dataAddr = R_FCL_I_read_memory_u32 (R_FPSYS_EXTRA3_AREA_SCDS_U32);

    data = R_FCL_I_read_memory_u32 (dataAddr + R_FPSYS_EXTRA3_AREA_PRDSEL1);
    g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32 = ((data & 0xffff0000u) >> 16) / 32;
    g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 = (uint8_t)((data & 0x0000ffffu) / 8);

    data = R_FCL_I_read_memory_u32 (dataAddr + R_FPSYS_EXTRA3_AREA_PRDSEL2);
    g_fcl_data_str.deviceInfo_str.cf2BlkCnt32kB_u32 = (data & 0x0000ffffu) / 32;

    data = ((R_FLI_USERBOOT_AREA_END + 1) - R_FLI_USERBOOT_AREA_START);
    g_fcl_data_str.deviceInfo_str.usrBlkCnt32kB_u32 = data / R_FLI_BLOCK_SIZE;

    data = R_FCL_I_read_memory_u32 (dataAddr + R_FPSYS_EXTRA3_AREA_PRDSEL4);

    if((data & 0x000000ffu) == 0x55u){
        g_fcl_data_str.deviceInfo_str.emulationMode_enu = R_FCL_TRUE;
    }
    else{
        g_fcl_data_str.deviceInfo_str.emulationMode_enu = R_FCL_FALSE;
    }

    data = R_FCL_I_read_memory_u32 (dataAddr + R_FPSYS_EXTRA3_AREA_PRDNAME1);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[0]  = (uint8_t)(data & 0x000000ffu);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[1]  = (uint8_t)((data & 0x0000ff00u) >> 8);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[2]  = (uint8_t)((data & 0x00ff0000u) >> 16);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[3]  = (uint8_t)((data & 0xff000000u) >> 24);
    data = R_FCL_I_read_memory_u32 (dataAddr + R_FPSYS_EXTRA3_AREA_PRDNAME2);

    if(g_fcl_data_str.deviceInfo_str.fVersion_u8 != 0xff){
        if(g_fcl_data_str.deviceInfo_str.fVersion_u8 < R_FPSYS_FPVER_04)
        {
            g_fcl_data_str.deviceInfo_str.fDivider_u8 =
                R_FCL_I_read_memory_u08 (R_FPSYS_EXTRA3_AREA_PCLKDIV1_FPVER03_U32);
            g_fcl_data_str.deviceInfo_str.fPClk_u16 =
                (uint16_t)(R_FCL_I_read_memory_u32 (R_FPSYS_EXTRA3_AREA_PCLK_FPVER03_U32) / 1000000uL);

            if(  ((data & 0x00FFFFFFu) == R_FPSYS_PRDNAME_E1x_012x)
               || ((data & 0x00FFFFFFu) == R_FPSYS_PRDNAME_E1x_01Zx) )
            {
                g_fcl_data_str.deviceInfo_str.accessExtendedUserArea_enu = R_FCL_FALSE;
            }
        }
        else
        {
            g_fcl_data_str.deviceInfo_str.fDivider_u8 =
                R_FCL_I_read_memory_u08 (R_FPSYS_EXTRA3_AREA_PCLKDIV1_FPVER04_U32);
            g_fcl_data_str.deviceInfo_str.fPClk_u16 =
                (uint16_t)(R_FCL_I_read_memory_u32 (R_FPSYS_EXTRA3_AREA_PCLK_FPVER04_U32) / 1000000uL);

            if(0u == R_FCL_I_read_memory_u08 (R_FPSYS_EXTRA3_AREA_UB_FPVER04_U08))
            {
                g_fcl_data_str.deviceInfo_str.accessExtendedUserArea_enu = R_FCL_FALSE;
            }
        }

        if(R_PID_CORE_G3KH == R_FCL_I_GetCPUCorePid ())
        {
            g_fcl_data_str.deviceInfo_str.accessExtendedUserArea_enu = R_FCL_TRUE;
        }

        g_fcl_data_str.deviceInfo_str.fMax_u16 =
            (uint16_t)(R_FCL_I_read_memory_u32 (R_FPSYS_EXTRA3_AREA_MAXHCLK_U32) / 1000000uL);
        g_fcl_data_str.deviceInfo_str.fMin_u16 =
            (uint16_t)(R_FCL_I_read_memory_u32 (R_FPSYS_EXTRA3_AREA_MINHCLK_U32) / 1000000uL);
    }

    g_fcl_data_str.deviceInfo_str.deviceName_au08[4]  = (uint8_t)(data & 0x000000ffu);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[5]  = (uint8_t)((data & 0x0000ff00u) >> 8);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[6]  = (uint8_t)((data & 0x00ff0000u) >> 16);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[7]  = (uint8_t)((data & 0xff000000u) >> 24);
    data = R_FCL_I_read_memory_u32 (dataAddr + R_FPSYS_EXTRA3_AREA_PRDNAME3);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[8]  = (uint8_t)(data & 0x000000ffu);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[9]  = (uint8_t)((data & 0x0000ff00u) >> 8);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[10] = (uint8_t)((data & 0x00ff0000u) >> 16);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[11] = (uint8_t)((data & 0xff000000u) >> 24);
    data = R_FCL_I_read_memory_u32 (dataAddr + R_FPSYS_EXTRA3_AREA_PRDNAME4);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[12] = (uint8_t)(data & 0x000000ffu);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[13] = (uint8_t)((data & 0x0000ff00u) >> 8);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[14] = (uint8_t)((data & 0x00ff0000u) >> 16);
    g_fcl_data_str.deviceInfo_str.deviceName_au08[15] = (uint8_t)((data & 0xff000000u) >> 24);

    g_fcl_data_str.deviceInfo_str.blkCnt_u16 = (uint16_t)(g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 +
                                                              g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32 +
                                                              g_fcl_data_str.deviceInfo_str.cf2BlkCnt32kB_u32);

}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_Erase (void){
    uint32_t blockCnt;

    if(R_FCL_FCUFct_CheckMode () == R_FCL_FALSE){
        g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_FLMD0;
    }
    else{
        if(R_FCL_USERBOOT_AREA_SELECT == (g_fcl_data_str.reqInt_pstr->idx_u32 & R_FCL_USERBOOT_AREA_SELECT))
        {
            blockCnt = (g_fcl_data_str.reqInt_pstr->idx_u32 & R_FLI_USERBOOT_AREA_MASK);

            if(  ((blockCnt + g_fcl_data_str.reqInt_pstr->cnt_u16) <=
                    g_fcl_data_str.deviceInfo_str.usrBlkCnt32kB_u32)
               && (g_fcl_data_str.reqInt_pstr->cnt_u16 > 0)
               && (g_fcl_data_str.deviceInfo_str.accessExtendedUserArea_enu != R_FCL_FALSE))
            {
                g_fcl_data_str.opVar_str.opCnt_u16 = g_fcl_data_str.reqInt_pstr->cnt_u16;
                g_fcl_data_str.opVar_str.opAddr_u32 = R_FLI_USERBOOT_AREA_START +
                                                        ((g_fcl_data_str.reqInt_pstr->idx_u32 &
                                                          R_FLI_USERBOOT_AREA_MASK) * R_FLI_BLOCK_SIZE);
                g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_BUSY;
                g_fcl_data_str.opVar_str.opResult_enu = R_FCL_BUSY;
                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_PREPARE_STATE;
            }

            else
            {
                g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
            }
        }

        else
        {
            blockCnt = g_fcl_data_str.reqInt_pstr->idx_u32;

            if(  ((blockCnt + g_fcl_data_str.reqInt_pstr->cnt_u16) <= g_fcl_data_str.deviceInfo_str.blkCnt_u16)
               && (g_fcl_data_str.reqInt_pstr->cnt_u16 > 0))
            {
                g_fcl_data_str.opVar_str.opCnt_u16 = g_fcl_data_str.reqInt_pstr->cnt_u16;

                if(g_fcl_data_str.reqInt_pstr->idx_u32  < g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8)
                {
                    g_fcl_data_str.opVar_str.opAddr_u32 =
                        g_fcl_data_str.reqInt_pstr->idx_u32 * R_FLI_SMALL_BLOCK_SIZE;
                }

                else if( g_fcl_data_str.reqInt_pstr->idx_u32 <
                          (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8  +
                           g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32)
                        )
                {
                    g_fcl_data_str.opVar_str.opAddr_u32 =
                       (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 * R_FLI_SMALL_BLOCK_SIZE) +
                       ((g_fcl_data_str.reqInt_pstr->idx_u32 - g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8)
                        * R_FLI_BLOCK_SIZE);
                }

                else
                {
                    g_fcl_data_str.opVar_str.opAddr_u32 = R_FLI_CFLASH2_START +
                        ((g_fcl_data_str.reqInt_pstr->idx_u32 - g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8
                          - g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32) * R_FLI_BLOCK_SIZE);
                }
                g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_BUSY;
                g_fcl_data_str.opVar_str.opResult_enu = R_FCL_BUSY;
                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_PREPARE_STATE;
            }

            else
            {
                g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
            }
        }
    }
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_Write (void){
    uint32_t startAddr;

    if(R_FCL_FCUFct_CheckMode () == R_FCL_FALSE){
        g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_FLMD0;
    }
    else{
        startAddr = g_fcl_data_str.reqInt_pstr->idx_u32;

        if((((startAddr + (g_fcl_data_str.reqInt_pstr->cnt_u16 * (2 * R_FLI_BLOCK_TRANSFERSIZE))) <=
             ((g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 * R_FLI_SMALL_BLOCK_SIZE) +
              (g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32 * R_FLI_BLOCK_SIZE))) ||
            (((startAddr + (g_fcl_data_str.reqInt_pstr->cnt_u16 * (2 * R_FLI_BLOCK_TRANSFERSIZE))) <=
              (R_FLI_CFLASH2_START + (g_fcl_data_str.deviceInfo_str.cf2BlkCnt32kB_u32 * R_FLI_BLOCK_SIZE))) &&
              (g_fcl_data_str.reqInt_pstr->idx_u32 >= R_FLI_CFLASH2_START))) &&
             ((g_fcl_data_str.reqInt_pstr->idx_u32 % (2 * R_FLI_BLOCK_TRANSFERSIZE)) == 0) &&
              (g_fcl_data_str.reqInt_pstr->cnt_u16 > 0))
        {
            g_fcl_data_str.opVar_str.buffAddr_u32 = g_fcl_data_str.reqInt_pstr->bufferAdd_u32;
            g_fcl_data_str.opVar_str.opCnt_u16    = g_fcl_data_str.reqInt_pstr->cnt_u16;
            g_fcl_data_str.opVar_str.opAddr_u32   = g_fcl_data_str.reqInt_pstr->idx_u32;
            g_fcl_data_str.intStatus_enu          = R_FCL_ISTAT_BUSY;
            g_fcl_data_str.opVar_str.opResult_enu = R_FCL_BUSY;
            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_PREPARE_STATE;
        }

        else if((((startAddr + (g_fcl_data_str.reqInt_pstr->cnt_u16 * (2 * R_FLI_BLOCK_TRANSFERSIZE))) <=
                   (R_FLI_USERBOOT_AREA_START +
                   (g_fcl_data_str.deviceInfo_str.usrBlkCnt32kB_u32 * R_FLI_BLOCK_SIZE))) &&
                  ((g_fcl_data_str.reqInt_pstr->idx_u32 % (2 * R_FLI_BLOCK_TRANSFERSIZE)) == 0)) &&
                   (g_fcl_data_str.reqInt_pstr->cnt_u16 > 0) &&
                   (g_fcl_data_str.reqInt_pstr->idx_u32 >= R_FLI_USERBOOT_AREA_START) &&
                   (g_fcl_data_str.deviceInfo_str.accessExtendedUserArea_enu != R_FCL_FALSE))
        {
            g_fcl_data_str.opVar_str.buffAddr_u32 = g_fcl_data_str.reqInt_pstr->bufferAdd_u32;
            g_fcl_data_str.opVar_str.opCnt_u16    = g_fcl_data_str.reqInt_pstr->cnt_u16;
            g_fcl_data_str.opVar_str.opAddr_u32   = g_fcl_data_str.reqInt_pstr->idx_u32;
            g_fcl_data_str.intStatus_enu          = R_FCL_ISTAT_BUSY;
            g_fcl_data_str.opVar_str.opResult_enu = R_FCL_BUSY;
            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_PREPARE_STATE;
        }

        else
        {
            g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
        }
    }
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
R_FCL_STATIC void R_FCL_FCUFct_HandleMultiOperation_IntErr (r_fcl_op_status_t opState){
    R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FMATSELC_U16,
                              g_fcl_data_str.deviceInfo_str.matSel_u16 + R_FPSYS_REGBIT_FMATSELC_KEY);

    g_fcl_data_str.opVar_str.opStatus_enu = opState;
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
void R_FCL_FCUFct_HandleMultiOperation (void){
    r_fcl_status_t ret;
    r_fcl_status_t res;
    uint32_t       regFSTATR;
    uint16_t       data;
    uint32_t       i;
    uint32_t       readData;
    r_fcl_flag_t   skipCode;
    r_fcl_flag_t   isCmdSpdExec;

    if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_OP_PREPARE_STATE){
        g_fcl_data_str.deviceInfo_str.matSel_u16  = R_FCL_I_read_memory_u16 (R_FPSYS_REGADD_FMATSELC_U16);

        if(R_FCL_FALSE == g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu)
        {
            if((g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_LOCKBIT) ||
                (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_LOCKBIT) ||
                (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_ERASE) ||
                (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_WRITE))
            {
                ret = R_FCL_FCUFct_SwitchMode_Start (R_FCL_WRITE_MODE);
            }

            else
            {
                ret = R_FCL_FCUFct_SwitchMode_Start (R_FCL_CFG_WRITE_MODE);
            }

            if(ret == R_FCL_OK)
            {
                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_CHECK_PE_MODE_SWITCH_STATE;
                g_fcl_data_str.opVar_str.opResult_enu = R_FCL_BUSY;
            }
            else
            {
                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_FINISHED_STATE;
                g_fcl_data_str.opVar_str.opResult_enu = ret;
            }
        }
        else
        {
            g_fcl_data_str.suspendInfo_str.matSel_u16 = g_fcl_data_str.deviceInfo_str.matSel_u16;
            g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu = g_fcl_data_str.opVar_str.opStatus_enu;
            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_FINISHED_STATE;
        }
    }

    else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_BUSY_CHECK_PE_MODE_SWITCH_STATE){
        ret = R_FCL_FCUFct_SwitchMode_Check();
        if(R_FCL_OK == ret)
        {
            if(R_FCL_FALSE == g_fcl_data_str.cancelReq_enu)
            {
                if(R_FCL_FALSE == g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu)
                {
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_START_OP_STATE;
                }
                else
                {
                    g_fcl_data_str.suspendInfo_str.matSel_u16 = g_fcl_data_str.deviceInfo_str.matSel_u16;
                    g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu = R_FCL_OP_PREPARE_STATE;
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;
                }
            }

            else
            {
                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;

                ret = R_FCL_FCUFct_ForcedStop ();

                if(R_FCL_OK != ret)
                {
                    R_FCL_FCUFct_HandleMultiOperation_IntErr (R_FCL_OP_INTERNAL_ERROR_SWITCH_READ_STATE);
                }
            }
        }
    }

    else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_BUSY_START_OP_STATE){
        if(R_FCL_FALSE == g_fcl_data_str.cancelReq_enu)
        {
            if(R_FCL_FALSE == g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu)
            {
                if((g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_LOCKBIT) ||
                    (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_LOCKBIT) ||
                    (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_ERASE) ||
                    (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_WRITE))
                {
                    if(g_fcl_data_str.deviceInfo_str.enableLockBits_enu == R_FCL_TRUE)
                    {
                        R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FPROTR_U16,
                                                  R_FPSYS_REGBIT_FPROTR_ON + R_FPSYS_REGBIT_FPROTR_KEY);
                    }
                    else
                    {
                        R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FPROTR_U16,
                                                  R_FPSYS_REGBIT_FPROTR_OFF + R_FPSYS_REGBIT_FPROTR_KEY);
                    }

                    if(g_fcl_data_str.opVar_str.opAddr_u32 < R_FLI_USERBOOT_AREA_START)
                    {
                        R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FMATSELC_U16,
                                                  R_FPSYS_REGBIT_FMATSELC_USS + R_FPSYS_REGBIT_FMATSELC_KEY);
                    }
                    else
                    {
                        R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FMATSELC_U16,
                                                  R_FPSYS_REGBIT_FMATSELC_EX2S + R_FPSYS_REGBIT_FMATSELC_KEY);
                    }
                }

                R_FCL_I_write_memory_u32 (R_FPSYS_REGADD_FSADR_U32, g_fcl_data_str.opVar_str.opAddr_u32);

                if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_ERASE)
                {
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_ERASE);
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_EXE);
                    g_fcl_data_str.opVar_str.opCnt_u16 -= 1u;
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_CHECK_RESULT_STATE;
                }

                else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_WRITE)
                {
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_WRITE);
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FLI_BLOCK_TRANSFERSIZE);

                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_START_WRITE_OP_STATE;

                    ret = R_FCL_OK;
                    for (i = 0; ( (i < R_FLI_BLOCK_TRANSFERSIZE_PART) && (R_FCL_OK == ret) ); i++)
                    {
                        data = (uint16_t)R_FCL_I_read_memory_u08 (g_fcl_data_str.opVar_str.buffAddr_u32 + 1u);
                        data <<= 8;
                        data += (uint16_t)R_FCL_I_read_memory_u08 (g_fcl_data_str.opVar_str.buffAddr_u32);
                        g_fcl_data_str.opVar_str.buffAddr_u32 += 2u;
                        R_FCL_I_write_memory_u16 (R_FPSYS_FLASH_ACCESS_AREA_BASE, data);

                        ret = R_FCL_FCUFct_Chk_DBFull ();

                        if(R_FCL_OK != ret)
                        {
                            R_FCL_FCUFct_HandleMultiOperation_IntErr (R_FCL_OP_INTERNAL_ERROR_STATE);
                        }
                    }
                }
                else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_LOCKBIT)
                {
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_READ_LOCKBIT);
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_EXE);
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_CHECK_RESULT_STATE;
                }
                else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_LOCKBIT)
                {
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_WRITE_LOCKBIT);
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_EXE);
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_CHECK_RESULT_STATE;
                }

                else
                {
                    if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_OTP)
                    {
                        R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_PRG_CFG_OTP);
                    }
                    else
                    {
                        R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_PRG_CFG);
                    }
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_PRG_CFG_TRANSFERSIZE);

                    for (i = 0; i < R_PRG_CFG_TRANSFERSIZE; i++)
                    {
                        data = (uint16_t)R_FCL_I_read_memory_u08 (g_fcl_data_str.opVar_str.buffAddr_u32 + 1u);
                        data <<= 8;
                        data += (uint16_t)R_FCL_I_read_memory_u08 (g_fcl_data_str.opVar_str.buffAddr_u32);
                        g_fcl_data_str.opVar_str.buffAddr_u32 += 2u;
                        R_FCL_I_write_memory_u16 (R_FPSYS_FLASH_ACCESS_AREA_BASE, data);
                    }
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_EXE);
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_CHECK_RESULT_STATE;
                }
            }
            else
            {
                g_fcl_data_str.suspendInfo_str.matSel_u16 = g_fcl_data_str.deviceInfo_str.matSel_u16;
                g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu = R_FCL_OP_PREPARE_STATE;
                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;
            }
        }

        else
        {
            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;

            ret = R_FCL_FCUFct_ForcedStop();

            if(R_FCL_OK != ret)
            {
                R_FCL_FCUFct_HandleMultiOperation_IntErr (R_FCL_OP_INTERNAL_ERROR_SWITCH_READ_STATE);
            }
        }
    }

    else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_BUSY_START_WRITE_OP_STATE){
        ret = R_FCL_OK;
        for (i = R_FLI_BLOCK_TRANSFERSIZE_PART; ( (i < R_FLI_BLOCK_TRANSFERSIZE) &&
                                                  (R_FCL_OK == ret) ); i++)
        {
            data = (uint16_t)R_FCL_I_read_memory_u08 (g_fcl_data_str.opVar_str.buffAddr_u32 + 1u);
            data <<= 8;
            data += (uint16_t)R_FCL_I_read_memory_u08 (g_fcl_data_str.opVar_str.buffAddr_u32);
            g_fcl_data_str.opVar_str.buffAddr_u32 += 2u;
            R_FCL_I_write_memory_u16 (R_FPSYS_FLASH_ACCESS_AREA_BASE, data);

            ret = R_FCL_FCUFct_Chk_DBFull ();
        }

        if(R_FCL_OK == ret)
        {
            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_CHECK_RESULT_STATE;
            R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_EXE);
        }

        else
        {
            R_FCL_FCUFct_HandleMultiOperation_IntErr (R_FCL_OP_INTERNAL_ERROR_STATE);
        }
    }

    else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_BUSY_CHECK_RESULT_STATE){
        if(R_FCL_FALSE == g_fcl_data_str.cancelReq_enu)
        {
            isCmdSpdExec = R_FCL_FALSE;

            if( (R_FCL_TRUE == g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu) &&
                 (g_fcl_data_str.suspendInfo_str.reqSuspend_pstr == R_FCL_REQUEST_POINTER_UNDEFINED) )
            {
                g_fcl_data_str.suspendInfo_str.matSel_u16 = R_FCL_I_read_memory_u16 (R_FPSYS_REGADD_FMATSELC_U16);
                regFSTATR = R_FCL_I_read_memory_u32 (R_FPSYS_REGADD_FSTATR_U32);

                if(R_FPSYS_REGBIT_FSTATR_SUSRDY == (regFSTATR & R_FPSYS_REGBIT_FSTATR_SUSRDY))
                {
                    R_FCL_I_write_memory_u08 (R_FPSYS_FLASH_ACCESS_AREA_BASE, R_FPSYS_FLASH_ACCESS_CMD_SUSPEND);
                    g_fcl_data_str.suspendInfo_str.reqSuspend_pstr = g_fcl_data_str.reqInt_pstr;
                    isCmdSpdExec = R_FCL_TRUE;
                }
            }

            ret = R_FCL_FCUFct_GetResult (isCmdSpdExec);

            if(ret != R_FCL_BUSY)
            {
                if((g_fcl_data_str.suspendInfo_str.reqSuspend_pstr != R_FCL_REQUEST_POINTER_UNDEFINED) &&
                    (R_FCL_TRUE == g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu))
                {
                    if(ret != R_FCL_OK)
                    {
                        g_fcl_data_str.opVar_str.opResult_enu = ret;
                        g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu = R_FCL_FALSE;
                    }
                    else
                    {
                        g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu = R_FCL_BUSY_CHECK_RESULT_STATE;
                    }
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;
                }

                else
                {
                    g_fcl_data_str.opVar_str.opResult_enu = ret;

                    if(g_fcl_data_str.opVar_str.opResult_enu != R_FCL_OK)
                    {
                        g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;
                    }
                    else
                    {
                        if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_WRITE)
                        {
                            readData = g_fcl_data_str.reqInt_pstr->idx_u32;

                            if((g_fcl_data_str.opVar_str.opAddr_u32 + R_FLI_MIN_WRITESIZE) <
                                (readData + (g_fcl_data_str.reqInt_pstr->cnt_u16 * R_FLI_MIN_WRITESIZE)))
                            {
                                g_fcl_data_str.opVar_str.opAddr_u32 += R_FLI_MIN_WRITESIZE;
                                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_START_OP_STATE;
                                g_fcl_data_str.opVar_str.opResult_enu = R_FCL_BUSY;
                            }

                            else
                            {
                                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;
                            }
                        }

                        else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_ERASE)
                        {
                            if(g_fcl_data_str.opVar_str.opCnt_u16 > 0u)
                            {
                                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_START_OP_STATE;
                                g_fcl_data_str.opVar_str.opResult_enu = R_FCL_BUSY;

                                readData = (g_fcl_data_str.reqInt_pstr->idx_u32 & R_FLI_USERBOOT_AREA_MASK);

                                if((readData +
                                    (g_fcl_data_str.reqInt_pstr->cnt_u16 - g_fcl_data_str.opVar_str.opCnt_u16))
                                     <= g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8)
                                {
                                    g_fcl_data_str.opVar_str.opAddr_u32 += R_FLI_SMALL_BLOCK_SIZE;
                                }

                                else if((readData +
                                     (g_fcl_data_str.reqInt_pstr->cnt_u16 - g_fcl_data_str.opVar_str.opCnt_u16))
                                     == (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 +
                                         g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32))
                                {
                                    g_fcl_data_str.opVar_str.opAddr_u32 = R_FLI_CFLASH2_START;
                                }

                                else
                                {
                                    g_fcl_data_str.opVar_str.opAddr_u32 += R_FLI_BLOCK_SIZE;
                                }
                            }

                            else
                            {
                                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;
                            }
                        }

                        else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_GET_LOCKBIT)
                        {
                            readData = (uint32_t)R_FCL_I_read_memory_u08 (R_FPSYS_REGADD_FLKSTAT_U8);
                            readData = ((~readData) & (uint32_t)0x01u);
                            R_FCL_I_write_unaligned_memory_u32(g_fcl_data_str.reqInt_pstr->bufferAdd_u32, readData);
                            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;
                        }

                        else if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_LOCKBIT)
                        {
                            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;
                        }

                        else if( (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_READ_PROTECT_FLAG) ||
                                  (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_WRITE_PROTECT_FLAG) ||
                                  (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_ERASE_PROTECT_FLAG) ||
                                  (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_SERIAL_PROG_DISABLED) ||
                                  (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_SET_SERIAL_ID_ENABLED) )
                        {
                            g_fcl_data_str.deviceInfo_str.secureData_u32 =
                                    (uint32_t)g_fcl_data_str.intBuf_au08[0] +
                                ( ( (uint32_t)g_fcl_data_str.intBuf_au08[1] ) << 8 ) +
                                ( ( (uint32_t)g_fcl_data_str.intBuf_au08[2] ) << 16 ) +
                                ( ( (uint32_t)g_fcl_data_str.intBuf_au08[3] ) << 24 );

                            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;
                        }

                        else
                        {
                            g_fcl_data_str.opVar_str.opCnt_u16 -= R_PRG_CFG_TRANSFERSIZE;

                            if(g_fcl_data_str.opVar_str.opCnt_u16 > 0u)
                            {
                                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_START_OP_STATE;
                                g_fcl_data_str.opVar_str.opResult_enu = R_FCL_BUSY;
                                g_fcl_data_str.opVar_str.opAddr_u32 += (2u * R_PRG_CFG_TRANSFERSIZE);
                            }

                            else
                            {
                                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;
                            }
                        }
                    }
                }
            }
        }

        else
        {
            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_SWITCH_READ_MODE_STATE;

            ret = R_FCL_FCUFct_ForcedStop ();

            if(R_FCL_OK != ret)
            {
                R_FCL_FCUFct_HandleMultiOperation_IntErr (R_FCL_OP_INTERNAL_ERROR_SWITCH_READ_STATE);
            }
        }

        if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_BUSY_SWITCH_READ_MODE_STATE)
        {
            R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FMATSELC_U16,
                                      g_fcl_data_str.deviceInfo_str.matSel_u16 + R_FPSYS_REGBIT_FMATSELC_KEY);
            R_FCL_FCUFct_ClearStatus ();
        }
    }

    else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_BUSY_SWITCH_READ_MODE_STATE){
        (void)R_FCL_FCUFct_SwitchMode_Start (R_FCL_READ_MODE);
        g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_CHECK_READ_MODE_SWITCH_STATE;
    }

    else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_BUSY_CHECK_READ_MODE_SWITCH_STATE){
        ret = R_FCL_FCUFct_SwitchMode_Check ();
        if(R_FCL_OK == ret)
        {
            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_FINISHED_STATE;
        }
    }

    else{
        if(R_FCL_FALSE == g_fcl_data_str.cancelReq_enu)
        {
            if(R_FCL_FALSE == g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu)
            {
                ret = R_FCL_OK;
                if((g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_ERASE) ||
                    (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_WRITE)  )
                {
                    ret = R_FCL_FCUFct_Clear_Cache ();

                    if(R_FCL_OK != ret)
                    {
                        R_FCL_FCUFct_HandleMultiOperation_IntErr (R_FCL_OP_INTERNAL_ERROR_STATE);
                    }
                }

                if(R_FCL_OK == ret)
                {
                    g_fcl_data_str.reqInt_pstr->status_enu = g_fcl_data_str.opVar_str.opResult_enu;
                    R_FCL_FCUFct_RestoreLastState ();
                    g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_IDLE_STATE;
                }
            }

            else
            {
                R_FCL_I_write_memory_u16 (R_FPSYS_REGADD_FMATSELC_U16,
                                          g_fcl_data_str.deviceInfo_str.matSel_u16 + R_FPSYS_REGBIT_FMATSELC_KEY);

                if((g_fcl_data_str.suspendInfo_str.reqSuspend_pstr == R_FCL_REQUEST_POINTER_UNDEFINED) &&
                    (g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu == R_FCL_OP_IDLE_STATE))
                {
                    g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu = R_FCL_OP_FINISHED_STATE;
                }
                g_fcl_data_str.suspendInfo_str.reqSuspend_pstr            = g_fcl_data_str.reqInt_pstr;
                g_fcl_data_str.suspendInfo_str.opSuspend_str.opAddr_u32   = g_fcl_data_str.opVar_str.opAddr_u32;
                g_fcl_data_str.suspendInfo_str.opSuspend_str.opCnt_u16    = g_fcl_data_str.opVar_str.opCnt_u16;
                g_fcl_data_str.suspendInfo_str.opSuspend_str.opResult_enu = g_fcl_data_str.opVar_str.opResult_enu;

                g_fcl_data_str.intStatus_enu                     = R_FCL_ISTAT_SUSPENDED;
                g_fcl_data_str.reqInt_pstr->status_enu           = R_FCL_SUSPENDED;
                g_fcl_data_str.suspendInfo_str.flagSuspended_enu = R_FCL_TRUE;
                g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu = R_FCL_FALSE;
            }
        }

        else
        {
            skipCode = R_FCL_FALSE;
            ret      = R_FCL_CANCELLED;

            if(R_FCL_REQUEST_POINTER_UNDEFINED != g_fcl_data_str.suspendInfo_str.reqSuspend_pstr)
            {
                if(R_FCL_FALSE != R_FCL_FCUFct_ChkSuspended())
                {
                    res = R_FCL_FCUFct_SwitchMode_Start (R_FCL_WRITE_MODE);
                    if(R_FCL_OK == res)
                    {
                        g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_BUSY_CHECK_PE_MODE_SWITCH_STATE;
                    }
                    else
                    {
                        R_FCL_FCUFct_HandleMultiOperation_IntErr (R_FCL_OP_INTERNAL_ERROR_SWITCH_READ_STATE);
                    }
                    skipCode = R_FCL_TRUE;
                }
            }

            if(R_FCL_FALSE == skipCode)
            {
                res = R_FCL_FCUFct_Clear_Cache ();

                if(R_FCL_OK != res)
                {
                    R_FCL_FCUFct_HandleMultiOperation_IntErr (R_FCL_OP_INTERNAL_ERROR_STATE);
                }
                else
                {
                    g_fcl_data_str.intStatus_enu           = R_FCL_ISTAT_PREPARED;
                    g_fcl_data_str.reqInt_pstr->status_enu = ret;
                    g_fcl_data_str.opVar_str.opStatus_enu  = R_FCL_OP_IDLE_STATE;
                    g_fcl_data_str.cancelReq_enu           = R_FCL_FALSE;
                    if(R_FCL_REQUEST_POINTER_UNDEFINED != g_fcl_data_str.suspendInfo_str.reqSuspend_pstr)
                    {
                        g_fcl_data_str.suspendInfo_str.reqSuspend_pstr->status_enu = ret;
                        g_fcl_data_str.suspendInfo_str.reqSuspend_pstr = R_FCL_REQUEST_POINTER_UNDEFINED;
                        g_fcl_data_str.suspendInfo_str.flagSuspended_enu = R_FCL_FALSE;
                    }
                }
            }
        }
    }

}

#ifdef R_FCL_SUPPORT_OTP

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_GetOTPBit (void){
    uint8_t  readData[16];
    uint8_t  data;
    uint32_t buffAddr;

    buffAddr = g_fcl_data_str.reqInt_pstr->bufferAdd_u32;

    if(R_FCL_USERBOOT_AREA_SELECT == (g_fcl_data_str.reqInt_pstr->idx_u32 & R_FCL_USERBOOT_AREA_SELECT)){
        if(  ((g_fcl_data_str.reqInt_pstr->idx_u32 & R_FLI_USERBOOT_AREA_MASK) <
                g_fcl_data_str.deviceInfo_str.usrBlkCnt32kB_u32)
           && (g_fcl_data_str.deviceInfo_str.accessExtendedUserArea_enu != R_FCL_FALSE) )
        {
            g_fcl_data_str.reqInt_pstr->bufferAdd_u32 = (uint32_t)&readData[0];
            g_fcl_data_str.opVar_str.opAddr_u32 = R_FPSYS_CONFIG_OTP_UB_OFFSET;
            R_FCL_Fct_CallFromRAM ();
            data = (~(readData[0]));
            g_fcl_data_str.reqInt_pstr->bufferAdd_u32 = buffAddr;
            R_FCL_I_write_unaligned_memory_u32 (g_fcl_data_str.reqInt_pstr->bufferAdd_u32, (uint32_t)data);
        }
        else
        {
            g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
        }
    }

    else{
        if(g_fcl_data_str.reqInt_pstr->idx_u32 < g_fcl_data_str.deviceInfo_str.blkCnt_u16 )
        {
            g_fcl_data_str.reqInt_pstr->bufferAdd_u32 = (uint32_t)&readData[0];

            if(g_fcl_data_str.reqInt_pstr->idx_u32 >
               (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 + g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32))
            {
                g_fcl_data_str.opVar_str.opAddr_u32 = R_FPSYS_CONFIG_OTP_CF2_OFFSET +
                    (0x10 * ((g_fcl_data_str.reqInt_pstr->idx_u32 -
                    (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 +
                     g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32)) / 128));
            }
            else
            {
                g_fcl_data_str.opVar_str.opAddr_u32 = R_FPSYS_CONFIG_OTP_CF1_OFFSET +
                    (0x10 * (g_fcl_data_str.reqInt_pstr->idx_u32 / 128));
            }
            R_FCL_Fct_CallFromRAM ();

            if(g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 > 0)
            {
                data = readData[(g_fcl_data_str.reqInt_pstr->idx_u32 / 8) % 16];
                data = (((uint8_t)(~data)) >> (g_fcl_data_str.reqInt_pstr->idx_u32 % 8)) & 0x01u;
            }

            else
            {
                if(g_fcl_data_str.reqInt_pstr->idx_u32 == 0)
                {
                    data = ((uint8_t)(~(readData[0]))) & 0x01u;
                }
                else if(g_fcl_data_str.reqInt_pstr->idx_u32 == 1)
                {
                    data = (((uint8_t)(~(readData[0]))) >> 4) & 0x01u;
                }
                else
                {
                    data = readData[((g_fcl_data_str.reqInt_pstr->idx_u32 + 6) / 8) % 16];

                    data = (((uint8_t)(~data)) >> ((g_fcl_data_str.reqInt_pstr->idx_u32 + 6) % 8)) & 0x01u;
                }
            }
            g_fcl_data_str.reqInt_pstr->bufferAdd_u32 = buffAddr;
            R_FCL_I_write_unaligned_memory_u32 (g_fcl_data_str.reqInt_pstr->bufferAdd_u32, (uint32_t)data);
        }
        else
        {
            g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
        }
    }
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_SetOTPBit (void){
    uint8_t     i;
    uint32_t    blockNo;

    if(g_fcl_data_str.deviceInfo_str.emulationMode_enu == R_FCL_TRUE){
        g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_OK;
    }

    else{
        for (i = 0; i < 16; i++)
        {
            g_fcl_data_str.intBuf_au08[i] = 0xffu;
        }

        g_fcl_data_str.opVar_str.buffAddr_u32 = (uint32_t)(&g_fcl_data_str.intBuf_au08[0]);

        if(R_FCL_USERBOOT_AREA_SELECT == (g_fcl_data_str.reqInt_pstr->idx_u32 & R_FCL_USERBOOT_AREA_SELECT))
        {
            if(  ((g_fcl_data_str.reqInt_pstr->idx_u32 & R_FLI_USERBOOT_AREA_MASK) <
                    g_fcl_data_str.deviceInfo_str.usrBlkCnt32kB_u32)
               && (g_fcl_data_str.deviceInfo_str.accessExtendedUserArea_enu != R_FCL_FALSE) )
            {
                g_fcl_data_str.opVar_str.opAddr_u32 = R_FPSYS_CONFIG_OTP_UB_OFFSET;
                g_fcl_data_str.intBuf_au08[0] = (uint8_t)(~0x01u);
                R_FCL_FCUFct_SetConfigArea ();
            }
            else
            {
                g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
            }
        }

        else
        {
            if(g_fcl_data_str.reqInt_pstr->idx_u32 < g_fcl_data_str.deviceInfo_str.blkCnt_u16)
            {
                blockNo = g_fcl_data_str.reqInt_pstr->idx_u32;

                if(g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 > 0)
                {
                    g_fcl_data_str.intBuf_au08[(blockNo / 8) % 16] = ~(0x01u << (blockNo % 8));
                }
                else
                {
                    if(blockNo  == 0)
                    {
                        g_fcl_data_str.intBuf_au08[0] = (uint8_t)(~0x01u);
                    }
                    else if(blockNo == 1)
                    {
                        g_fcl_data_str.intBuf_au08[0] = (uint8_t)(~0x10u);
                    }
                    else
                    {
                        g_fcl_data_str.intBuf_au08[((blockNo + 6) / 8) % 16] = (~(0x01u << ((blockNo + 6) % 8)));
                    }
                }

                if(g_fcl_data_str.reqInt_pstr->idx_u32 >
                    (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 +
                     g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32))
                {
                    g_fcl_data_str.opVar_str.opAddr_u32 = R_FPSYS_CONFIG_OTP_CF2_OFFSET +
                        (0x10 * ((g_fcl_data_str.reqInt_pstr->idx_u32 -
                        (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 +
                         g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32)) / 128));
                }
                else
                {
                    g_fcl_data_str.opVar_str.opAddr_u32 = R_FPSYS_CONFIG_OTP_CF1_OFFSET +
                        (0x10 * (g_fcl_data_str.reqInt_pstr->idx_u32 / 128));
                }
                R_FCL_FCUFct_SetConfigArea ();
            }
            else
            {
                g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
            }
        }
    }
}

#endif

#ifdef R_FCL_SUPPORT_LOCKBIT

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_HandleLockBit (void){
    if(R_FCL_FCUFct_CheckMode () == R_FCL_FALSE){
        g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_FLMD0;
    }
    else{
        if(R_FCL_USERBOOT_AREA_SELECT == (g_fcl_data_str.reqInt_pstr->idx_u32 & R_FCL_USERBOOT_AREA_SELECT))
        {
            if(  ((g_fcl_data_str.reqInt_pstr->idx_u32 & R_FLI_USERBOOT_AREA_MASK) <
                    g_fcl_data_str.deviceInfo_str.usrBlkCnt32kB_u32)
               && (g_fcl_data_str.deviceInfo_str.accessExtendedUserArea_enu != R_FCL_FALSE) )
            {
                g_fcl_data_str.opVar_str.opAddr_u32 = R_FLI_USERBOOT_AREA_START +
                                                        ((g_fcl_data_str.reqInt_pstr->idx_u32 &
                                                          R_FLI_USERBOOT_AREA_MASK) * R_FLI_BLOCK_SIZE);
                g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_BUSY;
                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_PREPARE_STATE;
            }
            else
            {
                g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
            }
        }

        else
        {
            if(g_fcl_data_str.reqInt_pstr->idx_u32 < g_fcl_data_str.deviceInfo_str.blkCnt_u16 )
            {
                if(g_fcl_data_str.reqInt_pstr->idx_u32 < g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8)
                {
                    g_fcl_data_str.opVar_str.opAddr_u32 =
                        g_fcl_data_str.reqInt_pstr->idx_u32 * R_FLI_SMALL_BLOCK_SIZE;
                }

                else if( g_fcl_data_str.reqInt_pstr->idx_u32 <
                          (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 +
                           g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32))
                {
                    g_fcl_data_str.opVar_str.opAddr_u32 =
                        (g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 * R_FLI_SMALL_BLOCK_SIZE) +
                        ( (g_fcl_data_str.reqInt_pstr->idx_u32 - g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8)
                          * R_FLI_BLOCK_SIZE);
                }
                else
                {
                    g_fcl_data_str.opVar_str.opAddr_u32 = R_FLI_CFLASH2_START +
                       ((g_fcl_data_str.reqInt_pstr->idx_u32 - g_fcl_data_str.deviceInfo_str.cf1BlkCnt8kB_u8 -
                         g_fcl_data_str.deviceInfo_str.cf1BlkCnt32kB_u32) * R_FLI_BLOCK_SIZE);
                }
                g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_BUSY;
                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_PREPARE_STATE;
            }
            else
            {
                g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_PARAMETER;
            }
        }
    }
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_FCUFct_LockBitMode (uint16_t mode_u16){
    if(mode_u16 != R_FPSYS_REGBIT_FPROTR_OFF){
        g_fcl_data_str.deviceInfo_str.enableLockBits_enu = R_FCL_TRUE;
    }
    else{
        g_fcl_data_str.deviceInfo_str.enableLockBits_enu = R_FCL_FALSE;
    }
    g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_OK;
}

#endif

