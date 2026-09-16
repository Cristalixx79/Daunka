#ifndef PRODUCT_ITEM_MANAGER_H
#define PRODUCT_ITEM_MANAGER_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
    class ProductItemManager;
}

class ProductItemManager : public QDialog {
    Q_OBJECT
public:
    explicit ProductItemManager(QWidget *parent, QSqlDatabase db, QString& md, QString& tp);
    ~ProductItemManager();
private slots:
    void on_backBtn_clicked();

    void on_cancelBtn_clicked();

    void on_deleteBtn_clicked();

    void on_saveBtn_clicked();

private:
    Ui::ProductItemManager *ui;
    QSqlDatabase dbconn;
    QString model;
    QString type;

    bool getProductInfo();
};

#endif // PRODUCT_ITEM_MANAGER_H
