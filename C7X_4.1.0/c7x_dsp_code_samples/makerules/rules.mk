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
#

##############################################################
include $(ALGBASE_PATH)/makerules/config.mk

BUILD_FOLDER      := $(ALGBASE_PATH)\out

ifdef SystemRoot
#Windows OS
    ifndef UTILS_PATH
      $(error You must define UTILS_PATH!)
    endif
    RM_CMD = $(UTILS_PATH)\rm -rf
    MKDIR_CMD = $(UTILS_PATH)\mkdir -p $(1)
    CHANGE_PATHSEP=$(subst /,\,$(1))
    CAT_CMD = $(UTILS_PATH)\cat
    MAKE = gmake
else
    ifeq ($(shell uname), Linux)
#Linux
      RM_CMD = rm -rf
      MKDIR_CMD = mkdir -p $(1)
      CHANGE_PATHSEP=$(subst \,/,$(1))
      CAT_CMD = cat
      MAKE = make
    endif
endif

ifeq ($(SHOW_COMMANDS),1)
Q:=
else
Q:=@
endif

ALGBASE_PATH:= $(call  CHANGE_PATHSEP,$(ALGBASE_PATH))
EMPTY:=
SPACE:=$(EMPTY) $(EMPTY)
COMMA:=$(EMPTY),$(EMPTY)

_MAKEPATH := $(abspath .)
_MAKEPATH:= $(call  CHANGE_PATHSEP,$(_MAKEPATH))


ifdef SystemRoot
_MODPATH  := $(subst $(ALGBASE_PATH)\,,$(_MAKEPATH))
else
_MODPATH  := $(subst $(ALGBASE_PATH)/,,$(_MAKEPATH))
endif
_MODPATH:= $(call CHANGE_PATHSEP,$(_MODPATH))

BUILD_MODE ?=OBJ

ifeq ($(TARGET_BUILD), )
ifeq ($(TARGET_PLATFORM) , PC)
	TARGET_BUILD := debug
else
	TARGET_BUILD := release
endif
endif

CURR_BUILD_FOLDER:= $(BUILD_FOLDER)/$(TARGET_PLATFORM)/$(CORE)/$(TARGET_BUILD)
CURR_BUILD_FOLDER:= $(call  CHANGE_PATHSEP,$(CURR_BUILD_FOLDER))

##############################################################

##############################################################
ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
  #Window Host Emulation
  CC = CL
  CP = CL
  AS = $(TARGET_CPU)ASM
  AR = LIB
  LD = LINK
  ifeq ($(TARGET_BUILD), release)
    COMPILER_FLAGS += /EHsc /TP /W4 /wd4505 /D_CRT_SECURE_NO_WARNINGS /D_HOST_EMULATION /D__C7100__ /c /nologo /Ox /D_NDEBUG /MT /Gm /Zi /D_HOST_BUILD  /D_HAS_ITERATOR_DEBUGGING=0 /D_ITERATOR_DEBUG_LEVEL=0 /DMSVC_BUILD
    LDDEBUG := /DEBUG                                                                               
  else                                                                                              
    COMPILER_FLAGS += /EHsc /TP /W4 /wd4505 /D_CRT_SECURE_NO_WARNINGS /D_HOST_EMULATION /D__C7100__ /c /nologo /Od /MT /Gm /Zi /D_HAS_ITERATOR_DEBUGGING=0 /D_ITERATOR_DEBUG_LEVEL=0 /DMSVC_BUILD 
    LDDEBUG := /DEBUG 
  endif
  ARFLAGS := /nologo /MACHINE:x64 /ignore:4099
else 
  #Linux Host Emulation
  CC=g++-5 -c
  AR=gcc-ar-5
  ARFLAGS := rvs
  ifeq ($(TARGET_BUILD), debug)
    COMPILER_FLAGS += -std=c++14 -fPIC -ggdb -ggdb3 -gdwarf-2 -D_HOST_EMULATION -w -DGCC_BUILD  -D__C7100__
  else
    COMPILER_FLAGS += -std=c++14 -fPIC -O3 -D_HOST_EMULATION  -w -DGCC_BUILD  -D__C7100__
  endif
  LD=g++-5
  LDFLAGS +=
endif
else
#TI_DEVICE
  ifeq ($(CORE),dsp)
    CC = $(DSP_TOOLS)\bin\cl7x
    LD = $(DSP_TOOLS)\bin\lnk7x
    AR = $(DSP_TOOLS)\bin\ar7x
    ifeq ($(TARGET_BUILD), release)
      CFLAGS = -O3 -k --abi=eabi --rtti -mo  -DUSE_LEVEL_1_MACROS
    else
      CFLAGS = -g  -k --abi=eabi --rtti -mo -DUSE_LEVEL_1_MACROS
    endif
   ifeq ($(TARGET_CPU),C71)
      CFLAGS += --silicon_version=7100 -D=xdc_target_name=C71
   endif
    ARFLAGS = r
    LDFLAGS +=
    CFLAGS += -I $(DSP_TOOLS)/include -DCORE_DSP
  endif
  
  CFLAGS += --diag_suppress=496 --diag_suppress=1311
