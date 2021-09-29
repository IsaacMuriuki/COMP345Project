cmake_minimum_required(VERSION 3.10)

project(COMP_345_Project)

include(ExternalProject)

# Set install directory
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist CACHE PATH ${CMAKE_SOURCE_DIR}/dist FORCE)
if(WIN32)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug;Release" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# COMP_345_Project
set(EXEC COMP_345_Project)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE INSTALL include/*.h)
include_directories(${INSTALL})
add_executable(${EXEC} ${SRC})

#target_sources(${EXEC} PRIVATE ${SRC})
target_include_directories(${EXEC} PUBLIC include)

list(APPEND BIN ${EXEC})
# end COMP_345_Project

# install files to install location
install(TARGETS ${BIN} DESTINATION ${CMAKE_INSTALL_PREFIX})