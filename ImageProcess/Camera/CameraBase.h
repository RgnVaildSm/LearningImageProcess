#pragma once
#include "CameraDef.h"

class CameraBase : public QObject
{
    Q_OBJECT

public:
    explicit CameraBase(QObject* parent = Q_NULLPTR);
    virtual ~CameraBase();
    virtual void Start(const QCameraDevice& device);
    virtual void Stop();
    virtual void Snap();
    virtual bool IsOpen() const;
    QCameraFormat GetCurrentCameraFormat() const;
    QString GetCameraSerialNumber() const;

signals:
    void frameReady(const QImage& frame);
    void errorOccurred(const QString& errorString);
    void snapshotReady(const QImage& snapshot);
    void formatChanged(const QCameraFormat& format);

public slots:
    QList<QCameraDevice> GetCameraDevices();
    QCameraDevice GetCurrentCameraDevice() const;

private slots:
    void processFrame(int id, const QImage& img);
    void handleError(int id, QImageCapture::Error error, const QString &errorString);
    void handleVideoFrame(const QVideoFrame &frame);

private:
    Q_DISABLE_COPY_MOVE(CameraBase);

private:
    QScopedPointer<QCamera>                 m_camera;
    QScopedPointer<QMediaCaptureSession>    m_captureSession;
    QScopedPointer<QImageCapture>           m_imageCapture;
    QScopedPointer<QVideoSink>              m_videoSink;
    bool                                    m_bIsSnap{false};
};
