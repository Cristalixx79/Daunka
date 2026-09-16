/********************************************************************************
** Form generated from reading UI file 'customer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMER_H
#define UI_CUSTOMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Customer
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *searchLe;
    QPushButton *searchBtn;
    QPushButton *clearBtn;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *sortBox;
    QPushButton *profileBtn;
    QLabel *label_3;
    QListWidget *productList;
    QTextBrowser *customerInfoTb;
    QLabel *productCountLb;

    void setupUi(QDialog *Customer)
    {
        if (Customer->objectName().isEmpty())
            Customer->setObjectName(QString::fromUtf8("Customer"));
        Customer->resize(1315, 801);
        verticalLayout_2 = new QVBoxLayout(Customer);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(Customer);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        widget_5 = new QWidget(widget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        widget_3 = new QWidget(widget_5);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        searchLe = new QLineEdit(widget_3);
        searchLe->setObjectName(QString::fromUtf8("searchLe"));

        horizontalLayout_2->addWidget(searchLe);

        searchBtn = new QPushButton(widget_3);
        searchBtn->setObjectName(QString::fromUtf8("searchBtn"));

        horizontalLayout_2->addWidget(searchBtn);

        clearBtn = new QPushButton(widget_3);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));

        horizontalLayout_2->addWidget(clearBtn);


        horizontalLayout_4->addWidget(widget_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        widget_4 = new QWidget(widget_5);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        sortBox = new QComboBox(widget_4);
        sortBox->setObjectName(QString::fromUtf8("sortBox"));

        horizontalLayout_3->addWidget(sortBox);

        profileBtn = new QPushButton(widget_4);
        profileBtn->setObjectName(QString::fromUtf8("profileBtn"));

        horizontalLayout_3->addWidget(profileBtn);


        horizontalLayout_4->addWidget(widget_4);


        verticalLayout->addWidget(widget_5);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        productList = new QListWidget(widget);
        productList->setObjectName(QString::fromUtf8("productList"));

        verticalLayout->addWidget(productList);

        customerInfoTb = new QTextBrowser(widget);
        customerInfoTb->setObjectName(QString::fromUtf8("customerInfoTb"));

        verticalLayout->addWidget(customerInfoTb);


        verticalLayout_2->addWidget(widget);

        productCountLb = new QLabel(Customer);
        productCountLb->setObjectName(QString::fromUtf8("productCountLb"));

        verticalLayout_2->addWidget(productCountLb);


        retranslateUi(Customer);

        QMetaObject::connectSlotsByName(Customer);
    } // setupUi

    void retranslateUi(QDialog *Customer)
    {
        Customer->setWindowTitle(QApplication::translate("Customer", "Dialog", nullptr));
        label->setText(QApplication::translate("Customer", "\320\235\320\260\321\210\320\270 \321\202\320\276\320\262\320\260\321\200\321\213", nullptr));
        searchBtn->setText(QApplication::translate("Customer", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        clearBtn->setText(QApplication::translate("Customer", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        label_2->setText(QApplication::translate("Customer", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276", nullptr));
        profileBtn->setText(QApplication::translate("Customer", "\320\237\321\200\320\276\321\204\320\270\320\273\321\214", nullptr));
        label_3->setText(QApplication::translate("Customer", "          \320\242\320\270\320\277               \320\234\320\276\320\264\320\265\320\273\321\214        \320\237\321\200\320\276\320\270\320\267\320\262\320\276\320\264\320\270\321\202\320\265\320\273\321\214               \320\246\320\265\320\275\320\260", nullptr));
        productCountLb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Customer: public Ui_Customer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMER_H
