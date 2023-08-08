#ifdef __cplusplus
extern "C"
{
#endif


#include "flashdrv.hpp"
#include "r_typedefs.hpp"
# include "CfgMcalFls_Fcl.hpp"
# include "r_fcl_types.hpp"
# include "r_fcl_global.hpp"
# include "r_fcl.hpp"
# include "r_fcl_env.hpp"

#if((FBLDRVFLASH_RH850RV40HIS_VERSION != 0x0109u)          || \
     (FBLDRVFLASH_RH850RV40HIS_RELEASE_VERSION != 0x00u))
# error "Error in flashdrv.c: Source and header file versions are inconsistent!!"
#endif

# define FLASHLIB_NULL                     R_FCL_NULL
# define FLASHLIB_USERBOOT_AREA_SELECT     R_FCL_USERBOOT_AREA_SELECT

# define FLASHLIB_CMD_PREPARE_ENV          R_FCL_CMD_PREPARE_ENV
# define FLASHLIB_CMD_CODEF_ERASE          R_FCL_CMD_ERASE
# define FLASHLIB_CMD_CODEF_WRITE          R_FCL_CMD_WRITE
# define FLASHLIB_CMD_ENABLE_LOCKBITS      R_FCL_CMD_ENABLE_LOCKBITS
# define FLASHLIB_CMD_DISABLE_LOCKBITS     R_FCL_CMD_DISABLE_LOCKBITS
# define FLASHLIB_CMD_GET_BLOCK_CNT        R_FCL_CMD_GET_BLOCK_CNT
# define FLASHLIB_CMD_GET_BLOCK_END_ADDR   R_FCL_CMD_GET_BLOCK_END_ADDR
# define FLASHLIB_CMD_SET_RESET_VECTOR     R_FCL_CMD_SET_RESET_VECTOR
# define FLASHLIB_CMD_GET_RESET_VECTOR     R_FCL_CMD_GET_RESET_VECTOR
# define FLASHLIB_CMD_SET_OPB              R_FCL_CMD_SET_OPB
# define FLASHLIB_CMD_GET_OPB              R_FCL_CMD_GET_OPB

# define FLASHLIB_OK                       R_FCL_OK
# define FLASHLIB_BUSY                     R_FCL_BUSY

# define FlashLibInit                      R_FCL_Init
# define FlashLibExecute                   R_FCL_Execute
# define FlashLibHandler                   R_FCL_Handler

# if !defined( R_FLI_USERBOOT_AREA_START )
#  error R_FLI_USERBOOT_AREA_START not defined by current version of library
# elif( R_FLI_USERBOOT_AREA_START != 0x01000000u )
#  error R_FLI_USERBOOT_AREA_START has unexpected value
# endif
# if !defined( R_FLI_USERBOOT_AREA_END )
#  error R_FLI_USERBOOT_AREA_END not defined by current version of library
# elif( R_FLI_USERBOOT_AREA_END != 0x01007FFFu )
#  error R_FLI_USERBOOT_AREA_END has unexpected value
# endif
# if !defined( R_FLI_BLOCK_SIZE )
#  error R_FLI_BLOCK_SIZE not defined by current version of library
# elif( R_FLI_BLOCK_SIZE != 0x8000u )
#  error R_FLI_BLOCK_SIZE has unexpected value
# endif
# if !defined( FLASHLIB_USERBOOT_AREA_SELECT )
#  error FLASHLIB_USERBOOT_AREA_SELECT not defined by current version of library
# elif( FLASHLIB_USERBOOT_AREA_SELECT != 0x80000000u )
#  error FLASHLIB_USERBOOT_AREA_SELECT has unexpected value
# endif

#define FLASH_MAX_CORES_RESET_VECTOR      4u

#define FLASH_NUM_OPTIONBYTES             8u

