#include <QListView>
#include <stdio.h>
#include "mymodel.h"
#include "mainwindow.h"
#include "dbus.h"


MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
    listView = new QListView(this);
    myModel = new MyModel(this);
    listView->setModel(myModel);
    buttonConnection = new KPushButton("connect",this);

    connect(listView, SIGNAL(activated(const QModelIndex &)), this, SLOT(on_listView_activated(QModelIndex)));
    connect(buttonConnection, SIGNAL(clicked(bool)), this, SLOT(on_buttonConnect_clicked()));

    master = new QWidget;
    layout = new QVBoxLayout;
    labelName = new QLabel("label");
    labelDescription = new QLabel("label");

    listWidget = new KListWidget(); //widget
    QListWidgetItem *item; //widget

   
    QStringList* list;
    list = Dbus::execute();
      
    if(list->empty()){
      fprintf(stderr, "empty list");
    }
    QString string;
    for(int i = 0; i < list->size(); i++){
      item = new QListWidgetItem(list->at(i));
      item->setData(Qt::UserRole, "description");
      listWidget->addItem(item);
    }

   /* 
    //widget
    for(int i=0; i<10; i++) {
        item = new QListWidgetItem(QString::number(i) + "item");
        item->setData(Qt::UserRole, "description" + QString::number(i));
        //item->setData(Qt::UserRole+1,"");
        listWidget->addItem(item);
    }*/

    layout->addWidget(listWidget); //widget
    layout->addWidget(labelName);
    layout->addWidget(labelDescription);
    layout->addWidget(listView);
    layout->addWidget(buttonConnection);

    master->setLayout(layout);

    setCentralWidget(master);

    //widget
    connect(listWidget, SIGNAL(executed(QListWidgetItem*)),
            this, SLOT(on_listWidget_executed(QListWidgetItem*)));

// setupGUI();
}

//widget
void MainWindow::on_listWidget_executed(QListWidgetItem *item) {
    QString text = item->text();
    QString desc = item->data(Qt::UserRole).toString();
    labelName->setText(text);
    labelDescription->setText(desc);

    fprintf(stderr ,"%s\n", qPrintable(text)); //debug
}


void MainWindow::on_listView_activated(QModelIndex index)
{
    labelName->setText(myModel->data(index, Qt::DisplayRole).toString());
    labelDescription->setText(myModel->data(index, Qt::UserRole).toString());

    fprintf(stderr ,"%s\n", qPrintable(myModel->data(index, Qt::DisplayRole).toString())); //debug

}

void MainWindow::on_buttonConnect_clicked() {
    QStringList* list;
    list = Dbus::execute();
      
    if(list->empty()){
      fprintf(stderr, "empty list");
    }
    QString string;
    for(int i = 0; i < list->size(); i++){
      item = new QListWidgetItem(list->at(i));
      item->setData(Qt::UserRole, "description");
      listWidget->addItem(item);
    }
}
