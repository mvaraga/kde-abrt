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
    buttonConnection = new KPushButton("get problems",this);
    buttonGetAllProblems = new KPushButton("get all problems",this);

    connect(listView, SIGNAL(activated(const QModelIndex &)), this, SLOT(on_listView_activated(QModelIndex)));
    connect(buttonConnection, SIGNAL(clicked(bool)), this, SLOT(on_buttonConnect_clicked()));
    connect(buttonGetAllProblems, SIGNAL(clicked(bool)), this, SLOT(on_buttonGetAllProblems_clicked()));

    
    master = new QWidget;
    layout = new QVBoxLayout;
    labelName = new QLabel("label");
    labelDescription = new QLabel("label");
    label1 = new QLabel();
    label2 = new QLabel();
    label3 = new QLabel();
    
    listWidget = new KListWidget(); //widget

    on_buttonConnect_clicked();

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
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);
    layout->addWidget(listView);
    layout->addWidget(buttonConnection);
    layout->addWidget(buttonGetAllProblems);

    master->setLayout(layout);

    setCentralWidget(master);

    //widget
    connect(listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
      this, SLOT(on_listWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*))
    );

// setupGUI();
}

//widget
void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem* item, QListWidgetItem* prev) {
    QString text = item->text();
    QString desc = item->data(Qt::UserRole).toString();
    labelDescription->setText(item->data(Qt::UserRole).toString()); //executable
    label1->setText(item->data(Qt::UserRole+1).toString()); //pkg_name
    label2->setText(item->data(Qt::UserRole+2).toString()); //time
    label3->setText(item->data(Qt::UserRole+3).toString()); //count
    labelName->setText(text);
    //labelDescription->setText();

    fprintf(stderr ,"%s\n", qPrintable(text)); //debug
}

void MainWindow::on_listView_activated(QModelIndex index)
{
    labelName->setText(myModel->data(index, Qt::DisplayRole).toString());
    labelDescription->setText(myModel->data(index, Qt::UserRole).toString());

    fprintf(stderr ,"%s\n", qPrintable(myModel->data(index, Qt::DisplayRole).toString())); //debug

}

void MainWindow::on_buttonConnect_clicked() {
    QList<QListWidgetItem*>* list;
    list = Dbus::getProblems(false);
      
    if(list->empty()){
      fprintf(stderr, "empty list");
    }
    
    for(int i = 0; i < list->size(); i++){ 
      item = list->at(i);
      listWidget->addItem(item);
    }
}

void MainWindow::on_buttonGetAllProblems_clicked() {
    QList<QListWidgetItem*>* list;
    list = Dbus::getProblems(true);
      
    if(list->empty()){
      fprintf(stderr, "empty list");
    }
    
    for(int i = 0; i < list->size(); i++){ 
      item = list->at(i);
      listWidget->addItem(item);
    }
}

