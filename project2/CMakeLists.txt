cmake_minimum_required(VERSION 2.8)

project (NCL_CSC3221_2_DanNixon)

add_library (Geometry
             ${CMAKE_CURRENT_SOURCE_DIR}/src/Vector2D.cpp
             ${CMAKE_CURRENT_SOURCE_DIR}/src/BoundingBox.cpp
             ${CMAKE_CURRENT_SOURCE_DIR}/src/Shape.cpp
             ${CMAKE_CURRENT_SOURCE_DIR}/src/Circle.cpp
             ${CMAKE_CURRENT_SOURCE_DIR}/src/Square.cpp)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Make CxxTest test suites
find_package (CxxTest)
if (CXXTEST_FOUND)
  include_directories(${CXXTEST_INCLUDE_DIR})
  link_libraries (Geometry)
  enable_testing ()

  # Find test files
  file (GLOB test_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/test"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h")

  # Generate test suites
  foreach (test_file ${test_files})
    string(REPLACE ".h" "" test_name ${test_file})
    CXXTEST_ADD_TEST(${test_name}
                     ${test_name}.cpp
                     "${CMAKE_CURRENT_SOURCE_DIR}/test/${test_file}")
  endforeach (test_file)
endif ()

add_executable (Game
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp)
target_link_libraries (Game
                       LINK_PUBLIC
                       Geometry)
