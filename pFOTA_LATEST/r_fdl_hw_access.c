#define TESTTT 0x1234

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 0292
#endif

#include "r_fdl_global.hpp"

R_FDL_STATIC r_fdl_status_t   R_FDL_IFct_ChkAccessRight (r_fdl_accessType_t accType_enu
   ,                                                        uint32_t granularity_u32);
R_FDL_STATIC void             R_FDL_IFct_ExeCodeInRAM   (r_fdl_pFct_ExeInRAM pFct
   ,                                                        uint32_t *          param_pu32);
R_FDL_STATIC uint32_t         R_FDL_IFct_GetFWParam     (uint32_t addr_u32);
R_FDL_STATIC void             R_FDL_FCUFct_InitRAM_Asm  (uint32_t * param_pu32);
R_FDL_STATIC void             R_FDL_IFct_GetFWParam_Asm (uint32_t * param_pu32);
R_FDL_STATIC uint8_t          R_FDL_IFct_ReadMemoryU08  (uint32_t addr_u32);
R_FDL_STATIC uint16_t         R_FDL_IFct_ReadMemoryU16  (uint32_t addr_u32);
R_FDL_STATIC uint32_t         R_FDL_IFct_ReadMemoryU32  (uint32_t addr_u32);
R_FDL_STATIC void             R_FDL_IFct_WriteMemoryU16 (uint32_t addr_u32, uint16_t val_u16);
R_FDL_STATIC void             R_FDL_IFct_WriteMemoryU32 (uint32_t addr_u32, uint32_t val_u32);

