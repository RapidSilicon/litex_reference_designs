cmake_minimum_required(VERSION 3.15)


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

if (${CMAKE_VERSION} VERSION_GREATER "3.8")
    #For cmake >= 3.9 INTERPROCEDURAL_OPTIMIZATION behaviour we need to explicitly
    #set the cmake policy version number
    cmake_policy(VERSION 3.9) 

    # If we are using verison < 3.9 then setting INTERPROCEDURAL_OPTIMIZATION
    # has no effect unless an Intel compiler is used
endif()

if(NOT CMAKE_BUILD_TYPE)
    message(WARNING "Build type not set, falling back to Release mode.
        To specify build type use:
        -DCMAKE_BUILD_TYPE=<mode> where <mode> is Debug or Release.")
    set(CMAKE_BUILD_TYPE
        "Release"
        CACHE STRING "Choose the type of build, options are: Debug Release."
        FORCE)
endif(NOT CMAKE_BUILD_TYPE)


project(litex_rs)

message(STATUS "Install happening here ")

set(Raptor_root /home/users/bilal.ahmed/litex_instll/litex_rs/litex_rs/)

message(STATUS "Python install happening")

find_package(Python COMPONENTS Interpreter REQUIRED)

message(${PROJECT_SOURCE_DIR})

execute_process(COMMAND cp -R ${PROJECT_SOURCE_DIR}/Example_designs /usr/local/share/Raptor)

message(STATUS "Copy files to /usr/local/share/Raptor")

execute_process(COMMAND python3 /home/users/bilal.ahmed/rs_plugin/litex_rs/litex_rs_setup.py --dev --install --config=minimal)

