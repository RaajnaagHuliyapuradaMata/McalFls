/******************************************************************************/
/* File   : Fls.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "CfgFls.hpp"
#include "Fls_core.hpp"
#include "infFls_Exp.hpp"
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
class module_Fls:
      INTERFACES_EXPORTED_FLS
      public abstract_module
   ,  public class_Fls_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
            Std_TypeReturn          IsInitDone{E_NOT_OK};
      const CfgModule_TypeAbstract* lptrCfg{(CfgModule_TypeAbstract*)NULL_PTR};

   public:
      module_Fls(Std_TypeVersionInfo lVersionInfo) : abstract_module(lVersionInfo){
      }
      FUNC(void, FLS_CODE) InitFunction(
         CONSTP2CONST(CfgModule_TypeAbstract, FLS_CONFIG_DATA, FLS_APPL_CONST) lptrCfgModule
      );
      FUNC(void, FLS_CODE) DeInitFunction (void);
      FUNC(void, FLS_CODE) MainFunction   (void);
      FLS_CORE_FUNCTIONALITIES
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

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_Fls, FLS_VAR) Fls(
   {
#if(STD_ON == _ReSIM)
   char strModuleName[6] = "FLS";
#else
#endif
         FLS_AR_RELEASE_VERSION_MAJOR
      ,  FLS_AR_RELEASE_VERSION_MINOR
      ,  0x00
      ,  0xFF
      ,  0x01
      ,  '0'
      ,  '1'
      ,  '0'
   }
);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#if(STD_ON == _ReSIM)
#include <iostream>
#include <fstream>
using namespace std;
using std::ios;
#else
#endif

FUNC(void, FLS_CODE) module_Fls::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, FLS_CONFIG_DATA, FLS_APPL_CONST) lptrCfgModule
){
#if(STD_ON == Fls_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(NULL_PTR != lptrCfgModule){
         if(STD_HIGH){
            lptrCfg = lptrCfgModule;
#if(STD_ON == _ReSIM)
            std::ifstream fin(
                  "Fls.hex" //argv[1]
               ,  ios::in
            );

            while(fin){
               string line;
               getline(fin, line);
               cout<<line<<endl;
            }

            fin.close();
#else
#endif
         }
         else{
            lptrCfg = &PBcfgFls;
         }
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

FUNC(void, FLS_CODE) module_Fls::DeInitFunction(void){
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

FUNC(void, FLS_CODE) module_Fls::MainFunction(void){
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

FUNC(void, FLS_CODE) module_Fls::Erase(void){
}

FUNC(void, FLS_CODE) module_Fls::Write(void){
}

FUNC(void, FLS_CODE) module_Fls::Cancel(void){
}

FUNC(void, FLS_CODE) module_Fls::GetStatus(void){
}

FUNC(void, FLS_CODE) module_Fls::GetJobResult(void){
}

FUNC(void, FLS_CODE) module_Fls::Read(void){
}

FUNC(void, FLS_CODE) module_Fls::Compare(void){
}

FUNC(void, FLS_CODE) module_Fls::SetMode(void){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