endif

##############################################################


##############################################################
ifeq ($(LIBDIR),)
LIBDIR =  .\lib\$(TARGET_BUILD)
endif
ifeq ($(OUTDIR),)
OUTDIR =  .\elf_out
endif

##############################################################

# In case there are no sources, it is better to not generate any lib
ifeq (,$(wildcard $(CFILES)))
OUTFILE=
endif
##############################################################
CFILES := $(call  CHANGE_PATHSEP,$(CFILES))
HFILES := $(call  CHANGE_PATHSEP,$(HFILES))

CFILESC:= $(filter %.c,$(CFILES))
CFILESCPP:= $(filter %.cpp,$(CFILES))
CFILESCC:= $(filter %.cc,$(CFILES))
CFILESASM:= $(filter %.asm,$(CFILES))
CFILES:=  $(CFILESC) $(CFILESASM) $(CFILESCPP) $(CFILESCC)

OFILES:= $(CFILESC:%.c=%.obj)
OFILES+= $(CFILESCPP:%.cpp=%.obj)
OFILES+= $(CFILESCC:%.cc=%.obj)

ifneq ($(TARGET_PLATFORM) , PC)
OFILES+= $(CFILESASM:%.asm=%.obj)
endif

DEPILES:= $(CFILESC:%.c=%.dep)
DEPILES+= $(CFILESCPP:%.cpp=%.dep)
DEPILES+= $(CFILESCC:%.cc=%.dep)
DEPILES+= $(CFILESCC:%.cu=%.dep)

BUILDDIR := $(CURR_BUILD_FOLDER)/$(_MODPATH)/
BUILDDIR := $(call  CHANGE_PATHSEP,$(BUILDDIR))

OFILES:= $(addprefix  $(BUILDDIR), $(OFILES))
DEPILES:= $(addprefix $(BUILDDIR), $(DEPILES))

OFILES := $(call  CHANGE_PATHSEP,$(OFILES))
FIRST_OFILES := $(word 1,$(OFILES))
RESTOF_OFILES := $(filter-out $(FIRST_OFILES), $(OFILES))

BUILDDIR := $(call  CHANGE_PATHSEP,$(BUILDDIR))
OUTFILE := $(call  CHANGE_PATHSEP,$(OUTFILE))
OBJDIRS := $(foreach file, $(OFILES), $(dir $(file)))
OBJDIRS += $(foreach file, $(OUTFILE), $(dir $(file)))
OBJDIRS += $(BUILDDIR)
OBJDIRS := $(sort $(OBJDIRS))
OBJDIRS := $(addsuffix .gitignore, $(OBJDIRS))

##############################################################
CC := $(call  CHANGE_PATHSEP,$(CC))
LD := $(call  CHANGE_PATHSEP,$(LD))
AR := $(call  CHANGE_PATHSEP,$(AR))

CFLAGS := $(call  CHANGE_PATHSEP,$(CFLAGS))
OUTFILE := $(call  CHANGE_PATHSEP,$(OUTFILE))
LIBDIR := $(call  CHANGE_PATHSEP,$(LIBDIR))
OUTDIR := $(call  CHANGE_PATHSEP,$(OUTDIR))

OBJDIRS := $(call  CHANGE_PATHSEP,$(OBJDIRS))

CFLAGS+= -I $(DSP_TOOLS)/host_emulation/include
CFLAGS := $(COMPILER_FLAGS) $(CFLAGS)
##############################################################
# 'all' rules
all : dir $(OUTFILE)

# Define a ".gitignore" file which will help in making sure the module's output
# folder always exists.
%gitignore:
#	@echo creating $@
	$(Q) $(MKDIR_CMD) $(dir $@)
	$(Q)echo .> $@
dir: $(OBJDIRS)

$(OUTFILE): $(OFILES)

ifdef SystemRoot
$(BUILDDIR)\%.obj: .\%.c
else
$(BUILDDIR)%.obj: %.c
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS) $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif

ifdef SystemRoot
$(BUILDDIR)\%.obj: ./%.cpp
else
$(BUILDDIR)%.obj: %.cpp
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS) $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif

ifdef SystemRoot
$(BUILDDIR)\%.obj: ./%.cc
else
$(BUILDDIR)%.obj: %.cc
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS) $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif


ifneq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
$(BUILDDIR)\%.obj : ./%.asm
else
$(BUILDDIR)%.obj : %.asm
endif
	$(Q)$(CC) $(CFLAGS) -c $^ --output_file=$@
endif
##############################################################

ifneq ($(TARGET_PLATFORM) , PC)
LDFLAGS+= -cr -x
LDFLAGS+= -l $(CGT7X_ROOT)/lib/rts7100_le.lib
LDFLAGS+= -l "./lnk.cmd"

else
ifdef SystemRoot
ifeq ($(TARGET_BUILD), debug)
LDFLAGS+= /NODEFAULTLIB:msvcrtd.lib
else
LDFLAGS+= /NODEFAULTLIB:msvcrt.lib
endif
endif
endif

