#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_imageprocess.h"
#include "Camera\CameraBase.h"
#include <QTimer>
#include <qthread.h>
#include <qlabel.h>

class SharpnessAnalyzer;
class AnalyzerChartWidget;
class SettingsDialog;

class ImageProcess : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcess(QWidget *parent = nullptr);
    ~ImageProcess();


protected:
    

private slots:
    void UpdateTimer();
    void UpdateVideoFrame(const QImage& frame);
    void HandleError(const QString& errorString);
    void OnSharpnessUpdated(double value);
    void OnShowSettings();
    void OnCameraFormatChanged(const QCameraFormat& fmt);

private:
    Ui::ImageProcessClass ui;
    QScopedPointer<QTimer>      m_timer;
    QScopedPointer<CameraBase>  m_camera;
    SharpnessAnalyzer*          m_sharpnessAnalyzer{nullptr};
    QThread*                    m_sharpnessThread{nullptr};
    AnalyzerChartWidget*        m_AnalyzerChart{nullptr};
    SettingsDialog*             m_settingsDialog{nullptr};
    QLabel*                     m_labelCameraInfo{nullptr};

};
