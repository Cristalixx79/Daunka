#include "product_item_manager.h"
#include "ui_product_item_manager.h"

ProductItemManager::ProductItemManager(QWidget *parent, QSqlDatabase db, QString& md, QString& tp)
    : QDialog(parent), dbconn(db), model(md), type(tp), ui(new Ui::ProductItemManager)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Товар");

    if (!this->getProductInfo())
    {
        QMessageBox::critical(this, "БД", "Невозможно получить характеристики товара!");
        return;
    }
}

ProductItemManager::~ProductItemManager()
{
    delete ui;
}

bool ProductItemManager::getProductInfo()
{
    QSqlQuery query(dbconn);
    query.prepare("SELECT * FROM products WHERE model = :model");
    query.bindValue(":model", model);

    if (!query.exec())
    {
        return false;
    }

    if (query.next())
    {
        ui->modelLe->setText(query.value("model").toString());
        ui->vendorLe->setText(query.value("vendor").toString());
        ui->priceLe->setText(query.value("price").toString());
        ui->inStockLe->setText(query.value("in_stock").toString());
        ui->isAvailable->setChecked(query.value("is_available").toBool());
    }
    return true;
}

void ProductItemManager::on_backBtn_clicked()
{
    dbconn = QSqlDatabase();
    this->close();
}

void ProductItemManager::on_cancelBtn_clicked()
{
    dbconn = QSqlDatabase();
    this->close();
}

void ProductItemManager::on_deleteBtn_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Удаление", "Подтвердите Ваше действие", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QSqlQuery query(dbconn);
        query.prepare(QString("DELETE FROM % WHERE model = %2").arg(type).arg(model));

        if (!query.exec())
        {
            QMessageBox::critical(this, "Удаление", "Не удалось удалить товар!");
            return;
        }

        reply = QMessageBox::information(this, "Удаление", QString("Товар '%1' был удалён!").arg(model), QMessageBox::Ok);
        if (reply)
        {
            dbconn = QSqlDatabase();
            this->close();
        }
    }
}

void ProductItemManager::on_saveBtn_clicked()
{
    QString model = ui->modelLe->text();
    QString vendor = ui->vendorLe->text();
    qreal price = ui->priceLe->text().toDouble();
    qint32 inStock = ui->inStockLe->text().toInt();
    bool isAvailable = ui->isAvailable->isChecked();

    QSqlQuery query(dbconn);
    query.prepare("UPDATE products SET vendor = :v, price = :p, in_stock = :in, is_available = :ia WHERE model = :m");
    query.bindValue(":v", vendor);
    query.bindValue(":p", price);
    query.bindValue(":in", inStock);
    query.bindValue(":ia", isAvailable);
    query.bindValue(":m", model);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Обновление", "Не удалось обновить товар!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, "Обновление", "Товар был обновлён!", QMessageBox::Ok);
    if (reply)
    {
        dbconn = QSqlDatabase();
        this->close();
    }
}
