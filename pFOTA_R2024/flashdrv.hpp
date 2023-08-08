

#ifndef __FBLDRVFLASH_RH850RV40HIS_H__
#define __FBLDRVFLASH_RH850RV40HIS_H__

#define FBLDRVFLASH_RH850RV40HIS_VERSION           0x0109u
#define FBLDRVFLASH_RH850RV40HIS_RELEASE_VERSION   0x00u

#if defined( FLASH_ENABLE_SET_RESETVECTOR_API )

# define FLASH_DRIVER_SET_RESET_VECTOR_INTERFACE   0x80u
#else
# define FLASH_DRIVER_SET_RESET_VECTOR_INTERFACE   0x00u
#endif

#define FLASH_DRIVER_VERSION_MCUTYPE      0x86u
#define FLASH_DRIVER_VERSION_MASKTYPE     0x00u
# define FLASH_DRIVER_VERSION_INTERFACE   (0x02u | FLASH_DRIVER_SET_RESET_VECTOR_INTERFACE)
#define FLASH_DRIVER_VERSION_MAJOR        (tFlashUint8)(FBLDRVFLASH_RH850RV40HIS_VERSION >> 8u)
#define FLASH_DRIVER_VERSION_MINOR        (tFlashUint8)(FBLDRVFLASH_RH850RV40HIS_VERSION & 0xFFu)
#define FLASH_DRIVER_VERSION_PATCH        (tFlashUint8)(FBLDRVFLASH_RH850RV40HIS_RELEASE_VERSION)

#define FLASH_SEGMENT_SIZE              0x100u
#define FBL_FLASH_DELETED               0xFFu
#define FLASH_DRIVER_NOT_RELOCATABLE
# define FLASH_AUTH_ID_LENGTH           4u

#define FLASH_DRIVER_HEADER_OFFSET      0x04u
#define FLASH_DRIVER_INIT_OFFSET        (FLASH_DRIVER_HEADER_OFFSET + 0x00u)
#define FLASH_DRIVER_DEINIT_OFFSET      (FLASH_DRIVER_HEADER_OFFSET + 0x04u)
#define FLASH_DRIVER_ERASE_OFFSET       (FLASH_DRIVER_HEADER_OFFSET + 0x08u)
#define FLASH_DRIVER_WRITE_OFFSET       (FLASH_DRIVER_HEADER_OFFSET + 0x0Cu)
#if defined( FLASH_ENABLE_SET_RESETVECTOR_API )
# define FLASH_DRIVER_SETRESVEC_OFFSET  (FLASH_DRIVER_HEADER_OFFSET + 0x10u)
#endif
# if defined( FLASH_ENABLE_OPTIONBYTE_API ) && defined( FLASH_ENABLE_SET_RESETVECTOR_API )
#  define FLASH_DRIVER_SETOPB_OFFSET    (FLASH_DRIVER_HEADER_OFFSET + 0x14u)
#  define FLASH_DRIVER_GETOPB_OFFSET    (FLASH_DRIVER_HEADER_OFFSET + 0x18u)
# endif
# if defined( FLASH_ENABLE_OPTIONBYTE_API ) && !defined( FLASH_ENABLE_SET_RESETVECTOR_API )
#  define FLASH_DRIVER_SETOPB_OFFSET    (FLASH_DRIVER_HEADER_OFFSET + 0x10u)
#  define FLASH_DRIVER_GETOPB_OFFSET    (FLASH_DRIVER_HEADER_OFFSET + 0x14u)
# endif

#define FLASH_DRIVER_MCUTYPE(flashCode)      (*(tFlashUint8*)((flashCode) + 3u))
#define FLASH_DRIVER_MASKTYPE(flashCode)     (*(tFlashUint8*)((flashCode) + 2u))
#define FLASH_DRIVER_INTERFACE(flashCode)    (*(tFlashUint8*)((flashCode) + 0u))

#define kFlashFctInit                  ((tFlashErrorCode)0x00u)
#define kFlashFctDeinit                ((tFlashErrorCode)0x20u)
#define kFlashFctErase                 ((tFlashErrorCode)0x40u)
#define kFlashFctWrite                 ((tFlashErrorCode)0x60u)

#define kFlashOk                       ((tFlashErrorCode)0x00u)
#define kFlashFailed                   ((tFlashErrorCode)0x01u)
#define kFlashVerify                   ((tFlashErrorCode)0x02u)
#define kFlashInvalidParam             ((tFlashErrorCode)0x03u)
#define kFlashInvalidAddress           ((tFlashErrorCode)0x04u)
#define kFlashInvalidSize              ((tFlashErrorCode)0x05u)
#define kFlashCmdBufFull               ((tFlashErrorCode)0x06u)
#define kFlashProtect                  ((tFlashErrorCode)0x07u)
#define kFlashAcc                      ((tFlashErrorCode)0x08u)
#define kFlashInvalidVersion           ((tFlashErrorCode)0x09u)
#define kFlashSequence                 ((tFlashErrorCode)0x0Au)

