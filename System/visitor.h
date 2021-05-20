#ifndef VISITOR_H
#define VISITOR_H
#include <QString>
#include <QDateTime>
#include <QSqlTableModel>

class Visitor
{
private:
    int myNumber;
    QDate myCurDate;
    QString myName;
    QString myPhone;
    QString myProduct;
    int myPrice;
    QString myDate;
    QString myReady;
public:
    Visitor();
    void SetVisitor(int Number, QString Name, QString Phone, QString Product, int Price, QString Date, QString Ready);
    void SetRow(QSqlTableModel *model, int i);
    QDate getCurDate();
    QString getNumber();
    QString getName();
    QString getPhone();
    QString getProduct();
    QString getPrice();
    QString getDate();
    QString getReady();
    void setNumber(int value);
    void setName(QString value);
    void setPhone(QString value);
    void setProduct(QString value);
    void setPrice(int value);
    void setDate(QString value);
    void setReady(QString value);
};

#endif // VISITOR_H
