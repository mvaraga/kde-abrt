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
#include <KListWidget>
#include <KListWidgetSearchLine>
#include <KPushButton>
#include <QGridLayout>
#include <QSpacerItem>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>

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

    QLabel* labelTitle;
    QLabel* labelDescription;
    QLabel* labelText;
    QLabel* labelName;
    QLabel* labelVersion;
    QLabel* labelReported;
    QLabel* labelDetected;
    QLabel* labelNameValue;
    QLabel* labelVersionValue;
    QLabel* labelDetectedValue;
    QLabel* labelReportedValue;
    QSpacerItem* spacerHorizontal;
    QSpacerItem* spacerVertical;

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

//      getProblemsAction->setShortcut(Qt::CTRL + Qt::Key_W);
//      connect(clearAction, SIGNAL(triggered(bool)),
//           textArea, SLOT(clear()));
//      KStandardAction::quit(kapp, SLOT(quit()),
//                        MainWindow->actionCollection());

        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        hLayout = new QHBoxLayout(centralWidget);
        hLayout->setObjectName("hLayout");
        vLeftLayout = new QVBoxLayout();
        vLeftLayout->setObjectName("vLeftLayout");

        listWidget = new KListWidget(MainWindow);
        listWidget->setObjectName("listWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        listWidget->setMinimumSize(QSize(300, 0));
        listWidget->setMaximumSize(QSize(300, 16777215));
        listWidget->setAlternatingRowColors(true);

        searchLine = new CustomSearchLine(MainWindow, listWidget);
        searchLine->setObjectName("searchLine");
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

        spacerHorizontal = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
        hLayout->addItem(spacerHorizontal);

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
        labelTitle = new QLabel("labelTitle", centralWidget);
        labelText = new QLabel("labelText", centralWidget);
        labelName = new QLabel("Name", centralWidget);
        labelVersion = new QLabel("Version", centralWidget);
        labelDetected = new QLabel("Detected", centralWidget);
        labelReported = new QLabel("Reported", centralWidget);
        labelNameValue = new QLabel("labelNameValue", centralWidget);
        labelVersionValue = new QLabel("labelVersionValue", centralWidget);
        labelDetectedValue = new QLabel("labelDetectedValue", centralWidget);
        labelReportedValue = new QLabel("labelReportedValue", centralWidget);
        labelName->setAlignment(Qt::AlignRight);
        labelVersion->setAlignment(Qt::AlignRight);
        labelReported->setAlignment(Qt::AlignRight);
        labelDetected->setAlignment(Qt::AlignRight);
        labelTitle->setAlignment(Qt::AlignTop);
        labelDescription->setAlignment(Qt::AlignTop);
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelDescription->sizePolicy().hasHeightForWidth());
        labelDescription->setSizePolicy(sizePolicy2);

//set font
        QFont font = labelTitle->font();
        font.setPointSize(font.pointSize() * 1.2);
        font.setBold(true);
        labelTitle->setFont(font);

        vRightLayout->addWidget(labelTitle);
        spacerVertical = new QSpacerItem(100, 100, QSizePolicy::Fixed, QSizePolicy::Fixed);
        //vRightLayout->addItem(spacerVertical);
        vRightLayout->addWidget(labelDescription);




        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        labelVersionValue->setMinimumWidth(300);
        gridLayout->addWidget(labelName, 0, 0);
        gridLayout->addWidget(labelVersion, 1, 0);
        gridLayout->addWidget(labelDetected, 2, 0);
        gridLayout->addWidget(labelReported, 3, 0);
        gridLayout->addWidget(labelNameValue, 0, 1);
        gridLayout->addWidget(labelVersionValue, 1, 1);
        gridLayout->addWidget(labelDetectedValue, 2, 1);
        gridLayout->addWidget(labelReportedValue, 3, 1);

        vRightLayout->addLayout(gridLayout);

        vRightLayout->addWidget(labelText);

        hLayout->addLayout(vRightLayout);

        MainWindow->setCentralWidget(centralWidget);

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