#if R_FDL_COMPILER == R_FDL_COMP_REC
#define asm _asm
#endif

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC uint32_t  R_FDL_IFct_ReadMemoryU32 (uint32_t addr_u32){
#if(defined TA_USE_TEST_CALLBACKS)
        return (test_cb_read_u32 (addr_u32));
#else
        return (*((volatile uint32_t *)(addr_u32)));
#endif
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC uint8_t  R_FDL_IFct_ReadMemoryU08 (uint32_t addr_u32){
#if(defined TA_USE_TEST_CALLBACKS)
        return (test_cb_read_u8 (addr_u32));
#else
        return (*((volatile uint8_t *)(addr_u32)));
#endif
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC uint16_t  R_FDL_IFct_ReadMemoryU16 (uint32_t addr_u32){
#if(defined TA_USE_TEST_CALLBACKS)
        return (test_cb_read_u16 (addr_u32));
#else
        return (*((volatile uint16_t *)(addr_u32)));
#endif
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
void R_FDL_IFct_WriteMemoryU08 (uint32_t addr_u32, uint8_t val_u08){
#if(defined TA_USE_TEST_CALLBACKS)
        test_cb_write_u8 (addr_u32, val_u08);
#else
        (*((volatile uint8_t *)(addr_u32))) = val_u08;
#endif
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC void R_FDL_IFct_WriteMemoryU16 (uint32_t addr_u32, uint16_t val_u16){
#if(defined TA_USE_TEST_CALLBACKS)
        test_cb_write_u16 (addr_u32, val_u16);
#else
        (*((volatile uint16_t *)(addr_u32))) = val_u16;
#endif
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC void R_FDL_IFct_WriteMemoryU32 (uint32_t addr_u32, uint32_t val_u32){
#if(defined TA_USE_TEST_CALLBACKS)
        test_cb_write_u32 (addr_u32, val_u32);
#else
        (*((volatile uint32_t *)(addr_u32))) = val_u32;
#endif
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
void R_FDL_IFct_CalcFOpUnitCnt_BC (uint32_t * cnt_pu32, uint32_t addr_u32){
    uint32_t cntTmp;
    uint32_t addMax;
    uint32_t cntTmpMax;

    cntTmp = (*cnt_pu32);

    addMax = ((addr_u32 / R_FDL_MACROSIZE_MIN) * R_FDL_MACROSIZE_MIN);
    addMax += R_FDL_MACROSIZE_MIN;
    cntTmpMax = (addMax - addr_u32);
    if(cntTmpMax < cntTmp){
        cntTmp = cntTmpMax;
    }

    *cnt_pu32 = cntTmp;

}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_IFct_ChkAccessBoundaries (uint32_t addrStart_u32
   ,                                              uint32_t bCnt_u32
   ,                                              r_fdl_accessType_t accType_enu
   ,                                              uint32_t granularity_u32){
    uint32_t eelPoolStart
   ,            eelPoolSize
   ,            eelPoolEnd
   ,            fdlPoolEnd
   ,            addEnd;
    r_fdl_status_t ret;
    r_fdl_flag_t   inEelRange;

    ret = R_FDL_BUSY;

    eelPoolStart = (g_fdl_str.RTCfg_pstr->eelPoolStart_u16) << R_FDL_BLOCK_SIZE_2N;
    eelPoolSize  = (g_fdl_str.RTCfg_pstr->eelPoolSize_u16) << R_FDL_BLOCK_SIZE_2N;
    fdlPoolEnd   = ((g_fdl_str.RTCfg_pstr->fdlPoolSize_u16) << R_FDL_BLOCK_SIZE_2N) - 1uL;

    inEelRange = R_FDL_FALSE;

    if(0uL == bCnt_u32){
        ret = R_FDL_ERR_PARAMETER;
    }
    else{
        addEnd = (addrStart_u32 + bCnt_u32) - 1uL;
        if((addrStart_u32 > addEnd) ||
            ((addEnd >= g_fdl_str.dfSize_u32) ||

             ((addrStart_u32 & (granularity_u32 - 1uL)) != 0x00000000uL)))
        {
            ret = R_FDL_ERR_PARAMETER;
        }
        else
        {
            if(eelPoolSize > 0u)
            {
                eelPoolEnd   = (eelPoolStart + eelPoolSize) - 1u;
                if((addrStart_u32 >= eelPoolStart) && (addEnd <= eelPoolEnd))
                {
                    inEelRange = R_FDL_TRUE;
                }
                else
                {
                    if(!((addEnd < eelPoolStart) || (addrStart_u32 > eelPoolEnd)))
                    {
                        ret = R_FDL_ERR_PARAMETER;
                    }
                }
            }

            if(R_FDL_ACCESS_EEL == accType_enu)
            {
                if(R_FDL_FALSE == inEelRange)
                {
                    ret = R_FDL_ERR_PARAMETER;
                }
            }

            else if(R_FDL_ACCESS_USER == accType_enu)
            {
                if((addEnd > fdlPoolEnd) || (R_FDL_TRUE == inEelRange))
                {
                    ret = R_FDL_ERR_PARAMETER;
                }
            }
            else
            {
                ret = R_FDL_ERR_PARAMETER;
            }
        }
    }
    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC r_fdl_status_t R_FDL_IFct_ChkAccessRight (r_fdl_accessType_t accType_enu
   ,                                                      uint32_t granularity_u32){
    r_fdl_status_t ret;
    uint32_t       addStart, bCnt;

    addStart = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSADR_U32);
    bCnt     = (R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FEADR_U32) - addStart) + R_FDL_WRITE_SIZE;

#ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if(tstData_str.simError_enu == R_FDL_TRUE)
        {
            if(R_FDL_SIM_ERROR_PROTECTION == tstData_str.simErrorType_enu)
            {
                bCnt = 0;
                tstData_str.simError_enu = R_FDL_FALSE;
            }
        }
        R_FDL_COV_RESTORE
#endif

    ret = R_FDL_IFct_ChkAccessBoundaries (addStart, bCnt, accType_enu, granularity_u32);

    if(R_FDL_ERR_PARAMETER == ret){
        ret = R_FDL_ERR_INTERNAL;
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
void R_FDL_FCUFct_ForcedStop (void){
    uint32_t res;

    R_FDL_IFct_WriteMemoryU08 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_FORCED_STOP);

    do
    {
        res = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
    }
    while(R_FCU_REGBIT_FSTATR_FRDY != (R_FCU_REGBIT_FSTATR_FRDY & res));
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
void R_FDL_FCUFct_ClearStatus (void){
    uint32_t res32;
    uint8_t  res8;

    res32 = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);

    if(R_FCU_REGBIT_FSTATR_ILGERR == (R_FCU_REGBIT_FSTATR_ILGERR & res32)){
        res8 = R_FDL_IFct_ReadMemoryU08 (R_FCU_REGADD_FASTAT_U08);

        if(R_FCU_REGBIT_FASTAT_CMDLK != res8)
        {
            R_FDL_IFct_WriteMemoryU08 (R_FCU_REGADD_FASTAT_U08, R_FCU_REGBIT_FASTAT_CMDLK);
        }
    }

    R_FDL_IFct_WriteMemoryU08 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_CLEARSTAT);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC uint32_t R_FDL_IFct_GetFWParam (uint32_t addr_u32){
    uint32_t getFWParam[2];

    getFWParam[0] = addr_u32;

    R_FDL_IFct_ExeCodeInRAM (&R_FDL_IFct_GetFWParam_Asm, (uint32_t *)(&getFWParam[0]));

    return (getFWParam[1]);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

R_FDL_COV_SAVEOFF

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 1006
#endif

#if R_FDL_COMPILER == R_FDL_COMP_GHS
R_FDL_STATIC void R_FDL_IFct_GetFWParam_Asm (uint32_t * param_pu32){
    asm (" movea 0x01, r0, r8                    ");
    asm (" br _R_FDL_IFct_GetFWParam_Asm_SWBFA   ");

    asm (" _R_FDL_IFct_GetFWParam_Asm_Read:      ");

    asm (" ld.w 0[r6], r7                       ");
    asm (" ld.bu 0[r7], r9                      ");

    asm (" ld.bu 1[r7], r10                     ");
    asm (" shl 8, r10                           ");
    asm (" add r10, r9                          ");

    asm (" ld.bu 2[r7], r10                     ");
    asm (" shl 16, r10                          ");
    asm (" add r10, r9                          ");

    asm (" ld.bu 3[r7], r10                     ");
    asm (" shl 24, r10                          ");
    asm (" add r10, r9                          ");

    asm (" st.w r9, 4[r6]                       ");

    asm (" mov r0, r8                           ");

    asm (" _R_FDL_IFct_GetFWParam_Asm_SWBFA:    ");

    asm (" mov 0xffc59008, r7                   ");
    asm (" st.b r8, 0[r7]                       ");
    asm (" ld.b 0[r7], r7                       ");
    asm (" synci                                ");

    asm (" stsr 24, r7, 4                       ");
    asm (" ori 0x0100, r7, r7                   ");
    asm (" ldsr r7, 24, 4                       ");

    asm ("_R_FDL_IFct_GetFWParam_Asm_Polling:");
    asm (" stsr 24, r7, 4                       ");
    asm ("andi    0x0100, r7, r7");
    asm ("cmp     r0, r7");
    asm ("bne _R_FDL_IFct_GetFWParam_Asm_Polling");
    asm ("synci");

    asm (" stsr 6, r7, 1                        ");
    asm (" andi 0x00E0, r7, r7                  ");

    asm (" movea 0x20, r0, r9                   ");
    asm (" cmp r7, r9                           ");
    asm (" bne _R_FDL_IFct_GetFWParam_Asm_G3M   ");

    asm (" mov 0x01, r7                         ");
    asm (" mov 0xFFBC0700, r9                   ");
    asm (" st.b r0, 0[r9]                       ");
    asm (" st.b r7, 0[r9]                       ");
    asm (" st.b r0, 0[r9]                       ");
    asm (" ld.b 0[r9], r7                       ");
    asm (" synci                                ");
    asm (" br _R_FDL_IFct_GetFWParam_Asm_CCEnd  ");

    asm (" _R_FDL_IFct_GetFWParam_Asm_G3M:      ");
    asm (" stsr 24, r7, 13                      ");
    asm (" ori 0x02, r7, r7                     ");
    asm (" ldsr r7, 24, 13                      ");
    asm (" stsr 24, r7, 13                      ");

    asm (" _R_FDL_IFct_GetFWParam_Asm_CCEnd:    ");

    asm (" cmp r8, r0                           ");
    asm (" bnz _R_FDL_IFct_GetFWParam_Asm_Read  ");
}
#endif

#if R_FDL_COMPILER == R_FDL_COMP_IAR
R_FDL_STATIC void R_FDL_IFct_GetFWParam_Asm (uint32_t * param_pu32){
    __asm("                                         \n"
          " movea 0x01, r0, r8                      \n"
          " br _R_FDL_IFct_GetFWParam_Asm_SWBFA     \n"
          "                                         \n"
          "_R_FDL_IFct_GetFWParam_Asm_Read:         \n"
          "                                         \n"
          " /* Read requested data as one unaligned word */ \n"
          " ld.w 0[r6], r7                          \n"
          " ld.bu 0[r7], r9                         \n"
          " ld.bu 1[r7], r10                        \n"
          " shl 8, r10                              \n"
          " add r10, r9                             \n"
          " ld.bu 2[r7], r10                        \n"
          " shl 16, r10                             \n"
          " add r10, r9                             \n"
          " ld.bu 3[r7], r10                        \n"
          " shl 24, r10                             \n"
          " add r10, r9                             \n"
          " st.w r9, 4[r6]                          \n"
          "                                         \n"
          " /* ----- Switch OFF BFA ----- */        \n"
          " mov r0, r8                              \n"
          "                                         \n"
          " /* Switch BFA and clear the cache */    \n"
          " /* & line buffer (Called twice) */      \n"
          "_R_FDL_IFct_GetFWParam_Asm_SWBFA:        \n"
          "                                         \n"
          " /* Switch EXA3 */                       \n"
          " mov 0xffc59008, r7                      \n"
          " st.b r8, 0[r7]                          \n"
          " ld.b 0[r7], r7                          \n"
          " synci                                   \n"
          "                                         \n"
          " /* Clear the cache */                   \n"
          " stsr 24, r7, 4                          \n"
          " ori 0x0100, r7, r7                      \n"
          " ldsr r7, 24, 4                          \n"
          "                                         \n"
          "_R_FDL_IFct_GetFWParam_Asm_Polling:      \n"
          " stsr 24, r7, 4                          \n"
          " andi    0x0100, r7, r7                  \n"
          " cmp     r0, r7                          \n"
          " bne _R_FDL_IFct_GetFWParam_Asm_Polling  \n"
          " synci                                   \n"
          "                                         \n"
          " /* Check the core */                    \n"
          " stsr 6, r7, 1                           \n"
          " andi 0x00E0, r7, r7                     \n"
          "                                         \n"
          " movea 0x20, r0, r9                      \n"
          " cmp r7, r9                              \n"
          " bne _R_FDL_IFct_GetFWParam_Asm_G3M      \n"
          "                                         \n"
          " /* G3K core: Clear BWC */               \n"
          " mov 0x01, r7                            \n"
          " mov 0xFFBC0700, r9                      \n"
          " st.b r0, 0[r9]                          \n"
          " st.b r7, 0[r9]                          \n"
          " st.b r0, 0[r9]                          \n"
          " ld.b 0[r9], r7                          \n"
          " synci                                   \n"
          " br _R_FDL_IFct_GetFWParam_Asm_CCEnd     \n"
          "                                         \n"
          " /* G3M core: clear sub-cache */         \n"
          "_R_FDL_IFct_GetFWParam_Asm_G3M:          \n"
          " stsr 24, r7, 13                         \n"
          " ori 0x02, r7, r7                        \n"
          " ldsr r7, 24, 13                         \n"
          " stsr 24, r7, 13                         \n"
          "                                         \n"
          "_R_FDL_IFct_GetFWParam_Asm_CCEnd:        \n"
          "                                         \n"
          " /* Check where to continue */           \n"
          " cmp r8, r0                              \n"
          " bnz _R_FDL_IFct_GetFWParam_Asm_Read     \n"
        );

}
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 1006
#endif

#if R_FDL_COMPILER == R_FDL_COMP_REC
#pragma inline_asm R_FDL_IFct_GetFWParam_Asm
R_FDL_STATIC void R_FDL_IFct_GetFWParam_Asm (uint32_t * param_pu32){
    movea 0x01, r0, r8
    br _R_FDL_IFct_GetFWParam_Asm_SWBFA

    _R_FDL_IFct_GetFWParam_Asm_Read:

    ld.w 0[r6], r7
    ld.bu 0[r7], r9
    ld.bu 1[r7], r10
    shl 8, r10
    add r10, r9
    ld.bu 2[r7], r10
    shl 16, r10
    add r10, r9
    ld.bu 3[r7], r10
    shl 24, r10
    add r10, r9
    st.w r9, 4[r6]

    mov r0, r8

    _R_FDL_IFct_GetFWParam_Asm_SWBFA:

    mov 0xffc59008, r7
    st.b r8, 0[r7]
    ld.b 0[r7], r7
    synci

    stsr 24, r7, 4
    ori 0x0100, r7, r7
    ldsr r7, 24, 4

    _R_FDL_IFct_GetFWParam_Asm_Polling:
    stsr 24, r7, 4
    andi    0x0100, r7, r7
    cmp     r0, r7
    bne _R_FDL_IFct_GetFWParam_Asm_Polling
    synci

    stsr 6, r7, 1
    andi 0x00E0, r7, r7

    movea 0x20, r0, r9
    cmp r7, r9
    bne _R_FDL_IFct_GetFWParam_Asm_G3M

    mov 0x01, r7
    mov 0xFFBC0700, r9
    st.b r0, 0[r9]
    st.b r7, 0[r9]
    st.b r0, 0[r9]
    ld.b 0[r9], r7
    synci
    br _R_FDL_IFct_GetFWParam_Asm_CCEnd

    _R_FDL_IFct_GetFWParam_Asm_G3M:
    stsr 24, r7, 13
    ori 0x02, r7, r7
    ldsr r7, 24, 13
    stsr 24, r7, 13

    _R_FDL_IFct_GetFWParam_Asm_CCEnd:

    cmp r8, r0
    bnz _R_FDL_IFct_GetFWParam_Asm_Read
}
#endif

R_FDL_COV_RESTORE

#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
uint32_t R_FDL_FCUFct_GetDFSize (void){
    uint32_t ret
   ,            data
   ,            dataAddr;

    dataAddr = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_SCDSADD);

    data = R_FDL_IFct_ReadMemoryU32 (dataAddr + R_FDL_PRDSEL3_OFFSET);
    data &= 0x0000FFFFuL;
    ret = data * 1024;

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_FCUFct_SetFrequency (void){
    r_fdl_status_t ret;
    uint16_t       fCpu;
    uint16_t       fFaci;
    uint32_t       fwVal;
    uint8_t        fwVer, fDivider;
    uint32_t       fMin, fMax, fPClk;
    uint32_t       dataAddr, data;

    ret  = R_FDL_OK;
    fCpu = g_fdl_str.RTCfg_pstr->cpuFrequencyMHz_u16;

    fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FWVER & (~0x00000003uL));
    fwVer    = (uint8_t)((fwVal >> 8) & 0xFFu);

    if(0xFF != fwVer){
        fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FMIN);
        fMin     = fwVal / 1000000uL;
        fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FMAX);
        fMax     = fwVal / 1000000uL;

        if(fwVer < R_FDL_FCU_FWVER_04)
        {
            fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FDIV_FWVER_03);
            fDivider = (uint8_t)(fwVal & 0xFFu);

            fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FPCLK_FWVER_03);
            fPClk    = fwVal / 1000000uL;

            dataAddr = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_SCDSADD);
            data = R_FDL_IFct_ReadMemoryU32 (dataAddr + R_FDL_PRDNAME2_OFFSET);

            if(R_PRDNAME_010x == (data & 0x00FFFFFFu))
            {
                g_fdl_str.baseAddrECC_u32 = R_DECC_BASE_F1X;
            }
            else
            {
                g_fdl_str.baseAddrECC_u32 = R_DECC_BASE_E1X;
            }
        }
        else
        {
            fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FDIV_FWVER_04);
            fDivider = (uint8_t)(fwVal & 0xFFu);

            fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FPCLK_FWVER_04);
            fPClk    = fwVal / 1000000uL;

            g_fdl_str.baseAddrECC_u32 = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_ECCADDR);
        }

        if((fCpu >= fMin) && (fCpu <= fMax))
        {
            if(0xFF == fDivider)
            {
                fFaci = (uint16_t)fPClk;
            }
            else
            {
                fFaci = (fCpu + fDivider) - 1;
                fFaci = fFaci / fDivider;
            }

            R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_PCKAR_U16, R_FCU_REGBIT_PCKAR_KEY + fFaci);
        }
        else
        {
            ret = R_FDL_ERR_CONFIGURATION;
        }
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_FCUFct_VerifyChecksum (void){
    r_fdl_status_t ret;
    uint32_t       add;
    uint32_t       addEnd;
    uint32_t       chkSum;

    R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FCURAME_U16, R_FCU_REGBIT_FCURAME_FCRME + R_FCU_REGBIT_FCURAME_KEY);

    addEnd = g_fdl_str.chksumEndAddr_u32;
    addEnd <<= 2;
    addEnd += R_FDL_FCU_RAM_ADD;
    chkSum = 0x00000000uL;
    for(add = R_FDL_FCU_RAM_ADD; add < addEnd; add += 2){
        chkSum += (uint32_t)(R_FDL_IFct_ReadMemoryU16 (add));
    }

#ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if((tstData_str.simError_enu == R_FDL_TRUE) &&
            (R_FDL_SIM_ERROR_CHKSUM == tstData_str.simErrorType_enu))
        {
            tstData_str.simError_enu = R_FDL_FALSE;
            g_fdl_str.chksumVal_u32++;
        }
        R_FDL_COV_RESTORE
#endif

    if(chkSum == g_fdl_str.chksumVal_u32){
        ret = R_FDL_BUSY;
    }
    else{
        ret = R_FDL_ERR_INTERNAL;
    }

    R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FCURAME_U16
   ,                              R_FCU_REGBIT_FCURAME_RESET + R_FCU_REGBIT_FCURAME_KEY);

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
void R_FDL_FCUFct_InitRAM (void){
    uint32_t initRamParam[5];

    initRamParam[0] = R_FDL_FCU_RAM_SRC_ADD;
    initRamParam[1] = R_FDL_FCU_RAM_ADD;
    initRamParam[2] = R_FDL_FCU_RAM_SIZE;
    initRamParam[3] = R_FDL_FCU_RAM_ADD_CHKSUM_END;
    initRamParam[4] = R_FDL_FCU_RAM_ADD_CHKSUM;

    R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FCURAME_U16,   R_FCU_REGBIT_FCURAME_FCRME + R_FCU_REGBIT_FCURAME_FRAMTRAN
                               + R_FCU_REGBIT_FCURAME_KEY);

    R_FDL_IFct_ExeCodeInRAM (&R_FDL_FCUFct_InitRAM_Asm, (uint32_t *)(&initRamParam[0]));

    g_fdl_str.chksumEndAddr_u32 = initRamParam[0];
    g_fdl_str.chksumVal_u32     = initRamParam[1];

    R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FCURAME_U16, R_FCU_REGBIT_FCURAME_RESET + R_FCU_REGBIT_FCURAME_KEY);

}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

