/********************************************************************************
** Form generated from reading UI file 'manager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Manager
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *manageCustBtn;
    QPushButton *managePrBtn;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *statisticsSort;
    QPushButton *logOutBtn;
    QFrame *frame;

    void setupUi(QDialog *Manager)
    {
        if (Manager->objectName().isEmpty())
            Manager->setObjectName(QString::fromUtf8("Manager"));
        Manager->resize(1239, 693);
        verticalLayout = new QVBoxLayout(Manager);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_2 = new QWidget(Manager);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget = new QWidget(widget_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        manageCustBtn = new QPushButton(widget);
        manageCustBtn->setObjectName(QString::fromUtf8("manageCustBtn"));

        horizontalLayout->addWidget(manageCustBtn);

        managePrBtn = new QPushButton(widget);
        managePrBtn->setObjectName(QString::fromUtf8("managePrBtn"));

        horizontalLayout->addWidget(managePrBtn);


        horizontalLayout_2->addWidget(widget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        statisticsSort = new QComboBox(widget_3);
        statisticsSort->setObjectName(QString::fromUtf8("statisticsSort"));

        horizontalLayout_3->addWidget(statisticsSort);

        logOutBtn = new QPushButton(widget_3);
        logOutBtn->setObjectName(QString::fromUtf8("logOutBtn"));

        horizontalLayout_3->addWidget(logOutBtn);


        horizontalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget_2);

        frame = new QFrame(Manager);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);


        retranslateUi(Manager);

        QMetaObject::connectSlotsByName(Manager);
    } // setupUi

    void retranslateUi(QDialog *Manager)
    {
        Manager->setWindowTitle(QApplication::translate("Manager", "Dialog", nullptr));
        manageCustBtn->setText(QApplication::translate("Manager", "\320\243\320\277\321\200\320\260\320\262\320\273\321\217\321\202\321\214 \320\272\320\273\320\270\320\265\320\275\321\202\320\260\320\274\320\270", nullptr));
        managePrBtn->setText(QApplication::translate("Manager", "\320\243\320\277\321\200\320\260\320\262\320\273\321\217\321\202\321\214 \320\277\321\200\320\276\320\264\321\203\320\272\321\202\320\260\320\274\320\270", nullptr));
        label->setText(QApplication::translate("Manager", "\320\222\321\213\320\262\320\276\320\264 \321\201\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\270 \320\277\320\276", nullptr));
        logOutBtn->setText(QApplication::translate("Manager", "\320\241\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Manager: public Ui_Manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGER_H
