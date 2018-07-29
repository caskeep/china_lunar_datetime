cmake_minimum_required(VERSION 3.5)

if (CYGWIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
else()
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

project(china_lunar_datetime)


add_library(${PROJECT_NAME} INTERFACE)
add_library(lib::ch_lunar ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(test test/main.cpp)
target_link_libraries(test lib::ch_lunar)