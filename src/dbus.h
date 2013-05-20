#ifndef DBUS_H
#define DBUS_H

#include <QtDBus/QtDBus>

class ProblemData;

typedef QMap <QString, QString> MetaMap;
Q_DECLARE_METATYPE(MetaMap)

/**
 * This class connects to abrtd via dbus. It can get problems for current user
 * or for all users on system and delete problems.
 */
class Dbus
{
public:
    explicit Dbus();
    virtual ~Dbus();
    QList<ProblemData*>* getProblems(bool allProblems = false);
    void deleteProblem(QStringList* problems);
    bool chownProblem(const QString&);

private:
    class DbusPrivate;
    DbusPrivate* const d;
};

#endif
