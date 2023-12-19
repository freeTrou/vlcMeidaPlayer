/****************************************************************************
** Meta object code from reading C++ file 'CVideoWidgetTopWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../CVideoWidgetTopWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CVideoWidgetTopWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CVideoWidgetTopWidget_t {
    QByteArrayData data[11];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CVideoWidgetTopWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CVideoWidgetTopWidget_t qt_meta_stringdata_CVideoWidgetTopWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "CVideoWidgetTopWidget"
QT_MOC_LITERAL(1, 22, 12), // "sig_OpenFile"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "fileList"
QT_MOC_LITERAL(4, 45, 14), // "sig_OpenFloder"
QT_MOC_LITERAL(5, 60, 4), // "path"
QT_MOC_LITERAL(6, 65, 16), // "sig_OpenPlaylist"
QT_MOC_LITERAL(7, 82, 14), // "sig_SliderMove"
QT_MOC_LITERAL(8, 97, 5), // "value"
QT_MOC_LITERAL(9, 103, 13), // "onSliderMoved"
QT_MOC_LITERAL(10, 117, 8) // "position"

    },
    "CVideoWidgetTopWidget\0sig_OpenFile\0\0"
    "fileList\0sig_OpenFloder\0path\0"
    "sig_OpenPlaylist\0sig_SliderMove\0value\0"
    "onSliderMoved\0position"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CVideoWidgetTopWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    0,   45,    2, 0x06 /* Public */,
       7,    1,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void CVideoWidgetTopWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CVideoWidgetTopWidget *_t = static_cast<CVideoWidgetTopWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_OpenFile((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: _t->sig_OpenFloder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sig_OpenPlaylist(); break;
        case 3: _t->sig_SliderMove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CVideoWidgetTopWidget::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVideoWidgetTopWidget::sig_OpenFile)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CVideoWidgetTopWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVideoWidgetTopWidget::sig_OpenFloder)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CVideoWidgetTopWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVideoWidgetTopWidget::sig_OpenPlaylist)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CVideoWidgetTopWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVideoWidgetTopWidget::sig_SliderMove)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CVideoWidgetTopWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CVideoWidgetTopWidget.data,
    qt_meta_data_CVideoWidgetTopWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CVideoWidgetTopWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CVideoWidgetTopWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CVideoWidgetTopWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CVideoWidgetTopWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CVideoWidgetTopWidget::sig_OpenFile(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CVideoWidgetTopWidget::sig_OpenFloder(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CVideoWidgetTopWidget::sig_OpenPlaylist()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CVideoWidgetTopWidget::sig_SliderMove(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
