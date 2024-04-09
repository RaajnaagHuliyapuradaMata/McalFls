#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 0292
#endif

#ifndef R_FCL_TYPES_H
#define R_FCL_TYPES_H

#define R_FCL_NULL      0x00000000uL

#define R_FCL_COMP_GHS         (1)
#define R_FCL_COMP_IAR         (2)
#define R_FCL_COMP_REC         (3)

#if defined (__IAR_SYSTEMS_ASM__)
#define R_FCL_COMPILER R_FCL_COMP_IAR
#elif defined (__IAR_SYSTEMS_ICC__)
#define R_FCL_COMPILER R_FCL_COMP_IAR
#elif defined (__v850e3v5__)
#define R_FCL_COMPILER R_FCL_COMP_REC
#else
#define R_FCL_COMPILER R_FCL_COMP_GHS
#endif

#if((defined R_FCL_MIRROR_FCU_COPY) && (defined R_FCL_NO_FCU_COPY))
#error "r_fcl_types.h: Invalid define for support device macro"
#elif((defined R_FCL_MIRROR_FCU_COPY) && (defined R_FCL_NO_BFA_SWITCH))
#error "r_fcl_types.h: Invalid define for support device macro"
#elif((defined R_FCL_NO_FCU_COPY) && (defined R_FCL_NO_BFA_SWITCH))
#error "r_fcl_types.h: Invalid define for support device macro"
#elif(defined R_FCL_MIRROR_FCU_COPY)
#define R_FCL_INNER_NO_BFA_SWITCH
#elif(defined R_FCL_NO_FCU_COPY)
#define R_FCL_INNER_NO_FCU_COPY
#elif(defined R_FCL_NO_BFA_SWITCH)
#define R_FCL_INNER_NO_BFA_SWITCH
#define R_FCL_INNER_NO_FCU_COPY
#endif

typedef struct R_FCL_DESCRIPTOR_T
{
    uint32_t    id_au32[4];
    uint32_t    addrRam_u32;
    uint16_t    frequencyCpuMHz_u16;
}r_fcl_descriptor_t;

typedef enum R_FCL_STATUS_T
{
    R_FCL_OK
   ,   R_FCL_BUSY
   ,   R_FCL_SUSPENDED
   ,   R_FCL_ERR_FLMD0
   ,   R_FCL_ERR_PARAMETER
   ,   R_FCL_ERR_PROTECTION
   ,   R_FCL_ERR_REJECTED
   ,   R_FCL_ERR_FLOW
   ,   R_FCL_ERR_WRITE
   ,   R_FCL_ERR_ERASE
   ,   R_FCL_ERR_COMMAND
   ,   R_FCL_ERR_SUSPEND_FAILED
   ,   R_FCL_CANCELLED
   ,   R_FCL_ERR_INTERNAL
}r_fcl_status_t;

typedef enum R_FCL_COMMAND_T
{
    R_FCL_CMD_PREPARE_ENV
   ,   R_FCL_CMD_ERASE
   ,   R_FCL_CMD_WRITE
   ,   R_FCL_CMD_SET_LOCKBIT
   ,   R_FCL_CMD_GET_LOCKBIT
   ,   R_FCL_CMD_ENABLE_LOCKBITS
   ,   R_FCL_CMD_DISABLE_LOCKBITS
   ,   R_FCL_CMD_SET_OTP
   ,   R_FCL_CMD_GET_OTP
   ,   R_FCL_CMD_SET_OPB
   ,   R_FCL_CMD_GET_OPB
   ,   R_FCL_CMD_SET_ID
   ,   R_FCL_CMD_GET_ID
   ,   R_FCL_CMD_SET_READ_PROTECT_FLAG
   ,   R_FCL_CMD_GET_READ_PROTECT_FLAG
   ,   R_FCL_CMD_SET_WRITE_PROTECT_FLAG
   ,   R_FCL_CMD_GET_WRITE_PROTECT_FLAG
   ,   R_FCL_CMD_SET_ERASE_PROTECT_FLAG
   ,   R_FCL_CMD_GET_ERASE_PROTECT_FLAG
   ,   R_FCL_CMD_SET_SERIAL_PROG_DISABLED
   ,   R_FCL_CMD_GET_SERIAL_PROG_DISABLED
   ,   R_FCL_CMD_SET_SERIAL_ID_ENABLED
   ,   R_FCL_CMD_GET_SERIAL_ID_ENABLED
   ,   R_FCL_CMD_SET_RESET_VECTOR
   ,   R_FCL_CMD_GET_RESET_VECTOR
   ,   R_FCL_CMD_GET_BLOCK_CNT
   ,   R_FCL_CMD_GET_BLOCK_END_ADDR
   ,   R_FCL_CMD_GET_DEVICE_NAME
}r_fcl_command_t;

typedef volatile struct R_FCL_REQUEST_T
{
    r_fcl_command_t     command_enu;
    uint32_t            bufferAdd_u32;
    uint32_t            idx_u32;
    uint16_t cnt_u16;
    r_fcl_status_t status_enu;
}r_fcl_request_t;

#endif

