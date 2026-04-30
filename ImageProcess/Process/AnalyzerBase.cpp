#include "AnalyzerBase.h"
#include "SettingDialog.h"
#include "SharpnessAnalyzer.h"
#include "opencv2/opencv.hpp"

AnalyzerBase::AnalyzerBase(QObject* parent)
    : QObject(parent)
{
    m_params = new AnalyzerParameters;
}

void AnalyzerBase::QImage2Mat(const QImage& image, cv::Mat& mat)
{
    if (image.isNull())
        return;
    switch(image.format())
    {
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
            mat = cv::Mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), image.bytesPerLine()).clone();
            break;
        case QImage::Format_RGB888:
        {
            mat = cv::Mat(image.height(), image.width(), CV_8UC3, const_cast<uchar*>(image.bits()), image.bytesPerLine()).clone();
            cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
        }
            break;
        case QImage::Format_Indexed8:
            mat = cv::Mat(image.height(), image.width(), CV_8UC1, const_cast<uchar*>(image.bits()), image.bytesPerLine()).clone();
            break;
        default:
            QImage converted = image.convertToFormat(QImage::Format_RGB888);
            QImage2Mat(converted, mat);
            break;
    }
}

void AnalyzerBase::Mat2QImage(const cv::Mat& mat, QImage& image)
{
    if (mat.empty())
        return;
    switch(mat.type())
    {
        case CV_8UC1:
            image = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8).copy();
            break;
        case CV_8UC3:
        {
            cv::Mat rgbMat;
            cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);
            image = QImage(rgbMat.data, rgbMat.cols, rgbMat.rows, rgbMat.step, QImage::Format_RGB888).copy();
        }
            break;
        case CV_8UC4:
        {
            image = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32).copy();
        }
            break;
        default:
            image = QImage();   // Unsupported format, return an empty image
            break;
    }
}

void AnalyzerBase::analyze(const QImage& image)
{
    if (image.isNull())
        return;
    // 只保留最新帧，避免排队处理历史帧
    {
        QMutexLocker locker(&m_mutex);
        m_latestImage = image.copy();
        m_hasNew = true;
        if (m_processing) 
        {
            return;// 已有处理在进行中，直接返回，处理完成后会检查是否有新帧
        }
        m_processing = true;
    }
    // 排队执行一次处理（在该对象所在线程中）
    QMetaObject::invokeMethod(this, "processLatest", Qt::QueuedConnection);
}

void AnalyzerBase::setParams(const AnalyzerParameters& params)
{
    QMutexLocker locker(&m_mutex);
    *m_params = params;
}

void AnalyzerBase::processLatest()
{
    while (true) 
    {
        QImage frame;
        {
            QMutexLocker locker(&m_mutex);
            if (!m_hasNew) 
            {
                m_processing = false;
                return;
            }
            frame = m_latestImage;
            m_hasNew = false;
        }
        if (frame.isNull())
            continue;
        QElapsedTimer timer;
        timer.start();
        m_timeCount   = 0.0;
        double result = imageProcess(frame);
        m_timeCount   = timer.elapsed();
        emit resultReady(result);
        emit resultTimeCounted(m_timeCount);
    }
}

AnalyzerBase* AnalyzerFactory::createAnalyzer(AlgorithmType type, QObject* parent)
{
    switch (type) {
    case AlgorithmType::Sharpness:
        return new SharpnessAnalyzer(parent);
        //case AlgorithmType::FeatureMatch:
        //    return new FeatureMatchAnalyzer(parent);
        //case AlgorithmType::Detect:
        //    return new DetectAnalyzer(parent);
    default:
        return nullptr;
    }
}

QString AnalyzerFactory::getAnalyzerName(AlgorithmType type)
{
    switch (type) {
    case AlgorithmType::Sharpness:
        return QStringLiteral("Sharpness");
        //case AlgorithmType::FeatureMatch:
        //    return QStringLiteral("特征匹配");
        //case AlgorithmType::Detect:
        //    return QStringLiteral("检测");
    default:
        return QStringLiteral("Unknown");
    }
}

void AnalyzerThreadManager::analyzeImage(const QImage& image)
{
    if (!m_currentAnalyzer) 
        return;
    if (m_paused)
        return;
    QMetaObject::invokeMethod(m_currentAnalyzer, "analyze", Qt::QueuedConnection, Q_ARG(QImage, image));
}

void AnalyzerThreadManager::setParameters(const AnalyzerParameters& params)
{
    if (!m_currentAnalyzer) 
        return;

    QMetaObject::invokeMethod(m_currentAnalyzer, "setParams", Qt::QueuedConnection, Q_ARG(AnalyzerParameters, params));
}

