cmake_minimum_required(VERSION 3.5)

if (CYGWIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
else()
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()


project(china_lunar_datetime)

add_subdirectory(third_party)
#add_subdirectory(src)
add_subdirectory(test)

add_library(${PROJECT_NAME}
        src/ch_lunar.cpp)

add_library(lib::ch_lunar
        ALIAS
        ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include)