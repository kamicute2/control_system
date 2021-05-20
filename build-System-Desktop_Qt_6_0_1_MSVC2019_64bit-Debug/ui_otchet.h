/********************************************************************************
** Form generated from reading UI file 'otchet.ui'
**
** Created by: Qt User Interface Compiler version 6.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OTCHET_H
#define UI_OTCHET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Otchet
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;

    void setupUi(QDialog *Otchet)
    {
        if (Otchet->objectName().isEmpty())
            Otchet->setObjectName(QString::fromUtf8("Otchet"));
        Otchet->resize(786, 532);
        verticalLayout = new QVBoxLayout(Otchet);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Otchet);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(16);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(Otchet);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(Otchet);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(Otchet);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(Otchet);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(Otchet);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_3->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Otchet);

        QMetaObject::connectSlotsByName(Otchet);
    } // setupUi

    void retranslateUi(QDialog *Otchet)
    {
        Otchet->setWindowTitle(QCoreApplication::translate("Otchet", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Otchet", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\202\320\270\320\277 \320\276\321\202\321\207\320\265\321\202\320\260:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Otchet", "\320\236\321\202\321\207\320\265\321\202 \320\267\320\260 \320\264\320\265\320\275\321\214", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Otchet", "\320\236\321\202\321\207\320\265\321\202 \320\267\320\260 \320\274\320\265\321\201\321\217\321\206", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Otchet", "\320\236\321\202\321\207\320\265\321\202 \320\267\320\260 \320\263\320\276\320\264", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Otchet", "\320\236\321\202\321\207\320\265\321\202 \320\267\320\260 N \320\264\320\275\320\265\320\271", nullptr));

        label_2->setText(QCoreApplication::translate("Otchet", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\264\320\275\320\265\320\271:", nullptr));
        pushButton->setText(QCoreApplication::translate("Otchet", "\320\241\320\276\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \320\276\321\202\321\207\320\265\321\202", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Otchet", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Otchet: public Ui_Otchet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OTCHET_H
