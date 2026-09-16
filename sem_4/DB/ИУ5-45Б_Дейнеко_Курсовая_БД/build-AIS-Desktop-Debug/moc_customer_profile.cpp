/****************************************************************************
** Meta object code from reading C++ file 'customer_profile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Main/customer_profile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customer_profile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CustomerProfile_t {
    QByteArrayData data[12];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomerProfile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomerProfile_t qt_meta_stringdata_CustomerProfile = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CustomerProfile"
QT_MOC_LITERAL(1, 16, 18), // "on_backBtn_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 20), // "on_logOutBtn_clicked"
QT_MOC_LITERAL(4, 57, 20), // "on_searchBtn_clicked"
QT_MOC_LITERAL(5, 78, 19), // "on_clearBtn_clicked"
QT_MOC_LITERAL(6, 98, 31), // "on_ordersList_itemDoubleClicked"
QT_MOC_LITERAL(7, 130, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 147, 4), // "item"
QT_MOC_LITERAL(9, 152, 30), // "on_sortBox_currentIndexChanged"
QT_MOC_LITERAL(10, 183, 4), // "arg1"
QT_MOC_LITERAL(11, 188, 21) // "on_refreshBtn_clicked"

    },
    "CustomerProfile\0on_backBtn_clicked\0\0"
    "on_logOutBtn_clicked\0on_searchBtn_clicked\0"
    "on_clearBtn_clicked\0on_ordersList_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0"
    "on_sortBox_currentIndexChanged\0arg1\0"
    "on_refreshBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomerProfile[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    1,   53,    2, 0x08 /* Private */,
       9,    1,   56,    2, 0x08 /* Private */,
      11,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,

       0        // eod
};

void CustomerProfile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomerProfile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_backBtn_clicked(); break;
        case 1: _t->on_logOutBtn_clicked(); break;
        case 2: _t->on_searchBtn_clicked(); break;
        case 3: _t->on_clearBtn_clicked(); break;
        case 4: _t->on_ordersList_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->on_sortBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_refreshBtn_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CustomerProfile::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_CustomerProfile.data,
    qt_meta_data_CustomerProfile,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CustomerProfile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomerProfile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomerProfile.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CustomerProfile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
