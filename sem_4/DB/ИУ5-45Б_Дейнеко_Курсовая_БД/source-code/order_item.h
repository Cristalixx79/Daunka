#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>

namespace Ui {
    class OrderItem;
}

class OrderItem : public QDialog {
    Q_OBJECT
public:
    explicit OrderItem(QWidget *parent, QSqlDatabase db, qint32 idfOrder, qint32 idfUser);
    ~OrderItem();
private slots:
    void on_backBtn_clicked();

    void on_payBtn_clicked();

    void on_deleteBtn_clicked();

    void on_pushButton_clicked();

    void on_reOrderBtn_clicked();

private:
    Ui::OrderItem *ui;
    QSqlDatabase dbconn;
    qint32 orderId_;
    qint32 userId;
    bool isPaid;

    QString orderId;
    QString model;
    QString orderDate;
    QString shipDate;
    QString paidDate;
    QString status;
    QString quantiy;
    QString price;

    bool getOrderItemData();
    bool createInvoicePdf();
    bool putNewOrder();
    bool putNewOrderContent(qint32 orderId);
    void deleteOrder(qint32 orderId);
};

#endif // ORDER_ITEM_H
