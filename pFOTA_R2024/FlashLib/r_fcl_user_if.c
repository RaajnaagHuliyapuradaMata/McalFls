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
#include "r_fcl.hpp"
#include "r_fcl_env.hpp"

#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_INTERNAL
    #define R_FCL_INT_STATIC    R_FCL_STATIC
#else
    #define R_FCL_INT_STATIC
#endif

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs startdata
    #pragma ghs section bss = ".R_FCL_DATA"
#elif R_FCL_COMPILER == FCL_COMP_IAR
    #pragma segment = "R_FCL_DATA"
    #pragma location = "R_FCL_DATA"
    #define R_FCL_NOINIT __no_init
#elif R_FCL_COMPILER == FCL_COMP_REC
    #pragma section r0_disp32 "R_FCL_DATA"
#endif

R_FCL_NOINIT r_fcl_data_t g_fcl_data_str;

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section bss = default
    #pragma ghs enddata
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma dataseg = default
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section default
#endif

#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_INTERNAL
    R_FCL_STATIC void R_FCL_Handler     (void);
    R_FCL_STATIC void R_FCL_Fct_Handler (void);
#endif

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROM"
#endif
r_fcl_status_t R_FCL_CopySections (void){
    uint32_t curSrcAddr;
    uint32_t nextSrcAddr;
    uint32_t destAddr;
    uint32_t curSize;
    uint32_t nextSize;
    r_fcl_status_t ret;

    ret = R_FCL_ERR_FLOW;

    if(g_fcl_data_str.intStatus_enu == R_FCL_ISTAT_INIT){
        if(g_fcl_data_str.RTCfg_pstr->addrRam_u32 != R_FCL_NULL)
        {
            destAddr = g_fcl_data_str.RTCfg_pstr->addrRam_u32;
            curSrcAddr = R_FCL_NULL;
            nextSrcAddr = R_FCL_NULL;
            curSize = 0x00;
            nextSize = 0x00;

            R_FCL_Fct_CodeUsrInt_CalcRange (&curSrcAddr, &curSize);
            R_FCL_Fct_CodeUsr_CalcRange (&nextSrcAddr, &nextSize);
            curSize = nextSrcAddr - curSrcAddr;
            destAddr = R_FCL_Fct_Copy_Code (curSrcAddr, destAddr, curSize);

            curSrcAddr = nextSrcAddr;
            R_FCL_Fct_CodeRam_CalcRange (&nextSrcAddr, &nextSize);
            curSize = nextSrcAddr - curSrcAddr;
            destAddr = R_FCL_Fct_Copy_Code (curSrcAddr, destAddr, curSize);

            curSrcAddr = nextSrcAddr;
            R_FCL_Fct_CodeRomRam_CalcRange (&nextSrcAddr, &nextSize);
            curSize = nextSrcAddr - curSrcAddr;
            destAddr = R_FCL_Fct_Copy_Code (curSrcAddr, destAddr, curSize);

            #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER

                curSrcAddr = nextSrcAddr;
                R_FCL_Fct_CodeExProt_CalcRange (&nextSrcAddr, &nextSize);
                curSize = nextSrcAddr - curSrcAddr;
                destAddr = R_FCL_Fct_Copy_Code (curSrcAddr, destAddr, curSize);
            #endif

            R_FCL_Fct_CodeExProt_CalcRange (&curSrcAddr, &curSize);
            (void)R_FCL_Fct_Copy_Code (curSrcAddr, destAddr, curSize);

            #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_INTERNAL
            g_fcl_data_str.executionPtr_p =
                (r_fcl_fctPtr_t)R_FCL_CalcFctAddr ((uint32_t)(&R_FCL_FCUFct_GetConfigArea));

                g_fcl_data_str.handlerPtr_p = (r_fcl_fctPtr_t)R_FCL_CalcFctAddr ((uint32_t)(&R_FCL_Fct_Handler));
            #endif

            ret = R_FCL_OK;
        }

        else
        {
            ret = R_FCL_ERR_INTERNAL;
        }
    }

    return (ret);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROM"
#endif
uint32_t R_FCL_CalcFctAddr (uint32_t addFct_u32){
    uint32_t secAdd;
    uint32_t secSize;
    uint32_t nextSecAdd;
    uint32_t nextSecSize;
    uint32_t destAdd;
    uint32_t exeOff;

    R_FCL_Fct_CodeUsrInt_CalcRange (&secAdd, &secSize);

    destAdd = g_fcl_data_str.RTCfg_pstr->addrRam_u32;

    if((addFct_u32 >= secAdd) && (addFct_u32 < (secAdd+secSize))){
        destAdd += (addFct_u32 - secAdd);
    }
    else{
        R_FCL_Fct_CodeUsr_CalcRange (&nextSecAdd, &nextSecSize);

        secSize = nextSecAdd - secAdd;
        destAdd += secSize;

        secAdd  = nextSecAdd;
        secSize = nextSecSize;

        if((addFct_u32 >= secAdd) && (addFct_u32 < (secAdd+secSize)))
        {
            destAdd += (addFct_u32 - secAdd);
        }
        else
        {
            R_FCL_Fct_CodeRam_CalcRange (&nextSecAdd, &nextSecSize);

            secSize = nextSecAdd - secAdd;
            destAdd += secSize;

            secAdd  = nextSecAdd;
            secSize = nextSecSize;

            if((addFct_u32 >= secAdd) && (addFct_u32 < (secAdd+secSize)))
            {
                destAdd += (addFct_u32 - secAdd);
            }
            else
            {
                #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
                    R_FCL_Fct_CodeRomRam_CalcRange (&nextSecAdd, &nextSecSize);

                    secSize = nextSecAdd - secAdd;
                    destAdd += secSize;

                    secAdd  = nextSecAdd;
                    secSize = nextSecSize;

                    if((addFct_u32 >= secAdd) && (addFct_u32 < (secAdd + secSize)))
                    {
                        destAdd += (addFct_u32 - secAdd);
                    }
                    else
                #endif
                {
                    destAdd = 0x00000000;
                }
            }
        }
    }

    if(destAdd != 0x00000000){
        exeOff = R_FCL_Fct_PrgOffset ();
        destAdd -= exeOff;
    }

    return (destAdd);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROM"
    #pragma ghs startdata
    #pragma ghs section rodata=".R_FCL_CONST"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROM"
    #pragma section const "R_FCL_CONST"
#endif
const uint8_t *R_FCL_GetVersionString (void){
    #if R_FCL_COMPILER == R_FCL_COMP_IAR
        static const uint8_t fcl_ver_str[] @ "R_FCL_CONST" = R_FCL_VERSION_STRING;
    #else
        static const uint8_t fcl_ver_str[] = R_FCL_VERSION_STRING;
    #endif

    return (&fcl_ver_str[0]);
}

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section rodata = default
    #pragma ghs enddata
#endif

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROM"
#endif
r_fcl_status_t R_FCL_Init (const r_fcl_descriptor_t * descriptor_pstr){
    uint32_t i;
    uint32_t fcl_addr;
    r_fcl_status_t ret;

    fcl_addr = (uint32_t)(&g_fcl_data_str);

    for (i = 0; i < sizeof (g_fcl_data_str); i++){
        R_FCL_I_write_memory_u08 (fcl_addr, 0u);
        fcl_addr++;
    }

    ret = R_FCL_OK;
    g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_NOINIT;

    if(R_FCL_DESCRIPTOR_POINTER_UNDEFINED != descriptor_pstr){
        g_fcl_data_str.reqInt_pstr  = R_FCL_REQUEST_POINTER_UNDEFINED;

        #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_INTERNAL
            g_fcl_data_str.handlerPtr_p = R_FCL_NULL;
        #endif

        g_fcl_data_str.RTCfg_pstr = descriptor_pstr;
        g_fcl_data_str.deviceInfo_str.enableLockBits_enu = R_FCL_TRUE;

        g_fcl_data_str.intStatus_enu = R_FCL_ISTAT_INIT;
    }

    else{
        ret = R_FCL_ERR_PARAMETER;
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
R_FCL_INT_STATIC void R_FCL_Handler (void){
    r_fcl_status_t ret;

    if((R_FCL_REQUEST_POINTER_UNDEFINED != g_fcl_data_str.suspendInfo_str.reqSuspend_pstr) &&
        (R_FCL_ISTAT_SUSPENDED == g_fcl_data_str.intStatus_enu)){
        if(g_fcl_data_str.suspendInfo_str.spdResRequest_enu == R_FCL_TRUE)
        {
            #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
                R_FCL_FCUFct_HandleResume ();
            #endif
        }
    }

    else if((R_FCL_REQUEST_POINTER_UNDEFINED != g_fcl_data_str.reqInt_pstr) &&
             (R_FCL_ISTAT_BUSY == g_fcl_data_str.intStatus_enu)){
        if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_OP_INTERNAL_ERROR_SWITCH_READ_STATE)
        {
            (void)R_FCL_FCUFct_SwitchMode_Start (R_FCL_READ_MODE);
            g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_INTERNAL_ERROR_CHECK_READ_STATE;
        }

        else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_OP_INTERNAL_ERROR_CHECK_READ_STATE)
        {
            ret = R_FCL_FCUFct_SwitchMode_Check ();
            if(R_FCL_OK == ret)
            {
                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_INTERNAL_ERROR_STATE;
            }
        }

        else if(g_fcl_data_str.opVar_str.opStatus_enu == R_FCL_OP_INTERNAL_ERROR_STATE)
        {
            g_fcl_data_str.reqInt_pstr->status_enu = R_FCL_ERR_INTERNAL;
            g_fcl_data_str.opVar_str.opStatus_enu  = R_FCL_OP_IDLE_STATE;
            g_fcl_data_str.intStatus_enu           = R_FCL_ISTAT_NOINIT;
        }

        else
        {
            if(g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_PREPARE_ENV)
            {
                R_FCL_FCUFct_PrepareEnvironment ();
            }
            else
            {
                R_FCL_FCUFct_HandleMultiOperation ();
            }
        }
    }
    else{
    }
}

#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_INTERNAL

    #if R_FCL_COMPILER == R_FCL_COMP_GHS
        #pragma ghs section text = ".R_FCL_CODE_RAM"
    #elif R_FCL_COMPILER == R_FCL_COMP_IAR
        #pragma location = "R_FCL_CODE_RAM"
    #elif R_FCL_COMPILER == R_FCL_COMP_REC
        #pragma section text "R_FCL_CODE_RAM"
    #endif
    R_FCL_STATIC void R_FCL_Fct_Handler (void){
        do
        {
            R_FCL_Handler ();
        }
        while (g_fcl_data_str.reqInt_pstr->status_enu == R_FCL_BUSY);
    }

#endif

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_ROMRAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_ROMRAM"
#endif
void R_FCL_Execute (r_fcl_request_t * request_pstr){
    if(R_FCL_REQUEST_POINTER_UNDEFINED != request_pstr){
        if((g_fcl_data_str.intStatus_enu == R_FCL_ISTAT_INIT) &&
            (request_pstr->command_enu    == R_FCL_CMD_PREPARE_ENV))
        {
            if(R_FCL_FCUFct_CheckMode () == R_FCL_TRUE)
            {
                g_fcl_data_str.reqInt_pstr            = request_pstr;
                g_fcl_data_str.intStatus_enu          = R_FCL_ISTAT_BUSY;
                g_fcl_data_str.opVar_str.opStatus_enu = R_FCL_OP_PREPARE_STATE;
                request_pstr->status_enu              = R_FCL_BUSY;
                #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_INTERNAL

                    while (R_FCL_BUSY == request_pstr->status_enu)
                    {
                        (*g_fcl_data_str.handlerPtr_p)();
                    }
                #endif
            }
            else
            {
                request_pstr->status_enu = R_FCL_ERR_FLMD0;
            }
        }

        else if((g_fcl_data_str.intStatus_enu == R_FCL_ISTAT_PREPARED) ||
                 (g_fcl_data_str.intStatus_enu == R_FCL_ISTAT_SUSPENDED))
        {
            g_fcl_data_str.reqInt_pstr = request_pstr;
            request_pstr->status_enu   = R_FCL_BUSY;

            if(request_pstr->command_enu == R_FCL_CMD_ERASE)
            {
                R_FCL_FCUFct_Erase ();
            }
            else if(request_pstr->command_enu == R_FCL_CMD_WRITE)
            {
                if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                {
                    request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                }
                else
                {
                    R_FCL_FCUFct_Write ();
                }
            }
            #ifdef R_FCL_SUPPORT_LOCKBIT
                else if(request_pstr->command_enu == R_FCL_CMD_GET_LOCKBIT)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_FCUFct_HandleLockBit ();
                    }
                }
                else if(request_pstr->command_enu == R_FCL_CMD_SET_LOCKBIT)
                {
                    R_FCL_FCUFct_HandleLockBit ();
                }
                else if(request_pstr->command_enu == R_FCL_CMD_ENABLE_LOCKBITS)
                {
                    R_FCL_FCUFct_LockBitMode (R_FPSYS_REGBIT_FPROTR_ON);
                }
                else if(request_pstr->command_enu == R_FCL_CMD_DISABLE_LOCKBITS)
                {
                    R_FCL_FCUFct_LockBitMode (R_FPSYS_REGBIT_FPROTR_OFF);
                }
            #endif
            #ifdef R_FCL_SUPPORT_OTP
                else if(request_pstr->command_enu == R_FCL_CMD_GET_OTP)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_FCUFct_GetOTPBit ();
                    }
                }
                else if(request_pstr->command_enu == R_FCL_CMD_SET_OTP)
                {
                    R_FCL_FCUFct_SetOTPBit ();
                }
            #endif
            #ifdef R_FCL_SUPPORT_OPB
                else if(request_pstr->command_enu == R_FCL_CMD_GET_OPB)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_Fct_CallFromRAM ();
                    }
                }
                else if(request_pstr->command_enu == R_FCL_CMD_SET_OPB)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_FCUFct_SetConfigArea ();
                    }
                }
            #endif
            #ifdef R_FCL_SUPPORT_ID
                else if(request_pstr->command_enu == R_FCL_CMD_GET_ID)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_Fct_CallFromRAM ();
                    }
                }
                else if(request_pstr->command_enu == R_FCL_CMD_SET_ID)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_FCUFct_SetConfigArea ();
                    }
                }
            #endif
            #ifdef R_FCL_SUPPORT_RESETVECTOR
                else if(request_pstr->command_enu == R_FCL_CMD_GET_RESET_VECTOR)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_Fct_CallFromRAM ();
                    }
                }
                else if(request_pstr->command_enu == R_FCL_CMD_SET_RESET_VECTOR)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_FCUFct_SetConfigArea ();
                    }
                }
            #endif
            #ifdef R_FCL_SUPPORT_SECURITYFLAGS
                else if((request_pstr->command_enu == R_FCL_CMD_SET_READ_PROTECT_FLAG) ||
                         (request_pstr->command_enu == R_FCL_CMD_SET_WRITE_PROTECT_FLAG) ||
                         (request_pstr->command_enu == R_FCL_CMD_SET_ERASE_PROTECT_FLAG) ||
                         (request_pstr->command_enu == R_FCL_CMD_SET_SERIAL_PROG_DISABLED) ||
                         (request_pstr->command_enu == R_FCL_CMD_SET_SERIAL_ID_ENABLED))
                {
                    R_FCL_FCUFct_SetConfigArea ();
                }
            #endif
            #ifdef R_FCL_SUPPORT_DEVICENAME
                else if(request_pstr->command_enu == R_FCL_CMD_GET_DEVICE_NAME)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_FCUFct_GetDeviceName ();
                    }
                }
            #endif
            #ifdef R_FCL_SUPPORT_BLOCKCNT
                else if(request_pstr->command_enu == R_FCL_CMD_GET_BLOCK_CNT)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_FCUFct_GetBlockCnt ();
                    }
                }
            #endif
            #ifdef R_FCL_SUPPORT_BLOCKENDADDR
                else if(request_pstr->command_enu == R_FCL_CMD_GET_BLOCK_END_ADDR)
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_FCUFct_GetBlockEndAddr ();
                    }
                }
            #endif
            #ifdef R_FCL_SUPPORT_SECURITYFLAGS
                else if((request_pstr->command_enu == R_FCL_CMD_GET_READ_PROTECT_FLAG) ||
                         (request_pstr->command_enu == R_FCL_CMD_GET_WRITE_PROTECT_FLAG) ||
                         (request_pstr->command_enu == R_FCL_CMD_GET_ERASE_PROTECT_FLAG) ||
                         (request_pstr->command_enu == R_FCL_CMD_GET_SERIAL_PROG_DISABLED) ||
                         (request_pstr->command_enu == R_FCL_CMD_GET_SERIAL_ID_ENABLED))
                {
                    if(request_pstr->bufferAdd_u32 == R_FCL_NULL)
                    {
                        request_pstr->status_enu = R_FCL_ERR_PARAMETER;
                    }
                    else
                    {
                        R_FCL_FCUFct_GetSecurityFlag ();
                    }
                }
            #endif
            else if(request_pstr->command_enu == R_FCL_CMD_PREPARE_ENV)
            {
                request_pstr->status_enu = R_FCL_ERR_FLOW;
            }
            else
            {
                request_pstr->status_enu = R_FCL_ERR_COMMAND;
            }
            #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_INTERNAL

                while (R_FCL_BUSY == request_pstr->status_enu)
                {
                    (*g_fcl_data_str.handlerPtr_p)();
                }
            #endif
        }

        else if(g_fcl_data_str.intStatus_enu == R_FCL_ISTAT_BUSY)
        {
            request_pstr->status_enu = R_FCL_ERR_REJECTED;
        }

        else
        {
            request_pstr->status_enu = R_FCL_ERR_FLOW;
        }
    }
}

