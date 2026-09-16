#ifndef CLIENT_PROFILE_ORDER_H
#define CLIENT_PROFILE_ORDER_H

#include <QDialog>

namespace Ui {
    class ClientProfileOrder;
}

class ClientProfileOrder : public QDialog {
    Q_OBJECT
public:
    explicit ClientProfileOrder(QWidget *parent);
    ~ClientProfileOrder();
private:
    Ui::ClientProfileOrder *ui;
};

#endif // CLIENT_PROFILE_ORDER_H
