#ifndef CUSTOMER_PROFILE_H
#define CUSTOMER_PROFILE_H

#include <QDialog>
#include <QListWidgetItem>
#include <QSqlDatabase>

#include "order_item.h"

namespace Ui {
    class CustomerProfile;
}

class CustomerProfile : public QDialog {
    Q_OBJECT
public:
    explicit CustomerProfile(QWidget *parent, QSqlDatabase db, qint32 idf);
    ~CustomerProfile();

private slots:
    void on_backBtn_clicked();

    void on_logOutBtn_clicked();

    void on_searchBtn_clicked();

    void on_clearBtn_clicked();

    void on_ordersList_itemDoubleClicked(QListWidgetItem *item);

    void on_sortBox_currentIndexChanged(const QString &arg1);

    void on_refreshBtn_clicked();

private:
    QSqlDatabase dbconn;
    qint32 userId;
    QString orderMethod;
    QString whereArg;

    Ui::CustomerProfile *ui;
    QWidget *par;
    OrderItem *item;

    void removeDataBaseConnection();
    bool getCustomerOrders();
};

#endif // CUSTOMER_PROFILE_H
