/****************************************************************************
** Meta object code from reading C++ file 'burcombobox.h'
**
** Created: Mon Dec 14 18:46:31 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/widgets/burcombobox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'burcombobox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BurComboBox[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       1,   22, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      52,   46,   12,   12, 0x0a,

 // properties: name, type, flags
      86,   77, 0xff095103,

       0        // eod
};

static const char qt_meta_stringdata_BurComboBox[] = {
    "BurComboBox\0\0currentItemDataChanged(QVariant)\0"
    "index\0currentIndexChanged(int)\0QVariant\0"
    "currentItemData\0"
};

const QMetaObject BurComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_BurComboBox,
      qt_meta_data_BurComboBox, 0 }
};

const QMetaObject *BurComboBox::metaObject() const
{
    return &staticMetaObject;
}

void *BurComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BurComboBox))
        return static_cast<void*>(const_cast< BurComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int BurComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: currentItemDataChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariant*>(_v) = currentItemData(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setCurrentItemData(*reinterpret_cast< QVariant*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void BurComboBox::currentItemDataChanged(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
