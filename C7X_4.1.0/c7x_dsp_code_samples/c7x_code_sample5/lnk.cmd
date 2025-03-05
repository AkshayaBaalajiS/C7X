/*
* module name       : c7x_sample5
*
* module descripton : 1D FIR filter using VFIR instruction
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

--heap_size  0x1000
--stack_size 0x1000

MEMORY
{
  L2SRAM (RWX)  : org = 0x60800000, len = 0x080000
  MSMCSRAM (RWX): org = 0x70000000, len = 0x800000
  EXTMEM (RWX)  : org = 0x80000000, len = 0x800000
}

SECTIONS
{
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
   xdc.meta:        > L2SRAM, type = COPY
}

