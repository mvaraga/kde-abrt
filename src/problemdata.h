#ifndef PROBLEMDATA_H
#define PROBLEMDATA_H

#include <QString>

class ProblemData
{
public:
    ProblemData();
    ProblemData(QString name, QString desc);
    ProblemData(QString name, QString executable, QString pkg_name, QString count, QString time); //bad
    QString getName();
    QString getDesc();
    QString getExecutable();
    QString getTime();
    QString getPkg_name();
    QString getCount();

private:
    QString name;
    QString desc;
    QString executable;
    QString time;
    QString count;
    QString pkg_name;
};

#endif // PROBLEMDATA_H
