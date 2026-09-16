#include "client_profile.h"
#include "ui_client_profile.h"

ClientProfile::ClientProfile(QWidget *parent, QSqlDatabase db, QString usern)
    : QDialog(parent), dbconn(db), username(usern), ui(new Ui::ClientProfile)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Профиль клиента");
    ui->clientInfoLb->setText(QString("Профиль пользователя %1").arg(usern));
    ui->clientOrdersLb->setText(QString("Заказы пользователя %1").arg(usern));

    if (!this->getClientOrders())
    {
        QMessageBox::critical(this, "БД", QString("Невозможно загрузить заказы пользователя %1").arg(username));
        return;
    }
}

ClientProfile::~ClientProfile()
{
    delete ui;
}

bool ClientProfile::getClientOrders()
{
    QSqlQuery query(dbconn);
    query.prepare("SELECT user_id FROM users WHERE username = :name");
    query.bindValue(":name", username);

    if (!query.exec())
    {
        return false;
    }

    qint32 userId = 0;
    if (query.next())
    {
        userId = query.value(0).toInt();
    }

    query.prepare("SELECT * FROM orders JOIN order_content AS oc ON(oc.order_id = orders.order_id)"
                  "JOIN products AS pr ON(pr.model = oc.product_model)"
                  "WHERE orders.customer_id = :cust_id");
    query.bindValue(":cust_id", userId);

    if (!query.exec())
    {
        return false;
    }

    double sumSpent = 0.0;
    while (query.next())
    {
        QString orderId = query.value("order_id").toString();
        QString model = query.value("product_model").toString();
        QString quantity = query.value("quantity").toString();
        QString orderDate = query.value("order_date").toString();
        QString shipDate = query.value("ship_date").toString();
        QString paidDate = query.value("paid_date").toString();
        QString status = query.value("status").toString();
        if (paidDate == "")
        {
            paidDate = "not paid";
        }
        double price = query.value("price").toDouble();
        sumSpent += price * quantity.toInt();

        QString itemText = orderId + " ) " + model + " \t" + quantity + "\t" + orderDate
                + "\t\t" + shipDate + "\t\t" + paidDate + "\t\t" + status;

        QListWidgetItem *item = new QListWidgetItem(QIcon("/home/student/Main/img/order.svg"), itemText);
        if (item)
        {
            ui->clientOrders->addItem(item);
        }
    }

    ui->clientInfo->append(QString("Пользователь:\t\t%1").arg(username));
    ui->clientInfo->append(QString("Кол-во заказов:\t%1").arg(query.size()));
    ui->clientInfo->append(QString("Денег потрачено:\t$%1").arg(sumSpent));

    return true;
}

void ClientProfile::on_backBtn_clicked()
{
    dbconn = QSqlDatabase();
    this->close();
}

void ClientProfile::on_banBtn_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Заблокировать", "Пожалуйста, подтвердите Ваше действие!", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QSqlQuery query(dbconn);
        query.prepare("DELETE FROM users WHERE username = :usern");
        query.bindValue(":usern", username);

        if (!query.exec())
        {
            QMessageBox::critical(this, "DELETE action", QString("Невозможно заблокировать пользователя! '%1'").arg(username));
        }

        QMessageBox::about(this, "DELETE action", QString("Пользователь '%1' был заблокирован!").arg(username));
        if (reply)
        {
            dbconn = QSqlDatabase();
            this->close();
        }
    }
}

void ClientProfile::on_clientOrders_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Отмена", "Отменить заказ", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        if (!item->text().contains("not paid"))
        {
            reply = QMessageBox::information(this, "Отмена заказа", "Невозможно отменить оплаченный заказ", QMessageBox::Ok);
            if (reply)
            {
                return;
            }
        }
        qint32 orderId = QString(item->text().split(" ")[0]).toInt();
        QSqlQuery query(dbconn);
        query.prepare("UPDATE orders SET status = 'C' WHERE order_id = :order_id");
        query.bindValue(":order_id", orderId);

        if (!query.exec())
        {
            QMessageBox::critical(this, "Отмена заказа", "Невозможно отменить заказ");
            return;
        }

        reply = QMessageBox::information(this, "Отмена заказа", "Заказ отменён!", QMessageBox::Ok);
        if (reply)
        {
            return;
        }
    }
}

void ClientProfile::on_refreshBtn_clicked()
{
    ui->clientInfo->clear();
    ui->clientOrders->clear();

    this->getClientOrders();
}
