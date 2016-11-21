cmake_minimum_required(VERSION 3.2)

SET(PROJECT_NAME RTOSFromScratch)
SET(ARM_TOOLCHAIN_BIN_PATH /usr/bin)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_C_COMPILER ${ARM_TOOLCHAIN_BIN_PATH}/arm-none-eabi-gcc CACHE STRING "CC" FORCE)
SET(CMAKE_CXX_COMPILER ${ARM_TOOLCHAIN_BIN_PATH}/arm-none-eabi-g++ CACHE STRING "CXX" FORCE)
SET(CMAKE_FIND_ROOT_PATH /usr/arm-none-eabi)
SET(PROJ_PATH CACHE PATH ${CMAKE_SOURCE_DIR})

#TODO: ?
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# check `tm4c123gh6pm.lds` existance
if( NOT EXISTS ${CMAKE_SOURCE_DIR}/tm4c123gh6pm.lds)
	MESSAGE(FATAL_ERROR "Can't find `tm4c123gh6pm.lds` linker file.")
endif(NOT EXISTS ${CMAKE_SOURCE_DIR}/tm4c123gh6pm.lds)

# check `startup.c` existance
# if( NOT EXISTS ${CMAKE_SOURCE_DIR}/startup.c )
# 	MESSAGE(FATAL_ERROR "Can't find `startup.c` file.")
# endif( NOT EXISTS ${CMAKE_SOURCE_DIR}/startup.c )

# My Src files
FILE(GLOB MyCSources ${CMAKE_SOURCE_DIR}/*.c ${PROJ_PATH}/*.c)
FILE(GLOB MyCppSources ${CMAKE_SOURCE_DIR}/*.cpp ${PROJ_PATH}/*.cpp)
FILE(GLOB MyASMSources ${CMAKE_SOURCE_DIR}/*.s ${PROJ_PATH}/*.s)
SET( SOURCES ${MyCSources} ${MyCppSources} ${MyASMSources} )

# cahce force -> used to force show in cmake-gui
# TODO: need to handle -MF -MT
set(FLAGS "-mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall")
set(CMAKE_C_FLAGS "${FLAGS} -MD -std=c99 -MMD -MP" CACHE STRING "C flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Map,'${PROJECT_NAME}.map' -Wl,-T'${CMAKE_SOURCE_DIR}/tm4c123gh6pm.lds' --specs=nosys.specs -Wl,--start-group -l'gcc' -l'nosys' -l'c' -Wl,--end-group" CACHE STRING "Linker flags" FORCE)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}.elf ${SOURCES})

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${ARM_TOOLCHAIN_BIN_PATH}/arm-none-eabi-objcopy ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)

# add option for Make
# add_custom_target(echo echo helloworld)

# add ON/OFF option in cmake-gui
# option(Sara "This is sara" ON)

# add the binary tree to the search path for include files
# include_directories(${PROJECT_BINARY_DIR})
# include_directories(${PROJECT_SOURCE_DIR})

# install (TARGETS MathFunctions DESTINATION bin)
# install (FILES MathFunctions.h DESTINATION include)
install (TARGETS ${PROJECT_NAME}.elf DESTINATION bin)