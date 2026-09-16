#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "product_item_manager.h"
#include "new_product.h"

namespace Ui {
    class ProductManager;
}

class ProductManager : public QDialog {
    Q_OBJECT
public:
    explicit ProductManager(QWidget *parent, QSqlDatabase db);
    ~ProductManager();
private slots:
    void on_backBtn_clicked();

    void on_searchBtn_clicked();

    void on_clearBtn_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_productList_itemDoubleClicked(QListWidgetItem *item);

    void on_addBtn_clicked();

private:
    Ui::ProductManager *ui;
    QString orderMethod;
    QSqlDatabase dbconn;
    NewProduct *np;
    ProductItemManager *pim;

    bool getDatabaseProducts();
};

#endif // PRODUCT_MANAGER_H
