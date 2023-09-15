#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 0292
#endif

#define R_FDL_USERIF_C

#include "r_fdl_global.hpp"

R_FDL_STATIC void           R_FDL_UFct_EndCurrentOperation             (r_fdl_status_t ret_enu);
R_FDL_STATIC r_fdl_flag_t   R_FDL_UFct_FlashOpStart                    (r_fdl_request_t * request_pstr
   ,                                                                       r_fdl_status_t * tmpStat_penu
   ,                                                                       r_fdl_flag_t isCalledFromExecute_enu);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_BusyAndSuspendPossible       (void);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_ChkResume                    (r_fdl_status_t * tmpStat_penu);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_ReactOnFatalErrors           (r_fdl_status_t * tmpStat_penu);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_StatusCheckAndSuspendOnReady (r_fdl_status_t * tmpStat_penu);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_MultiOperation               (r_fdl_status_t * tmpStat_penu);
R_FDL_STATIC r_fdl_flag_t   R_FDL_UFct_StateNotStandBy                 (void);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_OperationStates              (r_fdl_status_t * tmpStat_penu);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_CancelReq                    (r_fdl_status_t * tmpStat_penu);

#if(!defined R_FDL_COV_ENABLED)
#define R_FDL_START_SEC_VAR
#include "r_fdl_mem_map.hpp"
#endif

R_FDL_NOINIT r_fdl_data_t g_fdl_str;

