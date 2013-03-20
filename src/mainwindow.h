#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <KListWidget>
#include <KListWidgetSearchLine>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QLabel>
#include <KPushButton>
#include "problemdata.h"

class QListView;
class Dbus;

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);

private:
    QWidget* master;
    KListWidget* listWidget; //widget
    QVBoxLayout* layout;
    QHBoxLayout* hLayout;
    QVBoxLayout* vLeftLayout;
    QVBoxLayout* vRightLayout;
    QHBoxLayout* hRightLayout;
    QWidget* widget;
    KPushButton* buttonConnection;
    KPushButton* buttonGetAllProblems;
    KPushButton* buttonDelete;
    KPushButton* buttonReport;
    KListWidgetSearchLine* searchLine;

    QLabel* labelName;
    QLabel* labelDescription;
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;

    Dbus* dbus;

private slots:
    void on_buttonConnect_clicked();
    void on_buttonGetAllProblems_clicked();
    void on_buttonDelete_clicked();
    void on_buttonReport_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*);
};

#endif
