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
      public abstract_module
   ,  public class_Fls_Functionality
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
   if(E_OK == IsInitDone){
#if(STD_ON == Fls_DevErrorDetect)
      Det_ReportError(
      0 //TBD: IdModule
   ,  0 //TBD: IdInstance
   ,  0 //TBD: IdApi
   ,  0 //TBD: IdError
      );
#endif
   }
   else{
#endif
      if(NULL_PTR == lptrCfgModule){
#if(STD_ON == Fls_DevErrorDetect)
         Det_ReportError(
      0 //TBD: IdModule
   ,  0 //TBD: IdInstance
   ,  0 //TBD: IdApi
   ,  0 //TBD: IdError
         );
#endif
      }
      else{
         if(STD_LOW){
// check lptrCfgModule for memory faults
            lptrCfg = lptrCfgModule;
         }
         else{
// use PBcfgCanIf as back-up configuration
            lptrCfg = &PBcfgFls;

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
      }
      IsInitDone = E_OK;
#if(STD_ON == Fls_InitCheck)
   }
#endif
}

FUNC(void, FLS_CODE) module_Fls::DeInitFunction(void){
#if(STD_ON == Fls_InitCheck)
   if(E_OK != IsInitDone){
#if(STD_ON == Fls_DevErrorDetect)
      Det_ReportError(
      0 //TBD: IdModule
   ,  0 //TBD: IdInstance
   ,  0 //TBD: IdApi
   ,  0 //TBD: IdError
      );
#endif
   }
   else{
#endif
      IsInitDone = E_NOT_OK;
#if(STD_ON == Fls_InitCheck)
   }
#endif
}

FUNC(void, FLS_CODE) module_Fls::MainFunction(void){
#if(STD_ON == Fls_InitCheck)
   if(E_OK != IsInitDone){
#if(STD_ON == Fls_DevErrorDetect)
      Det_ReportError(
      0 //TBD: IdModule
   ,  0 //TBD: IdInstance
   ,  0 //TBD: IdApi
   ,  0 //TBD: IdError
      );
#endif
   }
   else{
#endif
#if(STD_ON == Fls_InitCheck)
   }
#endif
}

FUNC(void, FLS_CODE) class_Fls_Functionality::Erase(void){
}

FUNC(void, FLS_CODE) class_Fls_Functionality::Write(void){
}

FUNC(void, FLS_CODE) class_Fls_Functionality::Cancel(void){
}

FUNC(void, FLS_CODE) class_Fls_Functionality::GetStatus(void){
}

FUNC(void, FLS_CODE) class_Fls_Functionality::GetJobResult(void){
}

FUNC(void, FLS_CODE) class_Fls_Functionality::Read(void){
}

FUNC(void, FLS_CODE) class_Fls_Functionality::Compare(void){
}

FUNC(void, FLS_CODE) class_Fls_Functionality::SetMode(void){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

