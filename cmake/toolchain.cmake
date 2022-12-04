set(TOOLCHAIN_PREFIX $ENV{cross_toolchain})
set(PLATFORM $ENV{platform})
set(BUILD_MODE $ENV{build_mode})
set(INSTALL_PATH $ENV{install_path}/${PLATFORM})
set(RELY_PATH $ENV{rely_path}/${PLATFORM})
set(LIB_PATH $ENV{root_path}/libs/${PLATFORM})
set(VERSION_MAJOR $ENV{version_major})
set(VERSION_MINOR $ENV{version_minor})
set(VERSION_PATCH $ENV{version_patch})
set(EXTENSIONS $ENV{externsion})

set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(EXTRA_CFLAGS "")

set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})  #version x.y.z

# specify the cross compiler
# the name of the target operating system
#set(CMAKE_SYSTEM_NAME Generic)

if (PLATFORM STREQUAL x86)
    set(ARCH x86)
    set(OS   LINUX)
else()
    set(ARCH x86)
    set(OS   LINUX)
endif()

# GNU/linux:cross compile,ANDROID/linux:NDK
if (EXTENSIONS STREQUAL GNU)
    set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}gcc)
    set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
elseif (EXTENSIONS STREQUAL ANDROID)
else()
endif()

#ADD_DEFINITIONS(-D${ARCH} -D${OS}_OS)

# adjust the default behaviour of hte FIND_XXX() NEVER)
set(CMAKE_FIND_ROOT_PATH_MODULE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_INCLUDE ONLY)

set( FLAGS "")
# 规则选项
set( FLAGS "${FLAGS} -Wall -Wundef -fsigned-char") 
set( FLAGS "${FLAGS} -fPIC")
set( FLAGS "${FLAGS} -g")
set( CXX_FLAGS "-std=c++11")

# 建议选项
#set( FLAGS "${FLAGS} -Werror")
#set( FLAGS "${FLAGS} -fdata-sections -ffunction-sections")
set( FLAGS "${FLAGS} -pipe")
set( FLAGS "${FLAGS} -D_REENTRANT")
# set( FLAGS "${FLAGS} -Wno-strict-aliasing")
# set( FLAGS "${FLAGS} -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64")

set( FLAGS_DEBUG   "-O0" )
set( FLAGS_RELEASE "-O0" )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} $ENV{CFLAGS} ${FLAGS} ${EXTRA_CFLAGS}" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{CXXFLAGS} ${FLAGS} ${EXTRA_CFLAGS} ${CXX_FLAGS}")

set( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CMAKE_C_FLAGS} ${FLAGS_DEBUG}" )
set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${CMAKE_C_FLAGS} ${FLAGS_RELEASE}" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS} ${FLAGS_DEBUG}" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS} ${FLAGS_RELEASE}" )

if (BUILD_MODE  STREQUAL debug )
    set(CMAKE_BUILD_TYPE "Debug")
else()
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_STRIP ${TOOLCHAIN_PREFIX}strip)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)

function(ADD_LIBRARY name)
    add_library( ${name}_${ARGV1} ${ARGN} )
    set_target_properties (${name}_${ARGV1} PROPERTIES OUTPUT_NAME ${name})
    set_target_properties (${name}_${ARGV1} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    # SET_TARGET_PROPERTIES (${name}_${ARGV1} PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_MAJOR} )
    install( TARGETS ${name}_${ARGV1}
        ARCHIVE DESTINATION ${INSTALL_PATH}/libs
        LIBRARY DESTINATION ${INSTALL_PATH}/libs)

    if (BUILD_MODE  STREQUAL release )
        if (${ARGV1} STREQUAL SHARED )
            add_custom_command(TARGET ${name}_${ARGV1}
                POST_BUILD
                command cp lib${name}.so lib${name}.so.debug
                command ${CMAKE_STRIP} lib${name}.so
                )
            install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/lib${name}.so.debug DESTINATION ${install_path}/res/debugLib
                )
        endif()
    endif()

endfunction(ADD_LIBRARY name)


