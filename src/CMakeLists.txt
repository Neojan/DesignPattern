cmake_minimum_required(VERSION 3.1)

project(testDP)

set(CMAKE_PATH $ENV{cmake_path})

include(${CMAKE_PATH}/toolchain.cmake)

include_directories( ./include)

aux_source_directory( ./src SRC_LIST)
link_directories( ${LIB_PATH})

add_executable( testDP ${SRC_LIST})

if (${OS} STREQUAL ANDROID )
    message(WARNING "LINK ANDROID")
    target_link_libraries( testDP dl c++ m)
else()
    message(WARNING "LINK GNU")
    TARGET_LINK_LIBRARIES( testDP stdc++ pthread)
endif()

install( TARGETS testDP RUNTIME DESTINATION ${INSTALL_PATH}/ )