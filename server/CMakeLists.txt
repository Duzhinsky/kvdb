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


set(SOURCE_FILES src/main.cpp)
add_executable(redis ${SOURCE_FILES})
target_link_libraries(redis PUBLIC spdlog::spdlog)