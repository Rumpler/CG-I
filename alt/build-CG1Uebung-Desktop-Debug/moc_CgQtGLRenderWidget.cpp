/****************************************************************************
** Meta object code from reading C++ file 'CgQtGLRenderWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UebungSS2018/CgQtViewer/CgQtGLRenderWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CgQtGLRenderWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CgQtGLRenderWidget_t {
    QByteArrayData data[14];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CgQtGLRenderWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CgQtGLRenderWidget_t qt_meta_stringdata_CgQtGLRenderWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CgQtGLRenderWidget"
QT_MOC_LITERAL(1, 19, 10), // "mouseEvent"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 44, 5), // "event"
QT_MOC_LITERAL(5, 50, 15), // "viewportChanged"
QT_MOC_LITERAL(6, 66, 1), // "w"
QT_MOC_LITERAL(7, 68, 1), // "h"
QT_MOC_LITERAL(8, 70, 18), // "slotCustomRotation"
QT_MOC_LITERAL(9, 89, 12), // "slotLighting"
QT_MOC_LITERAL(10, 102, 17), // "slotPolygonPoints"
QT_MOC_LITERAL(11, 120, 20), // "slotPolygonWireframe"
QT_MOC_LITERAL(12, 141, 17), // "slotPolygonFilled"
QT_MOC_LITERAL(13, 159, 7) // "cleanup"

    },
    "CgQtGLRenderWidget\0mouseEvent\0\0"
    "QMouseEvent*\0event\0viewportChanged\0w\0"
    "h\0slotCustomRotation\0slotLighting\0"
    "slotPolygonPoints\0slotPolygonWireframe\0"
    "slotPolygonFilled\0cleanup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CgQtGLRenderWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    2,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   62,    2, 0x0a /* Public */,
       9,    0,   63,    2, 0x0a /* Public */,
      10,    0,   64,    2, 0x0a /* Public */,
      11,    0,   65,    2, 0x0a /* Public */,
      12,    0,   66,    2, 0x0a /* Public */,
      13,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CgQtGLRenderWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CgQtGLRenderWidget *_t = static_cast<CgQtGLRenderWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->viewportChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slotCustomRotation(); break;
        case 3: _t->slotLighting(); break;
        case 4: _t->slotPolygonPoints(); break;
        case 5: _t->slotPolygonWireframe(); break;
        case 6: _t->slotPolygonFilled(); break;
        case 7: _t->cleanup(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CgQtGLRenderWidget::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CgQtGLRenderWidget::mouseEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CgQtGLRenderWidget::*_t)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CgQtGLRenderWidget::viewportChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CgQtGLRenderWidget::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_CgQtGLRenderWidget.data,
      qt_meta_data_CgQtGLRenderWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CgQtGLRenderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CgQtGLRenderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CgQtGLRenderWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CgBaseRenderer"))
        return static_cast< CgBaseRenderer*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int CgQtGLRenderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CgQtGLRenderWidget::mouseEvent(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CgQtGLRenderWidget::viewportChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
