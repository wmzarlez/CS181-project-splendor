cmake_minimum_required(VERSION 3.23)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(stb_image)

aux_source_directory(./src opengl_src)

add_library(opengl_lib STATIC ${opengl_src})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

target_link_libraries(opengl_lib 
    PUBLIC 
        glad
        glfw3
        glm
        stb_image
)

target_include_directories(opengl_lib 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
)


