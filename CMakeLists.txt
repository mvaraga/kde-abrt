cmake_minimum_required(VERSION 2.8)

project (kde-abrt)
 
find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})
 
set(kde-abrt_SRCS
  main.cpp
  mainwindow.cpp
  mymodel.cpp
  problemdata.cpp
  dbus.cpp
)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -std=c++11")
 
kde4_add_executable(kde-abrt ${kde-abrt_SRCS})
target_link_libraries(kde-abrt ${KDE4_KDEUI_LIBS})
