cmake_minimum_required(VERSION 2.8)

project (NCL_CSCCSC3221_1_DanNixon)

add_library (Geometry
             ${CMAKE_CURRENT_SOURCE_DIR}/src/Vector3DStack.cpp
             ${CMAKE_CURRENT_SOURCE_DIR}/src/Quaternion.cpp)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/inc)

find_package(CxxTest)
if(CXXTEST_FOUND)
  include_directories(${CXXTEST_INCLUDE_DIR})
  link_libraries(Geometry)
  enable_testing()
  CXXTEST_ADD_TEST(cxxtests
                   runner.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/test/CxxTests.h)
endif()

add_executable (Test
                ${CMAKE_CURRENT_SOURCE_DIR}/test/Test.cpp)
target_link_libraries (Test
                       LINK_PUBLIC
                       Geometry)
