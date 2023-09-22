cmake_minimum_required(VERSION 3.7)
project(twin_pack)

if(CMAKE_VERSION VERSION_GREATER 3.12)
    cmake_policy(SET CMP0074 NEW)
endif()

if(CMAKE_TOOLCHAIN_FILE)
    find_package(Boost REQUIRED)
else()
    find_package(Boost CONFIG REQUIRED)
endif()

find_package(nlohmann_json CONFIG REQUIRED)
find_package(msgpack-cxx CONFIG REQUIRED)

set(TWIN_PACK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
file (GLOB HEADERS_FILES ${TWIN_PACK_INCLUDE_DIR}/*.h ${TWIN_PACK_INCLUDE_DIR}/*.hpp*)

add_library (${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${HEADERS_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE ${TWIN_PACK_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} INTERFACE msgpack-cxx nlohmann_json::nlohmann_json Boost::headers)

enable_testing()

add_subdirectory(examples)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()