/****************************************************************************
** Meta object code from reading C++ file 'CameraBase.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Camera/CameraBase.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CameraBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSCameraBaseENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSCameraBaseENDCLASS = QtMocHelpers::stringData(
    "CameraBase",
    "frameReady",
    "",
    "frame",
    "errorOccurred",
    "errorString",
    "snapshotReady",
    "snapshot",
    "formatChanged",
    "QCameraFormat",
    "format",
    "GetCameraDevices",
    "QList<QCameraDevice>",
    "processFrame",
    "id",
    "img",
    "handleError",
    "QImageCapture::Error",
    "error",
    "handleVideoFrame",
    "QVideoFrame",
    "GetCurrentCameraDevice",
    "QCameraDevice"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCameraBaseENDCLASS_t {
    uint offsetsAndSizes[46];
    char stringdata0[11];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[14];
    char stringdata5[12];
    char stringdata6[14];
    char stringdata7[9];
    char stringdata8[14];
    char stringdata9[14];
    char stringdata10[7];
    char stringdata11[17];
    char stringdata12[21];
    char stringdata13[13];
    char stringdata14[3];
    char stringdata15[4];
    char stringdata16[12];
    char stringdata17[21];
    char stringdata18[6];
    char stringdata19[17];
    char stringdata20[12];
    char stringdata21[23];
    char stringdata22[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCameraBaseENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCameraBaseENDCLASS_t qt_meta_stringdata_CLASSCameraBaseENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "CameraBase"
        QT_MOC_LITERAL(11, 10),  // "frameReady"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 5),  // "frame"
        QT_MOC_LITERAL(29, 13),  // "errorOccurred"
        QT_MOC_LITERAL(43, 11),  // "errorString"
        QT_MOC_LITERAL(55, 13),  // "snapshotReady"
        QT_MOC_LITERAL(69, 8),  // "snapshot"
        QT_MOC_LITERAL(78, 13),  // "formatChanged"
        QT_MOC_LITERAL(92, 13),  // "QCameraFormat"
        QT_MOC_LITERAL(106, 6),  // "format"
        QT_MOC_LITERAL(113, 16),  // "GetCameraDevices"
        QT_MOC_LITERAL(130, 20),  // "QList<QCameraDevice>"
        QT_MOC_LITERAL(151, 12),  // "processFrame"
        QT_MOC_LITERAL(164, 2),  // "id"
        QT_MOC_LITERAL(167, 3),  // "img"
        QT_MOC_LITERAL(171, 11),  // "handleError"
        QT_MOC_LITERAL(183, 20),  // "QImageCapture::Error"
        QT_MOC_LITERAL(204, 5),  // "error"
        QT_MOC_LITERAL(210, 16),  // "handleVideoFrame"
        QT_MOC_LITERAL(227, 11),  // "QVideoFrame"
        QT_MOC_LITERAL(239, 22),  // "GetCurrentCameraDevice"
        QT_MOC_LITERAL(262, 13)   // "QCameraDevice"
    },
    "CameraBase",
    "frameReady",
    "",
    "frame",
    "errorOccurred",
    "errorString",
    "snapshotReady",
    "snapshot",
    "formatChanged",
    "QCameraFormat",
    "format",
    "GetCameraDevices",
    "QList<QCameraDevice>",
    "processFrame",
    "id",
    "img",
    "handleError",
    "QImageCapture::Error",
    "error",
    "handleVideoFrame",
    "QVideoFrame",
    "GetCurrentCameraDevice",
    "QCameraDevice"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCameraBaseENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    1 /* Public */,
       4,    1,   71,    2, 0x06,    3 /* Public */,
       6,    1,   74,    2, 0x06,    5 /* Public */,
       8,    1,   77,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    0,   80,    2, 0x0a,    9 /* Public */,
      13,    2,   81,    2, 0x08,   10 /* Private */,
      16,    3,   86,    2, 0x08,   13 /* Private */,
      19,    1,   93,    2, 0x08,   17 /* Private */,
      21,    0,   96,    2, 0x108,   19 /* Private | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QImage,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    0x80000000 | 12,
    QMetaType::Void, QMetaType::Int, QMetaType::QImage,   14,   15,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 17, QMetaType::QString,   14,   18,    5,
    QMetaType::Void, 0x80000000 | 20,    3,
    0x80000000 | 22,

       0        // eod
};

Q_CONSTINIT const QMetaObject CameraBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSCameraBaseENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCameraBaseENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCameraBaseENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CameraBase, std::true_type>,
        // method 'frameReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'snapshotReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        // method 'formatChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCameraFormat &, std::false_type>,
        // method 'GetCameraDevices'
        QtPrivate::TypeAndForceComplete<QList<QCameraDevice>, std::false_type>,
        // method 'processFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        // method 'handleError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QImageCapture::Error, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleVideoFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVideoFrame &, std::false_type>,
        // method 'GetCurrentCameraDevice'
        QtPrivate::TypeAndForceComplete<QCameraDevice, std::false_type>
    >,
    nullptr
} };

void CameraBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CameraBase *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->frameReady((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->snapshotReady((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 3: _t->formatChanged((*reinterpret_cast< std::add_pointer_t<QCameraFormat>>(_a[1]))); break;
        case 4: { QList<QCameraDevice> _r = _t->GetCameraDevices();
            if (_a[0]) *reinterpret_cast< QList<QCameraDevice>*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->processFrame((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QImage>>(_a[2]))); break;
        case 6: _t->handleError((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QImageCapture::Error>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 7: _t->handleVideoFrame((*reinterpret_cast< std::add_pointer_t<QVideoFrame>>(_a[1]))); break;
        case 8: { QCameraDevice _r = _t->GetCurrentCameraDevice();
            if (_a[0]) *reinterpret_cast< QCameraDevice*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QVideoFrame >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CameraBase::*)(const QImage & );
            if (_t _q_method = &CameraBase::frameReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CameraBase::*)(const QString & );
            if (_t _q_method = &CameraBase::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CameraBase::*)(const QImage & );
            if (_t _q_method = &CameraBase::snapshotReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CameraBase::*)(const QCameraFormat & );
            if (_t _q_method = &CameraBase::formatChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *CameraBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCameraBaseENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CameraBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CameraBase::frameReady(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CameraBase::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CameraBase::snapshotReady(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CameraBase::formatChanged(const QCameraFormat & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
