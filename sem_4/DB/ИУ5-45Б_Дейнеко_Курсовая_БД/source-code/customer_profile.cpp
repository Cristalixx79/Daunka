#include "customer_profile.h"
#include "ui_customer_profile.h"

#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>

CustomerProfile::CustomerProfile(QWidget *parent, QSqlDatabase db, qint32 idf)
    : QDialog(parent), dbconn(db), userId(idf), ui(new Ui::CustomerProfile)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Профиль клиента");

    ui->noCanceledCb->setChecked(true);
    whereArg = "AND status != 'C' ";

    ui->sortBox->addItem("самые новые");
    ui->sortBox->addItem("самые старые");
    ui->sortBox->addItem("количество ⬇");
    ui->sortBox->addItem("количество ⬆");
    ui->sortBox->addItem("цена ⬇");
    ui->sortBox->addItem("цена ⬆");
}

CustomerProfile::~CustomerProfile()
{
    delete ui;
}

void CustomerProfile::removeDataBaseConnection()
{
    if (dbconn.isOpen())
    {
        dbconn.close();
    }

    QString connectionName = dbconn.connectionName();
    if (!connectionName.isEmpty()) {
        dbconn = QSqlDatabase();
        QSqlDatabase::removeDatabase(connectionName);
    }
}

bool CustomerProfile::getCustomerOrders()
{
    if (orderMethod == "")
    {
        return false;
    }
    ui->ordersList->clear();

    QSqlQuery query(dbconn);
    query.prepare(QString("SELECT * FROM orders JOIN order_content AS oc ON(orders.order_id = oc.order_id)"
                          "JOIN products AS pr ON(pr.model = oc.product_model)"
                          "WHERE orders.customer_id = :cust_id %1 ORDER BY %2").arg(whereArg).arg(orderMethod));
    query.bindValue(":cust_id", this->userId);

    if (!query.exec())
    {
        return false;
    }

    ui->orderCountLb->setText(QString("Всего заказов: %1").arg(query.size()));

    qint32 i = 1;
    while (query.next())
    {
        QString orderId = query.value("order_id").toString();
        QString model = query.value("product_model").toString().toUpper();
        QString orderDate = query.value("order_date").toString().toUpper();
        QString shipDate = query.value("ship_date").toString().toUpper();
        QString paidDate = query.value("paid_date").isNull() == false ? query.value("paid_date").toString().toUpper() : "Not paid";
        QString status = query.value("status").toString().toUpper();
        QString quantiy = query.value("quantity").toString().toUpper();
        QString price = query.value("price").toString();

        QString orderText = model + "\t" + quantiy
                + "\t" + status + "\t$" + price + "\t" + orderDate + "\t\t"
                + shipDate + "\t\t" + paidDate;
        if (orderText != nullptr)
        {
            QListWidgetItem *item = nullptr;
            if (model.toLower().startsWith("pc"))
            {
                item = new QListWidgetItem(QIcon("/home/student/Main/img/pc.png"), QString("%1 ) ").arg(orderId) + orderText);
                ui->ordersList->addItem(item);
            }
            else if (model.toLower().startsWith("lp"))
            {
                item = new QListWidgetItem(QIcon("/home/student/Main/img/laptop.png"), QString("%1 ) ").arg(orderId) + orderText);
                ui->ordersList->addItem(item);
            }
            else if (model.toLower().startsWith("pr"))
            {
                item = new QListWidgetItem(QIcon("/home/student/Main/img/printer.png"), QString("%1 ) ").arg(orderId) + orderText);
                ui->ordersList->addItem(item);
            }
            else if (model.toLower().startsWith("rt"))
            {
                item = new QListWidgetItem(QIcon("/home/student/Main/img/router.png"), QString("%1 ) ").arg(orderId) + orderText);
                ui->ordersList->addItem(item);
            }
            else
            {
                continue;
            }
        }
        i++;
    }

    return true;
}

void CustomerProfile::on_backBtn_clicked()
{
    this->close();
    dbconn = QSqlDatabase();
    this->parentWidget()->show();
}

void CustomerProfile::on_logOutBtn_clicked()
{
    this->removeDataBaseConnection();
    this->close();
    this->parentWidget()->close();
    this->parentWidget()->parentWidget()->show();
}

