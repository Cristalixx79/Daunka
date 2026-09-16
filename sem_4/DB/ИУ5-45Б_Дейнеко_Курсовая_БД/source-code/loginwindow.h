#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "customer.h"
#include "manager.h"

#include <QMainWindow>
#include <QString>
#include <QtSql/QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_LoginBtn_clicked();

private:
    Ui::LoginWindow *ui;
    QSqlDatabase dbconn;

    Customer *cust;
    Manager *manager;
    void removeDataBaseConnection();
};
#endif // LOGINWINDOW_H
