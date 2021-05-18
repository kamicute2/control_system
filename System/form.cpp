#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

Visitor Form::ReturnValue()
{
    Visitor visitor;
    int number = ui->lineEdit->text().toInt();
    QString name = ui->lineEdit_2->text();
    QString phone = ui->lineEdit_3->text();
    QString product = ui->lineEdit_4->text();
    QString price = ui->lineEdit_5->text();
    QString date = ui->lineEdit_6->text();
    QString ready = ui->lineEdit_7->text();
    visitor.SetVisitor(number, name, phone, product, price, date, ready);
    return visitor;
}
void Form::SetLineEdit(Visitor visitor)
{
    ui->lineEdit->setText(visitor.getNumber());
    ui->lineEdit_2->setText(visitor.getName());
    ui->lineEdit_3->setText(visitor.getPhone());
    ui->lineEdit_4->setText(visitor.getProduct());
    ui->lineEdit_5->setText(visitor.getPrice());
    ui->lineEdit_6->setText(visitor.getDate());
    ui->lineEdit_7->setText(visitor.getReady());
}
