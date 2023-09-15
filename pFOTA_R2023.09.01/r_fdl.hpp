#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 0292
#endif

#ifndef R_FDL_H
#define R_FDL_H

#define R_FDL_COMP_GHS 1
#define R_FDL_COMP_IAR 2
#define R_FDL_COMP_REC 3

#if defined (__IAR_SYSTEMS_ASM__)
#define R_FDL_COMPILER R_FDL_COMP_IAR
#elif defined (__IAR_SYSTEMS_ICC__)
#define R_FDL_COMPILER R_FDL_COMP_IAR
#elif defined (__v850e3v5__)
#define R_FDL_COMPILER R_FDL_COMP_REC
#else
#define R_FDL_COMPILER R_FDL_COMP_GHS
#endif

#include "CfgMcalFls_Fdl.hpp"
#include "r_fdl_types.hpp"

#ifdef R_FDL_USERIF_C
#define R_FDL_EXTERN
#else
#define R_FDL_EXTERN extern
#endif

R_FDL_EXTERN r_fdl_status_t     R_FDL_Init (const r_fdl_descriptor_t * descriptor_pstr);

R_FDL_EXTERN void               R_FDL_Execute (r_fdl_request_t * request_pstr);

R_FDL_EXTERN void               R_FDL_Handler (void);

R_FDL_EXTERN r_fdl_status_t     R_FDL_SuspendRequest (void);

R_FDL_EXTERN r_fdl_status_t     R_FDL_ResumeRequest (void);

R_FDL_EXTERN r_fdl_status_t     R_FDL_StandBy (void);

R_FDL_EXTERN r_fdl_status_t     R_FDL_WakeUp (void);

R_FDL_EXTERN r_fdl_status_t     R_FDL_CancelRequest (void);

R_FDL_EXTERN const uint8_t *    R_FDL_GetVersionString (void);

#endif

