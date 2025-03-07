#
# Copyright (c) {2015 - 2019} Texas Instruments Incorporated
#
# All rights reserved not granted herein.
#
# Limited License.
#
# Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
# license under copyrights and patents it now or hereafter owns or controls to make,
# have made, use, import, offer to sell and sell ("Utilize") this software subject to the
# terms herein.  With respect to the foregoing patent license, such license is granted
# solely to the extent that any such patent is necessary to Utilize the software alone.
# The patent license shall not apply to any combinations which include this software,
# other than combinations with devices manufactured by or for TI ("TI Devices").
# No hardware patent is licensed hereunder.
#
# Redistributions must preserve existing copyright notices and reproduce this license
# (including the above copyright notice and the disclaimer and (if applicable) source
# code license limitations below) in the documentation and/or other materials provided
# with the distribution
#
# Redistribution and use in binary form, without modification, are permitted provided
# that the following conditions are met:
#
# *       No reverse engineering, decompilation, or disassembly of this software is
# permitted with respect to any software provided in binary form.
#
# *       any redistribution and use are licensed by TI for use only with TI Devices.
#
# *       Nothing shall obligate TI to provide you with source code for the software
# licensed and provided to you in object code.
#
# If software source code is provided to you, modification and redistribution of the
# source code are permitted provided that the following conditions are met:
#
# *       any redistribution and use of the source code, including any resulting derivative
# works, are licensed by TI for use only with TI Devices.
#
# *       any redistribution and use of any object code compiled from the source code
# and any resulting derivative works, are licensed by TI for use only with TI Devices.
#
# Neither the name of Texas Instruments Incorporated nor the names of its suppliers
#
# may be used to endorse or promote products derived from this software without
# specific prior written permission.
#
# DISCLAIMER.
#
# THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#

echo $1
if [ "$1" == "C71" ]
then
 TOOL=loki7x
else
 TOOL=
fi
echo Executing with $TOOL

C7X_KERNEL=c7x_cellSum_4x4
cd $C7X_KERNEL
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_conv_5x5
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode... 
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode... 
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_erosion_3x3
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode... 
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode... 
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_fast9Corners
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode... 
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode... 
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_fft1d_16bit
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode... 
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode... 
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_harris_score_3x3
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode... 
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode... 
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_hough_lines
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_integral_image
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_kalman_4x8_correct
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_kalman_4x8_predict
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_matInv3x3
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_maxPooling_3x3_skip2
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_median_5x5
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_mergeSort
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_nms_7x7
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_NV12ToRGB
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_sobelX_3x3
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..

C7X_KERNEL=c7x_xyGradMagBin
cd $C7X_KERNEL
echo Building $C7x_KERNEL debug mode... 
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
make TARGET_BUILD=debug  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL debug mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=debug TARGET_PLATFORM=$1
echo Building $C7x_KERNEL release mode... 
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
make TARGET_BUILD=release  TARGET_PLATFORM=$1
echo Running $C7x_KERNEL release mode...
$TOOL ./out/$C7X_KERNEL.out
make clean TARGET_BUILD=release TARGET_PLATFORM=$1
cd ..
