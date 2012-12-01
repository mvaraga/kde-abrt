#ifndef DATACLASS_H
#define DATACLASS_H

#include <QString>

class DataClass
{
public:
  DataClass();
  DataClass(QString name, QString desc);
  QString getName();
  QString getDesc();
  
private:
  QString name;
  QString desc;
};

#endif // DATACLASS_H