void CustomerProfile::on_searchBtn_clicked()
{
    QString search = ui->searchLe->text().trimmed();
    if (search == nullptr)
    {
        return;
    }

    QSqlQuery query(dbconn);
    query.prepare(QString("SELECT * FROM orders JOIN order_content AS oc ON(orders.order_id = oc.order_id) "
                          "JOIN products AS pr ON(pr.model = oc.product_model) "
                          "WHERE orders.customer_id = :cust_id AND oc.product_model LIKE '%1%'").arg(search.toLower()));
    query.bindValue(":cust_id", userId);

    if (!query.exec())
    {
        return;
    }

    ui->orderCountLb->setText(QString("Всего заказов: %1").arg(query.size()));

    if (query.size() == 0)
    {
        QMessageBox::warning(this, "Поиск", QString("Ничего не найдено по запросу '%1'").arg(search));
        ui->searchLe->clear();
        return;
    }

    ui->ordersList->clear();
    qint32 i = 1;
    while (query.next())
    {
        QString orderId = query.value("order_id").toString();
        QString model = query.value("product_model").toString().toUpper();
        QString orderDate = query.value("order_date").toString().toUpper();
        QString shipDate = query.value("ship_date").toString().toUpper();
        QString paidDate = query.value("paid_date").isNull() == false ? query.value("paid_date").toString().toUpper() : "Not paid";
        QString status = query.value("status").toString().toUpper();
        QString quantiy = query.value("quantity").toString().toUpper();
        QString price = query.value("price").toString();

        QString orderText = model + "\t" + quantiy
                + "\t" + status + "\t$" + price + "\t" + orderDate + "\t\t"
                + shipDate + "\t\t" + paidDate;
        if (orderText != nullptr)
        {
            QListWidgetItem *item = nullptr;
            if (model.toLower().startsWith("pc"))
            {
                item = new QListWidgetItem(QIcon("/home/student/Main/img/pc.png"), QString("%1 ) ").arg(orderId) + orderText);
                ui->ordersList->addItem(item);
            }
            else if (model.toLower().startsWith("lp"))
            {
                item = new QListWidgetItem(QIcon("/home/student/Main/img/laptop.png"), QString("%1 ) ").arg(orderId) + orderText);
                ui->ordersList->addItem(item);
            }
            else if (model.toLower().startsWith("pr"))
            {
                item = new QListWidgetItem(QIcon("/home/student/Main/img/printer.png"), QString("%1 ) ").arg(orderId) + orderText);
                ui->ordersList->addItem(item);
            }
            else if (model.toLower().startsWith("rt"))
            {
                item = new QListWidgetItem(QIcon("/home/student/Main/img/router.png"), QString("%1 ) ").arg(orderId) + orderText);
                ui->ordersList->addItem(item);
            }
            else
            {
                continue;
            }
        }
        i++;
    }
}

void CustomerProfile::on_clearBtn_clicked()
{
    if (ui->searchLe->text().size() == 0)
    {
        return;
    }

    ui->searchLe->clear();
    ui->ordersList->clear();

    this->getCustomerOrders();
}

void CustomerProfile::on_ordersList_itemDoubleClicked(QListWidgetItem *item)
{
    QString id = item->text().split(" ")[0];
    if (id == nullptr)
    {
        return;
    }

    this->item = new OrderItem(this, dbconn, id.toInt(), userId);
    if (this->item)
    {
        this->item->show();
    }
    else
    {
        return;
    }
}

void CustomerProfile::on_sortBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        return;
    }

    if (arg1 == "самые старые")
    {
        orderMethod = "order_date ASC";
    }
    else if (arg1 == "самые новые")
    {
        orderMethod = "order_date DESC";
    }
    else if (arg1 == "количество ⬆")
    {
        orderMethod = "quantity ASC";
    }
    else if (arg1 == "количество ⬇")
    {
        orderMethod = "quantity DESC";
    }
    else if (arg1 == "цена ⬆")
    {
        orderMethod = "price ASC";
    }
    else if (arg1 == "цена ⬇")
    {
        orderMethod = "price DESC";
    }

    if (!this->getCustomerOrders())
    {
        QMessageBox::critical(this, "БД", "Невозможно получить список заказов");
        return;
    }
}

void CustomerProfile::on_refreshBtn_clicked()
{
    whereArg = "";
    if (ui->notPaidCb->isChecked())
    {
        whereArg += "AND paid_date IS NULL ";
    }
    if (ui->noCanceledCb->isChecked())
    {
        whereArg += "AND status != 'C' ";
    }
    this->getCustomerOrders();
}