#if(!defined R_FDL_COV_ENABLED)
#define R_FDL_STOP_SEC_VAR
#include "r_fdl_mem_map.hpp"
#endif

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_InitVariables (const r_fdl_descriptor_t * descriptor_pstr){
    r_fdl_status_t ret;
    uint32_t       fdAdd;
    uint32_t       i;
    uint16_t       blkEnd;

    fdAdd = (uint32_t)(&g_fdl_str);
    for(i = 0; i < sizeof (g_fdl_str); i++){
        R_FDL_IFct_WriteMemoryU08 (fdAdd, 0u);
        fdAdd++;
    }

    g_fdl_str.iStat_enu = R_FDL_ISTAT_NOINIT;
    ret = R_FDL_OK;

    if(R_FDL_DESCRIPTOR_POINTER_UNDEFINED != descriptor_pstr){
        g_fdl_str.RTCfg_pstr = descriptor_pstr;

        (g_fdl_str.reqSuspend_pstr)    = R_FDL_REQUEST_POINTER_UNDEFINED;
        (g_fdl_str.reqInt_pstr)        = R_FDL_REQUEST_POINTER_UNDEFINED;

        g_fdl_str.cancelRequest_enu    = R_FDL_FALSE;
        g_fdl_str.spdSpdRequest_enu    = R_FDL_FALSE;
        g_fdl_str.spdResRequest_enu    = R_FDL_FALSE;
        g_fdl_str.flashMode_u16        = R_FCU_MODE_USER;
        g_fdl_str.opStatus_enu         = R_FDL_OP_IDLE;

        if(0u != g_fdl_str.RTCfg_pstr->fdlPoolSize_u16)
        {
            blkEnd =   (g_fdl_str.RTCfg_pstr->eelPoolStart_u16)
                     + (g_fdl_str.RTCfg_pstr->eelPoolSize_u16);
            if(blkEnd >= (g_fdl_str.RTCfg_pstr->fdlPoolSize_u16 + 1u))
            {
                ret = R_FDL_ERR_CONFIGURATION;
            }
        }
        else
        {
            ret = R_FDL_ERR_CONFIGURATION;
        }
    }
    else{
        ret = R_FDL_ERR_CONFIGURATION;
    }

    if(R_FDL_OK == ret){
        g_fdl_str.iStat_enu = R_FDL_ISTAT_INIT;
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
void  R_FDL_Execute (r_fdl_request_t * request_pstr){
    r_fdl_status_t reqErr;

    reqErr = R_FDL_ERR_REJECTED;

    if(R_FDL_REQUEST_POINTER_UNDEFINED != request_pstr){
        if(R_FDL_REQUEST_POINTER_UNDEFINED == g_fdl_str.reqInt_pstr)
        {
            if(R_FDL_ISTAT_INIT == g_fdl_str.iStat_enu)
            {
                if(R_FDL_CMD_PREPARE_ENV == request_pstr->command_enu)
                {
                    reqErr = R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_PE);
                    if(R_FDL_OK == reqErr)
                    {
                        reqErr = R_FDL_BUSY;
                        g_fdl_str.opStatus_enu = R_FDL_OP_EXECUTE_SYNC_ON;
                    }
                }
            }
            else if((R_FDL_ISTAT_NORMALOP  == g_fdl_str.iStat_enu) ||
                     ((R_FDL_ISTAT_SUSPENDED == g_fdl_str.iStat_enu) &&
                      (R_FDL_FALSE == g_fdl_str.cancelRequest_enu)))
            {
                switch(request_pstr->command_enu)
                {
                    case R_FDL_CMD_BLANKCHECK:
                    {
                        (void)R_FDL_UFct_FlashOpStart (request_pstr, &reqErr, R_FDL_TRUE);
                        break;
                    }

#if(defined ENABLE_CMD_WRITE16B)
                    case R_FDL_CMD_WRITE16B:
#endif
                    case R_FDL_CMD_ERASE:
                    case R_FDL_CMD_WRITE:
                    {
                        if(R_FDL_TRUE == R_FDL_FCUFct_ChkStartable (request_pstr->command_enu))
                        {
                            (void)R_FDL_UFct_FlashOpStart (request_pstr, &reqErr, R_FDL_TRUE);
                        }
                        break;
                    }

                    case R_FDL_CMD_READ:
                    {
                        (void)R_FDL_UFct_FlashOpStart (request_pstr, &reqErr, R_FDL_TRUE);
                        break;
                    }

                    case R_FDL_CMD_PREPARE_ENV:
                    {
                        reqErr = R_FDL_ERR_REJECTED;
                        break;
                    }

                    default:
                    {
                        reqErr = R_FDL_ERR_COMMAND;
                        break;
                    }
                }
            }
            else
            {
            }
        }

        if(R_FDL_BUSY == reqErr)
        {
            g_fdl_str.reqInt_pstr = request_pstr;

        }
        else
        {
            request_pstr->accessType_enu = R_FDL_ACCESS_NONE;

            g_fdl_str.opStatus_enu = R_FDL_OP_IDLE;
        }

        request_pstr->status_enu = reqErr;
    }

    return;
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_CancelReq (r_fdl_status_t * tmpStat_penu){
    r_fdl_flag_t cont;

    cont = R_FDL_TRUE;

    if(R_FDL_TRUE == g_fdl_str.cancelRequest_enu){
        if(R_FDL_OK == R_FDL_FCUFct_SwitchMode_Check ())
        {
            if(R_FCU_MODE_PE == g_fdl_str.flashMode_u16)
            {
                R_FDL_FCUFct_ForcedStop ();
                (void)R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_USER);

                g_fdl_str.opStatus_enu = R_FDL_OP_END_SYNC_OFF;
                g_fdl_str.opResult_enu = R_FDL_CANCELLED;
            }
            else
            {
                (*tmpStat_penu) = R_FDL_CANCELLED;
                cont = R_FDL_FALSE;
            }

            g_fdl_str.cancelRequest_enu = R_FDL_FALSE;
            g_fdl_str.spdSpdRequest_enu = R_FDL_FALSE;
            g_fdl_str.spdResRequest_enu = R_FDL_FALSE;
            g_fdl_str.iStat_enu         = R_FDL_ISTAT_NORMALOP;

            if(R_FDL_REQUEST_POINTER_UNDEFINED != g_fdl_str.reqSuspend_pstr)
            {
                g_fdl_str.reqSuspend_pstr->status_enu = R_FDL_CANCELLED;
                g_fdl_str.reqSuspend_pstr             = R_FDL_REQUEST_POINTER_UNDEFINED;
            }
        }
        else
        {
            cont = R_FDL_FALSE;
        }
    }

    return (cont);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_BusyAndSuspendPossible (void){
    r_fdl_flag_t cont;

    cont = R_FDL_TRUE;

    if(R_FDL_TRUE == g_fdl_str.spdSpdRequest_enu){
        if(R_FDL_TRUE == R_FDL_FCUFct_ChkSuspendable ())
        {
            R_FDL_FCUFct_Suspend ();

            g_fdl_str.spdSpdRequest_enu = R_FDL_FALSE;
            g_fdl_str.iStat_enu         = R_FDL_ISTAT_SUSPEND_PR;
            cont                        = R_FDL_FALSE;
        }
    }

    return (cont);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_ChkResume (r_fdl_status_t * tmpStat_penu){
    r_fdl_flag_t   cont;
    r_fdl_status_t res;

    cont = R_FDL_FALSE;

    if((R_FDL_REQUEST_POINTER_UNDEFINED == g_fdl_str.reqInt_pstr)
        && (R_FDL_TRUE == g_fdl_str.spdResRequest_enu)){
        g_fdl_str.spdResRequest_enu = R_FDL_FALSE;

        if(R_FDL_BUSY == g_fdl_str.spdResStatus_enu)
        {
            res = R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_PE);
            if(R_FDL_OK != res)
            {
                g_fdl_str.reqSuspend_pstr->status_enu = res;
            }
            else
            {
                g_fdl_str.opStatus_enu  = R_FDL_OP_RESUME_SYNC_ON;
                cont                    = R_FDL_TRUE;
                g_fdl_str.iStat_enu     = R_FDL_ISTAT_NORMALOP;
            }
        }
        else
        {
            if((R_FDL_OK == g_fdl_str.spdResStatus_enu)
                && (g_fdl_str.spdMulOp_str.flashAdd_u32 < g_fdl_str.spdMulOp_str.flashAddEnd_u32))
            {
                res = R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_PE);
                if(R_FDL_OK != res)
                {
                    g_fdl_str.reqSuspend_pstr->status_enu = res;
                }
                else
                {
                    g_fdl_str.opStatus_enu            = R_FDL_OP_RESUME_MULTI_SYNC_ON;
                    g_fdl_str.spdResStatus_enu        = R_FDL_BUSY;
                    cont                              = R_FDL_TRUE;
                    g_fdl_str.iStat_enu               = R_FDL_ISTAT_NORMALOP;
                }
            }
            else
            {
                g_fdl_str.iStat_enu = R_FDL_ISTAT_NORMALOP;
                (*tmpStat_penu) = g_fdl_str.spdResStatus_enu;
            }

        }

        if(R_FDL_ISTAT_SUSPENDED != g_fdl_str.iStat_enu)
        {
            g_fdl_str.reqInt_pstr               = g_fdl_str.reqSuspend_pstr;

            g_fdl_str.reqInt_pstr->status_enu   = R_FDL_BUSY;
            g_fdl_str.reqSuspend_pstr           = R_FDL_REQUEST_POINTER_UNDEFINED;
            g_fdl_str.mulOp_str.flashAdd_u32    = g_fdl_str.spdMulOp_str.flashAdd_u32;
            g_fdl_str.mulOp_str.bufAdd_u32      = g_fdl_str.spdMulOp_str.bufAdd_u32;
            g_fdl_str.mulOp_str.flashAddEnd_u32 = g_fdl_str.spdMulOp_str.flashAddEnd_u32;
            g_fdl_str.mulOp_str.accessType_enu  = g_fdl_str.spdMulOp_str.accessType_enu;
        }
    }
    else{
        cont = R_FDL_TRUE;
    }

    return (cont);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_ReactOnFatalErrors (r_fdl_status_t * tmpStat_penu){
    r_fdl_flag_t   cont;
    r_fdl_status_t stat;

    cont = R_FDL_TRUE;

    stat = R_FDL_FCUFct_CheckFatalError ();

    if(R_FDL_OK != stat){
        R_FDL_FCUFct_ClearStatus ();
        (void)R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_USER);

        if(R_FDL_BUSY == R_FDL_FCUFct_SwitchMode_Check ())
        {
            g_fdl_str.opStatus_enu = R_FDL_OP_END_SYNC_OFF;

            g_fdl_str.opResult_enu = stat;
            (*tmpStat_penu)        = R_FDL_BUSY;
        }
        else
        {
            (*tmpStat_penu) = stat;
        }

        cont = R_FDL_FALSE;
    }

    return (cont);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_StatusCheckAndSuspendOnReady (r_fdl_status_t * tmpStat_penu){
    r_fdl_flag_t   cont;
    r_fdl_status_t res;

    cont = R_FDL_TRUE;

    (*tmpStat_penu) = R_FDL_FCUFct_GetStat ();
    R_FDL_FCUFct_ClearStatus ();

    if(R_FDL_TRUE == g_fdl_str.spdSpdRequest_enu){
        g_fdl_str.spdSpdRequest_enu = R_FDL_FALSE;
        g_fdl_str.iStat_enu = R_FDL_ISTAT_SUSPEND_PR;
    }
    if(R_FDL_ISTAT_SUSPEND_PR == g_fdl_str.iStat_enu){
        g_fdl_str.spdResStatus_enu = (*tmpStat_penu);

        (void)R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_USER);
        res = R_FDL_FCUFct_SwitchMode_Check ();

        if(R_FDL_OK == res)
        {
            (*tmpStat_penu) = R_FDL_SUSPENDED;

            g_fdl_str.reqSuspend_pstr = g_fdl_str.reqInt_pstr;

            g_fdl_str.iStat_enu = R_FDL_ISTAT_SUSPENDED;
        }
        else
        {
            (*tmpStat_penu) = R_FDL_BUSY;
            g_fdl_str.opStatus_enu = R_FDL_OP_SUSPEND_SYNC_OFF;
        }

        g_fdl_str.spdMulOp_str.flashAdd_u32    = g_fdl_str.mulOp_str.flashAdd_u32;
        g_fdl_str.spdMulOp_str.bufAdd_u32      = g_fdl_str.mulOp_str.bufAdd_u32;
        g_fdl_str.spdMulOp_str.flashAddEnd_u32 = g_fdl_str.mulOp_str.flashAddEnd_u32;
        g_fdl_str.spdMulOp_str.accessType_enu  = g_fdl_str.mulOp_str.accessType_enu;

        cont = R_FDL_FALSE;
    }

    return (cont);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_MultiOperation (r_fdl_status_t * tmpStat_penu){
    r_fdl_flag_t    cont;
    uint32_t        cnt;
    r_fdl_command_t cmd;

    cont = R_FDL_TRUE;
    cmd  = g_fdl_str.reqInt_pstr->command_enu;

    if((R_FDL_OK == (*tmpStat_penu))
        && (g_fdl_str.mulOp_str.flashAdd_u32 < g_fdl_str.mulOp_str.flashAddEnd_u32)){
#if(defined ENABLE_CMD_WRITE16B)
        if( (R_FDL_CMD_WRITE == cmd) || (R_FDL_CMD_WRITE16B == cmd) )
#else
        if(R_FDL_CMD_WRITE == cmd)
#endif
        {
#if(defined ENABLE_CMD_WRITE16B)
            if(R_FDL_CMD_WRITE == cmd)
            {
                cnt = R_FDL_WRITE_SIZE;
            }
            else
            {
                cnt = R_FDL_WRITE_SIZE_16B;
            }
#else
            cnt = R_FDL_WRITE_SIZE;
#endif

            (*tmpStat_penu) = R_FDL_FCUFct_StartWriteOperation (g_fdl_str.mulOp_str.bufAdd_u32
   ,                                                               g_fdl_str.mulOp_str.flashAdd_u32
   ,                                                               cnt
   ,                                                               g_fdl_str.mulOp_str.accessType_enu);

            g_fdl_str.mulOp_str.flashAdd_u32 += cnt;
            g_fdl_str.mulOp_str.bufAdd_u32   += cnt;
        }
        else if(R_FDL_CMD_ERASE == cmd)
        {
            (*tmpStat_penu) = R_FDL_FCUFct_StartBCEraseOperation (g_fdl_str.mulOp_str.flashAdd_u32
   ,                                                                 (g_fdl_str.mulOp_str.flashAdd_u32 + R_FDL_BLOCK_SIZE) - 1u
   ,                                                                 R_FCU_CMD_ERASE
   ,                                                                 g_fdl_str.mulOp_str.accessType_enu);

            g_fdl_str.mulOp_str.flashAdd_u32 += R_FDL_BLOCK_SIZE;
        }
        else
        {
            cnt = ((g_fdl_str.mulOp_str.flashAddEnd_u32 + 1uL) - g_fdl_str.mulOp_str.flashAdd_u32);

            R_FDL_IFct_CalcFOpUnitCnt_BC (&cnt, g_fdl_str.mulOp_str.flashAdd_u32);

            (*tmpStat_penu) = R_FDL_FCUFct_StartBCEraseOperation (g_fdl_str.mulOp_str.flashAdd_u32
   ,                                                                 ((g_fdl_str.mulOp_str.flashAdd_u32 + cnt) - 1u)
   ,                                                                 R_FCU_CMD_BLANKCHECK
   ,                                                                 g_fdl_str.mulOp_str.accessType_enu);

            g_fdl_str.mulOp_str.flashAdd_u32 += cnt;
        }

        if(R_FDL_BUSY != (*tmpStat_penu))
        {
            (void)R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_USER);
            if(R_FDL_BUSY == R_FDL_FCUFct_SwitchMode_Check ())
            {
                g_fdl_str.opStatus_enu = R_FDL_OP_END_SYNC_OFF;

                g_fdl_str.opResult_enu = (*tmpStat_penu);
                (*tmpStat_penu) = R_FDL_BUSY;
            }
        }

        cont = R_FDL_FALSE;
    }

    return (cont);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_OperationStates (r_fdl_status_t * tmpStat_penu){
    r_fdl_flag_t cont;

    cont = R_FDL_TRUE;

    if((R_FDL_OP_IDLE != g_fdl_str.opStatus_enu) &&
        (R_FDL_OP_BUSY != g_fdl_str.opStatus_enu)){
        (*tmpStat_penu) = R_FDL_FCUFct_SwitchMode_Check ();
        if(R_FDL_OK == (*tmpStat_penu))
        {
            switch(g_fdl_str.opStatus_enu)
            {
                case R_FDL_OP_EXECUTE_SYNC_ON:
                {
                    if(R_FDL_CMD_PREPARE_ENV == g_fdl_str.reqInt_pstr->command_enu)
                    {
                        R_FDL_FCUFct_ForcedStop ();
                        (void)R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_USER);

                        g_fdl_str.opStatus_enu = R_FDL_OP_PREPARE_START;
                        cont                   = R_FDL_FALSE;
                        (*tmpStat_penu)        = R_FDL_BUSY;
                    }
                    else
                    {
                        cont = R_FDL_UFct_FlashOpStart (g_fdl_str.reqInt_pstr, tmpStat_penu, R_FDL_FALSE);
                    }
                    break;
                }

                case R_FDL_OP_PREPARE_START:
                {
                    R_FDL_FCUFct_InitRAM ();

                    (*tmpStat_penu) = R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_PE);
                    if(R_FDL_OK == (*tmpStat_penu))
                    {
                        (*tmpStat_penu)        = R_FDL_BUSY;
                        g_fdl_str.opStatus_enu = R_FDL_OP_PREPARE_RST_FCU;
                    }

                    cont = R_FDL_FALSE;
                    break;
                }

                case R_FDL_OP_PREPARE_RST_FCU:
                {
                    R_FDL_FCUFct_ForcedStop ();
                    R_FDL_FCUFct_ClearStatus ();

                    (void)R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_USER);

                    (*tmpStat_penu)        = R_FDL_BUSY;
                    g_fdl_str.opStatus_enu = R_FDL_OP_PREPARE_END;
                    cont                   = R_FDL_FALSE;
                    break;
                }

                case R_FDL_OP_PREPARE_END:
                {
                    (*tmpStat_penu) = R_FDL_FCUFct_VerifyChecksum ();

                    if(R_FDL_BUSY == (*tmpStat_penu))
                    {
                        g_fdl_str.dfSize_u32 = R_FDL_FCUFct_GetDFSize ();
#ifdef R_FDL_F1L_PATCH_DF_OVERSIZE
                            g_fdl_str.dfSize_u32 *= 2uL;
#endif

                        if(g_fdl_str.RTCfg_pstr->fdlPoolSize_u16 <= (g_fdl_str.dfSize_u32 >> R_FDL_BLOCK_SIZE_2N))
                        {
                            (*tmpStat_penu) = R_FDL_FCUFct_SetFrequency ();
                        }
                        else
                        {
                            (*tmpStat_penu) = R_FDL_ERR_CONFIGURATION;
                        }
                    }

                    if(R_FDL_OK == (*tmpStat_penu))
                    {
                        g_fdl_str.iStat_enu = R_FDL_ISTAT_NORMALOP;
                    }

                    cont = R_FDL_FALSE;
                    break;
                }

                case R_FDL_OP_RESUME_SYNC_ON:
                {
                    R_FDL_FCUFct_Resume ();
                    g_fdl_str.opStatus_enu = R_FDL_OP_BUSY;
                    (*tmpStat_penu)        = R_FDL_BUSY;
                    break;
                }

                case R_FDL_OP_RESUME_MULTI_SYNC_ON:
                {
                    g_fdl_str.opStatus_enu = R_FDL_OP_BUSY;
                    (*tmpStat_penu)        = R_FDL_BUSY;
                    break;
                }

                case R_FDL_OP_END_SYNC_OFF:
                {
                    g_fdl_str.opStatus_enu = R_FDL_OP_IDLE;
                    (*tmpStat_penu)        = g_fdl_str.opResult_enu;
                    cont                   = R_FDL_FALSE;
                    break;
                }

                case R_FDL_OP_SUSPEND_SYNC_OFF:
                {
                    (*tmpStat_penu)                        = R_FDL_SUSPENDED;

                    g_fdl_str.reqSuspend_pstr              = g_fdl_str.reqInt_pstr;
                    g_fdl_str.iStat_enu                    = R_FDL_ISTAT_SUSPENDED;
                    cont                                   = R_FDL_FALSE;
                    break;
                }

                default:
                {
                    break;
                }
            }
        }
        else
        {
            cont = R_FDL_FALSE;
        }
    }
    return (cont);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