R_FDL_COV_SAVEOFF

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 1006
#endif

#if R_FDL_COMPILER == R_FDL_COMP_GHS
R_FDL_STATIC void R_FDL_FCUFct_InitRAM_Asm (uint32_t * param_pu32){
    asm (" movea 0x01, r0, r8                   ");
    asm (" br _R_FDL_FCUFct_InitRAM_Asm_SWBFA   ");

    asm (" _R_FDL_FCUFct_InitRAM_Asm_Copy:      ");

    asm (" ld.w 0[r6], r7                       ");
    asm (" ld.w 4[r6], r8                       ");
    asm (" ld.w 8[r6], r9                       ");

    asm (" _R_FDL_FCUFct_InitRAM_Asm_Loop:      ");
    asm (" ld.w 0[r7], r10                      ");
    asm (" st.w r10, 0[r8]                      ");
    asm (" add 4, r7                            ");
    asm (" add 4, r8                            ");
    asm (" add -4, r9                           ");
    asm (" bnz _R_FDL_FCUFct_InitRAM_Asm_Loop   ");

    asm (" ld.w 12[r6], r7                      ");
    asm (" ld.w 0[r7], r10                      ");
    asm (" st.w r10, 0[r6]                      ");
    asm (" ld.w 16[r6], r7                      ");
    asm (" ld.w 0[r7], r10                      ");
    asm (" st.w r10, 4[r6]                      ");

    asm (" mov r0, r8                           ");

    asm (" _R_FDL_FCUFct_InitRAM_Asm_SWBFA:     ");

    asm (" mov 0xffc59008, r7                   ");
    asm (" st.b r8, 0[r7]                       ");
    asm (" ld.b 0[r7], r7                       ");
    asm (" synci                                ");

    asm (" stsr 24, r7, 4                       ");
    asm (" ori 0x0100, r7, r7                   ");
    asm (" ldsr r7, 24, 4                       ");

    asm ("_R_FDL_FCUFct_InitRAM_Polling:        ");
    asm (" stsr 24, r7, 4                       ");
    asm (" andi    0x0100, r7, r7               ");
    asm (" cmp     r0, r7                       ");
    asm (" bne _R_FDL_FCUFct_InitRAM_Polling    ");
    asm (" synci                                ");

    asm (" stsr 6, r7, 1                        ");
    asm (" andi 0x00E0, r7, r7                  ");
    asm (" movea 0x20, r0, r9                   ");
    asm (" cmp r7, r9                           ");
    asm (" bne _R_FDL_FCUFct_InitRAM_Asm_G3M    ");

    asm (" mov 0x01, r7                         ");
    asm (" mov 0xFFBC0700, r9                   ");
    asm (" st.b r0, 0[r9]                       ");
    asm (" st.b r7, 0[r9]                       ");
    asm (" st.b r0, 0[r9]                       ");
    asm (" ld.b 0[r9], r7                       ");
    asm (" synci                                ");
    asm (" br _R_FDL_FCUFct_InitRAM_Asm_CCEnd   ");

    asm (" _R_FDL_FCUFct_InitRAM_Asm_G3M:       ");
    asm (" stsr 24, r7, 13                      ");
    asm (" ori 0x02, r7, r7                     ");
    asm (" ldsr r7, 24, 13                      ");
    asm (" stsr 24, r7, 13                      ");

    asm (" _R_FDL_FCUFct_InitRAM_Asm_CCEnd:     ");

    asm (" cmp r8, r0                           ");
    asm (" bnz _R_FDL_FCUFct_InitRAM_Asm_Copy   ");
}
#endif

