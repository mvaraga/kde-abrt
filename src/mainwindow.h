#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <KListWidget>
#include <KListWidgetSearchLine>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QLabel>
#include <KPushButton>
#include "customsearchline.h"
#include "problemdata.h"

class Dbus;

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);

private:
    void getProblems();
    void getAllProblems(bool allProblems = true);

    QWidget* master;
    KListWidget* listWidget; //widget
    QVBoxLayout* layout;
    QHBoxLayout* hLayout;
    QVBoxLayout* vLeftLayout;
    QVBoxLayout* vRightLayout;
    QHBoxLayout* hRightLayout;
    QWidget* widget;
    KPushButton* buttonGetProblems;
    KPushButton* buttonGetAllProblems;
    KPushButton* buttonDelete;
    KPushButton* buttonReport;
    KListWidgetSearchLine* searchLine;

    QLabel* labelDescription;
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QLabel* label4;

    Dbus* dbus;

    bool allProblems;

private slots:
    void on_buttonGetProblems_clicked();
    void on_buttonGetAllProblems_clicked();
    void on_buttonDelete_clicked();
    void on_buttonReport_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*);

    void crash(const QString &, const QString &, const QString &);
};

#endif
