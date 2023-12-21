cmake_minimum_required(VERSION 3.23)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
aux_source_directory(./src opengl_src)
#add_library(opengl_lib STATIC ${opengl_src})
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR/bin})