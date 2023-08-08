#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_ON 0292
#endif

#ifndef R_FDL_TYPES_H
#define R_FDL_TYPES_H

#include "Platform_Types.hpp"

typedef struct R_FDL_DESCRIPTOR_T
{
    uint16    cpuFrequencyMHz_u16;
    uint16    fdlPoolSize_u16;
    uint16    eelPoolStart_u16;
    uint16    eelPoolSize_u16;
}r_fdl_descriptor_t;

typedef enum R_FDL_STATUS_T
{
    R_FDL_OK                    = 0,
    R_FDL_BUSY                  = 1,
    R_FDL_SUSPENDED             = 2,
    R_FDL_ERR_CONFIGURATION     = 3,
    R_FDL_ERR_PARAMETER         = 4,
    R_FDL_ERR_PROTECTION        = 5,
    R_FDL_ERR_REJECTED          = 6,
    R_FDL_ERR_WRITE             = 7,
    R_FDL_ERR_ERASE             = 8,
    R_FDL_ERR_BLANKCHECK        = 9,
    R_FDL_ERR_COMMAND           = 10,
    R_FDL_ERR_ECC_SED           = 11,
    R_FDL_ERR_ECC_DED           = 12,
    R_FDL_ERR_INTERNAL          = 13,
    R_FDL_CANCELLED             = 14
}r_fdl_status_t;

typedef enum R_FDL_ACCESS_TYPE_T
{
    R_FDL_ACCESS_NONE           = 0,
    R_FDL_ACCESS_USER           = 1,
    R_FDL_ACCESS_EEL            = 2
}r_fdl_accessType_t;

typedef enum R_FDL_COMMAND_T
{
    R_FDL_CMD_ERASE             = 0,
    R_FDL_CMD_WRITE             = 1,
    R_FDL_CMD_BLANKCHECK        = 2,
    R_FDL_CMD_READ              = 3,
#if(defined ENABLE_CMD_WRITE16B)
    R_FDL_CMD_WRITE16B          = 4,
#endif
    R_FDL_CMD_PREPARE_ENV       = 5
}r_fdl_command_t;

typedef volatile struct R_FDL_REQUEST_T
{
    r_fdl_command_t     command_enu;
    uint32              bufAddr_u32;
    uint32              idx_u32;
    uint16              cnt_u16;
    r_fdl_accessType_t  accessType_enu;
    r_fdl_status_t      status_enu;
}r_fdl_request_t;

#endif