typedef struct tagFlashHeader
{
   tFlashUint8    version;
   tFlashUint8    reserved;
   tFlashUint8    maskType;
   tFlashUint8    CPUType;
   tFlashFct      flashInitFct;
   tFlashFct      flashDeinitFct;
   tFlashFct      flashEraseFct;
   tFlashFct      flashWriteFct;
#if defined( FLASH_ENABLE_SET_RESETVECTOR_API )
   tFlashFct      flashSetResetFct;
#endif
# if defined ( FLASH_ENABLE_OPTIONBYTE_API )
   tFlashFct      flashSetOpbFct;
   tFlashFct      flashGetOpbFct;
# endif
}tFlashHeader;

typedef r_fcl_request_t    tFlashLibRequest;
typedef r_fcl_descriptor_t tFlashLibDescriptor;

void ExpFlashInit ( tFlashParam * flashParam );
void ExpFlashDeinit ( tFlashParam * flashParam );
void ExpFlashErase ( tFlashParam * flashParam );
void ExpFlashWrite ( tFlashParam * flashParam );
#if defined( FLASH_ENABLE_SET_RESETVECTOR_API )
void ExpFlashSetResetVector ( tFlashParam * flashParam );
#endif
# if defined( FLASH_ENABLE_OPTIONBYTE_API )
void ExpFlashSetOptionByte ( tFlashParam * flashParam );
void ExpFlashGetOptionByte ( tFlashParam * flashParam );
# endif

void AsmDummy( void );
void FblDrvFlashSaveCurFblBasePtr( void );
void FblDrvFlashSetCurFlashDrvBasePtr( void );
void FblDrvFlashRestoreCurFblBasePtr( void );
tFlashUint8 FblDrvFlashCallWatchdog( tFlashUint8 (* wdTriggerFct)(void) );
static tFlashUint8 FblDrvFlashHandleWD( void );
static tFlashUint8 FblDrvFlashGetBlockByAddr( tFlashUint32 address, volatile tFlashUint32 * block );

# define NOINIT
# define BREL

BREL NOINIT tFlashParam* pflashParam;

BREL NOINIT unsigned int currentFblGP;
BREL NOINIT unsigned int currentFblTP;
BREL NOINIT unsigned int currentFblEP;

# pragma ghs startdata
# pragma ghs section rodata=".signature"

const tFlashHeader flashHeader =
{
   FLASH_DRIVER_VERSION_INTERFACE,
   0x00u,
   FLASH_DRIVER_VERSION_MASKTYPE,
   FLASH_DRIVER_VERSION_MCUTYPE,
   &ExpFlashInit,
   &ExpFlashDeinit,
   &ExpFlashErase,
   &ExpFlashWrite
#if defined( FLASH_ENABLE_SET_RESETVECTOR_API )
  ,&ExpFlashSetResetVector
#endif
# if defined( FLASH_ENABLE_OPTIONBYTE_API )
  ,&ExpFlashSetOptionByte
  ,&ExpFlashGetOptionByte
# endif
};

# pragma ghs section rodata=default
# pragma ghs enddata

