cmake_minimum_required(VERSION 3.14)
project(cleancoder)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Download and configure GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add coverage compilation option
add_compile_options(--coverage)

# Add executable target
add_executable(
  cleancoder
  CsvtoXmlTradeConverter.cpp
  CsvtoXmlTradeConverter.h
  StringHelpers.cpp
  StringHelpers.h
  TradeProcessor.Tests.cpp
)

# Link GoogleTest libraries
target_link_libraries(
  cleancoder
  GTest::gmock_main
  gcov
)

# Include GoogleTest and discover tests
include(GoogleTest)
gtest_discover_tests(cleancoder)

