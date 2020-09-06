cmake_minimum_required(VERSION 3.11.0)
project(Gengine)

set(GENGINE_SRCS
  gengine.cpp
  screenmanager.cpp
  gameobjectbase.cpp
  utility.cpp
  sprite.cpp
  spriteinfo.cpp
  )

set(GENGINE_HDRS
  ../include/gengine.hpp
  ../include/screenmanager.hpp
  ../include/gameobjectbase.hpp
  ../include/utility.hpp
  ../include/sprite.hpp
  )

add_library(Gengine
  ${GENGINE_SRCS}
  ${GENGINE_HDRS}
  )

target_include_directories(Gengine PUBLIC
  ../include
  )

target_link_libraries(Gengine PUBLIC
  SDL2::SDL2
  SDL2::SDL2main
  ${Boost_LIBRARIES}
  )

set_property(TARGET Gengine PROPERTY CXX_STANDARD 11)

