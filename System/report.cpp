#include "report.h"
#include "mainwindow.h"
#include "ui_report.h"
#include <QMessageBox>

Report::Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Report)
{

    ui->setupUi(this);
    ui->label_2->hide();
    ui->lineEdit->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    //ui->label_2->show();
}

Report::~Report()
{
    delete ui;
}

void Report::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
        case 3:
        {
            ui->label_2->show();
            ui->lineEdit->show();
            break;
        }
        default:
        {
            ui->label_2->hide();
            ui->lineEdit->hide();
        }
    }
}

void Report::on_pushButton_clicked()
{
    MainWindow mainwindow;
    int ret = 1;
    reportData data;
    if(ui->comboBox->currentIndex()<3)
        data = mainwindow.tableReport(ui->comboBox->currentIndex());
    else
        if(!ui->lineEdit->text().isEmpty())
            data = mainwindow.tableReport(ui->comboBox->currentIndex(), ui->lineEdit->text().toInt());
        else
        {
            QMessageBox::warning(this, "Неверное значение","Введите значение в поле \n \"Количество дней\"",QMessageBox::Ok, QMessageBox::Ok);

            return;
        }
    if (ret)
    {
        ui->label_3->show();
        ui->label_4->show();
        ui->label_5->show();
        ui->label_6->show();
        switch (ui->comboBox->currentIndex()) {
        case 0:
        {
            ui->label_3->setText("Отчет за " + QDate::currentDate().toString("d MMMM yyyy"));
            break;
        }
        case 1:
        {
            ui->label_3->setText("Отчет за " + QDate::currentDate().toString("MMMM"));
            break;
        }
        case 2:
        {
            ui->label_3->setText("Отчет за " + QDate::currentDate().toString("yyyy"));
            break;
        }
        case 3:
        {
            ui->label_3->setText("Отчет за " + ui->lineEdit->text() + " дней");
            break;
        }
        }
        ui->label_4->setText("Количество посетителей: " + QString::number(data.coutClients));
        ui->label_5->setText("Выручка: " + QString::number(data.sumPrice) + "₽");
        ui->label_6->setText("Самая большая покупка: " + QString::number(data.maxPrice) + "₽");
    }
}
