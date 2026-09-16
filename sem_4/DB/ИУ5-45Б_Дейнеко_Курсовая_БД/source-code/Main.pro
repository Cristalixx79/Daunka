QT       += core gui
QT       += core gui sql
QT       += widgets charts
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client_manager.cpp \
    client_profile.cpp \
    client_profile_order.cpp \
    customer_profile.cpp \
    main.cpp \
    loginwindow.cpp \
    customer.cpp \
    manager.cpp \
    new_product.cpp \
    order_item.cpp \
    product_item.cpp \
    product_item_manager.cpp \
    product_manager.cpp

HEADERS += \
    client_manager.h \
    client_profile.h \
    client_profile_order.h \
    customer_profile.h \
    loginwindow.h \
    customer.h \
    manager.h \
    new_product.h \
    order_item.h \
    product_item.h \
    product_item_manager.h \
    product_manager.h

FORMS += \
    client_manager.ui \
    client_profile.ui \
    client_profile_order.ui \
    customer.ui \
    customer_profile.ui \
    loginwindow.ui \
    manager.ui \
    new_product.ui \
    order_item.ui \
    product_item.ui \
    product_item_manager.ui \
    product_manager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
