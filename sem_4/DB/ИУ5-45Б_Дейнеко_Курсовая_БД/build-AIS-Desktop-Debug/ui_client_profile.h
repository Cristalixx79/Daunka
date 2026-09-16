/********************************************************************************
** Form generated from reading UI file 'client_profile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_PROFILE_H
#define UI_CLIENT_PROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientProfile
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *banBtn;
    QPushButton *refreshBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *backBtn;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *clientInfoLb;
    QTextBrowser *clientInfo;
    QSpacerItem *verticalSpacer;
    QLabel *clientOrdersLb;
    QLabel *label;
    QListWidget *clientOrders;

    void setupUi(QDialog *ClientProfile)
    {
        if (ClientProfile->objectName().isEmpty())
            ClientProfile->setObjectName(QString::fromUtf8("ClientProfile"));
        ClientProfile->resize(1140, 646);
        verticalLayout_2 = new QVBoxLayout(ClientProfile);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(ClientProfile);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        banBtn = new QPushButton(widget);
        banBtn->setObjectName(QString::fromUtf8("banBtn"));

        horizontalLayout->addWidget(banBtn);

        refreshBtn = new QPushButton(widget);
        refreshBtn->setObjectName(QString::fromUtf8("refreshBtn"));

        horizontalLayout->addWidget(refreshBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        backBtn = new QPushButton(widget);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));

        horizontalLayout->addWidget(backBtn);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(ClientProfile);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        clientInfoLb = new QLabel(widget_2);
        clientInfoLb->setObjectName(QString::fromUtf8("clientInfoLb"));

        verticalLayout->addWidget(clientInfoLb);

        clientInfo = new QTextBrowser(widget_2);
        clientInfo->setObjectName(QString::fromUtf8("clientInfo"));

        verticalLayout->addWidget(clientInfo);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        clientOrdersLb = new QLabel(widget_2);
        clientOrdersLb->setObjectName(QString::fromUtf8("clientOrdersLb"));

        verticalLayout->addWidget(clientOrdersLb);

        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        clientOrders = new QListWidget(widget_2);
        clientOrders->setObjectName(QString::fromUtf8("clientOrders"));

        verticalLayout->addWidget(clientOrders);


        verticalLayout_2->addWidget(widget_2);


        retranslateUi(ClientProfile);

        QMetaObject::connectSlotsByName(ClientProfile);
    } // setupUi

    void retranslateUi(QDialog *ClientProfile)
    {
        ClientProfile->setWindowTitle(QApplication::translate("ClientProfile", "Dialog", nullptr));
        banBtn->setText(QApplication::translate("ClientProfile", "\320\227\320\260\320\261\320\273\320\276\320\272\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        refreshBtn->setText(QApplication::translate("ClientProfile", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        backBtn->setText(QApplication::translate("ClientProfile", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        clientInfoLb->setText(QString());
        clientOrdersLb->setText(QString());
        label->setText(QApplication::translate("ClientProfile", "           ID   M\320\276\320\264\320\265\320\273\321\214                  \320\232\320\276\320\273-\320\262\320\276             \320\224\320\260\321\202\320\260 \320\267\320\260\320\272\320\260\320\267\320\260                      \320\224\320\260\321\202\320\260 \320\264\320\276\321\201\321\202\320\260\320\262\320\272\320\270                \320\224\320\260\321\202\320\260 \320\277\320\273\320\260\321\202\320\265\320\266\320\260               \320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientProfile: public Ui_ClientProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_PROFILE_H
