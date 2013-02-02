#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <KListWidget>
#include <KListWidgetSearchLine>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QLabel>
#include <KPushButton>

class QListView;
class QAbstractListModel;
class Dbus;

class MainWindow : public KXmlGuiWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent=0);

  private:
    QWidget *master;
    KListWidget *listWidget; //widget
    QListWidgetItem *item; //widget
    QVBoxLayout *layout;
    KPushButton *buttonConnection;

    QLabel *labelName;
    QLabel *labelDescription;
    
    QListView *listView;
    QAbstractListModel *myModel;
    
    Dbus *dbus;


private slots:
    void on_listWidget_executed(QListWidgetItem *item); //widget
    void on_listView_activated(QModelIndex);
    void on_buttonConnect_clicked();
};

#endif
    
