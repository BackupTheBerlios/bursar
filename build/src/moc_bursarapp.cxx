/****************************************************************************
** Meta object code from reading C++ file 'bursarapp.h'
**
** Created: Mon Dec 14 18:46:30 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/bursarapp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bursarapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BursarApp[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      36,   10,   10,   10, 0x08,
      62,   10,   10,   10, 0x08,
      88,   10,   10,   10, 0x08,
     115,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BursarApp[] = {
    "BursarApp\0\0on_actionNew_triggered()\0"
    "on_actionOpen_triggered()\0"
    "on_actionQuit_triggered()\0"
    "on_actionAbout_triggered()\0"
    "on_actionAboutQt_triggered()\0"
};

const QMetaObject BursarApp::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_BursarApp,
      qt_meta_data_BursarApp, 0 }
};

const QMetaObject *BursarApp::metaObject() const
{
    return &staticMetaObject;
}

void *BursarApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BursarApp))
        return static_cast<void*>(const_cast< BursarApp*>(this));
    return QApplication::qt_metacast(_clname);
}

int BursarApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionNew_triggered(); break;
        case 1: on_actionOpen_triggered(); break;
        case 2: on_actionQuit_triggered(); break;
        case 3: on_actionAbout_triggered(); break;
        case 4: on_actionAboutQt_triggered(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
