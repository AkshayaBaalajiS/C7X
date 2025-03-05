/*
* module name       : c7x_sobelX_3x3
*
* module descripton : Computes Sobel X gradients across 3x3 window
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

--heap_size  0x2000
--stack_size 0x2000

MEMORY
{
  L2SRAM_CINIT  : org = 0x64800000, len = 0x000100
  L2SRAM (RWX)  : org = 0x64800100, len = 0x07FF00
  MSMCSRAM (RWX): org = 0x70000000, len = 0x800000
  EXTMEM (RWX)  : org = 0x80000000, len = 0x800000
}

SECTIONS
{
  .text:_c_int00:   > L2SRAM_CINIT
  .text:            > L2SRAM
  .text:touch:      > L2SRAM
  .neardata:        > L2SRAM
  .rodata:          > L2SRAM
  .bss:             > L2SRAM
  .init_array:      > L2SRAM
  .far:             > L2SRAM
  .fardata:         > L2SRAM
  .neardata         > L2SRAM
  .rodata           > L2SRAM
  .data:            > L2SRAM
  .switch:          > L2SRAM
  .stack:           > L2SRAM
  .args:            > L2SRAM align = 0x4, fill = 0 {_argsize = 0x200; }
  .sysmem:          > L2SRAM
  .cinit:           > L2SRAM
  .const:           > L2SRAM START(const_start) SIZE(const_size)
  .pinit:           > L2SRAM
  .cio:             > L2SRAM
  .stack:           > L2SRAM
  .inData:          > L2SRAM
  .outData:         > L2SRAM
  .profile:         > L2SRAM
  .pOutSum:         > L2SRAM
  .pBlock:          > L2SRAM
  .randState:       > L2SRAM
  .refQC            > L2SRAM
  .outQC            > L2SRAM
   xdc.meta:        > L2SRAM, type = COPY
}
