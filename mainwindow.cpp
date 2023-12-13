#include "mainwindow.h"
#include "addmealdialog.h"
#include "./ui_mainwindow.h"
#include "qstandarditemmodel.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QStringListModel>
#include <QSqlError>
#include <QDebug>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fillListView();
}

void MainWindow::connectDb(QString&& path) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if(!MainWindow::db.isOpen()) {
        MainWindow::db.open();
    }
}

void MainWindow::fillListView() {
    connectDb("C:/Users/Ivan/Documents/CalorieCalculator/database/calorieCalc.db");
    auto * model = new QStandardItemModel(this);
    QStringList* tableList = new QStringList(db.tables().toList());
    tableList->sort();
    tableList->swapItemsAt(tableList->size()-1,tableList->size()-2);
    ui->listView->setModel(model);
    qDebug() << db.tables().toList();
    for(auto& iter : *tableList) {
        qDebug() << QString(iter.data());
        QIcon* iconBreakf = new QIcon("C:/Users/Ivan/Documents/CalorieCalculator/pics/"+QString(iter.data()).toLower()+".png");
        auto* itemToAdd = new QStandardItem(*iconBreakf, QString(iter.data()));
        model->appendRow(itemToAdd);
    }
    db.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_addMeal_clicked()
{
    addMealDialog* dialog = new addMealDialog();
    dialog->setModal(true);
    dialog->exec();
    delete(dialog);
}


void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QSqlQuery addQuery(db);
    if(!MainWindow::db.isOpen()) {
        MainWindow::db.open();
    }
    addQuery.bindValue(":Date",currentMonitoringDay.toString());
    addQuery.prepare(("SELECT Meal, PortionSize, kCal, Carbohydrates, Proteins, Fats, Date from "+index.data().toString())+" WHERE Date=('"+currentMonitoringDay.toString()+"')");
    if(addQuery.exec()) {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(std::move(addQuery));
    ui->tableView_2->setModel(model);
    } else {
        qDebug() << addQuery.lastError().text();
    }
    db.close();
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    currentMonitoringDay = date;
    qDebug() << date.toString();
}

