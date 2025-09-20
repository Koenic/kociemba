cmake_minimum_required(VERSION 3.15)
project(libkociemba VERSION 1.0.0 LANGUAGES C)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries instead of static" ON)
option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_EXAMPLES "Build example programs" ON)

# Include headers
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/internal)

# Library sources
set(KOCIEMBA_SOURCES
    src/facecube.c
    src/cubycube.c
    src/coordcube.c
)

# Build the library
add_library(kociemba ${KOCIEMBA_SOURCES})

# Set public include directory
target_include_directories(kociemba PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Install rules
install(TARGETS kociemba
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(FILES include/kociemba.h DESTINATION include)

# Install precomputed data files
install(DIRECTORY data/ DESTINATION share/libkociemba/data)

# Examples
if(BUILD_EXAMPLES)
    if(TARGET solve)
        target_link_libraries(solve kociemba)
    endif()
endif()

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_executable(test_cubycube tests/test_cubycube.c)
    target_link_libraries(test_cubycube kociemba)
    add_test(NAME SolverTest COMMAND test_cubycube)
endif()