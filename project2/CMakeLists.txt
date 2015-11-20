cmake_minimum_required(VERSION 2.8)

project (NCL_CSCCSC3221_2_DanNixon)

add_library (Geometry
             ${CMAKE_CURRENT_SOURCE_DIR}/src/Shape.cpp
             ${CMAKE_CURRENT_SOURCE_DIR}/src/Circle.cpp
             ${CMAKE_CURRENT_SOURCE_DIR}/src/Square.cpp)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/inc)

find_package(CxxTest)
if(CXXTEST_FOUND)
  include_directories(${CXXTEST_INCLUDE_DIR})
  link_libraries(Geometry)
  enable_testing()
  CXXTEST_ADD_TEST(cxxtests
                   runner.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/test/CircleTest.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/test/SquareTest.h)
endif()

add_executable (Game
                ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp)
target_link_libraries (Game
                       LINK_PUBLIC
                       Geometry)
