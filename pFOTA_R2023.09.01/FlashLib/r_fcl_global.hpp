#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 0292
#endif

#ifndef R_FCL_GLOBAL_H
#define R_FCL_GLOBAL_H

#define R_FCL_VERSION_STRING     "SH850T01xxxxxxV212"

#if !(defined FCL_TEST_PATCH)
#ifndef R_FCL_STATIC
#define R_FCL_STATIC        static
#endif
#else
#define R_FCL_STATIC
#endif

#define R_FCL_REQUEST_POINTER_UNDEFINED         (r_fcl_request_t *)(0x00000000uL)
#define R_FCL_DESCRIPTOR_POINTER_UNDEFINED      (r_fcl_descriptor_t *)(0x00000000uL)

#define R_FCL_TIMEOUT_CC_CLK_P_LOOP             (3)

#define R_FCL_TIMEOUT_CC                        (   ( (40 * g_fcl_data_str.RTCfg_pstr->frequencyCpuMHz_u16) \
                                                  + (R_FCL_TIMEOUT_CC_CLK_P_LOOP - 1) ) / R_FCL_TIMEOUT_CC_CLK_P_LOOP )

#define R_FCL_TIMEOUT_CHKREG_CLK_P_LOOP         (19)

#define R_FCL_TIMEOUT_CHKREG                    (   ( (40 * g_fcl_data_str.RTCfg_pstr->frequencyCpuMHz_u16) \
                                                  + (R_FCL_TIMEOUT_CHKREG_CLK_P_LOOP - 1) ) / R_FCL_TIMEOUT_CHKREG_CLK_P_LOOP )

#if R_FCL_COMPILER == R_FCL_COMP_GHS
    int32_t __STSR(int32_t regID, int32_t selID);

#elif R_FCL_COMPILER == R_FCL_COMP_IAR
    __intrinsic int32_t __STSR(int32_t reg, int32_t selID);
#elif R_FCL_COMPILER == R_FCL_COMP_REC
#endif

typedef enum R_FCL_FLAG_T
{
    R_FCL_FALSE                 = 0x00u
   ,   R_FCL_TRUE                  = 0x01u
}r_fcl_flag_t;

typedef enum R_FCL_MODE_T
{
    R_FCL_READ_MODE             = 0x00u
   ,   R_FCL_WRITE_MODE            = 0x01u
   ,   R_FCL_CFG_WRITE_MODE        = 0x80u
}r_fcl_mode_t;

typedef enum R_FCL_INT_STATUS_T
{
    R_FCL_ISTAT_NOINIT
   ,   R_FCL_ISTAT_INIT
   ,   R_FCL_ISTAT_PREPARED
   ,   R_FCL_ISTAT_BUSY
   ,   R_FCL_ISTAT_SUSPENDED
}r_fcl_int_status_t;

typedef enum R_FCL_OP_STATUS_T
{
    R_FCL_OP_IDLE_STATE
   ,   R_FCL_OP_PREPARE_STATE
   ,   R_FCL_PREP_COPY_FW_STATE
   ,   R_FCL_PREP_RESET_FCU_STATE
   ,   R_FCL_PREP_FCURAM_CHKSUM_STATE
   ,   R_FCL_PREP_ID_CHECK_FREQ_SET_STATE
   ,   R_FCL_BUSY_CHECK_PE_MODE_SWITCH_STATE
   ,   R_FCL_BUSY_START_OP_STATE
   ,   R_FCL_BUSY_START_WRITE_OP_STATE
   ,   R_FCL_BUSY_CHECK_RESULT_STATE
   ,   R_FCL_BUSY_SWITCH_READ_MODE_STATE
   ,   R_FCL_BUSY_CHECK_READ_MODE_SWITCH_STATE
   ,   R_FCL_OP_FINISHED_STATE
   ,   R_FCL_OP_INTERNAL_ERROR_SWITCH_READ_STATE
   ,   R_FCL_OP_INTERNAL_ERROR_CHECK_READ_STATE
   ,   R_FCL_OP_INTERNAL_ERROR_STATE
}r_fcl_op_status_t;

typedef struct R_FCL_MULTIOP_T
{
    uint32_t            opAddr_u32;
    uint32_t            buffAddr_u32;
    uint16_t            opCnt_u16;
    r_fcl_op_status_t   opStatus_enu;
    r_fcl_status_t      opResult_enu;
}r_fcl_multiOp_t;

typedef struct R_FCL_SUSPENDINFO_T
{
    r_fcl_request_t *   reqSuspend_pstr;
    r_fcl_multiOp_t     opSuspend_str;
    r_fcl_flag_t        spdSpdRequest_enu;
    r_fcl_flag_t        spdResRequest_enu;
    r_fcl_flag_t        flagSuspended_enu;
    uint16_t            matSel_u16;
}r_fcl_suspendInfo_t;

typedef struct R_FCL_DEVICEINFO_T
{
    uint32_t            cf1BlkCnt32kB_u32;
    uint32_t            cf2BlkCnt32kB_u32;
    uint32_t            usrBlkCnt32kB_u32;
    uint32_t            secureData_u32;
    uint16_t            fMin_u16;
    uint16_t            fMax_u16;
    uint16_t            fPClk_u16;
    uint16_t            blkCnt_u16;
    uint16_t            matSel_u16;
    uint8_t             deviceName_au08[16];
    uint8_t             cf1BlkCnt8kB_u8;
    uint8_t             fVersion_u8;
    uint8_t             fDivider_u8;
    r_fcl_flag_t        emulationMode_enu;
    r_fcl_flag_t        enableLockBits_enu;
    r_fcl_flag_t        accessExtendedUserArea_enu;
}r_fcl_deviceInfo_t;

