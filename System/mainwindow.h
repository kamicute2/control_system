#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "form.h"
#include "visitor.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_editButon_clicked();

public slots:
    //void receiveData(Visitor);
signals:
    //void sendData(Visitor);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QSqlTableModel *sqlmodel;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
