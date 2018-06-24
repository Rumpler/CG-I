/****************************************************************************
** Meta object code from reading C++ file 'CgQtGui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UebungSS2018/CgQtViewer/CgQtGui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CgQtGui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CgQtGui_t {
    QByteArrayData data[11];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CgQtGui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CgQtGui_t qt_meta_stringdata_CgQtGui = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CgQtGui"
QT_MOC_LITERAL(1, 8, 10), // "mouseEvent"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 33, 5), // "event"
QT_MOC_LITERAL(5, 39, 15), // "viewportChanged"
QT_MOC_LITERAL(6, 55, 21), // "slotMySpinBox1Changed"
QT_MOC_LITERAL(7, 77, 22), // "slotMyCheckBox1Changed"
QT_MOC_LITERAL(8, 100, 20), // "slotMyButton1Pressed"
QT_MOC_LITERAL(9, 121, 31), // "slotButtonGroupSelectionChanged"
QT_MOC_LITERAL(10, 153, 16) // "slotLoadMeshFile"

    },
    "CgQtGui\0mouseEvent\0\0QMouseEvent*\0event\0"
    "viewportChanged\0slotMySpinBox1Changed\0"
    "slotMyCheckBox1Changed\0slotMyButton1Pressed\0"
    "slotButtonGroupSelectionChanged\0"
    "slotLoadMeshFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CgQtGui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       5,    2,   52,    2, 0x08 /* Private */,
       6,    0,   57,    2, 0x08 /* Private */,
       7,    0,   58,    2, 0x08 /* Private */,
       8,    0,   59,    2, 0x08 /* Private */,
       9,    0,   60,    2, 0x08 /* Private */,
      10,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CgQtGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CgQtGui *_t = static_cast<CgQtGui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->viewportChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slotMySpinBox1Changed(); break;
        case 3: _t->slotMyCheckBox1Changed(); break;
        case 4: _t->slotMyButton1Pressed(); break;
        case 5: _t->slotButtonGroupSelectionChanged(); break;
        case 6: _t->slotLoadMeshFile(); break;
        default: ;
        }
    }
}

const QMetaObject CgQtGui::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CgQtGui.data,
      qt_meta_data_CgQtGui,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CgQtGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CgQtGui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CgQtGui.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CgObservable"))
        return static_cast< CgObservable*>(this);
    return QWidget::qt_metacast(_clname);
}

int CgQtGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
