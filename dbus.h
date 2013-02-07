#ifndef DBUS_H
#define DBUS_H

#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>

typedef QMap <QString, QString> MyMap;
Q_DECLARE_METATYPE(MyMap)

class Dbus
{
  public:
    static QList<QListWidgetItem*>* execute();

  private:


};


#endif
    
