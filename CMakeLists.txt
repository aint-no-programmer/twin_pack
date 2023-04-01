cmake_minimum_required(VERSION 3.7)
project(twin_pack)

if(CMAKE_VERSION VERSION_GREATER 3.12)
    cmake_policy(SET CMP0074 NEW)
endif()

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(TWIN_PACK_MASTER_PROJECT ON)
    message(STATUS "Build standalone ${PROJECT_NAME}")
endif ()

#-------------------------------------------------------------------------------------------------------------------------------------------
# Поиск внешних пакетов

find_package(Boost REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(msgpack CONFIG REQUIRED)

#-------------------------------------------------------------------------------------------------------------------------------------------
# Сборка библиотеки

set(TWIN_PACK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
file (GLOB HEADERS_FILES ${TWIN_PACK_INCLUDE_DIR}/*.h ${TWIN_PACK_INCLUDE_DIR}/*.hpp*)

add_library (${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${HEADERS_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE ${TWIN_PACK_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE msgpackc-cxx nlohmann_json::nlohmann_json Boost::headers)
#-------------------------------------------------------------------------------------------------------------------------------------------
# Сборка тестов и примеров

if(TWIN_PACK_MASTER_PROJECT)
    if(MSVC AND BUILD_SHARED_LIBS)
        message("Caution: No <copy> COMMAND for shared libraries like a gtest.dll for <tests> or <examples> ")
    endif()

    enable_testing()

    add_subdirectory(examples)
    add_subdirectory(tests)
endif()