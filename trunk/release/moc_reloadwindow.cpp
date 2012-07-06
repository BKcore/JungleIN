/****************************************************************************
** Meta object code from reading C++ file 'reloadwindow.h'
**
** Created: Sun 17. Jun 16:43:52 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ui/reloadwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reloadwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReloadWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   14,   13,   13, 0x0a,
      34,   32,   13,   13, 0x0a,
      50,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ReloadWindow[] = {
    "ReloadWindow\0\0d\0setDensity(int)\0s\0"
    "setSpacing(int)\0reGenerate()\0"
};

void ReloadWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReloadWindow *_t = static_cast<ReloadWindow *>(_o);
        switch (_id) {
        case 0: _t->setDensity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setSpacing((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->reGenerate(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ReloadWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReloadWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ReloadWindow,
      qt_meta_data_ReloadWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReloadWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReloadWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReloadWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReloadWindow))
        return static_cast<void*>(const_cast< ReloadWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int ReloadWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
