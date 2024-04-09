#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_ON 0292
#endif

#ifndef R_FDL_TYPES_H
#define R_FDL_TYPES_H

#include "Types.hpp"

//#define DATAFLASH_BLOCK_ALIG	16
//
//#define DATAFLASHINITIALIZED 0xAAAAAAAA
//
//
//uint32_t readBuf_au32[DATAFLASH_BLOCK_ALIG];
//uint32_t writeBuf_au32[DATAFLASH_BLOCK_ALIG];

typedef struct R_FDL_DESCRIPTOR_T
{
   uint16_t    cpuFrequencyMHz_u16;
   uint16_t    fdlPoolSize_u16;
   uint16_t    eelPoolStart_u16;
   uint16_t    eelPoolSize_u16;
}r_fdl_descriptor_t;

typedef enum R_FDL_STATUS_T
{
    R_FDL_OK                    = 0
   ,   R_FDL_BUSY                  = 1
   ,   R_FDL_SUSPENDED             = 2
   ,   R_FDL_ERR_CONFIGURATION     = 3
   ,   R_FDL_ERR_PARAMETER         = 4
   ,   R_FDL_ERR_PROTECTION        = 5
   ,   R_FDL_ERR_REJECTED          = 6
   ,   R_FDL_ERR_WRITE             = 7
   ,   R_FDL_ERR_ERASE             = 8
   ,   R_FDL_ERR_BLANKCHECK        = 9
   ,   R_FDL_ERR_COMMAND           = 10
   ,   R_FDL_ERR_ECC_SED           = 11
   ,   R_FDL_ERR_ECC_DED           = 12
   ,   R_FDL_ERR_INTERNAL          = 13
   ,   R_FDL_CANCELLED             = 14
}r_fdl_status_t;

typedef enum R_FDL_ACCESS_TYPE_T
{
    R_FDL_ACCESS_NONE           = 0
   ,   R_FDL_ACCESS_USER           = 1
   ,   R_FDL_ACCESS_EEL            = 2
}r_fdl_accessType_t;

typedef enum R_FDL_COMMAND_T
{
    R_FDL_CMD_ERASE             = 0
   ,   R_FDL_CMD_WRITE             = 1
   ,   R_FDL_CMD_BLANKCHECK        = 2
   ,   R_FDL_CMD_READ              = 3,
#if(defined ENABLE_CMD_WRITE16B)
    R_FDL_CMD_WRITE16B          = 4,
#endif
    R_FDL_CMD_PREPARE_ENV       = 5
}r_fdl_command_t;

typedef volatile struct R_FDL_REQUEST_T
{
    r_fdl_command_t     command_enu;
   uint32_t            bufAddr_u32;
   uint32_t            idx_u32;
   uint16_t            cnt_u16;
    r_fdl_accessType_t  accessType_enu;
    r_fdl_status_t      status_enu;
}r_fdl_request_t;

