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
    static QList<QListWidgetItem*>* getProblems(bool allProblems=false);
    static void deleteProblem(QStringList *problems);
    //static QList<QListWidgetItem*>* getAllProblems(int);
  private:
    static QDBusInterface* createInterface();


};


#endif
    
