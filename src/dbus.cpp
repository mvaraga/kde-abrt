#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>
#include <QListWidget>
#include <QtAlgorithms>
#include "dbus.h"
#include "problemdata.h"

/**
 * This constructor create connection to dbus.
 */
Dbus::Dbus()
{
    qDBusRegisterMetaType<QMap<QString, QString> >(); //allow QDBusReply<QMap<QString,QString> >

    service = "org.freedesktop.problems";
    path = "/org/freedesktop/problems";
    interface = "org.freedesktop.problems";

    connection = new QDBusConnection(QDBusConnection::systemBus());
    dInterface = new QDBusInterface(service,
                                    path,
                                    interface,
                                    *connection);
}

/**
 * This method gets problems from abrtd.
 * When @p allProblems is @c true, gets problems from all users.
 *
 * @param allProblems show problems from all users?
 * 
 * @return List of problems
 */
QList<ProblemData*>* Dbus::getProblems(bool allProblems)
{
    //get reply from dbus
    QDBusReply<QStringList> reply = dInterface->call(allProblems ? "GetAllProblems" : "GetProblems");

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

            QDBusReply<QMap<QString, QString> > replyInfo = dInterface->call("GetInfo", stringList.at(i), *stats);

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
	qSort(list->begin(), list->end(), comp);

        return list;

    } else {
        fprintf(stderr, "Call failed: %s\n", qPrintable(reply.error().message()));
        return NULL;
    }

}

/**
 * This method deletes problems.
 * 
 * @param problems problems to delete
 * 
 */
void Dbus::deleteProblem(QStringList* problems)
{
    QDBusReply<void> reply = dInterface->call("DeleteProblem", *problems);
    if (reply.isValid()) return;
    else {
        fprintf(stderr, "Call failed: %s\n", qPrintable(reply.error().message()));
    }
}

bool comp(ProblemData* left, ProblemData *right) {
  return left->getTime() < right->getTime();
}
