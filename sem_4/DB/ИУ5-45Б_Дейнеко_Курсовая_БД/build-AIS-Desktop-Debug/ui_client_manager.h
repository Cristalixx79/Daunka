/********************************************************************************
** Form generated from reading UI file 'client_manager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_MANAGER_H
#define UI_CLIENT_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientManager
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchLe;
    QPushButton *searchBtn;
    QPushButton *clearBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *backBtn;
    QLabel *label;
    QListWidget *usersList;
    QLabel *userCount;

    void setupUi(QDialog *ClientManager)
    {
        if (ClientManager->objectName().isEmpty())
            ClientManager->setObjectName(QString::fromUtf8("ClientManager"));
        ClientManager->resize(1216, 681);
        verticalLayout = new QVBoxLayout(ClientManager);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(ClientManager);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        searchLe = new QLineEdit(widget);
        searchLe->setObjectName(QString::fromUtf8("searchLe"));

        horizontalLayout->addWidget(searchLe);

        searchBtn = new QPushButton(widget);
        searchBtn->setObjectName(QString::fromUtf8("searchBtn"));

        horizontalLayout->addWidget(searchBtn);

        clearBtn = new QPushButton(widget);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));

        horizontalLayout->addWidget(clearBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        backBtn = new QPushButton(widget);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));

        horizontalLayout->addWidget(backBtn);


        verticalLayout->addWidget(widget);

        label = new QLabel(ClientManager);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        usersList = new QListWidget(ClientManager);
        usersList->setObjectName(QString::fromUtf8("usersList"));

        verticalLayout->addWidget(usersList);

        userCount = new QLabel(ClientManager);
        userCount->setObjectName(QString::fromUtf8("userCount"));

        verticalLayout->addWidget(userCount);


        retranslateUi(ClientManager);

        QMetaObject::connectSlotsByName(ClientManager);
    } // setupUi

    void retranslateUi(QDialog *ClientManager)
    {
        ClientManager->setWindowTitle(QApplication::translate("ClientManager", "Dialog", nullptr));
        searchBtn->setText(QApplication::translate("ClientManager", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        clearBtn->setText(QApplication::translate("ClientManager", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        backBtn->setText(QApplication::translate("ClientManager", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        label->setText(QApplication::translate("ClientManager", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\272\320\273\320\270\320\265\320\275\321\202\320\276\320\262", nullptr));
        userCount->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ClientManager: public Ui_ClientManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_MANAGER_H
