/********************************************************************************
** Form generated from reading UI file 'product_item.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCT_ITEM_H
#define UI_PRODUCT_ITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductItem
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *productItemBack;
    QSpacerItem *horizontalSpacer;
    QSpinBox *quantity;
    QPushButton *productItemOrder;
    QLabel *label;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QTextBrowser *productItemTb;
    QLabel *productItemImg;

    void setupUi(QDialog *ProductItem)
    {
        if (ProductItem->objectName().isEmpty())
            ProductItem->setObjectName(QString::fromUtf8("ProductItem"));
        ProductItem->resize(1020, 796);
        verticalLayout_2 = new QVBoxLayout(ProductItem);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(ProductItem);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        productItemBack = new QPushButton(widget);
        productItemBack->setObjectName(QString::fromUtf8("productItemBack"));

        horizontalLayout->addWidget(productItemBack);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        quantity = new QSpinBox(widget);
        quantity->setObjectName(QString::fromUtf8("quantity"));

        horizontalLayout->addWidget(quantity);

        productItemOrder = new QPushButton(widget);
        productItemOrder->setObjectName(QString::fromUtf8("productItemOrder"));

        horizontalLayout->addWidget(productItemOrder);


        verticalLayout_2->addWidget(widget);

        label = new QLabel(ProductItem);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        widget_2 = new QWidget(ProductItem);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        productItemTb = new QTextBrowser(widget_2);
        productItemTb->setObjectName(QString::fromUtf8("productItemTb"));

        horizontalLayout_2->addWidget(productItemTb);

        productItemImg = new QLabel(widget_2);
        productItemImg->setObjectName(QString::fromUtf8("productItemImg"));

        horizontalLayout_2->addWidget(productItemImg);


        verticalLayout_2->addWidget(widget_2);


        retranslateUi(ProductItem);

        QMetaObject::connectSlotsByName(ProductItem);
    } // setupUi

    void retranslateUi(QDialog *ProductItem)
    {
        ProductItem->setWindowTitle(QApplication::translate("ProductItem", "Dialog", nullptr));
        productItemBack->setText(QApplication::translate("ProductItem", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        productItemOrder->setText(QApplication::translate("ProductItem", "\320\227\320\260\320\272\320\260\320\267\320\260\321\202\321\214", nullptr));
        label->setText(QApplication::translate("ProductItem", "\320\245\320\260\321\200\320\260\320\272\321\202\320\265\321\200\320\270\321\201\321\202\320\270\320\272\320\270 \321\202\320\276\320\262\320\260\321\200\320\260", nullptr));
        productItemImg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ProductItem: public Ui_ProductItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCT_ITEM_H
