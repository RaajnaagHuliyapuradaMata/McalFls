#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 0292
#endif

#ifndef R_FCL_H
#define R_FCL_H

r_fcl_status_t  R_FCL_CopySections (void);

uint32_t        R_FCL_CalcFctAddr (uint32_t addFct_u32);

const uint8_t * R_FCL_GetVersionString (void);

r_fcl_status_t  R_FCL_Init (const r_fcl_descriptor_t * descriptor_pstr);

void            R_FCL_Execute (r_fcl_request_t * request_pstr);

#if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER

    void R_FCL_Handler (void);

    r_fcl_status_t R_FCL_SuspendRequest (void);
    r_fcl_status_t R_FCL_ResumeRequest  (void);

    r_fcl_status_t R_FCL_CancelRequest  (void);
#endif

#endif

