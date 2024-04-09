#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 0292
#endif

#ifndef R_FCL_ENV_H
#define R_FCL_ENV_H

#ifdef R_FCL_CPE_SUPPORT
#include "r_fcl_env_cpe.hpp"
#else
#define R_FPSYS_REG_AREA_BASE                       (0xFFA10000uL)
#define R_FPSYS_FCURAM_AREA_BASE                    (0xFFA12000uL)
#define R_FPSYS_FLASH_ACCESS_AREA_BASE              (0xFFA20000uL)
#define R_BWCBUF_G3K_ADD                            (0xFFBC0700uL)
#define R_BWCBUF_G3KH_ADD                           (0xFFC5B000uL)
#endif

#define R_FPSYS_REGADD_AUTH_BASE                        (0xFFA08000uL)
#define R_FPSYS_REGADD_AUTH_ID0_U32                     (R_FPSYS_REGADD_AUTH_BASE + 0x000uL)
#define R_FPSYS_REGADD_AUTH_ID1_U32                     (R_FPSYS_REGADD_AUTH_BASE + 0x004uL)
#define R_FPSYS_REGADD_AUTH_ID2_U32                     (R_FPSYS_REGADD_AUTH_BASE + 0x008uL)
#define R_FPSYS_REGADD_AUTH_ID3_U32                     (R_FPSYS_REGADD_AUTH_BASE + 0x00cuL)
#define R_FPSYS_REGADD_AUTH_STATUS_U32                  (R_FPSYS_REGADD_AUTH_BASE + 0x010uL)
#define R_FPSYS_REGBIT_AUTH_STATUS_LOCKED               (0x00000001uL)

#define R_FPSYS_REGADD_FPMON_U8                         (R_FPSYS_REG_AREA_BASE)
#define R_FPSYS_REGBIT_SFWE                             (0x80u)

#define R_FPSYS_REGADD_FCURAME_U16                      (R_FPSYS_REG_AREA_BASE + 0x054uL)
#define R_FPSYS_REGBIT_FCURAME_KEY                      (0xC400u)
#define R_FPSYS_REGBIT_FCURAME_FCRME                    (0x0001u)
#define R_FPSYS_REGBIT_FCURAME_FRAMTRAN                 (0x0002u)
#define R_FPSYS_REGBIT_FCURAME_RESET                    (0x0000u)

#define R_FPSYS_REGADD_FSADR_U32                        (R_FPSYS_REG_AREA_BASE + 0x030uL)
#define R_FPSYS_REGADD_FEADR_U32                        (R_FPSYS_REG_AREA_BASE + 0x034uL)

#define R_FPSYS_REGADD_FASTAT_U8                        (R_FPSYS_REG_AREA_BASE + 0x010uL)
#define R_FPSYS_REGBIT_FASTAT_CMDLK                     (0x10u)

#define R_FPSYS_REGADD_FAEINT_U8                        (R_FPSYS_REG_AREA_BASE + 0x014uL)
#define R_FPSYS_REGVAL_FAEINT_DISABLE                   (0x88u)
#define R_FPSYS_REGVAL_FAEINT_ENABLE                    (0x99u)

#define R_FPSYS_REGADD_PCKAR_U16                        (R_FPSYS_REG_AREA_BASE + 0x0E4uL)
#define R_FPSYS_REGBIT_PCKAR_KEY                        (0x1E00u)

#define R_FPSYS_REGADD_FMATSELC_U16                     (R_FPSYS_REG_AREA_BASE + 0x020uL)
#define R_FPSYS_REGBIT_FMATSELC_KEY                     (0x3B00u)
#define R_FPSYS_REGBIT_FMATSELC_USS                     (0x0000u)
#define R_FPSYS_REGBIT_FMATSELC_EX1S                    (0x0001u)
#define R_FPSYS_REGBIT_FMATSELC_EX2S                    (0x0002u)

