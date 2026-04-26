#include "SharpnessAnalyzer.h"
#include <qmath.h>
#include <qmetaobject.h>

SharpnessAnalyzer::SharpnessAnalyzer(QObject* parent)
    : QObject(parent)
{
}
void SharpnessAnalyzer::analyze(const QImage& image)
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

void SharpnessAnalyzer::processLatest()
{
    while (true) {
        QImage frame;
        {
            QMutexLocker locker(&m_mutex);
            if (!m_hasNew) {
                m_processing = false;
                return;
            }
            frame = m_latestImage;
            m_hasNew = false;
        }

        if (frame.isNull())
            continue;

        QImage gray = frame.convertToFormat(QImage::Format_Grayscale8);
        const int w = gray.width();
        const int h = gray.height();
        if (w < 3 || h < 3)
            continue;

        const int stride = gray.bytesPerLine();
        const uchar* data = gray.constBits();

        double sum = 0.0;
        size_t count = 0;

        for (int y = 1; y < h - 1; ++y) {
            for (int x = 1; x < w - 1; ++x) {
                int center = data[y * stride + x];
                int lap = 0;
                lap += data[(y-1)*stride + (x-1)];
                lap += data[(y-1)*stride + (x)];
                lap += data[(y-1)*stride + (x+1)];
                lap += data[(y)*stride + (x-1)];
                lap += data[(y)*stride + (x+1)];
                lap += data[(y+1)*stride + (x-1)];
                lap += data[(y+1)*stride + (x)];
                lap += data[(y+1)*stride + (x+1)];
                lap = m_strength * (8 * center - lap);

                double val = qAbs(lap);
                sum += val;
                ++count;
            }
        }

        if (count == 0)
            continue;

        double mean = sum / double(count);
        emit sharpnessReady(mean);
    }
}
