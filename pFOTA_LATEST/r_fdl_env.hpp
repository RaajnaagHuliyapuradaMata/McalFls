#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_OFF 0292
#endif

#ifdef ENABLE_QAC_TEST
#pragma PRQA_MESSAGES_ON 0292
#endif

#ifndef R_FDL_ENV_H
#define R_FDL_ENV_H

#define R_FCU_BASE                    (0xFFA10000uL)

#define R_FCU_REGADD_FASTAT_U08       (R_FCU_BASE + 0x010uL)
#define R_FCU_REGBIT_FASTAT_CMDLK     (0x10u)

#define R_FCU_REGADD_FMATSELC_U16     (R_FCU_BASE + 0x020uL)
#define R_FCU_REGBIT_FMATSELC_KEY     (0x3B00u)
#define R_FCU_REGBIT_FMATSELC_EX3S    (0x0004u)
#define R_FCU_REGBIT_FMATSELC_RESET   (0x0000u)

#define R_FCU_REGADD_FSADR_U32        (R_FCU_BASE + 0x030uL)
#define R_FCU_REGADD_FEADR_U32        (R_FCU_BASE + 0x034uL)

#define R_FCU_REGADD_FCURAME_U16      (R_FCU_BASE + 0x054uL)
#define R_FCU_REGBIT_FCURAME_KEY      (0xC400u)
#define R_FCU_REGBIT_FCURAME_FCRME    (0x0001u)
#define R_FCU_REGBIT_FCURAME_FRAMTRAN (0x0002u)
#define R_FCU_REGBIT_FCURAME_RESET    (0x0000u)

#define R_FCU_REGADD_FSTATR_U32       (R_FCU_BASE + 0x080uL)
#define R_FCU_REGBIT_FSTATR_FRCRCT    (0x00000001uL)
#define R_FCU_REGBIT_FSTATR_FRDTCT    (0x00000002uL)
#define R_FCU_REGBIT_FSTATR_TBLDTCT   (0x00000008uL)
#define R_FCU_REGBIT_FSTATR_CFGDTCT   (0x00000020uL)
#define R_FCU_REGBIT_FSTATR_FHVEERR   (0x00000040uL)
#define R_FCU_REGBIT_FSTATR_FCUERR    (0x00000080uL)
#define R_FCU_REGBIT_FSTATR_PRGSPD    (0x00000100uL)
#define R_FCU_REGBIT_FSTATR_ERSSPD    (0x00000200uL)
#define R_FCU_REGBIT_FSTATR_DBFULL    (0x00000400uL)
#define R_FCU_REGBIT_FSTATR_SUSRDY    (0x00000800uL)
#define R_FCU_REGBIT_FSTATR_PRGERR    (0x00001000uL)
#define R_FCU_REGBIT_FSTATR_ERSERR    (0x00002000uL)
#define R_FCU_REGBIT_FSTATR_ILGERR    (0x00004000uL)
#define R_FCU_REGBIT_FSTATR_FRDY      (0x00008000uL)
#define R_FCU_REGBIT_FSTATR_OTPDTCT   (0x00020000uL)
#define R_FCU_REGBIT_FSTATR_RESET     (0x00000000uL)

#define R_FCU_REGADD_FENTRYR_U16      (R_FCU_BASE + 0x084uL)
#define R_FCU_REGBIT_FENTRY_FENTRYD   (0x0080u)
#define R_FCU_REGBIT_FENTRY_FENTRYC   (0x0001u)
#define R_FCU_REGBIT_FENTRY_KEY       (0xAA00u)
#define R_FCU_REGBIT_FENTRY_OFF       (0x0000u)
#define R_FCU_REGBIT_FENTRY_KEYMASK   (0x00FFu)
#define R_FCU_MODE_PE                 (R_FCU_REGBIT_FENTRY_FENTRYD)
#define R_FCU_MODE_CPE                (R_FCU_REGBIT_FENTRY_FENTRYC)
#define R_FCU_MODE_USER               (R_FCU_REGBIT_FENTRY_OFF)

#define R_FCU_REGADD_FBCSTAT_U08      (R_FCU_BASE + 0x0D4uL)
#define R_FCU_REGBIT_FBCSTAT_BCST     (0x01u)

#define R_FCU_REGADD_FPSADDR_U32      (R_FCU_BASE + 0x0D8uL)

