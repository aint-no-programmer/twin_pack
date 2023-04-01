cmake_minimum_required (VERSION 3.7)

set(TARGET_NAME ${PROJECT_NAME}_examples)

file(GLOB HEADERS_FILES *.h *.hpp)
file(GLOB SOURCES_FILES *.c *.cpp)

add_executable(${TARGET_NAME} ${HEADERS_FILES} ${SOURCES_FILES})

target_link_libraries(${TARGET_NAME} ${PROJECT_NAME})