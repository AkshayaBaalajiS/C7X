# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(C7X_Add2Array_Project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# Include directory for the C++ compiler
include_directories(/home/akshayabaalaji-s/C7X/TI_C7X_DSP_TRAINING/ti-cgt-c7000_4.1.0.LTS/host_emulation/include/C7100)
include_directories(/home/akshayabaalaji-s/C7X/C7X_COPY/AA_TI_C7X_DSP_TRAINING_00.05/cgt-c7x_1.2/host_emulation/include)
include_directories(/home/akshayabaalaji-s/C7X/TI_C7X_DSP_TRAINING/c7x_dsp_code_samples_adv/c7x_common)
# Check if the FILE variable is set
if(NOT DEFINED FILE)
  message(FATAL_ERROR "No source file provided. Please pass -D FILE=<source_file.cpp>")
endif()

# Add executable and link the source file dynamically
add_executable(app ${FILE})

# Link library for the executable
# target_link_libraries(app /home/akshayabaalaji-s/C7X/TI_C7X_DSP_TRAINING/ti-cgt-c7000_4.1.0.LTS/host_emulation/libC7100-host-emulation.a)
# target_link_libraries(app /home/akshayabaalaji-s/C7X/C7X_COPY/AA_TI_C7X_DSP_TRAINING_00.05/cgt-c7x_1.2/host_emulation/libc70-host-emulation.a)
target_link_libraries(app 
    /home/akshayabaalaji-s/C7X/C7X_COPY/AA_TI_C7X_DSP_TRAINING_00.05/cgt-c7x_1.2/host_emulation/libc70-host-emulation.a
    /home/akshayabaalaji-s/C7X/TI_C7X_DSP_TRAINING/ti-cgt-c7000_4.1.0.LTS/host_emulation/libC7100-host-emulation.a
)

# Usage instruction:
# Run cmake with -D argument to pass a source file
# Example: cmake -D FILE=add2Array.cpp .


#cmake -D FILE=filename.cpp
#for SA, SE please include "c7x_host_emulation.h"


