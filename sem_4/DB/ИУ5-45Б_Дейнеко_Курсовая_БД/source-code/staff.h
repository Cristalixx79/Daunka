#ifndef STAFF_H
#define STAFF_H

#include <QDialog>

namespace Ui {
    class Staff;
}

class Staff : public QDialog {
    Q_OBJECT
public:
    explicit Staff(QWidget *parent);
    ~Staff();
private:
    Ui::Staff *ui;
};

#endif // STAFF_H
