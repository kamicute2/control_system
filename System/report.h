#ifndef REPORT_H
#define REPORT_H

#include <QDialog>

struct reportData{
    int coutClients = 0;
    int sumPrice = 0;
    int maxPrice = 0;
};

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = nullptr);
    ~Report();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Report *ui;
};

#endif // REPORT_H
