/********************************************************************************
** Form generated from reading UI file 'new_product.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_PRODUCT_H
#define UI_NEW_PRODUCT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewProduct
{
public:
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *backBtn;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLineEdit *modelLe;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_6;
    QLineEdit *typeLe;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QLineEdit *vendorLe;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *priceLe;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QLineEdit *inStockLe;
    QCheckBox *isAvailable;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveBtn;

    void setupUi(QDialog *NewProduct)
    {
        if (NewProduct->objectName().isEmpty())
            NewProduct->setObjectName(QString::fromUtf8("NewProduct"));
        NewProduct->resize(474, 499);
        verticalLayout_6 = new QVBoxLayout(NewProduct);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        widget_6 = new QWidget(NewProduct);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_2 = new QHBoxLayout(widget_6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widget_6);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        backBtn = new QPushButton(widget_6);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));

        horizontalLayout_2->addWidget(backBtn);


        verticalLayout_6->addWidget(widget_6);

        widget = new QWidget(NewProduct);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        modelLe = new QLineEdit(widget);
        modelLe->setObjectName(QString::fromUtf8("modelLe"));

        verticalLayout->addWidget(modelLe);


        verticalLayout_6->addWidget(widget);

        widget_7 = new QWidget(NewProduct);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        verticalLayout_5 = new QVBoxLayout(widget_7);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_6 = new QLabel(widget_7);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_5->addWidget(label_6);

        typeLe = new QLineEdit(widget_7);
        typeLe->setObjectName(QString::fromUtf8("typeLe"));

        verticalLayout_5->addWidget(typeLe);


        verticalLayout_6->addWidget(widget_7);

        widget_2 = new QWidget(NewProduct);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        vendorLe = new QLineEdit(widget_2);
        vendorLe->setObjectName(QString::fromUtf8("vendorLe"));

        verticalLayout_2->addWidget(vendorLe);


        verticalLayout_6->addWidget(widget_2);

        widget_3 = new QWidget(NewProduct);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        priceLe = new QLineEdit(widget_3);
        priceLe->setObjectName(QString::fromUtf8("priceLe"));

        verticalLayout_3->addWidget(priceLe);


        verticalLayout_6->addWidget(widget_3);

        widget_4 = new QWidget(NewProduct);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_4 = new QVBoxLayout(widget_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_4->addWidget(label_2);

        inStockLe = new QLineEdit(widget_4);
        inStockLe->setObjectName(QString::fromUtf8("inStockLe"));

        verticalLayout_4->addWidget(inStockLe);


        verticalLayout_6->addWidget(widget_4);

        isAvailable = new QCheckBox(NewProduct);
        isAvailable->setObjectName(QString::fromUtf8("isAvailable"));

        verticalLayout_6->addWidget(isAvailable);

        widget_5 = new QWidget(NewProduct);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout = new QHBoxLayout(widget_5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cancelBtn = new QPushButton(widget_5);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        saveBtn = new QPushButton(widget_5);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));

        horizontalLayout->addWidget(saveBtn);


        verticalLayout_6->addWidget(widget_5);


        retranslateUi(NewProduct);

        QMetaObject::connectSlotsByName(NewProduct);
    } // setupUi

    void retranslateUi(QDialog *NewProduct)
    {
        NewProduct->setWindowTitle(QApplication::translate("NewProduct", "Dialog", nullptr));
        label->setText(QApplication::translate("NewProduct", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\276\320\262\320\260\321\200", nullptr));
        backBtn->setText(QApplication::translate("NewProduct", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        label_5->setText(QApplication::translate("NewProduct", "\320\234\320\276\320\264\320\265\320\273\321\214", nullptr));
        label_6->setText(QApplication::translate("NewProduct", "\320\242\320\270\320\277 \320\277\321\200\320\276\320\264\321\203\320\272\321\202\320\260", nullptr));
        label_4->setText(QApplication::translate("NewProduct", "\320\237\321\200\320\276\320\270\320\267\320\262\320\276\320\264\320\270\321\202\320\265\320\273\321\214", nullptr));
        label_3->setText(QApplication::translate("NewProduct", "\320\246\320\265\320\275\320\260", nullptr));
        label_2->setText(QApplication::translate("NewProduct", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\262 \320\275\320\260\320\273\320\270\321\207\320\270\320\270", nullptr));
        isAvailable->setText(QApplication::translate("NewProduct", "\320\224\320\276\321\201\321\202\321\203\320\277\320\275\320\276 \320\272 \320\277\321\200\320\276\320\264\320\260\320\266\320\265", nullptr));
        cancelBtn->setText(QApplication::translate("NewProduct", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        saveBtn->setText(QApplication::translate("NewProduct", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewProduct: public Ui_NewProduct {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_PRODUCT_H
