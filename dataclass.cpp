#include "dataclass.h"

DataClass::DataClass()
{
}

DataClass::DataClass(QString name, QString desc)
{
  this->name = name;
  this->desc = desc;
}

QString DataClass::getDesc()
{
  return desc;
}

QString DataClass::getName()
{
  return name;
}

