#include <KLocalizedString>
#include <KDebug>
#include "mainwindow.h"
#include "dbus.h"

MainWindow::MainWindow(QWidget* parent) : KXmlGuiWindow(parent)
{
    allProblems = false;
    dbus = new Dbus();

    listWidget = new KListWidget(this);
    buttonGetProblems = new KPushButton(i18n("get problems"), this);
    buttonGetAllProblems = new KPushButton(i18n("get all problems"), this);
    buttonDelete = new KPushButton(i18n("delete problem"), this);
    buttonReport = new KPushButton(i18n("report problem"), this);
    buttonGetProblems->setObjectName("buttonGetProblems");
    buttonGetAllProblems->setObjectName("buttonGetAllProblems");
    buttonDelete->setObjectName("buttonDelete");
    buttonReport->setObjectName("buttonReport");
    listWidget->setObjectName("listWidget");
    
    QMetaObject::connectSlotsByName(this);

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
    searchLine = new CustomSearchLine(this, listWidget);

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

     QDBusConnection::systemBus().connect(QString(), "/org/freedesktop/problems", "org.freedesktop.problems", "Crash",
                                          this, SLOT(crash(const QString&, const QString&, const QString&)));

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
    qDebug(qPrintable(item->data(Qt::UserRole + 4).toString()));
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
        qDebug("warning: no item(s) selected");
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
        qDebug("warning: no item(s) selected");
        return;
    }

    if (list.size() == 1) {
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
    this->allProblems=allProblems;
    QList<ProblemData*>* list = dbus->getProblems(this->allProblems);

    if (list->empty()) {
        qDebug("empty list");
    }

    listWidget->clear();                                      //remove duplicates

    ProblemData* item;
    QListWidgetItem* widgetItem;
    for (int i = 0; i < list->size(); i++) {
        item = list->at(i);
        widgetItem = new QListWidgetItem();
        widgetItem->setData(Qt::UserRole, item->executable());
        widgetItem->setData(Qt::UserRole + 1, item->pkg_name());
        widgetItem->setData(Qt::UserRole + 2, item->time());
        widgetItem->setData(Qt::UserRole + 3, item->count());
        widgetItem->setData(Qt::UserRole + 4, item->id());

        //listWidget->addItem(widgetItem);
        QWidget* myWidget = new QWidget();
        QGridLayout* gridLayout = new QGridLayout();
        gridLayout->addWidget(new QLabel(item->executable()), 0, 0);
        gridLayout->addWidget(new QLabel(item->count()), 0, 1);
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

void MainWindow::crash(const QString& , const QString& , const QString&)
{
  getAllProblems(allProblems);
}