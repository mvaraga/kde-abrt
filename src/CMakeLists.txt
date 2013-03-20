project (kde-abrt)

find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})

set(kde-abrt_SRCS
  main.cpp
  mainwindow.cpp
  problemdata.cpp
  dbus.cpp
)


add_definitions(-DLIBEXEC_DIR="/usr/libexec")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11")

kde4_add_executable(kde-abrt ${kde-abrt_SRCS})
target_link_libraries(kde-abrt ${KDE4_KDEUI_LIBS})

