#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QtSql/QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void fillListView();
    ~MainWindow();
    void connectDb(QString&& path);
    QSqlDatabase db;
    QDate currentMonitoringDay=QDate::currentDate();
private slots:
    void on_addMeal_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