#if R_FDL_COMPILER == R_FDL_COMP_IAR
R_FDL_STATIC void R_FDL_FCUFct_InitRAM_Asm (uint32_t * param_pu32)

{
    __asm("                                         \n"
          " /* ----- Switch ON BFA ----- */         \n"
          " movea 0x01, r0, r8                      \n"
          " br _R_FDL_FCUFct_InitRAM_Asm_SWBFA      \n"
          "                                         \n"
          "_R_FDL_FCUFct_InitRAM_Asm_Copy:          \n"
          "                                         \n"
          " /* Copy FW to RAM */                    \n"
          " /* r7: src, r8: dest, r9: cnt, */       \n"
          " /* r10: read buffer */                  \n"
          " ld.w 0[r6], r7                          \n"
          " ld.w 4[r6], r8                          \n"
          " ld.w 8[r6], r9                          \n"
          "                                         \n"
          "_R_FDL_FCUFct_InitRAM_Asm_Loop:          \n"
          " ld.w 0[r7], r10                         \n"
          " st.w r10, 0[r8]                         \n"
          " add 4, r7                               \n"
          " add 4, r8                               \n"
          " add -4, r9                              \n"
          " bnz _R_FDL_FCUFct_InitRAM_Asm_Loop      \n"
          "                                         \n"
          " /* Copy end address and checksum */     \n"
          " ld.w 12[r6], r7                         \n"
          " ld.w 0[r7], r10                         \n"
          " st.w r10, 0[r6]                         \n"
          " ld.w 16[r6], r7                         \n"
          " ld.w 0[r7], r10                         \n"
          " st.w r10, 4[r6]                         \n"
          "                                         \n"
          " /* ----- Switch OFF BFA ----- */        \n"
          " mov r0, r8                              \n"
          "                                         \n"
          " /* Switch BFA and clear the cache */    \n"
          " /* & line buffer (Called twice) */      \n"
          "_R_FDL_FCUFct_InitRAM_Asm_SWBFA:         \n"
          "                                         \n"
          " /* Switch EXA3 */                       \n"
          " mov 0xffc59008, r7                      \n"
          " st.b r8, 0[r7]                          \n"
          " ld.b 0[r7], r7                          \n"
          " synci                                   \n"
          "                                         \n"
          " /* Clear the cache */                   \n"
          " stsr 24, r7, 4                          \n"
          " ori 0x0100, r7, r7                      \n"
          " ldsr r7, 24, 4                          \n"
          "                                         \n"
          "_R_FDL_FCUFct_InitRAM_Polling:           \n"
          " stsr 24, r7, 4                          \n"
          " andi    0x0100, r7, r7                  \n"
          " cmp     r0, r7                          \n"
          " bne _R_FDL_FCUFct_InitRAM_Polling       \n"
          " synci                                   \n"
          "                                         \n"
          " /* Check the core */                    \n"
          " stsr 6, r7, 1                           \n"
          " andi 0x00E0, r7, r7                     \n"
          "                                         \n"
          " movea 0x20, r0, r9                      \n"
          " cmp r7, r9                              \n"
          " bne _R_FDL_FCUFct_InitRAM_Asm_G3M       \n"
          "                                         \n"
          " /* G3K core: Clear BWC */               \n"
          " mov 0x01, r7                            \n"
          " mov 0xFFBC0700, r9                      \n"
          " st.b r0, 0[r9]                          \n"
          " st.b r7, 0[r9]                          \n"
          " st.b r0, 0[r9]                          \n"
          " ld.b 0[r9], r7                          \n"
          " synci                                   \n"
          " br _R_FDL_FCUFct_InitRAM_Asm_CCEnd      \n"
          "                                         \n"
          " /* G3M core: clear sub-cache */         \n"
          "_R_FDL_FCUFct_InitRAM_Asm_G3M:           \n"
          " stsr 24, r7, 13                         \n"
          " ori 0x02, r7, r7                        \n"
          " ldsr r7, 24, 13                         \n"
          " stsr 24, r7, 13                         \n"
          "                                         \n"
          "_R_FDL_FCUFct_InitRAM_Asm_CCEnd:         \n"
          "                                         \n"
          " /* Check where to continue */           \n"
          " cmp r8, r0                              \n"
          " bnz _R_FDL_FCUFct_InitRAM_Asm_Copy      \n"
         );
}
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 1006
#endif

#if R_FDL_COMPILER == R_FDL_COMP_REC
#pragma inline_asm R_FDL_FCUFct_InitRAM_Asm
R_FDL_STATIC void R_FDL_FCUFct_InitRAM_Asm (uint32_t * param_pu32){
    movea 0x01, r0, r8
    br _R_FDL_FCUFct_InitRAM_Asm_SWBFA

    _R_FDL_FCUFct_InitRAM_Asm_Copy:

    ld.w 0[r6], r7
    ld.w 4[r6], r8
    ld.w 8[r6], r9

    _R_FDL_FCUFct_InitRAM_Asm_Loop:
    ld.w 0[r7], r10
    st.w r10, 0[r8]
    add 4, r7
    add 4, r8
    add -4, r9
    bnz _R_FDL_FCUFct_InitRAM_Asm_Loop

    ld.w 12[r6], r7
    ld.w 0[r7], r10
    st.w r10, 0[r6]
    ld.w 16[r6], r7
    ld.w 0[r7], r10
    st.w r10, 4[r6]

    mov r0, r8

    _R_FDL_FCUFct_InitRAM_Asm_SWBFA:

    mov 0xffc59008, r7
    st.b r8, 0[r7]
    ld.b 0[r7], r7
    synci

    stsr 24, r7, 4
    ori 0x0100, r7, r7
    ldsr r7, 24, 4

    _R_FDL_FCUFct_InitRAM_Polling:
    stsr 24, r7, 4
    andi    0x0100, r7, r7
    cmp     r0, r7
    bne _R_FDL_FCUFct_InitRAM_Polling
    synci

    stsr 6, r7, 1
    andi 0x00E0, r7, r7

    movea 0x20, r0, r9
    cmp r7, r9
    bne _R_FDL_FCUFct_InitRAM_Asm_G3M

    mov 0x01, r7
    mov 0xFFBC0700, r9
    st.b r0, 0[r9]
    st.b r7, 0[r9]
    st.b r0, 0[r9]
    ld.b 0[r9], r7
    synci
    br _R_FDL_FCUFct_InitRAM_Asm_CCEnd

    _R_FDL_FCUFct_InitRAM_Asm_G3M:
    stsr 24, r7, 13
    ori 0x02, r7, r7
    ldsr r7, 24, 13
    stsr 24, r7, 13

    _R_FDL_FCUFct_InitRAM_Asm_CCEnd:

    cmp r8, r0
    bnz _R_FDL_FCUFct_InitRAM_Asm_Copy
}
#endif

