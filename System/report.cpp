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
    if(ui->comboBox->currentIndex()<3)
        reportData data = mainwindow.tableReport(ui->comboBox->currentIndex());
    else
        if(!ui->lineEdit->text().isEmpty())
            reportData data = mainwindow.tableReport(ui->comboBox->currentIndex(), ui->lineEdit->text().toInt());
        else
            int ret = QMessageBox::warning(this, "Неверное значение","Введите значение в поле \n \"Количество дней\"",QMessageBox::Ok, QMessageBox::Ok);

}
