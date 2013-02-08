#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>
#include <QListWidget>
#include "dbus.h"


QList<QListWidgetItem*>* Dbus::getProblems(bool allProblems)
{
    qDBusRegisterMetaType<QMap<QString,QString> >(); //allow QDBusReply<QMap<QString,QString> >

    //create connection
    QString service("org.freedesktop.problems");
    QDBusConnection bus = QDBusConnection::systemBus();
    QDBusInterface *interface = new QDBusInterface(service,
            "/org/freedesktop/problems",
            "org.freedesktop.problems",
            bus);

    
    //get reply from dbus
    QDBusReply<QStringList> reply = interface->call(allProblems ? "GetAllProblems" : "GetProblems");
    
    //attributes for problems
    QStringList *stats = new QStringList();
    *stats << "executable";
    *stats << "time";
    *stats << "count";
    *stats << "pkg_name";

    if (reply.isValid())
    {
        QStringList stringList = reply.value();
	QList<QListWidgetItem*> *list = new QList<QListWidgetItem*>();
	QListWidgetItem *item;
        for (int i = 0; i < stringList.size(); ++i)
        {
            //printf("%s\n", qPrintable(stringList.at(i)));

            QDBusReply<QMap<QString,QString> > replyInfo = interface->call("GetInfo", stringList.at(i),*stats);

            if(replyInfo.isValid()) {
		item = new QListWidgetItem(stringList.at(i));
		item->setData(Qt::UserRole, replyInfo.value().value("executable"));
		item->setData(Qt::UserRole+1, replyInfo.value().value("pkg_name"));
		item->setData(Qt::UserRole+2, replyInfo.value().value("time"));
		item->setData(Qt::UserRole+3, replyInfo.value().value("count"));
		list->append(item);
                //printf("\t%s\n", qPrintable(replyInfo.value().value("executable")));
            } else
            {
                fprintf(stderr, "replyInfo failed: %s\n", qPrintable(replyInfo.error().message()));
            }
        }
        
	return list;

    }
    else {
        fprintf(stderr, "Call failed: %s\n", qPrintable(reply.error().message()));
        return NULL;
    }
    
}

