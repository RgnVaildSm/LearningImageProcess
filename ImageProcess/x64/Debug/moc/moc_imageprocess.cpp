/****************************************************************************
** Meta object code from reading C++ file 'imageprocess.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../imageprocess.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageprocess.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSImageProcessENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSImageProcessENDCLASS = QtMocHelpers::stringData(
    "ImageProcess",
    "UpdateTimer",
    "",
    "UpdateVideoFrame",
    "frame",
    "HandleError",
    "errorString",
    "OnSharpnessUpdated",
    "value",
    "OnShowSettings",
    "OnCameraFormatChanged",
    "QCameraFormat",
    "fmt"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSImageProcessENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[13];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[6];
    char stringdata5[12];
    char stringdata6[12];
    char stringdata7[19];
    char stringdata8[6];
    char stringdata9[15];
    char stringdata10[22];
    char stringdata11[14];
    char stringdata12[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSImageProcessENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSImageProcessENDCLASS_t qt_meta_stringdata_CLASSImageProcessENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "ImageProcess"
        QT_MOC_LITERAL(13, 11),  // "UpdateTimer"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 16),  // "UpdateVideoFrame"
        QT_MOC_LITERAL(43, 5),  // "frame"
        QT_MOC_LITERAL(49, 11),  // "HandleError"
        QT_MOC_LITERAL(61, 11),  // "errorString"
        QT_MOC_LITERAL(73, 18),  // "OnSharpnessUpdated"
        QT_MOC_LITERAL(92, 5),  // "value"
        QT_MOC_LITERAL(98, 14),  // "OnShowSettings"
        QT_MOC_LITERAL(113, 21),  // "OnCameraFormatChanged"
        QT_MOC_LITERAL(135, 13),  // "QCameraFormat"
        QT_MOC_LITERAL(149, 3)   // "fmt"
    },
    "ImageProcess",
    "UpdateTimer",
    "",
    "UpdateVideoFrame",
    "frame",
    "HandleError",
    "errorString",
    "OnSharpnessUpdated",
    "value",
    "OnShowSettings",
    "OnCameraFormatChanged",
    "QCameraFormat",
    "fmt"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSImageProcessENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    1,   51,    2, 0x08,    2 /* Private */,
       5,    1,   54,    2, 0x08,    4 /* Private */,
       7,    1,   57,    2, 0x08,    6 /* Private */,
       9,    0,   60,    2, 0x08,    8 /* Private */,
      10,    1,   61,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

Q_CONSTINIT const QMetaObject ImageProcess::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSImageProcessENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSImageProcessENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSImageProcessENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ImageProcess, std::true_type>,
        // method 'UpdateTimer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'UpdateVideoFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        // method 'HandleError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'OnSharpnessUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'OnShowSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnCameraFormatChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCameraFormat &, std::false_type>
    >,
    nullptr
} };

void ImageProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageProcess *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->UpdateTimer(); break;
        case 1: _t->UpdateVideoFrame((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 2: _t->HandleError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->OnSharpnessUpdated((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 4: _t->OnShowSettings(); break;
        case 5: _t->OnCameraFormatChanged((*reinterpret_cast< std::add_pointer_t<QCameraFormat>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *ImageProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSImageProcessENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ImageProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
