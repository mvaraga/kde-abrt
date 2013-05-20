#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>
#include <QListWidget>
#include <QtAlgorithms>
#include <KDebug>
#include "dbus.h"
#include "problemdata.h"

/**
 * class DbusPrivate
 */
class Dbus::DbusPrivate
{
public:
    DbusPrivate(): m_dInterface(new QDBusInterface("org.freedesktop.problems",
                                    "/org/freedesktop/problems",
                                    "org.freedesktop.problems",
                                    QDBusConnection::systemBus()))
    {}

    QDBusInterface* m_dInterface;
};


/**
 * This constructor create connection to dbus.
 */
Dbus::Dbus(): d(new DbusPrivate())
{
    //allow QDBusReply<QMap<QString,QString> >
    qDBusRegisterMetaType<QMap<QString, QString> >();
}
/**
 * Destructor deleting d-pointer
 */
Dbus::~Dbus()
{
    delete(d);
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
    QDBusReply<QStringList> reply = d->m_dInterface->call(allProblems ? "GetAllProblems" : "GetProblems");

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
            //calling method GetInfo via dbus
            QDBusReply<QMap<QString, QString> > replyInfo = d->m_dInterface->call("GetInfo", stringList.at(i), *stats);
            if (replyInfo.isValid()) {
	      //set all attributes
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

                //sort by date, new on top
                //lambda abstraction, c++11
                qSort(list->begin(), list->end(),
                [](ProblemData * left, ProblemData *  right) {
                    return left->time() > right->time();
                });
            } else {
                kDebug() << qPrintable("replyInfo failed: " + replyInfo.error().message());
            }
        }
        delete(stats);
        return list;
    } else {
        kError() << "Call failed: " << qPrintable(reply.error().message());
        return NULL;
    }
}

/**
 * This method deletes problems.
 *
 * @param problems problems to delete
 *
 */
bool Dbus::deleteProblem(QStringList* problems)
{
    QDBusReply<void> reply = d->m_dInterface->call("DeleteProblem", *problems);
    if (reply.isValid())
      return true;
    else {
        kError() << "Call failed: " << qPrintable(reply.error().message());
	return false;
    }
}

/**
 * This method change ownership of problem to current user.
 * 
 * @param problem problem to change ownership
 * 
 * @return returns @c true if it is OK, @c false if method failed
 */
bool Dbus::chownProblem(const QString& problem)
{
    QDBusReply<void> reply = d->m_dInterface->call("ChownProblemDir", problem);
    if (reply.isValid())
      return true;
    else {
        kError() << "Call failed: " << qPrintable(reply.error().message());
	return false;
    }

}
