#ifndef PRODUCT_ITEM_H
#define PRODUCT_ITEM_H

#include <QDialog>
#include <QListWidgetItem>
#include <QSqlDatabase>

namespace Ui {
    class ProductItem;
}

class ProductItem : public QDialog {
    Q_OBJECT
public:
    explicit ProductItem(QWidget *parent, QSqlDatabase db, QStringList lst, qint32 idf);
    ~ProductItem();
private slots:
    void on_productItemBack_clicked();

    void on_productItemOrder_clicked();

private:
    Ui::ProductItem *ui;
    QSqlDatabase dbconn;

    qint32 userId;
    QString model;
    QString type;

    void routeProductInfo(QStringList lst);
    void getPcProductItemInfo(QStringList lst);
    void getPrinterProductItemInfo(QStringList lst);
    void getLaptopProductItemInfo(QStringList lst);
    void getRouterProductItemInfo(QStringList lst);

    bool putNewOrder();
    bool putNewOrderContent(qint32 orderId);
    void deleteOrder(qint32 orderId);
};

#endif // PRODUCT_ITEM_H
