/*****************************************************************************/
/* ARCH_DECL.H                                                               */
/*                                                                           */
/* Copyright (c) 2019 Texas Instruments Incorporated                         */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/
// Computer generated file - DO NOT EDIT
// Computer generated file - DO NOT EDIT
// Computer generated file - DO NOT EDIT
// Produced at Tue Sep  5 15:14:41 2023
// Declarations for bus MMA_EDI_ADDRESS
#define MMA_EDI_ADDRESS_SIZE                                         36      
#define MMA_EDI_ADDRESS_MSB                                          35      
#define MMA_EDI_ADDRESS_LSB                                          0       
#define MMA_EDI_ADDRESS_RESERVED_SIZE                                8        // Reserved field. Software should write zeros to this field for defined behavior.
#define MMA_EDI_ADDRESS_RESERVED_MSB                                 35      
#define MMA_EDI_ADDRESS_RESERVED_LSB                                 28      
#define MMA_EDI_ADDRESS_ROW_SIZE                                     8        // MMA EDI subspace-specific row address
#define MMA_EDI_ADDRESS_ROW_MSB                                      27      
#define MMA_EDI_ADDRESS_ROW_LSB                                      20      
#define MMA_EDI_ADDRESS_MMA_RANGE_SIZE                               4        // MMA EDI address offset in C7x EDI address space
#define MMA_EDI_ADDRESS_MMA_RANGE_MSB                                19      
#define MMA_EDI_ADDRESS_MMA_RANGE_LSB                                16      
#define MMA_EDI_ADDRESS_MMA_RANGE_MMA_EDI                            9        // EDI Control register subspace constant
#define MMA_EDI_ADDRESS_MMA_ARRAY_SIZE                               8        // MMA EDI address array-specific subspace
#define MMA_EDI_ADDRESS_MMA_ARRAY_MSB                                15      
#define MMA_EDI_ADDRESS_MMA_ARRAY_LSB                                8       
#define MMA_EDI_ADDRESS_MMA_ARRAY_A_OPERAND                          0        // Multiplier A operand
#define MMA_EDI_ADDRESS_MMA_ARRAY_A_STORAGE                          1        // A operand storage
#define MMA_EDI_ADDRESS_MMA_ARRAY_B0_OPERAND                         2        // B bank 0 multiplier operand
#define MMA_EDI_ADDRESS_MMA_ARRAY_B1_OPERAND                         3        // B bank 1 multiplier operand
#define MMA_EDI_ADDRESS_MMA_ARRAY_C0_STORAGE                         4        // C bank 0 accumulator storage
#define MMA_EDI_ADDRESS_MMA_ARRAY_C1_STORAGE                         5        // C bank 1 accumulator storage
#define MMA_EDI_ADDRESS_MMA_ARRAY_X_STORAGE                          6        // Elements selected with MMA_EDI_X_STORAGE_SUBSPACE
#define MMA_EDI_ADDRESS_MMA_ARRAY_RESERVED_7                         7        // Reserved encoding.  For defined behavior, software should not use this encoding.
#define MMA_EDI_ADDRESS_MMA_ARRAY_CONTROL                            8        // EDI Control register subspace
#define MMA_EDI_ADDRESS_MMA_ARRAY_RESERVED_9                         9        // Reserved encoding.  For defined behavior, software should not use this encoding.
#define MMA_EDI_ADDRESS_MMA_ARRAY_RESERVED_A                         10       // Reserved encoding.  For defined behavior, software should not use this encoding.
#define MMA_EDI_ADDRESS_MMA_ARRAY_RESERVED_B                         11       // Reserved encoding.  For defined behavior, software should not use this encoding.
#define MMA_EDI_ADDRESS_MMA_ARRAY_RESERVED_C                         12       // Reserved encoding.  For defined behavior, software should not use this encoding.
#define MMA_EDI_ADDRESS_MMA_ARRAY_RESERVED_D                         13       // Reserved encoding.  For defined behavior, software should not use this encoding.
#define MMA_EDI_ADDRESS_MMA_ARRAY_RESERVED_E                         14       // Reserved encoding.  For defined behavior, software should not use this encoding.
#define MMA_EDI_ADDRESS_MMA_ARRAY_RESERVED_F                         15       // Reserved encoding.  For defined behavior, software should not use this encoding.
#define MMA_EDI_ADDRESS_RESERVED_1_SIZE                              3        // Reserved field. Software should write zeros to this field for defined behavior.
#define MMA_EDI_ADDRESS_RESERVED_1_MSB                               7       
#define MMA_EDI_ADDRESS_RESERVED_1_LSB                               5       
#define MMA_EDI_ADDRESS_COLUMN_SIZE                                  5        // MMA EDI subspace-specific 8-byte granular column address
#define MMA_EDI_ADDRESS_COLUMN_MSB                                   4       
#define MMA_EDI_ADDRESS_COLUMN_LSB                                   0       
// Declarations for bus MMA_EDI_X_STORAGE_SUBSPACE
#define MMA_EDI_X_STORAGE_SUBSPACE_SIZE                              14      
#define MMA_EDI_X_STORAGE_SUBSPACE_MSB                               13      
#define MMA_EDI_X_STORAGE_SUBSPACE_LSB                               0       
#define MMA_EDI_X_STORAGE_SUBSPACE_RESERVED_SIZE                     5        // Reserved field.  Software should write zeros to this field for defined behavior.
#define MMA_EDI_X_STORAGE_SUBSPACE_RESERVED_MSB                      13      
#define MMA_EDI_X_STORAGE_SUBSPACE_RESERVED_LSB                      9       
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_SIZE                         6        // Transfer Buffer address
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_MSB                          8       
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_LSB                          3       
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X0                           0        // Transfer buffer element 0
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X1                           1        // Transfer buffer element 1
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X2                           2        // Transfer buffer element 2
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X3                           3        // Transfer buffer element 3
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X4                           4        // Transfer buffer element 4
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X5                           5        // Transfer buffer element 5
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X6                           6        // Transfer buffer element 6
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X7                           7        // Transfer buffer element 7
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X8                           8        // Transfer buffer element 8
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X9                           9        // Transfer buffer element 9
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X10                          10       // Transfer buffer element 10
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X11                          11       // Transfer buffer element 11
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X12                          12       // Transfer buffer element 12
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X13                          13       // Transfer buffer element 13
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X14                          14       // Transfer buffer element 14
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X15                          15       // Transfer buffer element 15
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X16                          16       // Transfer buffer element 16
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X17                          17       // Transfer buffer element 17
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X18                          18       // Transfer buffer element 18
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X19                          19       // Transfer buffer element 19
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X20                          20       // Transfer buffer element 20
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X21                          21       // Transfer buffer element 21
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X22                          22       // Transfer buffer element 22
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_X23                          23       // Transfer buffer element 23
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_CONFIG                   24       // HWA_CONFIG control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_OFFSET                   25       // HWA_OFFSET control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_STATUS                   26       // HWA_STATUS control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_BUSY                     27       // HWA_BUSY control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_BIAS0                    28       // HWA_BIAS0 control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_BIAS1                    29       // HWA_BIAS1 control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_BIAS2                    30       // HWA_BIAS2 control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_BIAS3                    31       // HWA_BIAS3 control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_SCALE0                   32       // HWA_BIAS3 control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_SCALE1                   33       // HWA_BIAS3 control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_SHIFT0                   34       // HWA_BIAS3 control register
#define MMA_EDI_X_STORAGE_SUBSPACE_XREG_HWA_SHIFT1                   35       // HWA_BIAS3 control register
#define MMA_EDI_X_STORAGE_SUBSPACE_COL_SIZE                          3        // 64-bit field in the selected register
#define MMA_EDI_X_STORAGE_SUBSPACE_COL_MSB                           2       
#define MMA_EDI_X_STORAGE_SUBSPACE_COL_LSB                           0       
// Declarations for bus MMA_EDI_CONTROL_SUBSPACE
#define MMA_EDI_CONTROL_SUBSPACE_SIZE                                14      
#define MMA_EDI_CONTROL_SUBSPACE_MSB                                 13      
#define MMA_EDI_CONTROL_SUBSPACE_LSB                                 0       
#define MMA_EDI_CONTROL_SUBSPACE_RESERVED_SIZE                       13       // Reserved field.  Software should write zeros to this field for defined behavior.
#define MMA_EDI_CONTROL_SUBSPACE_RESERVED_MSB                        13      
#define MMA_EDI_CONTROL_SUBSPACE_RESERVED_LSB                        1       
#define MMA_EDI_CONTROL_SUBSPACE_REGISTER_SIZE                       1        // Control register selection
#define MMA_EDI_CONTROL_SUBSPACE_REGISTER_MSB                        0       
#define MMA_EDI_CONTROL_SUBSPACE_REGISTER_LSB                        0       
// Declarations for reg MMA_EDI_CONTROL_REGISTER
#define MMA_EDI_CONTROL_REGISTER_SIZE                                64      
#define MMA_EDI_CONTROL_REGISTER_MSB                                 63      
#define MMA_EDI_CONTROL_REGISTER_LSB                                 0       
#define MMA_EDI_CONTROL_REGISTER_RESERVED_SIZE                       50       // Reserved field.  Software should write zeros to this field for defined behavior.
#define MMA_EDI_CONTROL_REGISTER_RESERVED_MSB                        63      
#define MMA_EDI_CONTROL_REGISTER_RESERVED_LSB                        14      
#define MMA_EDI_CONTROL_REGISTER_TC_SIZE                             1        // Timeout control
#define MMA_EDI_CONTROL_REGISTER_TC_MSB                              13      
#define MMA_EDI_CONTROL_REGISTER_TC_LSB                              13      
#define MMA_EDI_CONTROL_REGISTER_TC_TIMEOUT_DISABLED                 0        // MMA EDI transaction timeouts are disabled
#define MMA_EDI_CONTROL_REGISTER_TC_TIMEOUT_ENABLED                  1        // MMA EDI transaction timeouts are enabled.  This is the default value after reset.
#define MMA_EDI_CONTROL_REGISTER_ARB_MODE_SIZE                       1        // Arbitration Mode
#define MMA_EDI_CONTROL_REGISTER_ARB_MODE_MSB                        12      
#define MMA_EDI_CONTROL_REGISTER_ARB_MODE_LSB                        12      
#define MMA_EDI_CONTROL_REGISTER_ARB_MODE_GOOD                       0        // MMA EDI transactions arbitrate for access to state shared by mission-mode operations. This is the default value after reset.
#define MMA_EDI_CONTROL_REGISTER_ARB_MODE_EVIL                       1        // MMA EDI transactions ignore mission mode activity and immediately access state shared by mission-mode operations.  Results computed by mission-mode operations may be corrupted.
#define MMA_EDI_CONTROL_REGISTER_TIMEOUT_SIZE                        12       // Period before a MMA EDI register read transaction is aborted and returns an error. The default value after reset is 12'b111111111111 (4095 clock cycles).
#define MMA_EDI_CONTROL_REGISTER_TIMEOUT_MSB                         11      
#define MMA_EDI_CONTROL_REGISTER_TIMEOUT_LSB                         0       
// Declarations for reg HWA_BIAS0_8
#define HWA_BIAS0_8_SIZE                                             512     
#define HWA_BIAS0_8_MSB                                              511     
#define HWA_BIAS0_8_LSB                                              0       
#define HWA_BIAS0_8_ROW15_SIZE                                       32       // 32-bit bias for C row 15
#define HWA_BIAS0_8_ROW15_MSB                                        511     
#define HWA_BIAS0_8_ROW15_LSB                                        480     
#define HWA_BIAS0_8_ROW14_SIZE                                       32       // 32-bit bias for C row 14
#define HWA_BIAS0_8_ROW14_MSB                                        479     
#define HWA_BIAS0_8_ROW14_LSB                                        448     
#define HWA_BIAS0_8_ROW13_SIZE                                       32       // 32-bit bias for C row 13
#define HWA_BIAS0_8_ROW13_MSB                                        447     
#define HWA_BIAS0_8_ROW13_LSB                                        416     
#define HWA_BIAS0_8_ROW12_SIZE                                       32       // 32-bit bias for C row 12
#define HWA_BIAS0_8_ROW12_MSB                                        415     
#define HWA_BIAS0_8_ROW12_LSB                                        384     
#define HWA_BIAS0_8_ROW11_SIZE                                       32       // 32-bit bias for C row 11
#define HWA_BIAS0_8_ROW11_MSB                                        383     
#define HWA_BIAS0_8_ROW11_LSB                                        352     
#define HWA_BIAS0_8_ROW10_SIZE                                       32       // 32-bit bias for C row 10
#define HWA_BIAS0_8_ROW10_MSB                                        351     
#define HWA_BIAS0_8_ROW10_LSB                                        320     
#define HWA_BIAS0_8_ROW9_SIZE                                        32       // 32-bit bias for C row 9
#define HWA_BIAS0_8_ROW9_MSB                                         319     
#define HWA_BIAS0_8_ROW9_LSB                                         288     
#define HWA_BIAS0_8_ROW8_SIZE                                        32       // 32-bit bias for C row 8
#define HWA_BIAS0_8_ROW8_MSB                                         287     
#define HWA_BIAS0_8_ROW8_LSB                                         256     
#define HWA_BIAS0_8_ROW7_SIZE                                        32       // 32-bit bias for C row 7
#define HWA_BIAS0_8_ROW7_MSB                                         255     
#define HWA_BIAS0_8_ROW7_LSB                                         224     
#define HWA_BIAS0_8_ROW6_SIZE                                        32       // 32-bit bias for C row 6
#define HWA_BIAS0_8_ROW6_MSB                                         223     
#define HWA_BIAS0_8_ROW6_LSB                                         192     
#define HWA_BIAS0_8_ROW5_SIZE                                        32       // 32-bit bias for C row 5
#define HWA_BIAS0_8_ROW5_MSB                                         191     
#define HWA_BIAS0_8_ROW5_LSB                                         160     
#define HWA_BIAS0_8_ROW4_SIZE                                        32       // 32-bit bias for C row 4
#define HWA_BIAS0_8_ROW4_MSB                                         159     
#define HWA_BIAS0_8_ROW4_LSB                                         128     
#define HWA_BIAS0_8_ROW3_SIZE                                        32       // 32-bit bias for C row 3
#define HWA_BIAS0_8_ROW3_MSB                                         127     
#define HWA_BIAS0_8_ROW3_LSB                                         96      
#define HWA_BIAS0_8_ROW2_SIZE                                        32       // 32-bit bias for C row 2
#define HWA_BIAS0_8_ROW2_MSB                                         95      
#define HWA_BIAS0_8_ROW2_LSB                                         64      
#define HWA_BIAS0_8_ROW1_SIZE                                        32       // 32-bit bias for C row 1
#define HWA_BIAS0_8_ROW1_MSB                                         63      
#define HWA_BIAS0_8_ROW1_LSB                                         32      
#define HWA_BIAS0_8_ROW0_SIZE                                        32       // 32-bit bias for C row 0
#define HWA_BIAS0_8_ROW0_MSB                                         31      
#define HWA_BIAS0_8_ROW0_LSB                                         0       
// Declarations for reg HWA_BIAS1_8
#define HWA_BIAS1_8_SIZE                                             512     
#define HWA_BIAS1_8_MSB                                              511     
#define HWA_BIAS1_8_LSB                                              0       
#define HWA_BIAS1_8_ROW31_SIZE                                       32       // 32-bit bias for C row 31
#define HWA_BIAS1_8_ROW31_MSB                                        511     
#define HWA_BIAS1_8_ROW31_LSB                                        480     
#define HWA_BIAS1_8_ROW30_SIZE                                       32       // 32-bit bias for C row 30
#define HWA_BIAS1_8_ROW30_MSB                                        479     
#define HWA_BIAS1_8_ROW30_LSB                                        448     
#define HWA_BIAS1_8_ROW29_SIZE                                       32       // 32-bit bias for C row 29
#define HWA_BIAS1_8_ROW29_MSB                                        447     
#define HWA_BIAS1_8_ROW29_LSB                                        416     
#define HWA_BIAS1_8_ROW28_SIZE                                       32       // 32-bit bias for C row 28
#define HWA_BIAS1_8_ROW28_MSB                                        415     
#define HWA_BIAS1_8_ROW28_LSB                                        384     
#define HWA_BIAS1_8_ROW27_SIZE                                       32       // 32-bit bias for C row 27
#define HWA_BIAS1_8_ROW27_MSB                                        383     
#define HWA_BIAS1_8_ROW27_LSB                                        352     
#define HWA_BIAS1_8_ROW26_SIZE                                       32       // 32-bit bias for C row 26
#define HWA_BIAS1_8_ROW26_MSB                                        351     
#define HWA_BIAS1_8_ROW26_LSB                                        320     
#define HWA_BIAS1_8_ROW25_SIZE                                       32       // 32-bit bias for C row 25
#define HWA_BIAS1_8_ROW25_MSB                                        319     
#define HWA_BIAS1_8_ROW25_LSB                                        288     
#define HWA_BIAS1_8_ROW24_SIZE                                       32       // 32-bit bias for C row 24
#define HWA_BIAS1_8_ROW24_MSB                                        287     
#define HWA_BIAS1_8_ROW24_LSB                                        256     
#define HWA_BIAS1_8_ROW23_SIZE                                       32       // 32-bit bias for C row 23
#define HWA_BIAS1_8_ROW23_MSB                                        255     
#define HWA_BIAS1_8_ROW23_LSB                                        224     
#define HWA_BIAS1_8_ROW22_SIZE                                       32       // 32-bit bias for C row 22
#define HWA_BIAS1_8_ROW22_MSB                                        223     
#define HWA_BIAS1_8_ROW22_LSB                                        192     
#define HWA_BIAS1_8_ROW21_SIZE                                       32       // 32-bit bias for C row 21
#define HWA_BIAS1_8_ROW21_MSB                                        191     
#define HWA_BIAS1_8_ROW21_LSB                                        160     
#define HWA_BIAS1_8_ROW20_SIZE                                       32       // 32-bit bias for C row 20
#define HWA_BIAS1_8_ROW20_MSB                                        159     
#define HWA_BIAS1_8_ROW20_LSB                                        128     
#define HWA_BIAS1_8_ROW19_SIZE                                       32       // 32-bit bias for C row 19
#define HWA_BIAS1_8_ROW19_MSB                                        127     
#define HWA_BIAS1_8_ROW19_LSB                                        96      
#define HWA_BIAS1_8_ROW18_SIZE                                       32       // 32-bit bias for C row 18
#define HWA_BIAS1_8_ROW18_MSB                                        95      
#define HWA_BIAS1_8_ROW18_LSB                                        64      
#define HWA_BIAS1_8_ROW17_SIZE                                       32       // 32-bit bias for C row 17
#define HWA_BIAS1_8_ROW17_MSB                                        63      
#define HWA_BIAS1_8_ROW17_LSB                                        32      
#define HWA_BIAS1_8_ROW16_SIZE                                       32       // 32-bit bias for C row 16
#define HWA_BIAS1_8_ROW16_MSB                                        31      
#define HWA_BIAS1_8_ROW16_LSB                                        0       
// Declarations for reg HWA_BIAS2_8
#define HWA_BIAS2_8_SIZE                                             512     
#define HWA_BIAS2_8_MSB                                              511     
#define HWA_BIAS2_8_LSB                                              0       
#define HWA_BIAS2_8_ROW47_SIZE                                       32       // 32-bit bias for C row 47
#define HWA_BIAS2_8_ROW47_MSB                                        511     
#define HWA_BIAS2_8_ROW47_LSB                                        480     
#define HWA_BIAS2_8_ROW46_SIZE                                       32       // 32-bit bias for C row 46
#define HWA_BIAS2_8_ROW46_MSB                                        479     
#define HWA_BIAS2_8_ROW46_LSB                                        448     
#define HWA_BIAS2_8_ROW45_SIZE                                       32       // 32-bit bias for C row 45
#define HWA_BIAS2_8_ROW45_MSB                                        447     
#define HWA_BIAS2_8_ROW45_LSB                                        416     
#define HWA_BIAS2_8_ROW44_SIZE                                       32       // 32-bit bias for C row 44
#define HWA_BIAS2_8_ROW44_MSB                                        415     
#define HWA_BIAS2_8_ROW44_LSB                                        384     
#define HWA_BIAS2_8_ROW43_SIZE                                       32       // 32-bit bias for C row 43
#define HWA_BIAS2_8_ROW43_MSB                                        383     
#define HWA_BIAS2_8_ROW43_LSB                                        352     
#define HWA_BIAS2_8_ROW42_SIZE                                       32       // 32-bit bias for C row 42
#define HWA_BIAS2_8_ROW42_MSB                                        351     
#define HWA_BIAS2_8_ROW42_LSB                                        320     
#define HWA_BIAS2_8_ROW41_SIZE                                       32       // 32-bit bias for C row 41
#define HWA_BIAS2_8_ROW41_MSB                                        319     
#define HWA_BIAS2_8_ROW41_LSB                                        288     
#define HWA_BIAS2_8_ROW40_SIZE                                       32       // 32-bit bias for C row 40
#define HWA_BIAS2_8_ROW40_MSB                                        287     
#define HWA_BIAS2_8_ROW40_LSB                                        256     
#define HWA_BIAS2_8_ROW39_SIZE                                       32       // 32-bit bias for C row 39
#define HWA_BIAS2_8_ROW39_MSB                                        255     
#define HWA_BIAS2_8_ROW39_LSB                                        224     
#define HWA_BIAS2_8_ROW38_SIZE                                       32       // 32-bit bias for C row 38
#define HWA_BIAS2_8_ROW38_MSB                                        223     
#define HWA_BIAS2_8_ROW38_LSB                                        192     
#define HWA_BIAS2_8_ROW37_SIZE                                       32       // 32-bit bias for C row 37
#define HWA_BIAS2_8_ROW37_MSB                                        191     
#define HWA_BIAS2_8_ROW37_LSB                                        160     
#define HWA_BIAS2_8_ROW36_SIZE                                       32       // 32-bit bias for C row 36
#define HWA_BIAS2_8_ROW36_MSB                                        159     
#define HWA_BIAS2_8_ROW36_LSB                                        128     
#define HWA_BIAS2_8_ROW35_SIZE                                       32       // 32-bit bias for C row 35
#define HWA_BIAS2_8_ROW35_MSB                                        127     
#define HWA_BIAS2_8_ROW35_LSB                                        96      
#define HWA_BIAS2_8_ROW34_SIZE                                       32       // 32-bit bias for C row 34
#define HWA_BIAS2_8_ROW34_MSB                                        95      
#define HWA_BIAS2_8_ROW34_LSB                                        64      
#define HWA_BIAS2_8_ROW33_SIZE                                       32       // 32-bit bias for C row 33
#define HWA_BIAS2_8_ROW33_MSB                                        63      
#define HWA_BIAS2_8_ROW33_LSB                                        32      
#define HWA_BIAS2_8_ROW32_SIZE                                       32       // 32-bit bias for C row 32
#define HWA_BIAS2_8_ROW32_MSB                                        31      
#define HWA_BIAS2_8_ROW32_LSB                                        0       
// Declarations for reg HWA_BIAS3_8
#define HWA_BIAS3_8_SIZE                                             512     
#define HWA_BIAS3_8_MSB                                              511     
#define HWA_BIAS3_8_LSB                                              0       
#define HWA_BIAS3_8_ROW63_SIZE                                       32       // 32-bit bias for C row 63
#define HWA_BIAS3_8_ROW63_MSB                                        511     
#define HWA_BIAS3_8_ROW63_LSB                                        480     
#define HWA_BIAS3_8_ROW62_SIZE                                       32       // 32-bit bias for C row 62
#define HWA_BIAS3_8_ROW62_MSB                                        479     
#define HWA_BIAS3_8_ROW62_LSB                                        448     
#define HWA_BIAS3_8_ROW61_SIZE                                       32       // 32-bit bias for C row 61
#define HWA_BIAS3_8_ROW61_MSB                                        447     
#define HWA_BIAS3_8_ROW61_LSB                                        416     
#define HWA_BIAS3_8_ROW60_SIZE                                       32       // 32-bit bias for C row 60
#define HWA_BIAS3_8_ROW60_MSB                                        415     
#define HWA_BIAS3_8_ROW60_LSB                                        384     
#define HWA_BIAS3_8_ROW59_SIZE                                       32       // 32-bit bias for C row 59
#define HWA_BIAS3_8_ROW59_MSB                                        383     
#define HWA_BIAS3_8_ROW59_LSB                                        352     
#define HWA_BIAS3_8_ROW58_SIZE                                       32       // 32-bit bias for C row 58
#define HWA_BIAS3_8_ROW58_MSB                                        351     
#define HWA_BIAS3_8_ROW58_LSB                                        320     
#define HWA_BIAS3_8_ROW57_SIZE                                       32       // 32-bit bias for C row 57
#define HWA_BIAS3_8_ROW57_MSB                                        319     
#define HWA_BIAS3_8_ROW57_LSB                                        288     
#define HWA_BIAS3_8_ROW56_SIZE                                       32       // 32-bit bias for C row 56
#define HWA_BIAS3_8_ROW56_MSB                                        287     
#define HWA_BIAS3_8_ROW56_LSB                                        256     
#define HWA_BIAS3_8_ROW55_SIZE                                       32       // 32-bit bias for C row 55
#define HWA_BIAS3_8_ROW55_MSB                                        255     
#define HWA_BIAS3_8_ROW55_LSB                                        224     
#define HWA_BIAS3_8_ROW54_SIZE                                       32       // 32-bit bias for C row 54
#define HWA_BIAS3_8_ROW54_MSB                                        223     
#define HWA_BIAS3_8_ROW54_LSB                                        192     
#define HWA_BIAS3_8_ROW53_SIZE                                       32       // 32-bit bias for C row 53
#define HWA_BIAS3_8_ROW53_MSB                                        191     
#define HWA_BIAS3_8_ROW53_LSB                                        160     
#define HWA_BIAS3_8_ROW52_SIZE                                       32       // 32-bit bias for C row 52
#define HWA_BIAS3_8_ROW52_MSB                                        159     
#define HWA_BIAS3_8_ROW52_LSB                                        128     
#define HWA_BIAS3_8_ROW51_SIZE                                       32       // 32-bit bias for C row 51
#define HWA_BIAS3_8_ROW51_MSB                                        127     
#define HWA_BIAS3_8_ROW51_LSB                                        96      
#define HWA_BIAS3_8_ROW50_SIZE                                       32       // 32-bit bias for C row 50
#define HWA_BIAS3_8_ROW50_MSB                                        95      
#define HWA_BIAS3_8_ROW50_LSB                                        64      
#define HWA_BIAS3_8_ROW49_SIZE                                       32       // 32-bit bias for C row 49
#define HWA_BIAS3_8_ROW49_MSB                                        63      
#define HWA_BIAS3_8_ROW49_LSB                                        32      
#define HWA_BIAS3_8_ROW48_SIZE                                       32       // 32-bit bias for C row 48
#define HWA_BIAS3_8_ROW48_MSB                                        31      
#define HWA_BIAS3_8_ROW48_LSB                                        0       
// Declarations for reg HWA_BIAS0_16
#define HWA_BIAS0_16_SIZE                                            512     
#define HWA_BIAS0_16_MSB                                             511     
#define HWA_BIAS0_16_LSB                                             0       
#define HWA_BIAS0_16_ROW7_SIZE                                       64       // 64-bit bias for C row 7
#define HWA_BIAS0_16_ROW7_MSB                                        511     
#define HWA_BIAS0_16_ROW7_LSB                                        448     
#define HWA_BIAS0_16_ROW6_SIZE                                       64       // 64-bit bias for C row 6
#define HWA_BIAS0_16_ROW6_MSB                                        447     
#define HWA_BIAS0_16_ROW6_LSB                                        384     
#define HWA_BIAS0_16_ROW5_SIZE                                       64       // 64-bit bias for C row 5
#define HWA_BIAS0_16_ROW5_MSB                                        383     
#define HWA_BIAS0_16_ROW5_LSB                                        320     
#define HWA_BIAS0_16_ROW4_SIZE                                       64       // 64-bit bias for C row 4
#define HWA_BIAS0_16_ROW4_MSB                                        319     
#define HWA_BIAS0_16_ROW4_LSB                                        256     
#define HWA_BIAS0_16_ROW3_SIZE                                       64       // 64-bit bias for C row 3
#define HWA_BIAS0_16_ROW3_MSB                                        255     
#define HWA_BIAS0_16_ROW3_LSB                                        192     
#define HWA_BIAS0_16_ROW2_SIZE                                       64       // 64-bit bias for C row 2
#define HWA_BIAS0_16_ROW2_MSB                                        191     
#define HWA_BIAS0_16_ROW2_LSB                                        128     
#define HWA_BIAS0_16_ROW1_SIZE                                       64       // 64-bit bias for C row 1
#define HWA_BIAS0_16_ROW1_MSB                                        127     
#define HWA_BIAS0_16_ROW1_LSB                                        64      
#define HWA_BIAS0_16_ROW0_SIZE                                       64       // 64-bit bias for C row 0
#define HWA_BIAS0_16_ROW0_MSB                                        63      
#define HWA_BIAS0_16_ROW0_LSB                                        0       
// Declarations for reg HWA_BIAS1_16
#define HWA_BIAS1_16_SIZE                                            512     
#define HWA_BIAS1_16_MSB                                             511     
#define HWA_BIAS1_16_LSB                                             0       
#define HWA_BIAS1_16_ROW15_SIZE                                      64       // 64-bit bias for C row 15
#define HWA_BIAS1_16_ROW15_MSB                                       511     
#define HWA_BIAS1_16_ROW15_LSB                                       448     
#define HWA_BIAS1_16_ROW14_SIZE                                      64       // 64-bit bias for C row 14
#define HWA_BIAS1_16_ROW14_MSB                                       447     
#define HWA_BIAS1_16_ROW14_LSB                                       384     
#define HWA_BIAS1_16_ROW13_SIZE                                      64       // 64-bit bias for C row 13
#define HWA_BIAS1_16_ROW13_MSB                                       383     
#define HWA_BIAS1_16_ROW13_LSB                                       320     
#define HWA_BIAS1_16_ROW12_SIZE                                      64       // 64-bit bias for C row 12
#define HWA_BIAS1_16_ROW12_MSB                                       319     
#define HWA_BIAS1_16_ROW12_LSB                                       256     
#define HWA_BIAS1_16_ROW11_SIZE                                      64       // 64-bit bias for C row 11
#define HWA_BIAS1_16_ROW11_MSB                                       255     
#define HWA_BIAS1_16_ROW11_LSB                                       192     
#define HWA_BIAS1_16_ROW10_SIZE                                      64       // 64-bit bias for C row 10
#define HWA_BIAS1_16_ROW10_MSB                                       191     
#define HWA_BIAS1_16_ROW10_LSB                                       128     
#define HWA_BIAS1_16_ROW9_SIZE                                       64       // 64-bit bias for C row 9
#define HWA_BIAS1_16_ROW9_MSB                                        127     
#define HWA_BIAS1_16_ROW9_LSB                                        64      
#define HWA_BIAS1_16_ROW8_SIZE                                       64       // 64-bit bias for C row 8
#define HWA_BIAS1_16_ROW8_MSB                                        63      
#define HWA_BIAS1_16_ROW8_LSB                                        0       
// Declarations for reg HWA_BIAS2_16
#define HWA_BIAS2_16_SIZE                                            512     
#define HWA_BIAS2_16_MSB                                             511     
#define HWA_BIAS2_16_LSB                                             0       
#define HWA_BIAS2_16_ROW23_SIZE                                      64       // 64-bit bias for C row 23
#define HWA_BIAS2_16_ROW23_MSB                                       511     
#define HWA_BIAS2_16_ROW23_LSB                                       448     
#define HWA_BIAS2_16_ROW22_SIZE                                      64       // 64-bit bias for C row 22
#define HWA_BIAS2_16_ROW22_MSB                                       447     
#define HWA_BIAS2_16_ROW22_LSB                                       384     
#define HWA_BIAS2_16_ROW21_SIZE                                      64       // 64-bit bias for C row 21
#define HWA_BIAS2_16_ROW21_MSB                                       383     
#define HWA_BIAS2_16_ROW21_LSB                                       320     
#define HWA_BIAS2_16_ROW20_SIZE                                      64       // 64-bit bias for C row 20
#define HWA_BIAS2_16_ROW20_MSB                                       319     
#define HWA_BIAS2_16_ROW20_LSB                                       256     
#define HWA_BIAS2_16_ROW19_SIZE                                      64       // 64-bit bias for C row 19
#define HWA_BIAS2_16_ROW19_MSB                                       255     
#define HWA_BIAS2_16_ROW19_LSB                                       192     
#define HWA_BIAS2_16_ROW18_SIZE                                      64       // 64-bit bias for C row 18
#define HWA_BIAS2_16_ROW18_MSB                                       191     
#define HWA_BIAS2_16_ROW18_LSB                                       128     
#define HWA_BIAS2_16_ROW17_SIZE                                      64       // 64-bit bias for C row 17
#define HWA_BIAS2_16_ROW17_MSB                                       127     
#define HWA_BIAS2_16_ROW17_LSB                                       64      
#define HWA_BIAS2_16_ROW16_SIZE                                      64       // 64-bit bias for C row 16
#define HWA_BIAS2_16_ROW16_MSB                                       63      
#define HWA_BIAS2_16_ROW16_LSB                                       0       
// Declarations for reg HWA_BIAS3_16
#define HWA_BIAS3_16_SIZE                                            512     
#define HWA_BIAS3_16_MSB                                             511     
#define HWA_BIAS3_16_LSB                                             0       
#define HWA_BIAS3_16_ROW31_SIZE                                      64       // 64-bit bias for C row 31
#define HWA_BIAS3_16_ROW31_MSB                                       511     
#define HWA_BIAS3_16_ROW31_LSB                                       448     
#define HWA_BIAS3_16_ROW30_SIZE                                      64       // 64-bit bias for C row 30
#define HWA_BIAS3_16_ROW30_MSB                                       447     
#define HWA_BIAS3_16_ROW30_LSB                                       384     
#define HWA_BIAS3_16_ROW29_SIZE                                      64       // 64-bit bias for C row 29
#define HWA_BIAS3_16_ROW29_MSB                                       383     
#define HWA_BIAS3_16_ROW29_LSB                                       320     
#define HWA_BIAS3_16_ROW28_SIZE                                      64       // 64-bit bias for C row 28
#define HWA_BIAS3_16_ROW28_MSB                                       319     
#define HWA_BIAS3_16_ROW28_LSB                                       256     
#define HWA_BIAS3_16_ROW27_SIZE                                      64       // 64-bit bias for C row 27
#define HWA_BIAS3_16_ROW27_MSB                                       255     
#define HWA_BIAS3_16_ROW27_LSB                                       192     
#define HWA_BIAS3_16_ROW26_SIZE                                      64       // 64-bit bias for C row 26
#define HWA_BIAS3_16_ROW26_MSB                                       191     
#define HWA_BIAS3_16_ROW26_LSB                                       128     
#define HWA_BIAS3_16_ROW25_SIZE                                      64       // 64-bit bias for C row 25
#define HWA_BIAS3_16_ROW25_MSB                                       127     
#define HWA_BIAS3_16_ROW25_LSB                                       64      
#define HWA_BIAS3_16_ROW24_SIZE                                      64       // 64-bit bias for C row 24
#define HWA_BIAS3_16_ROW24_MSB                                       63      
#define HWA_BIAS3_16_ROW24_LSB                                       0       
// Declarations for reg HWA_BUSY
#define HWA_BUSY_SIZE                                                512     
#define HWA_BUSY_MSB                                                 511     
#define HWA_BUSY_LSB                                                 0       
#define HWA_BUSY_GATING_CONTROL_SIZE                                 1        // Internal root clock gating control.
#define HWA_BUSY_GATING_CONTROL_MSB                                  511     
#define HWA_BUSY_GATING_CONTROL_LSB                                  511     
#define HWA_BUSY_GATING_CONTROL_OFF                                  1        // Disable internal root clock gating
#define HWA_BUSY_GATING_CONTROL_AUTO                                 0        // Internal MMA logic can disable the MMA clock (default)
#define HWA_BUSY_RESERVED_SIZE                                       487      // Reserved field. Software should not expect any specific values in this field.
#define HWA_BUSY_RESERVED_MSB                                        510     
#define HWA_BUSY_RESERVED_LSB                                        24      
#define HWA_BUSY_BUSY_SIZE                                           24       // Transfer buffer FIFO entry valid state bits (read-only).
#define HWA_BUSY_BUSY_MSB                                            23      
#define HWA_BUSY_BUSY_LSB                                            0       
// Declarations for reg HWA_CONFIG
#define HWA_CONFIG_SIZE                                              512     
#define HWA_CONFIG_MSB                                               511     
#define HWA_CONFIG_LSB                                               0       
#define HWA_CONFIG_PARITYCTRL_SIZE                                   2        // Parity control, typically cleared in mission mode.
#define HWA_CONFIG_PARITYCTRL_MSB                                    511     
#define HWA_CONFIG_PARITYCTRL_LSB                                    510     
#define HWA_CONFIG_PARITYCTRL_NORMAL                                 0        // Parity is computed by hardware on write operations to HWA_CONFIG and HWA_OFFSET and checking is enabled.
#define HWA_CONFIG_PARITYCTRL_PNCM_CK                                1        // Parity is not computed by hardware on write operations to HWA_CONFIG and HWA_OFFSET (parity bits hold their prior state) and checking is enabled.
#define HWA_CONFIG_PARITYCTRL_PCM_NCK                                2        // Parity is computed by hardware on write operations to HWA_CONFIG and HWA_OFFSET and checking is disabled.
#define HWA_CONFIG_PARITYCTRL_PNCM_NCK                               3        // Parity is not computed by hardware on write operations to HWA_CONFIG and HWA_OFFSET (parity bits hold their prior state) and checking is disabled.
#define HWA_CONFIG_RSVD_SIZE                                         6        // Reserved field. Software should write zero to this field.
#define HWA_CONFIG_RSVD_MSB                                          509     
#define HWA_CONFIG_RSVD_LSB                                          504     
#define HWA_CONFIG_X_CONFIG_SIZE                                     104      // X FSM configuration field. See X_CONFIG bus definition.
#define HWA_CONFIG_X_CONFIG_MSB                                      503     
#define HWA_CONFIG_X_CONFIG_LSB                                      400     
#define HWA_CONFIG_C_CONFIG_SIZE                                     272      // C FSM configuration field. See C_CONFIG bus definition.
#define HWA_CONFIG_C_CONFIG_MSB                                      399     
#define HWA_CONFIG_C_CONFIG_LSB                                      128     
#define HWA_CONFIG_B_CONFIG_SIZE                                     96       // B FSM configuration field. See B_CONFIG bus definition.
#define HWA_CONFIG_B_CONFIG_MSB                                      127     
#define HWA_CONFIG_B_CONFIG_LSB                                      32      
#define HWA_CONFIG_A_CONFIG_SIZE                                     32       // A FSM configuration field. See A_CONFIG bus definition.
#define HWA_CONFIG_A_CONFIG_MSB                                      31      
#define HWA_CONFIG_A_CONFIG_LSB                                      0       
// Declarations for bus A_CONFIG
#define A_CONFIG_SIZE                                                32      
#define A_CONFIG_MSB                                                 31      
#define A_CONFIG_LSB                                                 0       
#define A_CONFIG_RSVD_SIZE                                           1        // Reserved field. Software should write zero to this field.
#define A_CONFIG_RSVD_MSB                                            31      
#define A_CONFIG_RSVD_LSB                                            31      
#define A_CONFIG_ARF_SIZE_SIZE                                       7        // ARF array size for read and write operations.
#define A_CONFIG_ARF_SIZE_MSB                                        30      
#define A_CONFIG_ARF_SIZE_LSB                                        24      
#define A_CONFIG_RSVD_1_SIZE                                         1        // Reserved field. Software should write zero to this field.
#define A_CONFIG_RSVD_1_MSB                                          23      
#define A_CONFIG_RSVD_1_LSB                                          23      
#define A_CONFIG_ARF_BASE_SIZE                                       6        // Base value of circular buffer in the A operand register file when ARF_CTRL is ARF_ENABLE.
#define A_CONFIG_ARF_BASE_MSB                                        22      
#define A_CONFIG_ARF_BASE_LSB                                        17      
#define A_CONFIG_ARF_CTRL_SIZE                                       1        // A operand register file write enable.
#define A_CONFIG_ARF_CTRL_MSB                                        16      
#define A_CONFIG_ARF_CTRL_LSB                                        16      
#define A_CONFIG_ARF_CTRL_ARF_DISABLE                                0        // A operands are used directly and not stored in the A operand register file.
#define A_CONFIG_ARF_CTRL_ARF_ENABLE                                 1        // MMA instructions that supply an A operand write into the A operand register file.
#define A_CONFIG_RSVD_2_SIZE                                         7        // Reserved field. Software should write zero to this field.
#define A_CONFIG_RSVD_2_MSB                                          15      
#define A_CONFIG_RSVD_2_LSB                                          9       
#define A_CONFIG_ALUTEN_SIZE                                         1        // A vector element lookup table expansion from 4-bit element packed vectors to 8-bit element packed vectors.
#define A_CONFIG_ALUTEN_MSB                                          8       
#define A_CONFIG_ALUTEN_LSB                                          8       
#define A_CONFIG_ALUTEN_LUT                                          1        // Packed 4-bit operands (3:0, 7:4 , 11:8, etc.) are passed through a lookup table. The ATYPE field must be set to INT8 or UINT8. Lookup table values are located in the HWA_OFFSET register.
#define A_CONFIG_ALUTEN_NOLUT                                        0        // Bypass the lookup table
#define A_CONFIG_RSVD_3_SIZE                                         4        // Reserved field. Software should write zero to this field.
#define A_CONFIG_RSVD_3_MSB                                          7       
#define A_CONFIG_RSVD_3_LSB                                          4       
#define A_CONFIG_ATYPE_SIZE                                          4        // A vector element type. Width must be consistent with the B FSM setting.
#define A_CONFIG_ATYPE_MSB                                           3       
#define A_CONFIG_ATYPE_LSB                                           0       
#define A_CONFIG_ATYPE_SP                                            11       // Single precision (32-bit) data
#define A_CONFIG_ATYPE_BF16                                          9        // Brain Float (16-bit) data
#define A_CONFIG_ATYPE_FP8                                           8        // 8 bit floating point (8-bit) data
#define A_CONFIG_ATYPE_INT32                                         7        // Signed word (32-bit) data
#define A_CONFIG_ATYPE_RESERVED                                      6        // Undefined A vector element type
#define A_CONFIG_ATYPE_INT16                                         5        // Signed half word (16-bit) data
#define A_CONFIG_ATYPE_INT8                                          4        // Signed byte data
#define A_CONFIG_ATYPE_UINT32                                        3        // Unsigned word (32-bit) data
#define A_CONFIG_ATYPE_RESERVED_1                                    2        // Undefined A vector element type
#define A_CONFIG_ATYPE_UINT16                                        1        // Unsigned half word (16-bit) data
#define A_CONFIG_ATYPE_UINT8                                         0        // Unsigned byte (8-bit) data
// Declarations for bus B_CONFIG
#define B_CONFIG_SIZE                                                96      
#define B_CONFIG_MSB                                                 95      
#define B_CONFIG_LSB                                                 0       
#define B_CONFIG_RSVD_SIZE                                           23       // Reserved field. Software should write zero to this field.
#define B_CONFIG_RSVD_MSB                                            95      
#define B_CONFIG_RSVD_LSB                                            73      
#define B_CONFIG_FLOAT_SIZE                                          1        // B matrix element type is floating point
#define B_CONFIG_FLOAT_MSB                                           72      
#define B_CONFIG_FLOAT_LSB                                           72      
#define B_CONFIG_FLOAT_ENABLED                                       1        // Floating point element type enabled
#define B_CONFIG_FLOAT_DISABLED                                      0        // Floating point element type disabled
#define B_CONFIG_BOFFSET_SIZE                                        8        // Global row or column offset
#define B_CONFIG_BOFFSET_MSB                                         71      
#define B_CONFIG_BOFFSET_LSB                                         64      
#define B_CONFIG_RSVD_1_SIZE                                         6        // Reserved field. Software should write zero to this field.
#define B_CONFIG_RSVD_1_MSB                                          63      
#define B_CONFIG_RSVD_1_LSB                                          58      
#define B_CONFIG_BCNT1_ENABLE_SIZE                                   1        // Enable bit for optional independent B row write row counter for B bank 1.                                                        Setting this bit also has the side-effects introducing an independent B_STATUS.BRSTCNT counter                                                        and reducing the effective width of the B_STATUS.BSWCNT field from 32-bits to 24-bits to                                                        accomodate the B_STATUS.BRSTCNT1 counter.
#define B_CONFIG_BCNT1_ENABLE_MSB                                    57      
#define B_CONFIG_BCNT1_ENABLE_LSB                                    57      
#define B_CONFIG_BSTART_SIZE                                         1        // Initial B bank selection for writing B matrix data
#define B_CONFIG_BSTART_MSB                                          56      
#define B_CONFIG_BSTART_LSB                                          56      
#define B_CONFIG_RSVD_2_SIZE                                         7        // Reserved field. Software should write zero to this field.
#define B_CONFIG_RSVD_2_MSB                                          55      
#define B_CONFIG_RSVD_2_LSB                                          49      
#define B_CONFIG_ORDER_SIZE                                          1        // B load transpose control
#define B_CONFIG_ORDER_MSB                                           48      
#define B_CONFIG_ORDER_LSB                                           48      
#define B_CONFIG_ORDER_COL                                           1        // Column-major order (transposed)
#define B_CONFIG_ORDER_ROW                                           0        // Row-major order (non-transposed)
#define B_CONFIG_RSVD_3_SIZE                                         2        // Reserved field. Software should write zero to this field.
#define B_CONFIG_RSVD_3_MSB                                          47      
#define B_CONFIG_RSVD_3_LSB                                          46      
#define B_CONFIG_B4EXP_SIZE                                          2        // B operand expansion control to convert 4-bit operands to 8-bit operands.
#define B_CONFIG_B4EXP_MSB                                           45      
#define B_CONFIG_B4EXP_LSB                                           44      
#define B_CONFIG_B4EXP_MMA1                                          0        // No expansion (MMA 1.0 behavior).
#define B_CONFIG_B4EXP_UNSIGNED                                      1        // Packed 4-bit B elements are expanded to 8-bit SIMD lanes by 0-padding.  The BTYPE field must be set to SIZE8.
#define B_CONFIG_B4EXP_SIGNED                                        2        // Packed 4-bit B elements are expanded to 8-bit SIMD lanes by sign extension.  The BTYPE field must be set to SIZE8.
#define B_CONFIG_B4EXP_RESERVED                                      3        // Reserved encoding. Software should not use this encoding.
#define B_CONFIG_LDBOPT_SIZE                                         2        // Control for enhanced B operand row loading.
#define B_CONFIG_LDBOPT_MSB                                          43      
#define B_CONFIG_LDBOPT_LSB                                          42      
#define B_CONFIG_LDBOPT_MMA1                                         0        // MMA 1.0 B loading (single row)
#define B_CONFIG_LDBOPT_LDB5X                                        1        // Enable 5x row load for the HWALDBC instruction. The BTYPE field must be set to SIZE8 or SIZE16. HWA_OFFSET must be 512'h0. Transpose mode is not supported.
#define B_CONFIG_LDBOPT_LDB2X                                        2        // Enable 2x row load for the HWALDBC instruction. There are no constraints on BTYPE. HWA_OFFSET must be 512'h0.  Transpose mode is not supported. The LDB2X function is sometimes called double-stuff mode (naming credit: Arthur Redfern).
#define B_CONFIG_LDBOPT_LDB3X                                        3        // Enable 3x row load for the HWALDBC instruction. The BTYPE field must be set to SIZE8 or SIZE16. HWA_OFFSET must be 512'h0. Transpose mode is not supported.
#define B_CONFIG_BTYPE_SIZE                                          2        // B matrix element type.  Width must be consistent with the A FSM setting and C FSM setting.
#define B_CONFIG_BTYPE_MSB                                           41      
#define B_CONFIG_BTYPE_LSB                                           40      
#define B_CONFIG_BTYPE_SIZE32                                        3        // Signed or unsigned word (32-bit) data
#define B_CONFIG_BTYPE_RESERVED                                      2        // Undefined B matrix element type
#define B_CONFIG_BTYPE_SIZE16                                        1        // Signed or unsigned half word (16-bit) data
#define B_CONFIG_BTYPE_SIZE8                                         0        // Signed or unsigned 8-bit data
#define B_CONFIG_BRSTPER_SIZE                                        8        // B offset reset period
#define B_CONFIG_BRSTPER_MSB                                         39      
#define B_CONFIG_BRSTPER_LSB                                         32      
#define B_CONFIG_BSWPER_SIZE                                         32       // B bank switch period
#define B_CONFIG_BSWPER_MSB                                          31      
#define B_CONFIG_BSWPER_LSB                                          0       
// Declarations for bus C_CONFIG
#define C_CONFIG_SIZE                                                272     
#define C_CONFIG_MSB                                                 271     
#define C_CONFIG_LSB                                                 0       
#define C_CONFIG_CWRSTPER_SIZE                                       8        // C write row offset reset period for computations
#define C_CONFIG_CWRSTPER_MSB                                        271     
#define C_CONFIG_CWRSTPER_LSB                                        264     
#define C_CONFIG_CRRSTPER_SIZE                                       8        // C read row offset reset period
#define C_CONFIG_CRRSTPER_MSB                                        263     
#define C_CONFIG_CRRSTPER_LSB                                        256     
#define C_CONFIG_CWSWPER_SIZE                                        32       // C bank switch period for computations writes
#define C_CONFIG_CWSWPER_MSB                                         255     
#define C_CONFIG_CWSWPER_LSB                                         224     
#define C_CONFIG_CRSWPER_SIZE                                        32       // C bank switch period for read  instructions
#define C_CONFIG_CRSWPER_MSB                                         223     
#define C_CONFIG_CRSWPER_LSB                                         192     
#define C_CONFIG_BSWPER_SIZE                                         32       // B bank switch period
#define C_CONFIG_BSWPER_MSB                                          191     
#define C_CONFIG_BSWPER_LSB                                          160     
#define C_CONFIG_OP0PER_SIZE                                         32       // Operation0 period. See C FSM description for behavior when OP0PER equals zero.
#define C_CONFIG_OP0PER_MSB                                          159     
#define C_CONFIG_OP0PER_LSB                                          128     
#define C_CONFIG_OP1PER_SIZE                                         32       // Operation1 period. See C FSM description for behavior when OP1PER equals zero.
#define C_CONFIG_OP1PER_MSB                                          127     
#define C_CONFIG_OP1PER_LSB                                          96      
#define C_CONFIG_CLRSTPER_SIZE                                       8        // C write row offset reset period for HWALD* instructions
#define C_CONFIG_CLRSTPER_MSB                                        95      
#define C_CONFIG_CLRSTPER_LSB                                        88      
#define C_CONFIG_CLSWPER_SIZE                                        8        // C bank switch period for HWALD* instruction writes
#define C_CONFIG_CLSWPER_MSB                                         87      
#define C_CONFIG_CLSWPER_LSB                                         80      
#define C_CONFIG_RSVD_SIZE                                           1        // Reserved field. Software should write zero to this field.
#define C_CONFIG_RSVD_MSB                                            79      
#define C_CONFIG_RSVD_LSB                                            79      
#define C_CONFIG_CLOFFSET_SIZE                                       7        // When A_STATUS.ARF_CTRL is ARF_DISABLE, C row write offset for HWALD* instructions. This value is scaled by 4x for HWLDDST X1 mode alignment with the row-granular address. When A_STATUS.ARF_CTRL is ARF_ENABLE, this field holds the ARF circular buffer size.
#define C_CONFIG_CLOFFSET_MSB                                        78      
#define C_CONFIG_CLOFFSET_LSB                                        72      
#define C_CONFIG_RSVD_1_SIZE                                         2        // Reserved field. Software should write zero to this field.
#define C_CONFIG_RSVD_1_MSB                                          71      
#define C_CONFIG_RSVD_1_LSB                                          70      
#define C_CONFIG_CWOFFSET_SIZE                                       6        // C row write offset for computations
#define C_CONFIG_CWOFFSET_MSB                                        69      
#define C_CONFIG_CWOFFSET_LSB                                        64      
#define C_CONFIG_RSVD_2_SIZE                                         2        // Reserved field. Software should write zero to this field.
#define C_CONFIG_RSVD_2_MSB                                          63      
#define C_CONFIG_RSVD_2_LSB                                          62      
#define C_CONFIG_CROFFSET_SIZE                                       6        // C row read offset
#define C_CONFIG_CROFFSET_MSB                                        61      
#define C_CONFIG_CROFFSET_LSB                                        56      
#define C_CONFIG_RSVD_3_SIZE                                         3        // Reserved field. Software should write zero to this field.
#define C_CONFIG_RSVD_3_MSB                                          55      
#define C_CONFIG_RSVD_3_LSB                                          53      
#define C_CONFIG_CLSTART_SIZE                                        1        // Initial C bank selection for writing operands from HWALD*
#define C_CONFIG_CLSTART_MSB                                         52      
#define C_CONFIG_CLSTART_LSB                                         52      
#define C_CONFIG_CWSTART_SIZE                                        1        // Initial C bank selection for writing computation results
#define C_CONFIG_CWSTART_MSB                                         51      
#define C_CONFIG_CWSTART_LSB                                         51      
#define C_CONFIG_CRSTART_SIZE                                        1        // Initial C bank selection for reading operands
#define C_CONFIG_CRSTART_MSB                                         50      
#define C_CONFIG_CRSTART_LSB                                         50      
#define C_CONFIG_BSTART_SIZE                                         1        // Initial B bank selection for reading B matrix data for the matrix computation
#define C_CONFIG_BSTART_MSB                                          49      
#define C_CONFIG_BSTART_LSB                                          49      
#define C_CONFIG_OPSTART_SIZE                                        1        // Initial C operation selection
#define C_CONFIG_OPSTART_MSB                                         48      
#define C_CONFIG_OPSTART_LSB                                         48      
#define C_CONFIG_RSVD_4_SIZE                                         4        // Reserved field. Software should write zero to this field.
#define C_CONFIG_RSVD_4_MSB                                          47      
#define C_CONFIG_RSVD_4_LSB                                          44      
#define C_CONFIG_HWLDTYPE_SIZE                                       4        // C matrix element type from a HWALD* instruction. In larger destination fields, signed types are sign extended and unsigned types are zero-extended. Future MMA architectures may not support this feature and the HWA_BIAS* registers should be used.
#define C_CONFIG_HWLDTYPE_MSB                                        43      
#define C_CONFIG_HWLDTYPE_LSB                                        40      
#define C_CONFIG_HWLDTYPE_RESERVED                                   15       // Undefined C operand element type
#define C_CONFIG_HWLDTYPE_RESERVED_1                                 14       // Undefined C operand element type
#define C_CONFIG_HWLDTYPE_RESERVED_2                                 13       // Undefined C operand element type
#define C_CONFIG_HWLDTYPE_RESERVED_3                                 12       // Undefined C operand element type
#define C_CONFIG_HWLDTYPE_INT32                                      11       // Signed word (32-bit) data.
#define C_CONFIG_HWLDTYPE_RESERVED_4                                 10       // Undefined C operand element type.
#define C_CONFIG_HWLDTYPE_INT16                                      9        // Signed half word (16-bit) data.
#define C_CONFIG_HWLDTYPE_INT8                                       8        // Signed byte (8-bit) data.
#define C_CONFIG_HWLDTYPE_RESERVED_5                                 7        // Undefined C operand element type
#define C_CONFIG_HWLDTYPE_RESERVED_6                                 6        // Undefined C operand element type
#define C_CONFIG_HWLDTYPE_RESERVED_7                                 5        // Undefined C operand element type
#define C_CONFIG_HWLDTYPE_RESERVED_8                                 4        // Undefined C operand element type
#define C_CONFIG_HWLDTYPE_UINT32                                     3        // Unsigned word (32-bit) data.
#define C_CONFIG_HWLDTYPE_RESERVED_9                                 2        // Undefined C operand element type
#define C_CONFIG_HWLDTYPE_UINT16                                     1        // Unsigned half word (16-bit) data.
#define C_CONFIG_HWLDTYPE_UINT8                                      0        // Unsigned byte (8-bit) data.
#define C_CONFIG_RSVD_5_SIZE                                         5        // Reserved field. Software should write zero to this field.
#define C_CONFIG_RSVD_5_MSB                                          39      
#define C_CONFIG_RSVD_5_LSB                                          35      
#define C_CONFIG_HWLDDST_SIZE                                        3        // Element size written into C matrix storage and element scaling. Future MMA architectures may not support this feature and the HWA_BIAS* registers should be used.
#define C_CONFIG_HWLDDST_MSB                                         34      
#define C_CONFIG_HWLDDST_LSB                                         32      
#define C_CONFIG_HWLDDST_X1                                          7        // Input data is copied directly into C storage with no scaling
#define C_CONFIG_HWLDDST_RESERVED                                    6        // Undefined C storage element type
#define C_CONFIG_HWLDDST_RESERVED_1                                  5        // Undefined C storage element type
#define C_CONFIG_HWLDDST_RESERVED_2                                  4        // Undefined C storage element type
#define C_CONFIG_HWLDDST_X4_3                                        3        // Input data is extended to 4 times the original bit width and shifted left by 3x the original bit width. Undefined for unsigned data.
#define C_CONFIG_HWLDDST_X4_2                                        2        // Input data is extended to 4 times the original bit width and shifted left by 2x the original bit width. Undefined for unsigned data.
#define C_CONFIG_HWLDDST_X4                                          1        // Input data is extended to 4 times the original bit width and shifted left by 1x the original bit width. Defined for signed and unsigned data.
#define C_CONFIG_HWLDDST_X4_0                                        0        // Input data is extended to 4 times the original bit width and shifted left by 0x the original bit width. Undefined for unsigned data.
#define C_CONFIG_RSVD_6_SIZE                                         4        // Reserved field. Software should write zero to this field.
#define C_CONFIG_RSVD_6_MSB                                          31      
#define C_CONFIG_RSVD_6_LSB                                          28      
#define C_CONFIG_BIASORDER_SIZE                                      1        // When set, the matrix formed by bias values is transposed (unique value per column rather than unique value per row).
#define C_CONFIG_BIASORDER_MSB                                       27      
#define C_CONFIG_BIASORDER_LSB                                       27      
#define C_CONFIG_BIASORDER_BIAS_COLUMN                               0        // BIAS* values are interpreted as a column vector, with values duplicated across the row used in the calculation.
#define C_CONFIG_BIASORDER_BIAS_ROW                                  1        // BIAS* values are interpreted as a row vector in the calculation.
#define C_CONFIG_LOP1_SIZE                                           1        // Left operand selection for OPERATION1
#define C_CONFIG_LOP1_MSB                                            26      
#define C_CONFIG_LOP1_LSB                                            26      
#define C_CONFIG_LOP1_C                                              0        // LOP1 is a C matrix row.
#define C_CONFIG_LOP1_BIAS                                           1        // LOP1 is a BIAS.
#define C_CONFIG_OPERATION1_SIZE                                     2        // Operation 1 calculation performed for HWA.*OP.* instructions. Operation 1 executes with a period defined in C_CONFIG.OP1PER.
#define C_CONFIG_OPERATION1_MSB                                      25      
#define C_CONFIG_OPERATION1_LSB                                      24      
#define C_CONFIG_OPERATION1_MULPLUS                                  3        //  Compute LOP1+(A&#215;<b>B</b>)
#define C_CONFIG_OPERATION1_MULMINUS                                 2        //  Compute LOP1-(A&#215;<b>B</b>)
#define C_CONFIG_OPERATION1_MULNEGATE                                1        //  Compute -(A&#215;<b>B</b>) 
#define C_CONFIG_OPERATION1_MUL                                      0        //  Compute (A&#215;<b>B</b>)  
#define C_CONFIG_RSVD_7_SIZE                                         5        // Reserved field. Software should write zero to this field.
#define C_CONFIG_RSVD_7_MSB                                          23      
#define C_CONFIG_RSVD_7_LSB                                          19      
#define C_CONFIG_LOP0_SIZE                                           1        // Left operand selection for OPERATION0
#define C_CONFIG_LOP0_MSB                                            18      
#define C_CONFIG_LOP0_LSB                                            18      
#define C_CONFIG_LOP0_C                                              0        // LOP0 is a C matrix row.
#define C_CONFIG_LOP0_BIAS                                           1        // LOP0 is a BIAS.
#define C_CONFIG_OPERATION0_SIZE                                     2        // Operation 0 calculation performed for HWA.*OP.* instructions. Operation 0 executes with a period defined in C_CONFIG.OP0PER.
#define C_CONFIG_OPERATION0_MSB                                      17      
#define C_CONFIG_OPERATION0_LSB                                      16      
#define C_CONFIG_OPERATION0_MULPLUS                                  3        //  Compute LOP0+(A&#215;<b>B</b>)
#define C_CONFIG_OPERATION0_MULMINUS                                 2        //  Compute LOP0-(A&#215;<b>B</b>)
#define C_CONFIG_OPERATION0_MULNEGATE                                1        //  Compute -(A&#215;<b>B</b>) 
#define C_CONFIG_OPERATION0_MUL                                      0        //  Compute (A&#215;<b>B</b>)  
#define C_CONFIG_RSVD_8_SIZE                                         4        // Reserved field. Software should write zero to this field.
#define C_CONFIG_RSVD_8_MSB                                          15      
#define C_CONFIG_RSVD_8_LSB                                          12      
#define C_CONFIG_BTYPE_SIZE                                          4        // B matrix element type and bias table element size. This must be consistent with the B FSM setting.
#define C_CONFIG_BTYPE_MSB                                           11      
#define C_CONFIG_BTYPE_LSB                                           8       
#define C_CONFIG_BTYPE_SP                                            11       // Single precision (32-bit) data
#define C_CONFIG_BTYPE_BF16                                          9        // Brain Float (16-bit) data
#define C_CONFIG_BTYPE_FP8                                           8        // 8 bit floating point (8-bit) data
#define C_CONFIG_BTYPE_INT32                                         7        // Signed word (32-bit) data. C element width will be 128 bits. Bias table element size is undefined.
#define C_CONFIG_BTYPE_RESERVED                                      6        // Undefined B matrix element type.
#define C_CONFIG_BTYPE_INT16                                         5        // Signed half word (16-bit) data. C element width will be 64 bits. Bias table elements are 64 bits.
#define C_CONFIG_BTYPE_INT8                                          4        // Signed byte (8-bit) data. C element width will be 32 bits. Bias table elements are 32 bits.
#define C_CONFIG_BTYPE_UINT32                                        3        // Unsigned word (32-bit) data. C element width will be 128 bits. Bias table element size is undefined.
#define C_CONFIG_BTYPE_RESERVED_1                                    2        // Undefined B matrix element type
#define C_CONFIG_BTYPE_UINT16                                        1        // Unsigned half word (16-bit) data. C element width will be 64 bits. Bias table elements are 64 bits.
#define C_CONFIG_BTYPE_UINT8                                         0        // Unsigned byte (8-bit) data. C element width will be 32 bits. Bias table elements are 32 bits.
#define C_CONFIG_ARF_C7_SIZE                                         1        // ARF read addresses are supplied by the host C7 processor as an argument to the HWAOP or HWAOPXFER instructions.  This argument will typically be a Streaming Address (SA) generator. When this bit is set, the ARF_BASE and ARF_SIZE fields are ignored on ARF reads.
#define C_CONFIG_ARF_C7_MSB                                          7       
#define C_CONFIG_ARF_C7_LSB                                          7       
#define C_CONFIG_ARF_BASE_SIZE                                       6        // ARF read pointer base value when ARF_C7 is cleared.
#define C_CONFIG_ARF_BASE_MSB                                        6       
#define C_CONFIG_ARF_BASE_LSB                                        1       
#define C_CONFIG_ATYPE_SIZE                                          1        // A vector signed/unsigned control. This must be consistent with A FSM setting.
#define C_CONFIG_ATYPE_MSB                                           0       
#define C_CONFIG_ATYPE_LSB                                           0       
#define C_CONFIG_ATYPE_SA                                            1        // A vector elements are signed.
#define C_CONFIG_ATYPE_UA                                            0        // A vector elements are unsigned.
// Declarations for bus X_CONFIG
#define X_CONFIG_SIZE                                                104     
#define X_CONFIG_MSB                                                 103     
#define X_CONFIG_LSB                                                 0       
#define X_CONFIG_SAT_MAX_15_9_SIZE                                   7        // PSAT SAT_MAX[15:9]
#define X_CONFIG_SAT_MAX_15_9_MSB                                    103     
#define X_CONFIG_SAT_MAX_15_9_LSB                                    97      
#define X_CONFIG_CSTART_SIZE                                         1        // Initial C bank selection
#define X_CONFIG_CSTART_MSB                                          96      
#define X_CONFIG_CSTART_LSB                                          96      
#define X_CONFIG_COFFSET_SIZE                                        8        // C matrix row read address offset
#define X_CONFIG_COFFSET_MSB                                         95      
#define X_CONFIG_COFFSET_LSB                                         88      
#define X_CONFIG_CRRSTPER_SIZE                                       8        // C read row offset reset period
#define X_CONFIG_CRRSTPER_MSB                                        87      
#define X_CONFIG_CRRSTPER_LSB                                        80      
#define X_CONFIG_CSWPER_SIZE                                         32       // C read bank switch period
#define X_CONFIG_CSWPER_MSB                                          79      
#define X_CONFIG_CSWPER_LSB                                          48      
#define X_CONFIG_SAT_MAX_8_4_SIZE                                    5        // PSAT SAT_MAX[8:4]
#define X_CONFIG_SAT_MAX_8_4_MSB                                     47      
#define X_CONFIG_SAT_MAX_8_4_LSB                                     43      
#define X_CONFIG_CTYPE_SIZE                                          3        // C matrix element type. This must be consistent with the B FSM setting.
#define X_CONFIG_CTYPE_MSB                                           42      
#define X_CONFIG_CTYPE_LSB                                           40      
#define X_CONFIG_CTYPE_INT128                                        7        // Signed 128-bit data
#define X_CONFIG_CTYPE_RESERVED                                      6        // Undefined C matrix element type
#define X_CONFIG_CTYPE_INT64                                         5        // Signed 64-bit data
#define X_CONFIG_CTYPE_INT32                                         4        // Signed 32-bit data
#define X_CONFIG_CTYPE_UINT128                                       3        // Unsigned 128-bit data
#define X_CONFIG_CTYPE_RESERVED_1                                    2        // Undefined C matrix element type
#define X_CONFIG_CTYPE_UINT64                                        1        // Unsigned 64-bit data
#define X_CONFIG_CTYPE_UINT32                                        0        // Unsigned 32-bit data
#define X_CONFIG_SAT_MAX_3_0_SIZE                                    4        // PSAT SAT_MAX[3:0]
#define X_CONFIG_SAT_MAX_3_0_MSB                                     39      
#define X_CONFIG_SAT_MAX_3_0_LSB                                     36      
#define X_CONFIG_XTYPE_SIZE                                          4        // Transfer buffer element type. Not all combinations of CTYPE and XTYPE are supported.
#define X_CONFIG_XTYPE_MSB                                           35      
#define X_CONFIG_XTYPE_LSB                                           32      
#define X_CONFIG_XTYPE_RESERVED                                      15       // Undefined transfer buffer element type
#define X_CONFIG_XTYPE_RESERVED_1                                    14       // Undefined transfer buffer element type
#define X_CONFIG_XTYPE_INT128                                        13       // Signed 128-bit data
#define X_CONFIG_XTYPE_INT64                                         12       // Signed 64-bit data
#define X_CONFIG_XTYPE_INT32                                         11       // Signed 32-bit data
#define X_CONFIG_XTYPE_RESERVED_2                                    10       // Undefined transfer buffer element type
#define X_CONFIG_XTYPE_INT16                                         9        // Signed 16-bit data
#define X_CONFIG_XTYPE_INT8                                          8        // Signed 8-bit data
#define X_CONFIG_XTYPE_RESERVED_3                                    7        // Undefined transfer buffer element type
#define X_CONFIG_XTYPE_RESERVED_4                                    6        // Undefined transfer buffer element type
#define X_CONFIG_XTYPE_UINT128                                       5        // Unsigned 128-bit data
#define X_CONFIG_XTYPE_UINT64                                        4        // Unsigned 64-bit data
#define X_CONFIG_XTYPE_UINT32                                        3        // Unsigned 32-bit data
#define X_CONFIG_XTYPE_RESERVED_5                                    2        // Undefined transfer buffer element type
#define X_CONFIG_XTYPE_UINT16                                        1        // Unsigned 16-bit data
#define X_CONFIG_XTYPE_UINT8                                         0        // Unsigned 8-bit data
#define X_CONFIG_VPACKN_SIZE                                         1        // 4-bit packing control.
#define X_CONFIG_VPACKN_MSB                                          31      
#define X_CONFIG_VPACKN_LSB                                          31      
#define X_CONFIG_VPACKN_DISABLE                                      0        // 4-bit packing is disabled (MMA 1.0 behavior).
#define X_CONFIG_VPACKN_ENABLE                                       1        // Bits [3:0] of each 8-bit SIMD lane are packed into bits [255:0] of the result after shifting, rounding and non-linearity.
#define X_CONFIG_SHIFT_SIZE                                          7        // When SCALE_SHIFT_CTRL is DISABLE, this is the right shift amount. It is signed or unsigned depending on the CTYPE field value. Right shift amounts greater than width of the type specified in the CTYPE field result in undefined behavior. When SCALE_SHIFT_CTRL is ENABLE, the encoding is defined below,
#define X_CONFIG_SHIFT_MSB                                           30      
#define X_CONFIG_SHIFT_LSB                                           24      
#define X_CONFIG_SHIFT_ROW_UNSIGNED                                  64       // Per-row shift and unsigned scale from HWA_SCALE(0|1) and HWA_SCALE(0|1)
#define X_CONFIG_SHIFT_ROW_SIGNED                                    65       // Per-row shift and signed scale from HWA_SCALE(0|1) and HWA_SCALE(0|1)
#define X_CONFIG_SHIFT_COL_UNSIGNED                                  66       // Per-column shift and unsigned scale from HWA_SCALE(0|1) and HWA_SCALE(0|1)
#define X_CONFIG_SHIFT_COL_SIGNED                                    67       // Per-column shift and signed scale from HWA_SCALE(0|1) and HWA_SCALE(0|1)
#define X_CONFIG_RSVD_SIZE                                           1        // Reserved field.  Software should write 0 to this field.
#define X_CONFIG_RSVD_MSB                                            23      
#define X_CONFIG_RSVD_LSB                                            23      
#define X_CONFIG_SCALE_SHIFT_CTRL_SIZE                               1        // Per-row shift and scaling control.
#define X_CONFIG_SCALE_SHIFT_CTRL_MSB                                22      
#define X_CONFIG_SCALE_SHIFT_CTRL_LSB                                22      
#define X_CONFIG_SCALE_SHIFT_CTRL_DISABLE                            0        // No per-row indirect shift, no per-row scale (MMA 1.0 behavior).
#define X_CONFIG_SCALE_SHIFT_CTRL_ENABLE                             1        // Enable scale from HWA_SCALE(0|1) and indirect shift from HWA_SHIFT(0|1). Additional control is overloaded on the SHIFT field.
#define X_CONFIG_RANGE_SIZE                                          2        // Min/Max range accumulation control on C matrix reads by X FSM.
#define X_CONFIG_RANGE_MSB                                           21      
#define X_CONFIG_RANGE_LSB                                           20      
#define X_CONFIG_RANGE_DISABLE_NOINIT                                0        // Disable updates to the min/max range calculation and do not initialize the min/max accumulators.
#define X_CONFIG_RANGE_DISABLE_INIT                                  1        // Disable updates to the min/max range calculation and initialize the min/max accumulators.
#define X_CONFIG_RANGE_ENABLE_NOINIT                                 2        // Enable updates to the min/max range calculation and do not initialize the min/max accumulators.
#define X_CONFIG_RANGE_ENABLE_INIT                                   3        // Enable updates to the min/max range calculation and initialize the min/max accumulators.
#define X_CONFIG_SAT_MIN_15_13_SIZE                                  3        // PSAT SAT_MIN[15:13].  See the X Finite State Machine section for more information.
#define X_CONFIG_SAT_MIN_15_13_MSB                                   19      
#define X_CONFIG_SAT_MIN_15_13_LSB                                   17      
#define X_CONFIG_RE_SIZE                                             1        // Enable rounding via 1/2 LSB addition after shifting. Rounding is suppressed by hardware when the SHIFT field is 7'b0
#define X_CONFIG_RE_MSB                                              16      
#define X_CONFIG_RE_LSB                                              16      
#define X_CONFIG_SAT_MIN_12_6_SIZE                                   7        // PSAT SAT_MIN[12:6]. See the X Finite State Machine section for more information.
#define X_CONFIG_SAT_MIN_12_6_MSB                                    15      
#define X_CONFIG_SAT_MIN_12_6_LSB                                    9       
#define X_CONFIG_SAT_SIZE                                            1        // Enable saturation in the transfer buffer element type after optional rounding. For predictable results, ReLU or PSAT should not be enabled with SAT.  Saturation is supported for all result sizes and signed/unsigned combinations.
#define X_CONFIG_SAT_MSB                                             8       
#define X_CONFIG_SAT_LSB                                             8       
#define X_CONFIG_SAT_MIN_5_0_SIZE                                    6        // PSAT SAT_MIN[5:0]. See the X Finite State Machine section for more information.
#define X_CONFIG_SAT_MIN_5_0_MSB                                     7       
#define X_CONFIG_SAT_MIN_5_0_LSB                                     2       
#define X_CONFIG_PSAT_SIZE                                           1        // Parameterized saturation function with minimum and maximum saturation values in the HWA_CONFIG.X_CONFIG.SAT_(MIN|MAX)* regsiter. PSAT is only supported for 16-bit results from 64-bit C elements and 8-bit results from 32-bit C elements and signed/unsigned combinations.  Using PSAT nonlinearity any other combinations of C element sizes and result sizes is undefined. PSAT should not be enabled with ReLU or SAT. See the X Finite State Machine section for more information.
#define X_CONFIG_PSAT_MSB                                            1       
#define X_CONFIG_PSAT_LSB                                            1       
#define X_CONFIG_RELU_SIZE                                           1        // Enable Rectified Linear Units non-linearity after optional rounding. For predictable results, SAT should not be enabled with ReLU.
#define X_CONFIG_RELU_MSB                                            0       
#define X_CONFIG_RELU_LSB                                            0       
// Declarations for reg HWA_OFFSET
#define HWA_OFFSET_SIZE                                              512     
#define HWA_OFFSET_MSB                                               511     
#define HWA_OFFSET_LSB                                               0       
#define HWA_OFFSET_A_LUT_VAL15_SIZE                                  8        // A FSM LUT value for data input value 4'b1111
#define HWA_OFFSET_A_LUT_VAL15_MSB                                   511     
#define HWA_OFFSET_A_LUT_VAL15_LSB                                   504     
#define HWA_OFFSET_OFFSET63_SIZE                                     6        // Local offset 63 for (u)int8
#define HWA_OFFSET_OFFSET63_MSB                                      503     
#define HWA_OFFSET_OFFSET63_LSB                                      498     
#define HWA_OFFSET_OFFSET62_SIZE                                     6        // Local offset 62 for (u)int8, offset 31 for (u)int16
#define HWA_OFFSET_OFFSET62_MSB                                      497     
#define HWA_OFFSET_OFFSET62_LSB                                      492     
#define HWA_OFFSET_OFFSET61_SIZE                                     6        // Local offset 61 for (u)int8
#define HWA_OFFSET_OFFSET61_MSB                                      491     
#define HWA_OFFSET_OFFSET61_LSB                                      486     
#define HWA_OFFSET_OFFSET60_SIZE                                     6        // Local offset 60 for (u)int8, offset 30 for (u)int16, offset 15 for (u)int32
#define HWA_OFFSET_OFFSET60_MSB                                      485     
#define HWA_OFFSET_OFFSET60_LSB                                      480     
#define HWA_OFFSET_A_LUT_VAL14_SIZE                                  8        // A FSM LUT value for data input value 4'b1110
#define HWA_OFFSET_A_LUT_VAL14_MSB                                   479     
#define HWA_OFFSET_A_LUT_VAL14_LSB                                   472     
#define HWA_OFFSET_OFFSET59_SIZE                                     6        // Local offset 59 for (u)int8
#define HWA_OFFSET_OFFSET59_MSB                                      471     
#define HWA_OFFSET_OFFSET59_LSB                                      466     
#define HWA_OFFSET_OFFSET58_SIZE                                     6        // Local offset 58 for (u)int8, offset 29 for (u)int16
#define HWA_OFFSET_OFFSET58_MSB                                      465     
#define HWA_OFFSET_OFFSET58_LSB                                      460     
#define HWA_OFFSET_OFFSET57_SIZE                                     6        // Local offset 57 for (u)int8
#define HWA_OFFSET_OFFSET57_MSB                                      459     
#define HWA_OFFSET_OFFSET57_LSB                                      454     
#define HWA_OFFSET_OFFSET56_SIZE                                     6        // Local offset 56 for (u)int8, offset 28 for (u)int16, offset 14 for (u)int32
#define HWA_OFFSET_OFFSET56_MSB                                      453     
#define HWA_OFFSET_OFFSET56_LSB                                      448     
#define HWA_OFFSET_A_LUT_VAL13_SIZE                                  8        // A FSM LUT value for data input value 4'b1101
#define HWA_OFFSET_A_LUT_VAL13_MSB                                   447     
#define HWA_OFFSET_A_LUT_VAL13_LSB                                   440     
#define HWA_OFFSET_OFFSET55_SIZE                                     6        // Local offset 55 for (u)int8
#define HWA_OFFSET_OFFSET55_MSB                                      439     
#define HWA_OFFSET_OFFSET55_LSB                                      434     
#define HWA_OFFSET_OFFSET54_SIZE                                     6        // Local offset 54 for (u)int8, offset 27 for (u)int16
#define HWA_OFFSET_OFFSET54_MSB                                      433     
#define HWA_OFFSET_OFFSET54_LSB                                      428     
#define HWA_OFFSET_OFFSET53_SIZE                                     6        // Local offset 53 for (u)int8
#define HWA_OFFSET_OFFSET53_MSB                                      427     
#define HWA_OFFSET_OFFSET53_LSB                                      422     
#define HWA_OFFSET_OFFSET52_SIZE                                     6        // Local offset 52 for (u)int8, offset 26 for (u)int16, offset 13 for (u)int32
#define HWA_OFFSET_OFFSET52_MSB                                      421     
#define HWA_OFFSET_OFFSET52_LSB                                      416     
#define HWA_OFFSET_A_LUT_VAL12_SIZE                                  8        // A FSM LUT value for data input value 4'b1100
#define HWA_OFFSET_A_LUT_VAL12_MSB                                   415     
#define HWA_OFFSET_A_LUT_VAL12_LSB                                   408     
#define HWA_OFFSET_OFFSET51_SIZE                                     6        // Local offset 51 for (u)int8
#define HWA_OFFSET_OFFSET51_MSB                                      407     
#define HWA_OFFSET_OFFSET51_LSB                                      402     
#define HWA_OFFSET_OFFSET50_SIZE                                     6        // Local offset 50 for (u)int8, offset 25 for (u)int16
#define HWA_OFFSET_OFFSET50_MSB                                      401     
#define HWA_OFFSET_OFFSET50_LSB                                      396     
#define HWA_OFFSET_OFFSET49_SIZE                                     6        // Local offset 49 for (u)int8
#define HWA_OFFSET_OFFSET49_MSB                                      395     
#define HWA_OFFSET_OFFSET49_LSB                                      390     
#define HWA_OFFSET_OFFSET48_SIZE                                     6        // Local offset 48 for (u)int8, offset 24 for (u)int16, offset 12 for (u)int32
#define HWA_OFFSET_OFFSET48_MSB                                      389     
#define HWA_OFFSET_OFFSET48_LSB                                      384     
#define HWA_OFFSET_A_LUT_VAL11_SIZE                                  8        // A FSM LUT value for data input value 4'b1011
#define HWA_OFFSET_A_LUT_VAL11_MSB                                   383     
#define HWA_OFFSET_A_LUT_VAL11_LSB                                   376     
#define HWA_OFFSET_OFFSET47_SIZE                                     6        // Local offset 47 for (u)int8
#define HWA_OFFSET_OFFSET47_MSB                                      375     
#define HWA_OFFSET_OFFSET47_LSB                                      370     
#define HWA_OFFSET_OFFSET46_SIZE                                     6        // Local offset 46 for (u)int8, offset 23 for (u)int16
#define HWA_OFFSET_OFFSET46_MSB                                      369     
#define HWA_OFFSET_OFFSET46_LSB                                      364     
#define HWA_OFFSET_OFFSET45_SIZE                                     6        // Local offset 45 for (u)int8
#define HWA_OFFSET_OFFSET45_MSB                                      363     
#define HWA_OFFSET_OFFSET45_LSB                                      358     
#define HWA_OFFSET_OFFSET44_SIZE                                     6        // Local offset 44 for (u)int8, offset 22 for (u)int16, offset 11 for (u)int32
#define HWA_OFFSET_OFFSET44_MSB                                      357     
#define HWA_OFFSET_OFFSET44_LSB                                      352     
#define HWA_OFFSET_A_LUT_VAL10_SIZE                                  8        // A FSM LUT value for data input value 4'b1010
#define HWA_OFFSET_A_LUT_VAL10_MSB                                   351     
#define HWA_OFFSET_A_LUT_VAL10_LSB                                   344     
#define HWA_OFFSET_OFFSET43_SIZE                                     6        // Local offset 43 for (u)int8
#define HWA_OFFSET_OFFSET43_MSB                                      343     
#define HWA_OFFSET_OFFSET43_LSB                                      338     
#define HWA_OFFSET_OFFSET42_SIZE                                     6        // Local offset 42 for (u)int8, offset 21 for (u)int16
#define HWA_OFFSET_OFFSET42_MSB                                      337     
#define HWA_OFFSET_OFFSET42_LSB                                      332     
#define HWA_OFFSET_OFFSET41_SIZE                                     6        // Local offset 41 for (u)int8
#define HWA_OFFSET_OFFSET41_MSB                                      331     
#define HWA_OFFSET_OFFSET41_LSB                                      326     
#define HWA_OFFSET_OFFSET40_SIZE                                     6        // Local offset 40 for (u)int8, offset 20 for (u)int16, offset 10 for (u)int32
#define HWA_OFFSET_OFFSET40_MSB                                      325     
#define HWA_OFFSET_OFFSET40_LSB                                      320     
#define HWA_OFFSET_A_LUT_VAL9_SIZE                                   8        // A FSM LUT value for data input value 4'b1001
#define HWA_OFFSET_A_LUT_VAL9_MSB                                    319     
#define HWA_OFFSET_A_LUT_VAL9_LSB                                    312     
#define HWA_OFFSET_OFFSET39_SIZE                                     6        // Local offset 39 for (u)int8
#define HWA_OFFSET_OFFSET39_MSB                                      311     
#define HWA_OFFSET_OFFSET39_LSB                                      306     
#define HWA_OFFSET_OFFSET38_SIZE                                     6        // Local offset 38 for (u)int8, offset 19 for (u)int16
#define HWA_OFFSET_OFFSET38_MSB                                      305     
#define HWA_OFFSET_OFFSET38_LSB                                      300     
#define HWA_OFFSET_OFFSET37_SIZE                                     6        // Local offset 37 for (u)int8
#define HWA_OFFSET_OFFSET37_MSB                                      299     
#define HWA_OFFSET_OFFSET37_LSB                                      294     
#define HWA_OFFSET_OFFSET36_SIZE                                     6        // Local offset 36 for (u)int8, offset 18 for (u)int16, offset 9 for (u)int32
#define HWA_OFFSET_OFFSET36_MSB                                      293     
#define HWA_OFFSET_OFFSET36_LSB                                      288     
#define HWA_OFFSET_A_LUT_VAL8_SIZE                                   8        // A FSM LUT value for data input value 4'b1000
#define HWA_OFFSET_A_LUT_VAL8_MSB                                    287     
#define HWA_OFFSET_A_LUT_VAL8_LSB                                    280     
#define HWA_OFFSET_OFFSET35_SIZE                                     6        // Local offset 35 for (u)int8
#define HWA_OFFSET_OFFSET35_MSB                                      279     
#define HWA_OFFSET_OFFSET35_LSB                                      274     
#define HWA_OFFSET_OFFSET34_SIZE                                     6        // Local offset 34 for (u)int8, offset 17 for (u)int16
#define HWA_OFFSET_OFFSET34_MSB                                      273     
#define HWA_OFFSET_OFFSET34_LSB                                      268     
#define HWA_OFFSET_OFFSET33_SIZE                                     6        // Local offset 33 for (u)int8
#define HWA_OFFSET_OFFSET33_MSB                                      267     
#define HWA_OFFSET_OFFSET33_LSB                                      262     
#define HWA_OFFSET_OFFSET32_SIZE                                     6        // Local offset 32 for (u)int8, offset 16 for (u)int16, offset 8 for (u)int32
#define HWA_OFFSET_OFFSET32_MSB                                      261     
#define HWA_OFFSET_OFFSET32_LSB                                      256     
#define HWA_OFFSET_A_LUT_VAL7_SIZE                                   8        // A FSM LUT value for data input value 4'b0111
#define HWA_OFFSET_A_LUT_VAL7_MSB                                    255     
#define HWA_OFFSET_A_LUT_VAL7_LSB                                    248     
#define HWA_OFFSET_OFFSET31_SIZE                                     6        // Local offset 31 for (u)int8
#define HWA_OFFSET_OFFSET31_MSB                                      247     
#define HWA_OFFSET_OFFSET31_LSB                                      242     
#define HWA_OFFSET_OFFSET30_SIZE                                     6        // Local offset 30 for (u)int8, offset 15 for (u)int16
#define HWA_OFFSET_OFFSET30_MSB                                      241     
#define HWA_OFFSET_OFFSET30_LSB                                      236     
#define HWA_OFFSET_OFFSET29_SIZE                                     6        // Local offset 29 for (u)int8
#define HWA_OFFSET_OFFSET29_MSB                                      235     
#define HWA_OFFSET_OFFSET29_LSB                                      230     
#define HWA_OFFSET_OFFSET28_SIZE                                     6        // Local offset 28 for (u)int8, offset 14 for (u)int16, offset 7 for (u)int32
#define HWA_OFFSET_OFFSET28_MSB                                      229     
#define HWA_OFFSET_OFFSET28_LSB                                      224     
#define HWA_OFFSET_A_LUT_VAL6_SIZE                                   8        // A FSM LUT value for data input value 4'b0110
#define HWA_OFFSET_A_LUT_VAL6_MSB                                    223     
#define HWA_OFFSET_A_LUT_VAL6_LSB                                    216     
#define HWA_OFFSET_OFFSET27_SIZE                                     6        // Local offset 27 for (u)int8
#define HWA_OFFSET_OFFSET27_MSB                                      215     
#define HWA_OFFSET_OFFSET27_LSB                                      210     
#define HWA_OFFSET_OFFSET26_SIZE                                     6        // Local offset 26 for (u)int8, offset 13 for (u)int16
#define HWA_OFFSET_OFFSET26_MSB                                      209     
#define HWA_OFFSET_OFFSET26_LSB                                      204     
#define HWA_OFFSET_OFFSET25_SIZE                                     6        // Local offset 25 for (u)int8
#define HWA_OFFSET_OFFSET25_MSB                                      203     
#define HWA_OFFSET_OFFSET25_LSB                                      198     
#define HWA_OFFSET_OFFSET24_SIZE                                     6        // Local offset 24 for (u)int8, offset 12 for (u)int16, offset 6 for (u)int32
#define HWA_OFFSET_OFFSET24_MSB                                      197     
#define HWA_OFFSET_OFFSET24_LSB                                      192     
#define HWA_OFFSET_A_LUT_VAL5_SIZE                                   8        // A FSM LUT value for data input value 4'b0101
#define HWA_OFFSET_A_LUT_VAL5_MSB                                    191     
#define HWA_OFFSET_A_LUT_VAL5_LSB                                    184     
#define HWA_OFFSET_OFFSET23_SIZE                                     6        // Local offset 23 for (u)int8
#define HWA_OFFSET_OFFSET23_MSB                                      183     
#define HWA_OFFSET_OFFSET23_LSB                                      178     
#define HWA_OFFSET_OFFSET22_SIZE                                     6        // Local offset 22 for (u)int8, offset 11 for (u)int16
#define HWA_OFFSET_OFFSET22_MSB                                      177     
#define HWA_OFFSET_OFFSET22_LSB                                      172     
#define HWA_OFFSET_OFFSET21_SIZE                                     6        // Local offset 21 for (u)int8
#define HWA_OFFSET_OFFSET21_MSB                                      171     
#define HWA_OFFSET_OFFSET21_LSB                                      166     
#define HWA_OFFSET_OFFSET20_SIZE                                     6        // Local offset 20 for (u)int8, offset 10 for (u)int16, offset 5 for (u)int32
#define HWA_OFFSET_OFFSET20_MSB                                      165     
#define HWA_OFFSET_OFFSET20_LSB                                      160     
#define HWA_OFFSET_A_LUT_VAL4_SIZE                                   8        // A FSM LUT value for data input value 4'b0100
#define HWA_OFFSET_A_LUT_VAL4_MSB                                    159     
#define HWA_OFFSET_A_LUT_VAL4_LSB                                    152     
#define HWA_OFFSET_OFFSET19_SIZE                                     6        // Local offset 19 for (u)int8
#define HWA_OFFSET_OFFSET19_MSB                                      151     
#define HWA_OFFSET_OFFSET19_LSB                                      146     
#define HWA_OFFSET_OFFSET18_SIZE                                     6        // Local offset 18 for (u)int8, offset 9 for (u)int16
#define HWA_OFFSET_OFFSET18_MSB                                      145     
#define HWA_OFFSET_OFFSET18_LSB                                      140     
#define HWA_OFFSET_OFFSET17_SIZE                                     6        // Local offset 17 for (u)int8
#define HWA_OFFSET_OFFSET17_MSB                                      139     
#define HWA_OFFSET_OFFSET17_LSB                                      134     
#define HWA_OFFSET_OFFSET16_SIZE                                     6        // Local offset 16 for (u)int8, offset 8 for (u)int16, offset 4 for (u)int32
#define HWA_OFFSET_OFFSET16_MSB                                      133     
#define HWA_OFFSET_OFFSET16_LSB                                      128     
#define HWA_OFFSET_A_LUT_VAL3_SIZE                                   8        // A FSM LUT value for data input value 4'b0011
#define HWA_OFFSET_A_LUT_VAL3_MSB                                    127     
#define HWA_OFFSET_A_LUT_VAL3_LSB                                    120     
#define HWA_OFFSET_OFFSET15_SIZE                                     6        // Local offset 15 for (u)int8
#define HWA_OFFSET_OFFSET15_MSB                                      119     
#define HWA_OFFSET_OFFSET15_LSB                                      114     
#define HWA_OFFSET_OFFSET14_SIZE                                     6        // Local offset 14 for (u)int8, offset 7 for (u)int16
#define HWA_OFFSET_OFFSET14_MSB                                      113     
#define HWA_OFFSET_OFFSET14_LSB                                      108     
#define HWA_OFFSET_OFFSET13_SIZE                                     6        // Local offset 13 for (u)int8
#define HWA_OFFSET_OFFSET13_MSB                                      107     
#define HWA_OFFSET_OFFSET13_LSB                                      102     
#define HWA_OFFSET_OFFSET12_SIZE                                     6        // Local offset 12 for (u)int8, offset 6 for (u)int16, offset 3 for (u)int32
#define HWA_OFFSET_OFFSET12_MSB                                      101     
#define HWA_OFFSET_OFFSET12_LSB                                      96      
#define HWA_OFFSET_A_LUT_VAL2_SIZE                                   8        // A FSM LUT value for data input value 4'b0010
#define HWA_OFFSET_A_LUT_VAL2_MSB                                    95      
#define HWA_OFFSET_A_LUT_VAL2_LSB                                    88      
#define HWA_OFFSET_OFFSET11_SIZE                                     6        // Local offset 11 for (u)int8
#define HWA_OFFSET_OFFSET11_MSB                                      87      
#define HWA_OFFSET_OFFSET11_LSB                                      82      
#define HWA_OFFSET_OFFSET10_SIZE                                     6        // Local offset 10 for (u)int8, offset 5 for (u)int16
#define HWA_OFFSET_OFFSET10_MSB                                      81      
#define HWA_OFFSET_OFFSET10_LSB                                      76      
#define HWA_OFFSET_OFFSET9_SIZE                                      6        // Local offset 9  for (u)int8
#define HWA_OFFSET_OFFSET9_MSB                                       75      
#define HWA_OFFSET_OFFSET9_LSB                                       70      
#define HWA_OFFSET_OFFSET8_SIZE                                      6        // Local offset 8  for (u)int8, offset 4 for (u)int16, offset 2 for (u)int32
#define HWA_OFFSET_OFFSET8_MSB                                       69      
#define HWA_OFFSET_OFFSET8_LSB                                       64      
#define HWA_OFFSET_A_LUT_VAL1_SIZE                                   8        // A FSM LUT value for data input value 4'b0001
#define HWA_OFFSET_A_LUT_VAL1_MSB                                    63      
#define HWA_OFFSET_A_LUT_VAL1_LSB                                    56      
#define HWA_OFFSET_OFFSET7_SIZE                                      6        // Local offset 7  for (u)int8
#define HWA_OFFSET_OFFSET7_MSB                                       55      
#define HWA_OFFSET_OFFSET7_LSB                                       50      
#define HWA_OFFSET_OFFSET6_SIZE                                      6        // Local offset 6  for (u)int8, offset 3 for (u)int16
#define HWA_OFFSET_OFFSET6_MSB                                       49      
#define HWA_OFFSET_OFFSET6_LSB                                       44      
#define HWA_OFFSET_OFFSET5_SIZE                                      6        // Local offset 5  for (u)int8
#define HWA_OFFSET_OFFSET5_MSB                                       43      
#define HWA_OFFSET_OFFSET5_LSB                                       38      
#define HWA_OFFSET_OFFSET4_SIZE                                      6        // Local offset 4  for (u)int8, offset 2 for (u)int16, offset 1 for (u)int32
#define HWA_OFFSET_OFFSET4_MSB                                       37      
#define HWA_OFFSET_OFFSET4_LSB                                       32      
#define HWA_OFFSET_A_LUT_VAL0_SIZE                                   8        // A FSM LUT value for data input value 4'b0000
#define HWA_OFFSET_A_LUT_VAL0_MSB                                    31      
#define HWA_OFFSET_A_LUT_VAL0_LSB                                    24      
#define HWA_OFFSET_OFFSET3_SIZE                                      6        // Local offset 3  for (u)int8
#define HWA_OFFSET_OFFSET3_MSB                                       23      
#define HWA_OFFSET_OFFSET3_LSB                                       18      
#define HWA_OFFSET_OFFSET2_SIZE                                      6        // Local offset 2  for (u)int8, offset 1 for (u)int16
#define HWA_OFFSET_OFFSET2_MSB                                       17      
#define HWA_OFFSET_OFFSET2_LSB                                       12      
#define HWA_OFFSET_OFFSET1_SIZE                                      6        // Local offset 1  for (u)int8
#define HWA_OFFSET_OFFSET1_MSB                                       11      
#define HWA_OFFSET_OFFSET1_LSB                                       6       
#define HWA_OFFSET_OFFSET0_SIZE                                      6        // Local offset 0  for (u)int8, (u)int16, (u)int32
#define HWA_OFFSET_OFFSET0_MSB                                       5       
#define HWA_OFFSET_OFFSET0_LSB                                       0       
// Declarations for reg HWA_SCALE0_8
#define HWA_SCALE0_8_SIZE                                            512     
#define HWA_SCALE0_8_MSB                                             511     
#define HWA_SCALE0_8_LSB                                             0       
#define HWA_SCALE0_8_ROW63_SIZE                                      8        // 8-bit scale for C bank 0 row or column 63
#define HWA_SCALE0_8_ROW63_MSB                                       511     
#define HWA_SCALE0_8_ROW63_LSB                                       504     
#define HWA_SCALE0_8_ROW62_SIZE                                      8        // 8-bit scale for C bank 0 row or column 62
#define HWA_SCALE0_8_ROW62_MSB                                       503     
#define HWA_SCALE0_8_ROW62_LSB                                       496     
#define HWA_SCALE0_8_ROW61_SIZE                                      8        // 8-bit scale for C bank 0 row or column 61
#define HWA_SCALE0_8_ROW61_MSB                                       495     
#define HWA_SCALE0_8_ROW61_LSB                                       488     
#define HWA_SCALE0_8_ROW60_SIZE                                      8        // 8-bit scale for C bank 0 row or column 60
#define HWA_SCALE0_8_ROW60_MSB                                       487     
#define HWA_SCALE0_8_ROW60_LSB                                       480     
#define HWA_SCALE0_8_ROW59_SIZE                                      8        // 8-bit scale for C bank 0 row or column 59
#define HWA_SCALE0_8_ROW59_MSB                                       479     
#define HWA_SCALE0_8_ROW59_LSB                                       472     
#define HWA_SCALE0_8_ROW58_SIZE                                      8        // 8-bit scale for C bank 0 row or column 58
#define HWA_SCALE0_8_ROW58_MSB                                       471     
#define HWA_SCALE0_8_ROW58_LSB                                       464     
#define HWA_SCALE0_8_ROW57_SIZE                                      8        // 8-bit scale for C bank 0 row or column 57
#define HWA_SCALE0_8_ROW57_MSB                                       463     
#define HWA_SCALE0_8_ROW57_LSB                                       456     
#define HWA_SCALE0_8_ROW56_SIZE                                      8        // 8-bit scale for C bank 0 row or column 56
#define HWA_SCALE0_8_ROW56_MSB                                       455     
#define HWA_SCALE0_8_ROW56_LSB                                       448     
#define HWA_SCALE0_8_ROW55_SIZE                                      8        // 8-bit scale for C bank 0 row or column 55
#define HWA_SCALE0_8_ROW55_MSB                                       447     
#define HWA_SCALE0_8_ROW55_LSB                                       440     
#define HWA_SCALE0_8_ROW54_SIZE                                      8        // 8-bit scale for C bank 0 row or column 54
#define HWA_SCALE0_8_ROW54_MSB                                       439     
#define HWA_SCALE0_8_ROW54_LSB                                       432     
#define HWA_SCALE0_8_ROW53_SIZE                                      8        // 8-bit scale for C bank 0 row or column 53
#define HWA_SCALE0_8_ROW53_MSB                                       431     
#define HWA_SCALE0_8_ROW53_LSB                                       424     
#define HWA_SCALE0_8_ROW52_SIZE                                      8        // 8-bit scale for C bank 0 row or column 52
#define HWA_SCALE0_8_ROW52_MSB                                       423     
#define HWA_SCALE0_8_ROW52_LSB                                       416     
#define HWA_SCALE0_8_ROW51_SIZE                                      8        // 8-bit scale for C bank 0 row or column 51
#define HWA_SCALE0_8_ROW51_MSB                                       415     
#define HWA_SCALE0_8_ROW51_LSB                                       408     
#define HWA_SCALE0_8_ROW50_SIZE                                      8        // 8-bit scale for C bank 0 row or column 50
#define HWA_SCALE0_8_ROW50_MSB                                       407     
#define HWA_SCALE0_8_ROW50_LSB                                       400     
#define HWA_SCALE0_8_ROW49_SIZE                                      8        // 8-bit scale for C bank 0 row or column 49
#define HWA_SCALE0_8_ROW49_MSB                                       399     
#define HWA_SCALE0_8_ROW49_LSB                                       392     
#define HWA_SCALE0_8_ROW48_SIZE                                      8        // 8-bit scale for C bank 0 row or column 48
#define HWA_SCALE0_8_ROW48_MSB                                       391     
#define HWA_SCALE0_8_ROW48_LSB                                       384     
#define HWA_SCALE0_8_ROW47_SIZE                                      8        // 8-bit scale for C bank 0 row or column 47
#define HWA_SCALE0_8_ROW47_MSB                                       383     
#define HWA_SCALE0_8_ROW47_LSB                                       376     
#define HWA_SCALE0_8_ROW46_SIZE                                      8        // 8-bit scale for C bank 0 row or column 46
#define HWA_SCALE0_8_ROW46_MSB                                       375     
#define HWA_SCALE0_8_ROW46_LSB                                       368     
#define HWA_SCALE0_8_ROW45_SIZE                                      8        // 8-bit scale for C bank 0 row or column 45
#define HWA_SCALE0_8_ROW45_MSB                                       367     
#define HWA_SCALE0_8_ROW45_LSB                                       360     
#define HWA_SCALE0_8_ROW44_SIZE                                      8        // 8-bit scale for C bank 0 row or column 44
#define HWA_SCALE0_8_ROW44_MSB                                       359     
#define HWA_SCALE0_8_ROW44_LSB                                       352     
#define HWA_SCALE0_8_ROW43_SIZE                                      8        // 8-bit scale for C bank 0 row or column 43
#define HWA_SCALE0_8_ROW43_MSB                                       351     
#define HWA_SCALE0_8_ROW43_LSB                                       344     
#define HWA_SCALE0_8_ROW42_SIZE                                      8        // 8-bit scale for C bank 0 row or column 42
#define HWA_SCALE0_8_ROW42_MSB                                       343     
#define HWA_SCALE0_8_ROW42_LSB                                       336     
#define HWA_SCALE0_8_ROW41_SIZE                                      8        // 8-bit scale for C bank 0 row or column 41
#define HWA_SCALE0_8_ROW41_MSB                                       335     
#define HWA_SCALE0_8_ROW41_LSB                                       328     
#define HWA_SCALE0_8_ROW40_SIZE                                      8        // 8-bit scale for C bank 0 row or column 40
#define HWA_SCALE0_8_ROW40_MSB                                       327     
#define HWA_SCALE0_8_ROW40_LSB                                       320     
#define HWA_SCALE0_8_ROW39_SIZE                                      8        // 8-bit scale for C bank 0 row or column 39
#define HWA_SCALE0_8_ROW39_MSB                                       319     
#define HWA_SCALE0_8_ROW39_LSB                                       312     
#define HWA_SCALE0_8_ROW38_SIZE                                      8        // 8-bit scale for C bank 0 row or column 38
#define HWA_SCALE0_8_ROW38_MSB                                       311     
#define HWA_SCALE0_8_ROW38_LSB                                       304     
#define HWA_SCALE0_8_ROW37_SIZE                                      8        // 8-bit scale for C bank 0 row or column 37
#define HWA_SCALE0_8_ROW37_MSB                                       303     
#define HWA_SCALE0_8_ROW37_LSB                                       296     
#define HWA_SCALE0_8_ROW36_SIZE                                      8        // 8-bit scale for C bank 0 row or column 36
#define HWA_SCALE0_8_ROW36_MSB                                       295     
#define HWA_SCALE0_8_ROW36_LSB                                       288     
#define HWA_SCALE0_8_ROW35_SIZE                                      8        // 8-bit scale for C bank 0 row or column 35
#define HWA_SCALE0_8_ROW35_MSB                                       287     
#define HWA_SCALE0_8_ROW35_LSB                                       280     
#define HWA_SCALE0_8_ROW34_SIZE                                      8        // 8-bit scale for C bank 0 row or column 34
#define HWA_SCALE0_8_ROW34_MSB                                       279     
#define HWA_SCALE0_8_ROW34_LSB                                       272     
#define HWA_SCALE0_8_ROW33_SIZE                                      8        // 8-bit scale for C bank 0 row or column 33
#define HWA_SCALE0_8_ROW33_MSB                                       271     
#define HWA_SCALE0_8_ROW33_LSB                                       264     
#define HWA_SCALE0_8_ROW32_SIZE                                      8        // 8-bit scale for C bank 0 row or column 32
#define HWA_SCALE0_8_ROW32_MSB                                       263     
#define HWA_SCALE0_8_ROW32_LSB                                       256     
#define HWA_SCALE0_8_ROW31_SIZE                                      8        // 8-bit scale for C bank 0 row or column 31
#define HWA_SCALE0_8_ROW31_MSB                                       255     
#define HWA_SCALE0_8_ROW31_LSB                                       248     
#define HWA_SCALE0_8_ROW30_SIZE                                      8        // 8-bit scale for C bank 0 row or column 30
#define HWA_SCALE0_8_ROW30_MSB                                       247     
#define HWA_SCALE0_8_ROW30_LSB                                       240     
#define HWA_SCALE0_8_ROW29_SIZE                                      8        // 8-bit scale for C bank 0 row or column 29
#define HWA_SCALE0_8_ROW29_MSB                                       239     
#define HWA_SCALE0_8_ROW29_LSB                                       232     
#define HWA_SCALE0_8_ROW28_SIZE                                      8        // 8-bit scale for C bank 0 row or column 28
#define HWA_SCALE0_8_ROW28_MSB                                       231     
#define HWA_SCALE0_8_ROW28_LSB                                       224     
#define HWA_SCALE0_8_ROW27_SIZE                                      8        // 8-bit scale for C bank 0 row or column 27
#define HWA_SCALE0_8_ROW27_MSB                                       223     
#define HWA_SCALE0_8_ROW27_LSB                                       216     
#define HWA_SCALE0_8_ROW26_SIZE                                      8        // 8-bit scale for C bank 0 row or column 26
#define HWA_SCALE0_8_ROW26_MSB                                       215     
#define HWA_SCALE0_8_ROW26_LSB                                       208     
#define HWA_SCALE0_8_ROW25_SIZE                                      8        // 8-bit scale for C bank 0 row or column 25
#define HWA_SCALE0_8_ROW25_MSB                                       207     
#define HWA_SCALE0_8_ROW25_LSB                                       200     
#define HWA_SCALE0_8_ROW24_SIZE                                      8        // 8-bit scale for C bank 0 row or column 24
#define HWA_SCALE0_8_ROW24_MSB                                       199     
#define HWA_SCALE0_8_ROW24_LSB                                       192     
#define HWA_SCALE0_8_ROW23_SIZE                                      8        // 8-bit scale for C bank 0 row or column 23
#define HWA_SCALE0_8_ROW23_MSB                                       191     
#define HWA_SCALE0_8_ROW23_LSB                                       184     
#define HWA_SCALE0_8_ROW22_SIZE                                      8        // 8-bit scale for C bank 0 row or column 22
#define HWA_SCALE0_8_ROW22_MSB                                       183     
#define HWA_SCALE0_8_ROW22_LSB                                       176     
#define HWA_SCALE0_8_ROW21_SIZE                                      8        // 8-bit scale for C bank 0 row or column 21
#define HWA_SCALE0_8_ROW21_MSB                                       175     
#define HWA_SCALE0_8_ROW21_LSB                                       168     
#define HWA_SCALE0_8_ROW20_SIZE                                      8        // 8-bit scale for C bank 0 row or column 20
#define HWA_SCALE0_8_ROW20_MSB                                       167     
#define HWA_SCALE0_8_ROW20_LSB                                       160     
#define HWA_SCALE0_8_ROW19_SIZE                                      8        // 8-bit scale for C bank 0 row or column 19
#define HWA_SCALE0_8_ROW19_MSB                                       159     
#define HWA_SCALE0_8_ROW19_LSB                                       152     
#define HWA_SCALE0_8_ROW18_SIZE                                      8        // 8-bit scale for C bank 0 row or column 18
#define HWA_SCALE0_8_ROW18_MSB                                       151     
#define HWA_SCALE0_8_ROW18_LSB                                       144     
#define HWA_SCALE0_8_ROW17_SIZE                                      8        // 8-bit scale for C bank 0 row or column 17
#define HWA_SCALE0_8_ROW17_MSB                                       143     
#define HWA_SCALE0_8_ROW17_LSB                                       136     
#define HWA_SCALE0_8_ROW16_SIZE                                      8        // 8-bit scale for C bank 0 row or column 16
#define HWA_SCALE0_8_ROW16_MSB                                       135     
#define HWA_SCALE0_8_ROW16_LSB                                       128     
#define HWA_SCALE0_8_ROW15_SIZE                                      8        // 8-bit scale for C bank 0 row or column 15
#define HWA_SCALE0_8_ROW15_MSB                                       127     
#define HWA_SCALE0_8_ROW15_LSB                                       120     
#define HWA_SCALE0_8_ROW14_SIZE                                      8        // 8-bit scale for C bank 0 row or column 14
#define HWA_SCALE0_8_ROW14_MSB                                       119     
#define HWA_SCALE0_8_ROW14_LSB                                       112     
#define HWA_SCALE0_8_ROW13_SIZE                                      8        // 8-bit scale for C bank 0 row or column 13
#define HWA_SCALE0_8_ROW13_MSB                                       111     
#define HWA_SCALE0_8_ROW13_LSB                                       104     
#define HWA_SCALE0_8_ROW12_SIZE                                      8        // 8-bit scale for C bank 0 row or column 12
#define HWA_SCALE0_8_ROW12_MSB                                       103     
#define HWA_SCALE0_8_ROW12_LSB                                       96      
#define HWA_SCALE0_8_ROW11_SIZE                                      8        // 8-bit scale for C bank 0 row or column 11
#define HWA_SCALE0_8_ROW11_MSB                                       95      
#define HWA_SCALE0_8_ROW11_LSB                                       88      
#define HWA_SCALE0_8_ROW10_SIZE                                      8        // 8-bit scale for C bank 0 row or column 10
#define HWA_SCALE0_8_ROW10_MSB                                       87      
#define HWA_SCALE0_8_ROW10_LSB                                       80      
#define HWA_SCALE0_8_ROW9_SIZE                                       8        // 8-bit scale for C bank 0 row or column 9
#define HWA_SCALE0_8_ROW9_MSB                                        79      
#define HWA_SCALE0_8_ROW9_LSB                                        72      
#define HWA_SCALE0_8_ROW8_SIZE                                       8        // 8-bit scale for C bank 0 row or column 8
#define HWA_SCALE0_8_ROW8_MSB                                        71      
#define HWA_SCALE0_8_ROW8_LSB                                        64      
#define HWA_SCALE0_8_ROW7_SIZE                                       8        // 8-bit scale for C bank 0 row or column 7
#define HWA_SCALE0_8_ROW7_MSB                                        63      
#define HWA_SCALE0_8_ROW7_LSB                                        56      
#define HWA_SCALE0_8_ROW6_SIZE                                       8        // 8-bit scale for C bank 0 row or column 6
#define HWA_SCALE0_8_ROW6_MSB                                        55      
#define HWA_SCALE0_8_ROW6_LSB                                        48      
#define HWA_SCALE0_8_ROW5_SIZE                                       8        // 8-bit scale for C bank 0 row or column 5
#define HWA_SCALE0_8_ROW5_MSB                                        47      
#define HWA_SCALE0_8_ROW5_LSB                                        40      
#define HWA_SCALE0_8_ROW4_SIZE                                       8        // 8-bit scale for C bank 0 row or column 4
#define HWA_SCALE0_8_ROW4_MSB                                        39      
#define HWA_SCALE0_8_ROW4_LSB                                        32      
#define HWA_SCALE0_8_ROW3_SIZE                                       8        // 8-bit scale for C bank 0 row or column 3
#define HWA_SCALE0_8_ROW3_MSB                                        31      
#define HWA_SCALE0_8_ROW3_LSB                                        24      
#define HWA_SCALE0_8_ROW2_SIZE                                       8        // 8-bit scale for C bank 0 row or column 2
#define HWA_SCALE0_8_ROW2_MSB                                        23      
#define HWA_SCALE0_8_ROW2_LSB                                        16      
#define HWA_SCALE0_8_ROW1_SIZE                                       8        // 8-bit scale for C bank 0 row or column 1
#define HWA_SCALE0_8_ROW1_MSB                                        15      
#define HWA_SCALE0_8_ROW1_LSB                                        8       
#define HWA_SCALE0_8_ROW0_SIZE                                       8        // 8-bit scale for C bank 0 row or column 0
#define HWA_SCALE0_8_ROW0_MSB                                        7       
#define HWA_SCALE0_8_ROW0_LSB                                        0       
// Declarations for reg HWA_SCALE1_8
#define HWA_SCALE1_8_SIZE                                            512     
#define HWA_SCALE1_8_MSB                                             511     
#define HWA_SCALE1_8_LSB                                             0       
#define HWA_SCALE1_8_ROW63_SIZE                                      8        // 8-bit scale for C bank 1 row or column 63
#define HWA_SCALE1_8_ROW63_MSB                                       511     
#define HWA_SCALE1_8_ROW63_LSB                                       504     
#define HWA_SCALE1_8_ROW62_SIZE                                      8        // 8-bit scale for C bank 1 row or column 62
#define HWA_SCALE1_8_ROW62_MSB                                       503     
#define HWA_SCALE1_8_ROW62_LSB                                       496     
#define HWA_SCALE1_8_ROW61_SIZE                                      8        // 8-bit scale for C bank 1 row or column 61
#define HWA_SCALE1_8_ROW61_MSB                                       495     
#define HWA_SCALE1_8_ROW61_LSB                                       488     
#define HWA_SCALE1_8_ROW60_SIZE                                      8        // 8-bit scale for C bank 1 row or column 60
#define HWA_SCALE1_8_ROW60_MSB                                       487     
#define HWA_SCALE1_8_ROW60_LSB                                       480     
#define HWA_SCALE1_8_ROW59_SIZE                                      8        // 8-bit scale for C bank 1 row or column 59
#define HWA_SCALE1_8_ROW59_MSB                                       479     
#define HWA_SCALE1_8_ROW59_LSB                                       472     
#define HWA_SCALE1_8_ROW58_SIZE                                      8        // 8-bit scale for C bank 1 row or column 58
#define HWA_SCALE1_8_ROW58_MSB                                       471     
#define HWA_SCALE1_8_ROW58_LSB                                       464     
#define HWA_SCALE1_8_ROW57_SIZE                                      8        // 8-bit scale for C bank 1 row or column 57
#define HWA_SCALE1_8_ROW57_MSB                                       463     
#define HWA_SCALE1_8_ROW57_LSB                                       456     
#define HWA_SCALE1_8_ROW56_SIZE                                      8        // 8-bit scale for C bank 1 row or column 56
#define HWA_SCALE1_8_ROW56_MSB                                       455     
#define HWA_SCALE1_8_ROW56_LSB                                       448     
#define HWA_SCALE1_8_ROW55_SIZE                                      8        // 8-bit scale for C bank 1 row or column 55
#define HWA_SCALE1_8_ROW55_MSB                                       447     
#define HWA_SCALE1_8_ROW55_LSB                                       440     
#define HWA_SCALE1_8_ROW54_SIZE                                      8        // 8-bit scale for C bank 1 row or column 54
#define HWA_SCALE1_8_ROW54_MSB                                       439     
#define HWA_SCALE1_8_ROW54_LSB                                       432     
#define HWA_SCALE1_8_ROW53_SIZE                                      8        // 8-bit scale for C bank 1 row or column 53
#define HWA_SCALE1_8_ROW53_MSB                                       431     
#define HWA_SCALE1_8_ROW53_LSB                                       424     
#define HWA_SCALE1_8_ROW52_SIZE                                      8        // 8-bit scale for C bank 1 row or column 52
#define HWA_SCALE1_8_ROW52_MSB                                       423     
#define HWA_SCALE1_8_ROW52_LSB                                       416     
#define HWA_SCALE1_8_ROW51_SIZE                                      8        // 8-bit scale for C bank 1 row or column 51
#define HWA_SCALE1_8_ROW51_MSB                                       415     
#define HWA_SCALE1_8_ROW51_LSB                                       408     
#define HWA_SCALE1_8_ROW50_SIZE                                      8        // 8-bit scale for C bank 1 row or column 50
#define HWA_SCALE1_8_ROW50_MSB                                       407     
#define HWA_SCALE1_8_ROW50_LSB                                       400     
#define HWA_SCALE1_8_ROW49_SIZE                                      8        // 8-bit scale for C bank 1 row or column 49
#define HWA_SCALE1_8_ROW49_MSB                                       399     
#define HWA_SCALE1_8_ROW49_LSB                                       392     
#define HWA_SCALE1_8_ROW48_SIZE                                      8        // 8-bit scale for C bank 1 row or column 48
#define HWA_SCALE1_8_ROW48_MSB                                       391     
#define HWA_SCALE1_8_ROW48_LSB                                       384     
#define HWA_SCALE1_8_ROW47_SIZE                                      8        // 8-bit scale for C bank 1 row or column 47
#define HWA_SCALE1_8_ROW47_MSB                                       383     
#define HWA_SCALE1_8_ROW47_LSB                                       376     
#define HWA_SCALE1_8_ROW46_SIZE                                      8        // 8-bit scale for C bank 1 row or column 46
#define HWA_SCALE1_8_ROW46_MSB                                       375     
#define HWA_SCALE1_8_ROW46_LSB                                       368     
#define HWA_SCALE1_8_ROW45_SIZE                                      8        // 8-bit scale for C bank 1 row or column 45
#define HWA_SCALE1_8_ROW45_MSB                                       367     
#define HWA_SCALE1_8_ROW45_LSB                                       360     
#define HWA_SCALE1_8_ROW44_SIZE                                      8        // 8-bit scale for C bank 1 row or column 44
#define HWA_SCALE1_8_ROW44_MSB                                       359     
#define HWA_SCALE1_8_ROW44_LSB                                       352     
#define HWA_SCALE1_8_ROW43_SIZE                                      8        // 8-bit scale for C bank 1 row or column 43
#define HWA_SCALE1_8_ROW43_MSB                                       351     
#define HWA_SCALE1_8_ROW43_LSB                                       344     
#define HWA_SCALE1_8_ROW42_SIZE                                      8        // 8-bit scale for C bank 1 row or column 42
#define HWA_SCALE1_8_ROW42_MSB                                       343     
#define HWA_SCALE1_8_ROW42_LSB                                       336     
#define HWA_SCALE1_8_ROW41_SIZE                                      8        // 8-bit scale for C bank 1 row or column 41
#define HWA_SCALE1_8_ROW41_MSB                                       335     
#define HWA_SCALE1_8_ROW41_LSB                                       328     
#define HWA_SCALE1_8_ROW40_SIZE                                      8        // 8-bit scale for C bank 1 row or column 40
#define HWA_SCALE1_8_ROW40_MSB                                       327     
#define HWA_SCALE1_8_ROW40_LSB                                       320     
#define HWA_SCALE1_8_ROW39_SIZE                                      8        // 8-bit scale for C bank 1 row or column 39
#define HWA_SCALE1_8_ROW39_MSB                                       319     
#define HWA_SCALE1_8_ROW39_LSB                                       312     
#define HWA_SCALE1_8_ROW38_SIZE                                      8        // 8-bit scale for C bank 1 row or column 38
#define HWA_SCALE1_8_ROW38_MSB                                       311     
#define HWA_SCALE1_8_ROW38_LSB                                       304     
#define HWA_SCALE1_8_ROW37_SIZE                                      8        // 8-bit scale for C bank 1 row or column 37
#define HWA_SCALE1_8_ROW37_MSB                                       303     
#define HWA_SCALE1_8_ROW37_LSB                                       296     
#define HWA_SCALE1_8_ROW36_SIZE                                      8        // 8-bit scale for C bank 1 row or column 36
#define HWA_SCALE1_8_ROW36_MSB                                       295     
#define HWA_SCALE1_8_ROW36_LSB                                       288     
#define HWA_SCALE1_8_ROW35_SIZE                                      8        // 8-bit scale for C bank 1 row or column 35
#define HWA_SCALE1_8_ROW35_MSB                                       287     
#define HWA_SCALE1_8_ROW35_LSB                                       280     
#define HWA_SCALE1_8_ROW34_SIZE                                      8        // 8-bit scale for C bank 1 row or column 34
#define HWA_SCALE1_8_ROW34_MSB                                       279     
#define HWA_SCALE1_8_ROW34_LSB                                       272     
#define HWA_SCALE1_8_ROW33_SIZE                                      8        // 8-bit scale for C bank 1 row or column 33
#define HWA_SCALE1_8_ROW33_MSB                                       271     
#define HWA_SCALE1_8_ROW33_LSB                                       264     
#define HWA_SCALE1_8_ROW32_SIZE                                      8        // 8-bit scale for C bank 1 row or column 32
#define HWA_SCALE1_8_ROW32_MSB                                       263     
#define HWA_SCALE1_8_ROW32_LSB                                       256     
#define HWA_SCALE1_8_ROW31_SIZE                                      8        // 8-bit scale for C bank 1 row or column 31
#define HWA_SCALE1_8_ROW31_MSB                                       255     
#define HWA_SCALE1_8_ROW31_LSB                                       248     
#define HWA_SCALE1_8_ROW30_SIZE                                      8        // 8-bit scale for C bank 1 row or column 30
#define HWA_SCALE1_8_ROW30_MSB                                       247     
#define HWA_SCALE1_8_ROW30_LSB                                       240     
#define HWA_SCALE1_8_ROW29_SIZE                                      8        // 8-bit scale for C bank 1 row or column 29
#define HWA_SCALE1_8_ROW29_MSB                                       239     
#define HWA_SCALE1_8_ROW29_LSB                                       232     
#define HWA_SCALE1_8_ROW28_SIZE                                      8        // 8-bit scale for C bank 1 row or column 28
#define HWA_SCALE1_8_ROW28_MSB                                       231     
#define HWA_SCALE1_8_ROW28_LSB                                       224     
#define HWA_SCALE1_8_ROW27_SIZE                                      8        // 8-bit scale for C bank 1 row or column 27
#define HWA_SCALE1_8_ROW27_MSB                                       223     
#define HWA_SCALE1_8_ROW27_LSB                                       216     
#define HWA_SCALE1_8_ROW26_SIZE                                      8        // 8-bit scale for C bank 1 row or column 26
#define HWA_SCALE1_8_ROW26_MSB                                       215     
#define HWA_SCALE1_8_ROW26_LSB                                       208     
#define HWA_SCALE1_8_ROW25_SIZE                                      8        // 8-bit scale for C bank 1 row or column 25
#define HWA_SCALE1_8_ROW25_MSB                                       207     
#define HWA_SCALE1_8_ROW25_LSB                                       200     
#define HWA_SCALE1_8_ROW24_SIZE                                      8        // 8-bit scale for C bank 1 row or column 24
#define HWA_SCALE1_8_ROW24_MSB                                       199     
#define HWA_SCALE1_8_ROW24_LSB                                       192     
#define HWA_SCALE1_8_ROW23_SIZE                                      8        // 8-bit scale for C bank 1 row or column 23
#define HWA_SCALE1_8_ROW23_MSB                                       191     
#define HWA_SCALE1_8_ROW23_LSB                                       184     
#define HWA_SCALE1_8_ROW22_SIZE                                      8        // 8-bit scale for C bank 1 row or column 22
#define HWA_SCALE1_8_ROW22_MSB                                       183     
#define HWA_SCALE1_8_ROW22_LSB                                       176     
#define HWA_SCALE1_8_ROW21_SIZE                                      8        // 8-bit scale for C bank 1 row or column 21
#define HWA_SCALE1_8_ROW21_MSB                                       175     
#define HWA_SCALE1_8_ROW21_LSB                                       168     
#define HWA_SCALE1_8_ROW20_SIZE                                      8        // 8-bit scale for C bank 1 row or column 20
#define HWA_SCALE1_8_ROW20_MSB                                       167     
#define HWA_SCALE1_8_ROW20_LSB                                       160     
#define HWA_SCALE1_8_ROW19_SIZE                                      8        // 8-bit scale for C bank 1 row or column 19
#define HWA_SCALE1_8_ROW19_MSB                                       159     
#define HWA_SCALE1_8_ROW19_LSB                                       152     
#define HWA_SCALE1_8_ROW18_SIZE                                      8        // 8-bit scale for C bank 1 row or column 18
#define HWA_SCALE1_8_ROW18_MSB                                       151     
#define HWA_SCALE1_8_ROW18_LSB                                       144     
#define HWA_SCALE1_8_ROW17_SIZE                                      8        // 8-bit scale for C bank 1 row or column 17
#define HWA_SCALE1_8_ROW17_MSB                                       143     
#define HWA_SCALE1_8_ROW17_LSB                                       136     
#define HWA_SCALE1_8_ROW16_SIZE                                      8        // 8-bit scale for C bank 1 row or column 16
#define HWA_SCALE1_8_ROW16_MSB                                       135     
#define HWA_SCALE1_8_ROW16_LSB                                       128     
#define HWA_SCALE1_8_ROW15_SIZE                                      8        // 8-bit scale for C bank 1 row or column 15
#define HWA_SCALE1_8_ROW15_MSB                                       127     
#define HWA_SCALE1_8_ROW15_LSB                                       120     
#define HWA_SCALE1_8_ROW14_SIZE                                      8        // 8-bit scale for C bank 1 row or column 14
#define HWA_SCALE1_8_ROW14_MSB                                       119     
#define HWA_SCALE1_8_ROW14_LSB                                       112     
#define HWA_SCALE1_8_ROW13_SIZE                                      8        // 8-bit scale for C bank 1 row or column 13
#define HWA_SCALE1_8_ROW13_MSB                                       111     
#define HWA_SCALE1_8_ROW13_LSB                                       104     
#define HWA_SCALE1_8_ROW12_SIZE                                      8        // 8-bit scale for C bank 1 row or column 12
#define HWA_SCALE1_8_ROW12_MSB                                       103     
#define HWA_SCALE1_8_ROW12_LSB                                       96      
#define HWA_SCALE1_8_ROW11_SIZE                                      8        // 8-bit scale for C bank 1 row or column 11
#define HWA_SCALE1_8_ROW11_MSB                                       95      
#define HWA_SCALE1_8_ROW11_LSB                                       88      
#define HWA_SCALE1_8_ROW10_SIZE                                      8        // 8-bit scale for C bank 1 row or column 10
#define HWA_SCALE1_8_ROW10_MSB                                       87      
#define HWA_SCALE1_8_ROW10_LSB                                       80      
#define HWA_SCALE1_8_ROW9_SIZE                                       8        // 8-bit scale for C bank 1 row or column 9
#define HWA_SCALE1_8_ROW9_MSB                                        79      
#define HWA_SCALE1_8_ROW9_LSB                                        72      
#define HWA_SCALE1_8_ROW8_SIZE                                       8        // 8-bit scale for C bank 1 row or column 8
#define HWA_SCALE1_8_ROW8_MSB                                        71      
#define HWA_SCALE1_8_ROW8_LSB                                        64      
#define HWA_SCALE1_8_ROW7_SIZE                                       8        // 8-bit scale for C bank 1 row or column 7
#define HWA_SCALE1_8_ROW7_MSB                                        63      
#define HWA_SCALE1_8_ROW7_LSB                                        56      
#define HWA_SCALE1_8_ROW6_SIZE                                       8        // 8-bit scale for C bank 1 row or column 6
#define HWA_SCALE1_8_ROW6_MSB                                        55      
#define HWA_SCALE1_8_ROW6_LSB                                        48      
#define HWA_SCALE1_8_ROW5_SIZE                                       8        // 8-bit scale for C bank 1 row or column 5
#define HWA_SCALE1_8_ROW5_MSB                                        47      
#define HWA_SCALE1_8_ROW5_LSB                                        40      
#define HWA_SCALE1_8_ROW4_SIZE                                       8        // 8-bit scale for C bank 1 row or column 4
#define HWA_SCALE1_8_ROW4_MSB                                        39      
#define HWA_SCALE1_8_ROW4_LSB                                        32      
#define HWA_SCALE1_8_ROW3_SIZE                                       8        // 8-bit scale for C bank 1 row or column 3
#define HWA_SCALE1_8_ROW3_MSB                                        31      
#define HWA_SCALE1_8_ROW3_LSB                                        24      
#define HWA_SCALE1_8_ROW2_SIZE                                       8        // 8-bit scale for C bank 1 row or column 2
#define HWA_SCALE1_8_ROW2_MSB                                        23      
#define HWA_SCALE1_8_ROW2_LSB                                        16      
#define HWA_SCALE1_8_ROW1_SIZE                                       8        // 8-bit scale for C bank 1 row or column 1
#define HWA_SCALE1_8_ROW1_MSB                                        15      
#define HWA_SCALE1_8_ROW1_LSB                                        8       
#define HWA_SCALE1_8_ROW0_SIZE                                       8        // 8-bit scale for C bank 1 row or column 0
#define HWA_SCALE1_8_ROW0_MSB                                        7       
#define HWA_SCALE1_8_ROW0_LSB                                        0       
// Declarations for reg HWA_SCALE0_16
#define HWA_SCALE0_16_SIZE                                           512     
#define HWA_SCALE0_16_MSB                                            511     
#define HWA_SCALE0_16_LSB                                            0       
#define HWA_SCALE0_16_RSVD_SIZE                                      256      // Software should write zero to this field
#define HWA_SCALE0_16_RSVD_MSB                                       511     
#define HWA_SCALE0_16_RSVD_LSB                                       256     
#define HWA_SCALE0_16_ROW31_SIZE                                     8        // 8-bit scale for C bank 0 row or column 31
#define HWA_SCALE0_16_ROW31_MSB                                      255     
#define HWA_SCALE0_16_ROW31_LSB                                      248     
#define HWA_SCALE0_16_ROW30_SIZE                                     8        // 8-bit scale for C bank 0 row or column 30
#define HWA_SCALE0_16_ROW30_MSB                                      247     
#define HWA_SCALE0_16_ROW30_LSB                                      240     
#define HWA_SCALE0_16_ROW29_SIZE                                     8        // 8-bit scale for C bank 0 row or column 29
#define HWA_SCALE0_16_ROW29_MSB                                      239     
#define HWA_SCALE0_16_ROW29_LSB                                      232     
#define HWA_SCALE0_16_ROW28_SIZE                                     8        // 8-bit scale for C bank 0 row or column 28
#define HWA_SCALE0_16_ROW28_MSB                                      231     
#define HWA_SCALE0_16_ROW28_LSB                                      224     
#define HWA_SCALE0_16_ROW27_SIZE                                     8        // 8-bit scale for C bank 0 row or column 27
#define HWA_SCALE0_16_ROW27_MSB                                      223     
#define HWA_SCALE0_16_ROW27_LSB                                      216     
#define HWA_SCALE0_16_ROW26_SIZE                                     8        // 8-bit scale for C bank 0 row or column 26
#define HWA_SCALE0_16_ROW26_MSB                                      215     
#define HWA_SCALE0_16_ROW26_LSB                                      208     
#define HWA_SCALE0_16_ROW25_SIZE                                     8        // 8-bit scale for C bank 0 row or column 25
#define HWA_SCALE0_16_ROW25_MSB                                      207     
#define HWA_SCALE0_16_ROW25_LSB                                      200     
#define HWA_SCALE0_16_ROW24_SIZE                                     8        // 8-bit scale for C bank 0 row or column 24
#define HWA_SCALE0_16_ROW24_MSB                                      199     
#define HWA_SCALE0_16_ROW24_LSB                                      192     
#define HWA_SCALE0_16_ROW23_SIZE                                     8        // 8-bit scale for C bank 0 row or column 23
#define HWA_SCALE0_16_ROW23_MSB                                      191     
#define HWA_SCALE0_16_ROW23_LSB                                      184     
#define HWA_SCALE0_16_ROW22_SIZE                                     8        // 8-bit scale for C bank 0 row or column 22
#define HWA_SCALE0_16_ROW22_MSB                                      183     
#define HWA_SCALE0_16_ROW22_LSB                                      176     
#define HWA_SCALE0_16_ROW21_SIZE                                     8        // 8-bit scale for C bank 0 row or column 21
#define HWA_SCALE0_16_ROW21_MSB                                      175     
#define HWA_SCALE0_16_ROW21_LSB                                      168     
#define HWA_SCALE0_16_ROW20_SIZE                                     8        // 8-bit scale for C bank 0 row or column 20
#define HWA_SCALE0_16_ROW20_MSB                                      167     
#define HWA_SCALE0_16_ROW20_LSB                                      160     
#define HWA_SCALE0_16_ROW19_SIZE                                     8        // 8-bit scale for C bank 0 row or column 19
#define HWA_SCALE0_16_ROW19_MSB                                      159     
#define HWA_SCALE0_16_ROW19_LSB                                      152     
#define HWA_SCALE0_16_ROW18_SIZE                                     8        // 8-bit scale for C bank 0 row or column 18
#define HWA_SCALE0_16_ROW18_MSB                                      151     
#define HWA_SCALE0_16_ROW18_LSB                                      144     
#define HWA_SCALE0_16_ROW17_SIZE                                     8        // 8-bit scale for C bank 0 row or column 17
#define HWA_SCALE0_16_ROW17_MSB                                      143     
#define HWA_SCALE0_16_ROW17_LSB                                      136     
#define HWA_SCALE0_16_ROW16_SIZE                                     8        // 8-bit scale for C bank 0 row or column 16
#define HWA_SCALE0_16_ROW16_MSB                                      135     
#define HWA_SCALE0_16_ROW16_LSB                                      128     
#define HWA_SCALE0_16_ROW15_SIZE                                     8        // 8-bit scale for C bank 0 row or column 15
#define HWA_SCALE0_16_ROW15_MSB                                      127     
#define HWA_SCALE0_16_ROW15_LSB                                      120     
#define HWA_SCALE0_16_ROW14_SIZE                                     8        // 8-bit scale for C bank 0 row or column 14
#define HWA_SCALE0_16_ROW14_MSB                                      119     
#define HWA_SCALE0_16_ROW14_LSB                                      112     
#define HWA_SCALE0_16_ROW13_SIZE                                     8        // 8-bit scale for C bank 0 row or column 13
#define HWA_SCALE0_16_ROW13_MSB                                      111     
#define HWA_SCALE0_16_ROW13_LSB                                      104     
#define HWA_SCALE0_16_ROW12_SIZE                                     8        // 8-bit scale for C bank 0 row or column 12
#define HWA_SCALE0_16_ROW12_MSB                                      103     
#define HWA_SCALE0_16_ROW12_LSB                                      96      
#define HWA_SCALE0_16_ROW11_SIZE                                     8        // 8-bit scale for C bank 0 row or column 11
#define HWA_SCALE0_16_ROW11_MSB                                      95      
#define HWA_SCALE0_16_ROW11_LSB                                      88      
#define HWA_SCALE0_16_ROW10_SIZE                                     8        // 8-bit scale for C bank 0 row or column 10
#define HWA_SCALE0_16_ROW10_MSB                                      87      
#define HWA_SCALE0_16_ROW10_LSB                                      80      
#define HWA_SCALE0_16_ROW9_SIZE                                      8        // 8-bit scale for C bank 0 row or column 9
#define HWA_SCALE0_16_ROW9_MSB                                       79      
#define HWA_SCALE0_16_ROW9_LSB                                       72      
#define HWA_SCALE0_16_ROW8_SIZE                                      8        // 8-bit scale for C bank 0 row or column 8
#define HWA_SCALE0_16_ROW8_MSB                                       71      
#define HWA_SCALE0_16_ROW8_LSB                                       64      
#define HWA_SCALE0_16_ROW7_SIZE                                      8        // 8-bit scale for C bank 0 row or column 7
#define HWA_SCALE0_16_ROW7_MSB                                       63      
#define HWA_SCALE0_16_ROW7_LSB                                       56      
#define HWA_SCALE0_16_ROW6_SIZE                                      8        // 8-bit scale for C bank 0 row or column 6
#define HWA_SCALE0_16_ROW6_MSB                                       55      
#define HWA_SCALE0_16_ROW6_LSB                                       48      
#define HWA_SCALE0_16_ROW5_SIZE                                      8        // 8-bit scale for C bank 0 row or column 5
#define HWA_SCALE0_16_ROW5_MSB                                       47      
#define HWA_SCALE0_16_ROW5_LSB                                       40      
#define HWA_SCALE0_16_ROW4_SIZE                                      8        // 8-bit scale for C bank 0 row or column 4
#define HWA_SCALE0_16_ROW4_MSB                                       39      
#define HWA_SCALE0_16_ROW4_LSB                                       32      
#define HWA_SCALE0_16_ROW3_SIZE                                      8        // 8-bit scale for C bank 0 row or column 3
#define HWA_SCALE0_16_ROW3_MSB                                       31      
#define HWA_SCALE0_16_ROW3_LSB                                       24      
#define HWA_SCALE0_16_ROW2_SIZE                                      8        // 8-bit scale for C bank 0 row or column 2
#define HWA_SCALE0_16_ROW2_MSB                                       23      
#define HWA_SCALE0_16_ROW2_LSB                                       16      
#define HWA_SCALE0_16_ROW1_SIZE                                      8        // 8-bit scale for C bank 0 row or column 1
#define HWA_SCALE0_16_ROW1_MSB                                       15      
#define HWA_SCALE0_16_ROW1_LSB                                       8       
#define HWA_SCALE0_16_ROW0_SIZE                                      8        // 8-bit scale for C bank 0 row or column 0
#define HWA_SCALE0_16_ROW0_MSB                                       7       
#define HWA_SCALE0_16_ROW0_LSB                                       0       
// Declarations for reg HWA_SCALE1_16
#define HWA_SCALE1_16_SIZE                                           512     
#define HWA_SCALE1_16_MSB                                            511     
#define HWA_SCALE1_16_LSB                                            0       
#define HWA_SCALE1_16_RSVD_SIZE                                      256      // Software should write zero to this field
#define HWA_SCALE1_16_RSVD_MSB                                       511     
#define HWA_SCALE1_16_RSVD_LSB                                       256     
#define HWA_SCALE1_16_ROW31_SIZE                                     8        // 8-bit scale for C bank 1 row or column 31
#define HWA_SCALE1_16_ROW31_MSB                                      255     
#define HWA_SCALE1_16_ROW31_LSB                                      248     
#define HWA_SCALE1_16_ROW30_SIZE                                     8        // 8-bit scale for C bank 1 row or column 30
#define HWA_SCALE1_16_ROW30_MSB                                      247     
#define HWA_SCALE1_16_ROW30_LSB                                      240     
#define HWA_SCALE1_16_ROW29_SIZE                                     8        // 8-bit scale for C bank 1 row or column 29
#define HWA_SCALE1_16_ROW29_MSB                                      239     
#define HWA_SCALE1_16_ROW29_LSB                                      232     
#define HWA_SCALE1_16_ROW28_SIZE                                     8        // 8-bit scale for C bank 1 row or column 28
#define HWA_SCALE1_16_ROW28_MSB                                      231     
#define HWA_SCALE1_16_ROW28_LSB                                      224     
#define HWA_SCALE1_16_ROW27_SIZE                                     8        // 8-bit scale for C bank 1 row or column 27
#define HWA_SCALE1_16_ROW27_MSB                                      223     
#define HWA_SCALE1_16_ROW27_LSB                                      216     
#define HWA_SCALE1_16_ROW26_SIZE                                     8        // 8-bit scale for C bank 1 row or column 26
#define HWA_SCALE1_16_ROW26_MSB                                      215     
#define HWA_SCALE1_16_ROW26_LSB                                      208     
#define HWA_SCALE1_16_ROW25_SIZE                                     8        // 8-bit scale for C bank 1 row or column 25
#define HWA_SCALE1_16_ROW25_MSB                                      207     
#define HWA_SCALE1_16_ROW25_LSB                                      200     
#define HWA_SCALE1_16_ROW24_SIZE                                     8        // 8-bit scale for C bank 1 row or column 24
#define HWA_SCALE1_16_ROW24_MSB                                      199     
#define HWA_SCALE1_16_ROW24_LSB                                      192     
#define HWA_SCALE1_16_ROW23_SIZE                                     8        // 8-bit scale for C bank 1 row or column 23
#define HWA_SCALE1_16_ROW23_MSB                                      191     
#define HWA_SCALE1_16_ROW23_LSB                                      184     
#define HWA_SCALE1_16_ROW22_SIZE                                     8        // 8-bit scale for C bank 1 row or column 22
#define HWA_SCALE1_16_ROW22_MSB                                      183     
#define HWA_SCALE1_16_ROW22_LSB                                      176     
#define HWA_SCALE1_16_ROW21_SIZE                                     8        // 8-bit scale for C bank 1 row or column 21
#define HWA_SCALE1_16_ROW21_MSB                                      175     
#define HWA_SCALE1_16_ROW21_LSB                                      168     
#define HWA_SCALE1_16_ROW20_SIZE                                     8        // 8-bit scale for C bank 1 row or column 20
#define HWA_SCALE1_16_ROW20_MSB                                      167     
#define HWA_SCALE1_16_ROW20_LSB                                      160     
#define HWA_SCALE1_16_ROW19_SIZE                                     8        // 8-bit scale for C bank 1 row or column 19
#define HWA_SCALE1_16_ROW19_MSB                                      159     
#define HWA_SCALE1_16_ROW19_LSB                                      152     
#define HWA_SCALE1_16_ROW18_SIZE                                     8        // 8-bit scale for C bank 1 row or column 18
#define HWA_SCALE1_16_ROW18_MSB                                      151     
#define HWA_SCALE1_16_ROW18_LSB                                      144     
#define HWA_SCALE1_16_ROW17_SIZE                                     8        // 8-bit scale for C bank 1 row or column 17
#define HWA_SCALE1_16_ROW17_MSB                                      143     
#define HWA_SCALE1_16_ROW17_LSB                                      136     
#define HWA_SCALE1_16_ROW16_SIZE                                     8        // 8-bit scale for C bank 1 row or column 16
#define HWA_SCALE1_16_ROW16_MSB                                      135     
#define HWA_SCALE1_16_ROW16_LSB                                      128     
#define HWA_SCALE1_16_ROW15_SIZE                                     8        // 8-bit scale for C bank 1 row or column 15
#define HWA_SCALE1_16_ROW15_MSB                                      127     
#define HWA_SCALE1_16_ROW15_LSB                                      120     
#define HWA_SCALE1_16_ROW14_SIZE                                     8        // 8-bit scale for C bank 1 row or column 14
#define HWA_SCALE1_16_ROW14_MSB                                      119     
#define HWA_SCALE1_16_ROW14_LSB                                      112     
#define HWA_SCALE1_16_ROW13_SIZE                                     8        // 8-bit scale for C bank 1 row or column 13
#define HWA_SCALE1_16_ROW13_MSB                                      111     
#define HWA_SCALE1_16_ROW13_LSB                                      104     
#define HWA_SCALE1_16_ROW12_SIZE                                     8        // 8-bit scale for C bank 1 row or column 12
#define HWA_SCALE1_16_ROW12_MSB                                      103     
#define HWA_SCALE1_16_ROW12_LSB                                      96      
#define HWA_SCALE1_16_ROW11_SIZE                                     8        // 8-bit scale for C bank 1 row or column 11
#define HWA_SCALE1_16_ROW11_MSB                                      95      
#define HWA_SCALE1_16_ROW11_LSB                                      88      
#define HWA_SCALE1_16_ROW10_SIZE                                     8        // 8-bit scale for C bank 1 row or column 10
#define HWA_SCALE1_16_ROW10_MSB                                      87      
#define HWA_SCALE1_16_ROW10_LSB                                      80      
#define HWA_SCALE1_16_ROW9_SIZE                                      8        // 8-bit scale for C bank 1 row or column 9
#define HWA_SCALE1_16_ROW9_MSB                                       79      
#define HWA_SCALE1_16_ROW9_LSB                                       72      
#define HWA_SCALE1_16_ROW8_SIZE                                      8        // 8-bit scale for C bank 1 row or column 8
#define HWA_SCALE1_16_ROW8_MSB                                       71      
#define HWA_SCALE1_16_ROW8_LSB                                       64      
#define HWA_SCALE1_16_ROW7_SIZE                                      8        // 8-bit scale for C bank 1 row or column 7
#define HWA_SCALE1_16_ROW7_MSB                                       63      
#define HWA_SCALE1_16_ROW7_LSB                                       56      
#define HWA_SCALE1_16_ROW6_SIZE                                      8        // 8-bit scale for C bank 1 row or column 6
#define HWA_SCALE1_16_ROW6_MSB                                       55      
#define HWA_SCALE1_16_ROW6_LSB                                       48      
#define HWA_SCALE1_16_ROW5_SIZE                                      8        // 8-bit scale for C bank 1 row or column 5
#define HWA_SCALE1_16_ROW5_MSB                                       47      
#define HWA_SCALE1_16_ROW5_LSB                                       40      
#define HWA_SCALE1_16_ROW4_SIZE                                      8        // 8-bit scale for C bank 1 row or column 4
#define HWA_SCALE1_16_ROW4_MSB                                       39      
#define HWA_SCALE1_16_ROW4_LSB                                       32      
#define HWA_SCALE1_16_ROW3_SIZE                                      8        // 8-bit scale for C bank 1 row or column 3
#define HWA_SCALE1_16_ROW3_MSB                                       31      
#define HWA_SCALE1_16_ROW3_LSB                                       24      
#define HWA_SCALE1_16_ROW2_SIZE                                      8        // 8-bit scale for C bank 1 row or column 2
#define HWA_SCALE1_16_ROW2_MSB                                       23      
#define HWA_SCALE1_16_ROW2_LSB                                       16      
#define HWA_SCALE1_16_ROW1_SIZE                                      8        // 8-bit scale for C bank 1 row or column 1
#define HWA_SCALE1_16_ROW1_MSB                                       15      
#define HWA_SCALE1_16_ROW1_LSB                                       8       
#define HWA_SCALE1_16_ROW0_SIZE                                      8        // 8-bit scale for C bank 1 row or column 0
#define HWA_SCALE1_16_ROW0_MSB                                       7       
#define HWA_SCALE1_16_ROW0_LSB                                       0       
// Declarations for reg HWA_SHIFT0_8
#define HWA_SHIFT0_8_SIZE                                            512     
#define HWA_SHIFT0_8_MSB                                             511     
#define HWA_SHIFT0_8_LSB                                             0       
#define HWA_SHIFT0_8_ROW63_SIZE                                      8        // 8-bit shift for C bank 0 row or column 63
#define HWA_SHIFT0_8_ROW63_MSB                                       511     
#define HWA_SHIFT0_8_ROW63_LSB                                       504     
#define HWA_SHIFT0_8_ROW62_SIZE                                      8        // 8-bit shift for C bank 0 row or column 62
#define HWA_SHIFT0_8_ROW62_MSB                                       503     
#define HWA_SHIFT0_8_ROW62_LSB                                       496     
#define HWA_SHIFT0_8_ROW61_SIZE                                      8        // 8-bit shift for C bank 0 row or column 61
#define HWA_SHIFT0_8_ROW61_MSB                                       495     
#define HWA_SHIFT0_8_ROW61_LSB                                       488     
#define HWA_SHIFT0_8_ROW60_SIZE                                      8        // 8-bit shift for C bank 0 row or column 60
#define HWA_SHIFT0_8_ROW60_MSB                                       487     
#define HWA_SHIFT0_8_ROW60_LSB                                       480     
#define HWA_SHIFT0_8_ROW59_SIZE                                      8        // 8-bit shift for C bank 0 row or column 59
#define HWA_SHIFT0_8_ROW59_MSB                                       479     
#define HWA_SHIFT0_8_ROW59_LSB                                       472     
#define HWA_SHIFT0_8_ROW58_SIZE                                      8        // 8-bit shift for C bank 0 row or column 58
#define HWA_SHIFT0_8_ROW58_MSB                                       471     
#define HWA_SHIFT0_8_ROW58_LSB                                       464     
#define HWA_SHIFT0_8_ROW57_SIZE                                      8        // 8-bit shift for C bank 0 row or column 57
#define HWA_SHIFT0_8_ROW57_MSB                                       463     
#define HWA_SHIFT0_8_ROW57_LSB                                       456     
#define HWA_SHIFT0_8_ROW56_SIZE                                      8        // 8-bit shift for C bank 0 row or column 56
#define HWA_SHIFT0_8_ROW56_MSB                                       455     
#define HWA_SHIFT0_8_ROW56_LSB                                       448     
#define HWA_SHIFT0_8_ROW55_SIZE                                      8        // 8-bit shift for C bank 0 row or column 55
#define HWA_SHIFT0_8_ROW55_MSB                                       447     
#define HWA_SHIFT0_8_ROW55_LSB                                       440     
#define HWA_SHIFT0_8_ROW54_SIZE                                      8        // 8-bit shift for C bank 0 row or column 54
#define HWA_SHIFT0_8_ROW54_MSB                                       439     
#define HWA_SHIFT0_8_ROW54_LSB                                       432     
#define HWA_SHIFT0_8_ROW53_SIZE                                      8        // 8-bit shift for C bank 0 row or column 53
#define HWA_SHIFT0_8_ROW53_MSB                                       431     
#define HWA_SHIFT0_8_ROW53_LSB                                       424     
#define HWA_SHIFT0_8_ROW52_SIZE                                      8        // 8-bit shift for C bank 0 row or column 52
#define HWA_SHIFT0_8_ROW52_MSB                                       423     
#define HWA_SHIFT0_8_ROW52_LSB                                       416     
#define HWA_SHIFT0_8_ROW51_SIZE                                      8        // 8-bit shift for C bank 0 row or column 51
#define HWA_SHIFT0_8_ROW51_MSB                                       415     
#define HWA_SHIFT0_8_ROW51_LSB                                       408     
#define HWA_SHIFT0_8_ROW50_SIZE                                      8        // 8-bit shift for C bank 0 row or column 50
#define HWA_SHIFT0_8_ROW50_MSB                                       407     
#define HWA_SHIFT0_8_ROW50_LSB                                       400     
#define HWA_SHIFT0_8_ROW49_SIZE                                      8        // 8-bit shift for C bank 0 row or column 49
#define HWA_SHIFT0_8_ROW49_MSB                                       399     
#define HWA_SHIFT0_8_ROW49_LSB                                       392     
#define HWA_SHIFT0_8_ROW48_SIZE                                      8        // 8-bit shift for C bank 0 row or column 48
#define HWA_SHIFT0_8_ROW48_MSB                                       391     
#define HWA_SHIFT0_8_ROW48_LSB                                       384     
#define HWA_SHIFT0_8_ROW47_SIZE                                      8        // 8-bit shift for C bank 0 row or column 47
#define HWA_SHIFT0_8_ROW47_MSB                                       383     
#define HWA_SHIFT0_8_ROW47_LSB                                       376     
#define HWA_SHIFT0_8_ROW46_SIZE                                      8        // 8-bit shift for C bank 0 row or column 46
#define HWA_SHIFT0_8_ROW46_MSB                                       375     
#define HWA_SHIFT0_8_ROW46_LSB                                       368     
#define HWA_SHIFT0_8_ROW45_SIZE                                      8        // 8-bit shift for C bank 0 row or column 45
#define HWA_SHIFT0_8_ROW45_MSB                                       367     
#define HWA_SHIFT0_8_ROW45_LSB                                       360     
#define HWA_SHIFT0_8_ROW44_SIZE                                      8        // 8-bit shift for C bank 0 row or column 44
#define HWA_SHIFT0_8_ROW44_MSB                                       359     
#define HWA_SHIFT0_8_ROW44_LSB                                       352     
#define HWA_SHIFT0_8_ROW43_SIZE                                      8        // 8-bit shift for C bank 0 row or column 43
#define HWA_SHIFT0_8_ROW43_MSB                                       351     
#define HWA_SHIFT0_8_ROW43_LSB                                       344     
#define HWA_SHIFT0_8_ROW42_SIZE                                      8        // 8-bit shift for C bank 0 row or column 42
#define HWA_SHIFT0_8_ROW42_MSB                                       343     
#define HWA_SHIFT0_8_ROW42_LSB                                       336     
#define HWA_SHIFT0_8_ROW41_SIZE                                      8        // 8-bit shift for C bank 0 row or column 41
#define HWA_SHIFT0_8_ROW41_MSB                                       335     
#define HWA_SHIFT0_8_ROW41_LSB                                       328     
#define HWA_SHIFT0_8_ROW40_SIZE                                      8        // 8-bit shift for C bank 0 row or column 40
#define HWA_SHIFT0_8_ROW40_MSB                                       327     
#define HWA_SHIFT0_8_ROW40_LSB                                       320     
#define HWA_SHIFT0_8_ROW39_SIZE                                      8        // 8-bit shift for C bank 0 row or column 39
#define HWA_SHIFT0_8_ROW39_MSB                                       319     
#define HWA_SHIFT0_8_ROW39_LSB                                       312     
#define HWA_SHIFT0_8_ROW38_SIZE                                      8        // 8-bit shift for C bank 0 row or column 38
#define HWA_SHIFT0_8_ROW38_MSB                                       311     
#define HWA_SHIFT0_8_ROW38_LSB                                       304     
#define HWA_SHIFT0_8_ROW37_SIZE                                      8        // 8-bit shift for C bank 0 row or column 37
#define HWA_SHIFT0_8_ROW37_MSB                                       303     
#define HWA_SHIFT0_8_ROW37_LSB                                       296     
#define HWA_SHIFT0_8_ROW36_SIZE                                      8        // 8-bit shift for C bank 0 row or column 36
#define HWA_SHIFT0_8_ROW36_MSB                                       295     
#define HWA_SHIFT0_8_ROW36_LSB                                       288     
#define HWA_SHIFT0_8_ROW35_SIZE                                      8        // 8-bit shift for C bank 0 row or column 35
#define HWA_SHIFT0_8_ROW35_MSB                                       287     
#define HWA_SHIFT0_8_ROW35_LSB                                       280     
#define HWA_SHIFT0_8_ROW34_SIZE                                      8        // 8-bit shift for C bank 0 row or column 34
#define HWA_SHIFT0_8_ROW34_MSB                                       279     
#define HWA_SHIFT0_8_ROW34_LSB                                       272     
#define HWA_SHIFT0_8_ROW33_SIZE                                      8        // 8-bit shift for C bank 0 row or column 33
#define HWA_SHIFT0_8_ROW33_MSB                                       271     
#define HWA_SHIFT0_8_ROW33_LSB                                       264     
#define HWA_SHIFT0_8_ROW32_SIZE                                      8        // 8-bit shift for C bank 0 row or column 32
#define HWA_SHIFT0_8_ROW32_MSB                                       263     
#define HWA_SHIFT0_8_ROW32_LSB                                       256     
#define HWA_SHIFT0_8_ROW31_SIZE                                      8        // 8-bit shift for C bank 0 row or column 31
#define HWA_SHIFT0_8_ROW31_MSB                                       255     
#define HWA_SHIFT0_8_ROW31_LSB                                       248     
#define HWA_SHIFT0_8_ROW30_SIZE                                      8        // 8-bit shift for C bank 0 row or column 30
#define HWA_SHIFT0_8_ROW30_MSB                                       247     
#define HWA_SHIFT0_8_ROW30_LSB                                       240     
#define HWA_SHIFT0_8_ROW29_SIZE                                      8        // 8-bit shift for C bank 0 row or column 29
#define HWA_SHIFT0_8_ROW29_MSB                                       239     
#define HWA_SHIFT0_8_ROW29_LSB                                       232     
#define HWA_SHIFT0_8_ROW28_SIZE                                      8        // 8-bit shift for C bank 0 row or column 28
#define HWA_SHIFT0_8_ROW28_MSB                                       231     
#define HWA_SHIFT0_8_ROW28_LSB                                       224     
#define HWA_SHIFT0_8_ROW27_SIZE                                      8        // 8-bit shift for C bank 0 row or column 27
#define HWA_SHIFT0_8_ROW27_MSB                                       223     
#define HWA_SHIFT0_8_ROW27_LSB                                       216     
#define HWA_SHIFT0_8_ROW26_SIZE                                      8        // 8-bit shift for C bank 0 row or column 26
#define HWA_SHIFT0_8_ROW26_MSB                                       215     
#define HWA_SHIFT0_8_ROW26_LSB                                       208     
#define HWA_SHIFT0_8_ROW25_SIZE                                      8        // 8-bit shift for C bank 0 row or column 25
#define HWA_SHIFT0_8_ROW25_MSB                                       207     
#define HWA_SHIFT0_8_ROW25_LSB                                       200     
#define HWA_SHIFT0_8_ROW24_SIZE                                      8        // 8-bit shift for C bank 0 row or column 24
#define HWA_SHIFT0_8_ROW24_MSB                                       199     
#define HWA_SHIFT0_8_ROW24_LSB                                       192     
#define HWA_SHIFT0_8_ROW23_SIZE                                      8        // 8-bit shift for C bank 0 row or column 23
#define HWA_SHIFT0_8_ROW23_MSB                                       191     
#define HWA_SHIFT0_8_ROW23_LSB                                       184     
#define HWA_SHIFT0_8_ROW22_SIZE                                      8        // 8-bit shift for C bank 0 row or column 22
#define HWA_SHIFT0_8_ROW22_MSB                                       183     
#define HWA_SHIFT0_8_ROW22_LSB                                       176     
#define HWA_SHIFT0_8_ROW21_SIZE                                      8        // 8-bit shift for C bank 0 row or column 21
#define HWA_SHIFT0_8_ROW21_MSB                                       175     
#define HWA_SHIFT0_8_ROW21_LSB                                       168     
#define HWA_SHIFT0_8_ROW20_SIZE                                      8        // 8-bit shift for C bank 0 row or column 20
#define HWA_SHIFT0_8_ROW20_MSB                                       167     
#define HWA_SHIFT0_8_ROW20_LSB                                       160     
#define HWA_SHIFT0_8_ROW19_SIZE                                      8        // 8-bit shift for C bank 0 row or column 19
#define HWA_SHIFT0_8_ROW19_MSB                                       159     
#define HWA_SHIFT0_8_ROW19_LSB                                       152     
#define HWA_SHIFT0_8_ROW18_SIZE                                      8        // 8-bit shift for C bank 0 row or column 18
#define HWA_SHIFT0_8_ROW18_MSB                                       151     
#define HWA_SHIFT0_8_ROW18_LSB                                       144     
#define HWA_SHIFT0_8_ROW17_SIZE                                      8        // 8-bit shift for C bank 0 row or column 17
#define HWA_SHIFT0_8_ROW17_MSB                                       143     
#define HWA_SHIFT0_8_ROW17_LSB                                       136     
#define HWA_SHIFT0_8_ROW16_SIZE                                      8        // 8-bit shift for C bank 0 row or column 16
#define HWA_SHIFT0_8_ROW16_MSB                                       135     
#define HWA_SHIFT0_8_ROW16_LSB                                       128     
#define HWA_SHIFT0_8_ROW15_SIZE                                      8        // 8-bit shift for C bank 0 row or column 15
#define HWA_SHIFT0_8_ROW15_MSB                                       127     
#define HWA_SHIFT0_8_ROW15_LSB                                       120     
#define HWA_SHIFT0_8_ROW14_SIZE                                      8        // 8-bit shift for C bank 0 row or column 14
#define HWA_SHIFT0_8_ROW14_MSB                                       119     
#define HWA_SHIFT0_8_ROW14_LSB                                       112     
#define HWA_SHIFT0_8_ROW13_SIZE                                      8        // 8-bit shift for C bank 0 row or column 13
#define HWA_SHIFT0_8_ROW13_MSB                                       111     
#define HWA_SHIFT0_8_ROW13_LSB                                       104     
#define HWA_SHIFT0_8_ROW12_SIZE                                      8        // 8-bit shift for C bank 0 row or column 12
#define HWA_SHIFT0_8_ROW12_MSB                                       103     
#define HWA_SHIFT0_8_ROW12_LSB                                       96      
#define HWA_SHIFT0_8_ROW11_SIZE                                      8        // 8-bit shift for C bank 0 row or column 11
#define HWA_SHIFT0_8_ROW11_MSB                                       95      
#define HWA_SHIFT0_8_ROW11_LSB                                       88      
#define HWA_SHIFT0_8_ROW10_SIZE                                      8        // 8-bit shift for C bank 0 row or column 10
#define HWA_SHIFT0_8_ROW10_MSB                                       87      
#define HWA_SHIFT0_8_ROW10_LSB                                       80      
#define HWA_SHIFT0_8_ROW9_SIZE                                       8        // 8-bit shift for C bank 0 row or column 9
#define HWA_SHIFT0_8_ROW9_MSB                                        79      
#define HWA_SHIFT0_8_ROW9_LSB                                        72      
#define HWA_SHIFT0_8_ROW8_SIZE                                       8        // 8-bit shift for C bank 0 row or column 8
#define HWA_SHIFT0_8_ROW8_MSB                                        71      
#define HWA_SHIFT0_8_ROW8_LSB                                        64      
#define HWA_SHIFT0_8_ROW7_SIZE                                       8        // 8-bit shift for C bank 0 row or column 7
#define HWA_SHIFT0_8_ROW7_MSB                                        63      
#define HWA_SHIFT0_8_ROW7_LSB                                        56      
#define HWA_SHIFT0_8_ROW6_SIZE                                       8        // 8-bit shift for C bank 0 row or column 6
#define HWA_SHIFT0_8_ROW6_MSB                                        55      
#define HWA_SHIFT0_8_ROW6_LSB                                        48      
#define HWA_SHIFT0_8_ROW5_SIZE                                       8        // 8-bit shift for C bank 0 row or column 5
#define HWA_SHIFT0_8_ROW5_MSB                                        47      
#define HWA_SHIFT0_8_ROW5_LSB                                        40      
#define HWA_SHIFT0_8_ROW4_SIZE                                       8        // 8-bit shift for C bank 0 row or column 4
#define HWA_SHIFT0_8_ROW4_MSB                                        39      
#define HWA_SHIFT0_8_ROW4_LSB                                        32      
#define HWA_SHIFT0_8_ROW3_SIZE                                       8        // 8-bit shift for C bank 0 row or column 3
#define HWA_SHIFT0_8_ROW3_MSB                                        31      
#define HWA_SHIFT0_8_ROW3_LSB                                        24      
#define HWA_SHIFT0_8_ROW2_SIZE                                       8        // 8-bit shift for C bank 0 row or column 2
#define HWA_SHIFT0_8_ROW2_MSB                                        23      
#define HWA_SHIFT0_8_ROW2_LSB                                        16      
#define HWA_SHIFT0_8_ROW1_SIZE                                       8        // 8-bit shift for C bank 0 row or column 1
#define HWA_SHIFT0_8_ROW1_MSB                                        15      
#define HWA_SHIFT0_8_ROW1_LSB                                        8       
#define HWA_SHIFT0_8_ROW0_SIZE                                       8        // 8-bit shift for C bank 0 row or column 0
#define HWA_SHIFT0_8_ROW0_MSB                                        7       
#define HWA_SHIFT0_8_ROW0_LSB                                        0       
// Declarations for reg HWA_SHIFT1_8
#define HWA_SHIFT1_8_SIZE                                            512     
#define HWA_SHIFT1_8_MSB                                             511     
#define HWA_SHIFT1_8_LSB                                             0       
#define HWA_SHIFT1_8_ROW63_SIZE                                      8        // 8-bit shift for C bank 1 row or column 63
#define HWA_SHIFT1_8_ROW63_MSB                                       511     
#define HWA_SHIFT1_8_ROW63_LSB                                       504     
#define HWA_SHIFT1_8_ROW62_SIZE                                      8        // 8-bit shift for C bank 1 row or column 62
#define HWA_SHIFT1_8_ROW62_MSB                                       503     
#define HWA_SHIFT1_8_ROW62_LSB                                       496     
#define HWA_SHIFT1_8_ROW61_SIZE                                      8        // 8-bit shift for C bank 1 row or column 61
#define HWA_SHIFT1_8_ROW61_MSB                                       495     
#define HWA_SHIFT1_8_ROW61_LSB                                       488     
#define HWA_SHIFT1_8_ROW60_SIZE                                      8        // 8-bit shift for C bank 1 row or column 60
#define HWA_SHIFT1_8_ROW60_MSB                                       487     
#define HWA_SHIFT1_8_ROW60_LSB                                       480     
#define HWA_SHIFT1_8_ROW59_SIZE                                      8        // 8-bit shift for C bank 1 row or column 59
#define HWA_SHIFT1_8_ROW59_MSB                                       479     
#define HWA_SHIFT1_8_ROW59_LSB                                       472     
#define HWA_SHIFT1_8_ROW58_SIZE                                      8        // 8-bit shift for C bank 1 row or column 58
#define HWA_SHIFT1_8_ROW58_MSB                                       471     
#define HWA_SHIFT1_8_ROW58_LSB                                       464     
#define HWA_SHIFT1_8_ROW57_SIZE                                      8        // 8-bit shift for C bank 1 row or column 57
#define HWA_SHIFT1_8_ROW57_MSB                                       463     
#define HWA_SHIFT1_8_ROW57_LSB                                       456     
#define HWA_SHIFT1_8_ROW56_SIZE                                      8        // 8-bit shift for C bank 1 row or column 56
#define HWA_SHIFT1_8_ROW56_MSB                                       455     
#define HWA_SHIFT1_8_ROW56_LSB                                       448     
#define HWA_SHIFT1_8_ROW55_SIZE                                      8        // 8-bit shift for C bank 1 row or column 55
#define HWA_SHIFT1_8_ROW55_MSB                                       447     
#define HWA_SHIFT1_8_ROW55_LSB                                       440     
#define HWA_SHIFT1_8_ROW54_SIZE                                      8        // 8-bit shift for C bank 1 row or column 54
#define HWA_SHIFT1_8_ROW54_MSB                                       439     
#define HWA_SHIFT1_8_ROW54_LSB                                       432     
#define HWA_SHIFT1_8_ROW53_SIZE                                      8        // 8-bit shift for C bank 1 row or column 53
#define HWA_SHIFT1_8_ROW53_MSB                                       431     
#define HWA_SHIFT1_8_ROW53_LSB                                       424     
#define HWA_SHIFT1_8_ROW52_SIZE                                      8        // 8-bit shift for C bank 1 row or column 52
#define HWA_SHIFT1_8_ROW52_MSB                                       423     
#define HWA_SHIFT1_8_ROW52_LSB                                       416     
#define HWA_SHIFT1_8_ROW51_SIZE                                      8        // 8-bit shift for C bank 1 row or column 51
#define HWA_SHIFT1_8_ROW51_MSB                                       415     
#define HWA_SHIFT1_8_ROW51_LSB                                       408     
#define HWA_SHIFT1_8_ROW50_SIZE                                      8        // 8-bit shift for C bank 1 row or column 50
#define HWA_SHIFT1_8_ROW50_MSB                                       407     
#define HWA_SHIFT1_8_ROW50_LSB                                       400     
#define HWA_SHIFT1_8_ROW49_SIZE                                      8        // 8-bit shift for C bank 1 row or column 49
#define HWA_SHIFT1_8_ROW49_MSB                                       399     
#define HWA_SHIFT1_8_ROW49_LSB                                       392     
#define HWA_SHIFT1_8_ROW48_SIZE                                      8        // 8-bit shift for C bank 1 row or column 48
#define HWA_SHIFT1_8_ROW48_MSB                                       391     
#define HWA_SHIFT1_8_ROW48_LSB                                       384     
#define HWA_SHIFT1_8_ROW47_SIZE                                      8        // 8-bit shift for C bank 1 row or column 47
#define HWA_SHIFT1_8_ROW47_MSB                                       383     
#define HWA_SHIFT1_8_ROW47_LSB                                       376     
#define HWA_SHIFT1_8_ROW46_SIZE                                      8        // 8-bit shift for C bank 1 row or column 46
#define HWA_SHIFT1_8_ROW46_MSB                                       375     
#define HWA_SHIFT1_8_ROW46_LSB                                       368     
#define HWA_SHIFT1_8_ROW45_SIZE                                      8        // 8-bit shift for C bank 1 row or column 45
#define HWA_SHIFT1_8_ROW45_MSB                                       367     
#define HWA_SHIFT1_8_ROW45_LSB                                       360     
#define HWA_SHIFT1_8_ROW44_SIZE                                      8        // 8-bit shift for C bank 1 row or column 44
#define HWA_SHIFT1_8_ROW44_MSB                                       359     
#define HWA_SHIFT1_8_ROW44_LSB                                       352     
#define HWA_SHIFT1_8_ROW43_SIZE                                      8        // 8-bit shift for C bank 1 row or column 43
#define HWA_SHIFT1_8_ROW43_MSB                                       351     
#define HWA_SHIFT1_8_ROW43_LSB                                       344     
#define HWA_SHIFT1_8_ROW42_SIZE                                      8        // 8-bit shift for C bank 1 row or column 42
#define HWA_SHIFT1_8_ROW42_MSB                                       343     
#define HWA_SHIFT1_8_ROW42_LSB                                       336     
#define HWA_SHIFT1_8_ROW41_SIZE                                      8        // 8-bit shift for C bank 1 row or column 41
#define HWA_SHIFT1_8_ROW41_MSB                                       335     
#define HWA_SHIFT1_8_ROW41_LSB                                       328     
#define HWA_SHIFT1_8_ROW40_SIZE                                      8        // 8-bit shift for C bank 1 row or column 40
#define HWA_SHIFT1_8_ROW40_MSB                                       327     
#define HWA_SHIFT1_8_ROW40_LSB                                       320     
#define HWA_SHIFT1_8_ROW39_SIZE                                      8        // 8-bit shift for C bank 1 row or column 39
#define HWA_SHIFT1_8_ROW39_MSB                                       319     
#define HWA_SHIFT1_8_ROW39_LSB                                       312     
#define HWA_SHIFT1_8_ROW38_SIZE                                      8        // 8-bit shift for C bank 1 row or column 38
#define HWA_SHIFT1_8_ROW38_MSB                                       311     
#define HWA_SHIFT1_8_ROW38_LSB                                       304     
#define HWA_SHIFT1_8_ROW37_SIZE                                      8        // 8-bit shift for C bank 1 row or column 37
#define HWA_SHIFT1_8_ROW37_MSB                                       303     
#define HWA_SHIFT1_8_ROW37_LSB                                       296     
#define HWA_SHIFT1_8_ROW36_SIZE                                      8        // 8-bit shift for C bank 1 row or column 36
#define HWA_SHIFT1_8_ROW36_MSB                                       295     
#define HWA_SHIFT1_8_ROW36_LSB                                       288     
#define HWA_SHIFT1_8_ROW35_SIZE                                      8        // 8-bit shift for C bank 1 row or column 35
#define HWA_SHIFT1_8_ROW35_MSB                                       287     
#define HWA_SHIFT1_8_ROW35_LSB                                       280     
#define HWA_SHIFT1_8_ROW34_SIZE                                      8        // 8-bit shift for C bank 1 row or column 34
#define HWA_SHIFT1_8_ROW34_MSB                                       279     
#define HWA_SHIFT1_8_ROW34_LSB                                       272     
#define HWA_SHIFT1_8_ROW33_SIZE                                      8        // 8-bit shift for C bank 1 row or column 33
#define HWA_SHIFT1_8_ROW33_MSB                                       271     
#define HWA_SHIFT1_8_ROW33_LSB                                       264     
#define HWA_SHIFT1_8_ROW32_SIZE                                      8        // 8-bit shift for C bank 1 row or column 32
#define HWA_SHIFT1_8_ROW32_MSB                                       263     
#define HWA_SHIFT1_8_ROW32_LSB                                       256     
#define HWA_SHIFT1_8_ROW31_SIZE                                      8        // 8-bit shift for C bank 1 row or column 31
#define HWA_SHIFT1_8_ROW31_MSB                                       255     
#define HWA_SHIFT1_8_ROW31_LSB                                       248     
#define HWA_SHIFT1_8_ROW30_SIZE                                      8        // 8-bit shift for C bank 1 row or column 30
#define HWA_SHIFT1_8_ROW30_MSB                                       247     
#define HWA_SHIFT1_8_ROW30_LSB                                       240     
#define HWA_SHIFT1_8_ROW29_SIZE                                      8        // 8-bit shift for C bank 1 row or column 29
#define HWA_SHIFT1_8_ROW29_MSB                                       239     
#define HWA_SHIFT1_8_ROW29_LSB                                       232     
#define HWA_SHIFT1_8_ROW28_SIZE                                      8        // 8-bit shift for C bank 1 row or column 28
#define HWA_SHIFT1_8_ROW28_MSB                                       231     
#define HWA_SHIFT1_8_ROW28_LSB                                       224     
#define HWA_SHIFT1_8_ROW27_SIZE                                      8        // 8-bit shift for C bank 1 row or column 27
#define HWA_SHIFT1_8_ROW27_MSB                                       223     
#define HWA_SHIFT1_8_ROW27_LSB                                       216     
#define HWA_SHIFT1_8_ROW26_SIZE                                      8        // 8-bit shift for C bank 1 row or column 26
#define HWA_SHIFT1_8_ROW26_MSB                                       215     
#define HWA_SHIFT1_8_ROW26_LSB                                       208     
#define HWA_SHIFT1_8_ROW25_SIZE                                      8        // 8-bit shift for C bank 1 row or column 25
#define HWA_SHIFT1_8_ROW25_MSB                                       207     
#define HWA_SHIFT1_8_ROW25_LSB                                       200     
#define HWA_SHIFT1_8_ROW24_SIZE                                      8        // 8-bit shift for C bank 1 row or column 24
#define HWA_SHIFT1_8_ROW24_MSB                                       199     
#define HWA_SHIFT1_8_ROW24_LSB                                       192     
#define HWA_SHIFT1_8_ROW23_SIZE                                      8        // 8-bit shift for C bank 1 row or column 23
#define HWA_SHIFT1_8_ROW23_MSB                                       191     
#define HWA_SHIFT1_8_ROW23_LSB                                       184     
#define HWA_SHIFT1_8_ROW22_SIZE                                      8        // 8-bit shift for C bank 1 row or column 22
#define HWA_SHIFT1_8_ROW22_MSB                                       183     
#define HWA_SHIFT1_8_ROW22_LSB                                       176     
#define HWA_SHIFT1_8_ROW21_SIZE                                      8        // 8-bit shift for C bank 1 row or column 21
#define HWA_SHIFT1_8_ROW21_MSB                                       175     
#define HWA_SHIFT1_8_ROW21_LSB                                       168     
#define HWA_SHIFT1_8_ROW20_SIZE                                      8        // 8-bit shift for C bank 1 row or column 20
#define HWA_SHIFT1_8_ROW20_MSB                                       167     
#define HWA_SHIFT1_8_ROW20_LSB                                       160     
#define HWA_SHIFT1_8_ROW19_SIZE                                      8        // 8-bit shift for C bank 1 row or column 19
#define HWA_SHIFT1_8_ROW19_MSB                                       159     
#define HWA_SHIFT1_8_ROW19_LSB                                       152     
#define HWA_SHIFT1_8_ROW18_SIZE                                      8        // 8-bit shift for C bank 1 row or column 18
#define HWA_SHIFT1_8_ROW18_MSB                                       151     
#define HWA_SHIFT1_8_ROW18_LSB                                       144     
#define HWA_SHIFT1_8_ROW17_SIZE                                      8        // 8-bit shift for C bank 1 row or column 17
#define HWA_SHIFT1_8_ROW17_MSB                                       143     
#define HWA_SHIFT1_8_ROW17_LSB                                       136     
#define HWA_SHIFT1_8_ROW16_SIZE                                      8        // 8-bit shift for C bank 1 row or column 16
#define HWA_SHIFT1_8_ROW16_MSB                                       135     
#define HWA_SHIFT1_8_ROW16_LSB                                       128     
#define HWA_SHIFT1_8_ROW15_SIZE                                      8        // 8-bit shift for C bank 1 row or column 15
#define HWA_SHIFT1_8_ROW15_MSB                                       127     
#define HWA_SHIFT1_8_ROW15_LSB                                       120     
#define HWA_SHIFT1_8_ROW14_SIZE                                      8        // 8-bit shift for C bank 1 row or column 14
#define HWA_SHIFT1_8_ROW14_MSB                                       119     
#define HWA_SHIFT1_8_ROW14_LSB                                       112     
#define HWA_SHIFT1_8_ROW13_SIZE                                      8        // 8-bit shift for C bank 1 row or column 13
#define HWA_SHIFT1_8_ROW13_MSB                                       111     
#define HWA_SHIFT1_8_ROW13_LSB                                       104     
#define HWA_SHIFT1_8_ROW12_SIZE                                      8        // 8-bit shift for C bank 1 row or column 12
#define HWA_SHIFT1_8_ROW12_MSB                                       103     
#define HWA_SHIFT1_8_ROW12_LSB                                       96      
#define HWA_SHIFT1_8_ROW11_SIZE                                      8        // 8-bit shift for C bank 1 row or column 11
#define HWA_SHIFT1_8_ROW11_MSB                                       95      
#define HWA_SHIFT1_8_ROW11_LSB                                       88      
#define HWA_SHIFT1_8_ROW10_SIZE                                      8        // 8-bit shift for C bank 1 row or column 10
#define HWA_SHIFT1_8_ROW10_MSB                                       87      
#define HWA_SHIFT1_8_ROW10_LSB                                       80      
#define HWA_SHIFT1_8_ROW9_SIZE                                       8        // 8-bit shift for C bank 1 row or column 9
#define HWA_SHIFT1_8_ROW9_MSB                                        79      
#define HWA_SHIFT1_8_ROW9_LSB                                        72      
#define HWA_SHIFT1_8_ROW8_SIZE                                       8        // 8-bit shift for C bank 1 row or column 8
#define HWA_SHIFT1_8_ROW8_MSB                                        71      
#define HWA_SHIFT1_8_ROW8_LSB                                        64      
#define HWA_SHIFT1_8_ROW7_SIZE                                       8        // 8-bit shift for C bank 1 row or column 7
#define HWA_SHIFT1_8_ROW7_MSB                                        63      
#define HWA_SHIFT1_8_ROW7_LSB                                        56      
#define HWA_SHIFT1_8_ROW6_SIZE                                       8        // 8-bit shift for C bank 1 row or column 6
#define HWA_SHIFT1_8_ROW6_MSB                                        55      
#define HWA_SHIFT1_8_ROW6_LSB                                        48      
#define HWA_SHIFT1_8_ROW5_SIZE                                       8        // 8-bit shift for C bank 1 row or column 5
#define HWA_SHIFT1_8_ROW5_MSB                                        47      
#define HWA_SHIFT1_8_ROW5_LSB                                        40      
#define HWA_SHIFT1_8_ROW4_SIZE                                       8        // 8-bit shift for C bank 1 row or column 4
#define HWA_SHIFT1_8_ROW4_MSB                                        39      
#define HWA_SHIFT1_8_ROW4_LSB                                        32      
#define HWA_SHIFT1_8_ROW3_SIZE                                       8        // 8-bit shift for C bank 1 row or column 3
#define HWA_SHIFT1_8_ROW3_MSB                                        31      
#define HWA_SHIFT1_8_ROW3_LSB                                        24      
#define HWA_SHIFT1_8_ROW2_SIZE                                       8        // 8-bit shift for C bank 1 row or column 2
#define HWA_SHIFT1_8_ROW2_MSB                                        23      
#define HWA_SHIFT1_8_ROW2_LSB                                        16      
#define HWA_SHIFT1_8_ROW1_SIZE                                       8        // 8-bit shift for C bank 1 row or column 1
#define HWA_SHIFT1_8_ROW1_MSB                                        15      
#define HWA_SHIFT1_8_ROW1_LSB                                        8       
#define HWA_SHIFT1_8_ROW0_SIZE                                       8        // 8-bit shift for C bank 1 row or column 0
#define HWA_SHIFT1_8_ROW0_MSB                                        7       
#define HWA_SHIFT1_8_ROW0_LSB                                        0       
// Declarations for reg HWA_SHIFT0_16
#define HWA_SHIFT0_16_SIZE                                           512     
#define HWA_SHIFT0_16_MSB                                            511     
#define HWA_SHIFT0_16_LSB                                            0       
#define HWA_SHIFT0_16_RSVD_SIZE                                      256      // Software should write zero to this field
#define HWA_SHIFT0_16_RSVD_MSB                                       511     
#define HWA_SHIFT0_16_RSVD_LSB                                       256     
#define HWA_SHIFT0_16_ROW31_SIZE                                     8        // 8-bit shift for C bank 0 row or column 31
#define HWA_SHIFT0_16_ROW31_MSB                                      255     
#define HWA_SHIFT0_16_ROW31_LSB                                      248     
#define HWA_SHIFT0_16_ROW30_SIZE                                     8        // 8-bit shift for C bank 0 row or column 30
#define HWA_SHIFT0_16_ROW30_MSB                                      247     
#define HWA_SHIFT0_16_ROW30_LSB                                      240     
#define HWA_SHIFT0_16_ROW29_SIZE                                     8        // 8-bit shift for C bank 0 row or column 29
#define HWA_SHIFT0_16_ROW29_MSB                                      239     
#define HWA_SHIFT0_16_ROW29_LSB                                      232     
#define HWA_SHIFT0_16_ROW28_SIZE                                     8        // 8-bit shift for C bank 0 row or column 28
#define HWA_SHIFT0_16_ROW28_MSB                                      231     
#define HWA_SHIFT0_16_ROW28_LSB                                      224     
#define HWA_SHIFT0_16_ROW27_SIZE                                     8        // 8-bit shift for C bank 0 row or column 27
#define HWA_SHIFT0_16_ROW27_MSB                                      223     
#define HWA_SHIFT0_16_ROW27_LSB                                      216     
#define HWA_SHIFT0_16_ROW26_SIZE                                     8        // 8-bit shift for C bank 0 row or column 26
#define HWA_SHIFT0_16_ROW26_MSB                                      215     
#define HWA_SHIFT0_16_ROW26_LSB                                      208     
#define HWA_SHIFT0_16_ROW25_SIZE                                     8        // 8-bit shift for C bank 0 row or column 25
#define HWA_SHIFT0_16_ROW25_MSB                                      207     
#define HWA_SHIFT0_16_ROW25_LSB                                      200     
#define HWA_SHIFT0_16_ROW24_SIZE                                     8        // 8-bit shift for C bank 0 row or column 24
#define HWA_SHIFT0_16_ROW24_MSB                                      199     
#define HWA_SHIFT0_16_ROW24_LSB                                      192     
#define HWA_SHIFT0_16_ROW23_SIZE                                     8        // 8-bit shift for C bank 0 row or column 23
#define HWA_SHIFT0_16_ROW23_MSB                                      191     
#define HWA_SHIFT0_16_ROW23_LSB                                      184     
#define HWA_SHIFT0_16_ROW22_SIZE                                     8        // 8-bit shift for C bank 0 row or column 22
#define HWA_SHIFT0_16_ROW22_MSB                                      183     
#define HWA_SHIFT0_16_ROW22_LSB                                      176     
#define HWA_SHIFT0_16_ROW21_SIZE                                     8        // 8-bit shift for C bank 0 row or column 21
#define HWA_SHIFT0_16_ROW21_MSB                                      175     
#define HWA_SHIFT0_16_ROW21_LSB                                      168     
#define HWA_SHIFT0_16_ROW20_SIZE                                     8        // 8-bit shift for C bank 0 row or column 20
#define HWA_SHIFT0_16_ROW20_MSB                                      167     
#define HWA_SHIFT0_16_ROW20_LSB                                      160     
#define HWA_SHIFT0_16_ROW19_SIZE                                     8        // 8-bit shift for C bank 0 row or column 19
#define HWA_SHIFT0_16_ROW19_MSB                                      159     
#define HWA_SHIFT0_16_ROW19_LSB                                      152     
#define HWA_SHIFT0_16_ROW18_SIZE                                     8        // 8-bit shift for C bank 0 row or column 18
#define HWA_SHIFT0_16_ROW18_MSB                                      151     
#define HWA_SHIFT0_16_ROW18_LSB                                      144     
#define HWA_SHIFT0_16_ROW17_SIZE                                     8        // 8-bit shift for C bank 0 row or column 17
#define HWA_SHIFT0_16_ROW17_MSB                                      143     
#define HWA_SHIFT0_16_ROW17_LSB                                      136     
#define HWA_SHIFT0_16_ROW16_SIZE                                     8        // 8-bit shift for C bank 0 row or column 16
#define HWA_SHIFT0_16_ROW16_MSB                                      135     
#define HWA_SHIFT0_16_ROW16_LSB                                      128     
#define HWA_SHIFT0_16_ROW15_SIZE                                     8        // 8-bit shift for C bank 0 row or column 15
#define HWA_SHIFT0_16_ROW15_MSB                                      127     
#define HWA_SHIFT0_16_ROW15_LSB                                      120     
#define HWA_SHIFT0_16_ROW14_SIZE                                     8        // 8-bit shift for C bank 0 row or column 14
#define HWA_SHIFT0_16_ROW14_MSB                                      119     
#define HWA_SHIFT0_16_ROW14_LSB                                      112     
#define HWA_SHIFT0_16_ROW13_SIZE                                     8        // 8-bit shift for C bank 0 row or column 13
#define HWA_SHIFT0_16_ROW13_MSB                                      111     
#define HWA_SHIFT0_16_ROW13_LSB                                      104     
#define HWA_SHIFT0_16_ROW12_SIZE                                     8        // 8-bit shift for C bank 0 row or column 12
#define HWA_SHIFT0_16_ROW12_MSB                                      103     
#define HWA_SHIFT0_16_ROW12_LSB                                      96      
#define HWA_SHIFT0_16_ROW11_SIZE                                     8        // 8-bit shift for C bank 0 row or column 11
#define HWA_SHIFT0_16_ROW11_MSB                                      95      
#define HWA_SHIFT0_16_ROW11_LSB                                      88      
#define HWA_SHIFT0_16_ROW10_SIZE                                     8        // 8-bit shift for C bank 0 row or column 10
#define HWA_SHIFT0_16_ROW10_MSB                                      87      
#define HWA_SHIFT0_16_ROW10_LSB                                      80      
#define HWA_SHIFT0_16_ROW9_SIZE                                      8        // 8-bit shift for C bank 0 row or column 9
#define HWA_SHIFT0_16_ROW9_MSB                                       79      
#define HWA_SHIFT0_16_ROW9_LSB                                       72      
#define HWA_SHIFT0_16_ROW8_SIZE                                      8        // 8-bit shift for C bank 0 row or column 8
#define HWA_SHIFT0_16_ROW8_MSB                                       71      
#define HWA_SHIFT0_16_ROW8_LSB                                       64      
#define HWA_SHIFT0_16_ROW7_SIZE                                      8        // 8-bit shift for C bank 0 row or column 7
#define HWA_SHIFT0_16_ROW7_MSB                                       63      
#define HWA_SHIFT0_16_ROW7_LSB                                       56      
#define HWA_SHIFT0_16_ROW6_SIZE                                      8        // 8-bit shift for C bank 0 row or column 6
#define HWA_SHIFT0_16_ROW6_MSB                                       55      
#define HWA_SHIFT0_16_ROW6_LSB                                       48      
#define HWA_SHIFT0_16_ROW5_SIZE                                      8        // 8-bit shift for C bank 0 row or column 5
#define HWA_SHIFT0_16_ROW5_MSB                                       47      
#define HWA_SHIFT0_16_ROW5_LSB                                       40      
#define HWA_SHIFT0_16_ROW4_SIZE                                      8        // 8-bit shift for C bank 0 row or column 4
#define HWA_SHIFT0_16_ROW4_MSB                                       39      
#define HWA_SHIFT0_16_ROW4_LSB                                       32      
#define HWA_SHIFT0_16_ROW3_SIZE                                      8        // 8-bit shift for C bank 0 row or column 3
#define HWA_SHIFT0_16_ROW3_MSB                                       31      
#define HWA_SHIFT0_16_ROW3_LSB                                       24      
#define HWA_SHIFT0_16_ROW2_SIZE                                      8        // 8-bit shift for C bank 0 row or column 2
#define HWA_SHIFT0_16_ROW2_MSB                                       23      
#define HWA_SHIFT0_16_ROW2_LSB                                       16      
#define HWA_SHIFT0_16_ROW1_SIZE                                      8        // 8-bit shift for C bank 0 row or column 1
#define HWA_SHIFT0_16_ROW1_MSB                                       15      
#define HWA_SHIFT0_16_ROW1_LSB                                       8       
#define HWA_SHIFT0_16_ROW0_SIZE                                      8        // 8-bit shift for C bank 0 row or column 0
#define HWA_SHIFT0_16_ROW0_MSB                                       7       
#define HWA_SHIFT0_16_ROW0_LSB                                       0       
// Declarations for reg HWA_SHIFT1_16
#define HWA_SHIFT1_16_SIZE                                           512     
#define HWA_SHIFT1_16_MSB                                            511     
#define HWA_SHIFT1_16_LSB                                            0       
#define HWA_SHIFT1_16_RSVD_SIZE                                      256      // Software should write zero to this field
#define HWA_SHIFT1_16_RSVD_MSB                                       511     
#define HWA_SHIFT1_16_RSVD_LSB                                       256     
#define HWA_SHIFT1_16_ROW31_SIZE                                     8        // 8-bit shift for C bank 1 row or column 31
#define HWA_SHIFT1_16_ROW31_MSB                                      255     
#define HWA_SHIFT1_16_ROW31_LSB                                      248     
#define HWA_SHIFT1_16_ROW30_SIZE                                     8        // 8-bit shift for C bank 1 row or column 30
#define HWA_SHIFT1_16_ROW30_MSB                                      247     
#define HWA_SHIFT1_16_ROW30_LSB                                      240     
#define HWA_SHIFT1_16_ROW29_SIZE                                     8        // 8-bit shift for C bank 1 row or column 29
#define HWA_SHIFT1_16_ROW29_MSB                                      239     
#define HWA_SHIFT1_16_ROW29_LSB                                      232     
#define HWA_SHIFT1_16_ROW28_SIZE                                     8        // 8-bit shift for C bank 1 row or column 28
#define HWA_SHIFT1_16_ROW28_MSB                                      231     
#define HWA_SHIFT1_16_ROW28_LSB                                      224     
#define HWA_SHIFT1_16_ROW27_SIZE                                     8        // 8-bit shift for C bank 1 row or column 27
#define HWA_SHIFT1_16_ROW27_MSB                                      223     
#define HWA_SHIFT1_16_ROW27_LSB                                      216     
#define HWA_SHIFT1_16_ROW26_SIZE                                     8        // 8-bit shift for C bank 1 row or column 26
#define HWA_SHIFT1_16_ROW26_MSB                                      215     
#define HWA_SHIFT1_16_ROW26_LSB                                      208     
#define HWA_SHIFT1_16_ROW25_SIZE                                     8        // 8-bit shift for C bank 1 row or column 25
#define HWA_SHIFT1_16_ROW25_MSB                                      207     
#define HWA_SHIFT1_16_ROW25_LSB                                      200     
#define HWA_SHIFT1_16_ROW24_SIZE                                     8        // 8-bit shift for C bank 1 row or column 24
#define HWA_SHIFT1_16_ROW24_MSB                                      199     
#define HWA_SHIFT1_16_ROW24_LSB                                      192     
#define HWA_SHIFT1_16_ROW23_SIZE                                     8        // 8-bit shift for C bank 1 row or column 23
#define HWA_SHIFT1_16_ROW23_MSB                                      191     
#define HWA_SHIFT1_16_ROW23_LSB                                      184     
#define HWA_SHIFT1_16_ROW22_SIZE                                     8        // 8-bit shift for C bank 1 row or column 22
#define HWA_SHIFT1_16_ROW22_MSB                                      183     
#define HWA_SHIFT1_16_ROW22_LSB                                      176     
#define HWA_SHIFT1_16_ROW21_SIZE                                     8        // 8-bit shift for C bank 1 row or column 21
#define HWA_SHIFT1_16_ROW21_MSB                                      175     
#define HWA_SHIFT1_16_ROW21_LSB                                      168     
#define HWA_SHIFT1_16_ROW20_SIZE                                     8        // 8-bit shift for C bank 1 row or column 20
#define HWA_SHIFT1_16_ROW20_MSB                                      167     
#define HWA_SHIFT1_16_ROW20_LSB                                      160     
#define HWA_SHIFT1_16_ROW19_SIZE                                     8        // 8-bit shift for C bank 1 row or column 19
#define HWA_SHIFT1_16_ROW19_MSB                                      159     
#define HWA_SHIFT1_16_ROW19_LSB                                      152     
#define HWA_SHIFT1_16_ROW18_SIZE                                     8        // 8-bit shift for C bank 1 row or column 18
#define HWA_SHIFT1_16_ROW18_MSB                                      151     
#define HWA_SHIFT1_16_ROW18_LSB                                      144     
#define HWA_SHIFT1_16_ROW17_SIZE                                     8        // 8-bit shift for C bank 1 row or column 17
#define HWA_SHIFT1_16_ROW17_MSB                                      143     
#define HWA_SHIFT1_16_ROW17_LSB                                      136     
#define HWA_SHIFT1_16_ROW16_SIZE                                     8        // 8-bit shift for C bank 1 row or column 16
#define HWA_SHIFT1_16_ROW16_MSB                                      135     
#define HWA_SHIFT1_16_ROW16_LSB                                      128     
#define HWA_SHIFT1_16_ROW15_SIZE                                     8        // 8-bit shift for C bank 1 row or column 15
#define HWA_SHIFT1_16_ROW15_MSB                                      127     
#define HWA_SHIFT1_16_ROW15_LSB                                      120     
#define HWA_SHIFT1_16_ROW14_SIZE                                     8        // 8-bit shift for C bank 1 row or column 14
#define HWA_SHIFT1_16_ROW14_MSB                                      119     
#define HWA_SHIFT1_16_ROW14_LSB                                      112     
#define HWA_SHIFT1_16_ROW13_SIZE                                     8        // 8-bit shift for C bank 1 row or column 13
#define HWA_SHIFT1_16_ROW13_MSB                                      111     
#define HWA_SHIFT1_16_ROW13_LSB                                      104     
#define HWA_SHIFT1_16_ROW12_SIZE                                     8        // 8-bit shift for C bank 1 row or column 12
#define HWA_SHIFT1_16_ROW12_MSB                                      103     
#define HWA_SHIFT1_16_ROW12_LSB                                      96      
#define HWA_SHIFT1_16_ROW11_SIZE                                     8        // 8-bit shift for C bank 1 row or column 11
#define HWA_SHIFT1_16_ROW11_MSB                                      95      
#define HWA_SHIFT1_16_ROW11_LSB                                      88      
#define HWA_SHIFT1_16_ROW10_SIZE                                     8        // 8-bit shift for C bank 1 row or column 10
#define HWA_SHIFT1_16_ROW10_MSB                                      87      
#define HWA_SHIFT1_16_ROW10_LSB                                      80      
#define HWA_SHIFT1_16_ROW9_SIZE                                      8        // 8-bit shift for C bank 1 row or column 9
#define HWA_SHIFT1_16_ROW9_MSB                                       79      
#define HWA_SHIFT1_16_ROW9_LSB                                       72      
#define HWA_SHIFT1_16_ROW8_SIZE                                      8        // 8-bit shift for C bank 1 row or column 8
#define HWA_SHIFT1_16_ROW8_MSB                                       71      
#define HWA_SHIFT1_16_ROW8_LSB                                       64      
#define HWA_SHIFT1_16_ROW7_SIZE                                      8        // 8-bit shift for C bank 1 row or column 7
#define HWA_SHIFT1_16_ROW7_MSB                                       63      
#define HWA_SHIFT1_16_ROW7_LSB                                       56      
#define HWA_SHIFT1_16_ROW6_SIZE                                      8        // 8-bit shift for C bank 1 row or column 6
#define HWA_SHIFT1_16_ROW6_MSB                                       55      
#define HWA_SHIFT1_16_ROW6_LSB                                       48      
#define HWA_SHIFT1_16_ROW5_SIZE                                      8        // 8-bit shift for C bank 1 row or column 5
#define HWA_SHIFT1_16_ROW5_MSB                                       47      
#define HWA_SHIFT1_16_ROW5_LSB                                       40      
#define HWA_SHIFT1_16_ROW4_SIZE                                      8        // 8-bit shift for C bank 1 row or column 4
#define HWA_SHIFT1_16_ROW4_MSB                                       39      
#define HWA_SHIFT1_16_ROW4_LSB                                       32      
#define HWA_SHIFT1_16_ROW3_SIZE                                      8        // 8-bit shift for C bank 1 row or column 3
#define HWA_SHIFT1_16_ROW3_MSB                                       31      
#define HWA_SHIFT1_16_ROW3_LSB                                       24      
#define HWA_SHIFT1_16_ROW2_SIZE                                      8        // 8-bit shift for C bank 1 row or column 2
#define HWA_SHIFT1_16_ROW2_MSB                                       23      
#define HWA_SHIFT1_16_ROW2_LSB                                       16      
#define HWA_SHIFT1_16_ROW1_SIZE                                      8        // 8-bit shift for C bank 1 row or column 1
#define HWA_SHIFT1_16_ROW1_MSB                                       15      
#define HWA_SHIFT1_16_ROW1_LSB                                       8       
#define HWA_SHIFT1_16_ROW0_SIZE                                      8        // 8-bit shift for C bank 1 row or column 0
#define HWA_SHIFT1_16_ROW0_MSB                                       7       
#define HWA_SHIFT1_16_ROW0_LSB                                       0       
// Declarations for reg HWA_STATUS
#define HWA_STATUS_SIZE                                              512     
#define HWA_STATUS_MSB                                               511     
#define HWA_STATUS_LSB                                               0       
#define HWA_STATUS_FIRSTERRORCODE_SIZE                               6        // Sticky error code.
#define HWA_STATUS_FIRSTERRORCODE_MSB                                511     
#define HWA_STATUS_FIRSTERRORCODE_LSB                                506     
#define HWA_STATUS_LASTERRORCODE_SIZE                                6        // Last-detected error code, same encoding as the FirstErrorCode field.
#define HWA_STATUS_LASTERRORCODE_MSB                                 505     
#define HWA_STATUS_LASTERRORCODE_LSB                                 500     
#define HWA_STATUS_MMAID_SIZE                                        6        // MMA Identification Register.  See MMAID bus definition.
#define HWA_STATUS_MMAID_MSB                                         499     
#define HWA_STATUS_MMAID_LSB                                         494     
#define HWA_STATUS_X_STATUS_SIZE                                     190      // X FSM status field. See X_STATUS bus definition.
#define HWA_STATUS_X_STATUS_MSB                                      493     
#define HWA_STATUS_X_STATUS_LSB                                      304     
#define HWA_STATUS_C_STATUS_SIZE                                     240      // C FSM status field. See C_STATUS bus definition.
#define HWA_STATUS_C_STATUS_MSB                                      303     
#define HWA_STATUS_C_STATUS_LSB                                      64      
#define HWA_STATUS_B_STATUS_SIZE                                     56       // B FSM status field. See B_STATUS bus definition.
#define HWA_STATUS_B_STATUS_MSB                                      63      
#define HWA_STATUS_B_STATUS_LSB                                      8       
#define HWA_STATUS_A_STATUS_SIZE                                     8        // A FSM status field. See A_STATUS bus definition.
#define HWA_STATUS_A_STATUS_MSB                                      7       
#define HWA_STATUS_A_STATUS_LSB                                      0       
// Declarations for reg MMAID
#define MMAID_SIZE                                                   6       
#define MMAID_MSB                                                    5       
#define MMAID_LSB                                                    0       
#define MMAID_MMAID_MAJOR_SIZE                                       2        // MMA instruction set, major version.
#define MMAID_MMAID_MAJOR_MSB                                        5       
#define MMAID_MMAID_MAJOR_LSB                                        4       
#define MMAID_MMAID_MAJOR_MMA_1                                      0        // MMA version 1 instruction set
#define MMAID_MMAID_MAJOR_MMA_2                                      1        // MMA version 2 instruction set
#define MMAID_MMAID_MAJOR_RESERVED_MMA_3                             2        // MMA version 3 instruction set (currently undefined)
#define MMAID_MMAID_MAJOR_RESERVED_MMA_4                             3        // MMA version 4 instruction set (currently undefined)
#define MMAID_MMAID_MINOR_SIZE                                       4        // MMA instruction set, minor version.
#define MMAID_MMAID_MINOR_MSB                                        3       
#define MMAID_MMAID_MINOR_LSB                                        0       
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_0                            0        // MMA minor revision 0  of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_1                            1        // MMA minor revision 1  of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_2                            2        // MMA minor revision 2  of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_3                            3        // MMA minor revision 3  of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_4                            4        // MMA minor revision 4  of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_5                            5        // MMA minor revision 5  of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_6                            6        // MMA minor revision 6  of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_7                            7        // MMA minor revision 7  of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_8                            8        // MMA minor revision 8  of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_9                            9        // MMA minor revision 9  of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_10                           10       // MMA minor revision 10 of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_11                           11       // MMA minor revision 11 of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_12                           12       // MMA minor revision 12 of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_13                           13       // MMA minor revision 13 of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_14                           14       // MMA minor revision 14 of the specified major version
#define MMAID_MMAID_MINOR_MMA_MINOR_REV_15                           15       // MMA minor revision 15 of the specified major version
// Declarations for bus A_STATUS
#define A_STATUS_SIZE                                                8       
#define A_STATUS_MSB                                                 7       
#define A_STATUS_LSB                                                 0       
#define A_STATUS_ACNT_SIZE                                           6        // A operand register storage counter when the A operand storage is enabled.
#define A_STATUS_ACNT_MSB                                            7       
#define A_STATUS_ACNT_LSB                                            2       
#define A_STATUS_ERROR_SIZE                                          1        // set when the A FSM has detected an error condition
#define A_STATUS_ERROR_MSB                                           1       
#define A_STATUS_ERROR_LSB                                           1       
#define A_STATUS_HALTED_SIZE                                         1        // set when the A FSM is halted for any reason
#define A_STATUS_HALTED_MSB                                          0       
#define A_STATUS_HALTED_LSB                                          0       
// Declarations for bus B_STATUS
#define B_STATUS_SIZE                                                56      
#define B_STATUS_MSB                                                 55      
#define B_STATUS_LSB                                                 0       
#define B_STATUS_RSVD_SIZE                                           1        // Reserved field. Software should not assume a specific value will be returned by hardware when this field is read.
#define B_STATUS_RSVD_MSB                                            55      
#define B_STATUS_RSVD_LSB                                            55      
#define B_STATUS_BCNT1_5_5_SIZE                                      1        // Optional B1 bank row counter bits [5:5] used when HWA_CONFIG.BCNT1_ENABLE is set.
#define B_STATUS_BCNT1_5_5_MSB                                       54      
#define B_STATUS_BCNT1_5_5_LSB                                       54      
#define B_STATUS_BCNT_SIZE                                           6        // current B row/column storage counter.
#define B_STATUS_BCNT_MSB                                            53      
#define B_STATUS_BCNT_LSB                                            48      
#define B_STATUS_BCNT1_4_0_SIZE                                      5        // Optional B1 bank row counter bits [4:0] used when HWA_CONFIG.BCNT1_ENABLE is set.
#define B_STATUS_BCNT1_4_0_MSB                                       47      
#define B_STATUS_BCNT1_4_0_LSB                                       43      
#define B_STATUS_BBANK_SIZE                                          1        // current B bank
#define B_STATUS_BBANK_MSB                                           42      
#define B_STATUS_BBANK_LSB                                           42      
#define B_STATUS_ERROR_SIZE                                          1        // set when the B FSM has detected an error condition
#define B_STATUS_ERROR_MSB                                           41      
#define B_STATUS_ERROR_LSB                                           41      
#define B_STATUS_HALTED_SIZE                                         1        // set when the B FSM is halted for any reason
#define B_STATUS_HALTED_MSB                                          40      
#define B_STATUS_HALTED_LSB                                          40      
#define B_STATUS_BRSTCNT_SIZE                                        8        // Remaining iterations in B offset period for the current bank when BCNT1 is disabled.  When HWA_CONFIG.BCNT1_ENABLE is set, BRSTCNT is used with BCNT only for Bank 0.
#define B_STATUS_BRSTCNT_MSB                                         39      
#define B_STATUS_BRSTCNT_LSB                                         32      
#define B_STATUS_BSWCNT_SIZE                                         32       // When BCNT1 is disabled, this is a 32-bit field holding the remaining iterations in B bank swap period.  When HWA_CONFIG.BCNT1_ENABLE is set, the most significant 8-bits are used to store and observe the BRSTCNT1 counter for the BCNT1 reset period. In BCNT1 mode, the width of the BSWCNT operations is 24 bits.
#define B_STATUS_BSWCNT_MSB                                          31      
#define B_STATUS_BSWCNT_LSB                                          0       
// Declarations for bus C_STATUS
#define C_STATUS_SIZE                                                240     
#define C_STATUS_MSB                                                 239     
#define C_STATUS_LSB                                                 0       
#define C_STATUS_CLROW_SIZE                                          8        // When A_STATUS.ARF_CTRL is ARF_DISABLE, this field contains the current C operand load (HWALD*) write row or sub-row depending on X1 or X4 scaling, otherwise it contains the current ARF read address.
#define C_STATUS_CLROW_MSB                                           239     
#define C_STATUS_CLROW_LSB                                           232     
#define C_STATUS_RSVD_SIZE                                           2        // Reserved field. Software should not assume a specific value will be returned by hardware when this field is read.
#define C_STATUS_RSVD_MSB                                            231     
#define C_STATUS_RSVD_LSB                                            230     
#define C_STATUS_CWROW_SIZE                                          6        // Current C computation write row
#define C_STATUS_CWROW_MSB                                           229     
#define C_STATUS_CWROW_LSB                                           224     
#define C_STATUS_RSVD_1_SIZE                                         2        // Reserved field. Software should not assume a specific value will be returned by hardware when this field is read.
#define C_STATUS_RSVD_1_MSB                                          223     
#define C_STATUS_RSVD_1_LSB                                          222     
#define C_STATUS_CRROW_SIZE                                          6        // Current C read row
#define C_STATUS_CRROW_MSB                                           221     
#define C_STATUS_CRROW_LSB                                           216     
#define C_STATUS_RSVD_2_SIZE                                         1        // Reserved field. Software should not assume a specific value will be returned by hardware when this field is read.
#define C_STATUS_RSVD_2_MSB                                          215     
#define C_STATUS_RSVD_2_LSB                                          215     
#define C_STATUS_CLBANK_SIZE                                         1        // Current C operand write bank
#define C_STATUS_CLBANK_MSB                                          214     
#define C_STATUS_CLBANK_LSB                                          214     
#define C_STATUS_CWBANK_SIZE                                         1        // Current C computation write bank
#define C_STATUS_CWBANK_MSB                                          213     
#define C_STATUS_CWBANK_LSB                                          213     
#define C_STATUS_CRBANK_SIZE                                         1        // Current C read bank
#define C_STATUS_CRBANK_MSB                                          212     
#define C_STATUS_CRBANK_LSB                                          212     
#define C_STATUS_BBANK_SIZE                                          1        // Current B bank for the matrix calculation
#define C_STATUS_BBANK_MSB                                           211     
#define C_STATUS_BBANK_LSB                                           211     
#define C_STATUS_OP_SIZE                                             1        // Current operation selection
#define C_STATUS_OP_MSB                                              210     
#define C_STATUS_OP_LSB                                              210     
#define C_STATUS_ERROR_SIZE                                          1        // Set when the C FSM has detected an error condition
#define C_STATUS_ERROR_MSB                                           209     
#define C_STATUS_ERROR_LSB                                           209     
#define C_STATUS_HALTED_SIZE                                         1        // Set when the C FSM is halted for any reason
#define C_STATUS_HALTED_MSB                                          208     
#define C_STATUS_HALTED_LSB                                          208     
#define C_STATUS_CLRSTCNT_SIZE                                       8        // Remaining iterations in C operand load (HWALD*) write row offset reset period
#define C_STATUS_CLRSTCNT_MSB                                        207     
#define C_STATUS_CLRSTCNT_LSB                                        200     
#define C_STATUS_CWRSTCNT_SIZE                                       32       // Remaining iterations in C computation write row offset reset period
#define C_STATUS_CWRSTCNT_MSB                                        199     
#define C_STATUS_CWRSTCNT_LSB                                        168     
#define C_STATUS_CRRSTCNT_SIZE                                       32       // Remaining iterations in C computation read row offset reset period
#define C_STATUS_CRRSTCNT_MSB                                        167     
#define C_STATUS_CRRSTCNT_LSB                                        136     
#define C_STATUS_CLSWCNT_SIZE                                        8        // Remaining iterations in C operand load (HWALD*) write bank swap period
#define C_STATUS_CLSWCNT_MSB                                         135     
#define C_STATUS_CLSWCNT_LSB                                         128     
#define C_STATUS_CWSWCNT_SIZE                                        32       // Remaining iterations in C computation write bank swap period
#define C_STATUS_CWSWCNT_MSB                                         127     
#define C_STATUS_CWSWCNT_LSB                                         96      
#define C_STATUS_CRSWCNT_SIZE                                        32       // Remaining iterations in C computation read bank swap period
#define C_STATUS_CRSWCNT_MSB                                         95      
#define C_STATUS_CRSWCNT_LSB                                         64      
#define C_STATUS_BSWCNT_SIZE                                         32       // Remaining iterations in B bank swap period
#define C_STATUS_BSWCNT_MSB                                          63      
#define C_STATUS_BSWCNT_LSB                                          32      
#define C_STATUS_OPCNT_SIZE                                          32       // Remaining iterations in current operation swap period
#define C_STATUS_OPCNT_MSB                                           31      
#define C_STATUS_OPCNT_LSB                                           0       
// Declarations for bus X_STATUS
#define X_STATUS_SIZE                                                190     
#define X_STATUS_MSB                                                 189     
#define X_STATUS_LSB                                                 0       
#define X_STATUS_RSVD_SIZE                                           6        // Reserved field. Software should not assume a specific value will be returned by hardware when this field is read.
#define X_STATUS_RSVD_MSB                                            189     
#define X_STATUS_RSVD_LSB                                            184     
#define X_STATUS_MAX_SIZE                                            64       // Maximum value over full-width C elements with the same signed/unsigned type as the C elements.
#define X_STATUS_MAX_MSB                                             183     
#define X_STATUS_MAX_LSB                                             120     
#define X_STATUS_MIN_SIZE                                            64       // Minimum value over full-width C elements with the same signed/unsigned type as the C elements.
#define X_STATUS_MIN_MSB                                             119     
#define X_STATUS_MIN_LSB                                             56      
#define X_STATUS_CRROW_SIZE                                          8        // Current C read row
#define X_STATUS_CRROW_MSB                                           55      
#define X_STATUS_CRROW_LSB                                           48      
#define X_STATUS_RSVD_1_SIZE                                         5        // Reserved field. Software should not assume a specific value will be returned by hardware when this field is read.
#define X_STATUS_RSVD_1_MSB                                          47      
#define X_STATUS_RSVD_1_LSB                                          43      
#define X_STATUS_CBANK_SIZE                                          1        // Current C bank
#define X_STATUS_CBANK_MSB                                           42      
#define X_STATUS_CBANK_LSB                                           42      
#define X_STATUS_ERROR_SIZE                                          1        // Set when the X FSM has detected an error condition
#define X_STATUS_ERROR_MSB                                           41      
#define X_STATUS_ERROR_LSB                                           41      
#define X_STATUS_HALTED_SIZE                                         1        // Set when the X FSM is halted for any reason
#define X_STATUS_HALTED_MSB                                          40      
#define X_STATUS_HALTED_LSB                                          40      
#define X_STATUS_CRRSTCNT_SIZE                                       8        // Remaining iterations in C read row offset period
#define X_STATUS_CRRSTCNT_MSB                                        39      
#define X_STATUS_CRRSTCNT_LSB                                        32      
#define X_STATUS_CSWCNT_SIZE                                         32       // Remaining iterations in C read bank swap period
#define X_STATUS_CSWCNT_MSB                                          31      
#define X_STATUS_CSWCNT_LSB                                          0       
// Declarations for bus MMA_ERROR_CODE
#define MMA_ERROR_CODE_SIZE                                          6       
#define MMA_ERROR_CODE_MSB                                           5       
#define MMA_ERROR_CODE_LSB                                           0       
#define MMA_ERROR_CODE_ERRORCODE_SIZE                                6        // Encoded error code.
#define MMA_ERROR_CODE_ERRORCODE_MSB                                 5       
#define MMA_ERROR_CODE_ERRORCODE_LSB                                 0       
#define MMA_ERROR_CODE_ERRORCODE_NO_ERROR                            0        // No error was detected
#define MMA_ERROR_CODE_ERRORCODE_RESERVED_01                         1        // Reserved error code, not used on the MMA 2.0 architecture
#define MMA_ERROR_CODE_ERRORCODE_C_READ_ERROR                        2        // More than one read from a C matrix bank (programming error)
#define MMA_ERROR_CODE_ERRORCODE_C_WRITE_ERROR                       3        // More than one write to a C matrix bank (programming error)
#define MMA_ERROR_CODE_ERRORCODE_X_UNDERFLOW                         4        // Transfer buffer read was attempted but there was no valid data in the FIFO (programming error)
#define MMA_ERROR_CODE_ERRORCODE_X_OVERFLOW                          5        // Transfer buffer read was attempted but an earlier HWA instruction caused the FIFO to overflow (programming error)
#define MMA_ERROR_CODE_ERRORCODE_FSM_STATE_ERROR                     6        // FSM state transition error (hardware error)
#define MMA_ERROR_CODE_ERRORCODE_OPERAND_ERROR                       7        // Unsupported on MMA 1.0 and MMA 2.0.  C7x does not source parity bits with HWA operands.  Vector operand parity error from C7x (hardware error)
#define MMA_ERROR_CODE_ERRORCODE_CONTROL_ERROR                       8        // Unsupported on MMA 1.0 and MMA 2.0.  C7x does not source parity bits with HWA controls.  Parity error on control from C7x (hardware error)
#define MMA_ERROR_CODE_ERRORCODE_CONFIG_PARITY                       9        // Parity error on HWA_CONFIG (hardware error)
#define MMA_ERROR_CODE_ERRORCODE_OFFSET_PARITY                       10       // Parity error on HWA_OFFSET (hardware error)
#define MMA_ERROR_CODE_ERRORCODE_ARF_PARITY                          11       // A operand register file parity error (hardware error)
#define MMA_ERROR_CODE_ERRORCODE_RESERVED_0C                         12       // Reserved error code, not used on the MMA 2.0 architecture
#define MMA_ERROR_CODE_ERRORCODE_RESERVED_0D                         13       // Reserved error code, not used on the MMA 2.0 architecture
#define MMA_ERROR_CODE_ERRORCODE_CR_WRITE_ERROR                      14       // HWA_BIAS[0:3], HWA_SCALE[0:1] or HWA_SHIFT[0:1] write rate error (programming error)
#define MMA_ERROR_CODE_ERRORCODE_RESERVED_0F                         15       // Reserved error code, not used on the MMA 2.0 architecture
#define A_FSM_PARAM_ARF_ENTRIES                                      64       // Number of A vector storage entries