void R_FDL_Handler (void){
    r_fdl_flag_t   contHdrFct;
    r_fdl_status_t tmpStatus;
    r_fdl_status_t res;

    tmpStatus = R_FDL_BUSY;

    if((R_FDL_TRUE == R_FDL_UFct_StateNotStandBy ()) &&
        ((R_FDL_REQUEST_POINTER_UNDEFINED != g_fdl_str.reqInt_pstr) ||
         (R_FDL_TRUE == g_fdl_str.spdResRequest_enu) ||
         (R_FDL_TRUE == g_fdl_str.cancelRequest_enu))){
        contHdrFct = R_FDL_Handler_CancelReq (&tmpStatus);

        if(R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_Handler_BusyAndSuspendPossible ();
        }

        if(R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_Handler_ChkResume (&tmpStatus);
        }

        if(R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_Handler_OperationStates (&tmpStatus);
        }

        if(R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_FCUFct_ChkReady ();
        }

        if(R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_Handler_ReactOnFatalErrors (&tmpStatus);
        }

        if(R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_Handler_StatusCheckAndSuspendOnReady (&tmpStatus);
        }

        if(R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_Handler_MultiOperation (&tmpStatus);
        }

        if(R_FDL_TRUE == contHdrFct)
        {
            (void)R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_USER);
            res = R_FDL_FCUFct_SwitchMode_Check ();
            if(R_FDL_BUSY == res)
            {
                g_fdl_str.opStatus_enu = R_FDL_OP_END_SYNC_OFF;

                g_fdl_str.opResult_enu = tmpStatus;
                tmpStatus = R_FDL_BUSY;
            }
        }

        if(R_FDL_BUSY != tmpStatus)
        {
            R_FDL_UFct_EndCurrentOperation (tmpStatus);
        }

#ifdef PATCH_TO_SIMULATE_ERRORS
            tstData_str.simCntHdr_u32++;
#endif

    }
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
const uint8_t *R_FDL_GetVersionString (void){
    static const uint8_t r_fdl_vStr[] = R_FDL_VERSION_STRING;

    return (&r_fdl_vStr[0]);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_SuspendRequest (void){
    r_fdl_status_t ret;

    ret = R_FDL_ERR_REJECTED;

    if(R_FDL_TRUE == R_FDL_UFct_StateNotStandBy ()){
        if((R_FDL_REQUEST_POINTER_UNDEFINED != g_fdl_str.reqInt_pstr)
            && (R_FDL_REQUEST_POINTER_UNDEFINED == g_fdl_str.reqSuspend_pstr)
            && (R_FDL_ISTAT_NORMALOP == g_fdl_str.iStat_enu)
            && (R_FDL_FALSE == g_fdl_str.cancelRequest_enu))
        {
            ret = R_FDL_OK;
            g_fdl_str.spdSpdRequest_enu = R_FDL_TRUE;
        }
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_ResumeRequest (void){
    r_fdl_status_t ret;

    ret = R_FDL_OK;

    if(R_FDL_TRUE == R_FDL_UFct_StateNotStandBy ()){
        if((R_FDL_ISTAT_SUSPENDED == g_fdl_str.iStat_enu)
            && (R_FDL_FALSE == g_fdl_str.cancelRequest_enu))
        {
            g_fdl_str.spdResRequest_enu = R_FDL_TRUE;
        }
        else
        {
            ret = R_FDL_ERR_REJECTED;
        }
    }
    else{
        ret = R_FDL_ERR_REJECTED;
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_StandBy (void){
    r_fdl_status_t ret;

    if(((R_FDL_TRUE == R_FDL_UFct_StateNotStandBy ()) &&
         (R_FDL_ISTAT_INIT != g_fdl_str.iStat_enu))
        || (R_FDL_ISTAT_STANDBY_PR == g_fdl_str.iStat_enu)){
        if(R_FDL_ISTAT_STANDBY_PR != g_fdl_str.iStat_enu)
        {
            g_fdl_str.stByIStatBackUp_enu = g_fdl_str.iStat_enu;

            g_fdl_str.iStat_enu = R_FDL_ISTAT_STANDBY_PR;
        }

        if(R_FDL_FALSE == R_FDL_FCUFct_ChkReady ())
        {
            ret = R_FDL_BUSY;

            if(R_FDL_TRUE == R_FDL_FCUFct_ChkSuspendable ())
            {
                R_FDL_FCUFct_Suspend ();
            }
        }
        else
        {
            g_fdl_str.iStat_enu = R_FDL_ISTAT_STANDBY;
            ret = R_FDL_OK;
        }
    }
    else{
        ret = R_FDL_ERR_REJECTED;
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_WakeUp (void){
    r_fdl_status_t ret;

    if(R_FDL_ISTAT_STANDBY == g_fdl_str.iStat_enu){
        ret = R_FDL_OK;

        g_fdl_str.iStat_enu = g_fdl_str.stByIStatBackUp_enu;

        if(R_FDL_TRUE == R_FDL_FCUFct_ResumeChkNeed ())
        {
            R_FDL_FCUFct_Resume ();
        }
    }
    else{
        ret = R_FDL_ERR_REJECTED;
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
r_fdl_status_t R_FDL_CancelRequest (void){
    r_fdl_status_t ret;

    ret = R_FDL_OK;

    if((R_FDL_TRUE ==  R_FDL_UFct_StateNotStandBy ()) &&
        (R_FDL_ISTAT_INIT != g_fdl_str.iStat_enu)      &&
        (R_FDL_FALSE == g_fdl_str.cancelRequest_enu)){
        if((R_FDL_ISTAT_SUSPENDED == g_fdl_str.iStat_enu) &&
            (R_FDL_REQUEST_POINTER_UNDEFINED == g_fdl_str.reqInt_pstr))
        {
            ret = R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_PE);
        }
        else if((R_FDL_ISTAT_NORMALOP == g_fdl_str.iStat_enu) &&
                 (R_FDL_REQUEST_POINTER_UNDEFINED == g_fdl_str.reqInt_pstr))
        {
            ret = R_FDL_ERR_REJECTED;
        }
        else
        {
        }

        if(R_FDL_OK == ret)
        {
            g_fdl_str.cancelRequest_enu = R_FDL_TRUE;
        }
    }
    else{
        ret = R_FDL_ERR_REJECTED;
    }

    return (ret);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC r_fdl_flag_t R_FDL_UFct_FlashOpStart (r_fdl_request_t * request_pstr
   ,                                                  r_fdl_status_t  * tmpStat_penu
   ,                                                  r_fdl_flag_t      isCalledFromExecute_enu){
    uint32_t           addFlash;
    uint32_t           cntTotal;
    uint32_t           addBuf;
    uint32_t           granularityCurOp;
    uint32_t           cntCurOp;
    uint32_t           addEndCurOp;
    r_fdl_command_t    cmd;
    r_fdl_accessType_t accType;
    r_fdl_flag_t       cont;
    uint8_t            fcuCmd;

    addFlash         = (request_pstr->idx_u32);
    cntTotal         = (request_pstr->cnt_u16);
    cmd              = (request_pstr->command_enu);
    accType          = (request_pstr->accessType_enu);
    addBuf           = (request_pstr->bufAddr_u32);

    granularityCurOp = R_FDL_WRITE_SIZE;
    cont             = R_FDL_TRUE;
    (*tmpStat_penu)  = R_FDL_BUSY;

    if(R_FDL_CMD_ERASE == cmd){
        addFlash <<= R_FDL_BLOCK_SIZE_2N;
        cntTotal <<= R_FDL_BLOCK_SIZE_2N;

        cntCurOp = (1 << R_FDL_BLOCK_SIZE_2N);

        addBuf   = 0x00000001uL;

        fcuCmd   = R_FCU_CMD_ERASE;
    }
    else if(R_FDL_CMD_BLANKCHECK == cmd){
        cntTotal *= R_FDL_WRITE_SIZE;
        cntCurOp = cntTotal;

        R_FDL_IFct_CalcFOpUnitCnt_BC (&cntCurOp, addFlash);

        addBuf   = 0x00000001uL;

        fcuCmd   = R_FCU_CMD_BLANKCHECK;
    }
    else if(R_FDL_CMD_WRITE == cmd){
        cntCurOp = R_FDL_WRITE_SIZE;
        cntTotal *= R_FDL_WRITE_SIZE;

        fcuCmd   = R_FCU_CMD_WRITE;
    }
#if(defined ENABLE_CMD_WRITE16B)
    else if(R_FDL_CMD_WRITE16B == cmd){
        cntCurOp = R_FDL_WRITE_SIZE_16B;
        cntTotal *= R_FDL_WRITE_SIZE_16B;

        granularityCurOp = cntCurOp;

        fcuCmd   = R_FCU_CMD_WRITE;
    }
#endif
    else{
        cntTotal *= R_FDL_WRITE_SIZE;
        cntCurOp = cntTotal;

        fcuCmd = 0x00;
    }

    addEndCurOp = (addFlash + cntCurOp) - 1uL;

    if(R_FDL_TRUE == isCalledFromExecute_enu){
        if(R_FDL_NULL == addBuf)
        {
            (*tmpStat_penu) = R_FDL_ERR_PARAMETER;
        }
        else
        {
            (*tmpStat_penu) = R_FDL_IFct_ChkAccessBoundaries (addFlash, cntTotal, accType, granularityCurOp);
        }

        cont = R_FDL_FALSE;
    }

    if(R_FDL_BUSY == (*tmpStat_penu)){
        if(R_FDL_CMD_READ == cmd)
        {
            if(0 == (addBuf & R_FDL_U32_ALIGNED))
            {
                (*tmpStat_penu) = R_FDL_FCUFct_ReadOperation ((volatile uint32_t *)(&addFlash)
   ,                                                             addBuf
   ,                                                             (cntTotal / R_FDL_WRITE_SIZE));
                request_pstr->idx_u32 = addFlash;
            }
            else
            {
                (*tmpStat_penu) = R_FDL_ERR_PARAMETER;
            }
        }
        else
        {
            if(R_FDL_TRUE == isCalledFromExecute_enu)
            {
                (*tmpStat_penu) = R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_PE);
                if(R_FDL_OK == (*tmpStat_penu))
                {
                    (*tmpStat_penu) = R_FDL_FCUFct_SwitchMode_Check ();
                    if(R_FDL_OK == (*tmpStat_penu))
                    {
                        cont = R_FDL_TRUE;
                    }
                    else
                    {
                        g_fdl_str.opStatus_enu = R_FDL_OP_EXECUTE_SYNC_ON;
                    }
                }
            }

            if(R_FDL_TRUE == cont)
            {
                if((R_FDL_CMD_ERASE == cmd) || (R_FDL_CMD_BLANKCHECK == cmd))
                {
                    (*tmpStat_penu) = R_FDL_FCUFct_StartBCEraseOperation (addFlash, addEndCurOp, fcuCmd, accType);
                }
                else
                {
                    (*tmpStat_penu) = R_FDL_FCUFct_StartWriteOperation (addBuf, addFlash, cntCurOp, accType);

                    g_fdl_str.mulOp_str.bufAdd_u32 = addBuf + cntCurOp;
                }

                if(R_FDL_BUSY == (*tmpStat_penu))
                {
                    g_fdl_str.opStatus_enu = R_FDL_OP_BUSY;

                    g_fdl_str.mulOp_str.flashAdd_u32     = addEndCurOp + 1uL;
                    g_fdl_str.mulOp_str.flashAddEnd_u32  = (addFlash + cntTotal) - 1uL;
                    g_fdl_str.mulOp_str.accessType_enu   = accType;
                }
                else
                {
                    (void)R_FDL_FCUFct_SwitchMode_Start (R_FCU_MODE_USER);
                    if(R_FDL_BUSY == R_FDL_FCUFct_SwitchMode_Check ())
                    {
                        g_fdl_str.opResult_enu = (*tmpStat_penu);
                        g_fdl_str.opStatus_enu = R_FDL_OP_END_SYNC_OFF;
                        cont = R_FDL_FALSE;
                        (*tmpStat_penu) = R_FDL_BUSY;
                    }
                }
            }
        }
    }

    return (cont);
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC void R_FDL_UFct_EndCurrentOperation (r_fdl_status_t ret_enu){
    (g_fdl_str.reqInt_pstr)->status_enu = ret_enu;
    if((R_FDL_CMD_BLANKCHECK == (g_fdl_str.reqInt_pstr)->command_enu) && (R_FDL_ERR_BLANKCHECK == ret_enu)){
        (g_fdl_str.reqInt_pstr)->idx_u32 = g_fdl_str.opFailAddr_u32;
    }
    (g_fdl_str.reqInt_pstr)->accessType_enu = R_FDL_ACCESS_NONE;
    (g_fdl_str.reqInt_pstr)                 = R_FDL_REQUEST_POINTER_UNDEFINED;
    g_fdl_str.opStatus_enu                  = R_FDL_OP_IDLE;
}
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"
R_FDL_STATIC r_fdl_flag_t R_FDL_UFct_StateNotStandBy (void){
    r_fdl_flag_t ret;

    if((R_FDL_ISTAT_NORMALOP == g_fdl_str.iStat_enu)
        || (R_FDL_ISTAT_INIT == g_fdl_str.iStat_enu)
        || ((R_FDL_ISTAT_SUSPEND_PR == g_fdl_str.iStat_enu)
            || (R_FDL_ISTAT_SUSPENDED == g_fdl_str.iStat_enu))){
        ret = R_FDL_TRUE;
    }
    else{
        ret = R_FDL_FALSE;
    }

    return (ret);
}

#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

