#ifndef CLIENT_PROFILE_H
#define CLIENT_PROFILE_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "client_profile_order.h"

namespace Ui {
    class ClientProfile;
}

class ClientProfile : public QDialog {
    Q_OBJECT
public:
    explicit ClientProfile(QWidget *parent, QSqlDatabase db, QString usern);
    ~ClientProfile();
private slots:
    void on_backBtn_clicked();

    void on_banBtn_clicked();

    void on_clientOrders_itemDoubleClicked(QListWidgetItem *item);

    void on_refreshBtn_clicked();

private:
    Ui::ClientProfile *ui;
    ClientProfileOrder *cpo;
    QSqlDatabase dbconn;
    QString username;

    bool getClientOrders();
};

#endif // CLIENT_PROFILE_H
