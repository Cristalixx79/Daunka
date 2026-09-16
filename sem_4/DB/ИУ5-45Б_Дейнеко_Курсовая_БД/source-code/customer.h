#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QDialog>
#include <QStringList>
#include <QSqlDatabase>
#include <QListWidgetItem>

#include "product_item.h"
#include "customer_profile.h"

namespace Ui {
    class Customer;
}

class Customer : public QDialog {
    Q_OBJECT
public:
    explicit Customer(QWidget *parent, qint32 idf);
    ~Customer();
private slots:

    void on_searchBtn_clicked();

    void on_clearBtn_clicked();

    void on_profileBtn_clicked();

    void on_productList_itemDoubleClicked(QListWidgetItem *item);

    void on_sortBox_currentIndexChanged(const QString &arg1);

private:
    Ui::Customer *ui;
    QSqlDatabase dbconn;
    qint32 userId;
    QString orderMethod;

    ProductItem *prItem;
    CustomerProfile *profile;

    bool setDataBaseConnection();
    void removeDataBaseConnection();

    bool getDataBaseProductList();
};

#endif // CUSTOMER_H
