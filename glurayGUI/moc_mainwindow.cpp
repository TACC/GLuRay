/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Jun 21 21:50:15 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      24,   11,   11,   11, 0x08,
      40,   11,   11,   11, 0x08,
      55,   11,   11,   11, 0x08,
      77,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,
     138,   11,   11,   11, 0x08,
     156,   11,   11,   11, 0x08,
     173,   11,   11,   11, 0x08,
     193,   11,   11,   11, 0x08,
     208,   11,   11,   11, 0x08,
     223,   11,   11,   11, 0x08,
     247,   11,   11,   11, 0x08,
     268,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0onConnect()\0onClickRender()\0"
    "onClickApply()\0onClickEnvMapBrowse()\0"
    "clientDisconnected()\0onGLDraw()\0"
    "updateFPS()\0onClickPinhole()\0"
    "onClickThinLens()\0onClickPreview()\0"
    "onClickLambertian()\0onClickPhong()\0"
    "onClickGlass()\0onClickThinDielectric()\0"
    "onClickTransparent()\0onClickOrenNayar()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onConnect(); break;
        case 1: onClickRender(); break;
        case 2: onClickApply(); break;
        case 3: onClickEnvMapBrowse(); break;
        case 4: clientDisconnected(); break;
        case 5: onGLDraw(); break;
        case 6: updateFPS(); break;
        case 7: onClickPinhole(); break;
        case 8: onClickThinLens(); break;
        case 9: onClickPreview(); break;
        case 10: onClickLambertian(); break;
        case 11: onClickPhong(); break;
        case 12: onClickGlass(); break;
        case 13: onClickThinDielectric(); break;
        case 14: onClickTransparent(); break;
        case 15: onClickOrenNayar(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
