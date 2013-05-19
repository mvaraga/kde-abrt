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
    /*
        (Qt::UserRole, item->executable());
        (Qt::UserRole + 1, item->pkg_name());
        (Qt::UserRole + 2, item->time());
        (Qt::UserRole + 3, item->count());
        (Qt::UserRole + 4, item->id());
        (Qt::UserRole + 5, item->reported_to());
        (Qt::UserRole + 6, item->package());*/
    ui->labelTitle->setText(item->data(Qt::UserRole + 1).toString() + i18n(" crashed")); //name
    QString timeInString = item->data(Qt::UserRole + 2).toString();
    uint timeInInt = timeInString.toUInt();
    ui->labelDetectedValue->setText(QDateTime::fromTime_t(timeInInt).toString()); //time
    ui->labelReportedValue->setText(parseReported_to(item->data(Qt::UserRole + 5).toString())); //reported_to
    ui->labelVersionValue->setText(item->data(Qt::UserRole + 6).toString()); //package
    ui->labelNameValue->setText(item->data(Qt::UserRole + 1).toString()); //name
    ui->labelDescription->setText(item->data(Qt::UserRole + 8).toString()); //reason
    ui->labelDescription->setWordWrap(true);
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
        QProcess* process = new QProcess();
        process->start(LIBEXEC_DIR"/abrt-handle-event", stringList);
        connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
        qDebug("started reporting process");
        //QProcess::startDetached(LIBEXEC_DIR"/abrt-handle-event", stringList);
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
        widgetItem->setData(Qt::UserRole + 5, item->reported_to());
        widgetItem->setData(Qt::UserRole + 6, item->package());
        widgetItem->setData(Qt::UserRole + 7, item->type());
        widgetItem->setData(Qt::UserRole + 8, item->reason());

        //listWidget->addItem(widgetItem);
        QWidget* myWidget = new QWidget();
        QGridLayout* gridLayout = new QGridLayout();
        gridLayout->addWidget(new QLabel(item->pkg_name()), 0, 0);
        gridLayout->addWidget(new QLabel("topright"), 0, 1);
        gridLayout->addWidget(new QLabel(item->type()), 1, 0);
        gridLayout->addWidget(new QLabel(item->count()), 1, 1);
        myWidget->setLayout(gridLayout);
        widgetItem->setSizeHint(QSize(0, 40));
        ui->listWidget->addItem(widgetItem);
        ui->listWidget->setItemWidget(widgetItem, myWidget);
        delete(item);
    }
    if (ui->listWidget->count() > 0) {
        ui->listWidget->item(0)->setSelected(true);
    }
    delete(list);
}

void MainWindow::crash(const QString& , const QString& , const QString&)
{
    getAllProblems(ui->allProblems);
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

QString MainWindow::parseReported_to(const QString& reported_to) const
{

    if (reported_to.isEmpty()) {
        return "no";
    }
    if (reported_to.indexOf("URL=") != -1) {
        QStringList list = reported_to.split("\n");
        QStringList result;
        int index;
        QString subStr = ": URL=";
        foreach (const QString & str, list) {
            index = str.indexOf(subStr);
            if (index != -1)
                result += "<a href='" + str.mid(index + subStr.length()) + "' >" + str.left(index) + "</a>";
        }
        return result.join("\n<br />");

    }
    return "yes";
}

void MainWindow::processFinished(int , QProcess::ExitStatus)
{
    getAllProblems(ui->allProblems);
    qDebug("reporting process finished");
}
