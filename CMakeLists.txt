cmake_minimum_required(VERSION 2.8.9)

project(countinuous_integration)

include_directories(include)
file(GLOB SOURCES "src/*.c")

#Generate the shared (STATIC, SHARED or MODULE) library from the sources
add_library(${PROJECT_NAME} STATIC ${SOURCES} include/university.h src/university.c include/list.h src/list.c)


#------------------------------------------------------------------------------

# install library headers
install(
        DIRECTORY      include/
        DESTINATION    /usr/local/include
        FILES_MATCHING PATTERN "*.h"
)

#Set the location for library installation -- i.e., /usr/local/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(
        TARGETS     ${PROJECT_NAME}
        DESTINATION /usr/local/lib
)

project(test.out)

add_executable(${PROJECT_NAME} tests/main.c ${SOURCES})

target_link_libraries(${PROJECT_NAME} check subunit rt m pthread)

target_link_libraries(test.out m)

SET(CMAKE_C_FLAGS "-std=c11 -Wall -pedantic-errors -Werror -Wno-unused")

#
# Create make test
#
enable_testing()
add_test(unit-tests ${CMAKE_PROJECT_NAME})

## Coverage
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)
include(CodeCoverage)
setup_target_for_coverage(${CMAKE_PROJECT_NAME}_coverage ${CMAKE_PROJECT_NAME} coverage)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-std=c99 -g -O0 -fprofile-arcs -ftest-coverage")
