#include "problemdata.h"

ProblemData::ProblemData()
{
}

ProblemData::ProblemData(QString name, QString desc)
{
    this->name = name;
    this->desc = desc;
}

ProblemData::ProblemData(QString name, QString executable, QString pkg_name, QString count, QString time)
{
    this->name = name;
    this->executable = executable;
    this->pkg_name = pkg_name;
    this->count = count;
    this->time = time;
}

QString ProblemData::getDesc()
{
    return desc;
}

QString ProblemData::getName()
{
    return name;
}

QString ProblemData::getCount()
{
    return count;
}

QString ProblemData::getExecutable()
{
    return executable;
}

QString ProblemData::getPkg_name()
{
    return pkg_name;
}

QString ProblemData::getTime()
{
    return time;
}

