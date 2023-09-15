#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 0292
#endif

#include "r_fdl_global.hpp"

extern r_fdl_status_t R_FDL_InitVariables (const r_fdl_descriptor_t * descriptor_pstr);

#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

#ifdef R_FDL_LIB_V1_COMPATIBILITY
    r_fdl_status_t R_FDL_Init (const r_fdl_descriptor_t * descriptor_pstr){
        r_fdl_status_t  ret;
        r_fdl_request_t request;

        ret = R_FDL_InitVariables (descriptor_pstr);

        if(R_FDL_OK == ret)
        {
            request.command_enu = R_FDL_CMD_PREPARE_ENV;
            R_FDL_Execute (&request);

            while(R_FDL_BUSY == request.status_enu)
            {
                R_FDL_Handler ();
            }

            ret = request.status_enu;
        }

        return (ret);
    }
#else
    r_fdl_status_t R_FDL_Init (const r_fdl_descriptor_t * descriptor_pstr){
        r_fdl_status_t ret;

        ret = R_FDL_InitVariables (descriptor_pstr);

        return (ret);
    }
#endif

#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.hpp"

