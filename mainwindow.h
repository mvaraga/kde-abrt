#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <KListWidget>
#include <KListWidgetSearchLine>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QLabel>

class QListView;
class QAbstractListModel;

class MainWindow : public KXmlGuiWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent=0);

  private:
    QWidget *master;
    KListWidget *listWidget; //old
    QListWidgetItem *item; //old
    QVBoxLayout *layout;

    QLabel *labelName;
    QLabel *labelDescription;
    
    QListView *listView;
    QAbstractListModel *myModel;

private slots:
    void on_listWidget_executed(QListWidgetItem *item); //old
    void on_listView_activated(QModelIndex);
};

#endif
    
