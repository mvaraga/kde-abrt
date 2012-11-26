#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <KListWidget>
#include <KListWidgetSearchLine>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QLabel>


class MainWindow : public KXmlGuiWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent=0);

  private:
    QWidget *master;
    KListWidget *listWidget;
    QListWidgetItem *item;
    KListWidgetSearchLine *searchLine;
    QVBoxLayout *layout;

    QLabel *labelName;
    QLabel *labelDescription;

private slots:
    void on_listWidget_executed(QListWidgetItem *item);

};

#endif
