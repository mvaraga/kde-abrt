#include <stdio.h>
#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>
#include "dbus.h"


QStringList* Dbus::execute()
{
    qDBusRegisterMetaType<QMap<QString,QString> >();

  

    QString service("org.freedesktop.problems");

    QDBusConnection bus = QDBusConnection::systemBus();
    QDBusInterface *interface = new QDBusInterface(service,
            "/org/freedesktop/problems",
            "org.freedesktop.problems",
            bus);

    QDBusReply<QStringList> reply = interface->call("GetProblems");
    QStringList stats("executable");

    if (reply.isValid())
    {
        QStringList list = reply.value();

        for (int i = 0; i < list.size(); ++i)
        {
            printf("%s\n", qPrintable(list.at(i)));

            QDBusReply<QMap<QString,QString> > replyInfo = interface->call("GetInfo", list.at(i),stats);

            if(replyInfo.isValid()) {
                printf("\t%s\n", qPrintable(replyInfo.value().value("executable")));
            } else
            {
                fprintf(stderr, "replyInfo failed: %s\n", qPrintable(replyInfo.error().message()));
            }
        }
        
        return new QStringList(list);

    }
    else {
        fprintf(stderr, "Call failed: %s\n", qPrintable(reply.error().message()));
        return NULL;
    }
    
}

