#include "problemdata.h"

ProblemData::ProblemData()
{
}

QString ProblemData::getDesc()
{
    return desc;
}

void ProblemData::setDesc(QString desc)
{
    this->desc = desc;
}

QString ProblemData::getName()
{
    return name;
}

void ProblemData::setName(QString name)
{
    this->name = name;

}

QString ProblemData::getCount()
{
    return count;
}

void ProblemData::setCount(QString count)
{
    this->count = count;
}

QString ProblemData::getExecutable()
{
    return executable;
}

void ProblemData::setExecutable(QString executable)
{
    this->executable = executable;
}

QString ProblemData::getPkg_name()
{
    return pkg_name;
}

void ProblemData::setPkg_name(QString pkg_name)
{
    this->pkg_name = pkg_name;
}

QString ProblemData::getTime()
{
    return time;
}

void ProblemData::setTime(QString time)
{
    this->time = time;
}

QString ProblemData::getID()
{
    return id;
}

void ProblemData::setID(QString id)
{
    this->id = id;
}
