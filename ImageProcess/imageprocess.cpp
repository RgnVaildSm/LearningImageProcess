#include "imageprocess.h"
#include <qboxlayout.h>
#include <algorithm>
#include "SharpnessAnalyzer.h"
#include "AnalyzerChartWidget.h"
#include "SettingDialog.h"
#include <qdockwidget.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qaction.h>

ImageProcess::ImageProcess(QWidget *parent)
    : QMainWindow(parent)
    , m_camera(new CameraBase(this))
    , m_timer(new QTimer(this))
{
    ui.setupUi(this);
    m_labelCameraInfo = new QLabel(this);
    ui.statusBar->addPermanentWidget(m_labelCameraInfo);
    m_AnalyzerChart = new AnalyzerChartWidget();
    ui.dockWidget->setWidget(m_AnalyzerChart);
    ui.dockWidget->setWindowTitle(QStringLiteral("分析结果"));

    // 创建分析器并移到后台线程
    m_sharpnessAnalyzer = new SharpnessAnalyzer(); // no parent
    m_sharpnessThread = new QThread(this);
    m_sharpnessAnalyzer->moveToThread(m_sharpnessThread);
    connect(m_sharpnessThread, &QThread::finished, m_sharpnessAnalyzer, &QObject::deleteLater);
    m_sharpnessThread->start();

    m_settingsDialog = new SettingsDialog(this);
    connect(ui.actionSetting, &QAction::triggered, this, &ImageProcess::OnShowSettings);

    //连接信号和槽
    connect(m_timer.get(),     &QTimer::timeout,           this, &ImageProcess::UpdateTimer);
    connect(m_camera.get(),    &CameraBase::frameReady,    this, &ImageProcess::UpdateVideoFrame);
    connect(m_camera.get(),    &CameraBase::errorOccurred, this, &ImageProcess::HandleError);
    connect(m_camera.get(),    &CameraBase::formatChanged, this, &ImageProcess::OnCameraFormatChanged);// 当 CameraBase 在 active 后报告格式时，更新状态栏
    connect(m_camera.get(),    &CameraBase::frameReady,    m_sharpnessAnalyzer, &SharpnessAnalyzer::analyze, Qt::QueuedConnection);// 连接帧到后台分析器（QueuedConnection 确保跨线程）
    connect(m_sharpnessAnalyzer, &SharpnessAnalyzer::sharpnessReady, this, &ImageProcess::OnSharpnessUpdated, Qt::QueuedConnection);// 分析器结果到主线程的槽（自动 queued）
    // 设置对话框参数改变应用到分析器（Queued）
    connect(m_settingsDialog, &SettingsDialog::parametersChanged, this, [this](int newStrength){
        // 使用 invokeMethod 保证跨线程调用安全
        QMetaObject::invokeMethod(m_sharpnessAnalyzer, "setKernelStrength", Qt::QueuedConnection, Q_ARG(int, newStrength));
        });
    connect(ui.pushButtonOpen, &QPushButton::clicked, this, [this]() {
        if (m_camera.get()->IsOpen())
            return;
        auto index = ui.comboBoxCameras->currentIndex();
        if (index >= 0)
        {
            const QString deviceId = ui.comboBoxCameras->itemData(index).toString();
            auto camerasList = m_camera->GetCameraDevices();
            auto it = std::find_if(camerasList.begin(), camerasList.end(), [&](const QCameraDevice &d) {
                return d.id() == deviceId;
                });
            if (it != camerasList.end())
            {
                m_camera->Start(*it);
                if (m_camera.get()->IsOpen())
                {
                    ui.comboBoxCameras->setEnabled(false);
                }
            }
        }
        });
    connect(ui.pushButtonClose, &QPushButton::clicked, this, [ this ]() {
           m_camera->Stop();
           ui.comboBoxCameras->setEnabled(true);
           if (m_labelCameraInfo) m_labelCameraInfo->clear();
           if (m_AnalyzerChart)   m_AnalyzerChart->clearSamples();
           ui.widgetVideo->findChild<QLabel*>("dynamicVideoLabel")->clear();
        });
    connect(ui.pushButtonAnalyzer, &QPushButton::clicked, this, [this](bool bchecked){
           if (bchecked) ui.dockWidget->show();
           else          ui.dockWidget->hide();
        });
    m_timer->start(1000);
    m_timer->start();
    ui.pushButtonAnalyzer->click();
}

