/*****************************************************************************/
/* UARCH_DECL.H                                                              */
/*                                                                           */
/* Copyright (c) 2020 Texas Instruments Incorporated                         */
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
// Produced at Thu Dec 17 10:58:05 2020
// Declarations for bus DBG_ADDR
#define DBG_ADDR_SIZE                                                17      
#define DBG_ADDR_MSB                                                 16      
#define DBG_ADDR_LSB                                                 0       
#define DBG_ADDR_DBG_IDX_SIZE                                        14       // Debug object index with in the defined MMA EDI address space.  See the below definitions for specific address layout.
#define DBG_ADDR_DBG_IDX_MSB                                         16      
#define DBG_ADDR_DBG_IDX_LSB                                         3       
#define DBG_ADDR_BYTE_OFFSET_SIZE                                    3        // Byte offset of register being accessed
#define DBG_ADDR_BYTE_OFFSET_MSB                                     2       
#define DBG_ADDR_BYTE_OFFSET_LSB                                     0       
// Declarations for bus DBG_IDX_ARRAY_SUBSPACE
#define DBG_IDX_ARRAY_SUBSPACE_SIZE                                  14      
#define DBG_IDX_ARRAY_SUBSPACE_MSB                                   13      
#define DBG_IDX_ARRAY_SUBSPACE_LSB                                   0       
#define DBG_IDX_ARRAY_SUBSPACE_OPERAND_SIZE                          2        // MMA EDI array operand selection
#define DBG_IDX_ARRAY_SUBSPACE_OPERAND_MSB                           13      
#define DBG_IDX_ARRAY_SUBSPACE_OPERAND_LSB                           12      
#define DBG_IDX_ARRAY_SUBSPACE_OPERAND_AX1                           0        // A operand scaled by 1
#define DBG_IDX_ARRAY_SUBSPACE_OPERAND_ARF                           1        // A register file
#define DBG_IDX_ARRAY_SUBSPACE_OPERAND_B0                            2        // B operand from bank 0
#define DBG_IDX_ARRAY_SUBSPACE_OPERAND_B1                            3        // B operand from bank 1
#define DBG_IDX_ARRAY_SUBSPACE_ROW_SIZE                              6        // Array element row number
#define DBG_IDX_ARRAY_SUBSPACE_ROW_MSB                               11      
#define DBG_IDX_ARRAY_SUBSPACE_ROW_LSB                               6       
#define DBG_IDX_ARRAY_SUBSPACE_COL_SIZE                              6        // 64-bit field in the selected row
#define DBG_IDX_ARRAY_SUBSPACE_COL_MSB                               5       
#define DBG_IDX_ARRAY_SUBSPACE_COL_LSB                               0       
// Declarations for bus DBG_IDX_C_STORAGE_SUBSPACE
#define DBG_IDX_C_STORAGE_SUBSPACE_SIZE                              14      
#define DBG_IDX_C_STORAGE_SUBSPACE_MSB                               13      
#define DBG_IDX_C_STORAGE_SUBSPACE_LSB                               0       
#define DBG_IDX_C_STORAGE_SUBSPACE_RESERVED_SIZE                     1        // Reserved field.  Software should write zeros to this field for defined behavior.
#define DBG_IDX_C_STORAGE_SUBSPACE_RESERVED_MSB                      13      
#define DBG_IDX_C_STORAGE_SUBSPACE_RESERVED_LSB                      13      
#define DBG_IDX_C_STORAGE_SUBSPACE_BANK_SIZE                         1        // MMA EDI C storage bank selection from ARRAY field of EDI address
#define DBG_IDX_C_STORAGE_SUBSPACE_BANK_MSB                          12      
#define DBG_IDX_C_STORAGE_SUBSPACE_BANK_LSB                          12      
#define DBG_IDX_C_STORAGE_SUBSPACE_BANK_BANK0                        0        // C storage bank 0
#define DBG_IDX_C_STORAGE_SUBSPACE_BANK_BANK1                        1        // C storage bank 1
#define DBG_IDX_C_STORAGE_SUBSPACE_ROW_SIZE                          6        // Array element row number from COLUMN field of EDI address
#define DBG_IDX_C_STORAGE_SUBSPACE_ROW_MSB                           11      
#define DBG_IDX_C_STORAGE_SUBSPACE_ROW_LSB                           6       
#define DBG_IDX_C_STORAGE_SUBSPACE_COL_SIZE                          6        // 64-bit field in the selected row from ROW field of EDI address
#define DBG_IDX_C_STORAGE_SUBSPACE_COL_MSB                           5       
#define DBG_IDX_C_STORAGE_SUBSPACE_COL_LSB                           0       
// Declarations for bus DBG_IDX_X_STORAGE_SUBSPACE
#define DBG_IDX_X_STORAGE_SUBSPACE_SIZE                              14      
#define DBG_IDX_X_STORAGE_SUBSPACE_MSB                               13      
#define DBG_IDX_X_STORAGE_SUBSPACE_LSB                               0       
#define DBG_IDX_X_STORAGE_SUBSPACE_RESERVED_SIZE                     5        // Reserved field.  Software should write zeros to this field for defined behavior.
#define DBG_IDX_X_STORAGE_SUBSPACE_RESERVED_MSB                      13      
#define DBG_IDX_X_STORAGE_SUBSPACE_RESERVED_LSB                      9       
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_SIZE                         6        // Transfer Buffer address from ROW field of EDI address
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_MSB                          8       
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_LSB                          3       
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X0                           0        // Transfer buffer element 0
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X1                           1        // Transfer buffer element 1
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X2                           2        // Transfer buffer element 2
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X3                           3        // Transfer buffer element 3
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X4                           4        // Transfer buffer element 4
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X5                           5        // Transfer buffer element 5
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X6                           6        // Transfer buffer element 6
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X7                           7        // Transfer buffer element 7
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X8                           8        // Transfer buffer element 8
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X9                           9        // Transfer buffer element 9
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X10                          10       // Transfer buffer element 10
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X11                          11       // Transfer buffer element 11
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X12                          12       // Transfer buffer element 12
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X13                          13       // Transfer buffer element 13
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X14                          14       // Transfer buffer element 14
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X15                          15       // Transfer buffer element 15
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X16                          16       // Transfer buffer element 16
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X17                          17       // Transfer buffer element 17
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X18                          18       // Transfer buffer element 18
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X19                          19       // Transfer buffer element 19
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X20                          20       // Transfer buffer element 20
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X21                          21       // Transfer buffer element 21
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X22                          22       // Transfer buffer element 22
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_X23                          23       // Transfer buffer element 23
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_CONFIG                   24       // HWA_CONFIG control register
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_OFFSET                   25       // HWA_OFFSET control register
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_STATUS                   26       // HWA_STATUS control register
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_BUSY                     27       // HWA_BUSY control register
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_BIAS0                    28       // Bias register 0
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_BIAS1                    29       // Bias register 1
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_BIAS2                    30       // Bias register 2
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_BIAS3                    31       // Bias register 3
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_SCALE0                   32       // Scale register 0
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_SCALE1                   33       // Scale register 1
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_SHIFT0                   34       // Shift register 0
#define DBG_IDX_X_STORAGE_SUBSPACE_XREG_HWA_SHIFT1                   35       // Shift register 1
#define DBG_IDX_X_STORAGE_SUBSPACE_COL_SIZE                          3        // 64-bit field in the selected register
#define DBG_IDX_X_STORAGE_SUBSPACE_COL_MSB                           2       
#define DBG_IDX_X_STORAGE_SUBSPACE_COL_LSB                           0       
// Declarations for bus DBG_IDX_CONTROL_SUBSPACE
#define DBG_IDX_CONTROL_SUBSPACE_SIZE                                14      
#define DBG_IDX_CONTROL_SUBSPACE_MSB                                 13      
#define DBG_IDX_CONTROL_SUBSPACE_LSB                                 0       
#define DBG_IDX_CONTROL_SUBSPACE_RESERVED_SIZE                       13       // Reserved field.  Software should write zeros to this field for defined behavior.
#define DBG_IDX_CONTROL_SUBSPACE_RESERVED_MSB                        13      
#define DBG_IDX_CONTROL_SUBSPACE_RESERVED_LSB                        1       
#define DBG_IDX_CONTROL_SUBSPACE_REGISTER_SIZE                       1        // Control register selection from ROW field of EDI address
#define DBG_IDX_CONTROL_SUBSPACE_REGISTER_MSB                        0       
#define DBG_IDX_CONTROL_SUBSPACE_REGISTER_LSB                        0       
// Declarations for bus EDI_STATE
#define EDI_STATE_SIZE                                               6       
#define EDI_STATE_MSB                                                5       
#define EDI_STATE_LSB                                                0       
#define EDI_STATE_STATE_SIZE                                         6        // MMA EDI controller current state
#define EDI_STATE_STATE_MSB                                          5       
#define EDI_STATE_STATE_LSB                                          0       
#define EDI_STATE_STATE_IDLE                                         0        // Idle state
#define EDI_STATE_STATE_BARRIER                                      53       // EDI access barrier state that waits for all MMA instructions to complete
#define EDI_STATE_STATE_FETCH0                                       33       // Fetch byte offset 0
#define EDI_STATE_STATE_WAIT0                                        34       // Wait for byte offset 0
#define EDI_STATE_STATE_FETCH1                                       3        // Fetch byte offset 1
#define EDI_STATE_STATE_WAIT1                                        36       // Wait for byte offset 1
#define EDI_STATE_STATE_FETCH2                                       5        // Fetch byte offset 2
#define EDI_STATE_STATE_WAIT2                                        6        // Wait for byte offset 2
#define EDI_STATE_STATE_FETCH3                                       39       // Fetch byte offset 3
#define EDI_STATE_STATE_WAIT3                                        40       // Wait for byte offset 3
#define EDI_STATE_STATE_FETCH4                                       9        // Fetch byte offset 4
#define EDI_STATE_STATE_WAIT4                                        10       // Wait for byte offset 4
#define EDI_STATE_STATE_FETCH5                                       43       // Fetch byte offset 5
#define EDI_STATE_STATE_WAIT5                                        12       // Wait for byte offset 5
#define EDI_STATE_STATE_FETCH6                                       45       // Fetch byte offset 6
#define EDI_STATE_STATE_WAIT6                                        46       // Wait for byte offset 6
#define EDI_STATE_STATE_FETCH7                                       15       // Fetch byte offset 7
#define EDI_STATE_STATE_WAIT7                                        48       // Wait for byte offset 7
#define EDI_STATE_STATE_SEND                                         17       // Send result to CPU
#define EDI_STATE_STATE_CANCEL                                       18       // Cancel current transation because a new transaction was requested
#define EDI_STATE_STATE_ERROR                                        51       // Access timeout was detected in the EDI controller
// Declarations for bus OTYPE
#define OTYPE_SIZE                                                   3       
#define OTYPE_MSB                                                    2       
#define OTYPE_LSB                                                    0       
#define OTYPE_SIGN_SIZE                                              1        // operand signed or unsigned selection
#define OTYPE_SIGN_MSB                                               2       
#define OTYPE_SIGN_LSB                                               2       
#define OTYPE_SIGN_S                                                 1        // Signed operand
#define OTYPE_SIGN_U                                                 0        // Unsigned operand
#define OTYPE_WIDTH_SIZE                                             2        // operand width
#define OTYPE_WIDTH_MSB                                              1       
#define OTYPE_WIDTH_LSB                                              0       
#define OTYPE_WIDTH_8                                                0        // (u)int_8 operand
#define OTYPE_WIDTH_16                                               1        // (u)int_16 operand
#define OTYPE_WIDTH_32                                               3        // (u)int_32 operand
// Declarations for bus DOT_L1_8
#define DOT_L1_8_SIZE                                                72      
#define DOT_L1_8_MSB                                                 71      
#define DOT_L1_8_LSB                                                 0       
#define DOT_L1_8_SUM3_SIZE                                           18       // 8-bit column 3 sum
#define DOT_L1_8_SUM3_MSB                                            71      
#define DOT_L1_8_SUM3_LSB                                            54      
#define DOT_L1_8_SUM2_SIZE                                           18       // 8-bit column 2 sum
#define DOT_L1_8_SUM2_MSB                                            53      
#define DOT_L1_8_SUM2_LSB                                            36      
#define DOT_L1_8_SUM1_SIZE                                           18       // 8-bit column 1 sum
#define DOT_L1_8_SUM1_MSB                                            35      
#define DOT_L1_8_SUM1_LSB                                            18      
#define DOT_L1_8_SUM0_SIZE                                           18       // 8-bit column 0 sum
#define DOT_L1_8_SUM0_MSB                                            17      
#define DOT_L1_8_SUM0_LSB                                            0       
// Declarations for bus DOT_L1_16
#define DOT_L1_16_SIZE                                               72      
#define DOT_L1_16_MSB                                                71      
#define DOT_L1_16_LSB                                                0       
#define DOT_L1_16_UNDEFINED_SIZE                                     2        // Undefined boolean values
#define DOT_L1_16_UNDEFINED_MSB                                      71      
#define DOT_L1_16_UNDEFINED_LSB                                      70      
#define DOT_L1_16_SUM1_SIZE                                          34       // 16-bit column 1 sum
#define DOT_L1_16_SUM1_MSB                                           69      
#define DOT_L1_16_SUM1_LSB                                           36      
#define DOT_L1_16_UNDEFINED_1_SIZE                                   2        // Undefined boolean values
#define DOT_L1_16_UNDEFINED_1_MSB                                    35      
#define DOT_L1_16_UNDEFINED_1_LSB                                    34      
#define DOT_L1_16_SUM0_SIZE                                          34       // 16-bit column 0 sum
#define DOT_L1_16_SUM0_MSB                                           33      
#define DOT_L1_16_SUM0_LSB                                           0       
// Declarations for bus DOT_L1_32
#define DOT_L1_32_SIZE                                               72      
#define DOT_L1_32_MSB                                                71      
#define DOT_L1_32_LSB                                                0       
#define DOT_L1_32_UNDEFINED_SIZE                                     6        // Undefined boolean values
#define DOT_L1_32_UNDEFINED_MSB                                      71      
#define DOT_L1_32_UNDEFINED_LSB                                      66      
#define DOT_L1_32_SUM0_SIZE                                          66       // 32-bit column 0 sum
#define DOT_L1_32_SUM0_MSB                                           65      
#define DOT_L1_32_SUM0_LSB                                           0       
// Declarations for bus DOT_L2_8
#define DOT_L2_8_SIZE                                                76      
#define DOT_L2_8_MSB                                                 75      
#define DOT_L2_8_LSB                                                 0       
#define DOT_L2_8_SUM3_SIZE                                           19       // 8-bit column 3 sum
#define DOT_L2_8_SUM3_MSB                                            75      
#define DOT_L2_8_SUM3_LSB                                            57      
#define DOT_L2_8_SUM2_SIZE                                           19       // 8-bit column 2 sum
#define DOT_L2_8_SUM2_MSB                                            56      
#define DOT_L2_8_SUM2_LSB                                            38      
#define DOT_L2_8_SUM1_SIZE                                           19       // 8-bit column 1 sum
#define DOT_L2_8_SUM1_MSB                                            37      
#define DOT_L2_8_SUM1_LSB                                            19      
#define DOT_L2_8_SUM0_SIZE                                           19       // 8-bit column 0 sum
#define DOT_L2_8_SUM0_MSB                                            18      
#define DOT_L2_8_SUM0_LSB                                            0       
// Declarations for bus DOT_L2_16
#define DOT_L2_16_SIZE                                               76      
#define DOT_L2_16_MSB                                                75      
#define DOT_L2_16_LSB                                                0       
#define DOT_L2_16_UNDEFINED_SIZE                                     4        // Undefined boolean values
#define DOT_L2_16_UNDEFINED_MSB                                      75      
#define DOT_L2_16_UNDEFINED_LSB                                      72      
#define DOT_L2_16_SUM1_SIZE                                          34       // 16-bit column 1 sum
#define DOT_L2_16_SUM1_MSB                                           71      
#define DOT_L2_16_SUM1_LSB                                           38      
#define DOT_L2_16_UNDEFINED_1_SIZE                                   4        // Undefined boolean values
#define DOT_L2_16_UNDEFINED_1_MSB                                    37      
#define DOT_L2_16_UNDEFINED_1_LSB                                    34      
#define DOT_L2_16_SUM0_SIZE                                          34       // 16-bit column 0 sum
#define DOT_L2_16_SUM0_MSB                                           33      
#define DOT_L2_16_SUM0_LSB                                           0       
// Declarations for bus DOT_L2_32
#define DOT_L2_32_SIZE                                               76      
#define DOT_L2_32_MSB                                                75      
#define DOT_L2_32_LSB                                                0       
#define DOT_L2_32_UNDEFINED_SIZE                                     11       // Undefined boolean values
#define DOT_L2_32_UNDEFINED_MSB                                      75      
#define DOT_L2_32_UNDEFINED_LSB                                      65      
#define DOT_L2_32_SUM0_SIZE                                          65       // 32-bit column 0 sum
#define DOT_L2_32_SUM0_MSB                                           64      
#define DOT_L2_32_SUM0_LSB                                           0       
// Declarations for bus DOT_L3_8
#define DOT_L3_8_SIZE                                                80      
#define DOT_L3_8_MSB                                                 79      
#define DOT_L3_8_LSB                                                 0       
#define DOT_L3_8_SUM3_SIZE                                           20       // 8-bit column 3 sum
#define DOT_L3_8_SUM3_MSB                                            79      
#define DOT_L3_8_SUM3_LSB                                            60      
#define DOT_L3_8_SUM2_SIZE                                           20       // 8-bit column 2 sum
#define DOT_L3_8_SUM2_MSB                                            59      
#define DOT_L3_8_SUM2_LSB                                            40      
#define DOT_L3_8_SUM1_SIZE                                           20       // 8-bit column 1 sum
#define DOT_L3_8_SUM1_MSB                                            39      
#define DOT_L3_8_SUM1_LSB                                            20      
#define DOT_L3_8_SUM0_SIZE                                           20       // 8-bit column 0 sum
#define DOT_L3_8_SUM0_MSB                                            19      
#define DOT_L3_8_SUM0_LSB                                            0       
// Declarations for bus DOT_L3_16
#define DOT_L3_16_SIZE                                               80      
#define DOT_L3_16_MSB                                                79      
#define DOT_L3_16_LSB                                                0       
#define DOT_L3_16_UNDEFINED_SIZE                                     4        // Undefined boolean values
#define DOT_L3_16_UNDEFINED_MSB                                      79      
#define DOT_L3_16_UNDEFINED_LSB                                      76      
#define DOT_L3_16_SUM1_SIZE                                          36       // 16-bit column 1 sum
#define DOT_L3_16_SUM1_MSB                                           75      
#define DOT_L3_16_SUM1_LSB                                           40      
#define DOT_L3_16_UNDEFINED_1_SIZE                                   4        // Undefined boolean values
#define DOT_L3_16_UNDEFINED_1_MSB                                    39      
#define DOT_L3_16_UNDEFINED_1_LSB                                    36      
#define DOT_L3_16_SUM0_SIZE                                          36       // 16-bit column 0 sum
#define DOT_L3_16_SUM0_MSB                                           35      
#define DOT_L3_16_SUM0_LSB                                           0       
// Declarations for bus DOT_L3_32
#define DOT_L3_32_SIZE                                               80      
#define DOT_L3_32_MSB                                                79      
#define DOT_L3_32_LSB                                                0       
#define DOT_L3_32_UNDEFINED_SIZE                                     10       // Undefined boolean values
#define DOT_L3_32_UNDEFINED_MSB                                      79      
#define DOT_L3_32_UNDEFINED_LSB                                      70      
#define DOT_L3_32_SUM0_SIZE                                          70       // 32-bit column 0 sum
#define DOT_L3_32_SUM0_MSB                                           69      
#define DOT_L3_32_SUM0_LSB                                           0       
// Declarations for bus DOT_L4_8
#define DOT_L4_8_SIZE                                                84      
#define DOT_L4_8_MSB                                                 83      
#define DOT_L4_8_LSB                                                 0       
#define DOT_L4_8_SUM3_SIZE                                           21       // 8-bit column 3 sum
#define DOT_L4_8_SUM3_MSB                                            83      
#define DOT_L4_8_SUM3_LSB                                            63      
#define DOT_L4_8_SUM2_SIZE                                           21       // 8-bit column 2 sum
#define DOT_L4_8_SUM2_MSB                                            62      
#define DOT_L4_8_SUM2_LSB                                            42      
#define DOT_L4_8_SUM1_SIZE                                           21       // 8-bit column 1 sum
#define DOT_L4_8_SUM1_MSB                                            41      
#define DOT_L4_8_SUM1_LSB                                            21      
#define DOT_L4_8_SUM0_SIZE                                           21       // 8-bit column 0 sum
#define DOT_L4_8_SUM0_MSB                                            20      
#define DOT_L4_8_SUM0_LSB                                            0       
// Declarations for bus DOT_L4_16
#define DOT_L4_16_SIZE                                               84      
#define DOT_L4_16_MSB                                                83      
#define DOT_L4_16_LSB                                                0       
#define DOT_L4_16_UNDEFINED_SIZE                                     5        // Undefined boolean values
#define DOT_L4_16_UNDEFINED_MSB                                      83      
#define DOT_L4_16_UNDEFINED_LSB                                      79      
#define DOT_L4_16_SUM1_SIZE                                          37       // 16-bit column 1 sum
#define DOT_L4_16_SUM1_MSB                                           78      
#define DOT_L4_16_SUM1_LSB                                           42      
#define DOT_L4_16_UNDEFINED_1_SIZE                                   5        // Undefined boolean values
#define DOT_L4_16_UNDEFINED_1_MSB                                    41      
#define DOT_L4_16_UNDEFINED_1_LSB                                    37      
#define DOT_L4_16_SUM0_SIZE                                          37       // 16-bit column 0 sum
#define DOT_L4_16_SUM0_MSB                                           36      
#define DOT_L4_16_SUM0_LSB                                           0       
// Declarations for bus DOT_L4_32
#define DOT_L4_32_SIZE                                               84      
#define DOT_L4_32_MSB                                                83      
#define DOT_L4_32_LSB                                                0       
#define DOT_L4_32_UNDEFINED_SIZE                                     13       // Undefined boolean values
#define DOT_L4_32_UNDEFINED_MSB                                      83      
#define DOT_L4_32_UNDEFINED_LSB                                      71      
#define DOT_L4_32_SUM0_SIZE                                          71       // 32-bit column 0 sum
#define DOT_L4_32_SUM0_MSB                                           70      
#define DOT_L4_32_SUM0_LSB                                           0       
// Declarations for bus DOT_L5_8
#define DOT_L5_8_SIZE                                                88      
#define DOT_L5_8_MSB                                                 87      
#define DOT_L5_8_LSB                                                 0       
#define DOT_L5_8_SUM3_SIZE                                           22       // 8-bit column 3 sum
#define DOT_L5_8_SUM3_MSB                                            87      
#define DOT_L5_8_SUM3_LSB                                            66      
#define DOT_L5_8_SUM2_SIZE                                           22       // 8-bit column 2 sum
#define DOT_L5_8_SUM2_MSB                                            65      
#define DOT_L5_8_SUM2_LSB                                            44      
#define DOT_L5_8_SUM1_SIZE                                           22       // 8-bit column 1 sum
#define DOT_L5_8_SUM1_MSB                                            43      
#define DOT_L5_8_SUM1_LSB                                            22      
#define DOT_L5_8_SUM0_SIZE                                           22       // 8-bit column 0 sum
#define DOT_L5_8_SUM0_MSB                                            21      
#define DOT_L5_8_SUM0_LSB                                            0       
// Declarations for bus DOT_L5_16
#define DOT_L5_16_SIZE                                               88      
#define DOT_L5_16_MSB                                                87      
#define DOT_L5_16_LSB                                                0       
#define DOT_L5_16_UNDEFINED_SIZE                                     6        // Undefined boolean values
#define DOT_L5_16_UNDEFINED_MSB                                      87      
#define DOT_L5_16_UNDEFINED_LSB                                      82      
#define DOT_L5_16_SUM1_SIZE                                          38       // 16-bit column 1 sum
#define DOT_L5_16_SUM1_MSB                                           81      
#define DOT_L5_16_SUM1_LSB                                           44      
#define DOT_L5_16_UNDEFINED_1_SIZE                                   6        // Undefined boolean values
#define DOT_L5_16_UNDEFINED_1_MSB                                    43      
#define DOT_L5_16_UNDEFINED_1_LSB                                    38      
#define DOT_L5_16_SUM0_SIZE                                          38       // 16-bit column 0 sum
#define DOT_L5_16_SUM0_MSB                                           37      
#define DOT_L5_16_SUM0_LSB                                           0       
// Declarations for bus DOT_L5_32
#define DOT_L5_32_SIZE                                               88      
#define DOT_L5_32_MSB                                                87      
#define DOT_L5_32_LSB                                                0       
#define DOT_L5_32_UNDEFINED_SIZE                                     16       // Undefined boolean values
#define DOT_L5_32_UNDEFINED_MSB                                      87      
#define DOT_L5_32_UNDEFINED_LSB                                      72      
#define DOT_L5_32_SUM0_SIZE                                          72       // 32-bit column 0 sum
#define DOT_L5_32_SUM0_MSB                                           71      
#define DOT_L5_32_SUM0_LSB                                           0       
// Declarations for bus DOT_L6_8
#define DOT_L6_8_SIZE                                                92      
#define DOT_L6_8_MSB                                                 91      
#define DOT_L6_8_LSB                                                 0       
#define DOT_L6_8_SUM3_SIZE                                           23       // 8-bit column 3 sum
#define DOT_L6_8_SUM3_MSB                                            91      
#define DOT_L6_8_SUM3_LSB                                            69      
#define DOT_L6_8_SUM2_SIZE                                           23       // 8-bit column 2 sum
#define DOT_L6_8_SUM2_MSB                                            68      
#define DOT_L6_8_SUM2_LSB                                            46      
#define DOT_L6_8_SUM1_SIZE                                           23       // 8-bit column 1 sum
#define DOT_L6_8_SUM1_MSB                                            45      
#define DOT_L6_8_SUM1_LSB                                            23      
#define DOT_L6_8_SUM0_SIZE                                           23       // 8-bit column 0 sum
#define DOT_L6_8_SUM0_MSB                                            22      
#define DOT_L6_8_SUM0_LSB                                            0       
// Declarations for bus DOT_L6_16
#define DOT_L6_16_SIZE                                               92      
#define DOT_L6_16_MSB                                                91      
#define DOT_L6_16_LSB                                                0       
#define DOT_L6_16_UNDEFINED_SIZE                                     7        // Undefined boolean values
#define DOT_L6_16_UNDEFINED_MSB                                      91      
#define DOT_L6_16_UNDEFINED_LSB                                      85      
#define DOT_L6_16_SUM1_SIZE                                          39       // 16-bit column 1 sum
#define DOT_L6_16_SUM1_MSB                                           84      
#define DOT_L6_16_SUM1_LSB                                           46      
#define DOT_L6_16_UNDEFINED_1_SIZE                                   7        // Undefined boolean values
#define DOT_L6_16_UNDEFINED_1_MSB                                    45      
#define DOT_L6_16_UNDEFINED_1_LSB                                    39      
#define DOT_L6_16_SUM0_SIZE                                          39       // 16-bit column 0 sum
#define DOT_L6_16_SUM0_MSB                                           38      
#define DOT_L6_16_SUM0_LSB                                           0       
// Declarations for bus DOT_L6_32
#define DOT_L6_32_SIZE                                               92      
#define DOT_L6_32_MSB                                                91      
#define DOT_L6_32_LSB                                                0       
#define DOT_L6_32_UNDEFINED_SIZE                                     19       // Undefined boolean values
#define DOT_L6_32_UNDEFINED_MSB                                      91      
#define DOT_L6_32_UNDEFINED_LSB                                      73      
#define DOT_L6_32_SUM0_SIZE                                          73       // 32-bit column 0 sum
#define DOT_L6_32_SUM0_MSB                                           72      
#define DOT_L6_32_SUM0_LSB                                           0       
// Declarations for bus:input src1
#define src1_SIZE                                                    512     
#define src1_MSB                                                     511     
#define src1_LSB                                                     0       
#define SRC1_DATA_SIZE                                               512      // Data to MMA for src1 operand
#define SRC1_DATA_MSB                                                511     
#define SRC1_DATA_LSB                                                0       
// Declarations for bus:input src1p
#define src1p_SIZE                                                   32      
#define src1p_MSB                                                    31      
#define src1p_LSB                                                    0       
#define SRC1P_PARITY_SIZE                                            32       // 16-bit granular parity on src1 operand to MMA. Unimplemented on current version.
#define SRC1P_PARITY_MSB                                             31      
#define SRC1P_PARITY_LSB                                             0       
// Declarations for bus:input src2
#define src2_SIZE                                                    512     
#define src2_MSB                                                     511     
#define src2_LSB                                                     0       
#define SRC2_DATA_SIZE                                               512      // Data to MMA for src2 operand
#define SRC2_DATA_MSB                                                511     
#define SRC2_DATA_LSB                                                0       
// Declarations for bus:input src2p
#define src2p_SIZE                                                   32      
#define src2p_MSB                                                    31      
#define src2p_LSB                                                    0       
#define SRC2P_PARITY_SIZE                                            32       // 16-bit granular parity on src2 operand to MMA
#define SRC2P_PARITY_MSB                                             31      
#define SRC2P_PARITY_LSB                                             0       
// Declarations for bus:input instr
#define instr_SIZE                                                   20      
#define instr_MSB                                                    19      
#define instr_LSB                                                    0       
#define INSTR_ARF_SA_SIZE                                            6        // ARF row address from C7 streaming address generator (in MMA1 this is a 6-bit reserved field)
#define INSTR_ARF_SA_MSB                                             19      
#define INSTR_ARF_SA_LSB                                             14      
#define INSTR_IMM_OPEN_SIZE                                          4        // 4-bit immediate value encoded in HWAOPEN
#define INSTR_IMM_OPEN_MSB                                           13      
#define INSTR_IMM_OPEN_LSB                                           10      
#define INSTR_HWALDA_SIZE                                            1        // C7x decoded a HWALDA    instruction
#define INSTR_HWALDA_MSB                                             9       
#define INSTR_HWALDA_LSB                                             9       
#define INSTR_HWALDB_SIZE                                            1        // C7x decoded a HWALDB    instruction
#define INSTR_HWALDB_MSB                                             8       
#define INSTR_HWALDB_LSB                                             8       
#define INSTR_HWALDC_SIZE                                            1        // C7x decoded a HWALDC    instruction
#define INSTR_HWALDC_MSB                                             7       
#define INSTR_HWALDC_LSB                                             7       
#define INSTR_HWALDAB_SIZE                                           1        // C7x decoded a HWALDAB   instruction
#define INSTR_HWALDAB_MSB                                            6       
#define INSTR_HWALDAB_LSB                                            6       
#define INSTR_HWALDBC_SIZE                                           1        // C7x decoded a HWALDBC   instruction
#define INSTR_HWALDBC_MSB                                            5       
#define INSTR_HWALDBC_LSB                                            5       
#define INSTR_HWAOP_SIZE                                             1        // C7x decoded a HWAOP     instruction
#define INSTR_HWAOP_MSB                                              4       
#define INSTR_HWAOP_LSB                                              4       
#define INSTR_HWAOPXFER_SIZE                                         1        // C7x decoded a HWAOPXFER instruction
#define INSTR_HWAOPXFER_MSB                                          3       
#define INSTR_HWAOPXFER_LSB                                          3       
#define INSTR_HWAXFER_SIZE                                           1        // C7x decoded a HWAXFER   instruction
#define INSTR_HWAXFER_MSB                                            2       
#define INSTR_HWAXFER_LSB                                            2       
#define INSTR_HWAOPEN_SIZE                                           1        // C7x decoded a HWAOPEN   instruction
#define INSTR_HWAOPEN_MSB                                            1       
#define INSTR_HWAOPEN_LSB                                            1       
#define INSTR_HWACLOSE_SIZE                                          1        // C7x decoded a HWACLOSE  instruction
#define INSTR_HWACLOSE_MSB                                           0       
#define INSTR_HWACLOSE_LSB                                           0       
// Declarations for bus:input hwarcv_control
#define hwarcv_control_SIZE                                          4       
#define hwarcv_control_MSB                                           3       
#define hwarcv_control_LSB                                           0       
#define HWARCV_CONTROL_RA_SIZE                                       1        // 16-bit granular parity on src2 operand
#define HWARCV_CONTROL_RA_MSB                                        3       
#define HWARCV_CONTROL_RA_LSB                                        3       
#define HWARCV_CONTROL_RE_SIZE                                       3        // 3-bit address specifying the transfer buffer entry or MMA state register value to be sent back to the C7x CPU
#define HWARCV_CONTROL_RE_MSB                                        2       
#define HWARCV_CONTROL_RE_LSB                                        0       
// Declarations for bus:output rslt
#define rslt_SIZE                                                    512     
#define rslt_MSB                                                     511     
#define rslt_LSB                                                     0       
#define RSLT_DATA_SIZE                                               512      // Data to C7x for result operand
#define RSLT_DATA_MSB                                                511     
#define RSLT_DATA_LSB                                                0       
// Declarations for bus:output rsltp
#define rsltp_SIZE                                                   32      
#define rsltp_MSB                                                    31      
#define rsltp_LSB                                                    0       
#define RSLTP_PARITY_SIZE                                            32       // 16-bit granular parity on result to MMA. Unimplemented on current version.
#define RSLTP_PARITY_MSB                                             31      
#define RSLTP_PARITY_LSB                                             0       
// Declarations for bus:output rslt_status
#define rslt_status_SIZE                                             8       
#define rslt_status_MSB                                              7       
#define rslt_status_LSB                                              0       
#define RSLT_STATUS_RSVD_SIZE                                        1        // Reserved field for future implementations that compute odd parity over the remaining fields in the rslt_status bus
#define RSLT_STATUS_RSVD_MSB                                         7       
#define RSLT_STATUS_RSVD_LSB                                         7       
#define RSLT_STATUS_RSVD_1_SIZE                                      1        // Reserved field for future implementations that signal any error condition by setting this bit
#define RSLT_STATUS_RSVD_1_MSB                                       6       
#define RSLT_STATUS_RSVD_1_LSB                                       6       
#define RSLT_STATUS_ERRORCODE_SIZE                                   6        // errorcode corresponding to the error detected by the MMA unit
#define RSLT_STATUS_ERRORCODE_MSB                                    5       
#define RSLT_STATUS_ERRORCODE_LSB                                    0       
// Declarations for bus ctl_edi_if_slave
#define ctl_edi_if_slave_SIZE                                        177     
#define ctl_edi_if_slave_MSB                                         176     
#define ctl_edi_if_slave_LSB                                         0       
#define CTL_EDI_IF_SLAVE_ADDR_SIZE                                   36       // Registered EDI address (input)
#define CTL_EDI_IF_SLAVE_ADDR_MSB                                    176     
#define CTL_EDI_IF_SLAVE_ADDR_LSB                                    141     
#define CTL_EDI_IF_SLAVE_WDATA_SIZE                                  64       // EDI write data (input)
#define CTL_EDI_IF_SLAVE_WDATA_MSB                                   140     
#define CTL_EDI_IF_SLAVE_WDATA_LSB                                   77      
#define CTL_EDI_IF_SLAVE_VALID_SIZE                                  1        // An EDI access is entering the pipe (input)
#define CTL_EDI_IF_SLAVE_VALID_MSB                                   76      
#define CTL_EDI_IF_SLAVE_VALID_LSB                                   76      
#define CTL_EDI_IF_SLAVE_RNW_SIZE                                    1        // EDI access is read or write (input)
#define CTL_EDI_IF_SLAVE_RNW_MSB                                     75      
#define CTL_EDI_IF_SLAVE_RNW_LSB                                     75      
#define CTL_EDI_IF_SLAVE_SIZE_SIZE                                   3        // EDI access size (input)
#define CTL_EDI_IF_SLAVE_SIZE_MSB                                    74      
#define CTL_EDI_IF_SLAVE_SIZE_LSB                                    72      
#define CTL_EDI_IF_SLAVE_MEM_SIZE                                    1        // EDI Access to mem space (input)
#define CTL_EDI_IF_SLAVE_MEM_MSB                                     71      
#define CTL_EDI_IF_SLAVE_MEM_LSB                                     71      
#define CTL_EDI_IF_SLAVE_TYPE_SIZE                                   4        // Specifies which register files to be accessed (input)
#define CTL_EDI_IF_SLAVE_TYPE_MSB                                    70      
#define CTL_EDI_IF_SLAVE_TYPE_LSB                                    67      
#define CTL_EDI_IF_SLAVE_RDATA_SIZE                                  64       // Read data (output)
#define CTL_EDI_IF_SLAVE_RDATA_MSB                                   66      
#define CTL_EDI_IF_SLAVE_RDATA_LSB                                   3       
#define CTL_EDI_IF_SLAVE_STATUS_SIZE                                 3        // Transactions status, goes with rdata (output)
#define CTL_EDI_IF_SLAVE_STATUS_MSB                                  2       
#define CTL_EDI_IF_SLAVE_STATUS_LSB                                  0       
#define MMA_CS_ILLEGAL                                               0        // MMA common FSM state illegal
#define MMA_CS_DELAY                                                 3        // MMA common FSM state delay
#define MMA_CS_ITERATE                                               5        // MMA common FSM state iterate
#define MMA_CS_ERROR                                                 6        // MMA common FSM state error
#define MMA_CS_HALT                                                  9        // MMA common FSM state halt
#define MMA_D_PIPELINE_STAGES                                        7        // Distribution pipeline stages.
#define MMA_C_PIPELINE_STAGES                                        11       // Computation pipeline stages
#define MMA_X_PIPELINE_STAGES                                        4        // Result transfer pipeline stages
#define MMA_R_PIPELINE_STAGES                                        2        // HWARCV pipeline stages
#define LEAF_PPW                                                     17       // Carry-save product width from leaf 8x8 adders
#define LEAF_PMW                                                     25       // Full-width pre-multiplied operand width from middle datapath
#define MMA_BBANKS                                                   2        // Number of B matrix storage banks
#define MMA_BROWS                                                    64       // Number of B matrix 8-bit rows
#define MMA_BCOLS                                                    64       // Number of B matrix 8-bit columns
#define MMA_CBANKS                                                   2        // Number of C matrix storage banks
#define MMA_CROWS                                                    64       // Number of C matrix 8-bit rows
#define MMA_CROW_BITS                                                2048     // Number of bits per C row
#define MMA_CROWS_LOG2                                               6        // Number of C matrix 8-bit rows log2
#define MMA_CCOLS                                                    64       // Number of C matrix 8-bit columns
#define MMA_X_DEPTH                                                  24       // Number of transfer buffer FIFO vector elements
#define MMA_XCOLS                                                    64       // Number of 8-bit columns in a transfer buffer data element
#define MMA_XCOLS_BIT                                                512      // Number of 8-bit columns in a transfer buffer data element
