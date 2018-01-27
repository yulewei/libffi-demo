cmake_minimum_required(VERSION 3.7)
project(ffidemo)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(ffidemo ${SOURCE_FILES})

include_directories("/usr/local/Cellar/libffi/3.0.13/lib/libffi-3.0.13/include")
link_directories(/usr/local/Cellar/libffi/3.0.13/lib)
target_link_libraries(ffidemo ffi)