R_FDL_COV_RESTORE

#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC void R_FDL_IFct_ExeCodeInRAM (r_fdl_pFct_ExeInRAM pFct, uint32_t * param_pu32){
    uint32_t size
   ,            i
   ,            add
   ,            addAl;

    volatile uint16_t * pSrc;
    r_fdl_pFct_ExeInRAM pFctExe;

    volatile uint16_t ramCodeBuffer[105];

    add   = (uint32_t)(&ramCodeBuffer[0]);
    addAl = (((add + 15uL) >> 4) << 4);
    pSrc  = (uint16_t *)((uint32_t)pFct - (addAl - add));
    size  = sizeof (ramCodeBuffer) >> 1;

    for(i = 0; i < size; i++){
        ramCodeBuffer[i] = pSrc[i];
    }

    pFctExe = (r_fdl_pFct_ExeInRAM)(addAl);

    FDL_CRITICAL_SECTION_BEGIN

    pFctExe (param_pu32);

    FDL_CRITICAL_SECTION_END
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_FCUFct_SwitchMode_Start (uint16_t mode_u16){
    volatile uint16_t regFENTRYR;
    uint32_t          regFSTATR;
    uint32_t          cmp;
    r_fdl_status_t    ret;

    ret = R_FDL_OK;

    if(R_FCU_MODE_USER == mode_u16){
        regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
        cmp = R_FCU_REGBIT_FSTATR_ILGERR + R_FCU_REGBIT_FSTATR_ERSERR + R_FCU_REGBIT_FSTATR_PRGERR;
        if(R_FCU_REGBIT_FSTATR_RESET != (regFSTATR & cmp))
        {
            R_FDL_FCUFct_ClearStatus ();
        }
        R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FENTRYR_U16, mode_u16 + R_FCU_REGBIT_FENTRY_KEY);
        g_fdl_str.flashMode_u16 = mode_u16;
    }
    else{
        regFENTRYR =  R_FDL_IFct_ReadMemoryU16 (R_FCU_REGADD_FENTRYR_U16);
        if((regFENTRYR & R_FCU_MODE_CPE) == R_FCU_MODE_CPE)
        {
            ret = R_FDL_ERR_PROTECTION;
        }
        else
        {
            if(mode_u16 != regFENTRYR)
            {
                R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FENTRYR_U16, mode_u16 + R_FCU_REGBIT_FENTRY_KEY);

                R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FSADR_U32, 0x00000000uL);
                R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FEADR_U32, 0x00000000uL);
            }
            g_fdl_str.flashMode_u16 = mode_u16;
        }
    }

#ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if((tstData_str.simError_enu == R_FDL_TRUE) &&
            (R_FDL_SIM_ERROR_SWITCH_PROT == tstData_str.simErrorType_enu))
        {
            if(tstData_str.simErrorCntSet_u32 == tstData_str.simErrorCnt_u32)
            {
                ret = R_FDL_ERR_PROTECTION;
                tstData_str.simError_enu = R_FDL_FALSE;
            }
            tstData_str.simErrorCnt_u32++;
        }
        R_FDL_COV_RESTORE
