#pragma once
/******************************************************************************/
/* File   : McalFls.hpp                                                           */
/*                                                                            */
/* Author : Nagaraja HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Nagaraja HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/NagarajaHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "ConstMcalFls.hpp"
#include "CfgMcalFls.hpp"
#include "McalFls_core.hpp"
#include "infMcalFls_Exp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_McalFls:
      INTERFACES_EXPORTED_MCALFLS
      public abstract_module
   ,  public class_McalFls_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
      const ConstMcalFls_Type* lptrConst = (ConstMcalFls_Type*)NULL_PTR;

   public:
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
      FUNC(void, MCALFLS_CODE) InitFunction(
            CONSTP2CONST(ConstModule_TypeAbstract, MCALFLS_CONST,       MCALFLS_APPL_CONST) lptrConstModule
         ,  CONSTP2CONST(CfgModule_TypeAbstract,   MCALFLS_CONFIG_DATA, MCALFLS_APPL_CONST) lptrCfgModule
      );
      FUNC(void, MCALFLS_CODE) DeInitFunction (void);
      FUNC(void, MCALFLS_CODE) MainFunction   (void);
      MCALFLS_CORE_FUNCTIONALITIES
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
extern VAR(module_McalFls, MCALFLS_VAR) McalFls;

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

