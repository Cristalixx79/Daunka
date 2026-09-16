/********************************************************************************
** Form generated from reading UI file 'client_profile_order.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_PROFILE_ORDER_H
#define UI_CLIENT_PROFILE_ORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ClientProfileOrder
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *orderNameLb;
    QSpacerItem *verticalSpacer;
    QPushButton *backBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *ClientProfileOrder)
    {
        if (ClientProfileOrder->objectName().isEmpty())
            ClientProfileOrder->setObjectName(QString::fromUtf8("ClientProfileOrder"));
        ClientProfileOrder->resize(349, 152);
        verticalLayout = new QVBoxLayout(ClientProfileOrder);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        orderNameLb = new QLabel(ClientProfileOrder);
        orderNameLb->setObjectName(QString::fromUtf8("orderNameLb"));

        verticalLayout->addWidget(orderNameLb);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        backBtn = new QPushButton(ClientProfileOrder);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));

        verticalLayout->addWidget(backBtn);

        cancelBtn = new QPushButton(ClientProfileOrder);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        verticalLayout->addWidget(cancelBtn);


        retranslateUi(ClientProfileOrder);

        QMetaObject::connectSlotsByName(ClientProfileOrder);
    } // setupUi

    void retranslateUi(QDialog *ClientProfileOrder)
    {
        ClientProfileOrder->setWindowTitle(QApplication::translate("ClientProfileOrder", "Dialog", nullptr));
        orderNameLb->setText(QString());
        backBtn->setText(QApplication::translate("ClientProfileOrder", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        cancelBtn->setText(QApplication::translate("ClientProfileOrder", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214 \320\267\320\260\320\272\320\260\320\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientProfileOrder: public Ui_ClientProfileOrder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_PROFILE_ORDER_H
