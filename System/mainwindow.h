#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include "form.h"
#include "report.h"
#include "visitor.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    reportData tableReport(int value);
    reportData tableReport(int value, int days);
private:
    void setupModel(const QString &tableName);
    void createUI();
private slots:
    void on_addButton_clicked();
    void on_editButon_clicked();

    void on_deleteButton_clicked();

    void on_makeReportButton_clicked();

public slots:
    //void receiveData(Visitor);
signals:
    //void sendData(Visitor);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QSqlTableModel *sqlmodel;
    DataBase        *db;
};
#endif // MAINWINDOW_H
