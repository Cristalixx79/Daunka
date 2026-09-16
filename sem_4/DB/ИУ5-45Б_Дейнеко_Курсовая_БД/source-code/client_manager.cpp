#include "client_manager.h"
#include "ui_client_manager.h"

ClientManager::ClientManager(QWidget *parent, QSqlDatabase db) :
        QDialog(parent), dbconn(db), ui(new Ui::ClientManager)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Управление клиентами");

    if (!this->getUsersList())
    {
        QMessageBox::critical(this, "AIS", "Cannot get users list!");
        return;
    }
}

ClientManager::~ClientManager()
{
    delete ui;
}

bool ClientManager::getUsersList()
{
    QSqlQuery query(dbconn);
    query.prepare("SELECT * FROM users WHERE user_role = 'Customer' ORDER BY username");

    if (!query.exec())
    {
        return false;
    }

    ui->userCount->setText(QString("Всего клиентов: %1").arg(query.size()));

    while (query.next())
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon("/home/student/Main/img/user.png"), query.value("username").toString());
        if (item)
        {
            ui->usersList->addItem(item);
        }

    }
    return true;
}

void ClientManager::on_backBtn_clicked()
{
    dbconn = QSqlDatabase();
    this->close();
    this->parentWidget()->show();
}

void ClientManager::on_searchBtn_clicked()
{
    QString search = ui->searchLe->text().trimmed();
    if (search == "")
    {
        return;
    }

    QSqlQuery query(dbconn);
    query.prepare(QString("SELECT * FROM users WHERE username LIKE '%1%'").arg(search));

    if (!query.exec())
    {
        return;
    }
    if (query.size() == 0)
    {
        QMessageBox::about(this, "AIS", QString("Ничего не найдено по запросу '%1'").arg(search));
        ui->searchLe->clear();
        return;
    }

    ui->usersList->clear();
    ui->userCount->setText(QString("Найдено пользователей: %1").arg(query.size()));

    while (query.next())
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon("/home/student/Main/img/user.png"), query.value("username").toString());
        if (item)
        {
            ui->usersList->addItem(item);
        }
    }
}

void ClientManager::on_clearBtn_clicked()
{
    if (ui->searchLe->text() == nullptr)
    {
        return;
    }

    ui->searchLe->clear();
    ui->usersList->clear();

    this->getUsersList();
}

void ClientManager::on_usersList_itemDoubleClicked(QListWidgetItem *item)
{
    clientProfile = new ClientProfile(this, dbconn, item->text());
    if (clientProfile)
    {
         clientProfile->show();
    }
}
