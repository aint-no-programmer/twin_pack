cmake_minimum_required (VERSION 3.7)

set(TARGET_NAME ${PROJECT_NAME}_tests)

file(GLOB HEADERS_FILES *.h *.hpp)
file(GLOB SOURCES_FILES *.c *.cpp)

# Configute GTest
if (NOT GTEST_FOUND)
    find_package(GTest REQUIRED)
endif()

#threads needed for gtest in linux
if (NOT Threads_FOUND)
    find_package(Threads REQUIRED)
endif()

add_executable (${TARGET_NAME} ${HEADERS_FILES} ${SOURCES_FILES} )

target_include_directories(${TARGET_NAME} PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} PUBLIC ${PROJECT_NAME} GTest::GTest GTest::Main Threads::Threads) 
#GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main - proper targets from vcpkg

add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})