#endif

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_FCUFct_SwitchMode_Check (void){
    volatile uint16_t regFENTRYR;
    r_fdl_status_t    ret;

    ret = R_FDL_BUSY;

    regFENTRYR =  R_FDL_IFct_ReadMemoryU16 (R_FCU_REGADD_FENTRYR_U16);
    regFENTRYR =  R_FDL_IFct_ReadMemoryU16 (R_FCU_REGADD_FENTRYR_U16);

    if(g_fdl_str.flashMode_u16 == regFENTRYR){
        ret = R_FDL_OK;
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_FCUFct_GetStat (void){
    r_fdl_status_t    stat;
    volatile uint32_t regFSTATR;
    volatile uint8_t  regFBCSTAT;

    regFBCSTAT = R_FDL_IFct_ReadMemoryU08 (R_FCU_REGADD_FBCSTAT_U08);
#ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if((R_FDL_CMD_BLANKCHECK == g_fdl_str.reqInt_pstr->command_enu)
            && (tstData_str.simError_enu == R_FDL_TRUE))
        {
            if(R_FDL_SIM_ERROR_BLANKCHECK == tstData_str.simErrorType_enu)
            {
                stat = R_FDL_ERR_BLANKCHECK;
                tstData_str.simError_enu = R_FDL_FALSE;
            }
        }
        R_FDL_COV_RESTORE
#endif

    if((R_FCU_REGBIT_FBCSTAT_BCST == (regFBCSTAT & R_FCU_REGBIT_FBCSTAT_BCST)) &&
        (R_FDL_CMD_BLANKCHECK == g_fdl_str.reqInt_pstr->command_enu)){
        stat = R_FDL_ERR_BLANKCHECK;
        g_fdl_str.opFailAddr_u32 = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FPSADDR_U32);
    }
    else{
        regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);

#ifdef PATCH_TO_SIMULATE_ERRORS
            R_FDL_COV_SAVEOFF
            if(tstData_str.simError_enu == R_FDL_TRUE)
            {
                if((R_FCU_REGBIT_FSTATR_PRGERR == (regFSTATR & R_FCU_REGBIT_FSTATR_PRGERR))
                    && (R_FDL_SIM_ERROR_SWITCH_PROT_WERR == tstData_str.simErrorType_enu))
                {
                    tstData_str.simErrorType_enu = R_FDL_SIM_ERROR_SWITCH_PROT;
                }

                switch(tstData_str.simErrorType_enu)
                {
                    case R_FDL_SIM_ERROR_ERASE:
                    {
                        regFSTATR |= R_FCU_REGBIT_FSTATR_ERSERR;
                        tstData_str.simError_enu = R_FDL_FALSE;
                        break;
                    }

                    case R_FDL_SIM_ERROR_WRITE:
                    {
                        regFSTATR |= R_FCU_REGBIT_FSTATR_PRGERR;
                        tstData_str.simError_enu = R_FDL_FALSE;
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }

            }
            R_FDL_COV_RESTORE
#endif

        if(R_FCU_REGBIT_FSTATR_PRGERR == (regFSTATR & R_FCU_REGBIT_FSTATR_PRGERR))
        {
            stat = R_FDL_ERR_WRITE;
        }
        else
        {
            if(R_FCU_REGBIT_FSTATR_ERSERR == (regFSTATR & R_FCU_REGBIT_FSTATR_ERSERR))
            {
                stat = R_FDL_ERR_ERASE;
            }
            else
            {
                if(((R_FCU_REGBIT_FSTATR_PRGSPD == (regFSTATR & R_FCU_REGBIT_FSTATR_PRGSPD)) &&
                     (R_FDL_CMD_WRITE == g_fdl_str.reqInt_pstr->command_enu)) ||
                    ((R_FCU_REGBIT_FSTATR_ERSSPD == (regFSTATR & R_FCU_REGBIT_FSTATR_ERSSPD)) &&
                     (R_FDL_CMD_ERASE == g_fdl_str.reqInt_pstr->command_enu)))
                {
                    stat = R_FDL_BUSY;
                }
                else
                {
                    stat = R_FDL_OK;
                }
            }
        }
    }

    return (stat);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_FCUFct_StartWriteOperation (uint32_t addSrc_u32
   ,                                                uint32_t addDest_u32
   ,                                                uint32_t cnt_u32
   ,                                                r_fdl_accessType_t accType_enu){
    volatile uint32_t regFSTATR;
    uint32_t          i;
    r_fdl_status_t    ret;
    uint16_t          data;

    R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FSADR_U32, addDest_u32);

    R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FEADR_U32, addDest_u32 + (cnt_u32 - 1uL));

#ifdef R_FDL_TST_WA_F1L_RESETBLOCKING
    {
        uint32_t loop;
        EEL_ROBUSTNESSTEST_DISABLE_RESET
        for( loop = 0; loop < 10000; loop++ );
    }
#endif

    R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_WRITE);

    cnt_u32 /= R_FDL_FCU_DATA_TRANSFERSIZE;

    R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, (uint16_t)cnt_u32);

    for(i = 0; i < cnt_u32; ++i){
        data = (uint16_t)R_FDL_IFct_ReadMemoryU08 (addSrc_u32 + 1);
        data <<= 8;
        data += (uint16_t)R_FDL_IFct_ReadMemoryU08 (addSrc_u32);

        addSrc_u32 += 2;
        R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, data);

        do
        {
            regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
        }
        while(R_FCU_REGBIT_FSTATR_DBFULL == (regFSTATR & R_FCU_REGBIT_FSTATR_DBFULL));
    }

    ret = R_FDL_IFct_ChkAccessRight (accType_enu, (cnt_u32 * R_FDL_FCU_DATA_TRANSFERSIZE));
    if(R_FDL_BUSY == ret){
        R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_EXE);
    }
    else{
        R_FDL_FCUFct_ForcedStop ();
    }

#ifdef R_FDL_TST_WA_F1L_RESETBLOCKING
    EEL_ROBUSTNESSTEST_ENABLE_RESET
