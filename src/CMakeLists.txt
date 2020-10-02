cmake_minimum_required(VERSION 3.11.0)
project(Gengine)

set(GENGINE_SRCS
  gengine.cpp
  inputmanager.cpp
  screenmanager.cpp
  sprite.cpp
  spriteinfo.cpp
  componentmanager.cpp
  systemmanager.cpp
  )

set(GENGINE_HDRS
  ../include/gengine.hpp
  ../include/inputmanager.hpp
  ../include/screenmanager.hpp
  ../include/sprite.hpp
  ../include/utility.hpp
  ../include/fwd.hpp
  ../include/componentmanager.hpp
  )

add_library(Gengine
  ${GENGINE_SRCS}
  ${GENGINE_HDRS}
  )

target_include_directories(Gengine PUBLIC
  ../include
  )

target_link_libraries(Gengine PUBLIC
  SDL2::SDL2-static
  SDL2::SDL2main
  ${Boost_LIBRARIES}
  )

set_property(TARGET Gengine PROPERTY CXX_STANDARD 17)
