#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QTableWidgetItem>
#include <QMessageBox>

int RowNum = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setLocale(QLocale::Byelorussian);
    ui->setupUi(this);
    /* Создать объект, который будет использоваться для работы с данными нашей БД  и инициализировать подключение к базе данных */
    db = new DataBase();
    db->connectToDataBase();
    Visitor visitor;
    /* Производим наполнение таблицы базы данных контентом, который будет отображаться в TableView*/
    //db->inserIntoTable(visitor);
    this->setupModel(TABLE);
    this->createUI();
    Form form;
    //Соединяем сигналы и слоты
    //connect(this, SIGNAL(sendData(Visitor)), form, SLOT(receiveData(Visitor)));
    qDebug() <<  QDate::currentDate().dayOfYear();
    //connect(this, SIGNAL(receiveData(Visitor)), form, SLOT((Visitor)));
    //Работа с таблицей
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
        Visitor visitor;
        visitor = form.ReturnValue();
        db->inserIntoTable(visitor);
        sqlmodel->select();
    }
}
void MainWindow::on_editButon_clicked()
{
    QModelIndexList selectedRowsIndexesList = ui->tableView->selectionModel()->selectedRows();
    if(!selectedRowsIndexesList.isEmpty())
    {
        Visitor visitor;
        //Из значений строк создаем объект, который передадим в функцию формы для заполнения строк
        QModelIndex index;
        int j=1; //столбец
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
        visitor.setPrice(text.toInt());
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
        if(form.exec())
        {
            Visitor visitor;
            j=0;

            visitor = form.ReturnValue();
            index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
            j++;
            sqlmodel->setData(index, visitor.getNumber());
            index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
            j++;
            sqlmodel->setData(index, visitor.getName());
            index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
            j++;
            sqlmodel->setData(index, visitor.getPhone());
            index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
            j++;
            sqlmodel->setData(index, visitor.getProduct());
            index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
            j++;
            sqlmodel->setData(index, visitor.getPrice());
            index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
            j++;
            sqlmodel->setData(index, visitor.getDate());
            index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
            sqlmodel->setData(index, visitor.getReady());
            //sqlmodel->select();
        }
    }
}

void MainWindow::setupModel(const QString &tableName)
{
    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     */
    sqlmodel = new QSqlTableModel(this);
    sqlmodel->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     */
    sqlmodel->setHeaderData(0, Qt::Horizontal, "Номер");
    sqlmodel->setHeaderData(1, Qt::Horizontal, "Дата");
    sqlmodel->setHeaderData(2, Qt::Horizontal, "ФИО");
    sqlmodel->setHeaderData(3, Qt::Horizontal, "Телефон");
    sqlmodel->setHeaderData(4, Qt::Horizontal, "Товар");
    sqlmodel->setHeaderData(5, Qt::Horizontal, "Цена");
    sqlmodel->setHeaderData(6, Qt::Horizontal, "Время записи");
    sqlmodel->setHeaderData(7, Qt::Horizontal, "Готовность");
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    sqlmodel->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI()
{
    ui->tableView->setModel(sqlmodel);     // Устанавливаем модель на TableView
//    ui->tableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    ui->tableView->verticalHeader()->hide();

    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(7, QHeaderView::ResizeToContents);


    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
//    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    sqlmodel->select(); // Делаем выборку данных из таблицы
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndexList selectedRowsIndexesList = ui->tableView->selectionModel()->selectedRows();
    if(!selectedRowsIndexesList.isEmpty())
    {
        int ret = QMessageBox::question(this, "Удалить","Удалить элемент\n\nВы действительно хотите удалить элемент?",QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        switch(ret){
        case QMessageBox::Ok:{
            // Нажата кнопка Save
            QModelIndex index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), 0);
            db->deleteIntoTable(index.data().toInt());
            sqlmodel->select();
            break;
        }
        case QMessageBox::Cancel:
          // Нажата кнопка Cancel
          break;
        }
    }
}



void MainWindow::on_makeReportButton_clicked()
{
    Report report;
    report.setModal(true);
    report.exec();
}

reportData MainWindow::tableReport(int value)
{
    reportData data;
    QDate date = QDate::currentDate();
    switch(value)
    {
        case 0:
        {
            for(int i=0; i<sqlmodel->rowCount();i++ )
            {
                if(sqlmodel->index(i, 1, QModelIndex()).data().toDate().day() == date.day())
                {
                    data.coutClients++;
                    data.sumPrice += sqlmodel->index(i, 5, QModelIndex()).data().toInt();
                    if(data.maxPrice<sqlmodel->index(i, 5, QModelIndex()).data().toInt())
                        data.maxPrice=sqlmodel->index(i, 5, QModelIndex()).data().toInt();
                }
            }
            break;
        }
        case 1:
        {
            for(int i=0; i<sqlmodel->rowCount();i++ )
            {
                if(sqlmodel->index(i, 1, QModelIndex()).data().toDate().month() == date.month())
                {
                    data.coutClients++;
                    data.sumPrice += sqlmodel->index(i, 5, QModelIndex()).data().toInt();
                    if(data.maxPrice<sqlmodel->index(i, 5, QModelIndex()).data().toInt())
                        data.maxPrice=sqlmodel->index(i, 5, QModelIndex()).data().toInt();
                }
            }
            break;
        }
        case 2:
        {
            for(int i=0; i<sqlmodel->rowCount();i++ )
            {
                if(sqlmodel->index(i, 1, QModelIndex()).data().toDate().year() == date.year())
                {
                    data.coutClients++;
                    data.sumPrice += sqlmodel->index(i, 5, QModelIndex()).data().toInt();
                    if(data.maxPrice<sqlmodel->index(i, 5, QModelIndex()).data().toInt())
                        data.maxPrice=sqlmodel->index(i, 5, QModelIndex()).data().toInt();
                }
            }
            break;
        }
    }
    return data;
}

reportData MainWindow::tableReport(int value, int days)
{
    reportData data;
    QDate date = QDate::currentDate();
    for(int i=0; i<sqlmodel->rowCount();i++ )
    {
        if(date.dayOfYear() - sqlmodel->index(i, 1, QModelIndex()).data().toDate().day() <= days-1 )
        {
            data.coutClients++;
            data.sumPrice += sqlmodel->index(i, 5, QModelIndex()).data().toInt();
            if(data.maxPrice<sqlmodel->index(i, 5, QModelIndex()).data().toInt())
                data.maxPrice=sqlmodel->index(i, 5, QModelIndex()).data().toInt();
        }
    }
    return data;
}
