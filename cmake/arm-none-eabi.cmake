set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# On Windows, CMake may pick up xpm wrapper scripts instead of the real .exe.
# Prefer the .exe suffix explicitly to avoid that.
if(WIN32)
    set(CMAKE_C_COMPILER   arm-none-eabi-gcc.exe)
    set(CMAKE_CXX_COMPILER arm-none-eabi-g++.exe)
else()
    set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
endif()
set(CMAKE_C_COMPILER_ID   GNU)
set(CMAKE_CXX_COMPILER_ID GNU)
set(CMAKE_C_COMPILER_FORCED   TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_NM      arm-none-eabi-nm)
set(CMAKE_SIZE    arm-none-eabi-size)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
