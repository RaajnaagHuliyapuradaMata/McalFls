#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 0292
#endif

#ifndef R_FDL_GLOBAL_H
#define R_FDL_GLOBAL_H

#include "r_typedefs.hpp"
#include "r_fdl.hpp"
#include "r_fdl_env.hpp"

#define R_FDL_VERSION_STRING                    "DH850T01xxxxxxV200"

#define R_FDL_REQUEST_POINTER_UNDEFINED         (r_fdl_request_t *)(0x00000000uL)
#define R_FDL_DESCRIPTOR_POINTER_UNDEFINED      (r_fdl_descriptor_t *)(0x00000000uL)
#define R_FDL_NULL                              (0x00000000uL)
#define AUTOSAR_IMPLEMENTATION

typedef enum R_FDL_FLAG_T
{
    R_FDL_FALSE
   ,   R_FDL_TRUE
}r_fdl_flag_t;

typedef enum R_FDL_INT_STATUS_T
{
    R_FDL_ISTAT_NOINIT          = 0x00000000uL
   ,   R_FDL_ISTAT_INIT            = 0x55555554uL
   ,   R_FDL_ISTAT_NORMALOP        = 0x55555555uL
   ,   R_FDL_ISTAT_SUSPEND_PR      = 0x55555556uL
   ,   R_FDL_ISTAT_SUSPENDED       = 0x55555557uL
   ,   R_FDL_ISTAT_STANDBY_PR      = 0x55555558uL
   ,   R_FDL_ISTAT_STANDBY         = 0x55555559uL
}r_fdl_int_status_t;

typedef void (* r_fdl_pFct_ExeInRAM)(uint32_t * param_pu32);

typedef enum R_FDL_OP_STATUS_T
{
    R_FDL_OP_IDLE                 = 0
   ,   R_FDL_OP_EXECUTE_SYNC_ON      = 1
   ,   R_FDL_OP_PREPARE_START        = 2
   ,   R_FDL_OP_PREPARE_RST_FCU      = 3
   ,   R_FDL_OP_PREPARE_END          = 4
   ,   R_FDL_OP_RESUME_SYNC_ON       = 5
   ,   R_FDL_OP_RESUME_MULTI_SYNC_ON = 6
   ,   R_FDL_OP_BUSY                 = 7
   ,   R_FDL_OP_SUSPEND_SYNC_OFF     = 8
   ,   R_FDL_OP_END_SYNC_OFF         = 9
}r_fdl_op_status_t;

typedef struct R_FDL_MULTIOP_T
{
    uint32_t            flashAdd_u32;
    uint32_t            bufAdd_u32;
    uint32_t            flashAddEnd_u32;
    r_fdl_accessType_t  accessType_enu;
}r_fdl_multiOp_t;

typedef struct R_FDL_DATA_T
{
    const r_fdl_descriptor_t *  RTCfg_pstr;
    r_fdl_multiOp_t     mulOp_str;
    r_fdl_multiOp_t     spdMulOp_str;
    r_fdl_request_t *   reqSuspend_pstr;
    r_fdl_request_t *   reqInt_pstr;
    r_fdl_op_status_t   opStatus_enu;
    uint32_t            opFailAddr_u32;
    uint32_t            dfSize_u32;
    uint32_t            baseAddrECC_u32;
    uint32_t            chksumEndAddr_u32;
    uint32_t            chksumVal_u32;
    uint16_t            flashMode_u16;
    r_fdl_status_t      spdResStatus_enu;
    r_fdl_status_t      opResult_enu;
    r_fdl_flag_t        cancelRequest_enu;
    r_fdl_flag_t        spdSpdRequest_enu;
    r_fdl_flag_t        spdResRequest_enu;
    r_fdl_int_status_t  stByIStatBackUp_enu;
    r_fdl_int_status_t  iStat_enu;
}r_fdl_data_t;

#ifndef R_FDL_STATIC
#define R_FDL_STATIC static
#endif

r_fdl_status_t  R_FDL_FCUFct_CheckFatalError       (void);
r_fdl_flag_t    R_FDL_FCUFct_ChkReady              (void);
r_fdl_flag_t    R_FDL_FCUFct_ChkSuspendable        (void);
r_fdl_flag_t    R_FDL_FCUFct_ChkStartable          (r_fdl_command_t     cmd_enu);
void            R_FDL_FCUFct_ClearStatus           (void);
r_fdl_status_t  R_FDL_FCUFct_GetStat               (void);
void            R_FDL_FCUFct_InitRAM               (void);
r_fdl_status_t  R_FDL_FCUFct_ReadOperation         (volatile uint32_t * pAddSrc_u32
   ,                                                   uint32_t            addDest_u32
   ,                                                   uint32_t            cnt_u32);
r_fdl_flag_t    R_FDL_FCUFct_ResumeChkNeed         (void);
void            R_FDL_FCUFct_Resume                (void);
r_fdl_status_t  R_FDL_FCUFct_SetFrequency          (void);
uint32_t        R_FDL_FCUFct_GetDFSize             (void);
r_fdl_status_t  R_FDL_FCUFct_StartBCEraseOperation (uint32_t            addStart_u32
   ,                                                   uint32_t            addEnd_u32
   ,                                                   uint8_t             fcuCmd_u08
   ,                                                   r_fdl_accessType_t  accType_enu);
r_fdl_status_t  R_FDL_FCUFct_StartWriteOperation   (uint32_t            addSrc_u32
   ,                                                   uint32_t            addDest_u32
   ,                                                   uint32_t            cnt_u32
   ,                                                   r_fdl_accessType_t  accType_enu);
void            R_FDL_FCUFct_Suspend               (void);
r_fdl_status_t  R_FDL_FCUFct_SwitchMode_Start      (uint16_t            mode_u16);
r_fdl_status_t  R_FDL_FCUFct_SwitchMode_Check      (void);
r_fdl_status_t  R_FDL_IFct_ChkAccessBoundaries     (uint32_t            addrStart_u32
   ,                                                   uint32_t            bCnt_u32
   ,                                                   r_fdl_accessType_t  accType_enu
   ,                                                   uint32_t            granularity_u32);
void            R_FDL_IFct_WriteMemoryU08          (uint32_t            addr_u32
   ,                                                   uint8_t             val_u08);
void            R_FDL_IFct_CalcFOpUnitCnt_BC       (uint32_t *          cnt_pu32
   ,                                                   uint32_t            addr_u32);
void            R_FDL_FCUFct_ForcedStop            (void);
r_fdl_status_t  R_FDL_FCUFct_VerifyChecksum        (void);

#define R_FDL_START_SEC_VAR		
#include "r_fdl_mem_map.hpp"

#if R_FDL_COMPILER == R_FDL_COMP_GHS
#define R_FDL_NOINIT
#elif R_FDL_COMPILER == R_FDL_COMP_IAR
#define R_FDL_NOINIT __no_init
#elif R_FDL_COMPILER == R_FDL_COMP_REC
#define R_FDL_NOINIT
#endif

extern R_FDL_NOINIT r_fdl_data_t   g_fdl_str;

#define R_FDL_STOP_SEC_VAR	
#include "r_fdl_mem_map.hpp"

#ifdef PATCH_TO_SIMULATE_ERRORS
#include "FDL-tc_common.hpp"
#endif

#ifdef _BullseyeCoverage
#define R_FDL_COV_SAVEOFF _Pragma ("BullseyeCoverage save off")
#define R_FDL_COV_RESTORE _Pragma ("BullseyeCoverage restore")
#else
#define R_FDL_COV_SAVEOFF
#define R_FDL_COV_RESTORE
#endif

#endif

