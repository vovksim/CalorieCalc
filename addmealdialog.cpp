#include "addmealdialog.h"
#include "ui_addmealdialog.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

addMealDialog::addMealDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addMealDialog)
{
    ui->setupUi(this);
    categoryToAdd = ui->addingCategory->currentText();
}

addMealDialog::~addMealDialog()
{
    addMealDialog::mealInfoDb->removeDatabase("mealInfoCon");
    delete ui;
}

bool addMealDialog::notEnoughMealData() {
    if(ui->mealLineEdit->text()=="" or ui->carbsLineEdit->text().toInt()<0 or
        ui->proteinsLineEdit->text().toInt()<0 or ui->fatsLineEdit->text().toInt()<0) {
        return true;
    }
    return false;
}

void addMealDialog::connectDb(QString&& path) {
    addMealDialog::mealInfoDb = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE","mealInfoCon"));
    addMealDialog::mealInfoDb->setDatabaseName(path);
    if(!mealInfoDb->isOpen()) {
        mealInfoDb->open();
    }
}

void addMealDialog::on_saveMeal_clicked()
{
    qDebug() << categoryToAdd;
    connectDb("C:/Users/Ivan/Documents/CalorieCalculator/database/calorieCalc.db");
    QDate currentDate;
    QSqlQuery query(*addMealDialog::mealInfoDb);
    if(mealInfoDb->isValid() && !notEnoughMealData()) {
        query.bindValue(":TableName", categoryToAdd);
        query.prepare("insert into "+categoryToAdd+" (Meal, kCal, PortionSize, Carbohydrates, Proteins, Fats, Date) values(:Meal, :kCal, :PortionSize, :Carbohydrates, :Proteins, :Fats, :Date)");
        query.bindValue(":Meal", ui->mealLineEdit->text());
        query.bindValue(":PortionSize",ui->portionLineEdit->text());
        query.bindValue(":kCal", ui->kCalLineEdit->text());
        query.bindValue(":Carbohydrates", ui->carbsLineEdit->text().toInt());
        query.bindValue(":Proteins", ui->proteinsLineEdit->text().toInt());
        query.bindValue(":Fats", ui->fatsLineEdit->text().toInt());
        query.bindValue(":Date", currentDate.currentDate().toString());
        if(!query.exec()) {
            qDebug() << query.lastError();
        }
    } else {
        QMessageBox::critical(this,tr("Error"), "Incorrect data!");
    }
    mealInfoDb->close();
    delete(mealInfoDb);
    accept();
}


void addMealDialog::on_addingCategory_activated(int index)
{
    categoryToAdd = ui->addingCategory->currentText();
}