void AsmDummy( void ){
#pragma asm
--
--
--
--
_FblDrvFlashSaveCurFblBasePtr:
--
  addi -4,sp,sp
  st.w r19,0[sp]
--
  movhi hi(_currentFblEP),zero,r19
  movea lo(_currentFblEP),r19,r19
  st.w ep,0[r19]
  movhi hi(_currentFblGP),zero,r19
  movea lo(_currentFblGP),r19,r19
  st.w gp,0[r19]
  movhi hi(_currentFblTP),zero,r19
  movea lo(_currentFblTP),r19,r19
  st.w r5,0[r19]
--
  ld.w 0[sp],r19
  addi 4,sp,sp
  jmp [lp]

--
--
--
_FblDrvFlashSetCurFlashDrvBasePtr:
--
   -- Initialisation of the global pointer
   movhi hi(___ghsbegin_sdabase+0x8000),zero,gp
   movea lo(___ghsbegin_sdabase+0x8000),gp,gp
   -- Initialisation of the r5 for SDA optimization
   movhi hi(___ghsbegin_rosdata+0x8000),zero,r5
   movea lo(___ghsbegin_rosdata+0x8000),r5,r5
   -- Initialisation of the ep pointer
   movhi hi(___ghsbegin_tdata),zero,ep
   movea lo(___ghsbegin_tdata),ep,ep
   jmp [lp]

--
--
_FblDrvFlashRestoreCurFblBasePtr:
--
  addi -4,sp,sp
  st.w r19,0[sp]
--
  movhi hi(_currentFblEP),zero,r19
  movea lo(_currentFblEP),r19,r19
  ld.w 0[r19],ep
  movhi hi(_currentFblTP),zero,r19
  movea lo(_currentFblTP),r19,r19
  ld.w 0[r19],r5
  movhi hi(_currentFblGP),zero,r19
  movea lo(_currentFblGP),r19,r19
  ld.w 0[r19],gp
--
  ld.w 0[sp],r19
  addi 4,sp,sp
  jmp [lp]
--
--
--
--
_FblDrvFlashCallWatchdog:
--
  addi -4,sp,sp
  st.w lp,0[sp]
--
--
  jarl _FblDrvFlashRestoreCurFblBasePtr,lp
--
  ld.w 0[sp],lp
  addi 4,sp,sp
--
--
--
--
  jmp [r6]
#pragma endasm
}

static tFlashUint8 FblDrvFlashHandleWD( void ){
   tFlashUint8 tmp;

   tmp = FblDrvFlashCallWatchdog(pflashParam->wdTriggerFct);

   FblDrvFlashSetCurFlashDrvBasePtr();

   return tmp;
}

static tFlashUint8 FblDrvFlashGetBlockByAddr( tFlashUint32 address, volatile tFlashUint32 * block ){
   tFlashLibRequest libRequest;
   tFlashUint32 i;

   tFlashUint32 blockAddr = 0u;
   tFlashUint32 blockCnt = 1u;

   libRequest.command_enu = FLASHLIB_CMD_GET_BLOCK_CNT;
   libRequest.bufferAdd_u32 = (tFlashUint32) &blockCnt;

   FlashLibExecute(&libRequest);
   while (FLASHLIB_BUSY == libRequest.status_enu){
      (void)FblDrvFlashHandleWD();
      FlashLibHandler();
   }
   if(FLASHLIB_OK != libRequest.status_enu){
      return kFlashFailed;
   }

   libRequest.command_enu = FLASHLIB_CMD_GET_BLOCK_END_ADDR;
   libRequest.bufferAdd_u32 = (tFlashUint32) &blockAddr;

   for (i = 0u; i < blockCnt; i++){
      (void)FblDrvFlashHandleWD();
      libRequest.idx_u32 = i;
      FlashLibExecute(&libRequest);
      while (FLASHLIB_BUSY == libRequest.status_enu)
      {
         (void)FblDrvFlashHandleWD();
         FlashLibHandler();
      }

      if(FLASHLIB_OK != libRequest.status_enu)
      {
         return kFlashFailed;
      }

      if(address <= blockAddr)
      {
         *block = i;
         return kFlashOk;
      }
   }

   if((R_FLI_USERBOOT_AREA_START <= address) && (R_FLI_USERBOOT_AREA_END >= address)){
      *block = FLASHLIB_USERBOOT_AREA_SELECT;
      return kFlashOk;
   }

   return kFlashFailed;
}

