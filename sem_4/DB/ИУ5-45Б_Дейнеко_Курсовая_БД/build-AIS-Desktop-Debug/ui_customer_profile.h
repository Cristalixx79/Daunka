/********************************************************************************
** Form generated from reading UI file 'customer_profile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMER_PROFILE_H
#define UI_CUSTOMER_PROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
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

class Ui_CustomerProfile
{
public:
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchLe;
    QPushButton *searchBtn;
    QPushButton *clearBtn;
    QPushButton *refreshBtn;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *sortBox;
    QPushButton *backBtn;
    QPushButton *logOutBtn;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *notPaidCb;
    QCheckBox *noCanceledCb;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QListWidget *ordersList;
    QLabel *orderCountLb;

    void setupUi(QDialog *CustomerProfile)
    {
        if (CustomerProfile->objectName().isEmpty())
            CustomerProfile->setObjectName(QString::fromUtf8("CustomerProfile"));
        CustomerProfile->resize(1301, 802);
        verticalLayout_3 = new QVBoxLayout(CustomerProfile);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(CustomerProfile);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        widget_4 = new QWidget(CustomerProfile);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget = new QWidget(widget_4);
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

        refreshBtn = new QPushButton(widget);
        refreshBtn->setObjectName(QString::fromUtf8("refreshBtn"));

        horizontalLayout->addWidget(refreshBtn);


        horizontalLayout_3->addWidget(widget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        sortBox = new QComboBox(widget_3);
        sortBox->setObjectName(QString::fromUtf8("sortBox"));

        horizontalLayout_2->addWidget(sortBox);

        backBtn = new QPushButton(widget_3);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));

        horizontalLayout_2->addWidget(backBtn);

        logOutBtn = new QPushButton(widget_3);
        logOutBtn->setObjectName(QString::fromUtf8("logOutBtn"));

        horizontalLayout_2->addWidget(logOutBtn);


        horizontalLayout_3->addWidget(widget_3);


        verticalLayout_3->addWidget(widget_4);

        widget_5 = new QWidget(CustomerProfile);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        verticalLayout_2 = new QVBoxLayout(widget_5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        notPaidCb = new QCheckBox(widget_5);
        notPaidCb->setObjectName(QString::fromUtf8("notPaidCb"));

        verticalLayout_2->addWidget(notPaidCb);

        noCanceledCb = new QCheckBox(widget_5);
        noCanceledCb->setObjectName(QString::fromUtf8("noCanceledCb"));

        verticalLayout_2->addWidget(noCanceledCb);


        verticalLayout_3->addWidget(widget_5);

        widget_2 = new QWidget(CustomerProfile);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        ordersList = new QListWidget(widget_2);
        ordersList->setObjectName(QString::fromUtf8("ordersList"));

        verticalLayout->addWidget(ordersList);

        orderCountLb = new QLabel(widget_2);
        orderCountLb->setObjectName(QString::fromUtf8("orderCountLb"));

        verticalLayout->addWidget(orderCountLb);


        verticalLayout_3->addWidget(widget_2);


        retranslateUi(CustomerProfile);

        QMetaObject::connectSlotsByName(CustomerProfile);
    } // setupUi

    void retranslateUi(QDialog *CustomerProfile)
    {
        CustomerProfile->setWindowTitle(QApplication::translate("CustomerProfile", "Dialog", nullptr));
        label->setText(QApplication::translate("CustomerProfile", "\320\234\320\276\320\270 \320\267\320\260\320\272\320\260\320\267\321\213", nullptr));
        searchBtn->setText(QApplication::translate("CustomerProfile", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        clearBtn->setText(QApplication::translate("CustomerProfile", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        refreshBtn->setText(QApplication::translate("CustomerProfile", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("CustomerProfile", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276", nullptr));
        backBtn->setText(QApplication::translate("CustomerProfile", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        logOutBtn->setText(QApplication::translate("CustomerProfile", "\320\241\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        notPaidCb->setText(QApplication::translate("CustomerProfile", "\320\242\320\276\320\273\321\214\320\272\320\276 \320\275\320\265\320\276\320\277\320\273\320\260\321\207\320\265\320\275\320\275\321\213\320\265", nullptr));
        noCanceledCb->setText(QApplication::translate("CustomerProfile", "\320\235\320\265 \320\277\320\276\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214 \320\276\321\202\320\274\320\265\320\275\321\221\320\275\320\275\321\213\320\265", nullptr));
        label_3->setText(QApplication::translate("CustomerProfile", "           ID      \320\234\320\276\320\264\320\265\320\273\321\214         \320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276     \320\241\321\202\320\260\321\202\321\203\321\201            \320\246\320\265\320\275\320\260             \320\224\320\260\321\202\320\260 \320\267\320\260\320\272\320\260\320\267\320\260                      \320\224\320\260\321\202\320\260 \320\264\320\276\321\201\321\202\320\260\320\262\320\272\320\270                 \320\224\320\260\321\202\320\260 \320\277\320\273\320\260\321\202\320\265\320\266\320\260", nullptr));
        orderCountLb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CustomerProfile: public Ui_CustomerProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMER_PROFILE_H
