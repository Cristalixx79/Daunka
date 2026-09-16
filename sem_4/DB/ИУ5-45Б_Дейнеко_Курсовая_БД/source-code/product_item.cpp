#include "product_item.h"
#include "ui_product_item.h"

#include <QMessageBox>
#include <QPixmap>
#include <QDate>
#include <QSqlQuery>

ProductItem::ProductItem(QWidget *parent, QSqlDatabase db, QStringList lst, qint32 idf)
    : QDialog(parent), dbconn(db), userId(idf), ui(new Ui::ProductItem)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Товар");

    ui->quantity->setMinimum(1);
    ui->quantity->setMaximum(10);
    this->type = lst[0];
    this->model = lst[1];
    this->routeProductInfo(lst);
}

ProductItem::~ProductItem()
{
    delete ui;
}

void ProductItem::routeProductInfo(QStringList lst)
{
    if (this->type == "pc")
    {
        this->getPcProductItemInfo(lst);
    }
    else if (this->type == "laptop")
    {
        this->getLaptopProductItemInfo(lst);
    }
    else if (this->type == "printer")
    {
        this->getPrinterProductItemInfo(lst);
    }
    else if (this->type == "router")
    {
        this->getRouterProductItemInfo(lst);
    }
}

void ProductItem::getPcProductItemInfo(QStringList lst)
{
    ui->productItemImg->setPixmap(QPixmap("/home/student/Main/img/pc.png"));

    QSqlQuery query(dbconn);
    query.prepare("SELECT * FROM pc JOIN products AS pr ON(pr.model = pc.model) WHERE pc.model = :model");
    query.bindValue(":model", this->model);

    if (!query.exec())
    {
        this->close();
    }

    while (query.next())
    {
        ui->productItemTb->append("Product:\t\t" + lst[0].toUpper() + "\n\nModel:\t\t" + query.value("model").toString().toUpper()
            + "\nVendor:\t\t" + lst[2].toUpper() + "\nProcessor:\t\t" + query.value("processor").toString().toUpper()
            + "\nRam:\t\t" + query.value("ram").toString().toUpper() + "\n\nPrice: \t\t$" + query.value("price").toString());
    }
}

void ProductItem::getPrinterProductItemInfo(QStringList lst)
{
    ui->productItemImg->setPixmap(QPixmap("/home/student/Main/img/printer.png"));

    QSqlQuery query(dbconn);
    query.prepare("SELECT * FROM printer JOIN products AS pr ON(pr.model = printer.model) WHERE printer.model = :model");
    query.bindValue(":model", this->model);

    if (!query.exec())
    {
        this->close();
    }

    while (query.next())
    {
        ui->productItemTb->append("Product:\t\t" + lst[0].toUpper() + "\n\nModel:\t\t" + query.value("model").toString().toUpper()
            + "\nVendor:\t\t" + lst[2].toUpper() + "\nType:\t\t" + query.value("printer_type").toString().toUpper()
            + "\n\nPrice: \t\t$" + query.value("price").toString());
    }
}

void ProductItem::getLaptopProductItemInfo(QStringList lst)
{
    ui->productItemImg->setPixmap(QPixmap("/home/student/Main/img/laptop.png"));

    QSqlQuery query(dbconn);
    query.prepare("SELECT * FROM laptop JOIN products AS pr ON(pr.model = laptop.model) WHERE laptop.model = :model");
    query.bindValue(":model", this->model);

    if (!query.exec())
    {
        this->close();
    }

    while (query.next())
    {
        ui->productItemTb->append("Product:\t\t" + lst[0].toUpper() + "\n\nModel:\t\t" + query.value("model").toString().toUpper()
            + "\nVendor:\t\t" + lst[2].toUpper() + "\nProcessor:\t\t" + query.value("processor").toString().toUpper()
            + "\nRam:\t\t" + query.value("ram").toString().toUpper() + "\n\nPrice: \t\t$" + query.value("price").toString());
    }
}

void ProductItem::getRouterProductItemInfo(QStringList lst)
{
    ui->productItemImg->setPixmap(QPixmap("/home/student/Main/img/router.png"));

    QSqlQuery query(dbconn);
    query.prepare("SELECT * FROM router JOIN products AS pr ON(pr.model = router.model) WHERE router.model = :model");
    query.bindValue(":model", this->model);

    if (!query.exec())
    {
        this->close();
    }

    while (query.next())
    {
        ui->productItemTb->append("Product:\t\t" + lst[0].toUpper() + "\n\nModel:\t\t" + query.value("model").toString().toUpper()
            + "\nVendor:\t\t" + lst[2].toUpper() + "\nFrequency:\t\t" + query.value("frequency").toString().toUpper() + " GHz" +
            + "\nBandwidth:\t\t" + query.value("bandwidth").toString().toUpper() + " Mbit/s"
            + "\n\nPrice: \t\t$" + query.value("price").toString());
    }
}

void ProductItem::deleteOrder(qint32 orderId)
{
    QSqlQuery query(dbconn);
    query.prepare("DELETE FROM orders WHERE order_id = :order_id");
    query.bindValue(":order_id", orderId);
}

bool ProductItem::putNewOrder()
{
    QSqlQuery query(dbconn);
    query.prepare("INSERT INTO orders(customer_id, order_date, ship_date, paid_date, status)"
                          "VALUES (?, CURRENT_DATE, CURRENT_DATE, NULL, 'A')");
    query.bindValue(0, userId);

    if (!query.exec())
    {
        QMessageBox::warning(this, "Заказ", "Не удалось добавить товар в корзину");
        return false;
    }

    query.prepare("SELECT order_id FROM orders ORDER BY order_id DESC LIMIT 1");
    if (!query.exec())
    {
        QMessageBox::warning(this, "Заказ", "Не удалось дзагрузить товар");
        return false;
    }

    qint32 order_id = 0;
    if (query.next()) {
        order_id = query.value("order_id").toInt();
    }

    if (!this->putNewOrderContent(order_id))
    {
        QMessageBox::warning(this, "Заказ", "Не удалось добавить товар в корзину");
        this->deleteOrder(order_id);
        return false;
    }
    return true;
}

bool ProductItem::putNewOrderContent(qint32 orderId)
{
    qint8 quantity = ui->quantity->value();
    QSqlQuery query(dbconn);
    query.prepare("INSERT INTO order_content(order_id, product_model, quantity) VALUES (?, ?, ?)");
    query.bindValue(0, orderId);
    query.bindValue(1, this->model);
    query.bindValue(2, quantity);

    if (!query.exec())
    {
        return false;
    }
    return true;
}

void ProductItem::on_productItemBack_clicked()
{
    this->close();
    dbconn = QSqlDatabase();
    this->parentWidget()->show();
}

void ProductItem::on_productItemOrder_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Заказ", "Пожалуйста, подтвердите Ваш заказ", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        if (this->putNewOrder())
        {
            QMessageBox::about(this, "Заказ", "Ваш заказ был создан!");
            dbconn = QSqlDatabase();
            this->close();
        }
    }
    else
    {
        QMessageBox::critical(this, "Заказ", "Произошла ошибка при создании Вашего заказа, попробуйте снова!");
        dbconn = QSqlDatabase();
        this->close();
    }
}
