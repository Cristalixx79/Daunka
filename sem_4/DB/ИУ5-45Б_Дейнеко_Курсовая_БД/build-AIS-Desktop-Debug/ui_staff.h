/********************************************************************************
** Form generated from reading UI file 'staff.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAFF_H
#define UI_STAFF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Staff
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;

    void setupUi(QDialog *Staff)
    {
        if (Staff->objectName().isEmpty())
            Staff->setObjectName(QString::fromUtf8("Staff"));
        Staff->resize(400, 300);
        verticalLayout = new QVBoxLayout(Staff);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton = new QPushButton(Staff);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(Staff);

        QMetaObject::connectSlotsByName(Staff);
    } // setupUi

    void retranslateUi(QDialog *Staff)
    {
        Staff->setWindowTitle(QApplication::translate("Staff", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("Staff", "Staff", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Staff: public Ui_Staff {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAFF_H
