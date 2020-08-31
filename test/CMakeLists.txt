cmake_minimum_required(VERSION 3.11.0)
project(GengineTest)

add_executable(GengineTest
  main.cpp
  guy.hpp
  guy.cpp
  )

target_link_libraries(GengineTest PRIVATE
  Gengine
  )

configure_file(./images/guy.bmp guy.bmp COPYONLY)
