cmake_minimum_required ( VERSION 2.8 )

project ( NCL_CSC3221_2_DanNixon )

set ( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include ( CppcheckTargets )

find_program ( LCOV_PATH lcov )
if ( LCOV_PATH )
  include ( CodeCoverage )
  SET ( GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage" )
  SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
endif ( LCOV_PATH )

include ( EnableExtraCompilerWarnings )
globally_enable_extra_compiler_warnings()

include ( DoxygenTargets )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR}/inc )

# Geometry library
add_library ( Geometry
              ${CMAKE_CURRENT_SOURCE_DIR}/src/Vector2D.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/src/BoundingBox.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/src/Shape.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/src/Circle.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/src/Square.cpp )
add_cppcheck ( Geometry
               STYLE POSSIBLE_ERROR
               FAIL_ON_WARNINGS )

# Game framework library
add_library ( GameFramework
  ${CMAKE_CURRENT_SOURCE_DIR}/src/GameImpl.cpp )
add_cppcheck ( GameFramework
               STYLE POSSIBLE_ERROR
               FAIL_ON_WARNINGS )

# Make CxxTest test suites
find_package ( CxxTest )
if ( CXXTEST_FOUND )
  include_directories ( ${CXXTEST_INCLUDE_DIR} )
  link_libraries ( Geometry
                   GameFramework )
  enable_testing ()

  # Find test files
  file ( GLOB test_files
         RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/test"
         "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h")

  # Generate test suites
  foreach ( test_file ${test_files} )
    string ( REPLACE ".h" "" test_name ${test_file} )
    CXXTEST_ADD_TEST( ${test_name}
                      ${test_name}.cpp
                      "${CMAKE_CURRENT_SOURCE_DIR}/test/${test_file}" )
  endforeach ( test_file )

  if ( LCOV_PATH )
    # Generate test coverage report
    SETUP_TARGET_FOR_COVERAGE( coverage
                               ctest
                               coverage )
  endif ( LCOV_PATH )
endif ()

add_executable ( Game
                 ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp )
target_link_libraries ( Game
                        LINK_PUBLIC
                        Geometry
                        GameFramework )
add_cppcheck ( Game
               UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR
               FAIL_ON_WARNINGS )

add_doxygen( Doxyfile
             OUTPUT_DIRECTORY docs
             NO_PDF )