#define R_FPSYS_REGADD_FSTATR_U32                       (R_FPSYS_REG_AREA_BASE + 0x080uL)
#define R_FPSYS_REGBIT_FSTATR_RESET                     (0x00000000uL)
#define R_FPSYS_REGBIT_FSTATR_FCURAMERR                 (0x00000002uL)
#define R_FPSYS_REGBIT_FSTATR_TBLDERR                   (0x00000008uL)
#define R_FPSYS_REGBIT_FSTATR_CONFDERR                  (0x00000020uL)
#define R_FPSYS_REGBIT_FSTATR_FHVEERR                   (0x00000040uL)
#define R_FPSYS_REGBIT_FSTATR_FCUERR                    (0x00000080uL)
#define R_FPSYS_REGBIT_FSTATR_PRGSPD                    (0x00000100uL)
#define R_FPSYS_REGBIT_FSTATR_ERSSPD                    (0x00000200uL)
#define R_FPSYS_REGBIT_FSTATR_DBFULL                    (0x00000400uL)
#define R_FPSYS_REGBIT_FSTATR_SUSRDY                    (0x00000800uL)
#define R_FPSYS_REGBIT_FSTATR_PRGERR                    (0x00001000uL)
#define R_FPSYS_REGBIT_FSTATR_ERSERR                    (0x00002000uL)
#define R_FPSYS_REGBIT_FSTATR_ILGERR                    (0x00004000uL)
#define R_FPSYS_REGBIT_FSTATR_FRDY                      (0x00008000uL)
#define R_FPSYS_REGBIT_FSTATR_OTPDERR                   (0x00020000uL)

#define R_FPSYS_REGADD_FPESTAT_U16                      (R_FPSYS_REG_AREA_BASE + 0x0C0uL)
#define R_FPSYS_REGBIT_FPESTAT_WRITELOCK                (0x0001u)
#define R_FPSYS_REGBIT_FPESTAT_ERASELOCK                (0x0011u)

#define R_FPSYS_REGADD_FPROTR_U16                       (R_FPSYS_REG_AREA_BASE + 0x088uL)
#define R_FPSYS_REGBIT_FPROTR_RESET                     (0x0000u)
#define R_FPSYS_REGBIT_FPROTR_KEY                       (0x5500u)
#define R_FPSYS_REGBIT_FPROTR_OFF                       (0x0001u)
#define R_FPSYS_REGBIT_FPROTR_ON                        (0x0000u)

#define R_FPSYS_REGADD_FLKSTAT_U8                       (R_FPSYS_REG_AREA_BASE + 0x090uL)

#define R_FPSYS_REGADD_FENTRYR_U16                      (R_FPSYS_REG_AREA_BASE + 0x084uL)
#define R_FPSYS_REGBIT_FENTRY_FENTRYD                   (0x0080u)
#define R_FPSYS_REGBIT_FENTRY_FENTRYC                   (0x0001u)
#define R_FPSYS_REGBIT_FENTRY_KEY                       (0xAA00u)
#define R_FPSYS_REGBIT_FENTRY_OFF                       (0x0000u)
#define R_FPSYS_REGBIT_FENTRY_KEYMASK                   (0x00FFu)
#define R_FPSYS_MODE_DPE                                (R_FPSYS_REGBIT_FENTRY_FENTRYD)
#define R_FPSYS_MODE_CPE                                (R_FPSYS_REGBIT_FENTRY_FENTRYC)
#define R_FPSYS_MODE_USER                               (R_FPSYS_REGBIT_FENTRY_OFF)

#define R_FPSYS_FCURAM_AREA_SIZE                        (0x00001000uL)

#ifdef R_FCL_INNER_NO_BFA_SWITCH
#define R_FPSYS_FCURAM_AREA_RAM_ADD                 (0x01037000uL)
#define R_FPSYS_EXTRA3_AREA_BASE                    (0x01030000uL)
#else
#define R_FPSYS_FCURAM_AREA_RAM_ADD                 (0x00017000uL)
#define R_FPSYS_EXTRA3_AREA_BASE                    (0x00010000uL)
#endif

#define R_FPSYS_FCURAM_AREA_COPY_SIZE                   (R_FPSYS_FCURAM_AREA_SIZE / 8)

