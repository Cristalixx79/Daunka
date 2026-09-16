/****************************************************************************
** Meta object code from reading C++ file 'product_manager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Main/product_manager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'product_manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProductManager_t {
    QByteArrayData data[11];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProductManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProductManager_t qt_meta_stringdata_ProductManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ProductManager"
QT_MOC_LITERAL(1, 15, 18), // "on_backBtn_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 20), // "on_searchBtn_clicked"
QT_MOC_LITERAL(4, 56, 19), // "on_clearBtn_clicked"
QT_MOC_LITERAL(5, 76, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(6, 108, 4), // "arg1"
QT_MOC_LITERAL(7, 113, 32), // "on_productList_itemDoubleClicked"
QT_MOC_LITERAL(8, 146, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(9, 163, 4), // "item"
QT_MOC_LITERAL(10, 168, 17) // "on_addBtn_clicked"

    },
    "ProductManager\0on_backBtn_clicked\0\0"
    "on_searchBtn_clicked\0on_clearBtn_clicked\0"
    "on_comboBox_currentIndexChanged\0arg1\0"
    "on_productList_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0on_addBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProductManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       7,    1,   50,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void ProductManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProductManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_backBtn_clicked(); break;
        case 1: _t->on_searchBtn_clicked(); break;
        case 2: _t->on_clearBtn_clicked(); break;
        case 3: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_productList_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->on_addBtn_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ProductManager::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_ProductManager.data,
    qt_meta_data_ProductManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ProductManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProductManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProductManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ProductManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
