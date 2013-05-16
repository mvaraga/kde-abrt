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
#include <QGridLayout>
#include "dbus.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget* centralWidget;
    KListWidget* listWidget;
    QVBoxLayout* layout;
    QHBoxLayout* hLayout;
    QVBoxLayout* vLeftLayout;
    QVBoxLayout* vRightLayout;
    QHBoxLayout* hRightLayout;
    QGridLayout* gridLayout;
    QWidget* widget;
    KPushButton* buttonDelete;
    KPushButton* buttonReport;
    KListWidgetSearchLine* searchLine;

    QLabel* labelDescription;
    QLabel* label1;
    QLabel* labelName;
    QLabel* labelVersion;
    QLabel* labelReported;
    QLabel* labelDetected;
    QLabel* labelNameValue;
    QLabel* labelVersionValue;
    QLabel* labelDetectedValue;
    QLabel* labelReportedValue;

    Dbus* dbus;

    bool allProblems;

    KAction* getAllProblemsAction;
    KAction* getProblemsAction;

    void setupUi(KXmlGuiWindow* MainWindow) {

        allProblems = false;
        dbus = new Dbus();

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

        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        hLayout = new QHBoxLayout(centralWidget);
        hLayout->setObjectName("hLayout");
        vLeftLayout = new QVBoxLayout();
        vLeftLayout->setObjectName("vLeftLayout");

        listWidget = new KListWidget(MainWindow);
        listWidget->setObjectName("listWidget");
        listWidget->setSelectionMode(KListWidget::ExtendedSelection);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        listWidget->setMinimumSize(QSize(300, 0));
        listWidget->setMaximumSize(QSize(300, 16777215));
        listWidget->setAlternatingRowColors(true);

        searchLine = new CustomSearchLine(MainWindow, listWidget);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(searchLine->sizePolicy().hasHeightForWidth());
        searchLine->setSizePolicy(sizePolicy);
        searchLine->setMinimumSize(QSize(300, 0));
        searchLine->setMaximumSize(QSize(300, 16777215));

        vLeftLayout->addWidget(searchLine);
        vLeftLayout->addWidget(listWidget);

        hLayout->addLayout(vLeftLayout);

        vRightLayout = new QVBoxLayout();
        vRightLayout->setObjectName("vRightLayout");
        hRightLayout = new QHBoxLayout();
        hRightLayout->setObjectName("hRightLayout");

        buttonDelete = new KPushButton(i18n("delete problem"), centralWidget);
        buttonReport = new KPushButton(i18n("report problem"), centralWidget);
        buttonDelete->setObjectName("buttonDelete");
        buttonReport->setObjectName("buttonReport");

        hRightLayout->addWidget(buttonDelete);
        hRightLayout->addWidget(buttonReport);

        vRightLayout->addLayout(hRightLayout);



        labelDescription = new QLabel("labelDescription", centralWidget);
        label1 = new QLabel("label1", centralWidget);
        labelName = new QLabel("Name", centralWidget);
        labelVersion = new QLabel("Version", centralWidget);
        labelDetected = new QLabel("Detected", centralWidget);
        labelReported = new QLabel("Reported", centralWidget);
        labelNameValue = new QLabel("labelNameValue", centralWidget);
        labelVersionValue = new QLabel("labelVersionValue", centralWidget);
        labelDetectedValue = new QLabel("labelDetectedValue", centralWidget);
        labelReportedValue = new QLabel("labelReportedValue", centralWidget);

        vRightLayout->addWidget(labelDescription);
        vRightLayout->addWidget(label1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");

        gridLayout->addWidget(labelName, 0, 0);
        gridLayout->addWidget(labelVersion, 1, 0);
        gridLayout->addWidget(labelDetected, 2, 0);
        gridLayout->addWidget(labelReported, 3, 0);
        gridLayout->addWidget(labelNameValue, 0, 1);
        gridLayout->addWidget(labelVersionValue, 1, 1);
        gridLayout->addWidget(labelDetectedValue, 2, 1);
        gridLayout->addWidget(labelReportedValue, 3, 1);

        vRightLayout->addLayout(gridLayout);






        hLayout->addLayout(vRightLayout);

        MainWindow->setCentralWidget(centralWidget);



//      getProblemsAction->setShortcut(Qt::CTRL + Qt::Key_W);
//      connect(clearAction, SIGNAL(triggered(bool)),
//           textArea, SLOT(clear()));
//      KStandardAction::quit(kapp, SLOT(quit()),
//                        MainWindow->actionCollection());





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
