#include "product_manager.h"
#include "ui_product_manager.h"

ProductManager::ProductManager(QWidget *parent, QSqlDatabase db)
    : QDialog(parent), dbconn(db), ui(new Ui::ProductManager)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Управление товарами");
    ui->comboBox->addItem("количество на складе ⬇");
    ui->comboBox->addItem("количество на складе ⬆");
    ui->comboBox->addItem("цена ⬇");
    ui->comboBox->addItem("цена ⬆");
}

ProductManager::~ProductManager()
{
    delete ui;
}

bool ProductManager::getDatabaseProducts()
{
    QSqlQuery query(dbconn);
    query.prepare(QString("SELECT * FROM products ORDER BY %1").arg(orderMethod));

    if (!query.exec())
    {
        return false;
    }

    ui->productCount->setText(QString("Всего товаров: %1").arg(query.size()));

    while (query.next())
    {
        QString model = query.value(0).toString();
        QString type = query.value(1).toString();
        QString vendor = query.value(2).toString();
        qreal price = query.value(3).toDouble();
        qint32 inStock = query.value(4).toInt();

        QString text = model + "\t" + vendor + "\t\t" + QString("$%1").arg(price) + "\t" + QString("%1").arg(inStock);
        QListWidgetItem *item = new QListWidgetItem(QIcon(QString("/home/student/Main/img/%1.png").arg(type)), text);
        if (item)
        {
            ui->productList->addItem(item);
        }
    }
    return true;
}

void ProductManager::on_backBtn_clicked()
{
    dbconn = QSqlDatabase();
    this->close();
}

void ProductManager::on_searchBtn_clicked()
{
    QString search = ui->searchLe->text().trimmed();
    if (search == nullptr)
    {
        return;
    }

    QSqlQuery query(dbconn);
    query.prepare(QString("SELECT * FROM products WHERE model LIKE '%1%' ORDER BY model").arg(search.toLower()));

    if (!query.exec())
    {
        return;
    }

    if (query.size() == 0)
    {
        QMessageBox::warning(this, "БД", QString("Ничего не найдено по запросу '%1'").arg(search));
        ui->searchLe->clear();
        return;
    }

    ui->productCount->setText(QString("Всего товаров: %1").arg(query.size()));

    ui->productList->clear();
    while (query.next())
    {
        QString model = query.value(0).toString();
        QString type = query.value(1).toString();
        QString vendor = query.value(2).toString();
        qreal price = query.value(3).toDouble();
        qint32 inStock = query.value(4).toInt();

        QString text = model + "\t" + vendor + "\t" + QString("$%1").arg(price) + "\t" + QString("%1").arg(inStock);
        QListWidgetItem *item = new QListWidgetItem(QIcon(QString("/home/student/Main/img/%1.png").arg(type)), text);
        if (item)
        {
            ui->productList->addItem(item);
        }
    }
}

void ProductManager::on_clearBtn_clicked()
{
    if (ui->searchLe->text().size() == 0)
    {
        return;
    }

    ui->searchLe->clear();
    ui->productList->clear();
    this->getDatabaseProducts();
}

void ProductManager::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        return;
    }

    if (arg1 == "количество на складе ⬇")
    {
        orderMethod = "in_stock DESC";
    }
    else if (arg1 == "количество на складе ⬆")
    {
        orderMethod = "in_stock ASC";
    }
    else if (arg1 == "цена ⬇")
    {
        orderMethod = "price DESC";
    }
    else if (arg1 == "цена ⬆")
    {
        orderMethod = "price ASC";
    }

    if (ui->productList->size().isEmpty())
    {
        return;
    }
    ui->productList->clear();
    if (!this->getDatabaseProducts())
    {
        QMessageBox::critical(this, "БД", "Не удалось получить список товаров");
        return;
    }
}

void ProductManager::on_productList_itemDoubleClicked(QListWidgetItem *item)
{
    QString model = QString(item->text().split("\t")[0]).trimmed();
    QString type = QString(item->text().split("\t")[1]).trimmed();
    pim = new ProductItemManager(this, dbconn, model, type);
    if (pim && model != "")
    {
        pim->show();
    }
}

void ProductManager::on_addBtn_clicked()
{
    np = new NewProduct(this, dbconn);
    if (np)
    {
        np->show();
    }
}
