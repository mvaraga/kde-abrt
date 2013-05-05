#include <QListView>
#include <stdio.h>
#include <KLocalizedString>
#include "mainwindow.h"
#include "dbus.h"

MainWindow::MainWindow(QWidget* parent) : KXmlGuiWindow(parent)
{
    allProblems = false;
    dbus = new Dbus();

    buttonGetProblems = new KPushButton(i18n("get problems"), this);
    buttonGetAllProblems = new KPushButton(i18n("get all problems"), this);
    buttonDelete = new KPushButton(i18n("delete problem"), this);
    buttonReport = new KPushButton(i18n("report problem"), this);

    connect(buttonGetProblems, SIGNAL(clicked(bool)), this, SLOT(on_buttonGetProblems_clicked()));
    connect(buttonGetAllProblems, SIGNAL(clicked(bool)), this, SLOT(on_buttonGetAllProblems_clicked()));
    connect(buttonDelete, SIGNAL(clicked(bool)), this, SLOT(on_buttonDelete_clicked()));
    connect(buttonReport, SIGNAL(clicked(bool)), this, SLOT(on_buttonReport_clicked()));

    widget = new QWidget;
    master = new QWidget;
    //layout = new QVBoxLayout;
    hLayout = new QHBoxLayout;
    vLeftLayout = new QVBoxLayout;
    vRightLayout = new QVBoxLayout;
    hRightLayout = new QHBoxLayout;
    labelDescription = new QLabel("labelDescription");
    label1 = new QLabel("label1");
    label2 = new QLabel("label2");
    label3 = new QLabel("label3");
    label4 = new QLabel("label4");



    listWidget = new KListWidget();

    listWidget->setSelectionMode(KListWidget::ExtendedSelection);
    searchLine = new KListWidgetSearchLine(this, listWidget);

    getProblems();

    vLeftLayout->addWidget(searchLine);
    vLeftLayout->addWidget(listWidget);
    vLeftLayout->addWidget(buttonGetProblems);
    vLeftLayout->addWidget(buttonGetAllProblems);
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

    setCentralWidget(master);

    connect(listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
            this, SLOT(on_listWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*))
           );

// setupGUI();
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem* item, QListWidgetItem*)
{
    if (item == NULL) return;

    labelDescription->setText(item->data(Qt::UserRole).toString()); //executable
    label1->setText(item->data(Qt::UserRole + 1).toString()); //pkg_name
    QString timeInString = item->data(Qt::UserRole + 2).toString();
    uint timeInInt = timeInString.toUInt();
    label2->setText(QDateTime::fromTime_t(timeInInt).toString()); //time
    label3->setText(item->data(Qt::UserRole + 3).toString()); //count
    label4->setText(item->data(Qt::UserRole + 4).toString()); //id

    fprintf(stderr , "%s\n", qPrintable(item->data(Qt::UserRole + 4).toString()));              //debug
}

void MainWindow::on_buttonGetProblems_clicked()
{
    getProblems();
}

void MainWindow::on_buttonGetAllProblems_clicked()
{
    getAllProblems();
}

void MainWindow::on_buttonDelete_clicked()
{
    QList<QListWidgetItem*> list = listWidget->selectedItems();
    QListWidgetItem* item;
    QStringList* stringList = new QStringList();

    if (list.isEmpty()) {
        fprintf(stderr, "warning: no item(s) selected\n");
        return;
    }
    if (list.size() == 1) {
        item = list.at(0);
        dbus->deleteProblem(new QStringList(item->data(Qt::UserRole + 4).toString()));
    } else {
        foreach (item, list) {
            stringList->append(item->text());
            dbus->deleteProblem(stringList);
        }
    }
    getAllProblems(allProblems);
}

void MainWindow::on_buttonReport_clicked()
{
    QList<QListWidgetItem*> list = listWidget->selectedItems();
    QStringList stringList;
    if (list.isEmpty()) {
        fprintf(stderr, "warning: no item(s) selected\n");
        return;
    }

    if (list.size() == 1) {
        printf(LIBEXEC_DIR"/abrt-handle-event");
        stringList.append("-e");
        stringList.append("report-gui");
        stringList.append("--");
        stringList.append(list.first()->data(Qt::UserRole + 4).toString());

        QProcess::startDetached(LIBEXEC_DIR"/abrt-handle-event", stringList);
    }
}

void MainWindow::getProblems()
{
    getAllProblems(false);
}

void MainWindow::getAllProblems(bool allProblems)
{
    QList<ProblemData*>* list = dbus->getProblems(allProblems);

    if (list->empty()) {
        fprintf(stderr, "empty list");
    }

    listWidget->clear();                                      //remove duplicates

    ProblemData* item;
    QListWidgetItem* widgetItem;
    for (int i = 0; i < list->size(); i++) {
        item = list->at(i);
        widgetItem = new QListWidgetItem();
        widgetItem->setData(Qt::UserRole, item->getExecutable());
        widgetItem->setData(Qt::UserRole + 1, item->getPkg_name());
        widgetItem->setData(Qt::UserRole + 2, item->getTime());
        widgetItem->setData(Qt::UserRole + 3, item->getCount());
        widgetItem->setData(Qt::UserRole + 4, item->getID());

        //listWidget->addItem(widgetItem);
        QWidget* myWidget = new QWidget();
        QGridLayout* gridLayout = new QGridLayout();
        gridLayout->addWidget(new QLabel(item->getExecutable()), 0, 0);
        gridLayout->addWidget(new QLabel(item->getCount()), 0, 1);
        gridLayout->addWidget(new QLabel("botleft"), 1, 0);
        gridLayout->addWidget(new QLabel("botright"), 1, 1);
        myWidget->setLayout(gridLayout);
        widgetItem->setSizeHint(QSize(0, 40));
        listWidget->addItem(widgetItem);
        listWidget->setItemWidget(widgetItem, myWidget);
        listWidget->setAlternatingRowColors(true);
        delete(item);
    }
    delete(list);
}
