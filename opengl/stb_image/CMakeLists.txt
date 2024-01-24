set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_library(stb_image_static STATIC stb_image.cpp)
add_library(stb_image SHARED stb_image.cpp)

target_include_directories(stb_image_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

