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
    QString reported_to = parseReported_to(item->data(Qt::UserRole + 5).toString());
    ui->labelTitle->setText(item->data(Qt::UserRole + 1).toString() + i18n(" crashed")); //name
    QString timeInString = item->data(Qt::UserRole + 2).toString();
    uint timeInInt = timeInString.toUInt();
    ui->labelDetectedValue->setText(QDateTime::fromTime_t(timeInInt).date().toString(Qt::DefaultLocaleShortDate)); //time
    ui->labelReportedValue->setText(reported_to); //reported_to
    ui->labelVersionValue->setText(item->data(Qt::UserRole + 6).toString()); //package
    ui->labelNameValue->setText(item->data(Qt::UserRole + 1).toString()); //name
    ui->labelDescription->setText(item->data(Qt::UserRole + 8).toString()); //reason
    if (reported_to.compare("no") == 0 || reported_to.compare("yes") == 0) {
        ui->labelText->setText(i18n("This problem hasn't been reported to <i>Bugzilla</i> yet. "
                                    "Our developers may need more information to fix the problem.\n"
                                    "Please consider <b>reporting it</b> - you may help them. Thank you."));
    } else {
        ui->labelText->clear();
    }
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
        QString problem = list.first()->data(Qt::UserRole + 4).toString();
        item = list.first();
        if (ui->m_allProblems == true) {
            ui->m_dbus->chownProblem(problem);
        }

        ui->m_dbus->deleteProblem(new QStringList(problem));
    } else {
        foreach (item, list) {
            stringList->append(item->text());
            ui->m_dbus->deleteProblem(stringList);
        }
    }
    getAllProblems(ui->m_allProblems);
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
        QString problem = list.first()->data(Qt::UserRole + 4).toString();
        stringList.append("-e");
        stringList.append("report-gui");
        stringList.append("--");
        stringList.append(problem);
        if (ui->m_allProblems == true) {
            ui->m_dbus->chownProblem(problem);
        }
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
    ui->m_allProblems = allProblems;
    QList<ProblemData*>* list = ui->m_dbus->getProblems(ui->m_allProblems);

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

        QWidget* myWidget = new QWidget();
        QGridLayout* gridLayout = new QGridLayout();
        QLabel* label;

        gridLayout->addWidget(new QLabel(item->pkg_name(), ui->centralWidget), 0, 0);
        label = new QLabel(getFancyDate(QDateTime::fromTime_t(item->time().toUInt())), ui->centralWidget);
        label->setAlignment(Qt::AlignRight);
        label->setIndent(5);
        gridLayout->addWidget(label, 0, 1);
        gridLayout->addWidget(new QLabel(item->type(), ui->centralWidget), 1, 0);
        label = new QLabel(item->count(), ui->centralWidget);
        label->setAlignment(Qt::AlignRight);
        label->setIndent(5);
        gridLayout->addWidget(label, 1, 1);
        myWidget->setLayout(gridLayout);
        widgetItem->setSizeHint(QSize(0, 45));
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
    getAllProblems(ui->m_allProblems);
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
        return i18n("no");
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
    return i18n("yes");
}

void MainWindow::processFinished(int , QProcess::ExitStatus)
{
    getAllProblems(ui->m_allProblems);
    qDebug("reporting process finished");
}

QString MainWindow::getFancyDate(QDateTime value)
{
    QDateTime base = QDateTime::currentDateTime();
    QDate baseDate = base.date();
    QDate valueDate = value.date();
    QString name;
    int offset;
    if (base < value)
        return i18n("Future"); //never should happen
    int days = valueDate.daysTo(baseDate);
    if (days == 0)
        return value.time().toString();
    else if (days == 1)
        return i18n("Yesterday");
    if (days < baseDate.dayOfWeek())
        return QDate::longDayName(valueDate.dayOfWeek());
    if (valueDate.month() == baseDate.month() && valueDate.year() == baseDate.year()) {
        offset = qRound((days - baseDate.dayOfWeek()) / 7) + 1;
        return i18np("Last week", "%1 weeks ago", offset);
    } else if (valueDate.year() == baseDate.year()) {
        offset = baseDate.month() - valueDate.month();
        return i18np("Last month", "%1 months ago", offset);
    } else {
        offset = baseDate.year() - valueDate.year();
        return i18np("Last year", "%1 years ago", offset);
    }
}
