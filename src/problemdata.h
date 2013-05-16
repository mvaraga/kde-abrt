#ifndef PROBLEMDATA_H
#define PROBLEMDATA_H

#include <QString>

class ProblemData
{
public:
    ProblemData();
    QString package() const;
    void setPackage(QString);
    QString reported_to() const;
    void setReported_to(QString);
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
    QString m_package;
    QString m_reported_to;
    QString m_executable;
    QString m_time;
    QString m_count;
    QString m_pkg_name;
    QString m_id;
};

#endif // PROBLEMDATA_H
