#include <QListView>
#include <stdio.h>
#include "mainwindow.h"
#include "dbus.h"

MainWindow::MainWindow(QWidget* parent) : KXmlGuiWindow(parent)
{
    buttonGetProblems = new KPushButton("get problems", this);
    buttonGetAllProblems = new KPushButton("get all problems", this);
    buttonDelete = new KPushButton("delete problem", this);
    buttonReport = new KPushButton("report problem", this);

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
    labelName = new QLabel("label");
    labelDescription = new QLabel("label");
    label1 = new QLabel();
    label2 = new QLabel();
    label3 = new QLabel();

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
    vRightLayout->addWidget(labelName);
    vRightLayout->addWidget(labelDescription);
    vRightLayout->addWidget(label1);
    vRightLayout->addWidget(label2);
    vRightLayout->addWidget(label3);

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
    QString text = item->text();
    //QString desc = item->data(Qt::UserRole).toString();
    //executable
    labelDescription->setText(item->data(Qt::UserRole).toString());
    label1->setText(item->data(Qt::UserRole + 1).toString()); //pkg_name
    label2->setText(item->data(Qt::UserRole + 2).toString()); //time
    label3->setText(item->data(Qt::UserRole + 3).toString()); //count
    labelName->setText(text);
    //labelDescription->setText();

    fprintf(stderr , "%s\n", qPrintable(text));               //debug
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
        Dbus::deleteProblem(new QStringList(item->text()));
    } else {
        foreach (item, list) {
            stringList->append(item->text());
            Dbus::deleteProblem(stringList);
        }
        return;
    }
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
        stringList.append(list.first()->text());

        QProcess::startDetached(LIBEXEC_DIR"/abrt-handle-event", stringList);
    }
}

void MainWindow::getProblems()
{
    getAllProblems(false);
}

void MainWindow::getAllProblems(bool allProblems)
{
    QList<ProblemData*>* list = Dbus::getProblems(allProblems);

    if (list->empty()) {
        fprintf(stderr, "empty list");
    }

    listWidget->clear();                                      //remove duplicates

    ProblemData* item;
    QListWidgetItem* widgetItem;
    for (int i = 0; i < list->size(); i++) {
        item = list->at(i);
        widgetItem = new QListWidgetItem(item->getName());
        widgetItem->setData(Qt::UserRole, item->getExecutable());
        widgetItem->setData(Qt::UserRole + 1, item->getPkg_name());
        widgetItem->setData(Qt::UserRole + 2, item->getTime());
        widgetItem->setData(Qt::UserRole + 3, item->getCount());

        listWidget->addItem(widgetItem);
        delete(item);
    }
    delete(list);
}
