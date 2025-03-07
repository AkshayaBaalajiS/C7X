REM
REM Copyright (c) {2015 - 2019} Texas Instruments Incorporated
REM
REM All rights reserved not granted herein.
REM
REM Limited License.
REM
REM Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
REM license under copyrights and patents it now or hereafter owns or controls to make,
REM have made, use, import, offer to sell and sell ("Utilize") this software subject to the
REM terms herein.  With respect to the foregoing patent license, such license is granted
REM solely to the extent that any such patent is necessary to Utilize the software alone.
REM The patent license shall not apply to any combinations which include this software,
REM other than combinations with devices manufactured by or for TI ("TI Devices").
REM No hardware patent is licensed hereunder.
REM
REM Redistributions must preserve existing copyright notices and reproduce this license
REM (including the above copyright notice and the disclaimer and (if applicable) source
REM code license limitations below) in the documentation and/or other materials provided
REM with the distribution
REM
REM Redistribution and use in binary form, without modification, are permitted provided
REM that the following conditions are met:
REM
REM *       No reverse engineering, decompilation, or disassembly of this software is
REM permitted with respect to any software provided in binary form.
REM
REM *       any redistribution and use are licensed by TI for use only with TI Devices.
REM
REM *       Nothing shall obligate TI to provide you with source code for the software
REM licensed and provided to you in object code.
REM
REM If software source code is provided to you, modification and redistribution of the
REM source code are permitted provided that the following conditions are met:
REM
REM *       any redistribution and use of the source code, including any resulting derivative
REM works, are licensed by TI for use only with TI Devices.
REM
REM *       any redistribution and use of any object code compiled from the source code
REM and any resulting derivative works, are licensed by TI for use only with TI Devices.
REM
REM Neither the name of Texas Instruments Incorporated nor the names of its suppliers
REM
REM may be used to endorse or promote products derived from this software without
REM specific prior written permission.
REM
REM DISCLAIMER.
REM
REM THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
REM OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
REM OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
REM IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
REM INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
REM BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
REM DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
REM OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
REM OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
REM OF THE POSSIBILITY OF SUCH DAMAGE.
REM

cd c7x_code_sample1
gmake TARGET_BUILD=debug clean
gmake TARGET_BUILD=debug
out\add_arrays.exe
gmake clean
gmake
out\add_arrays.exe
cd ..

cd c7x_code_sample2
gmake TARGET_BUILD=debug clean
gmake TARGET_BUILD=debug
out\fir_1d.exe
gmake clean
gmake
out\fir_1d.exe
cd ..

cd c7x_code_sample3
gmake TARGET_BUILD=debug clean
gmake TARGET_BUILD=debug
out\fir_1d_se.exe
gmake clean
gmake
out\fir_1d_se.exe
cd ..

cd c7x_code_sample4
gmake TARGET_BUILD=debug clean
gmake TARGET_BUILD=debug
out\fir_1d_se_sa.exe
gmake clean
gmake
out\fir_1d_se_sa.exe
cd ..

cd c7x_code_sample5
gmake TARGET_BUILD=debug clean
gmake TARGET_BUILD=debug
out\fir_1d_vfir.exe
gmake clean
gmake
out\fir_1d_vfir.exe
cd ..
