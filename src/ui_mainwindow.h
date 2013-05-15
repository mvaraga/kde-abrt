#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <KLocalizedString>
#include <KDebug>
#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <KXmlGuiWindow>
#include "dbus.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget* master;
    KListWidget* listWidget;
    QVBoxLayout* layout;
    QHBoxLayout* hLayout;
    QVBoxLayout* vLeftLayout;
    QVBoxLayout* vRightLayout;
    QHBoxLayout* hRightLayout;
    QWidget* widget;
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

    KAction* getAllProblemsAction;
    KAction* getProblemsAction;

    void setupUi(KXmlGuiWindow* MainWindow) {

        getProblemsAction = new KAction(MainWindow);
        getAllProblemsAction = new KAction(MainWindow);
        getProblemsAction->setText(i18n("&Get Problems"));
        getAllProblemsAction->setText(i18n("Get &All Problems"));
        MainWindow->actionCollection()->addAction("getProblems", getProblemsAction);
        MainWindow->actionCollection()->addAction("getAllProblems", getAllProblemsAction);
        getProblemsAction->setIcon(KIcon("document-new")); //bad icon
        getAllProblemsAction->setIcon(KIcon("document-new")); //bad icon
        getProblemsAction->setCheckable(true);
        getAllProblemsAction->setCheckable(true);

        getProblemsAction->setObjectName("getProblemsAction");
        getAllProblemsAction->setObjectName("getAllProblemsAction");

        getProblemsAction->setChecked(true);

//      getProblemsAction->setShortcut(Qt::CTRL + Qt::Key_W);
//      connect(clearAction, SIGNAL(triggered(bool)),
//           textArea, SLOT(clear()));
//      KStandardAction::quit(kapp, SLOT(quit()),
//                        MainWindow->actionCollection());

        allProblems = false;
        dbus = new Dbus();

        listWidget = new KListWidget(MainWindow);
        buttonDelete = new KPushButton(i18n("delete problem"), MainWindow);
        buttonReport = new KPushButton(i18n("report problem"), MainWindow);
        buttonDelete->setObjectName("buttonDelete");
        buttonReport->setObjectName("buttonReport");
        listWidget->setObjectName("listWidget");

        widget = new QWidget;
        master = new QWidget;
        hLayout = new QHBoxLayout;
        vLeftLayout = new QVBoxLayout;
        vRightLayout = new QVBoxLayout;
        hRightLayout = new QHBoxLayout;
        labelDescription = new QLabel("labelDescription");
        label1 = new QLabel("label1");
        label2 = new QLabel("label2");
        label3 = new QLabel("label3");
        label4 = new QLabel("label4");

        listWidget->setSelectionMode(KListWidget::ExtendedSelection);
        searchLine = new CustomSearchLine(MainWindow, listWidget);

        vLeftLayout->addWidget(searchLine);
        vLeftLayout->addWidget(listWidget);
        widget->setLayout(vLeftLayout);
        widget->setMinimumWidth(400);
        widget->setMaximumWidth(400);
        hLayout->addWidget(widget);
        vRightLayout->addWidget(labelDescription);
        vRightLayout->addWidget(label1);
        vRightLayout->addWidget(label2);
        vRightLayout->addWidget(label3);
        vRightLayout->addWidget(label4);

        hRightLayout->addWidget(buttonDelete);
        hRightLayout->addWidget(buttonReport);
        vRightLayout->addLayout(hRightLayout);

        hLayout->addLayout(vRightLayout);

        master->setLayout(hLayout);

        MainWindow->setCentralWidget(master);

        QMetaObject::connectSlotsByName(MainWindow);
        MainWindow->setupGUI(KXmlGuiWindow::StandardWindowOption::Default, "kde-abrtui.rc");

    } // setupUi
};

namespace Ui
{
class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H
