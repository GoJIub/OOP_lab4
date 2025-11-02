cmake_minimum_required(VERSION 3.10)
project(homework3)

# === Настройки C++ ===
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# === Флаги компиляции ===
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror=maybe-uninitialized")

# === Google Test через FetchContent ===
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# === Библиотека с реализациями ===
add_library(${CMAKE_PROJECT_NAME}_lib
    src/Trapezoid.cpp
    src/Rhomb.cpp
    src/Pentagon.cpp
    src/Array.cpp
    src/Point.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# === Основная программа ===
add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib)

# === Тесты ===
enable_testing()

add_executable(tests
    test/tests.cpp
)

target_link_libraries(tests
    ${CMAKE_PROJECT_NAME}_lib
    gtest_main
    gtest
    pthread
)

target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# === Добавление тестов в ctest ===
add_test(NAME Homework2Tests COMMAND tests)