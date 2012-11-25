#include "mainwindow.h"
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{

  master = new QWidget;
  QHBoxLayout *layout = new QHBoxLayout;

  listWidget = new KListWidget();
  searchLine = new KListWidgetSearchLine(0,listWidget);

  for(int i=0;i<10;i++){
    listWidget->addItem(QString::number(i) + "item");
  }

  layout->addWidget(listWidget);

  master->setLayout(layout);

  setCentralWidget(master);

 // setupGUI();
}
