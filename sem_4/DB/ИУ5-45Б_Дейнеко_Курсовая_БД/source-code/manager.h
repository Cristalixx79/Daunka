#ifndef MANAGER_H
#define MANAGER_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QDebug>

#include "client_manager.h"
#include "product_manager.h"

namespace Ui {
    class Manager;
}

class Manager : public QDialog {
    Q_OBJECT
public:
    explicit Manager(QWidget *parent);
    ~Manager();
private slots:
    void on_logOutBtn_clicked();

    void on_managePrBtn_clicked();

    void on_manageCustBtn_clicked();

    void on_statisticsSort_currentIndexChanged(const QString &arg1);

private:
    Ui::Manager *ui;
    QtCharts::QChartView *chartView;
    QString orderMethod;
    QSqlDatabase dbconn;
    ClientManager *clientManager;
    ProductManager *productManager;

    void removeDataBaseConnection();
    bool setDataBaseConnection();
    bool getStatistics();
    void renderChart(QSqlQuery *q);
    void foo();
};

#endif // MANAGER_H
