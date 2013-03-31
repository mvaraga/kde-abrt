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
    Dbus();
    QList<ProblemData*>* getProblems(bool allProblems = false);
    void deleteProblem(QStringList* problems);

private:
    QDBusInterface* createInterface();

    QString service;
    QString path;
    QString interface;
    QDBusConnection* connection;
    QDBusInterface* dInterface;
};

#endif
