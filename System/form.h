#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include <visitor.h>
namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    Visitor ReturnValue();
    void SetLineEdit(Visitor visitor);
public slots:
    //void receiveData(Visitor);
signals:
    //void sendData(Visitor);
private:
    Ui::Form *ui;
};

#endif // FORM_H
