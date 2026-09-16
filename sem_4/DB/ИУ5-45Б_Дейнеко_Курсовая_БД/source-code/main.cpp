#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("/home/student/Main/img/db.png"));
    LoginWindow w;
    w.show();
    return a.exec();
}
