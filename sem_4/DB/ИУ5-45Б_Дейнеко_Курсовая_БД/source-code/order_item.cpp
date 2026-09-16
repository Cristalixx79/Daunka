#include "order_item.h"
#include "ui_order_item.h"

#include <QSqlQuery>
#include <QMessageBox>

OrderItem::OrderItem(QWidget *parent, QSqlDatabase db, qint32 idfOrder, qint32 idfUser)
    : QDialog(parent), dbconn(db), orderId_(idfOrder), userId(idfUser), isPaid(false), ui(new Ui::OrderItem)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Заказ");

    if (!this->getOrderItemData())
    {
        QMessageBox::critical(this, "БД", "Невозможно загрузить заказ!");
        return;
    }
}

OrderItem::~OrderItem()
{
    delete ui;
}

bool OrderItem::getOrderItemData()
{
    QSqlQuery query(dbconn);
    query.prepare(QString("SELECT * FROM orders JOIN order_content AS oc ON(orders.order_id = oc.order_id)"
                          "JOIN products AS pr ON(pr.model = oc.product_model)"
                          "WHERE orders.customer_id = :cust_id AND orders.order_id = :order_id"));
    query.bindValue(":cust_id", this->userId);
    query.bindValue(":order_id", this->orderId_);

    if (!query.exec())
    {
        return false;
    }

    if (query.next())
    {
        orderId = query.value("order_id").toString();
        model = query.value("product_model").toString();
        orderDate = query.value("order_date").toString();
        shipDate = query.value("ship_date").toString();
        paidDate = query.value("paid_date").isNull() == false ? query.value("paid_date").toString() : "not paid";
        status = query.value("status").toString();
        quantiy = query.value("quantity").toString();
        price = query.value("price").toString();

        ui->orderItemTb->append("Модель:\t\t" + model);
        ui->orderItemTb->append("Количество:\t" + quantiy);
        ui->orderItemTb->append("Статутс заказа:\t" + status + "\n");
        ui->orderItemTb->append("Дата заказа:\t" + orderDate);
        ui->orderItemTb->append("Дата доставки:\t" + shipDate);
        ui->orderItemTb->append("Дата оплаты:\t" + paidDate + "\n");
        ui->orderItemTb->append("Цена:\t\t$" + price);

        if (paidDate.toLower() != "not paid")
        {
            isPaid = true;
        }
    }
    else
    {
        return false;
    }

    return true;
}

void OrderItem::on_backBtn_clicked()
{
    dbconn = QSqlDatabase();
    this->close();
}

void OrderItem::on_payBtn_clicked()
{
    QMessageBox::StandardButton reply;
    if (isPaid)
    {
        QMessageBox::information(this, "Оплата", "Этот заказ уже оплачен!");
        return;
    }

    reply = QMessageBox::question(this, "Оплата", "Пожалуйста, подтвердите Ваш платёж", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        QSqlQuery query(dbconn);
        query.prepare("UPDATE orders SET paid_date = CURRENT_DATE, status = 'P'"
                      "WHERE status = 'A' AND order_id = :order_id");
        query.bindValue(":order_id", orderId);

        if (!query.exec())
        {
            QMessageBox::critical(this, "Оплата заказа", "Ошибка платежа!");
            return;
        }

        reply = QMessageBox::information(this, "Оплата заказа", "Вы успешно оплатили Ваш заказ!", QMessageBox::Ok);
        if (reply)
        {
            dbconn = QSqlDatabase();
            this->close();
        }
    }
}

