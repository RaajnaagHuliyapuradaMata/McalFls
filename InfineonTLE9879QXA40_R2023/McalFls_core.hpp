#pragma once
/******************************************************************************/
/* File   : McalFls_core.hpp                                                      */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "CompilerCfg_McalFls.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define MCALFLS_CORE_FUNCTIONALITIES                                               \
              FUNC(void, MCALFLS_CODE) Erase          (void);                      \
              FUNC(void, MCALFLS_CODE) Write          (void);                      \
              FUNC(void, MCALFLS_CODE) McalCancel         (void);                      \
              FUNC(void, MCALFLS_CODE) GetStatus      (void);                      \
              FUNC(void, MCALFLS_CODE) GetJobResult   (void);                      \
              FUNC(void, MCALFLS_CODE) Read           (void);                      \
              FUNC(void, MCALFLS_CODE) ServiceCompare        (void);                      \
              FUNC(void, MCALFLS_CODE) SetMode        (void);                      \

#define MCALFLS_CORE_FUNCTIONALITIES_VIRTUAL                                       \
      virtual FUNC(void, MCALFLS_CODE) Erase          (void) = 0;                  \
      virtual FUNC(void, MCALFLS_CODE) Write          (void) = 0;                  \
      virtual FUNC(void, MCALFLS_CODE) McalCancel         (void) = 0;                  \
      virtual FUNC(void, MCALFLS_CODE) GetStatus      (void) = 0;                  \
      virtual FUNC(void, MCALFLS_CODE) GetJobResult   (void) = 0;                  \
      virtual FUNC(void, MCALFLS_CODE) Read           (void) = 0;                  \
      virtual FUNC(void, MCALFLS_CODE) ServiceCompare        (void) = 0;                  \
      virtual FUNC(void, MCALFLS_CODE) SetMode        (void) = 0;                  \

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class class_McalFls_Functionality{
   public:
      MCALFLS_CORE_FUNCTIONALITIES_VIRTUAL
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

