/****************************************************************************
** Meta object code from reading C++ file 'MyChatDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MyChatDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyChatDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyChatDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   15,   11,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   10,   11,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyChatDlg[] = {
    "MyChatDlg\0\0int\0chatDlg,msg,flag\0"
    "sendMsg(MyChatDlg*,QString&,bool)\0"
    "mysend()\0"
};

void MyChatDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyChatDlg *_t = static_cast<MyChatDlg *>(_o);
        switch (_id) {
        case 0: { int _r = _t->sendMsg((*reinterpret_cast< MyChatDlg*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->mysend();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyChatDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyChatDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MyChatDlg,
      qt_meta_data_MyChatDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyChatDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyChatDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyChatDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyChatDlg))
        return static_cast<void*>(const_cast< MyChatDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int MyChatDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
int MyChatDlg::sendMsg(MyChatDlg * _t1, QString & _t2, bool _t3)
{
    int _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_END_MOC_NAMESPACE
