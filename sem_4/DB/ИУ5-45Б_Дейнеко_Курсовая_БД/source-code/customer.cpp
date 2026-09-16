#include "customer.h"
#include "ui_customer.h"

#include <QMessageBox>
#include <QSqlQuery>

Customer::Customer(QWidget *parent, qint32 idf)
    : QDialog(parent), userId(idf), ui(new Ui::Customer)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Клиент");

    if (!this->setDataBaseConnection())
    {
        QMessageBox::critical(this, "Подключение", "Невозможно подклучиться к БД!");
        return;
    }

    ui->sortBox->addItem("модель ⬆");
    ui->sortBox->addItem("модель ⬇");
    ui->sortBox->addItem("производитель ⬆");
    ui->sortBox->addItem("производитель ⬇");
    ui->sortBox->addItem("цена ⬆");
    ui->sortBox->addItem("цена ⬇");
}

Customer::~Customer()
{
    this->removeDataBaseConnection();
    delete ui;
}

bool Customer::setDataBaseConnection()
{
    QString connectionName = "Customer";
    dbconn = QSqlDatabase::addDatabase("QPSQL", connectionName);
    dbconn.setDatabaseName("AIS");
    dbconn.setHostName("localhost");
    dbconn.setUserName("ais_customer");
    dbconn.setPassword("cust");

    if (!dbconn.open())
    {
        ui->customerInfoTb->append("Невозможно подклучиться к БД");
        return false;
    }
    ui->customerInfoTb->append("Подключение установлено");
    return true;
}

bool Customer::getDataBaseProductList()
{
    if (orderMethod == "")
    {
        return false;
    }
    ui->productList->clear();

    QSqlQuery query(dbconn);
    QString select = QString("SELECT * FROM products WHERE is_available = true ORDER BY %1")
            .arg(orderMethod);

    if (!query.exec(select))
    {
        ui->customerInfoTb->append("Невозможно получить список товаров!");
        return false;
    }

    ui->productCountLb->setText(QString("Всего товаров: %1").arg(query.size()));

    while (query.next())
    {
        QString model = query.value(0).toString();
        QString type = query.value(1).toString();
        QString vendor = query.value(2).toString();
        qreal price = query.value(3).toDouble();

        QString itemText = type + "\t" + model + "\t" + vendor + "\t\t" + QString("$%1").arg(price);

        QListWidgetItem *item = nullptr;
        if (type.toLower() == "pc")
        {
            item = new QListWidgetItem(QIcon(QString("/home/student/Main/img/%1.png").arg(type)), itemText);
            if (item)
            {
                ui->productList->addItem(item);
            }
        }
        if (type.toLower() == "laptop")
        {
            item = new QListWidgetItem(QIcon(QString("/home/student/Main/img/%1.png").arg(type)), itemText);
            if (item)
            {
                ui->productList->addItem(item);
            }
        }
        else if (type.toLower() == "printer")
        {
            item = new QListWidgetItem(QIcon(QString("/home/student/Main/img/%1.png").arg(type)), itemText);
            if (item)
            {
                ui->productList->addItem(item);
            }
        }
        else if (type.toLower() == "router")
        {
            item = new QListWidgetItem(QIcon(QString("/home/student/Main/img/%1.png").arg(type)), itemText);
            if (item)
            {
                ui->productList->addItem(item);
            }
        }
        else
        {
            continue;
        }
    }
    return true;
}

void Customer::removeDataBaseConnection()
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

void Customer::on_searchBtn_clicked()
{
    QString search = ui->searchLe->text().trimmed();
    if (search == nullptr)
    {
        return;
    }

    QSqlQuery query(dbconn);
    query.prepare(QString("SELECT * FROM products WHERE is_available = true AND model LIKE '%1%'").arg(search.toLower()));

    if (!query.exec())
    {
        return;
    }

    if (query.size() == 0)
    {
        QMessageBox::warning(this, "Поиск", QString("Ничего не найдено по запросу '%1'").arg(search));
        ui->searchLe->clear();
        return;
    }

    ui->productCountLb->setText(QString("Всего товаров: %1").arg(query.size()));

    ui->productList->clear();
    while (query.next())
    {
        QString model = query.value(0).toString();
        QString type = query.value(1).toString();
        QString vendor = query.value(2).toString();
        qreal price = query.value(3).toDouble();

        QString itemText = type + "\t" + model + "\t" + vendor + "\t" + QString("$%1").arg(price);

        QListWidgetItem *item = nullptr;
        if (type.toLower() == "pc")
        {
            item = new QListWidgetItem(QIcon(QString("/home/student/Main/img/%1.png").arg(type)), itemText);
            if (item)
            {
                ui->productList->addItem(item);
            }
        }
        if (type.toLower() == "laptop")
        {
            item = new QListWidgetItem(QIcon(QString("/home/student/Main/img/%1.png").arg(type)), itemText);
            if (item)
            {
                ui->productList->addItem(item);
            }
        }
        else if (type.toLower() == "printer")
        {
            item = new QListWidgetItem(QIcon(QString("/home/student/Main/img/%1.png").arg(type)), itemText);
            if (item)
            {
                ui->productList->addItem(item);
            }
        }
        else if (type.toLower() == "router")
        {
            item = new QListWidgetItem(QIcon(QString("/home/student/Main/img/%1.png").arg(type)), itemText);
            if (item)
            {
                ui->productList->addItem(item);
            }
        }
        else
        {
            continue;
        }
    }
}

void Customer::on_clearBtn_clicked()
{
    if (ui->searchLe->text().size() == 0)
    {
        return;
    }

    ui->searchLe->clear();
    ui->productList->clear();

    this->getDataBaseProductList();
}

void Customer::on_profileBtn_clicked()
{
    profile = new CustomerProfile(this, dbconn, this->userId);
    if (profile)
    {
        profile->show();
    }
}

void Customer::on_productList_itemDoubleClicked(QListWidgetItem *item)
{
    QStringList lst = item->text().toLower().split("\t");
    prItem = new ProductItem(this, dbconn, lst, userId);
    if (prItem)
    {
        prItem->show();
    }
}

void Customer::on_sortBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        return;
    }

    if (arg1 == "модель ⬆")
    {
        orderMethod = "model ASC";
    }
    else if (arg1 == "модель ⬇")
    {
        orderMethod = "model DESC";
    }
    else if (arg1 == "производитель ⬆")
    {
        orderMethod = "vendor ASC";
    }
    else if (arg1 == "производитель ⬇")
    {
        orderMethod = "vendor DESC";
    }
    else if (arg1 == "цена ⬆")
    {
        orderMethod = "price ASC";
    }
    else if (arg1 == "цена ⬇")
    {
        orderMethod = "price DESC";
    }

    if (!this->getDataBaseProductList())
    {
        QMessageBox::critical(this, "БД", "Невозможно получить список товаров");
        return;
    }
}
