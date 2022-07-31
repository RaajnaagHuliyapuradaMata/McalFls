/******************************************************************************/
/* File   : Fls.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "Fls.hpp"
#include "infFls_Imp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define FLS_AR_RELEASE_VERSION_MAJOR                                           4
#define FLS_AR_RELEASE_VERSION_MINOR                                           3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(FLS_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible FLS_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(FLS_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible FLS_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#if(STD_ON == _ReSIM)
#include <iostream>
#include <fstream>
using namespace std;
using std::ios;

#include "Fm.hpp"
#else
#endif

FUNC(void, FLS_CODE) module_Fls::InitFunction(
      CONSTP2CONST(ConstModule_TypeAbstract, FLS_CONST,       FLS_APPL_CONST) lptrConstModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   FLS_CONFIG_DATA, FLS_APPL_CONST) lptrCfgModule
){
#if(STD_ON == Fls_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(
            (NULL_PTR != lptrConstModule)
         && (NULL_PTR != lptrCfgModule)
      ){
         lptrConst = (const ConstFls_Type*)lptrConstModule;
         lptrCfg   = lptrCfgModule;
      }
      else{
#if(STD_ON == Fls_DevErrorDetect)
         Det_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
#if(STD_ON == _ReSIM)
//      if(FALSE){
         //TBD: Read from Flash -> CfgGen_Fls
//      }
//      else{
         //TBD: Read from File -> CfgGen_Fls
           uint8 au8Data[32768];
           Fm Fls;
           Fls.Read(au8Data);
//      }
#else
#endif
#if(STD_ON == Fls_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == Fls_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  FLS_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, FLS_CODE) module_Fls::DeInitFunction(
   void
){
#if(STD_ON == Fls_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == Fls_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == Fls_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  FLS_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, FLS_CODE) module_Fls::MainFunction(
   void
){
#if(STD_ON == Fls_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == Fls_InitCheck)
   }
   else{
#if(STD_ON == Fls_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  FLS_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, FLS_CODE) module_Fls::Erase(
   void
){
}

FUNC(void, FLS_CODE) module_Fls::Write(
   void
){
}

FUNC(void, FLS_CODE) module_Fls::Cancel(
   void
){
}

FUNC(void, FLS_CODE) module_Fls::GetStatus(
   void
){
}

FUNC(void, FLS_CODE) module_Fls::GetJobResult(
   void
){
}

FUNC(void, FLS_CODE) module_Fls::Read(
   void
){
}

FUNC(void, FLS_CODE) module_Fls::Compare(
   void
){
}

FUNC(void, FLS_CODE) module_Fls::SetMode(
   void
){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

