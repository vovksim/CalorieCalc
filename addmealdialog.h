#ifndef ADDMEALDIALOG_H
#define ADDMEALDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addMealDialog;
}

class addMealDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addMealDialog(QWidget *parent = nullptr);
    ~addMealDialog();
    bool notEnoughMealData();
    QSqlDatabase* mealInfoDb;
    void connectDb(QString&& path);
    QString categoryToAdd;

private slots:
    void on_saveMeal_clicked();

    void on_comboBox_activated(int index);

    void on_addingCategory_activated(int index);

    void on_addingCategory_textActivated(const QString &arg1);

private:
    Ui::addMealDialog *ui;
};

#endif // ADDMEALDIALOG_H
