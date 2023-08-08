#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_ON 0292
#endif

#ifdef AUTOSAR_IMPLEMENTATION
    #if defined R_FDL_START_SEC_PUBLIC_CODE
		#undef R_FDL_START_SEC_PUBLIC_CODE			
        #define FDL_START_SEC_PUBLIC_CODE
    #elif defined R_FDL_STOP_SEC_PUBLIC_CODE
		#undef R_FDL_STOP_SEC_PUBLIC_CODE
        #define FDL_STOP_SEC_PUBLIC_CODE
    #elif defined R_FDL_START_SEC_CONST
		#undef R_FDL_START_SEC_CONST
        #define FDL_START_SEC_CONST_UNSPECIFIED
    #elif defined R_FDL_STOP_SEC_CONST
		#undef R_FDL_STOP_SEC_CONST
        #define FDL_STOP_SEC_CONST_UNSPECIFIED
    #elif defined R_FDL_START_SEC_VAR
		#undef R_FDL_START_SEC_VAR
        #define FDL_START_SEC_VAR_UNSPECIFIED
    #elif defined R_FDL_STOP_SEC_VAR
		#undef R_FDL_STOP_SEC_VAR
        #define FDL_STOP_SEC_VAR_UNSPECIFIED
    #else
      #error "r_fdl_mem_map.h: No valid section define found"
    #endif

    #include "MemMap.hpp"	
#else

    #if defined R_FDL_START_SEC_PUBLIC_CODE
        #undef R_FDL_START_SEC_PUBLIC_CODE
        #if   R_FDL_COMPILER == R_FDL_COMP_GHS
            #pragma ghs section text=".R_FDL_Text"
        #elif R_FDL_COMPILER == R_FDL_COMP_IAR
            #pragma location = "R_FDL_Text"
        #elif R_FDL_COMPILER == R_FDL_COMP_REC
            #pragma section text "R_FDL_Text"
        #endif
    #elif defined R_FDL_STOP_SEC_PUBLIC_CODE
        #undef R_FDL_STOP_SEC_PUBLIC_CODE
        #if   R_FDL_COMPILER == R_FDL_COMP_GHS
            #pragma ghs section text=default
        #elif R_FDL_COMPILER == R_FDL_COMP_IAR

        #elif R_FDL_COMPILER == R_FDL_COMP_REC
            #pragma section default
        #endif

    #elif defined R_FDL_START_SEC_CONST
        #undef R_FDL_START_SEC_CONST
        #if   R_FDL_COMPILER == R_FDL_COMP_GHS
            #pragma ghs startdata
            #pragma ghs section rodata=".R_FDL_Const"
        #elif R_FDL_COMPILER == R_FDL_COMP_IAR
            #pragma constseg = "R_FDL_Const"
        #elif R_FDL_COMPILER == R_FDL_COMP_REC
            #pragma section const "R_FDL_Const"
        #endif
    #elif defined R_FDL_STOP_SEC_CONST
        #undef R_FDL_STOP_SEC_CONST
        #if   R_FDL_COMPILER == R_FDL_COMP_GHS
            #pragma ghs section rodata=default
            #pragma ghs enddata
        #elif R_FDL_COMPILER == R_FDL_COMP_IAR
            #pragma constseg = default
        #elif R_FDL_COMPILER == R_FDL_COMP_REC

        #endif

    #elif defined R_FDL_START_SEC_VAR
        #undef R_FDL_START_SEC_VAR
        #if R_FDL_COMPILER == R_FDL_COMP_GHS
            #pragma ghs startdata
            #pragma ghs section bss = ".R_FDL_Data"
        #elif R_FDL_COMPILER == R_FDL_COMP_IAR
            #pragma dataseg = R_FDL_Data
        #elif R_FDL_COMPILER == R_FDL_COMP_REC
            #pragma section r0_disp32 "R_FDL_Data"
        #endif
    #elif defined R_FDL_STOP_SEC_VAR
        #undef R_FDL_STOP_SEC_VAR
        #if R_FDL_COMPILER == R_FDL_COMP_GHS
            #pragma ghs section bss = default
            #pragma ghs enddata
        #elif R_FDL_COMPILER == R_FDL_COMP_IAR
            #pragma dataseg = default
        #elif R_FDL_COMPILER == R_FDL_COMP_REC

        #endif

    #else
      #error "r_fdl_mem_map.h: No valid section define found"
    #endif

#endif