#endif

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_FCUFct_StartBCEraseOperation (uint32_t addStart_u32
   ,                                                  uint32_t addEnd_u32
   ,                                                  uint8_t fcuCmd_u08
   ,                                                  r_fdl_accessType_t accType_enu){
    r_fdl_status_t ret;

    R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FSADR_U32, addStart_u32);
    R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FEADR_U32, addEnd_u32);

    R_FDL_IFct_WriteMemoryU08 (R_FCU_DFLASH_CMD_ADD, fcuCmd_u08);

    ret = R_FDL_IFct_ChkAccessRight (accType_enu, R_FDL_WRITE_SIZE);
    if(R_FDL_BUSY == ret){
        R_FDL_IFct_WriteMemoryU08 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_EXE);
    }
    else{
        R_FDL_FCUFct_ForcedStop ();
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_FCUFct_ReadOperation (volatile uint32_t * pAddSrc_u32
   ,                                          uint32_t addDest_u32
   ,                                          uint32_t cnt_u32){
    r_fdl_status_t ret;
    uint32_t       addEnd;
    uint32_t       add;
    uint32_t       data;
    uint8_t        regDFERINT;
    uint32_t       regDFERSTR;

    ret     = R_FDL_OK;
    add     = (*pAddSrc_u32) + R_FCU_DFLASH_READ_ADD;
    addEnd  = add + (cnt_u32 * R_FDL_WRITE_SIZE);

    R_FDL_IFct_WriteMemoryU08 (R_FCU_REGADD_DFERSTC_U08, R_FCU_REGBIT_DFERSTC_ERRCLR);

    regDFERINT = R_FDL_IFct_ReadMemoryU08 (R_FCU_REGADD_DFERINT_U08);
    R_FDL_IFct_WriteMemoryU08 (R_FCU_REGADD_DFERINT_U08, R_FCU_REGVAL_DFERINT_NOINT);

    do
    {
        data = R_FDL_IFct_ReadMemoryU32 (add);
        R_FDL_IFct_WriteMemoryU32 (addDest_u32, data);

        regDFERSTR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_DFERSTR_U32);
#ifdef PATCH_TO_SIMULATE_ERRORS
            R_FDL_COV_SAVEOFF
            if(tstData_str.simError_enu == R_FDL_TRUE)
            {
                if(R_FDL_SIM_ERROR_BITCHECK == tstData_str.simErrorType_enu)
                {
                    if(2 == tstData_str.simErrorVal_u32)
                    {
                        regDFERSTR |= R_FCU_REGBIT_DFERSTR_DEDF;
                        tstData_str.simError_enu = R_FDL_FALSE;
                    }
                    else
                    {
                        regDFERSTR |= R_FCU_REGBIT_DFERSTR_SEDF;
                        tstData_str.simError_enu = R_FDL_FALSE;
                    }
                }
            }
            R_FDL_COV_RESTORE
#endif

        if(R_FCU_REGVAL_DFERSTR_NOERR != regDFERSTR)
        {
            if(R_FCU_REGBIT_DFERSTR_DEDF == (R_FCU_REGBIT_DFERSTR_DEDF & regDFERSTR))
            {
                (*pAddSrc_u32) = add - R_FCU_DFLASH_READ_ADD;
                ret = R_FDL_ERR_ECC_DED;
            }
            else

            {
                if(R_FDL_OK == ret)
                {
                    (*pAddSrc_u32) = add - R_FCU_DFLASH_READ_ADD;
                    ret = R_FDL_ERR_ECC_SED;
                }
            }

            R_FDL_IFct_WriteMemoryU08 (R_FCU_REGADD_DFERSTC_U08, R_FCU_REGBIT_DFERSTC_ERRCLR);
        }
        add += R_FDL_WRITE_SIZE;
        addDest_u32 += R_FDL_WRITE_SIZE;
    }
    while((add < addEnd) && (R_FDL_ERR_ECC_DED != ret));

    R_FDL_IFct_WriteMemoryU08 (R_FCU_REGADD_DFERINT_U08, regDFERINT);

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_flag_t R_FDL_FCUFct_ChkStartable (r_fdl_command_t cmd_enu){
    volatile uint32_t regFSTATR;
    r_fdl_flag_t      ret;

    ret = R_FDL_TRUE;

    regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);

#if(defined ENABLE_CMD_WRITE16B)
    if((R_FDL_CMD_WRITE == cmd_enu) || (R_FDL_CMD_WRITE16B == cmd_enu))
#else
    if(R_FDL_CMD_WRITE == cmd_enu)
#endif
    {
        if(0x00000000uL != (regFSTATR & R_FCU_REGBIT_FSTATR_PRGSPD))
        {
            ret = R_FDL_FALSE;
        }
    }
    else{
        if(0x00000000uL != (regFSTATR & (R_FCU_REGBIT_FSTATR_ERSSPD + R_FCU_REGBIT_FSTATR_PRGSPD)))
        {
            ret = R_FDL_FALSE;
        }
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_flag_t R_FDL_FCUFct_ChkSuspendable (void){
    volatile uint32_t regFSTATR;
    r_fdl_flag_t      ret;

    regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
    if(R_FCU_REGBIT_FSTATR_SUSRDY == (regFSTATR & R_FCU_REGBIT_FSTATR_SUSRDY)){
        ret = R_FDL_TRUE;
#if(defined ENABLE_CMD_WRITE16B)
            if(R_FDL_CMD_WRITE16B == g_fdl_str.reqInt_pstr->command_enu)
            {
                ret = R_FDL_FALSE;
            }
#endif
    }
    else{
        ret = R_FDL_FALSE;
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
void R_FDL_FCUFct_Suspend (void){
    R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_SUSPEND);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_flag_t R_FDL_FCUFct_ResumeChkNeed (void){
    volatile uint32_t regFSTATR;
    r_fdl_flag_t      ret;

    regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
    if(0x00000000uL == (regFSTATR & (R_FCU_REGBIT_FSTATR_PRGSPD + R_FCU_REGBIT_FSTATR_ERSSPD))){
        ret = R_FDL_FALSE;
    }
    else{
        ret = R_FDL_TRUE;
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
void R_FDL_FCUFct_Resume (void){
    R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_EXE);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_flag_t R_FDL_FCUFct_ChkReady (void){
    r_fdl_flag_t      ret;
    volatile uint32_t regFSTATR;

    regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);

#ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if((tstData_str.simError_enu == R_FDL_TRUE) &&
            (R_FDL_SIM_FCU_TIMEOUT == tstData_str.simErrorType_enu))
        {
            regFSTATR &= (~R_FCU_REGBIT_FSTATR_FRDY);
        }
        R_FDL_COV_RESTORE
#endif

    if(R_FCU_REGBIT_FSTATR_FRDY == (regFSTATR & R_FCU_REGBIT_FSTATR_FRDY)){
        ret = R_FDL_TRUE;

#ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if((tstData_str.simError_enu == R_FDL_TRUE) &&
            (tstData_str.simErrorType_enu == R_FDL_SIM_ERROR_FATALERROR))
        {
            tstData_str.simErrorCnt_u32++;
        }
        R_FDL_COV_RESTORE
#endif
    }
    else{
        ret = R_FDL_FALSE;
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_FCUFct_CheckFatalError (void){
    r_fdl_status_t    ret;
    volatile uint32_t regFSTATR;
    uint32_t          checkVal;

    regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);

#ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if(tstData_str.simError_enu == R_FDL_TRUE)
        {
            if(R_FDL_SIM_ERROR_FATALERROR == tstData_str.simErrorType_enu)
            {
                if((tstData_str.simErrorCntSet_u32 == 0)
                    || ((tstData_str.simErrorCntSet_u32 != 0)
                        && (tstData_str.simErrorCntSet_u32 == tstData_str.simErrorCnt_u32)))
                {
                    while((regFSTATR & R_FCU_REGBIT_FSTATR_FRDY) != R_FCU_REGBIT_FSTATR_FRDY)
                    {
                        regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
                    }
                    regFSTATR |= ((uint16_t)tstData_str.simErrorVal_u32);
                    tstData_str.simError_enu = R_FDL_FALSE;
                }
            }
            else if(R_FDL_SIM_ERROR_FHVE == tstData_str.simErrorType_enu)
            {
                regFSTATR |= ((uint16_t)tstData_str.simErrorVal_u32);
                tstData_str.simError_enu = R_FDL_FALSE;
            }
        }
        R_FDL_COV_RESTORE
#endif

    ret = R_FDL_OK;
    checkVal = ( ( ( ( ( R_FCU_REGBIT_FSTATR_FRDTCT
                       + R_FCU_REGBIT_FSTATR_TBLDTCT )
                       + R_FCU_REGBIT_FSTATR_CFGDTCT )
                       + R_FCU_REGBIT_FSTATR_FCUERR )
                       + R_FCU_REGBIT_FSTATR_ILGERR )
                       + R_FCU_REGBIT_FSTATR_OTPDTCT );

    if((checkVal & regFSTATR) != 0x00000000u){
        ret = R_FDL_ERR_INTERNAL;
    }
    else{
        checkVal = R_FCU_REGBIT_FSTATR_FHVEERR;

        if((checkVal & regFSTATR) != 0x00000000u)
        {
            ret = R_FDL_ERR_PROTECTION;
        }
    }

    return (ret);
}

#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

