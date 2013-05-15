#include <KLocalizedString>
#include <KDebug>
#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbus.h"

MainWindow::MainWindow(QWidget* parent) : KXmlGuiWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->getProblems();
    QDBusConnection::systemBus().connect(QString(), "/org/freedesktop/problems", "org.freedesktop.problems", "Crash",
                                         this, SLOT(crash(const QString&, const QString&, const QString&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem* item, QListWidgetItem*)
{
    if (item == NULL) return;

    ui->labelDescription->setText(item->data(Qt::UserRole).toString()); //executable
    ui->label1->setText(item->data(Qt::UserRole + 1).toString()); //pkg_name
    QString timeInString = item->data(Qt::UserRole + 2).toString();
    uint timeInInt = timeInString.toUInt();
    ui->label2->setText(QDateTime::fromTime_t(timeInInt).toString()); //time
    ui->label3->setText(item->data(Qt::UserRole + 3).toString()); //count
    ui->label4->setText(item->data(Qt::UserRole + 4).toString()); //id
    qDebug(qPrintable(item->data(Qt::UserRole + 4).toString()));
}

void MainWindow::on_buttonDelete_clicked()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    QListWidgetItem* item;
    QStringList* stringList = new QStringList();

    if (list.isEmpty()) {
        qDebug("warning: no item(s) selected");
        return;
    }
    if (list.size() == 1) {
        item = list.at(0);
        ui->dbus->deleteProblem(new QStringList(item->data(Qt::UserRole + 4).toString()));
    } else {
        foreach (item, list) {
            stringList->append(item->text());
            ui->dbus->deleteProblem(stringList);
        }
    }
    getAllProblems(ui->allProblems);
}

void MainWindow::on_buttonReport_clicked()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
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
//
void MainWindow::getAllProblems(bool allProblems)
{
    ui->allProblems = allProblems;
    QList<ProblemData*>* list = ui->dbus->getProblems(ui->allProblems);

    if (list->empty()) {
        qDebug("empty list");
    }

    ui->listWidget->clear();                                      //remove duplicates

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
        ui->listWidget->addItem(widgetItem);
        ui->listWidget->setItemWidget(widgetItem, myWidget);
        ui->listWidget->setAlternatingRowColors(true);
        delete(item);
    }
    delete(list);
}

void MainWindow::crash(const QString& , const QString& , const QString&)
{
    getAllProblems(ui->allProblems);
}

void MainWindow::setupActions()
{
    KAction* getProblemsAction = new KAction(this);
    getProblemsAction->setText(i18n("&Get all problems"));
    getProblemsAction->setIcon(KIcon("document-new"));
    getProblemsAction->setShortcut(Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("getProblems", getProblemsAction);
//   connect(clearAction, SIGNAL(triggered(bool)),
//           textArea, SLOT(clear()));

//   KStandardAction::quit(app, SLOT(quit()),
//                         actionCollection());

    setupGUI(Default, "kde-abrtui.rc");
}

void MainWindow::on_getProblemsAction_triggered(bool check)
{
    if (check) {
        this->getProblems();
        if (ui->getAllProblemsAction->isChecked()) {
            ui->getAllProblemsAction->setChecked(false);
        }
    } else {
        ui->getProblemsAction->setChecked(true);
    }
}

void MainWindow::on_getAllProblemsAction_triggered(bool check)
{
    if (check) {
        this->getAllProblems();
        if (ui->getProblemsAction->isChecked()) {
            ui->getProblemsAction->setChecked(false);
        }
    } else {
        ui->getAllProblemsAction->setChecked(true);
    }
}
