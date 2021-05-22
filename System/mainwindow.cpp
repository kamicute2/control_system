#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QTableWidgetItem>
#include <QMessageBox>

static const int TotalBytes = 50 * 1024 * 1024;
static const int PayloadSize = 64 * 1024; // 64 KB


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowTitle("Kitsune");
    this->setWindowIconText("Kitsune");
    this->setWindowIcon(QIcon(":images/icon.png"));
    ui->setupUi(this);

    ui->addButton->setIconSize({100,80});
    ui->editButon->setIconSize({100,80});
    ui->deleteButton->setIconSize({100,80});
    ui->makeReportButton->setIconSize({100,80});
    /* Создать объект, который будет использоваться для работы с данными нашей БД  и инициализировать подключение к базе данных */
    db = new DataBase();
    db->connectToDataBase();
    Visitor visitor;
    /* Производим наполнение таблицы базы данных контентом, который будет отображаться в TableView*/
    //db->inserIntoTable(visitor);
    this->setupModel(TABLE);
    this->createUI();
    Form form;
    //connect(this, SIGNAL(sendData(Visitor)), form, SLOT(receiveData(Visitor)));

    //connect(this, SIGNAL(receiveData(Visitor)), form, SLOT((Visitor)));
    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    Form form;
    form.setModal(true);
    form.hint(OftenWords());
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
        int j=2; //столбец
        QString text;
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
        QDateTime a = index.data().toDateTime();
        visitor.setDate(a);
        j++;
        index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
        text = index.data().toString();
        visitor.setReady(text);



        Form form;
        form.SetLineEdit(visitor);
        form.setModal(true);
        if(form.exec())
        {
            Visitor visitor;
            j=1;

            visitor = form.ReturnValue();
            index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
            j++;
            sqlmodel->setData(index, visitor.getCurDate().toString("d MMMM yyyy"));
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
            sqlmodel->setData(index, visitor.getDate().toString("d MMMM yyyy HH:mm"));
            index = selectedRowsIndexesList[0].sibling(selectedRowsIndexesList[0].row(), j);
            sqlmodel->setData(index, visitor.getReady());
            //sqlmodel->select();
        }
        // В Database есть метод editIntoTable(), однако по неизвестным мне причинам он не работает, поэтому используем submitAll()
        sqlmodel->submitAll();

    }
    else
        QMessageBox::warning(this, "Строка не выбрана","Выберете строку! \n",QMessageBox::Ok, QMessageBox::Ok);
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
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


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
            // Нажата кнопка OK
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
    else
        QMessageBox::warning(this, "Строка не выбрана","Выберете строку! \n",QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::on_makeReportButton_clicked()
{
    Report report;
    report.setModal(true);
    report.exec();
}

QSqlQuery MainWindow::OftenWords()
{
    QSqlQuery query;
    query.prepare("SELECT Name, COUNT(*) FROM " TABLE
                    " GROUP BY Name "
                    " HAVING COUNT(*) > 1");
    query.exec();
    return query;

}

reportData MainWindow::tableReport(int value)
{
    reportData data;
    QString date = QDate::currentDate().toString("d MMMM yyyy");
    QStringList items = date.split(" ");
    switch(value)
    {
        case 0:
        {
            for(int i=0; i<sqlmodel->rowCount();i++ )
            {
                if(sqlmodel->index(i, 1, QModelIndex()).data().toString() == date)
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
                if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == items[1] &&
                   sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2] == items[2])
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
                if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2] == items[2])
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
    QDate datadate = QDate(sqlmodel->index(1, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
            1,sqlmodel->index(1, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
    for(int i=0; i<sqlmodel->rowCount();i++ )
    {

        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "January")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    1,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "February")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    2,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "March")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    3,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "April")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    4,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "May")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    5,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "June")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    6,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "July")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    7,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "August")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    8,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "September")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    9,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "October")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    10,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "November")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    11,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[1] == "December")
            datadate = QDate(sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[2].toInt(),
                    12,sqlmodel->index(i, 1, QModelIndex()).data().toString().split(" ")[0].toInt());
        if(date.dayOfYear() - datadate.dayOfYear() <= days-1 )
        {
            data.coutClients++;
            data.sumPrice += sqlmodel->index(i, 5, QModelIndex()).data().toInt();
            if(data.maxPrice<sqlmodel->index(i, 5, QModelIndex()).data().toInt())
                data.maxPrice=sqlmodel->index(i, 5, QModelIndex()).data().toInt();
        }
    }
    return data;
}

// Реализация поиска

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString filter;
    if(arg1.length()>=1){
        filter =QString("id LIKE ('%%1%') OR " TABLE_CURRENT_DATE " LIKE ('%%1%') OR " TABLE_NAME " LIKE ('%%1%') OR " TABLE_PHONE " LIKE ('%%1%')").arg(arg1);
        sqlmodel->setFilter(filter);
    } else {
        filter= QString("id LIKE ('') OR " TABLE_CURRENT_DATE " LIKE ('') OR " TABLE_NAME " LIKE ('') OR " TABLE_PHONE " LIKE ('')");
        sqlmodel->setFilter(QString());
    }
    sqlmodel->select();

}










//Сервепные слоты

void MainWindow::acceptConnection()
{
    tcpServerConnection = tcpServer.nextPendingConnection();
    connect(tcpServerConnection,SIGNAL(connected()), this, SLOT(startTransfer()));
    connect(tcpServerConnection, SIGNAL(bytesWritten(qint64)), this, SLOT(updateServerProgress(qint64)));
    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    ui->label_2->setText(tr("Accepted connection"));
    startTransfer();
}
void MainWindow::startTransfer()
{
    if(QFile("./" DATABASE_NAME).exists())
    {
        if (!QFile("./" DATABASE_NAME).open(QIODevice::ReadOnly))
        {
        ui->label_2->setText("Couldn't open the file");
        return;
        }
        int TotalBytes = QFile("./" DATABASE_NAME).size();

        bytesToWrite = TotalBytes - (int)tcpServerConnection->write("./" DATABASE_NAME);
        ui->label_2->setText(tr("Connected"));
    }
    else
    {
        ui->label_2->setText("The file does not exist");
        return;
    }

}

void MainWindow::updateServerProgress(qint64 numBytes)
{
    bytesWritten += (int)numBytes;

    // only write more if not finished and when the Qt write buffer is below a certain size.
    if (bytesToWrite > 0 && tcpServerConnection->bytesToWrite() <= 4*PayloadSize)
        bytesToWrite -= (int)tcpServerConnection->write("./" DATABASE_NAME);

    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesWritten);
    ui->label_2->setText(tr("Sent %1MB").arg(bytesWritten / (1024 * 1024)));
}
