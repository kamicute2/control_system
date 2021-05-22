#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include <QCompleter>
Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    this->setWindowTitle("Kitsune");
    this->setWindowIconText("Kitsune");
    this->setWindowIcon(QIcon(":images/icon.png"));
    ui->setupUi(this);
    ui->label->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit->setTime(QTime::currentTime());
    //Podskazka();

}

Form::~Form()
{
    delete ui;
}

void Form::hint(QSqlQuery query)
{
    if(query.first())
    {
        QStringList  list;
        list<<query.value(0).toString();

        for(int i=1; query.next(); i++)
            list<< query.value(0).toString();
        QCompleter* completer = new QCompleter(list, this);
        completer->setCaseSensitivity( Qt::CaseInsensitive );
        completer->setMaxVisibleItems(6);
        ui->lineEdit_2->setCompleter( completer );
    }

}

Visitor Form::ReturnValue()
{
    Visitor visitor;
    int number = ui->lineEdit->text().toInt();
    QString name = ui->lineEdit_2->text();
    QString phone = ui->lineEdit_3->text();
    QString product = ui->lineEdit_4->text();
    int price = ui->lineEdit_5->text().toInt();
    QDateTime date = ui->dateTimeEdit->dateTime();
    QString ready = ui->comboBox->currentText();
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
    ui->comboBox->setCurrentText(visitor.getDate().toString());
    ui->comboBox->setCurrentText(visitor.getReady());
}
