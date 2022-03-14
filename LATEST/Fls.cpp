/******************************************************************************/
/* File   : Fls.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "module.h"
#include "infFls_EcuM.h"
#include "infFls_Dcm.h"
#include "infFls_SchM.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/


/*****************************************************/
/* OBJECTS                                           */
/*****************************************************/
VAR(module_Fls, FLS_VAR) Fls;
CONSTP2VAR(infEcuMClient, FLS_VAR, FLS_CONST) gptrinfEcuMClient_Fls = &Fls;
CONSTP2VAR(infDcmClient,  FLS_VAR, FLS_CONST) gptrinfDcmClient_Fls  = &Fls;
CONSTP2VAR(infSchMClient, FLS_VAR, FLS_CONST) gptrinfSchMClient_Fls = &Fls;

/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
FUNC(void, FLS_CODE) module_Fls::InitFunction(void){
}

FUNC(void, FLS_CODE) module_Fls::DeInitFunction(void){
}

FUNC(void, FLS_CODE) module_Fls::GetVersionInfo(void){
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

/*****************************************************/
/* EOF                                               */
/*****************************************************/

