#pragma once
/******************************************************************************/
/* File   : McalFls_core.hpp                                                      */
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
#include "CompilerCfg_McalFls.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define FLS_CORE_FUNCTIONALITIES                                               \
              FUNC(void, FLS_CODE) Erase          (void);                      \
              FUNC(void, FLS_CODE) Write          (void);                      \
              FUNC(void, FLS_CODE) McalCancel         (void);                      \
              FUNC(void, FLS_CODE) GetStatus      (void);                      \
              FUNC(void, FLS_CODE) GetJobResult   (void);                      \
              FUNC(void, FLS_CODE) Read           (void);                      \
              FUNC(void, FLS_CODE) ServiceCompare        (void);                      \
              FUNC(void, FLS_CODE) SetMode        (void);                      \

#define FLS_CORE_FUNCTIONALITIES_VIRTUAL                                       \
      virtual FUNC(void, FLS_CODE) Erase          (void) = 0;                  \
      virtual FUNC(void, FLS_CODE) Write          (void) = 0;                  \
      virtual FUNC(void, FLS_CODE) McalCancel         (void) = 0;                  \
      virtual FUNC(void, FLS_CODE) GetStatus      (void) = 0;                  \
      virtual FUNC(void, FLS_CODE) GetJobResult   (void) = 0;                  \
      virtual FUNC(void, FLS_CODE) Read           (void) = 0;                  \
      virtual FUNC(void, FLS_CODE) ServiceCompare        (void) = 0;                  \
      virtual FUNC(void, FLS_CODE) SetMode        (void) = 0;                  \

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class class_McalFls_Functionality{
   public:
      FLS_CORE_FUNCTIONALITIES_VIRTUAL
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