typedef void (* r_fcl_fctPtr_t)(void);

typedef struct R_FCL_DATA_T
{
    const r_fcl_descriptor_t *  RTCfg_pstr;
    r_fcl_request_t *           reqInt_pstr;
    r_fcl_multiOp_t             opVar_str;
    r_fcl_suspendInfo_t         suspendInfo_str;
    r_fcl_int_status_t          intStatus_enu;
    r_fcl_mode_t                flashMode_enu;
    r_fcl_deviceInfo_t          deviceInfo_str;
    r_fcl_fctPtr_t              executionPtr_p;
    r_fcl_flag_t                waitAckModeSwitch_enu;
    r_fcl_flag_t                cancelReq_enu;
    uint32_t                    fcuramAddr_u32;
    uint32_t                    firmAddr_u32;
    uint8_t                     intBuf_au08[16];
#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_INTERNAL
            r_fcl_fctPtr_t      handlerPtr_p;
#endif
}r_fcl_data_t;

#if R_FCL_COMPILER == R_FCL_COMP_GHS
#pragma ghs startdata
#pragma ghs section bss = ".R_FCL_DATA"
#define R_FCL_NOINIT
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
#pragma segment = "R_FCL_DATA"
#pragma location = "R_FCL_DATA"
#define R_FCL_NOINIT __no_init
#elif R_FCL_COMPILER == R_FCL_COMP_REC
#pragma section r0_disp32 "R_FCL_DATA"
#define R_FCL_NOINIT
#endif

extern R_FCL_NOINIT r_fcl_data_t   g_fcl_data_str;

#if R_FCL_COMPILER == R_FCL_COMP_GHS
#pragma ghs section bss = default
#pragma ghs enddata
#elif R_FCL_COMPILER == R_FCL_COMP_IAR
#pragma dataseg = default
#elif R_FCL_COMPILER == R_FCL_COMP_REC
#pragma section default
#endif

void            R_FCL_I_write_memory_u08          (const uint32_t addr_u32, const uint8_t val_u08);
void            R_FCL_Fct_CallFromRAM             (void);
void            R_FCL_FCUFct_PrepareEnvironment   (void);
void            R_FCL_FCUFct_HandleMultiOperation (void);
void            R_FCL_FCUFct_GetConfigArea        (void);
void            R_FCL_FCUFct_SetConfigArea        (void);
void            R_FCL_FCUFct_HandleLockBit        (void);
void            R_FCL_FCUFct_LockBitMode          (uint16_t mode_u16);
void            R_FCL_FCUFct_GetOTPBit            (void);
void            R_FCL_FCUFct_SetOTPBit            (void);
void            R_FCL_FCUFct_GetSecurityFlag      (void);
void            R_FCL_FCUFct_GetDeviceName        (void);
void            R_FCL_FCUFct_GetBlockEndAddr      (void);
void            R_FCL_FCUFct_GetBlockCnt          (void);
void            R_FCL_FCUFct_Erase                (void);
void            R_FCL_FCUFct_Write                (void);
void            R_FCL_Fct_CodeRam_CalcRange       (uint32_t * secStart_pu32, uint32_t * secSize_pu32);
void            R_FCL_Fct_CodeRomRam_CalcRange    (uint32_t * secStart_pu32, uint32_t * secSize_pu32);
void            R_FCL_Fct_CodeUsr_CalcRange       (uint32_t * secStart_pu32, uint32_t * secSize_pu32);
void            R_FCL_Fct_CodeUsrInt_CalcRange    (uint32_t * secStart_pu32, uint32_t * secSize_pu32);
void            R_FCL_Fct_CodeExProt_CalcRange    (uint32_t * secStart_pu32, uint32_t * secSize_pu32);
void            R_FCL_FCUFct_Switch_BFlash        (uint8_t mode_u08);
uint32_t        R_FCL_FCUFct_ChkReg               (uint32_t regAdd, uint32_t valMask, uint32_t val, uint32_t to);
uint32_t        R_FCL_FCUFct_Clear_Cache_Asm      (uint32_t add_u32, uint32_t timeout_u32);
uint32_t        R_FCL_Fct_PrgOffset               (void);
uint32_t        R_FCL_Fct_Copy_Code               (uint32_t src_u32, uint32_t dest_u32, uint32_t cnt_u32);
r_fcl_status_t  R_FCL_FCUFct_SwitchMode_Start     (r_fcl_mode_t mode_enu);
r_fcl_status_t  R_FCL_FCUFct_SwitchMode_Check     (void);
r_fcl_flag_t    R_FCL_FCUFct_CheckMode            (void);
#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
    void        R_FCL_FCUFct_HandleResume         (void);
#endif

#if(defined FCL_TEST_PATCH)
typedef struct TESTPATCH_T
{
    uint32_t status_patch_active;
    uint32_t status_patch_value;
}TestPatch_t;

extern TestPatch_t TestPatch;

uint32_t test_cb_read_u32 (const uint32_t addr);
uint16_t test_cb_read_u16 (const uint32_t addr);
uint8_t test_cb_read_u8   (const uint32_t addr);

void test_cb_write_u32    (const uint32_t addr, const uint32_t val);
void test_cb_write_u16    (const uint32_t addr, const uint16_t val);
void test_cb_write_u8     (const uint32_t addr, const uint8_t val);
#endif

#endif