#define R_FPSYS_FCURAM_AREA_CHKSUM_END                  (R_FPSYS_FCURAM_AREA_RAM_ADD + 0x0FF8uL)
#define R_FPSYS_FCURAM_AREA_CHKSUM                      (R_FPSYS_FCURAM_AREA_RAM_ADD + 0x0FFCuL)

#define R_FPSYS_FLASH_ACCESS_CMD_ERASE                  (0x20u)
#define R_FPSYS_FLASH_ACCESS_CMD_CLEARSTAT              (0x50u)
#define R_FPSYS_FLASH_ACCESS_CMD_FORCED_STOP            (0xB3u)
#define R_FPSYS_FLASH_ACCESS_CMD_WRITE                  (0xE8u)
#define R_FPSYS_FLASH_ACCESS_CMD_PRG_CFG                (0x40u)
#define R_FPSYS_FLASH_ACCESS_CMD_PRG_CFG_OTP            (0x45u)
#define R_FPSYS_FLASH_ACCESS_CMD_READ_LOCKBIT           (0x71u)
#define R_FPSYS_FLASH_ACCESS_CMD_WRITE_LOCKBIT          (0x77u)
#define R_FPSYS_FLASH_ACCESS_CMD_SUSPEND                (0xB0u)
#define R_FPSYS_FLASH_ACCESS_CMD_RESUME                 (0xD0u)
#define R_FPSYS_FLASH_ACCESS_CMD_EXE                    (0xD0u)

#define R_FPSYS_CONFIG_AREA_BASE                        (0xFF300000uL)
#define R_FPSYS_CONFIG_AREA_SEC_FLAGS                   (R_FPSYS_CONFIG_AREA_BASE + 0x40u)
#define R_FPSYS_CONFIG_AREA_OCD                         (R_FPSYS_CONFIG_AREA_BASE + 0x50u)
#define R_FPSYS_CONFIG_AREA_RESET                       (R_FPSYS_CONFIG_AREA_BASE + 0x60u)
#define R_FPSYS_CONFIG_AREA_OPTIONBYTES                 (R_FPSYS_CONFIG_AREA_BASE + 0x70u)

#define R_FPSYS_CONFIG_OTP                              (0xFF380040uL)
#define R_FPSYS_CONFIG_OTP_CF1_OFFSET                   (R_FPSYS_CONFIG_OTP + 0x00u)
#define R_FPSYS_CONFIG_OTP_CF2_OFFSET                   (R_FPSYS_CONFIG_OTP + 0x20u)
#define R_FPSYS_CONFIG_OTP_UB_OFFSET                    (R_FPSYS_CONFIG_OTP + 0x50u)

#define R_FPSYS_EXTRA3_AREA_SCDS_U32                    (R_FPSYS_EXTRA3_AREA_BASE + 0x270uL)
#define R_FPSYS_EXTRA3_AREA_PRDSEL1                     (0xC0uL)
#define R_FPSYS_EXTRA3_AREA_PRDSEL2                     (0xC4uL)
#define R_FPSYS_EXTRA3_AREA_PRDSEL4                     (0xCCuL)
#define R_FPSYS_EXTRA3_AREA_PRDNAME1                    (0xD0uL)
#define R_FPSYS_EXTRA3_AREA_PRDNAME2                    (0xD4uL)
#define R_FPSYS_EXTRA3_AREA_PRDNAME3                    (0xD8uL)
#define R_FPSYS_EXTRA3_AREA_PRDNAME4                    (0xDCuL)
#define R_FPSYS_EXTRA3_AREA_FPVER_U08                   (R_FPSYS_EXTRA3_AREA_BASE + 0x219uL)
#define R_FPSYS_FPVER_03                                (0x03u)
#define R_FPSYS_FPVER_04                                (0x04u)

