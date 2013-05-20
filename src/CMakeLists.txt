project (kde-abrt)

find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})

set(kde-abrt_SRCS
  main.cpp
  mainwindow.cpp
  problemdata.cpp
  dbus.cpp
  customsearchline.cpp
)

add_definitions(-DLIBEXEC_DIR="/usr/libexec")

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -pedantic -std=c++11")

SET(KDE-ABRT_DESKTOP_DIR "~/.local/share/applications/")
SET(KDE-ABRT_RC_DIR "~/.kde/share/apps/")
set(KDE-ABRT_BIN_DIR "~/.local/bin/")

kde4_add_executable(kde-abrt ${kde-abrt_SRCS})
target_link_libraries(kde-abrt ${KDE4_KDEUI_LIBS})

install(TARGETS kde-abrt DESTINATION ${KDE-ABRT_BIN_DIR})
install(FILES kde-abrtui.rc DESTINATION  ${KDE-ABRT_RC_DIR}/kde-abrt)
install(FILES kde-abrt.desktop DESTINATION ${KDE-ABRT_DESKTOP_DIR})
