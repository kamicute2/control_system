#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QTableWidgetItem>

int RowNum = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //Подключаем бд
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    db.setHostName("localhost");
    db.setDatabaseName("./db.sqlite");
    if (!db.open()) {
          qDebug() << db.lastError().text();
    }
    else
    {
        sqlmodel = new QSqlTableModel(this, db);
        sqlmodel ->setTable("System");
        sqlmodel->select();

    }


    Form form;
    //Соединяем сигналы и слоты
    //connect(this, SIGNAL(sendData(Visitor)), form, SLOT(receiveData(Visitor)));

    //connect(this, SIGNAL(receiveData(Visitor)), form, SLOT((Visitor)));
    //Работа с таблицей

    model = new QStandardItemModel( 0, 7, this );
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->hide();
    model->setHeaderData(0, Qt::Horizontal, "Номер");
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    model->setHeaderData(1, Qt::Horizontal, "ФИО");
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    model->setHeaderData(2, Qt::Horizontal, "Телефон");
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    model->setHeaderData(3, Qt::Horizontal, "Товар");
    ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    model->setHeaderData(4, Qt::Horizontal, "Цена");
    ui->tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    model->setHeaderData(5, Qt::Horizontal, "Время записи");
    ui->tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    model->setHeaderData(6, Qt::Horizontal, "Готовность");
    ui->tableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    Form form;
    form.setModal(true);
    if(form.exec())
    {
        model->setRowCount(model->rowCount()+1);
        ui->tableView->setModel(model);
        Visitor visitor;
        visitor = form.ReturnValue();
        visitor.SetRow(model, RowNum);
        RowNum++;
    }
}
void MainWindow::on_editButon_clicked()
{
    QModelIndexList selectedRowsIndexesList = ui->tableView->selectionModel()->selectedRows();
    Visitor visitor;
    //Из значений строк создаем объект, который передадим в функцию формы для заполнения строк
    QModelIndex index;
    int j=0; //столбец
    QString text;
    index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
    text = index.data().toString();
    visitor.setNumber(text.toInt());
    j++;
    index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
    text = index.data().toString();
    visitor.setName(text);
    j++;
    index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
    text = index.data().toString();
    visitor.setPhone(text);
    j++;
    index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
    text = index.data().toString();
    visitor.setProduct(text);
    j++;
    index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
    text = index.data().toString();
    visitor.setPrice(text);
    j++;
    index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
    text = index.data().toString();
    visitor.setDate(text);
    j++;
    index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
    text = index.data().toString();
    visitor.setReady(text);


    Form form;
    form.SetLineEdit(visitor);
    form.setModal(true);
    //form.SetLineEdit();
    form.exec();
}
