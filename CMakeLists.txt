cmake_minimum_required(VERSION 2.8.9)
project(MFCC_CMake_Test)
set(CMAKE_BUILD_TYPE Debug)
set(HOME_DIR /home/artik)
set(PORT_AUDIO_DIR ${HOME_DIR}/portaudio)
set(GLOBAL_LIB /usr/local/lib)
set(LIB_LINK_LIBS libportaudio.so)
link_directories(${GLOBAL_LIB})

#Bring the headers
include_directories(include)
include_directories(${PORT_AUDIO_DIR}/include)

#source file
file(GLOB SOURCES_C "src/*.c")
file(GLOB SOURCES_CPP "src/*.cpp")
message(${SOURCES_C})

#Generate the shared library from the sources
add_library(voiceDetection SHARED ${SOURCES_C} ${SOURCES_CPP})

install(TARGETS voiceDetection DESTINATION /usr/lib)
target_link_libraries(voiceDetection ${LIB_LINK_LIBS})

project(MFCC_CMake_Exe)
set(CMAKE_BUILD_TYPE Debug)
set(HOME_DIR /home/artik)
set(PORT_AUDIO_DIR ${HOME_DIR}/portaudio)
set(PROJECT_LINK_LIBS libvoiceDetection.so)
link_directories(${HOME_DIR}/MFCC_CMAKE/build)

include_directories(${HOME_DIR}/MFCC_CMAKE/include)
add_definitions(-DUNIX)

add_executable(voiceDetect main.c)
target_link_libraries(voiceDetect ${PROJECT_LINK_LIBS})