ImageProcess::~ImageProcess()
{
    if (m_sharpnessThread) 
    {
        m_sharpnessThread->quit();
        m_sharpnessThread->wait();
    }
}

void ImageProcess::UpdateTimer()
{
    //定时器触发时的处理逻辑，例如更新UI、检查相机状态等
    if (!ui.comboBoxCameras->isEnabled() || m_camera.get()->IsOpen())
        return;

    //必要时更新相机列表
    auto camerasList = m_camera->GetCameraDevices();
    ui.comboBoxCameras->clear();
    for (const auto& camera : camerasList) 
    {
        ui.comboBoxCameras->addItem(camera.description(), camera.id());
    }
}

void ImageProcess::UpdateVideoFrame(const QImage& frame)
{
    if (frame.isNull())
        return;
    // 显示视频帧的处理逻辑，例如将帧转换为适合显示的格式并更新UI
    QLabel* label = qobject_cast<QLabel*>(ui.widgetVideo);
    if (!label) label = ui.widgetVideo->findChild<QLabel*>();
    if (!label)
    {
        // 在占位 widget 上创建一个新的 QLabel 并填充它
        label = new QLabel(ui.widgetVideo);
        label->setObjectName("dynamicVideoLabel");
        label->setAlignment(Qt::AlignCenter);
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        label->setContentsMargins(0, 0, 0, 0);

        if (!ui.widgetVideo->layout())
        {
            auto layout = new QHBoxLayout(ui.widgetVideo);
            layout->setContentsMargins(0, 0, 0, 0);
            ui.widgetVideo->setLayout(layout);
        }
        ui.widgetVideo->layout()->addWidget(label);
    }

    // 将帧转换为 QPixmap 并按显示区域等比缩放，平滑转换
    QPixmap pixmap = QPixmap::fromImage(frame);
    if (!pixmap.isNull())
    {
        QSize targetSize = label->size();
        if (targetSize.isEmpty())
            targetSize = frame.size();
        label->setPixmap(pixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    // 不在此线程计算锐度：已连接到后台分析器
}

void ImageProcess::HandleError(const QString& errorString)
{
    //处理相机错误的逻辑，例如显示错误消息、尝试重新连接等
    ui.statusBar->showMessage(errorString, 5000); // 在状态栏显示错误信息，持续5秒
}
void ImageProcess::OnSharpnessUpdated(double value)
{
    if (m_AnalyzerChart)
        m_AnalyzerChart->addSample(value);
}

void ImageProcess::OnShowSettings()
{
    QString camInfo;
    auto index = ui.comboBoxCameras->currentIndex();
    if (index >= 0)
    {
        auto camerasList = m_camera->GetCameraDevices();
        auto id = ui.comboBoxCameras->itemData(index).toString();
        auto it = std::find_if(camerasList.begin(), camerasList.end(), [&](const QCameraDevice &d) {
            return d.id() == id;
            });
        if (it != camerasList.end())
        {
            auto fmt = m_camera->GetCurrentCameraFormat();
            if (!fmt.isNull())
                camInfo = QString("%1  %2x%3  @ %4").arg(it->description())
                .arg(fmt.resolution().width()).arg(fmt.resolution().height()).arg(fmt.maxFrameRate());
            else
                camInfo = it->description();
        }
    }
    m_settingsDialog->setCameraInfo(camInfo);
    m_settingsDialog->exec();
}

void ImageProcess::OnCameraFormatChanged(const QCameraFormat& fmt)
{
    // 更新状态栏显示
    QString info = QStringLiteral(" %1x%2   FPS: %3 ")
        .arg(fmt.resolution().width())
        .arg(fmt.resolution().height())
        .arg(fmt.maxFrameRate(), 0, 'f', 2);
    if (m_labelCameraInfo)
        m_labelCameraInfo->setText(info);
}