ifeq ($(TARGET_PLATFORM) , PC)
  #HOST BUILD SETUP
  ifdef SystemRoot
    LDFLAGS+= -l $(CGT7X_ROOT)/host_emulation/c70-host-emulation.lib
  else
    # g++ options
    LDFLAGS+= -L $(CGT7X_ROOT)/host_emulation
    LDFLAGS+= -lc70-host-emulation
  endif
endif
##############################################################

print :
	echo $(LDFLAGS)
	echo $(OFILES)
	echo $(OUTFILE)
	echo $(CFILES)
	echo $(HFILES)
	echo @$(AR) $(ARFLAGS) $(OUTFILE) $(OFILES) $(ARFILES)
##############################################################

# clean rules
.IGNORE: clean
clean:
ifdef SystemRoot
	@echo echo OFF > temp_pps.bat
	@FOR %%i IN ($(OFILES) ) DO echo del %%i >> temp_pps.bat
ifneq ($(TARGET_PLATFORM) , PC)
	@FOR %%i IN ( $(DEPILES)) DO echo del %%i >> temp_pps.bat
endif
	@echo echo ON >> temp_pps.bat
	@temp_pps.bat
	@-del temp_pps.bat
else
	$(Q)$(RM_CMD) $(OFILES) 
endif	
ifneq ($(BUILD_MODE),OBJ)
	$(Q)$(RM_CMD) $(LIBDIR)
endif
	$(Q)$(RM_CMD) $(OUTDIR)
##############################################################


##############################################################
.PHONY: libfile
libfile: $(LIBDIR) $(OFILES) $(ARFILES)
ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
  #Window Host Emulation
	$(Q)echo Linking $(OUTFILE)
	$(Q)echo $(ARFLAGS) /OUT:$(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
else
	$(Q)$(AR) $(ARFLAGS) $(OUTFILE) $(OFILES) $(ARFILES)
endif
else
	$(Q)$(RM_CMD) $(OUTFILE)
ifdef SystemRoot
	$(Q)echo $(ARFLAGS) $(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)$(RM_CMD) ar_cmd.txt
else	
	@$(AR) $(ARFLAGS) $(OUTFILE) $(OFILES) $(ARFILES)
endif	
endif 
$(LIBDIR):
	$(Q) $(MKDIR_CMD) $(LIBDIR) || cd $(LIBDIR)

##############################################################
.PHONY: pllibfile
pllibfile: $(LIBDIR) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo Linking $(OUTFILE)
ifdef SystemRoot
  #Window Host Emulation
	$(Q)echo $(ARFLAGS) /OUT:$(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
else
	$(Q)$(AR) $(ARFLAGS) $(OUTFILE) $(OFILES) $(ARFILES)
endif
else
ifdef SystemRoot
	$(Q)echo $(ARFLAGS) temp_pl.lib > ar_cmd.txt
	$(Q)FOR %%i IN ($(RESTOF_OFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
	$(Q)if exist $(OUTFILE) del $(OUTFILE)
	$(Q)$(LD) -r $(LDFLAGS) --output_file="plink.out"  $(FIRST_OFILES) $(LDFILES) -m "plink.map" -l temp_pl.lib
	$(Q)echo $(ARFLAGS) $(OUTFILE) > ar_cmd.txt
	$(Q)echo plink.out >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del temp_pl.lib
	$(Q)-del ar_cmd.txt
	$(Q)-del plink.map
	$(Q)-del plink.out
else	
	$(Q)$(LD) -r --output_file="plink.out"  $(FIRST_OFILES) $(RESTOF_OFILES) -m "plink.map"
	$(Q)$(AR) $(ARFLAGS) $(OUTFILE) plink.out
endif	
endif

##############################################################
PC_LDFLAGS1 = $(filter-out %rtsarp32_v200.lib,$(LDFLAGS))
PC_LDFLAGS = $(filter-out %rtsarp32_v200.lib",$(PC_LDFLAGS1))
ALL_LIBS1 = $(filter %.lib,$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.lib",$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.lib"",$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.a86",$(PC_LDFLAGS))

ALL_LIBS  = $(subst .lib,.lib,$(ALL_LIBS1))

##############################################################
.PHONY: outfile
outfile: $(OUTDIR) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
	$(Q)$(RM_CMD) $(OUTFILE).exe
	$(Q)$(LD) $(ALL_LIBS) $(LDDEBUG) $(ARFLAGS) /OUT:$(OUTFILE).exe $(OFILES) $(LDFILES)
else
	$(Q)$(RM_CMD) $(OUTFILE).out
	$(Q)$(LD) -o $(OUTFILE).out $(OFILES) $(LDFILES) $(LDFLAGS) 
endif
else
	$(Q)$(RM_CMD) $(OUTFILE)
	$(Q)$(LD) $(LDFLAGS) --output_file=$(OUTFILE).out $(OFILES) $(LDFILES) -m "$(OUTFILE)".map
endif
$(OUTDIR):
	$(Q)$(MKDIR_CMD) $(OUTDIR) || cd $(OUTDIR)

##############################################################
