set(lib_path ./lib-mingw-w64)

file(COPY ${lib_path}/glfw3.dll ${lib_path}/libglfw3.a DESTINATION ${CMAKE_SOURCE_DIR}/bin)