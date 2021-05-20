#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile("./" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("./" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            "id INTEGER PRIMARY KEY, "
                            TABLE_CURRENT_DATE  " DATE            NOT NULL,"
                            TABLE_NAME          " VARCHAR(255)    NOT NULL,"
                            TABLE_PHONE         " VARCHAR(255)    NOT NULL,"
                            TABLE_PRODUCT       " VARCHAR(255)    NOT NULL,"
                            TABLE_PRICE         " INTEGER         NOT NULL,"
                            TABLE_DATE          " VARCHAR(255)    NOT NULL,"
                            TABLE_READY         " VARCHAR(255)    NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 */
bool DataBase::inserIntoTable(Visitor &visitor)
{
    /* Запрос SQL формируется из Visitor,
    */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_CURRENT_DATE ", "
                                             TABLE_NAME ", "
                                             TABLE_PHONE ", "
                                             TABLE_PRODUCT ", "
                                             TABLE_PRICE ", "
                                             TABLE_DATE ", "
                                             TABLE_READY " ) "
                  "VALUES (:CurDate, :Name, :Phone, :Product, :Price, :Date, :Ready )");
    query.bindValue(":CurDate",     visitor.getCurDate().toString("d MMMM yyyy"));
    query.bindValue(":Name",        visitor.getName());
    query.bindValue(":Phone",      visitor.getPhone());
    query.bindValue(":Product",     visitor.getProduct());
    query.bindValue(":Price",     visitor.getPrice().toInt());
    query.bindValue(":Date",     visitor.getDate());
    query.bindValue(":Ready",     visitor.getReady());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
/* Метод для изменения записи в базе данных
 */
bool DataBase::editIntoTable(Visitor &visitor)
{
    QSqlQuery query;
    query.prepare("UPDATE " TABLE " SET "    TABLE_CURRENT_DATE  " =: " TABLE_CURRENT_DATE ", "
                                             TABLE_NAME " =: " TABLE_NAME ", "
                                             TABLE_PHONE " =: " TABLE_PHONE ", "
                                             TABLE_PRODUCT " =: " TABLE_PRODUCT ", "
                                             TABLE_PRICE " =: " TABLE_PRICE ", "
                                             TABLE_DATE " =: " TABLE_DATE ", "
                                             TABLE_READY " =: " TABLE_READY
                  "WHERE id=:id) ");
    query.bindValue(":TABLE_CURRENT_DATE",  visitor.getCurDate().toString("d MMMM yyyy"));
    query.bindValue(":Name",        visitor.getName());
    query.bindValue(":Phone",      visitor.getPhone());
    query.bindValue(":Product",     visitor.getProduct());
    query.bindValue(":Price",     visitor.getPrice().toInt());
    query.bindValue(":Date",     visitor.getDate());
    query.bindValue(":Ready",     visitor.getReady());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error edit into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
bool DataBase::deleteIntoTable(int value)
{
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE " WHERE id=:id;");
    query.bindValue(":id", value);
    if(!query.exec()){
        qDebug() << "error delete into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