void ExpFlashInit ( tFlashParam * flashParam ){
   tFlashLibRequest libRequest;
   tFlashUint32 index;

   tFlashLibDescriptor flashLibConfig;

   FblDrvFlashSaveCurFblBasePtr();
   FblDrvFlashSetCurFlashDrvBasePtr();

   flashParam->errorCode = kFlashInitFailed;

   pflashParam = flashParam;

   flashParam->majorVersion         = FLASH_DRIVER_VERSION_MAJOR;
   flashParam->minorVersion         = FLASH_DRIVER_VERSION_MINOR;
   flashParam->patchLevel           = FLASH_DRIVER_VERSION_PATCH;

   for (index = 0u; index < FLASH_AUTH_ID_LENGTH; index++){
      flashLibConfig.id_au32[index] = flashParam->authID[index];
   }

   flashLibConfig.addrRam_u32         = FLASHLIB_NULL;

   flashLibConfig.frequencyCpuMHz_u16 = flashParam->frequencyMHz;

   libRequest.status_enu = FlashLibInit(&flashLibConfig);
   if(FLASHLIB_OK == libRequest.status_enu){
      libRequest.command_enu = FLASHLIB_CMD_PREPARE_ENV;
      FlashLibExecute(&libRequest);
      while (FLASHLIB_BUSY == libRequest.status_enu)
      {
         (void)FblDrvFlashHandleWD();
         FlashLibHandler();
      }
   }

   if(FLASHLIB_OK == libRequest.status_enu){
      libRequest.command_enu = FLASHLIB_CMD_DISABLE_LOCKBITS;
      FlashLibExecute(&libRequest);
      while (FLASHLIB_BUSY == libRequest.status_enu)
      {
         (void)FblDrvFlashHandleWD();
         FlashLibHandler();
      }
   }

   if(FLASHLIB_OK != libRequest.status_enu){
      flashParam->errorCode = kFlashInitFailed | (((tFlashUint16)(libRequest.status_enu)) << 8);
   }
   else{
      flashParam->errorCode = kFlashOk;
   }

   FblDrvFlashRestoreCurFblBasePtr();
}

void ExpFlashDeinit ( tFlashParam * flashParam ){
   tFlashLibRequest libRequest;

   FblDrvFlashSaveCurFblBasePtr();
   FblDrvFlashSetCurFlashDrvBasePtr();

   libRequest.command_enu = FLASHLIB_CMD_ENABLE_LOCKBITS;
   FlashLibExecute(&libRequest);
   while (FLASHLIB_BUSY == libRequest.status_enu){
      (void)FblDrvFlashHandleWD();
      FlashLibHandler();
   }

   if(FLASHLIB_OK != libRequest.status_enu){
      flashParam->errorCode = kFlashDeinitFailed | (((tFlashUint16)(libRequest.status_enu)) << 8);
   }
   else{
      flashParam->errorCode = kFlashOk;
   }

   FblDrvFlashRestoreCurFblBasePtr();
}

void ExpFlashErase ( tFlashParam * flashParam ){
   tFlashLibRequest libRequest;
   tFlashUint32 tmpBlock;

   FblDrvFlashSaveCurFblBasePtr();
   FblDrvFlashSetCurFlashDrvBasePtr();

   pflashParam = flashParam;

   flashParam->errorCode = kFlashOk;
   flashParam->errorAddress = flashParam->address;
   if(kFlashOk != FblDrvFlashGetBlockByAddr(pflashParam->address, &libRequest.idx_u32)){
      pflashParam->errorCode = kFlashInvalidAddress;
   }

   if(kFlashOk != FblDrvFlashGetBlockByAddr(((pflashParam->address - 1u) + pflashParam->length), &tmpBlock)){
      pflashParam->errorCode = kFlashInvalidAddress;
   }

   if(pflashParam->errorCode == kFlashOk){
      libRequest.command_enu = FLASHLIB_CMD_CODEF_ERASE;
      libRequest.cnt_u16 = (tFlashUint16)(((tmpBlock + 1u) - libRequest.idx_u32) & 0xFFFFu);

      FlashLibExecute(&libRequest);
      while (FLASHLIB_BUSY == libRequest.status_enu)
      {
         (void)FblDrvFlashHandleWD();
         FlashLibHandler();
      }

      if(FLASHLIB_OK != libRequest.status_enu)
      {
         flashParam->errorCode = kFlashEraseFailed | (((tFlashUint16)(libRequest.status_enu)) << 8u);
      }
      else
      {
         flashParam->errorCode = kFlashOk;
      }
   }

   FblDrvFlashRestoreCurFblBasePtr();
}

