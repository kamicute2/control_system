#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include "visitor.h"

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "localhost"
#define DATABASE_NAME       "db.db"

#define TABLE               "ClientSystemTable"

#define TABLE_CURRENT_DATE  "CurDate"
#define TABLE_NAME          "Name"
#define TABLE_PHONE         "Phone"
#define TABLE_PRODUCT       "Product"
#define TABLE_PRICE         "Price"
#define TABLE_DATE          "Date"
#define TABLE_READY         "Ready"


class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    bool inserIntoTable(Visitor &visitor);
    //bool editIntoTable(Visitor &visitor);
    bool deleteIntoTable(int value);
private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};

#endif // DATABASE_H
