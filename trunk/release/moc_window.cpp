/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created: Sun 17. Jun 16:43:50 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ui/window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Window[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      30,   24,    7,    7, 0x0a,
      52,   45,    7,    7, 0x0a,
      69,   45,    7,    7, 0x0a,
      93,   45,    7,    7, 0x0a,
     113,   45,    7,    7, 0x0a,
     133,   45,    7,    7, 0x0a,
     151,   24,    7,    7, 0x0a,
     168,   24,    7,    7, 0x0a,
     190,   24,    7,    7, 0x0a,
     206,   24,    7,    7, 0x0a,
     219,   45,    7,    7, 0x0a,
     238,   45,    7,    7, 0x0a,
     260,   24,    7,    7, 0x0a,
     279,   45,    7,    7, 0x0a,
     293,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Window[] = {
    "Window\0\0exResetCamera()\0value\0"
    "exQuality(int)\0active\0exPostFXAA(bool)\0"
    "exPostLenseFlares(bool)\0exPostDistord(bool)\0"
    "exPostGodrays(bool)\0exPostBloom(bool)\0"
    "exFlareDisp(int)\0exFlareIntensity(int)\0"
    "exSunSpeed(int)\0exGamma(int)\0"
    "exAnisotropy(bool)\0exShadowCascade(bool)\0"
    "exRenderRatio(int)\0playBtn(bool)\0"
    "reGenerate()\0"
};

void Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Window *_t = static_cast<Window *>(_o);
        switch (_id) {
        case 0: _t->exResetCamera(); break;
        case 1: _t->exQuality((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->exPostFXAA((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->exPostLenseFlares((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->exPostDistord((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->exPostGodrays((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->exPostBloom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->exFlareDisp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->exFlareIntensity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->exSunSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->exGamma((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->exAnisotropy((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->exShadowCascade((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->exRenderRatio((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->playBtn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->reGenerate(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Window::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Window::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_Window,
      qt_meta_data_Window, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Window))
        return static_cast<void*>(const_cast< Window*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