void ExpFlashWrite ( tFlashParam * flashParam ){
   tFlashLibRequest libRequest;

   FblDrvFlashSaveCurFblBasePtr();
   FblDrvFlashSetCurFlashDrvBasePtr();

   pflashParam = flashParam;

   flashParam->errorAddress = flashParam->address;
   flashParam->errorCode = kFlashOk;

   libRequest.command_enu   = FLASHLIB_CMD_CODEF_WRITE;
   libRequest.bufferAdd_u32 = (tFlashUint32) &(pflashParam->data[0u]);
   libRequest.idx_u32       = (tFlashUint32)(pflashParam->address);
   libRequest.cnt_u16       = (tFlashUint16)((pflashParam->length) >> 8u);

   FlashLibExecute(&libRequest);
   while (FLASHLIB_BUSY == libRequest.status_enu){
      (void)FblDrvFlashHandleWD();
      FlashLibHandler();
   }

   if(FLASHLIB_OK != libRequest.status_enu){
      flashParam->errorCode = kFlashWriteFailed | (((tFlashUint16)(libRequest.status_enu)) << 8u);
   }
   else{
      flashParam->errorCode = kFlashOk;
   }

   FblDrvFlashRestoreCurFblBasePtr();
}

#if defined( FLASH_ENABLE_SET_RESETVECTOR_API )

void ExpFlashSetResetVector ( tFlashParam * flashParam ){
   tFlashLibRequest libRequest;
   tFlashUint32 resetVectorArray[4u];

   FblDrvFlashSaveCurFblBasePtr();
   FblDrvFlashSetCurFlashDrvBasePtr();

   pflashParam = flashParam;

   flashParam->errorAddress = flashParam->address;
   flashParam->errorCode = kFlashOk;

   if(flashParam->length >= FLASH_MAX_CORES_RESET_VECTOR){
      flashParam->errorCode = kFlashWriteInvalidParam;
   }
   else{
      libRequest.command_enu   = FLASHLIB_CMD_GET_RESET_VECTOR;
      libRequest.bufferAdd_u32 = (tFlashUint32) &(resetVectorArray);

      FlashLibExecute(&libRequest);
      while (FLASHLIB_BUSY == libRequest.status_enu)
      {
         (void)FblDrvFlashHandleWD();
         FlashLibHandler();
      }

      if(FLASHLIB_OK == libRequest.status_enu)
      {
         resetVectorArray[flashParam->length] = flashParam->address;

         libRequest.command_enu   = FLASHLIB_CMD_SET_RESET_VECTOR;
         libRequest.bufferAdd_u32 = (tFlashUint32) &(resetVectorArray);

         FlashLibExecute(&libRequest);
         while (FLASHLIB_BUSY == libRequest.status_enu)
         {
            (void)FblDrvFlashHandleWD();
            FlashLibHandler();
         }
      }

      if(FLASHLIB_OK != libRequest.status_enu)
      {
         flashParam->errorCode = kFlashWriteFailed | (((tFlashUint16)(libRequest.status_enu)) << 8);
      }
      else
      {
         flashParam->errorCode = kFlashOk;
      }
   }

   FblDrvFlashRestoreCurFblBasePtr();
}
#endif

# if defined( FLASH_ENABLE_OPTIONBYTE_API )

