/****************************************************************************
** Meta object code from reading C++ file 'CPlayButtonGroupWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../CPlayButtonGroupWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CPlayButtonGroupWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CPlayButtonGroupWidget_t {
    QByteArrayData data[6];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPlayButtonGroupWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPlayButtonGroupWidget_t qt_meta_stringdata_CPlayButtonGroupWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "CPlayButtonGroupWidget"
QT_MOC_LITERAL(1, 23, 8), // "sig_play"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "sig_stop"
QT_MOC_LITERAL(4, 42, 8), // "sig_next"
QT_MOC_LITERAL(5, 51, 7) // "sig_pre"

    },
    "CPlayButtonGroupWidget\0sig_play\0\0"
    "sig_stop\0sig_next\0sig_pre"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPlayButtonGroupWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CPlayButtonGroupWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CPlayButtonGroupWidget *_t = static_cast<CPlayButtonGroupWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_play(); break;
        case 1: _t->sig_stop(); break;
        case 2: _t->sig_next(); break;
        case 3: _t->sig_pre(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CPlayButtonGroupWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPlayButtonGroupWidget::sig_play)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CPlayButtonGroupWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPlayButtonGroupWidget::sig_stop)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CPlayButtonGroupWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPlayButtonGroupWidget::sig_next)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CPlayButtonGroupWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPlayButtonGroupWidget::sig_pre)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CPlayButtonGroupWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CPlayButtonGroupWidget.data,
    qt_meta_data_CPlayButtonGroupWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CPlayButtonGroupWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPlayButtonGroupWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CPlayButtonGroupWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CPlayButtonGroupWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CPlayButtonGroupWidget::sig_play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CPlayButtonGroupWidget::sig_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CPlayButtonGroupWidget::sig_next()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CPlayButtonGroupWidget::sig_pre()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
