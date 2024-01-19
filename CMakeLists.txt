cmake_minimum_required(VERSION 3.23)

project(CS181)

set(CMAKE_CXX_STANDARD 20)

#add any include directory
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/opengl/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opengl/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/opengl/glm/
    ${CMAKE_CURRENT_SOURCE_DIR}/opengl/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

add_subdirectory(opengl)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src src)

find_package(OpenMP REQUIRED)

add_executable(main main.cpp ${src})

target_link_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_link_libraries(main PUBLIC glfw3 glad)

target_link_libraries(main PRIVATE OpenMP::OpenMP_CXX)

# find_package(OpenMP REQUIRED)

# add_executable(test test.cpp)

# target_link_libraries(test PRIVATE OpenMP::OpenMP_CXX)

