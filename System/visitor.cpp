#include "visitor.h"

Visitor::Visitor()
{
    myNumber = 1;
    myCurDate = QDate::currentDate();
    myName = "Name";
    myPhone = "Phone";
    myProduct = "Product";
    myPrice = 100;
    myDate = "Date";
    myReady = "Ready";
}

void Visitor::SetVisitor(int Number, QString Name, QString Phone, QString Product, int Price, QString Date, QString Ready)
{
    myNumber = Number;
    myCurDate = QDate::currentDate();
    myName = Name;
    myPhone = Phone;
    myProduct = Product;
    myPrice = Price;
    myDate = Date;
    myReady = Ready;
}

void Visitor::SetRow(QSqlTableModel *model, int i)
{
    QModelIndex index = model->index(i,0);
    model->setData(index, myNumber);
    index = model->index(i,1);
    model->setData(index, myName);
    index = model->index(i,2);
    model->setData(index, myPhone);
    index = model->index(i,3);
    model->setData(index, myProduct);
    index = model->index(i,4);
    model->setData(index, myPrice);
    index = model->index(i,5);
    model->setData(index, myDate);
    index = model->index(i,6);
    model->setData(index, myReady);
}

QString Visitor::getNumber()
{
    return QString::number(myNumber);
}

QDate Visitor::getCurDate()
{
    return myCurDate;
}

QString Visitor::getName()
{
    return myName;
}

QString Visitor::getPhone()
{
    return myPhone;
}

QString Visitor::getProduct()
{
    return myProduct;
}

QString Visitor::getPrice()
{
    return QString::number(myPrice);
}

QString Visitor::getDate()
{
    return myDate;
}

QString Visitor::getReady()
{
    return myReady;
}

void Visitor::setNumber(int value)
{
    myNumber = value;
}

void Visitor::setName(QString value)
{
    myName = value;
}

void Visitor::setPhone(QString value)
{
    myPhone = value;
}

void Visitor::setProduct(QString value)
{
    myProduct = value;
}

void Visitor::setPrice(int value)
{
    myPrice = value;
}

void Visitor::setDate(QString value)
{
    myDate = value;
}

void Visitor::setReady(QString value)
{
    myReady = value;
}


