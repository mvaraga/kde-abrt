#ifndef DBUS_H
#define DBUS_H

#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>

class ProblemData;

typedef QMap <QString, QString> MetaMap;
Q_DECLARE_METATYPE(MetaMap)

class Dbus
{
public:
    static QList<ProblemData*>* getProblems(bool allProblems = false);
    static void deleteProblem(QStringList* problems);
    //static QList<QListWidgetItem*>* getAllProblems(int);
private:
    static QDBusInterface* createInterface();
};

#endif