void ExpFlashSetOptionByte ( tFlashParam * flashParam ){
   tFlashLibRequest libRequest;
   tFlashUint8 optionByteArray[32u];
   tFlashUint16 opbCnt;
   tFlashUint16 dataCnt = 0u;

   FblDrvFlashSaveCurFblBasePtr();
   FblDrvFlashSetCurFlashDrvBasePtr();

   pflashParam = flashParam;

   flashParam->errorAddress = flashParam->address;
   flashParam->errorCode = kFlashOk;

   if(flashParam->length != FLASH_NUM_OPTIONBYTES){
      flashParam->errorCode = kFlashInvalidParam;
   }
   else{
      for (opbCnt = 0u; opbCnt < sizeof(optionByteArray); opbCnt += 4u)
      {
         optionByteArray[opbCnt] = ((tFlashUint8)(flashParam->data[dataCnt] & 0xFFu));
         optionByteArray[opbCnt+1u] = ((tFlashUint8)((flashParam->data[dataCnt] & 0xFF00u) >> 8u));
         optionByteArray[opbCnt+2u] = ((tFlashUint8)((flashParam->data[dataCnt] & 0xFF0000u) >> 16u));
         optionByteArray[opbCnt+3u] = ((tFlashUint8)((flashParam->data[dataCnt] & 0xFF000000u) >> 24u));
         dataCnt++;
      }

      libRequest.command_enu   = FLASHLIB_CMD_SET_OPB;
      libRequest.bufferAdd_u32 = (tFlashUint32) &optionByteArray[0u];
      FlashLibExecute(&libRequest);

      while (FLASHLIB_BUSY == libRequest.status_enu)
      {
         (void)FblDrvFlashHandleWD();
         FlashLibHandler();
      }

      if(FLASHLIB_OK != libRequest.status_enu)
      {
         flashParam->errorCode = kFlashWriteFailed | (((tFlashUint16)(libRequest.status_enu)) << 8u);
      }
      else
      {
         flashParam->errorCode = kFlashOk;
      }
   }

   FblDrvFlashRestoreCurFblBasePtr();
}

void ExpFlashGetOptionByte ( tFlashParam * flashParam ){
   tFlashLibRequest libRequest;
   tFlashUint8 optionByteArray[32u];
   tFlashUint16 dataCnt;
   tFlashUint8 opbCnt;

   FblDrvFlashSaveCurFblBasePtr();
   FblDrvFlashSetCurFlashDrvBasePtr();

   pflashParam = flashParam;

   flashParam->errorAddress = flashParam->address;
   flashParam->errorCode = kFlashOk;

   if(flashParam->length != FLASH_NUM_OPTIONBYTES){
      flashParam->errorCode = kFlashInvalidParam;
   }
   else{
      for (opbCnt = 0u; opbCnt < sizeof(optionByteArray); opbCnt++)
      {
         optionByteArray[opbCnt] = 0xFFu;
      }

      libRequest.command_enu = FLASHLIB_CMD_GET_OPB;
      libRequest.bufferAdd_u32 = (tFlashUint32) &optionByteArray[0u];
      FlashLibExecute(&libRequest);

      if(FLASHLIB_OK != libRequest.status_enu)
      {
         flashParam->errorCode = kFlashWriteFailed | (((tFlashUint16)(libRequest.status_enu)) << 8u);
      }
      else
      {
         opbCnt = 0u;

         for (dataCnt = 0u; dataCnt < flashParam->length; dataCnt++)
         {
            flashParam->data[dataCnt] = ((tFlashUint32)optionByteArray[opbCnt+3u] << 24u) | \
                                        ((tFlashUint32)optionByteArray[opbCnt+2u] << 16u) | \
                                        ((tFlashUint32)optionByteArray[opbCnt+1u] <<  8u) | \
                                        ((tFlashUint32)optionByteArray[opbCnt]);
            opbCnt += 4u;
         }

         flashParam->errorCode = kFlashOk;
      }
   }

   FblDrvFlashRestoreCurFblBasePtr();
}
# endif

#ifdef __cplusplus
}
#endif
