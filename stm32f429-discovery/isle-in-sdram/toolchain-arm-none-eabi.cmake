# toolchain-arm-none-eabi.cmake

# System and processor
set(CMAKE_SYSTEM_NAME        Generic)
set(CMAKE_SYSTEM_PROCESSOR   arm)

# Toolchain prefix
set(TOOLCHAIN_PREFIX arm-none-eabi-)

# Compilers
set(CMAKE_C_COMPILER         ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER       ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER       ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_OBJCOPY            ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE               ${TOOLCHAIN_PREFIX}size)

# Linker script
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/stm32f429-discovery/isle-in-sdram/stm32f429_sdram.ld")

# Flags as space-separated strings (NOT semicolon-separated lists)
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

set(COMMON_FLAGS
    "${MCU_FLAGS} \
     -ffunction-sections \
     -fdata-sections \
     -fno-exceptions \
     -fno-unwind-tables \
     -g3 \
     -D__BAREMETAL__ \
     -DSTM32F429ZITx \
     -I${CMAKE_SOURCE_DIR}/stm32f429-discovery/isle-in-sdram/ \
     -I${CMAKE_SOURCE_DIR}/stm32f429-discovery/isle-in-sdram/system \
     -I${CMAKE_SOURCE_DIR}/stm32f429-discovery/bootloader-in-flash/libraries/CMSIS/Device/ST/STM32F4xx/Include \
     -I${CMAKE_SOURCE_DIR}/stm32f429-discovery/bootloader-in-flash/libraries/CMSIS/Include"
)

# Compiler flags
set(CMAKE_C_FLAGS_INIT       "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT     "${COMMON_FLAGS}")
set(CMAKE_ASM_FLAGS_INIT     "${MCU_FLAGS} -x assembler-with-cpp")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS_INIT
    "${MCU_FLAGS} -T${LINKER_SCRIPT} -Wl,--gc-sections -Wl,-Map=${CMAKE_PROJECT_NAME}.map"
)

# Disable standard libraries
set(CMAKE_C_STANDARD_LIBRARIES   "")
set(CMAKE_CXX_STANDARD_LIBRARIES "")

# Force static library for try_compile
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

