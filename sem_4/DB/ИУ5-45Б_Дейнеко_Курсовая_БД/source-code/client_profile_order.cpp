#include "client_profile_order.h"
#include "ui_client_profile_order.h"

ClientProfileOrder::ClientProfileOrder(QWidget *parent)
    : QDialog(parent)
{
    ui->setupUi(this);
    this->setWindowTitle("АИС Управления заказами компьютерной фирмы - заказ");
}

ClientProfileOrder::~ClientProfileOrder()
{
    delete ui;
}
