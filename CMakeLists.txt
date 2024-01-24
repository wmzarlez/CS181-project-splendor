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
    ${CMAKE_CURRENT_SOURCE_DIR}/learnopengl
    ${CMAKE_CURRENT_SOURCE_DIR}/opengl/stb_image
)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

add_subdirectory(opengl)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src src)

add_executable(main main.cpp ${src})
add_executable(test test.cpp ${src})
add_executable(basic_lighting basic_lighting.cpp ${src})

target_link_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bin)
target_link_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bin)
target_link_directories(basic_lighting PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_link_libraries(main PUBLIC opengl_lib)
target_link_libraries(test PUBLIC opengl_lib)
target_link_libraries(basic_lighting PUBLIC opengl_lib)

