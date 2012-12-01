#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    :QAbstractListModel(parent)
{
  for(int i=0; i < 10; i++){
    m_data << DataClass(QString::number(i)+"item", QString::number(i)+"description");
  }
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_data.count();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
      DataClass myClass = m_data.at(index.row());
      return myClass.getName();
    }
    
    if (role == Qt::UserRole){
      DataClass myClass = m_data.at(index.row());
      return myClass.getDesc();
    }
    
    return QVariant();
}