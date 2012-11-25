#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <KListWidget>
#include <KListWidgetSearchLine>
#include <QListWidgetItem>
#include <QHBoxLayout>


class MainWindow : public KXmlGuiWindow
{

  public:
    MainWindow(QWidget *parent=0);

  private:
    QWidget *master;
    KListWidget *listWidget;
    QListWidgetItem *item;
    KListWidgetSearchLine *searchLine;
    QHBoxLayout *layout;

};

#endif
