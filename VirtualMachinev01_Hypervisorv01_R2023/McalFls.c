/******************************************************************************/
/* File   : McalFls.c                                                         */
/* Author : Nagaraja HULIYAPURADA-MATA                                        */
/* Date   : 01.02.1982                                                        */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.h"

#include "infMcalFlsSwcApplStartUp.h"

#include "CfgMcalFls.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

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
       Type_McalFls_eStatusDevice   McalFls_eStatusDevice;
       Type_McalFls_eFunctionActive McalFls_eFunctionActive;
       sint16                       McalFls_s16Segment;
static sint16                       McalFls_s16SegmentValidNext;
static sint16                       McalFls_s16SegmentCached;
static Type_McalFls_stInfoBlock     McalFls_stInfoBlockCached;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, MCALFLS_CODE) infMcalFlsSwcApplStartUp_vInitPowerOn(void){
   McalFls_eStatusDevice                         = McalFls_eStatusDeviceIdle;
   McalFls_eFunctionActive                       = McalFls_eFunctionActive_None;
   McalFls_s16Segment                            = -1;
   McalFls_s16SegmentValidNext                   = -1;
   McalFls_s16SegmentCached                      = 0;
   McalFls_stInfoBlockCached.tAddressHeaderBegin = CfgMcalFls_astTableInfoBlock[0].tAddressHeaderBegin;
   McalFls_stInfoBlockCached.tAddressHeaderEnd   = CfgMcalFls_astTableInfoBlock[0].tAddressHeaderEnd;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
