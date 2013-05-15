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

namespace Ui
{
class MainWindow;
}

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow* ui;

    void getProblems();
    void getAllProblems(bool allProblems = true);

private slots:
    void on_buttonGetProblems_clicked();
    void on_buttonGetAllProblems_clicked();
    void on_buttonDelete_clicked();
    void on_buttonReport_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*);

    void crash(const QString&, const QString&, const QString&);
};

#endif
