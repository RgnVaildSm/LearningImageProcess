/****************************************************************************
** Meta object code from reading C++ file 'AnalyzerChartWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Process/AnalyzerChartWidget.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnalyzerChartWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSAnalyzerChartWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSAnalyzerChartWidgetENDCLASS = QtMocHelpers::stringData(
    "AnalyzerChartWidget",
    "addSample",
    "",
    "value",
    "clearSamples"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSAnalyzerChartWidgetENDCLASS_t {
    uint offsetsAndSizes[10];
    char stringdata0[20];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSAnalyzerChartWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSAnalyzerChartWidgetENDCLASS_t qt_meta_stringdata_CLASSAnalyzerChartWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 19),  // "AnalyzerChartWidget"
        QT_MOC_LITERAL(20, 9),  // "addSample"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 5),  // "value"
        QT_MOC_LITERAL(37, 12)   // "clearSamples"
    },
    "AnalyzerChartWidget",
    "addSample",
    "",
    "value",
    "clearSamples"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSAnalyzerChartWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x0a,    1 /* Public */,
       4,    0,   29,    2, 0x0a,    3 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject AnalyzerChartWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QChartView::staticMetaObject>(),
    qt_meta_stringdata_CLASSAnalyzerChartWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSAnalyzerChartWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSAnalyzerChartWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AnalyzerChartWidget, std::true_type>,
        // method 'addSample'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'clearSamples'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void AnalyzerChartWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AnalyzerChartWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addSample((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->clearSamples(); break;
        default: ;
        }
    }
}

const QMetaObject *AnalyzerChartWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnalyzerChartWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSAnalyzerChartWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QChartView::qt_metacast(_clname);
}

int AnalyzerChartWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QChartView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
