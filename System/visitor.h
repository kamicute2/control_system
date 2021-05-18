#ifndef VISITOR_H
#define VISITOR_H
#include <QString>
#include <QDateTime>
#include <QStandardItemModel>

class Visitor
{
private:
    int myNumber;
    QString myName;
    QString myPhone;
    QString myProduct;
    int myPrice;
    QString myDate;
    QString myReady;
public:
    Visitor();
    void SetVisitor(int Number, QString Name, QString Phone, QString Product, QString Price, QString Date, QString Ready);
    void SetRow(QStandardItemModel *model, int i);
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
    void setPrice(QString value);
    void setDate(QString value);
    void setReady(QString value);
};

#endif // VISITOR_H
