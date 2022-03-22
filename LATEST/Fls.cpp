/******************************************************************************/
/* File   : Fls.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "module.h"
#include "Fls_Cfg.h"
#include "infFls_EcuM.h"
#include "infFls_Dcm.h"
#include "infFls_SchM.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define FLS_AR_RELEASE_MAJOR_VERSION                                           4
#define FLS_AR_RELEASE_MINOR_VERSION                                           3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(FLS_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION)
   #error "Incompatible FLS_AR_RELEASE_MAJOR_VERSION!"
#endif

#if(FLS_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)
   #error "Incompatible FLS_AR_RELEASE_MINOR_VERSION!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_Fls:
      public abstract_module
{
   public:
      FUNC(void, FLS_CODE) InitFunction   (void);
      FUNC(void, FLS_CODE) DeInitFunction (void);
      FUNC(void, FLS_CODE) GetVersionInfo (void);
      FUNC(void, FLS_CODE) MainFunction   (void);
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_Fls, FLS_VAR) Fls;
CONSTP2VAR(infEcuMClient, FLS_VAR, FLS_CONST) gptrinfEcuMClient_Fls = &Fls;
CONSTP2VAR(infDcmClient,  FLS_VAR, FLS_CONST) gptrinfDcmClient_Fls  = &Fls;
CONSTP2VAR(infSchMClient, FLS_VAR, FLS_CONST) gptrinfSchMClient_Fls = &Fls;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, FLS_CODE) module_Fls::InitFunction(void){
   Fls.IsInitDone = E_OK;
}

FUNC(void, FLS_CODE) module_Fls::DeInitFunction(void){
   Fls.IsInitDone = E_NOT_OK;
}

FUNC(void, FLS_CODE) module_Fls::GetVersionInfo(void){
#if(STD_ON == Fls_DevErrorDetect)
//TBD: API parameter check
   Det_ReportError(
   );
#endif
}

FUNC(void, FLS_CODE) module_Fls::MainFunction(void){
}

#include "Fls_Unused.h"

FUNC(void, FLS_CODE) class_Fls_Unused::Erase(void){
}

FUNC(void, FLS_CODE) class_Fls_Unused::Write(void){
}

FUNC(void, FLS_CODE) class_Fls_Unused::Cancel(void){
}

FUNC(void, FLS_CODE) class_Fls_Unused::GetStatus(void){
}

FUNC(void, FLS_CODE) class_Fls_Unused::GetJobResult(void){
}

FUNC(void, FLS_CODE) class_Fls_Unused::Read(void){
}

FUNC(void, FLS_CODE) class_Fls_Unused::Compare(void){
}

FUNC(void, FLS_CODE) class_Fls_Unused::SetMode(void){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