#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
    r_fcl_status_t R_FCL_SuspendRequest (void){
        r_fcl_status_t ret;

        ret = R_FCL_ERR_FLOW;

        if((R_FCL_ISTAT_BUSY == g_fcl_data_str.intStatus_enu) &&
            (R_FCL_FALSE == g_fcl_data_str.cancelReq_enu) &&
            (R_FCL_FALSE == g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu ))
        {
            if((g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_ERASE) ||
                (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_WRITE))
            {
                g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu = R_FCL_TRUE;
                g_fcl_data_str.suspendInfo_str.spdResRequest_enu = R_FCL_FALSE;
                ret = R_FCL_OK;
            }
            else
            {
                ret = R_FCL_ERR_REJECTED;
            }
        }

        return (ret);
    }

#endif

#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
    r_fcl_status_t R_FCL_ResumeRequest (void){
        r_fcl_status_t ret;

        ret = R_FCL_ERR_FLOW;

        if((g_fcl_data_str.intStatus_enu == R_FCL_ISTAT_SUSPENDED) &&
            (g_fcl_data_str.cancelReq_enu == R_FCL_FALSE) &&
            (g_fcl_data_str.suspendInfo_str.spdResRequest_enu == R_FCL_FALSE))
        {
            if(R_FCL_BUSY_CHECK_RESULT_STATE == g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu)
            {
                if(R_FCL_OK == R_FCL_FCUFct_SwitchMode_Start (R_FCL_WRITE_MODE))
                {
                    g_fcl_data_str.waitAckModeSwitch_enu = R_FCL_TRUE;
                    g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu = R_FCL_FALSE;
                    g_fcl_data_str.suspendInfo_str.spdResRequest_enu = R_FCL_TRUE;
                    ret = R_FCL_OK;
                }
            }
            else
            {
                g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu = R_FCL_FALSE;
                g_fcl_data_str.suspendInfo_str.spdResRequest_enu = R_FCL_TRUE;
                ret = R_FCL_OK;
            }
        }

        return (ret);
    }

