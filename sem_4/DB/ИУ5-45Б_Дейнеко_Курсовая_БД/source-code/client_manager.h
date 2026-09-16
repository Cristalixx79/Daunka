#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "client_profile.h"

namespace Ui {
    class ClientManager;
}

class ClientManager : public QDialog {
    Q_OBJECT
public:
    explicit ClientManager(QWidget *parent, QSqlDatabase db);
    ~ClientManager();
private slots:
    void on_backBtn_clicked();

    void on_searchBtn_clicked();

    void on_clearBtn_clicked();

    void on_usersList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ClientManager *ui;
    QSqlDatabase dbconn;
    ClientProfile *clientProfile;

    bool getUsersList();
};

#endif // CLIENT_MANAGER_H
