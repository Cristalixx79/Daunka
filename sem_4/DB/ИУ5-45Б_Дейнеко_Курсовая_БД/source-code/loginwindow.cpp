#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow),
      cust(nullptr), manager(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - Вход");
    ui->passwordLe->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow()
{
    this->removeDataBaseConnection();
    delete ui;
}

void LoginWindow::removeDataBaseConnection()
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

void LoginWindow::on_LoginBtn_clicked()
{
    this->removeDataBaseConnection();

    QString username = ui->usernameLe->text().trimmed();
    QString password = ui->passwordLe->text().trimmed();
    if (username == nullptr || password == nullptr)
    {
        ui->loginInfoTb->append("Имя пользователя или пароль отсутствуют");
        return;
    }

    QString connectionName = "Login";
    dbconn = QSqlDatabase::addDatabase("QPSQL", connectionName);
    dbconn.setDatabaseName("AIS");
    dbconn.setHostName("localhost");
    dbconn.setUserName("student");
    dbconn.setPassword("1");

    if (!dbconn.open())
    {
        ui->loginInfoTb->append("Не удалось подключится к БД");
        return;
    }
    ui->loginInfoTb->append("Подключение установлено");

    QSqlQuery query(dbconn);
    query.prepare("SELECT user_id, user_role FROM users WHERE username = :username AND passphrase = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (!query.exec())
    {
        ui->loginInfoTb->append("Ошибка входа");
        return;
    }

    QString role = nullptr;
    qint32 userId = 0;
    if (query.next())
    {
        role = query.value("user_role").toString();
        userId = query.value("user_id").toInt();
    }

    if (role.toLower() == "customer")
    {
        ui->loginInfoTb->append(QString("Вход как %1").arg(role.toLower()));
        this->close();
        cust = new Customer(this, userId);
        cust->show();
        ui->loginInfoTb->clear();
    }
    else if (role.toLower() == "manager")
    {
        ui->loginInfoTb->append(QString("Вход как %1").arg(role.toLower()));
        this->close();
        manager = new Manager(this);
        manager->show();
        ui->loginInfoTb->clear();
    }
    else
    {
        QMessageBox::warning(this, "Вход", "Неверный логин или пароль!");
    }
    ui->usernameLe->clear();
    ui->passwordLe->clear();
}
