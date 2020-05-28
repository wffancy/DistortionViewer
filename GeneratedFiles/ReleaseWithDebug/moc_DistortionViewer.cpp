/****************************************************************************
** Meta object code from reading C++ file 'DistortionViewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DistortionViewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DistortionViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DistortionViewer_t {
    QByteArrayData data[11];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DistortionViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DistortionViewer_t qt_meta_stringdata_DistortionViewer = {
    {
QT_MOC_LITERAL(0, 0, 16), // "DistortionViewer"
QT_MOC_LITERAL(1, 17, 12), // "resizeCamera"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "width"
QT_MOC_LITERAL(4, 37, 6), // "height"
QT_MOC_LITERAL(5, 44, 17), // "changeAspectRatio"
QT_MOC_LITERAL(6, 62, 3), // "num"
QT_MOC_LITERAL(7, 66, 16), // "changeCameraType"
QT_MOC_LITERAL(8, 83, 4), // "type"
QT_MOC_LITERAL(9, 88, 15), // "changeCameraFOV"
QT_MOC_LITERAL(10, 104, 3) // "fov"

    },
    "DistortionViewer\0resizeCamera\0\0width\0"
    "height\0changeAspectRatio\0num\0"
    "changeCameraType\0type\0changeCameraFOV\0"
    "fov"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DistortionViewer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x0a /* Public */,
       5,    1,   39,    2, 0x0a /* Public */,
       7,    1,   42,    2, 0x0a /* Public */,
       9,    1,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void DistortionViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DistortionViewer *_t = static_cast<DistortionViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resizeCamera((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->changeAspectRatio((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->changeCameraType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changeCameraFOV((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject DistortionViewer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DistortionViewer.data,
      qt_meta_data_DistortionViewer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DistortionViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DistortionViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DistortionViewer.stringdata0))
        return static_cast<void*>(const_cast< DistortionViewer*>(this));
    return QObject::qt_metacast(_clname);
}

int DistortionViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
