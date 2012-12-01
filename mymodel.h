#ifndef MYMODEL_H
#define MYMODEL_H
// mymodel.h

#include <QAbstractListModel>
#include "dataclass.h"

class MyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    MyModel(QObject *parent);
   
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    
private:
  QList<DataClass> m_data;
  
};

#endif // MYMODEL_H