#define kFlashInitFailed               (kFlashFctInit|kFlashFailed)
#define kFlashInitInvalidParam         (kFlashFctInit|kFlashInvalidParam)
#define kFlashInitInvalidAddr          (kFlashFctInit|kFlashInvalidAddress)
#define kFlashInitInvalidSize          (kFlashFctInit|kFlashInvalidSize)
#define kFlashInitInvalidVersion       (kFlashFctInit|kFlashInvalidVersion)

#define kFlashDeinitFailed             (kFlashFctDeinit|kFlashFailed)
#define kFlashDeinitInvalidParam       (kFlashFctDeinit|kFlashInvalidParam)

#define kFlashEraseFailed              (kFlashFctErase|kFlashFailed)
#define kFlashEraseVerify              (kFlashFctErase|kFlashVerify)
#define kFlashEraseInvalidParam        (kFlashFctErase|kFlashInvalidParam)
#define kFlashEraseInvalidAddr         (kFlashFctErase|kFlashInvalidAddress)
#define kFlashEraseInvalidSize         (kFlashFctErase|kFlashInvalidSize)
#define kFlashEraseSequence            (kFlashFctErase|kFlashSequence)
#define kFlashEraseAcc                 (kFlashFctErase|kFlashAcc)
#define kFlashEraseCmdBufFull          (kFlashFctErase|kFlashCmdBufFull)

#define kFlashWriteFailed              (kFlashFctWrite|kFlashFailed)
#define kFlashWriteVerify              (kFlashFctWrite|kFlashVerify)
#define kFlashWriteInvalidParam        (kFlashFctWrite|kFlashInvalidParam)
#define kFlashWriteInvalidAddr         (kFlashFctWrite|kFlashInvalidAddress)
#define kFlashWriteInvalidSize         (kFlashFctWrite|kFlashInvalidSize)
#define kFlashWriteSequence            (kFlashFctWrite|kFlashSequence)
#define kFlashWriteAcc                 (kFlashFctWrite|kFlashAcc)
#define kFlashWriteCmdBufFull          (kFlashFctWrite|kFlashCmdBufFull)

#define FLASH_DRIVER_WRITE(flashCode, flashParam)\
   ((tFlashFct)(*(tFlashUint32 *)&(flashCode)[FLASH_DRIVER_WRITE_OFFSET]))(flashParam)

#define FLASH_DRIVER_ERASE(flashCode, flashParam)\
   ((tFlashFct)(*(tFlashUint32 *)&(flashCode)[FLASH_DRIVER_ERASE_OFFSET]))(flashParam)

#define FLASH_DRIVER_INIT(flashCode, flashParam)\
   ((tFlashFct)(*(tFlashUint32 *)&(flashCode)[FLASH_DRIVER_INIT_OFFSET]))(flashParam)

#define FLASH_DRIVER_DEINIT(flashCode,flashParam)\
   ((tFlashFct)(*(tFlashUint32 *)&(flashCode)[FLASH_DRIVER_DEINIT_OFFSET]))(flashParam)

#if defined( FLASH_ENABLE_SET_RESETVECTOR_API )

# define FLASH_DRIVER_SET_RESET_VECTOR(flashCode,flashParam)\
   ((tFlashFct)(*(tFlashUint32 *)&(flashCode)[FLASH_DRIVER_SETRESVEC_OFFSET]))(flashParam)
#endif

# if defined ( FLASH_ENABLE_OPTIONBYTE_API )

#  define FLASH_DRIVER_SET_OPTIONBYTE(flashCode, flashParam)\
   ((tFlashFct)(*(tFlashUint32 *)&(flashCode)[FLASH_DRIVER_SETOPB_OFFSET]))(flashParam)

#  define FLASH_DRIVER_GET_OPTIONBYTE(flashCode, flashParam)\
   ((tFlashFct)(*(tFlashUint32 *)&(flashCode)[FLASH_DRIVER_GETOPB_OFFSET]))(flashParam)
# endif

typedef unsigned long  tFlashData;
typedef unsigned long  tFlashAddress;
typedef unsigned long  tFlashLength;
typedef unsigned short tFlashErrorCode;

typedef unsigned char  tFlashUint8;
typedef unsigned short tFlashUint16;
typedef unsigned long  tFlashUint32;

typedef struct tagFlashParam
{
   tFlashUint8       patchLevel;
   tFlashUint8       minorVersion;
   tFlashUint8       majorVersion;
   tFlashUint8       reserved1;

   tFlashErrorCode   errorCode;
   tFlashUint16      reserved2;

   tFlashAddress     address;
   tFlashLength      length;
   tFlashData*       data;

   tFlashUint8       (* wdTriggerFct)(void);

   tFlashData        intendedData;
   tFlashData        actualData;
   tFlashAddress     errorAddress;

   tFlashUint32      authID[FLASH_AUTH_ID_LENGTH];
   tFlashUint16      frequencyMHz;
}tFlashParam;

typedef void (*tFlashFct)(tFlashParam *flashParam);

#endif

