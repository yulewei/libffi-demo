cmake_minimum_required(VERSION 3.7)
project(ffidemo)

set(CMAKE_C_STANDARD 99)

#set(SOURCE_FILES main.c)
set(SOURCE_FILES main_closure.c)
add_executable(ffidemo ${SOURCE_FILES})

include_directories("/usr/local/opt/libffi/lib/libffi-3.2.1/include")
link_directories(/usr/local/opt/libffi/lib)
target_link_libraries(ffidemo /usr/local/opt/libffi/lib/libffi.dylib)