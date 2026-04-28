#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_imageprocess.h"
#include "Camera\CameraBase.h"
#include <QTimer>
#include <qthread.h>
#include <qlabel.h>
#include "AnalyzerBase.h"
#include "AnalyzerChartWidget.h"
#include "SettingDialog.h"

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
    void OnAlgorithmChanged(int index);

private:
    Ui::ImageProcessClass ui;
    AlgorithmType               m_algorithmType{ AlgorithmType::Sharpness };
    QScopedPointer<QTimer>      m_timer;
    QScopedPointer<CameraBase>  m_camera;
    AnalyzerBase*               m_analyzer{nullptr};
    AnalyzerThreadManager*      m_threadManager{ nullptr };
    AnalyzerChartWidget*        m_AnalyzerChart{nullptr};
    SettingsDialog*             m_settingsDialog{nullptr};
    QLabel*                     m_labelCameraInfo{nullptr};

};
