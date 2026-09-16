/********************************************************************************
** Form generated from reading UI file 'product_manager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCT_MANAGER_H
#define UI_PRODUCT_MANAGER_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductManager
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchLe;
    QPushButton *searchBtn;
    QPushButton *clearBtn;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboBox;
    QPushButton *backBtn;
    QLabel *label;
    QListWidget *productList;
    QPushButton *addBtn;
    QLabel *productCount;

    void setupUi(QDialog *ProductManager)
    {
        if (ProductManager->objectName().isEmpty())
            ProductManager->setObjectName(QString::fromUtf8("ProductManager"));
        ProductManager->resize(1215, 682);
        verticalLayout = new QVBoxLayout(ProductManager);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(ProductManager);
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

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        backBtn = new QPushButton(widget);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));

        horizontalLayout->addWidget(backBtn);


        verticalLayout->addWidget(widget);

        label = new QLabel(ProductManager);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        productList = new QListWidget(ProductManager);
        productList->setObjectName(QString::fromUtf8("productList"));

        verticalLayout->addWidget(productList);

        addBtn = new QPushButton(ProductManager);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));

        verticalLayout->addWidget(addBtn);

        productCount = new QLabel(ProductManager);
        productCount->setObjectName(QString::fromUtf8("productCount"));

        verticalLayout->addWidget(productCount);


        retranslateUi(ProductManager);

        QMetaObject::connectSlotsByName(ProductManager);
    } // setupUi

    void retranslateUi(QDialog *ProductManager)
    {
        ProductManager->setWindowTitle(QApplication::translate("ProductManager", "Dialog", nullptr));
        searchBtn->setText(QApplication::translate("ProductManager", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        clearBtn->setText(QApplication::translate("ProductManager", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        backBtn->setText(QApplication::translate("ProductManager", "\320\235\320\260\320\267\320\260\320\264", nullptr));
        label->setText(QApplication::translate("ProductManager", "          \320\234\320\276\320\264\320\265\320\273\321\214      \320\237\321\200\320\276\320\270\320\267\320\262\320\276\320\264\320\270\321\202\320\265\320\273\321\214              \320\246\320\265\320\275\320\260          \320\222 \320\275\320\260\320\273\320\270\321\207\320\270\320\270", nullptr));
        addBtn->setText(QApplication::translate("ProductManager", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \321\202\320\276\320\262\320\260\321\200", nullptr));
        productCount->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ProductManager: public Ui_ProductManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCT_MANAGER_H
