#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>
#include <QListWidget>
#include "dbus.h"
#include "problemdata.h"


QList<ProblemData*>* Dbus::getProblems(bool allProblems)
{
    qDBusRegisterMetaType<QMap<QString, QString> >(); //allow QDBusReply<QMap<QString,QString> >

    //create connection
    QDBusInterface* interface = createInterface();

    //get reply from dbus
    QDBusReply<QStringList> reply = interface->call(allProblems ? "GetAllProblems" : "GetProblems");

    if (reply.isValid()) {

        //attributes for problems
        QStringList* stats = new QStringList();
        const QString statExecutable("executable");
        const QString statTime("time");
        const QString statCount("count");
        const QString statPkg_name("pkg_name");
        stats->append(statExecutable);
        stats->append(statTime);
        stats->append(statPkg_name);
        stats->append(statCount);

        QStringList stringList = reply.value();
        QList<ProblemData*> *list = new QList<ProblemData*>();
        ProblemData* item;

        for (int i = 0; i < stringList.size(); ++i) {
            //printf("%s\n", qPrintable(stringList.at(i)));

            QDBusReply<QMap<QString, QString> > replyInfo = interface->call("GetInfo", stringList.at(i), *stats);

            if (replyInfo.isValid()) {
                item = new ProblemData();
                item->setID(stringList.at(i));
                item->setExecutable(replyInfo.value().value(statExecutable));
                item->setPkg_name(replyInfo.value().value(statPkg_name));
                item->setCount(replyInfo.value().value(statCount));
                item->setTime(replyInfo.value().value(statTime));
                list->append(item);
                //printf("\t%s\n", qPrintable(replyInfo.value().value("executable")));
            } else {
                fprintf(stderr, "replyInfo failed: %s\n", qPrintable(replyInfo.error().message()));
            }
        }
        delete(stats);
        return list;

    } else {
        fprintf(stderr, "Call failed: %s\n", qPrintable(reply.error().message()));
        return NULL;
    }

}

void Dbus::deleteProblem(QStringList* problems)
{
    //create connection
    QDBusInterface* interface = createInterface();

    QDBusReply<void> reply = interface->call("DeleteProblem", *problems);
    if (reply.isValid()) return;
    else {
        fprintf(stderr, "Call failed: %s\n", qPrintable(reply.error().message()));
    }
}

QDBusInterface* Dbus::createInterface()
{
    QString service("org.freedesktop.problems");
    QDBusConnection bus = QDBusConnection::systemBus();
    QDBusInterface* interface = new QDBusInterface(service,
            "/org/freedesktop/problems",
            "org.freedesktop.problems",
            bus);
    return interface;
}
