/********************************************************************************
** Form generated from reading UI file 'imageprocess.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROCESS_H
#define UI_IMAGEPROCESS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageProcessClass
{
public:
    QAction *actionSetting;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBoxCameras;
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonAnalyzer;
    QSpacerItem *verticalSpacer;
    QWidget *widgetVideo;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;

    void setupUi(QMainWindow *ImageProcessClass)
    {
        if (ImageProcessClass->objectName().isEmpty())
            ImageProcessClass->setObjectName("ImageProcessClass");
        ImageProcessClass->resize(1285, 946);
        ImageProcessClass->setMinimumSize(QSize(400, 256));
        ImageProcessClass->setMaximumSize(QSize(16777215, 16777215));
        actionSetting = new QAction(ImageProcessClass);
        actionSetting->setObjectName("actionSetting");
        centralWidget = new QWidget(ImageProcessClass);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(6, 6, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 6, 6);
        comboBoxCameras = new QComboBox(centralWidget);
        comboBoxCameras->setObjectName("comboBoxCameras");

        verticalLayout->addWidget(comboBoxCameras);

        pushButtonOpen = new QPushButton(centralWidget);
        pushButtonOpen->setObjectName("pushButtonOpen");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonOpen->sizePolicy().hasHeightForWidth());
        pushButtonOpen->setSizePolicy(sizePolicy);
        pushButtonOpen->setMinimumSize(QSize(20, 20));
        pushButtonOpen->setMaximumSize(QSize(16777215, 256));
        pushButtonOpen->setSizeIncrement(QSize(0, 0));
        pushButtonOpen->setBaseSize(QSize(0, 0));

        verticalLayout->addWidget(pushButtonOpen);

        pushButtonClose = new QPushButton(centralWidget);
        pushButtonClose->setObjectName("pushButtonClose");
        sizePolicy.setHeightForWidth(pushButtonClose->sizePolicy().hasHeightForWidth());
        pushButtonClose->setSizePolicy(sizePolicy);
        pushButtonClose->setMinimumSize(QSize(20, 20));
        pushButtonClose->setMaximumSize(QSize(16777215, 256));

        verticalLayout->addWidget(pushButtonClose);

        pushButtonAnalyzer = new QPushButton(centralWidget);
        pushButtonAnalyzer->setObjectName("pushButtonAnalyzer");
        pushButtonAnalyzer->setCheckable(true);

        verticalLayout->addWidget(pushButtonAnalyzer);

        verticalSpacer = new QSpacerItem(72, 27, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout->setStretch(4, 1);

        horizontalLayout->addLayout(verticalLayout);

        widgetVideo = new QWidget(centralWidget);
        widgetVideo->setObjectName("widgetVideo");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetVideo->sizePolicy().hasHeightForWidth());
        widgetVideo->setSizePolicy(sizePolicy1);
        widgetVideo->setMinimumSize(QSize(1000, 640));
        widgetVideo->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(widgetVideo);

        horizontalLayout->setStretch(1, 1);
        ImageProcessClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageProcessClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1285, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName("menu");
        ImageProcessClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageProcessClass);
        mainToolBar->setObjectName("mainToolBar");
        ImageProcessClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageProcessClass);
        statusBar->setObjectName("statusBar");
        ImageProcessClass->setStatusBar(statusBar);
        dockWidget = new QDockWidget(ImageProcessClass);
        dockWidget->setObjectName("dockWidget");
        dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        dockWidget->setWidget(dockWidgetContents);
        ImageProcessClass->addDockWidget(Qt::BottomDockWidgetArea, dockWidget);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionSetting);

        retranslateUi(ImageProcessClass);

        QMetaObject::connectSlotsByName(ImageProcessClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageProcessClass)
    {
        ImageProcessClass->setWindowTitle(QCoreApplication::translate("ImageProcessClass", "ImageProcess", nullptr));
        actionSetting->setText(QCoreApplication::translate("ImageProcessClass", "\350\256\276\347\275\256", nullptr));
        pushButtonOpen->setText(QCoreApplication::translate("ImageProcessClass", "\346\211\223\345\274\200", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("ImageProcessClass", "\345\205\263\351\227\255", nullptr));
        pushButtonAnalyzer->setText(QCoreApplication::translate("ImageProcessClass", "\345\256\236\346\227\266\346\225\260\346\215\256", nullptr));
        menu->setTitle(QCoreApplication::translate("ImageProcessClass", "\345\233\276\345\203\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageProcessClass: public Ui_ImageProcessClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESS_H
