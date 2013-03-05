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
 
kde4_add_executable(kde-abrt ${kde-abrt_SRCS})
target_link_libraries(kde-abrt ${KDE4_KDEUI_LIBS})
