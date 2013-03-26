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
    void setName(QString);
    QString getDesc();
    void setDesc(QString);
    QString getExecutable();
    void setExecutable(QString);
    QString getTime();
    void setTime(QString);
    QString getPkg_name();
    void setPkg_name(QString);
    QString getCount();
    void setCount(QString);
    QString getID();
    void setID(QString);

private:
    QString name;
    QString desc;
    QString executable;
    QString time;
    QString count;
    QString pkg_name;
    QString id;
};

#endif // PROBLEMDATA_H
