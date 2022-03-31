/******************************************************************************/
/* File   : Fls.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "infFls_EcuM.hpp"
#include "infFls_Dcm.hpp"
#include "infFls_SchM.hpp"

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
      module_Fls(Std_TypeVersionInfo lVersionInfo) : abstract_module(lVersionInfo){
      }
      FUNC(void, FLS_CODE) InitFunction(
         CONSTP2CONST(CfgModule_TypeAbstract, FLS_CONFIG_DATA, FLS_APPL_CONST) lptrCfgModule
      );
      FUNC(void, FLS_CODE) DeInitFunction (void);
      FUNC(void, FLS_CODE) MainFunction   (void);
};

extern VAR(module_Fls, FLS_VAR) Fls;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
CONSTP2VAR(infEcuMClient, FLS_VAR, FLS_CONST) gptrinfEcuMClient_Fls = &Fls;
CONSTP2VAR(infDcmClient,  FLS_VAR, FLS_CONST) gptrinfDcmClient_Fls  = &Fls;
CONSTP2VAR(infSchMClient, FLS_VAR, FLS_CONST) gptrinfSchMClient_Fls = &Fls;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/
#include "CfgFls.hpp"

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_Fls, FLS_VAR) Fls(
   {
         0x0000
      ,  0xFFFF
      ,  0x01
      ,  '0'
      ,  '1'
      ,  '0'
   }
);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, FLS_CODE) module_Fls::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, FLS_CONFIG_DATA, FLS_APPL_CONST) lptrCfgModule
){
   if(E_OK == IsInitDone){
#if(STD_ON == Fls_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
      if(NULL_PTR == lptrCfgModule){
#if(STD_ON == Fls_DevErrorDetect)
         Det_ReportError(
         );
#endif
      }
      else{
// check lptrCfgModule for memory faults
// use PBcfg_Fls as back-up configuration
      }
      IsInitDone = E_OK;
   }
}

FUNC(void, FLS_CODE) module_Fls::DeInitFunction(void){
   if(E_OK != IsInitDone){
#if(STD_ON == Fls_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
      IsInitDone = E_NOT_OK;
   }
}

FUNC(void, FLS_CODE) module_Fls::MainFunction(void){
}

class class_Fls_Unused{
   public:
      FUNC(void, FLS_CODE) Erase          (void);
      FUNC(void, FLS_CODE) Write          (void);
      FUNC(void, FLS_CODE) Cancel         (void);
      FUNC(void, FLS_CODE) GetStatus      (void);
      FUNC(void, FLS_CODE) GetJobResult   (void);
      FUNC(void, FLS_CODE) Read           (void);
      FUNC(void, FLS_CODE) Compare        (void);
      FUNC(void, FLS_CODE) SetMode        (void);
};

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