#define R_FPSYS_EXTRA3_AREA_UB_FPVER04_U08              (R_FPSYS_EXTRA3_AREA_BASE + 0x21EuL)
#define R_FPSYS_EXTRA3_AREA_MAXHCLK_U32                 (R_FPSYS_EXTRA3_AREA_BASE + 0x234uL)
#define R_FPSYS_EXTRA3_AREA_MINHCLK_U32                 (R_FPSYS_EXTRA3_AREA_BASE + 0x238uL)
#define R_FPSYS_EXTRA3_AREA_PCLKDIV1_FPVER03_U32        (R_FPSYS_EXTRA3_AREA_BASE + 0x264uL)
#define R_FPSYS_EXTRA3_AREA_PCLK_FPVER03_U32            (R_FPSYS_EXTRA3_AREA_BASE + 0x274uL)
#define R_FPSYS_EXTRA3_AREA_PCLKDIV1_FPVER04_U32        (R_FPSYS_EXTRA3_AREA_BASE + 0x265uL)
#define R_FPSYS_EXTRA3_AREA_PCLK_FPVER04_U32            (R_FPSYS_EXTRA3_AREA_BASE + 0x278uL)

#define R_FPSYS_PRDNAME_E1x_012x                        (0x00323130u)
#define R_FPSYS_PRDNAME_E1x_01Zx                        (0x005A3130u)

#define R_RDPR_FLAG_MASK                                (0x80000000u)
#define R_WRPR_FLAG_MASK                                (0x40000000u)
#define R_SEPR_FLAG_MASK                                (0x20000000u)
#define R_SPD_FLAG_MASK                                 (0x08000000u)
#define R_SPIE_FLAG_MASK                                (0x01000000u)
#define R_RDPR_FLAG_SHIFT                               (0x1Fu)
#define R_WRPR_FLAG_SHIFT                               (0x1Eu)
#define R_SEPR_FLAG_SHIFT                               (0x1Du)
#define R_SPD_FLAG_SHIFT                                (0x1Bu)
#define R_SPIE_FLAG_SHIFT                               (0x18u)

#define R_FLI_BLOCK_SIZE                                (0x8000u)
#define R_FLI_SMALL_BLOCK_SIZE                          (0x2000u)
#define R_FLI_BLOCK_TRANSFERSIZE                        (0x80u)
#define R_FLI_BLOCK_TRANSFERSIZE_PART                   (0x40u)
#define R_PRG_CFG_TRANSFERSIZE                          (0x08u)
#define R_PRG_CFG_TRANSFERSIZE_OTP                      (R_PRG_CFG_TRANSFERSIZE)
#define R_PRG_CFG_TRANSFERSIZE_OPB                      (2 * R_PRG_CFG_TRANSFERSIZE)
#define R_PRG_CFG_TRANSFERSIZE_OCD                      (R_PRG_CFG_TRANSFERSIZE)
#define R_PRG_CFG_TRANSFERSIZE_RESET                    (R_PRG_CFG_TRANSFERSIZE)

#define R_FLI_USERBOOT_AREA_START                       (0x01000000u)
#define R_FLI_USERBOOT_AREA_END                         (0x01007FFFu)
#define R_FCL_USERBOOT_AREA_SELECT                      (0x80000000u)
#define R_FLI_USERBOOT_AREA_MASK                        (0x7FFFFFFFu)
#define R_FLI_CFLASH1_START                             (0x00000000u)
#if((defined R_FCL_CFL2_START_ADDR_2048K) && (defined R_FCL_CFL2_START_ADDR_4096K))
#error "r_fcl_env.h: Invalid define for R_FCL_CFL2_START_ADDR_*"
#elif(defined R_FCL_CFL2_START_ADDR_2048K)
#define R_FLI_CFLASH2_START                             (0x00200000u)
#elif(defined R_FCL_CFL2_START_ADDR_4096K)
#define R_FLI_CFLASH2_START                             (0x00400000u)
#else
#define R_FLI_CFLASH2_START                             (0x00800000u)
#endif

#define R_FCL_FCU_FMIN                                  (0x0004u)
#define R_FCL_FCU_FMAX                                  (0x0064u)

#define R_FLI_MIN_WRITESIZE                             (2 * R_FLI_BLOCK_TRANSFERSIZE)

#define R_SYSTEM_REGISTER_PID                           6, 1
#define R_PID_CORE_MASK                                 (0x000000E0)
#define R_PID_CORE_G3K                                  (0x00000020)
#define R_PID_CORE_G3KH                                 (0x000000a0)

#endif

