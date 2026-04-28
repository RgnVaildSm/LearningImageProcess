#include "imageprocess.h"
#include <qboxlayout.h>
#include <algorithm>
#include <qdockwidget.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qaction.h>
#include "SharpnessAnalyzer.h"

ImageProcess::ImageProcess(QWidget *parent)
    : QMainWindow(parent)
    , m_camera(new CameraBase(this))
    , m_timer(new QTimer(this))
    , m_labelCameraInfo(new QLabel(this))
    , m_AnalyzerChart(new AnalyzerChartWidget())
    , m_settingsDialog(new SettingsDialog(this))
    , m_threadManager(new AnalyzerThreadManager(this))
{
    ui.setupUi(this);
    ui.statusBar->addPermanentWidget(m_labelCameraInfo);
    ui.dockWidget->setWidget(m_AnalyzerChart);
    for(auto& item : supportedAlgorithms)
    {
        ui.comboBoxAlgorithm->addItem(item);
    }
    ui.comboBoxAlgorithm->setCurrentIndex(0);
    ui.dockWidget->setWindowTitle(AnalyzerFactory::getAnalyzerName(m_algorithmType));
    m_threadManager->createAnalyzer<SharpnessAnalyzer>();   // 创建默认分析器
    
    //连接信号和槽
    connect(ui.actionSetting,  &QAction::triggered,        this, &ImageProcess::OnShowSettings);
    connect(m_timer.get(),     &QTimer::timeout,           this, &ImageProcess::UpdateTimer);
    connect(m_camera.get(),    &CameraBase::frameReady,    this, &ImageProcess::UpdateVideoFrame);
    connect(m_camera.get(),    &CameraBase::errorOccurred, this, &ImageProcess::HandleError);
    connect(m_camera.get(),    &CameraBase::formatChanged, this, &ImageProcess::OnCameraFormatChanged);
    connect(m_camera.get(),    &CameraBase::frameReady, m_threadManager, &AnalyzerThreadManager::analyzeImage, Qt::QueuedConnection);
    connect(m_settingsDialog,  &SettingsDialog::parametersChanged, this, [this](const AnalyzerParameters &p){
        QMetaObject::invokeMethod(m_threadManager, "setParameters", Qt::QueuedConnection, Q_ARG(AnalyzerParameters, p));
        });
    connect(m_threadManager,   &AnalyzerThreadManager::resultReady, this, &ImageProcess::OnSharpnessUpdated);
    connect(m_threadManager,   &AnalyzerThreadManager::resultTimeCounted, this, [this](double ms){
        ui.statusBar->showMessage(QStringLiteral("分析耗时: %1 ms").arg(ms), 1);
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
                    ui.comboBoxAlgorithm->setEnabled(false);
                    m_settingsDialog->setWidgetEnabled(false);
                    m_settingsDialog->setCameraName(it->description());
                    m_settingsDialog->setCameraSerialNumber(m_camera->GetCameraSerialNumber());
                }
            }
        }
        });
    connect(ui.pushButtonClose, &QPushButton::clicked, this, [ this ]() {
           m_camera->Stop();
           ui.comboBoxCameras->setEnabled(true);
           ui.comboBoxAlgorithm->setEnabled(true);
           m_settingsDialog->setWidgetEnabled(true);
           m_settingsDialog->setCameraName(QString());
           m_settingsDialog->setCameraSerialNumber(QString());
           if (m_labelCameraInfo) m_labelCameraInfo->clear();
           if (m_AnalyzerChart)   m_AnalyzerChart->clearSamples();
           ui.widgetVideo->findChild<QLabel*>("dynamicVideoLabel")->clear();
        });
    connect(ui.pushButtonAnalyzer, &QPushButton::clicked, this, [this](bool bchecked){
           if (bchecked) ui.dockWidget->show();
           else          ui.dockWidget->hide();
        });
    connect(ui.comboBoxAlgorithm, &QComboBox::currentIndexChanged, this, &ImageProcess::OnAlgorithmChanged);
    m_timer->start(1000);
    m_timer->start();
    ui.pushButtonAnalyzer->click();
}

ImageProcess::~ImageProcess()
{
}

void ImageProcess::UpdateTimer()
{
    //定时器触发时的处理逻辑，例如更新UI、检查相机状态等
    if (m_camera.get()->IsOpen())
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
    ui.statusBar->showMessage(errorString, 5000);
}

void ImageProcess::OnSharpnessUpdated(double value)
{
    if (m_AnalyzerChart)
        m_AnalyzerChart->addSample(value);
}

void ImageProcess::OnShowSettings()
{
    if (m_camera.get()->IsOpen())
    {
        m_settingsDialog->setWidgetEnabled(false);
    }
    else
    {
        m_settingsDialog->setWidgetEnabled(true);

    }
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

void ImageProcess::OnAlgorithmChanged(int index)
{
    if (index < 0 || index >= supportedAlgorithms.size())
        return;
    m_algorithmType = static_cast<AlgorithmType>(index);
    ui.dockWidget->setWindowTitle(AnalyzerFactory::getAnalyzerName(m_algorithmType));
    // 切换分析器
    switch (m_algorithmType)
    {
    case AlgorithmType::Sharpness:
        m_threadManager->createAnalyzer<SharpnessAnalyzer>();
        break;
    //case AlgorithmType::Laplacian:
    //    m_threadManager->createAnalyzer<LaplacianAnalyzer>();
    //    break;
    //case AlgorithmType::Brenner:
    //    m_threadManager->createAnalyzer<BrennerAnalyzer>();
        break;
    default:
        break;
    }
}
