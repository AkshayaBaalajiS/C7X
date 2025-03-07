/*
* module name       : c7x_common
*
* module descripton : Common utility functions
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#ifndef PRINTV_H_
#define PRINTV_H_ 1

#include <stdint.h>
#ifdef _HOST_EMULATION
#include <c7x_host_emulation.h>
#else
#include <c7x.h>
#endif

/*----------------------------------------------------------------------------*/
/* Console print options.                                                     */
/* Use the below macros as needed to indicate the bit depth and sign of the   */
/* elements constituting a vector.                                            */
/*----------------------------------------------------------------------------*/
#define PRINTV_UNSIGNED_8BIT  (0)
#define PRINTV_UNSIGNED_16BIT (1)
#define PRINTV_UNSIGNED_32BIT (2)
#define PRINTV_UNSIGNED_64BIT (3)
#define PRINTV_SIGNED_8BIT    (4)
#define PRINTV_SIGNED_16BIT   (5)
#define PRINTV_SIGNED_32BIT   (6)
#define PRINTV_SIGNED_64BIT   (7)
#define PRINTV_FLOAT        (8)

/*----------------------------------------------------------------------------*/
/* Flags to indicate if the output must be printed in hex or decimal.         */
/*----------------------------------------------------------------------------*/
#define PRINTV_HEX_ON  (1)
#define PRINTV_HEX_OFF (0)

/*----------------------------------------------------------------------------*/
/* Flag to indicate quite mode. No prints!                                    */
/*----------------------------------------------------------------------------*/
#define PRINTV_QUIET   (0)

/*----------------------------------------------------------------------------*/
/* Func: PRINTV                                                               */
/*                                                                            */
/* Args: const char *msg                                                      */
/*            - Input message string to be prefixed.                          */
/*       long8 Vec                                                            */
/*            - Input 512 bit data vector to be displayed                     */
/*       U32 data_type                                                         */
/*            - Predefined macro values indicating bitdepth and sign.         */
/*       U32 HEX                                                              */
/*            - Predefined macro value to indicate hex or decimal display.    */
/* Return: None                                                               */
/*                                                                            */
/* Desc: This function is used to display the contents of a vector            */
/*       horizontally with spacing as indicated by data_type and HEX flags.    */
/*       Ex. Using PRINTV_USIGN_16BIT with PRINTV_HEX_ON will print as,       */
/*                                                                            */
/*       0x0000 0x0001 0x0002 0x0003 0x0004 0x0005 0x0006 0x0007 0x0008 ....  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
void PRINTV(const char *msg, long8 Vec, uint32_t data_type, uint32_t mode);

#endif /* PRINTV_H_ */

/* ======================================================================== */
/*  End of file:  printv.h                                                  */
/* ======================================================================== */
