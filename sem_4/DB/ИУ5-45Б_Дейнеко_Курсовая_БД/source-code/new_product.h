#ifndef NEW_PRODUCT_H
#define NEW_PRODUCT_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
    class NewProduct;
}

class NewProduct : public QDialog {
    Q_OBJECT
public:
    explicit NewProduct(QWidget *parent, QSqlDatabase db);
    ~NewProduct();
private slots:
    void on_backBtn_clicked();

    void on_cancelBtn_clicked();

    void on_saveBtn_clicked();

private:
    Ui::NewProduct *ui;
    QSqlDatabase dbconn;
};

#endif // NEW_PRODUCT_H
