/*****************************************************/
/* File   : Fls.cpp                                  */
/* Author : Naagraaj HM                              */
/*****************************************************/

/*****************************************************/
/* #INCLUDES                                         */
/*****************************************************/
#include "module.h"
#include "Fls_EcuM.h"
#include "Fls_SchM.h"
#include "Fls_Unused.h"

/*****************************************************/
/* #DEFINES                                          */
/*****************************************************/

/*****************************************************/
/* MACROS                                            */
/*****************************************************/

/*****************************************************/
/* TYPEDEFS                                          */
/*****************************************************/
class module_Fls:
      public abstract_module
{
   public:
      FUNC(void, FLS_CODE) InitFunction   (void);
      FUNC(void, FLS_CODE) DeInitFunction (void);
      FUNC(void, FLS_CODE) MainFunction   (void);
};

/*****************************************************/
/* CONSTS                                            */
/*****************************************************/

/*****************************************************/
/* PARAMS                                            */
/*****************************************************/

/*****************************************************/
/* OBJECTS                                           */
/*****************************************************/
module_Fls     Fls;
infEcuMClient* gptrinfEcuMClient_Fls = &Fls;
infSchMClient* gptrinfSchMClient_Fls = &Fls;

/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
FUNC(void, FLS_CODE) module_Fls::InitFunction(void){
}

FUNC(void, FLS_CODE) module_Fls::DeInitFunction(void){
}

FUNC(void, FLS_CODE) module_Fls::MainFunction(void){
}

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

FUNC(void, FLS_CODE) class_Fls_Unused::GetVersionInfo(void){
}

/*****************************************************/
/* EOF                                               */
/*****************************************************/

