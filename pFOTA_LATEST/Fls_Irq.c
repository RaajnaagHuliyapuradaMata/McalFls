

#include "Fls_Internal.hpp"
#include "Fls_Irq.hpp"

#include "rh850_Types.hpp"

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#define FLS_IRQ_C_AR_RELEASE_MAJOR_VERSION FLS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLS_IRQ_C_AR_RELEASE_MINOR_VERSION FLS_AR_RELEASE_MINOR_VERSION_VALUE
#define FLS_IRQ_C_AR_RELEASE_REVISION_VERSION \
                                        FLS_AR_RELEASE_REVISION_VERSION_VALUE

#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#define FLS_IRQ_C_AR_MAJOR_VERSION    FLS_AR_MAJOR_VERSION_VALUE
#define FLS_IRQ_C_AR_MINOR_VERSION    FLS_AR_MINOR_VERSION_VALUE
#define FLS_IRQ_C_AR_PATCH_VERSION    FLS_AR_PATCH_VERSION_VALUE

#endif

#define FLS_IRQ_C_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION_VALUE
#define FLS_IRQ_C_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION_VALUE

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#if(FLS_IRQ_AR_RELEASE_MAJOR_VERSION != FLS_IRQ_C_AR_RELEASE_MAJOR_VERSION)
#error "Fls_Irq.c : Mismatch in Release Major Version"
#endif

#if(FLS_IRQ_AR_RELEASE_MINOR_VERSION != FLS_IRQ_C_AR_RELEASE_MINOR_VERSION)
#error "Fls_Irq.c : Mismatch in Release Minor Version"
#endif

#if(FLS_IRQ_AR_RELEASE_REVISION_VERSION != \
                                          FLS_IRQ_C_AR_RELEASE_REVISION_VERSION)
#error "Fls_Irq.c : Mismatch in Release Revision Version"
#endif

#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#if(FLS_IRQ_AR_MAJOR_VERSION != FLS_IRQ_C_AR_MAJOR_VERSION)
#error "Fls_Irq.c : Mismatch in Specification Major Version"
#endif

#if(FLS_IRQ_AR_MINOR_VERSION != FLS_IRQ_C_AR_MINOR_VERSION)
#error "Fls_Irq.c : Mismatch in Specification Minor Version"
#endif

#if(FLS_IRQ_AR_PATCH_VERSION != FLS_IRQ_C_AR_PATCH_VERSION)
#error "Fls_Irq.c : Mismatch in Specification Patch Version"
#endif
#endif

#if(FLS_IRQ_SW_MAJOR_VERSION != FLS_IRQ_C_SW_MAJOR_VERSION)
#error "Fls_Irq.c : Mismatch in Software Major Version"
#endif

#if(FLS_IRQ_SW_MINOR_VERSION != FLS_IRQ_C_SW_MINOR_VERSION)
#error "Fls_Irq.c : Mismatch in Software Minor Version"
#endif

#if(FLS_FLENDNM_ISR_API == STD_ON)
#define FLS_START_SEC_CODE_FAST
#include "MemMap.hpp"

#if defined (Os_FLS_FLENDNM_CAT2_ISR) || defined (FLS_FLENDNM_CAT2_ISR)
ISR(FLS_FLENDNM_CAT2_ISR)

#else
_INTERRUPT_ FUNC(void, FLS_FAST_CODE) FLS_FLENDNM_ISR(void)
#endif
{
  switch(Fls_GVar.Fls_GenCommand){
    case FLS_COMMAND_ERASE:
    case FLS_COMMAND_WRITE:

         if(FLS_ZERO == Fls_GVar.Fls_MutexFlag)
         {
           Fls_GVar.Fls_MutexFlag = FLS_ONE;
           R_FDL_Handler();
           if(R_FDL_SUSPENDED == Fls_GstVar.GstfdlRequest.status_enu)
           {
             Fls_GstVar.GucDFStatus = Fls_GstVar.GstfdlNewRequest.status_enu;
           }
           else
           {
             Fls_GstVar.GucDFStatus = Fls_GstVar.GstfdlRequest.status_enu;
           }
           if(R_FDL_BUSY != Fls_GstVar.GucDFStatus)
           {
             Fls_GVar.Fls_GenState = MEMIF_IDLE;
             if(R_FDL_OK == Fls_GstVar.GucDFStatus)
             {
               Fls_GVar.Fls_GenJobResult = MEMIF_JOB_OK;

               Fls_GpConfigPtr->pJobEndNotificationPointer();
             }
             else
             {
               Fls_GVar.Fls_GenJobResult = MEMIF_JOB_FAILED;

               Fls_GpConfigPtr->pJobErrorNotificationPointer();
             }
#if(FLS_INTERRUPT_MODE == STD_ON)

             RH850_SV_MODE_IMR_OR(16, (Fls_GpConfigPtr->pFlEndImrAddress),

                                  ((uint16)~(Fls_GpConfigPtr->usFlEndImrMask)));
#endif

             Fls_GVar.Fls_GenCommand = FLS_COMMAND_NONE;
           }
           else
           {
           }

           Fls_GVar.Fls_MutexFlag = FLS_ZERO;
         }
         else
         {
         }
    break;
    case FLS_COMMAND_READ:
    case FLS_COMMAND_COMPARE:
    case FLS_COMMAND_BLANKCHECK:
    case FLS_COMMAND_READ_IMM:
    default:

    break;
  }
}
#define FLS_STOP_SEC_CODE_FAST
#include "MemMap.hpp"
#endif

