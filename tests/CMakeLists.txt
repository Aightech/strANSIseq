# Tests CMakeLists.txt
# Build with: cmake .. -DBUILD_TESTS=ON && make
#
# To add a new test:
# 1. Create test_<name>.cpp in this directory
# 2. Add test_<name>.cpp to TEST_SOURCES below
# 3. Rebuild

# Get parent project's library name
get_directory_property(PARENT_LIB_NAME DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/.. DEFINITION LIB_NAME)

# Test executables - add your test files here
set(TEST_SOURCES
    # test_example.cpp
)

foreach(test_source ${TEST_SOURCES})
    # Get test name from filename
    get_filename_component(test_name ${test_source} NAME_WE)

    # Create executable
    add_executable(${test_name} ${test_source})

    # Link against the library
    target_link_libraries(${test_name} PRIVATE ${PARENT_LIB_NAME})

    # Include directories
    target_include_directories(${test_name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    # Add pthread on Unix
    if(UNIX)
        target_link_libraries(${test_name} PRIVATE pthread)
    endif()

    # Compiler options
    target_compile_options(${test_name} PRIVATE -Wall -Wextra)
endforeach()

# Custom target to run all tests
# Uncomment and modify when you have tests:
# add_custom_target(run_tests
#     COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_example
#     COMMENT "Running unit tests..."
#     DEPENDS test_example
# )
