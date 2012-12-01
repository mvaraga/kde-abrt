#include <QListView>
#include "mymodel.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
    listView = new QListView(this);
    myModel = new MyModel(this);
    listView->setModel(myModel);
    
    connect(listView, SIGNAL(activated(const QModelIndex &)), this, SLOT(on_listView_activated(QModelIndex)));
  

  
  master = new QWidget;
  layout = new QVBoxLayout;
  labelName = new QLabel("label");
  labelDescription = new QLabel("label");

  listWidget = new KListWidget(); //old
  
  QListWidgetItem *item; //old
  
  //old
  for(int i=0;i<10;i++){
    item = new QListWidgetItem(QString::number(i) + "item");
    item->setData(Qt::UserRole, "description" + QString::number(i));
    //item->setData(Qt::UserRole+1,"");
    listWidget->addItem(item);
  }

  layout->addWidget(listWidget); //old
  layout->addWidget(labelName);
  layout->addWidget(labelDescription);
  layout->addWidget(listView);

  master->setLayout(layout);

  setCentralWidget(master);

  //old
  connect(listWidget, SIGNAL(executed(QListWidgetItem*)),
          this, SLOT(on_listWidget_executed(QListWidgetItem*)));

 // setupGUI();
}

//old
void MainWindow::on_listWidget_executed(QListWidgetItem *item){
  QString text = item->text();
  QString desc = item->data(Qt::UserRole).toString();
  labelName->setText(text);
  labelDescription->setText(desc);
}


void MainWindow::on_listView_activated(QModelIndex index)
{
  labelName->setText(myModel->data(index, Qt::DisplayRole).toString());
  labelDescription->setText(myModel->data(index, Qt::UserRole).toString());
}




