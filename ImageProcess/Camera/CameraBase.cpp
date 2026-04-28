#include "CameraBase.h"

CameraBase::CameraBase(QObject* parent)
    : QObject(parent)
{

}

CameraBase::~CameraBase()
{
    Stop();
}

void CameraBase::Start(const QCameraDevice& device)
{
    if (device.isNull())
        return;
    m_camera.reset(new QCamera(device));
    m_captureSession.reset(new QMediaCaptureSession());
    m_imageCapture.reset(new QImageCapture());
    m_videoSink.reset(new QVideoSink());
    m_captureSession->setCamera(m_camera.get());
    m_captureSession->setImageCapture(m_imageCapture.get());
    m_captureSession->setVideoOutput(m_videoSink.get());

    // 选择最合适的视频格式：优先可转换为 QImage 的格式，按分辨率和帧率排序选择最优项
    const auto formats = device.videoFormats();
#if _DEBUG
    qDebug() << "Available camera formats:";
    for (const auto &format : formats)
    {
        qDebug() << "  " << format.pixelFormat() << format.resolution() << format.maxFrameRate() << "\n";
    }
#endif
    if (!formats.isEmpty())
    {
        QList<QCameraFormat> convertible;
        for (const auto &f : formats)
        {
            if (QVideoFrameFormat::imageFormatFromPixelFormat(f.pixelFormat()) != QImage::Format_Invalid)
                convertible.append(f);
        }
    
        auto chooseBest = [](const QList<QCameraFormat> &list) -> QCameraFormat {
            // 以分辨率面积为主、帧率为辅进行比较
            return *std::max_element(list.begin(), list.end(), [](const QCameraFormat &a, const QCameraFormat &b) {
                qint64 areaA = qint64(a.resolution().width()) * a.resolution().height();
                qint64 areaB = qint64(b.resolution().width()) * b.resolution().height();
                if (areaA != areaB) return areaA < areaB;
                return a.maxFrameRate() < b.maxFrameRate();
                });
            };
        // 在所有格式中选择最优一个
        if (!convertible.isEmpty())
        {
            m_camera->setCameraFormat(chooseBest(convertible));
        }
        else
        {
            m_camera->setCameraFormat(chooseBest(formats));
        }
        // 连接到本类的槽
        connect(m_imageCapture.get(), &QImageCapture::imageCaptured, this, &CameraBase::processFrame);
        connect(m_imageCapture.get(), &QImageCapture::errorOccurred, this, &CameraBase::handleError);
        connect(m_videoSink.get(), &QVideoSink::videoFrameChanged, this, &CameraBase::handleVideoFrame);
        
        // 转发 QCamera 错误为统一的 QString 类型的 errorOccurred 信号
        connect(m_camera.get(), &QCamera::errorOccurred, this, [this](QCamera::Error error) {
            emit errorOccurred(QStringLiteral("Camera error: %1").arg(static_cast<int>(error)));
            });
        // 当相机 active 状态变化（启动完成），向外部通知当前格式
        connect(m_camera.get(), &QCamera::activeChanged, this, [this](bool active) {
            if (active && m_camera) {
                emit formatChanged(m_camera->cameraFormat());
            }
            });
        // 启动相机（状态变化通过信号异步通知）
        m_camera->start();
#if _DEBUG
        qDebug() << "Camera started with format:" << m_camera->cameraFormat().pixelFormat() 
            << m_camera->cameraFormat().resolution() << m_camera->cameraFormat().maxFrameRate();
#endif
    }
}

void CameraBase::Stop()
{
    if (m_camera) 
    {
        m_camera->stop();
        m_camera.reset();
        m_captureSession.reset();
        m_imageCapture.reset();
        m_videoSink.reset();
    }
}

bool CameraBase::IsOpen() const
{
    if (!m_camera)
        return false;
    return m_camera->isActive();
}

QCameraFormat CameraBase::GetCurrentCameraFormat() const
{
    if (!IsOpen())
        return QCameraFormat();
    return m_camera->cameraFormat();
}

QString CameraBase::GetCameraSerialNumber() const
{
    //if (m_)
    return QString("0.0.0.1");
}

QList<QCameraDevice> CameraBase::GetCameraDevices()
{
    return QMediaDevices::videoInputs();
}

void CameraBase::Snap()
{
    if (m_imageCapture && IsOpen() && !m_bIsSnap) 
    {
        m_bIsSnap = true;
        //if you need to snap image to file, use captureToFile()
        m_imageCapture->capture();
    }
}

void CameraBase::processFrame(int id, const QImage& img)
{
    m_bIsSnap = false;
    emit snapshotReady(img);
    Q_UNUSED(id)
    if (m_bIsSnap) 
    {
        emit snapshotReady(img);
        m_bIsSnap = false;
    } 
    else 
    {
        emit frameReady(img);
    }
}

void CameraBase::handleError(int id, QImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id)
    Q_UNUSED(error)
    m_bIsSnap = false;
    emit errorOccurred(errorString);
}

void CameraBase::handleVideoFrame(const QVideoFrame &frame)
{
    if (frame.isValid())
    {
        QImage img = frame.toImage();
        emit frameReady(img);
    }
}

QCameraDevice CameraBase::GetCurrentCameraDevice() const
{
    if (!IsOpen())
        return QCameraDevice();
    return m_camera->cameraDevice();
}


