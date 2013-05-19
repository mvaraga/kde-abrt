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

    Dbus* m_dbus;

    bool m_allProblems;

    KAction* getAllProblemsAction;
    KAction* getProblemsAction;

    void setupUi(KXmlGuiWindow* MainWindow) {

        m_allProblems = false;
        m_dbus = new Dbus();

        getProblemsAction = new KAction(MainWindow);
        getAllProblemsAction = new KAction(MainWindow);
        getProblemsAction->setText(i18n("Get Problems"));
        getAllProblemsAction->setText(i18n("Get All Problems"));
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
        centralWidget->setMinimumSize(700, 400);
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

        spacerHorizontal = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
        hLayout->addItem(spacerHorizontal);

        vRightLayout = new QVBoxLayout();
        vRightLayout->setObjectName("vRightLayout");
        hRightLayout = new QHBoxLayout();
        hRightLayout->setObjectName("hRightLayout");

        buttonDelete = new KPushButton(i18n("Delete"), centralWidget);
        buttonReport = new KPushButton(i18n("Report"), centralWidget);
        buttonDelete->setObjectName("buttonDelete");
        buttonReport->setObjectName("buttonReport");

        hRightLayout->addWidget(buttonDelete);
        hRightLayout->addWidget(buttonReport);

        vRightLayout->addLayout(hRightLayout);

        labelDescription = new QLabel(centralWidget);
        labelTitle = new QLabel(centralWidget);
        labelText = new QLabel(centralWidget);
        labelName = new QLabel("<font color='#87877e7e8080'>" + i18n("Name") + "</font>", centralWidget);
        labelVersion = new QLabel("<font color='#87877e7e8080'>" + i18n("Version") + "</font>", centralWidget);
        labelDetected = new QLabel("<font color='#87877e7e8080'>" + i18n("Detected") + "</font>", centralWidget);
        labelReported = new QLabel("<font color='#87877e7e8080'>" + i18n("Reported") + "</font>", centralWidget);
        labelNameValue = new QLabel(centralWidget);
        labelVersionValue = new QLabel(centralWidget);
        labelDetectedValue = new QLabel(centralWidget);
        labelReportedValue = new QLabel(centralWidget);
        labelReportedValue->setOpenExternalLinks(true);
        labelName->setAlignment(Qt::AlignRight);
        labelName->setMargin(2);
        labelName->setIndent(6);
        labelVersion->setAlignment(Qt::AlignRight);
        labelVersion->setMargin(2);
        labelVersion->setIndent(6);
        labelReported->setAlignment(Qt::AlignRight);
        labelReported->setMargin(2);
        labelReported->setFixedHeight(50);
        labelReportedValue->setFixedHeight(50);
        labelReportedValue->setAlignment(Qt::AlignLeft);
        labelReported->setIndent(6);
        labelDetected->setAlignment(Qt::AlignRight);
        labelDetected->setMargin(2);
        labelDetected->setIndent(6);
        labelTitle->setAlignment(Qt::AlignTop);
        labelTitle->setIndent(30);

        labelDescription->setAlignment(Qt::AlignBottom);
        labelDescription->setIndent(30);
        labelDescription->setWordWrap(true);
        labelText->setWordWrap(true);

        //set font
        QFont font = labelTitle->font();
        font.setPointSize(font.pointSize() * 1.2);
        font.setBold(true);
        labelTitle->setFont(font);

        vRightLayout->addWidget(labelTitle);
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
