#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>

#include "mainwindow.h"

int main (int argc, char *argv[])
{
  KAboutData aboutData( "kde-abrt", 0,
      ki18n("KDE ABRT"), "1.0",
      ki18n("KDE Automatic Bug Reporting Tool"),
      KAboutData::License_GPL,
      ki18n("Copyright (c) 2007 Developer") );
  KCmdLineArgs::init( argc, argv, &aboutData );

  KApplication app;

  MainWindow* window = new MainWindow();
  window->show();

  return app.exec();
}