//   RST 4.12.2019 commented out, this is code from truck demo system and not needed here.
//
//
//
//  typedef struct DatenFlashBlock0
//  {
//  	uint32	ulDataFlashInitialized;
//  	uint32	ulProgResettCnt;
//  	uint32	ulProgAttemptCnt;
//  	uint32		ucRefPressureVL;
//  	uint32		ucRefPressureVR;
//  	uint32		ucRefPressureHL;
//  	uint32		ucRefPressureHR;
//  	sint32		usRefTempVL;
//  	sint32		usRefTempVR;
//  	sint32		usRefTempHL;
//  	sint32		usRefTempHR;
//  	uint32	ulNotUsedInBL0[5];
//  }DF_Block0;
//
//  typedef union
//  {
//  	DF_Block0 DF_BL0;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block0)];
//  }tDF_BL0_Decl;
//
//  tDF_BL0_Decl tDFBL0;
//
//  typedef union
//  {
//  	DF_Block0 DF1Byte_BL0;
//    uint8_t ucByteAccess[(uint8_t) sizeof(DF_Block0)];
//  }tDF_BL0_Decl1Byte;
//
//  tDF_BL0_Decl1Byte tDF1Byte_BL0;
//
//
//#define ulProgResettCnt_DF_BL0 tDFBL0.DF_BL0.ulProgResettCnt
//#define ulProgAttemptCnt_DF_BL0 tDFBL0.DF_BL0.ulProgAttemptCnt
//#define ucRefPressureVL_DF tDFBL0.DF_BL0.ucRefPressureVL
//#define ucRefPressureVR_DF tDFBL0.DF_BL0.ucRefPressureVR
//#define ucRefPressureHL_DF tDFBL0.DF_BL0.ucRefPressureHL
//#define ucRefPressureHR_DF tDFBL0.DF_BL0.ucRefPressureHR
//
//
//
//  typedef struct DatenFlashBlock1
//  {
//  	uint32	ulID_Ax1Pos7;
//  	uint32	ulID_Ax2Pos6;
//  	uint32	ulID_Ax2Pos7;
//  	uint32	ulID_Ax3Pos6;
//  	uint32	ulID_Ax3Pos7;
//  	uint32	ulID_Ax4Pos6;
//  	uint32	ulID_Ax4Pos7;
//  	uint32	ulID_Ax5Pos6;
//  	uint32	ulID_Ax5Pos7;
//  	uint32	ulID_Ax6Pos6;
//  	uint32	ulID_Ax6Pos7;
//  	uint32	ulNotUsedInBL0[5];
//  }DF_Block1;
//
//  typedef union
//  {
//  	DF_Block1 DF_BL1;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block1)];
//  }tDF_BL1_Decl;
//
//  tDF_BL1_Decl tDFBL1;
//
//
//
//
//
//
//  typedef volatile struct DatenFlashBlock2
//  {
//  	uint32	ulID_Ax1Pos9;
//  	uint32	ulID_Ax2Pos9;
//  	uint32	ulID_Ax2PosA;
//  	uint32	ulID_Ax3Pos9;
//  	uint32	ulID_Ax3PosA;
//  	uint32	ulID_Ax4Pos9;
//  	uint32	ulID_Ax4PosA;
//  	uint32	ulID_Ax5Pos9;
//  	uint32	ulID_Ax5PosA;
//  	uint32	ulID_Ax6Pos9;
//  	uint32	ulID_Ax6PosA;
//  	uint32	ulNotUsedInBL0[5];
//  }DF_Block2;
//
//  typedef union
//  {
//  	DF_Block2 DF_BL2;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block2)];
//  }tDF_BL2_Decl;
//
//  tDF_BL2_Decl tDFBL2;
//
//
//
//#ifdef as_DFBlock1
//
//
//  typedef struct DatenFlashBlock1
//  {
//  	uint8	ucCalPressureREL1;
//  	uint8	ucCalPressureREL2;
//  	uint8	ucCalPressureREL3;
//  	uint8	ucCalPressureREL4;
//  	uint8	ucCalPressureREL5;
//  	uint8	ucCalPressureREL6;
//  	uint8	ucCalPressureREL7;
//  	uint8	ucCalPressureREL8;
//  	uint8	ucCalPressureREL9;
//  	uint8	ucCalPressureREL10;
//  	uint8	ucCalPressureREL11;
//  	uint8	ucCalPressureREL12;
//  	uint8	ucCalPressureREL13;
//  	uint8	ucCalPressureREL14;
//  	uint8	ucCalPressureREL15;
//  	uint8	ucCalPressureREL16;
//  
//  	uint8	ucCalPressureRER1;
//  	uint8	ucCalPressureRER2;
//  	uint8	ucCalPressureRER3;
//  	uint8	ucCalPressureRER4;
//  	uint8	ucCalPressureRER5;
//  	uint8	ucCalPressureRER6;
//  	uint8	ucCalPressureRER7;
//  	uint8	ucCalPressureRER8;
//  	uint8	ucCalPressureRER9;
//  	uint8	ucCalPressureRER10;
//  	uint8	ucCalPressureRER11;
//  	uint8	ucCalPressureRER12;
//  	uint8	ucCalPressureRER13;
//  	uint8	ucCalPressureRER14;
//  	uint8	ucCalPressureRER15;
//  	uint8	ucCalPressureRER16;
//
//  	sint8 scTempREL1;
//  	sint8 scTempREL2;
//  	sint8 scTempREL3;
//  	sint8 scTempREL4;
//  	sint8 scTempREL5;
//  	sint8 scTempREL6;
//  	sint8 scTempREL7;
//  	sint8 scTempREL8;
//  	sint8 scTempREL9;
//  	sint8 scTempREL10;
//  	sint8 scTempREL11;
//  	sint8 scTempREL12;
//  	sint8 scTempREL13;
//  	sint8 scTempREL14;
//  	sint8 scTempREL15;
//  	sint8 scTempREL16;
//
//  	sint8 scTempRER1;
//  	sint8 scTempRER2;
//  	sint8 scTempRER3;
//  	sint8 scTempRER4;
//  	sint8 scTempRER5;
//  	sint8 scTempRER6;
//  	sint8 scTempRER7;
//  	sint8 scTempRER8;
//  	sint8 scTempRER9;
//  	sint8 scTempRER10;
//  	sint8 scTempRER11;
//  	sint8 scTempRER12;
//  	sint8 scTempRER14;
//  	sint8 scTempRER15;
//  	sint8 scTempRER16;
//
//  }DF_Block1;
//
//  typedef union
//  {
//  	DF_Block1 DF_BL1;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block1)];
//  }tDF_BL1_Decl;
//
//  tDF_BL1_Decl tDFBL1;
//
//#define ucCalPressureREL1DF	tDFBL1.DF_BL1.ucCalPressureREL1
//#define ucCalPressureREL2DF	tDFBL1.DF_BL1.ucCalPressureREL2
//#define ucCalPressureREL3DF	tDFBL1.DF_BL1.ucCalPressureREL3
//#define ucCalPressureREL4DF	tDFBL1.DF_BL1.ucCalPressureREL4
//#define ucCalPressureREL5DF	tDFBL1.DF_BL1.ucCalPressureREL5
//#define ucCalPressureREL6DF	tDFBL1.DF_BL1.ucCalPressureREL6
//#define ucCalPressureREL7DF	tDFBL1.DF_BL1.ucCalPressureREL7
//#define ucCalPressureREL8DF	tDFBL1.DF_BL1.ucCalPressureREL8
//#define ucCalPressureREL9DF	tDFBL1.DF_BL1.ucCalPressureREL9
//#define ucCalPressureREL10DF	tDFBL1.DF_BL1.ucCalPressureREL10
//#define ucCalPressureREL11DF	tDFBL1.DF_BL1.ucCalPressureREL11
//#define ucCalPressureREL12DF	tDFBL1.DF_BL1.ucCalPressureREL12
//#define ucCalPressureREL13DF	tDFBL1.DF_BL1.ucCalPressureREL13
//#define ucCalPressureREL14DF	tDFBL1.DF_BL1.ucCalPressureREL14
//#define ucCalPressureREL15DF	tDFBL1.DF_BL1.ucCalPressureREL15
//#define ucCalPressureREL16DF	tDFBL1.DF_BL1.ucCalPressureREL16
//
//#define ucCalPressureRER1DF	tDFBL1.DF_BL1.ucCalPressureRER1
//#define ucCalPressureRER2DF	tDFBL1.DF_BL1.ucCalPressureRER2
//#define ucCalPressureRER3DF	tDFBL1.DF_BL1.ucCalPressureRER3
//#define ucCalPressureRER4DF	tDFBL1.DF_BL1.ucCalPressureRER4
//#define ucCalPressureRER5DF	tDFBL1.DF_BL1.ucCalPressureRER5
//#define ucCalPressureRER6DF	tDFBL1.DF_BL1.ucCalPressureRER6
//#define ucCalPressureRER7DF	tDFBL1.DF_BL1.ucCalPressureRER7
//#define ucCalPressureRER8DF	tDFBL1.DF_BL1.ucCalPressureRER8
//#define ucCalPressureRER9DF	tDFBL1.DF_BL1.ucCalPressureRER9
//#define ucCalPressureRER10DF	tDFBL1.DF_BL1.ucCalPressureRER10
//#define ucCalPressureRER11DF	tDFBL1.DF_BL1.ucCalPressureRER11
//#define ucCalPressureRER12DF	tDFBL1.DF_BL1.ucCalPressureRER12
//#define ucCalPressureRER13DF	tDFBL1.DF_BL1.ucCalPressureRER13
//#define ucCalPressureRER14DF	tDFBL1.DF_BL1.ucCalPressureRER14
//#define ucCalPressureRER15DF	tDFBL1.DF_BL1.ucCalPressureRER15
//#define ucCalPressureRER16DF	tDFBL1.DF_BL1.ucCalPressureRER16
//
//#define scTempREL1DF	tDFBL1.DF_BL1.scTempREL1
//#define scTempREL2DF	tDFBL1.DF_BL1.scTempREL2
//#define scTempREL3DF	tDFBL1.DF_BL1.scTempREL3
//#define scTempREL4DF	tDFBL1.DF_BL1.scTempREL4
//#define scTempREL5DF	tDFBL1.DF_BL1.scTempREL5
//#define scTempREL6DF	tDFBL1.DF_BL1.scTempREL6
//#define scTempREL7DF	tDFBL1.DF_BL1.scTempREL7
//#define scTempREL8DF	tDFBL1.DF_BL1.scTempREL8
//#define scTempREL9DF	tDFBL1.DF_BL1.scTempREL9
//#define scTempREL10DF	tDFBL1.DF_BL1.scTempREL10
//#define scTempREL11DF	tDFBL1.DF_BL1.scTempREL11
//#define scTempREL12DF	tDFBL1.DF_BL1.scTempREL12
//#define scTempREL13DF	tDFBL1.DF_BL1.scTempREL13
//#define scTempREL14DF	tDFBL1.DF_BL1.scTempREL14
//#define scTempREL15DF	tDFBL1.DF_BL1.scTempREL15
//#define scTempREL16DF	tDFBL1.DF_BL1.scTempREL16
//
//#define scTempRER1DF	tDFBL1.DF_BL1.scTempRER1
//#define scTempREL3DF	tDFBL1.DF_BL1.scTempRER3
//#define scTempRER4DF	tDFBL1.DF_BL1.scTempRER4
//#define scTempRER5DF	tDFBL1.DF_BL1.scTempRER5
//#define scTempRER6DF	tDFBL1.DF_BL1.scTempRER6
//#define scTempRER7DF	tDFBL1.DF_BL1.scTempRER7
//#define scTempRER8DF	tDFBL1.DF_BL1.scTempRER8
//#define scTempRER9DF	tDFBL1.DF_BL1.scTempRER9
//#define scTempRER10DF	tDFBL1.DF_BL1.scTempRER10
//#define scTempRER11DF	tDFBL1.DF_BL1.scTempRER11
//#define scTempRER12DF	tDFBL1.DF_BL1.scTempRER12
//#define scTempRER13DF	tDFBL1.DF_BL1.scTempRER13
//#define scTempRER14DF	tDFBL1.DF_BL1.scTempRER14
//#define scTempRER15DF	tDFBL1.DF_BL1.scTempRER15
//#define scTempRER16DF	tDFBL1.DF_BL1.scTempRER16
//
//#endif
//
//
//
//
//
//
//  typedef volatile struct DatenFlashBlock3
//  {
//  	uint32	ucRefP4ID_Ax1Pos7;
//  	uint32	ucRefP4ID_Ax2Pos6;
//  	uint32	ucRefP4ID_Ax2Pos7;
//  	uint32	ucRefP4ID_Ax3Pos6;
//  	uint32	ucRefP4ID_Ax3Pos7;
//  	uint32	ucRefP4ID_Ax4Pos6;
//  	uint32	ucRefP4ID_Ax4Pos7;
//  	uint32	ucRefP4ID_Ax5Pos6;
//  	uint32	ucRefP4ID_Ax5Pos7;
//  	uint32	ucRefP4ID_Ax6Pos6;
//  	uint32	ucRefP4ID_Ax6Pos7;
//  	uint32	ulNotUsedInBL0[5];
//  }DF_Block3;
//
//  typedef union
//  {
//  	DF_Block3 DF_BL3;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block3)];
//  }tDF_BL3_Decl;
//
//  volatile tDF_BL3_Decl tDFBL3;
//
//
//
//
//
//  typedef volatile struct DatenFlashBlock4
//  {
//  	uint32	ucRefP4ID_Ax1Pos9;
//  	uint32	ucRefP4ID_Ax2Pos9;
//  	uint32	ucRefP4ID_Ax2PosA;
//  	uint32	ucRefP4ID_Ax3Pos9;
//  	uint32	ucRefP4ID_Ax3PosA;
//  	uint32	ucRefP4ID_Ax4Pos9;
//  	uint32	ucRefP4ID_Ax4PosA;
//  	uint32	ucRefP4ID_Ax5Pos9;
//  	uint32	ucRefP4ID_Ax5PosA;
//  	uint32	ucRefP4ID_Ax6Pos9;
//  	uint32	ucRefP4ID_Ax6PosA;
//  	uint32	ulNotUsedInBL0[5];
//  }DF_Block4;
//
//  typedef union
//  {
//  	DF_Block4 DF_BL4;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block4)];
//  }tDF_BL4_Decl;
//
//  volatile tDF_BL4_Decl tDFBL4;
//
//
//
//
//  typedef volatile struct DatenFlashBlock5
//  {
//  	uint32	ucRefTemp4ID_Ax1Pos7;
//  	uint32	ucRefTemp4ID_Ax2Pos6;
//  	uint32	ucRefTemp4ID_Ax2Pos7;
//  	uint32	ucRefTemp4ID_Ax3Pos6;
//  	uint32	ucRefTemp4ID_Ax3Pos7;
//  	uint32	ucRefTemp4ID_Ax4Pos6;
//  	uint32	ucRefTemp4ID_Ax4Pos7;
//  	uint32	ucRefTemp4ID_Ax5Pos6;
//  	uint32	ucRefTemp4ID_Ax5Pos7;
//  	uint32	ucRefTemp4ID_Ax6Pos6;
//  	uint32	ucRefTemp4ID_Ax6Pos7;
//  	uint32	ulNotUsedInBL0[5];
//  }DF_Block5;
//
//  typedef union
//  {
//  	DF_Block5 DF_BL5;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block5)];
//  }tDF_BL5_Decl;
//
//  volatile tDF_BL5_Decl tDFBL5;
//
//
//
//
//  typedef volatile struct DatenFlashBlock6
//  {
//  	uint32	ucRefTemp4ID_Ax1Pos9;
//  	uint32	ucRefTemp4ID_Ax2Pos9;
//  	uint32	ucRefTemp4ID_Ax2PosA;
//  	uint32	ucRefTemp4ID_Ax3Pos9;
//  	uint32	ucRefTemp4ID_Ax3PosA;
//  	uint32	ucRefTemp4ID_Ax4Pos9;
//  	uint32	ucRefTemp4ID_Ax4PosA;
//  	uint32	ucRefTemp4ID_Ax5Pos9;
//  	uint32	ucRefTemp4ID_Ax5PosA;
//  	uint32	ucRefTemp4ID_Ax6Pos9;
//  	uint32	ucRefTemp4ID_Ax6PosA;
//  	uint32	ulNotUsedInBL0[5];
//  }DF_Block6;
//
//  typedef union
//  {
//  	DF_Block6 DF_BL6;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block6)];
//  }tDF_BL6_Decl;
//
//  volatile tDF_BL6_Decl tDFBL6;
//
//
//
//
//  typedef volatile struct DatenFlashBlock7
//  {
//  	uint32_t            ulNotUsedInBL7[16];
//  }DF_Block7;
//
//  typedef union
//  {
//  	DF_Block7 DF_BL7;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block7)];
//  }tDF_BL7_Decl;
//
//  volatile tDF_BL7_Decl tDFBL7;
//
//
//
//
//  typedef volatile struct DatenFlashBlock8
//  {
//  	uint32_t            ulNotUsedInBL8[16];
//  }DF_Block8;
//
//  typedef union
//  {
//  	DF_Block8 DF_BL8;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block8)];
//  }tDF_BL8_Decl;
//
//  volatile tDF_BL8_Decl tDFBL8;
//
//
//
//
//  typedef volatile struct DatenFlashBlock9
//  {
//  	uint32_t            ulNotUsedInBL9[16];
//  }DF_Block9;
//
//  typedef union
//  {
//  	DF_Block9 DF_BL9;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block9)];
//  }tDF_BL9_Decl;
//
//  volatile tDF_BL9_Decl tDFBL9;
//
//
//
//
//  typedef volatile struct DatenFlashBlock10
//  {
//  	uint32_t            ulNotUsedInBL10[16];
//  }DF_Block10;
//
//  typedef union
//  {
//  	DF_Block10 DF_BL10;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block10)];
//  }tDF_BL10_Decl;
//
//  volatile tDF_BL10_Decl tDFBL10;
//
//
//
//
//  typedef volatile struct DatenFlashBlock11
//  {
//  	uint32_t            ulNotUsedInBL11[16];
//  }DF_Block11;
//
//  typedef union
//  {
//  	DF_Block11 DF_BL11;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block11)];
//  }tDF_BL11_Decl;
//
//  volatile tDF_BL11_Decl tDFBL11;
//
//
//
//
//  typedef volatile struct DatenFlashBlock12
//  {
//  	uint32_t            ulNotUsedInBL12[16];
//  }DF_Block12;
//
//  typedef union
//  {
//  	DF_Block12 DF_BL12;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block12)];
//  }tDF_BL12_Decl;
//
//  volatile tDF_BL12_Decl tDFBL12;
//
//
//
//
//  typedef volatile struct DatenFlashBlock13
//  {
//  	uint32_t            ulNotUsedInBL13[16];
//  }DF_Block13;
//
//  typedef union
//  {
//  	DF_Block13 DF_BL13;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block13)];
//  }tDF_BL13_Decl;
//
//  volatile tDF_BL13_Decl tDFBL13;
//
//
//
//
//  typedef volatile struct DatenFlashBlock14
//  {
//  	uint32_t            ulNotUsedInBL14[16];
//  }DF_Block14;
//
//  typedef union
//  {
//  	DF_Block14 DF_BL14;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block14)];
//  }tDF_BL14_Decl;
//
//  volatile tDF_BL14_Decl tDFBL14;
//
//
//
//
//  typedef volatile struct DatenFlashBlock15
//  {
//  	uint32_t            ulNotUsedInBL15[16];
//  }DF_Block15;
//
//  typedef union
//  {
//  	DF_Block15 DF_BL15;
//    uint32_t ulByteAccess[(uint32_t) sizeof(DF_Block15)];
//  }tDF_BL15_Decl;
//
//  volatile tDF_BL15_Decl tDFBL15;
//
//

#endif

