/****************************************************************************
** Meta object code from reading C++ file 'apihandler.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/api/apihandler.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apihandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10ApiHandlerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10ApiHandlerE = QtMocHelpers::stringData(
    "ApiHandler",
    "stateChange",
    "",
    "onTimeSpeedTrain",
    "time",
    "speed",
    "train_id",
    "onIndexStateHouse",
    "QList<int>",
    "states",
    "house_id",
    "onSwitch",
    "onTurbin",
    "onStateChange",
    "onServerConnection",
    "onDataReceived",
    "id",
    "onErrorOccurred",
    "QLocalSocket::LocalSocketError",
    "error"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10ApiHandlerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    3,   69,    2, 0x0a,    2 /* Public */,
       7,    2,   76,    2, 0x0a,    6 /* Public */,
      11,    0,   81,    2, 0x0a,    9 /* Public */,
      12,    0,   82,    2, 0x0a,   10 /* Public */,
      13,    0,   83,    2, 0x08,   11 /* Private */,
      14,    0,   84,    2, 0x08,   12 /* Private */,
      15,    1,   85,    2, 0x08,   13 /* Private */,
      17,    1,   88,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int,    9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

Q_CONSTINIT const QMetaObject ApiHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN10ApiHandlerE.offsetsAndSizes,
    qt_meta_data_ZN10ApiHandlerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10ApiHandlerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ApiHandler, std::true_type>,
        // method 'stateChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTimeSpeedTrain'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onIndexStateHouse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVector<int>, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onSwitch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTurbin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStateChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onServerConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onErrorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QLocalSocket::LocalSocketError, std::false_type>
    >,
    nullptr
} };

void ApiHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ApiHandler *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->stateChange(); break;
        case 1: _t->onTimeSpeedTrain((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 2: _t->onIndexStateHouse((*reinterpret_cast< std::add_pointer_t<QList<int>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 3: _t->onSwitch(); break;
        case 4: _t->onTurbin(); break;
        case 5: _t->onStateChange(); break;
        case 6: _t->onServerConnection(); break;
        case 7: _t->onDataReceived((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->onErrorOccurred((*reinterpret_cast< std::add_pointer_t<QLocalSocket::LocalSocketError>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (ApiHandler::*)();
            if (_q_method_type _q_method = &ApiHandler::stateChange; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *ApiHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApiHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10ApiHandlerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ApiHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ApiHandler::stateChange()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
