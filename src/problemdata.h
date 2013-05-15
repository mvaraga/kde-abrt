#ifndef PROBLEMDATA_H
#define PROBLEMDATA_H

#include <QString>

class ProblemData
{
public:
    ProblemData();
    ProblemData(QString name, QString desc);
    ProblemData(QString name, QString executable, QString pkg_name, QString count, QString time); //bad
    QString name() const;
    void setName(QString);
    QString desc() const;
    void setDesc(QString);
    QString executable() const;
    void setExecutable(QString);
    QString time() const;
    void setTime(QString);
    QString pkg_name() const;
    void setPkg_name(QString);
    QString count() const;
    void setCount(QString);
    QString id() const;
    void setId(QString);

private:
    QString m_name;
    QString m_desc;
    QString m_executable;
    QString m_time;
    QString m_count;
    QString m_pkg_name;
    QString m_id;
};

#endif // PROBLEMDATA_H
