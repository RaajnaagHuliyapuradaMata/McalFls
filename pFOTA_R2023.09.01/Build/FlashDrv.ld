MEMORY {
  /* ROM /FLASH */
  iVect       : ORIGIN = 0x00000000, LENGTH = 0x300
  iBMHeader   : ORIGIN = 0x00000300, LENGTH = 0x20
  iFbl		 : ORIGIN = 0x00000320, LENGTH = 0x20000-0x320
  iApplBMHeaderHdr: ORIGIN = 0x00020000, LENGTH = 0x100
  iApplVect   : ORIGIN = 0x00020100, LENGTH = 0x100
  iAppl       : ORIGIN = 0x00020200, LENGTH = 0x20000
  /* Primary RAM */
  iFlashDrv   : ORIGIN = 0xFEDF8000, LENGTH = 0x2800
  iEeprom     : ORIGIN = 0xFEDFA800, LENGTH = 0x00000300
  MAGICFL     : ORIGIN = 0xFEDFAB00, LENGTH = 0x00000010
  iRAM2       : ORIGIN = 0xFEDFAB10, LENGTH = 0x000004F0
  iStack      : ORIGIN = 0xFEDFB000, LENGTH = 0x00001000
  iRAM        : ORIGIN = 0xFEDFC000, LENGTH = 0x0000C000
}
SECTIONS {
  /********************************************************************************************************************/
  /* RAM*/
  /********************************************************************************************************************/
  /* RAM */
  .sdabase                 align(4) :>iFlashDrv  /* initialize globalpointer GP for SDA addressing */
  .signature                align(4) :>.          /* Space for FlashCode */
  .text                    align(4) :>.          /* program code area */
  .R_FCL_CODE_RAM          align(4) :>.
  .R_FCL_CODE_ROMRAM       align(4) :>.
  .R_FCL_DATA              align(4) :>.
  .R_FCL_CODE_USRINT       align(4) :>.          /* Interrupt code located in RAM */
  .R_FCL_CODE_USR          align(4) :>.          /* User code located in RAM */
  .R_FCL_CODE_ROM          align(4) :>.          /* FCL code in ROM */
  .rozdata                          :>.          /* constant datas in ZDA area */
  .robase                  align(4) :>.          /* initialize textpointer TP for SDA addressing */
  .rosdata                 align(4) :>.          /* constant datas in SDA area */
  .rodata                  align(4) :>.          /* constant datas in normal area */
  .data                             :>.          /* initialized data */
  .bss                     align(4) :>.          /* zero initialized data*/
  .sdata                   align(4) :>.          /* initialized data in SDA area*/
  .sbss                    align(4) :>.          /* zero initialized data in SDA area*/
  .zdata                   align(4) :>.          /* initialized data in ZDA area*/
  .zbss                    align(4) :>.          /* zero initialized data in ZDA area*/
  .tdata                   align(4) MAX_SIZE(256) :>.      /* initialized and zero-initialized data in TDA area */
  .secinfo                 align(4) :>.          /* ghs internal (runtime library) */
  .fixaddr                 align(4) :>.          /* ghs internal (compiler) */
  .fixtype                 align(4) :>.          /* ghs internal (compiler) */
  .syscall                 align(4) :>.          /* ghs internal (linker) */
  .R_FCL_CODE_RAM_EX_PROT  align(4) pad(0x20)     :>.           /* ECC Exception protection */
  .R_FCL_CONST             align(4) :>.          /* FCL constants in ROM */
  .stack                   align(4) pad(0x1000)   :>iStack     /* definition of stack size */
}
-sda
