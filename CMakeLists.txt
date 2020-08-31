cmake_minimum_required(VERSION 3.11.0)
project(Gengine)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

find_package(SDL2 CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
