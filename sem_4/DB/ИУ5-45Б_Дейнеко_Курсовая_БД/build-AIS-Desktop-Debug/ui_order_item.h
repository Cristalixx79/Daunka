/********************************************************************************
** Form generated from reading UI file 'order_item.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDER_ITEM_H
#define UI_ORDER_ITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderItem
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *backBtn;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *orderItemLb;
    QTextBrowser *orderItemTb;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *deleteBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *reOrderBtn;
    QPushButton *payBtn;

    void setupUi(QDialog *OrderItem)
    {
        if (OrderItem->objectName().isEmpty())
            OrderItem->setObjectName(QString::fromUtf8("OrderItem"));
        OrderItem->resize(535, 503);
        verticalLayout_2 = new QVBoxLayout(OrderItem);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_3 = new QWidget(OrderItem);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        backBtn = new QPushButton(widget_3);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));

        horizontalLayout_2->addWidget(backBtn);


        verticalLayout_2->addWidget(widget_3);

        widget_2 = new QWidget(OrderItem);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        orderItemLb = new QLabel(widget_2);
        orderItemLb->setObjectName(QString::fromUtf8("orderItemLb"));

        verticalLayout->addWidget(orderItemLb);

        orderItemTb = new QTextBrowser(widget_2);
        orderItemTb->setObjectName(QString::fromUtf8("orderItemTb"));

        verticalLayout->addWidget(orderItemTb);

        widget = new QWidget(widget_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        deleteBtn = new QPushButton(widget);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));

        horizontalLayout->addWidget(deleteBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        reOrderBtn = new QPushButton(widget);
        reOrderBtn->setObjectName(QString::fromUtf8("reOrderBtn"));

        horizontalLayout->addWidget(reOrderBtn);

        payBtn = new QPushButton(widget);
        payBtn->setObjectName(QString::fromUtf8("payBtn"));

        horizontalLayout->addWidget(payBtn);


        verticalLayout->addWidget(widget);


        verticalLayout_2->addWidget(widget_2);


        retranslateUi(OrderItem);

        QMetaObject::connectSlotsByName(OrderItem);
    } // setupUi

    void retranslateUi(QDialog *OrderItem)
    {
        OrderItem->setWindowTitle(QApplication::translate("OrderItem", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("OrderItem", "\320\240\320\260\321\201\320\277\320\265\321\207\320\260\321\202\320\260\321\202\321\214 \320\275\320\260\320\272\320\273\320\260\320\264\320\275\321\203\321\216", nullptr));
        backBtn->setText(QApplication::translate("OrderItem", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        orderItemLb->setText(QString());
        deleteBtn->setText(QApplication::translate("OrderItem", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214 \320\267\320\260\320\272\320\260\320\267", nullptr));
        reOrderBtn->setText(QApplication::translate("OrderItem", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214 \320\267\320\260\320\272\320\260\320\267", nullptr));
        payBtn->setText(QApplication::translate("OrderItem", "\320\236\320\277\320\273\320\260\321\202\320\270\321\214 \320\267\320\260\320\272\320\260\320\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderItem: public Ui_OrderItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDER_ITEM_H