void OrderItem::on_deleteBtn_clicked()
{
    QMessageBox::StandardButton reply;
    if (isPaid)
    {
        reply = QMessageBox::information(this, "Отмена заказа", "Вы не можете отменить оплаченный заказ!", QMessageBox::Ok);
        if (reply)
        {
            return;
        }
    }

    reply = QMessageBox::question(this, "Отмена заказа", "Пожалуйста, подтвердите отмену заказа", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        QSqlQuery query(dbconn);
        query.prepare("UPDATE orders SET status = 'C' WHERE order_id = :order_id");
        query.bindValue(":order_id", orderId);

        if (!query.exec())
        {
            QMessageBox::critical(this, "Отмена заказа", "Не удалось отменить заказ!");
        }

        reply = QMessageBox::information(this, "Отмена заказа", "Ваш заказ был отменён!", QMessageBox::Ok);
        if (reply)
        {
            dbconn = QSqlDatabase();
            this->close();
        }
    }
}

bool OrderItem::createInvoicePdf() {
    QString htmlContent = QString(
        "<html>"
        "<head>"
        "  <style>"
        "    body { font-family: Arial, sans-serif; font-size: 12pt; }"
        "    h2 { text-align: center; color: #333; }"
        "    table { width: 100%; border-collapse: collapse; margin-top: 20px; }"
        "    th, td { border: 1px solid #999; padding: 8px; text-align: left; }"
        "    th { background-color: #f2f2f2; }"
        "    .total { text-align: right; font-weight: bold; padding-top: 15px; }"
        "  </style>"
        "</head>"
        "<body>"
        "  <h2>НАКЛАДНАЯ НА ПРОДАННЫЙ ТОВАР № %1</h2>"
        "  <p><b>Дата:</b> %2</p>"
        "  <p><b>Продавец:</b> ООО 'DNS'</p>"
        "  <table>"
        "    <tr>"
        "      <th>№</th>"
        "      <th>Наименование товара</th>"
        "      <th>Кол-во</th>"
        "      <th>Цена</th>"
        "      <th>Сумма</th>"
        "    </tr>"
        "    <tr>"
        "      <td>1</td>"
        "      <td>%3</td>"
        "      <td>%4</td>"
        "      <td>$%5</td>"
        "      <td>$%6</td>"
        "    </tr>"
        "  </table>"
        "  <p class='total'>ИТОГО К ОПЛАТЕ: $%7</p>"
        "  <br><br>"
        "  <p>Отпустил (подпись): ___________________</p>"
        "  <p>Получил (подпись): ___________________</p>"
        "</body>"
        "</html>"
        ).arg(orderId).arg(orderDate).arg(model).arg(quantiy.toInt())
            .arg(price.toInt()).arg(price.toInt() * quantiy.toInt())
            .arg(price.toInt() * quantiy.toInt());

    QString filePath = QFileDialog::getSaveFileName(this,
        "Сохранить накладную", "Накладная_.pdf", "PDF файлы (*.pdf)");

    if (filePath.isEmpty()) {
        return false;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);
    printer.setOutputFileName(filePath);

    QTextDocument document;
    document.setHtml(htmlContent);
    document.print(&printer);

    return true;
}

void OrderItem::on_pushButton_clicked()
{
    if (!this->createInvoicePdf())
    {
        QMessageBox::critical(nullptr, "Ошибка", "Невозможно сохранить накладную!");
    }
}

void OrderItem::deleteOrder(qint32 orderId)
{
    QSqlQuery query(dbconn);
    query.prepare("DELETE FROM orders WHERE order_id = :order_id");
    query.bindValue(":order_id", orderId);
}

bool OrderItem::putNewOrder()
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

bool OrderItem::putNewOrderContent(qint32 orderId)
{
    QSqlQuery query(dbconn);
    query.prepare("INSERT INTO order_content(order_id, product_model, quantity) VALUES (?, ?, ?)");
    query.bindValue(0, orderId);
    query.bindValue(1, this->model);
    query.bindValue(2, quantiy);

    if (!query.exec())
    {
        return false;
    }
    return true;
}

void OrderItem::on_reOrderBtn_clicked()
{
    if (!this->putNewOrder())
    {
        QMessageBox::critical(this, "Заказ", "Не удалось пересоздать заказ!");
        return;
    }
    QMessageBox::information(this, "Заказ", "Заказ был пересоздан!", QMessageBox::Ok);
}
