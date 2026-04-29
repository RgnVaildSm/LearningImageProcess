#include "imageprocess.h"
#include <qboxlayout.h>
#include <algorithm>
#include <qdockwidget.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qaction.h>
#include <qexception.h>
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
    // 创建默认分析器
    ui.comboBoxAlgorithm->setCurrentIndex(0);
    ui.dockWidget->setWindowTitle(AnalyzerFactory::getAnalyzerName(m_algorithmType));
    m_threadManager->createAnalyzer<SharpnessAnalyzer>();
    
    // 连接信号和槽
    connect(ui.pushButtonOpen,      &QPushButton::clicked,                          this, &ImageProcess::on_pushButtonOpen_clicked);
    connect(ui.pushButtonClose,     &QPushButton::clicked,                          this, &ImageProcess::on_pushButtonClose_clicked);
    connect(ui.pushButtonAnalyzer,  &QPushButton::clicked,                          this, &ImageProcess::on_pushButtonAnalyzer_clicked);
    connect(ui.checkBoxAnalyze,     &QCheckBox::clicked,                            this, &ImageProcess::on_checkBoxAnalyze_checked);
    connect(ui.actionSetting,       &QAction::triggered,                            this, &ImageProcess::OnShowSettings);
    connect(m_timer.get(),          &QTimer::timeout,                               this, &ImageProcess::UpdateTimer);
    connect(m_camera.get(),         &CameraBase::errorOccurred,                     this, &ImageProcess::HandleError, Qt::QueuedConnection);
    connect(m_settingsDialog,       &SettingsDialog::parametersChanged,             this, &ImageProcess::OnParametersChanged);
    connect(m_threadManager,        &AnalyzerThreadManager::resultReady,            this, &ImageProcess::OnAnalyzeResult);
    connect(m_threadManager,        &AnalyzerThreadManager::resultTimeCounted,      this, &ImageProcess::OnAnalyzeTimeCounted);
    connect(ui.comboBoxAlgorithm,   &QComboBox::currentIndexChanged,                this, &ImageProcess::OnAlgorithmChanged);
    m_timer->start(500);
    m_timer->start();
    ui.dockWidget->show();
}

ImageProcess::~ImageProcess()
{
}

void ImageProcess::on_pushButtonOpen_clicked(bool bChecked)
{
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
                m_settingsDialog->setCameraName(it->description());
                m_settingsDialog->setCameraSerialNumber(m_camera->GetCameraSerialNumber());
                connect(m_camera.get(),&CameraBase::frameReady,    this, &ImageProcess::UpdateVideoFrame);
                connect(m_camera.get(),&CameraBase::formatChanged, this, &ImageProcess::OnCameraFormatChanged);
                connect(m_camera.get(),&CameraBase::frameReady, m_threadManager, &AnalyzerThreadManager::analyzeImage, Qt::QueuedConnection);
            }
        }
    }
    else
    {
        ui.statusBar->showMessage(QStringLiteral("Can Not Find Any Available Camera!"), 2000);
    }
}

void ImageProcess::on_pushButtonClose_clicked(bool bChecked)
{
    closeCamera();
    setSettingsDialog(true);
}

void ImageProcess::on_pushButtonAnalyzer_clicked(bool bChecked)
{
    bChecked ? ui.dockWidget->show() : ui.dockWidget->hide();
}

void ImageProcess::on_checkBoxAnalyze_checked(bool bChecked)
{
    bChecked ? m_threadManager->resumeProcessing() : m_threadManager->pauseProcessing();
}

void ImageProcess::setSettingsDialog(bool bEnable)
{
    //除开当前分析器以外的算法设置项根据相机状态启用或禁用
    for (int i = 0; i < ui.comboBoxAlgorithm->count(); ++i)
    {
        AlgorithmType algoType = static_cast<AlgorithmType>(i);
        m_settingsDialog->setWidgetEnabled(i, bEnable ? true : (algoType == m_algorithmType));
    }
}

void ImageProcess::closeCamera()
{
    m_camera->Stop();
    ui.comboBoxCameras->setEnabled(true);
    ui.comboBoxAlgorithm->setEnabled(true);
    m_settingsDialog->setCameraName(QString());
    m_settingsDialog->setCameraSerialNumber(QString());
    if (m_labelCameraInfo) m_labelCameraInfo->clear();
    if (m_AnalyzerChart)   m_AnalyzerChart->clearSamples();
    ui.widgetVideo->findChild<QLabel*>("dynamicVideoLabel")->clear();
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
    // 如果当前不在 GUI 线程，则排队回到 GUI 线程执行
    if (QThread::currentThread() != qApp->thread()) 
    {
        QMetaObject::invokeMethod(this, "HandleError", Qt::QueuedConnection, Q_ARG(QString, errorString));
        return;
    }
    if (m_settingsDialog && m_settingsDialog->isVisible()) 
    {
        m_settingsDialog->done(QDialog::Rejected);
    }

    // 断开相机并恢复 UI 状态
    closeCamera();

    //断开相机与分析器的连接，防止在相机发生错误后继续处理帧数据，相机打开时再连接
    disconnect(m_camera.get(), &CameraBase::frameReady,    m_threadManager, &AnalyzerThreadManager::analyzeImage);
    disconnect(m_camera.get(), &CameraBase::frameReady,    this,            &ImageProcess::UpdateVideoFrame);
    disconnect(m_camera.get(), &CameraBase::formatChanged, this,            &ImageProcess::OnCameraFormatChanged);
}

void ImageProcess::OnParametersChanged(const AnalyzerParameters& param)
{
    QMetaObject::invokeMethod(m_threadManager, "setParameters", Qt::QueuedConnection, Q_ARG(AnalyzerParameters, param));
}

void ImageProcess::OnAnalyzeResult(double value)
{
    if (m_AnalyzerChart)
        m_AnalyzerChart->addSample(value);
}

void ImageProcess::OnAnalyzeTimeCounted(double ms)
{
}

void ImageProcess::OnShowSettings()
{
    setSettingsDialog(!m_camera.get()->IsOpen());
    try 
    {
        m_settingsDialog->exec();
    } catch (const QException& ex) {
        m_settingsDialog->reject();
        m_settingsDialog->close();
        ui.statusBar->showMessage(QStringLiteral("Settings Dialog Error: %1").arg(ex.what()), 5000);
    }
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


