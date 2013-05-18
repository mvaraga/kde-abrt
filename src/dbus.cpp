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

    m_service = "org.freedesktop.problems";
    m_path = "/org/freedesktop/problems";
    m_interface = "org.freedesktop.problems";

    m_connection = new QDBusConnection(QDBusConnection::systemBus());
    m_dInterface = new QDBusInterface(m_service,
                                    m_path,
                                    m_interface,
                                    *m_connection);
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
    QDBusReply<QStringList> reply = m_dInterface->call(allProblems ? "GetAllProblems" : "GetProblems");

    if (reply.isValid()) {

        //attributes for problems
        QStringList* stats = new QStringList();
        const QString statExecutable("executable");
        const QString statTime("time");
        const QString statCount("count");
        const QString statReported_to("reported_to");
        const QString statPkg_name("pkg_name");
        const QString statPackage("package");
	const QString statType("type");
	const QString statReason("reason");
        stats->append(statExecutable);
        stats->append(statTime);
        stats->append(statPkg_name);
        stats->append(statCount);
        stats->append(statReported_to);
        stats->append(statPackage);
	stats->append(statType);
	stats->append(statReason);

        QStringList stringList = reply.value();
        QList<ProblemData*>* list = new QList<ProblemData*>();
        ProblemData* item;

        for (int i = 0; i < stringList.size(); ++i) {
            QDBusReply<QMap<QString, QString> > replyInfo = m_dInterface->call("GetInfo", stringList.at(i), *stats);
            if (replyInfo.isValid()) {
                item = new ProblemData();
                item->setId(stringList.at(i));
                item->setExecutable(replyInfo.value().value(statExecutable));
                item->setPkg_name(replyInfo.value().value(statPkg_name));
                item->setCount(replyInfo.value().value(statCount));
                item->setTime(replyInfo.value().value(statTime));
                item->setPackage(replyInfo.value().value(statPackage));
                item->setReported_to(replyInfo.value().value(statReported_to));
		item->setType(replyInfo.value().value(statType));
		item->setReason(replyInfo.value().value(statReason));
                list->append(item);
            } else {
                qDebug("replyInfo failed: %s", qPrintable(replyInfo.error().message()));
            }
        }
        delete(stats);
        //sort by date, new on top
        qSort(list->begin(), list->end(), comp);

        return list;

    } else {
        qDebug("Call failed: %s\n", qPrintable(reply.error().message()));
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
    QDBusReply<void> reply = m_dInterface->call("DeleteProblem", *problems);
    if (reply.isValid()) return;
    else {
        qDebug("Call failed: %s\n", qPrintable(reply.error().message()));
    }
}

bool comp(ProblemData* left, ProblemData* right)
{
    return left->time() > right->time();
}
