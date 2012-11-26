#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{

  master = new QWidget;
  layout = new QVBoxLayout;
  labelName = new QLabel("label");
  labelDescription = new QLabel("label");

  listWidget = new KListWidget();
  searchLine = new KListWidgetSearchLine(0,listWidget);

  QListWidgetItem *item;
  for(int i=0;i<10;i++){
    item = new QListWidgetItem(QString::number(i) + "item");
    item->setData(Qt::UserRole, "description" + QString::number(i));
    //item->setData(Qt::UserRole+1,"");
    listWidget->addItem(item);
  }

  layout->addWidget(listWidget);
  layout->addWidget(labelName);
  layout->addWidget(labelDescription);

  master->setLayout(layout);

  setCentralWidget(master);

  //connect(listWidget, )
  connect(listWidget, SIGNAL(executed(QListWidgetItem*)),
          this, SLOT(on_listWidget_executed(QListWidgetItem*)));

 // setupGUI();
}

void MainWindow::on_listWidget_executed(QListWidgetItem *item){

  QString text = item->text();
  QString desc = item->data(Qt::UserRole).toString();
  labelName->setText(text);
  labelDescription->setText(desc);
}



