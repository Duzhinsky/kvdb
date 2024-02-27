cmake_minimum_required(VERSION 3.22)
project(kvdb)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.74.0 REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_BOOST_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})


set(SOURCE_FILES src/main.cpp
        src/server.h
        src/server.cpp
        src/connection.cpp
        src/connection.h)
add_executable(redis ${SOURCE_FILES})

target_link_libraries(redis ${USED_BOOST_LIBS} spdlog::spdlog)