#endif

#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    #pragma ghs section text = ".R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    #pragma location = "R_FCL_CODE_RAM"
#elif R_FCL_COMPILER == R_FCL_COMP_REC
    #pragma section text "R_FCL_CODE_RAM"
#endif
    r_fcl_status_t R_FCL_CancelRequest (void){
        r_fcl_status_t ret;

        ret = R_FCL_ERR_FLOW;

        if(((g_fcl_data_str.intStatus_enu == R_FCL_ISTAT_BUSY) ||
             (g_fcl_data_str.intStatus_enu == R_FCL_ISTAT_SUSPENDED)) &&
            (g_fcl_data_str.cancelReq_enu == R_FCL_FALSE))
        {
            if((g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_ERASE) ||
                (g_fcl_data_str.reqInt_pstr->command_enu == R_FCL_CMD_WRITE))
            {
                if(g_fcl_data_str.intStatus_enu == R_FCL_ISTAT_SUSPENDED)
                {
                    if(R_FCL_BUSY_CHECK_RESULT_STATE == g_fcl_data_str.suspendInfo_str.opSuspend_str.opStatus_enu)
                    {
                        if(R_FCL_FALSE == g_fcl_data_str.waitAckModeSwitch_enu)
                        {
                            if(R_FCL_OK == R_FCL_FCUFct_SwitchMode_Start (R_FCL_WRITE_MODE))
                            {
                                g_fcl_data_str.waitAckModeSwitch_enu = R_FCL_TRUE;
                                g_fcl_data_str.suspendInfo_str.spdResRequest_enu = R_FCL_TRUE;
                                g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu = R_FCL_FALSE;
                                g_fcl_data_str.cancelReq_enu = R_FCL_TRUE;
                                ret = R_FCL_OK;
                            }
                        }
                        else
                        {
                            g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu = R_FCL_FALSE;
                            g_fcl_data_str.cancelReq_enu = R_FCL_TRUE;
                            ret = R_FCL_OK;
                        }
                    }

                    else
                    {
                        g_fcl_data_str.suspendInfo_str.spdResRequest_enu = R_FCL_TRUE;
                        g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu = R_FCL_FALSE;
                        g_fcl_data_str.cancelReq_enu = R_FCL_TRUE;
                        ret = R_FCL_OK;
                    }
                }
                else
                {
                    g_fcl_data_str.suspendInfo_str.spdSpdRequest_enu = R_FCL_FALSE;
                    g_fcl_data_str.cancelReq_enu = R_FCL_TRUE;
                    ret = R_FCL_OK;
                }
            }
            else
            {
                ret = R_FCL_ERR_REJECTED;
            }
        }

        return (ret);
    }

#endif