#define R_FCU_REGADD_PCKAR_U16        (R_FCU_BASE + 0x0E4uL)
#define R_FCU_REGBIT_PCKAR_KEY        (0x1E00u)

#define R_DECC_BASE_E1X               (0xFFC62C00uL)
#define R_DECC_BASE_F1X               (0xFFC66000uL)
#define R_DECC_BASE                   (g_fdl_str.baseAddrECC_u32)

#define R_FCU_REGADD_DFERSTR_U32      (R_DECC_BASE + 0x004uL)
#define R_FCU_REGBIT_DFERSTR_SEDF     (0x00000001u)
#define R_FCU_REGBIT_DFERSTR_DEDF     (0x00000002u)
#define R_FCU_REGVAL_DFERSTR_NOERR    (0x00000000u)

#define R_FCU_REGADD_DFERSTC_U08      (R_DECC_BASE + 0x008uL)
#define R_FCU_REGBIT_DFERSTC_ERRCLR   (0x01u)

#define R_FCU_REGADD_DFERINT_U08      (R_DECC_BASE + 0x014uL)
#define R_FCU_REGVAL_DFERINT_NOINT    (0x00u)

#define R_CCIB_BASE                   (0xFFC59000uL)

#define R_FCU_REGADD_BFASELR_U08      (R_CCIB_BASE + 0x008uL)
#define R_FCU_REGBIT_BFASELR_BFASEL   (0x01u)
#define R_FCU_REGBIT_BFASELR_RESET    (0x00u)

#define R_FDL_FCU_RAM_ADD             (0xFFA12000uL)
#define R_FDL_FCU_RAM_SIZE            (0x00001000uL)
#define R_FDL_FCU_RAM_SRC_ADD         (0x00017000uL)
#define R_FDL_FCU_RAM_ADD_CHKSUM_END  (0x00017FF8uL)
#define R_FDL_FCU_RAM_ADD_CHKSUM      (0x00017FFCuL)
#define R_FDL_EXTRA3_FWVER            (0x00010219uL)
#define R_FDL_EXTRA3_FMAX             (0x00010234uL)
#define R_FDL_EXTRA3_FMIN             (0x00010238uL)
#define R_FDL_EXTRA3_FDIV_FWVER_03    (0x00010264uL)
#define R_FDL_EXTRA3_FPCLK_FWVER_03   (0x00010274uL)
#define R_FDL_EXTRA3_FDIV_FWVER_04    (0x00010265uL)
#define R_FDL_EXTRA3_FPCLK_FWVER_04   (0x00010278uL)
#define R_FDL_EXTRA3_SCDSADD          (0x00010270uL)
#define R_FDL_EXTRA3_ECCADDR          (0x00010288uL)

#define R_FDL_FCU_FWVER_03            (0x03u)
#define R_FDL_FCU_FWVER_04            (0x04u)

#define R_FDL_PRDSEL3_OFFSET          (0xC8uL)
#define R_FDL_PRDNAME2_OFFSET         (0xD4uL)
#define R_PRDNAME_010x                (0x00303130u)

#define R_FCU_DFLASH_CMD_ADD          (0xFFA20000uL)
#define R_FCU_DFLASH_READ_ADD         (0xFF200000uL)

#define R_FCU_CMD_ERASE               (0x20u)
#define R_FCU_CMD_CLEARSTAT           (0x50u)
#define R_FCU_CMD_BLANKCHECK          (0x71u)
#define R_FCU_CMD_SUSPEND             (0xB0u)
#define R_FCU_CMD_FORCED_STOP         (0xB3u)
#define R_FCU_CMD_WRITE               (0xE8u)
#define R_FCU_CMD_EXE                 (0xD0u)

#define R_FDL_FCU_DATA_TRANSFERSIZE   (0x02uL)

#define R_FDL_FCU_FMIN                (0x0004u)
#define R_FDL_FCU_FMAX                (0x0064u)

#define R_FDL_BLOCK_SIZE              (0x0040u)
#define R_FDL_BLOCK_SIZE_2N           (0x0006u)
#define R_FDL_WRITE_SIZE              (0x00000004uL)
#define R_FDL_WRITE_SIZE_16B          (0x00000010uL)
#define R_FDL_MACROSIZE_MIN           (0x00001000uL)

#define R_FDL_U32_ALIGNED             (0x03u)

#endif

