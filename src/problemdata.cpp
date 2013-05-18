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
    m_reported_to = reported_to;
}

QString ProblemData::package() const
{
    return m_package;
}

void ProblemData::setPackage(QString pkg)
{
    m_package = pkg;
}

QString ProblemData::count() const
{
    return m_count;
}

void ProblemData::setCount(QString count)
{
    m_count = count;
}

QString ProblemData::executable() const
{
    return m_executable;
}

void ProblemData::setExecutable(QString executable)
{
    m_executable = executable;
}

QString ProblemData::pkg_name() const
{
    return m_pkg_name;
}

void ProblemData::setPkg_name(QString pkg_name)
{
    m_pkg_name = pkg_name;
}

QString ProblemData::time() const
{
    return m_time;
}

void ProblemData::setTime(QString time)
{
    m_time = time;
}

QString ProblemData::id() const
{
    return m_id;
}

void ProblemData::setId(QString id)
{
    m_id = id;
}

QString ProblemData::type() const
{
    return m_type;
}

void ProblemData::setType(QString type)
{
    m_type = type;
}

QString ProblemData::reason() const
{
    return m_reason;
}

void ProblemData::setReason(QString reason)
{
    m_reason = reason;
}
