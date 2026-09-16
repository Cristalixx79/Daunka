#include "manager.h"
#include "ui_manager.h"

Manager::Manager(QWidget *parent)
    : QDialog(parent), chartView(nullptr), ui(new Ui::Manager)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Менеджер");

    if (!this->setDataBaseConnection())
    {
        QMessageBox::critical(this, "БД", "Не удалось подключится к БД!");
        return;
    }

    ui->statisticsSort->addItem("самые активные клиенты (топ 5)");
    ui->statisticsSort->addItem("самые неактивные клиенты (топ 5)");
    ui->statisticsSort->addItem("самые продаваемые позиции (топ 5)");
    ui->statisticsSort->addItem("самые непродаваемые позиции (топ 5)");
    ui->statisticsSort->addItem("продажи по категориям");
}

void Manager::renderChart(QSqlQuery *q)
{
    if (q == nullptr)
    {
        return;
    }

    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    qint32 i = 0;
    while (q->next())
    {
        QString v1 = q->value(0).toString();
        qreal v2 = q->value(1).toReal();
        series->append(QString("%1 -- %2 шт").arg(v1).arg(v2), v2);
        series->slices().at(i)->setLabelVisible();
        i++;
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle(ui->statisticsSort->currentText());
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->legend()->setAlignment(Qt::AlignRight);

    if (chartView != nullptr)
    {
        chartView->close();
    }

    chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chartView);
}

bool Manager::getStatistics()
{
    if (orderMethod == "")
    {
        return false;
    }

    QSqlQuery query(dbconn);
    if (orderMethod == "самые активные клиенты (топ 5)")
    {
        query.prepare("SELECT * FROM v_most_active_clients LIMIT 5");
        if (!query.exec())
        {
            return false;
        }

        this->renderChart(&query);
    }
    else if (orderMethod == "самые неактивные клиенты (топ 5)")
    {
        query.prepare("SELECT * FROM v_most_inactive_clients LIMIT 5");
        if (!query.exec())
        {
            return false;
        }

        this->renderChart(&query);
    }
    else if (orderMethod == "продажи по категориям")
    {
        query.prepare("SELECT * FROM v_most_sold_products");
        if (!query.exec())
        {
            return false;
        }

        this->renderChart(&query);
    }
    else if (orderMethod == "самые продаваемые позиции (топ 5)")
    {
        query.prepare("SELECT * FROM v_most_sold_items LIMIT 5");
        if (!query.exec())
        {
            return false;
        }

        this->renderChart(&query);
    }
    else if (orderMethod == "самые непродаваемые позиции (топ 5)")
    {
        query.prepare("SELECT * FROM v_least_sold_items LIMIT 5");
        if (!query.exec())
        {
            return false;
        }

        this->renderChart(&query);
    }
    else
    {
        return false;
    }
    return true;
}

bool Manager::setDataBaseConnection()
{
    this->removeDataBaseConnection();

    QString connectionName = "Manager";
    dbconn = QSqlDatabase::addDatabase("QPSQL", connectionName);
    dbconn.setDatabaseName("AIS");
    dbconn.setHostName("localhost");
    dbconn.setUserName("ais_manager");
    dbconn.setPassword("manager");

    if (!dbconn.open())
    {
        return false;
    }
    return true;
}

Manager::~Manager()
{
    this->removeDataBaseConnection();
    delete ui;
}

void Manager::removeDataBaseConnection()
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

void Manager::on_logOutBtn_clicked()
{
    this->removeDataBaseConnection();
    this->close();
    this->parentWidget()->show();
}

void Manager::on_managePrBtn_clicked()
{
    productManager = new ProductManager(this, dbconn);
    if (productManager)
    {
        productManager->show();
    }
}

void Manager::on_manageCustBtn_clicked()
{
    clientManager = new ClientManager(this, dbconn);
    if (clientManager)
    {
        clientManager->show();
    }
}

void Manager::on_statisticsSort_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        return;
    }

    orderMethod = arg1.toLower();
    if (!this->getStatistics())
    {
        QMessageBox::critical(this, "БД", "Невозможно получить статистику!");
        return;
    }
}
