#include "AnalyzerBase.h"
#include "SettingDialog.h"
#include "SharpnessAnalyzer.h"

AnalyzerBase::AnalyzerBase(QObject* parent)
    : QObject(parent)
{
    m_params = new AnalyzerParameters;
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

