#include "problemdata.h"

ProblemData::ProblemData()
{
}

QString ProblemData::reported_to() const
{
    return m_reported_to;
}

void ProblemData::setReported_to(QString reported_to)
{
    this->m_reported_to = reported_to;
}

QString ProblemData::package() const
{
    return m_package;
}

void ProblemData::setPackage(QString pkg)
{
    this->m_package = pkg;

}

QString ProblemData::count() const
{
    return m_count;
}

void ProblemData::setCount(QString count)
{
    this->m_count = count;
}

QString ProblemData::executable() const
{
    return m_executable;
}

void ProblemData::setExecutable(QString executable)
{
    this->m_executable = executable;
}

QString ProblemData::pkg_name() const
{
    return m_pkg_name;
}

void ProblemData::setPkg_name(QString pkg_name)
{
    this->m_pkg_name = pkg_name;
}

QString ProblemData::time() const
{
    return m_time;
}

void ProblemData::setTime(QString time)
{
    this->m_time = time;
}

QString ProblemData::id() const
{
    return m_id;
}

void ProblemData::setId(QString id)
{
    this->m_id = id;
}
