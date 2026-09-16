#include "new_product.h"
#include "ui_new_product.h"

NewProduct::NewProduct(QWidget *parent, QSqlDatabase db)
    : QDialog(parent), dbconn(db), ui(new Ui::NewProduct)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Новый товар");
}

NewProduct::~NewProduct()
{
    delete ui;
}

void NewProduct::on_backBtn_clicked()
{
    dbconn = QSqlDatabase();
    this->close();
}

void NewProduct::on_cancelBtn_clicked()
{
    dbconn = QSqlDatabase();
    this->close();
}

void NewProduct::on_saveBtn_clicked()
{
    QString model = ui->modelLe->text().trimmed();
    QString type = ui->typeLe->text().trimmed();
    QString vendor = ui->vendorLe->text().trimmed();
    qreal price = ui->priceLe->text().trimmed().toDouble();
    if (price == 0)
    {
        QMessageBox::warning(this, "Товар", "Цена должна быть положительным числом");
        return;
    }
    qint32 inStock = ui->inStockLe->text().trimmed().toInt();
    bool isAvalable = ui->isAvailable->isChecked();

    QSqlQuery query(dbconn);
    query.prepare("INSERT INTO products(model, product_type, vendor, price, in_stock, is_available) VALUES"
                  "(?, ?, ?, ?, ?, ?)");
    query.bindValue(0, model);
    query.bindValue(1, type);
    query.bindValue(2, vendor);
    query.bindValue(3, price);
    query.bindValue(4, inStock);
    query.bindValue(5, isAvalable);

    QMessageBox::StandardButton reply;
    if (!query.exec())
    {
        QMessageBox::critical(this, "Добавление", "Не удалось добавить товар", QMessageBox::Ok);
        return;
    }

    reply = QMessageBox::information(this, "Добавление", "Товар был добавлен", QMessageBox::Ok);
    if (reply)
    {
        dbconn = QSqlDatabase();
        this->close();
    }
}
