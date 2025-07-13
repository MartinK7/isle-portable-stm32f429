# toolchain-arm-none-eabi.cmake

# Target system is not a full OS
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Specify the cross-compiler
set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

# Define the path to the linker script
# You can override this in your main CMakeLists.txt with -T path/to/your.ld
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/baremetal/stm32f429_ram.ld)

# CPU and FPU settings for STM32F429 (Cortex-M4F)
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# Common flags
set(COMMON_FLAGS "${MCU_FLAGS} -ffunction-sections -fdata-sections -fno-exceptions -fno-unwind-tables -g3 -D__BAREMETAL__ -I${CMAKE_SOURCE_DIR}/baremetal -DSTM32F429ZITx -I${CMAKE_SOURCE_DIR}/baremetal/stm32f429-discovery/libraries/CMSIS/Device/ST/STM32F4xx/Include -I${CMAKE_SOURCE_DIR}/baremetal/stm32f429-discovery/libraries/CMSIS/Include")

set(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS}")
set(CMAKE_ASM_FLAGS_INIT "${MCU_FLAGS} -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${MCU_FLAGS} -T${LINKER_SCRIPT} -Wl,--gc-sections -Wl,-Map=${CMAKE_PROJECT_NAME}.map")

# Disable standard library if needed (bare-metal)
set(CMAKE_C_STANDARD_LIBRARIES "")
set(CMAKE_CXX_STANDARD_LIBRARIES "")

# Set output format
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

