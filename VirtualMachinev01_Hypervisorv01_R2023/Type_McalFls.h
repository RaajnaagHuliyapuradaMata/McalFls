#pragma once
/******************************************************************************/
/* File   : Type_McalFls.h                                                    */
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
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
   McalFls_eStatusDeviceIdle = 0xFFu
}Type_McalFls_eStatusDevice;

typedef enum{
      McalFls_eFunctionActive_None
   ,  McalFls_eFunctionActive_Init
   ,  McalFls_eFunctionActive_Deinit
   ,  McalFls_eFunctionActive_Write
   ,  McalFls_eFunctionActive_Erase
   ,  McalFls_eFunctionActive_Verify
}Type_McalFls_eFunctionActive;

typedef uint32 SwcServiceStartUp_tAddressHeader;

typedef struct{
  SwcServiceStartUp_tAddressHeader tAddressHeaderBegin;
  SwcServiceStartUp_tAddressHeader tAddressHeaderEnd;
}Type_McalFls_stInfoBlock;

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
