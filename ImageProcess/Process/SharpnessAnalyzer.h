#pragma once
#include <qobject.h>
#include <qimage.h>
#include <qmutex.h>

class SharpnessAnalyzer : public QObject
{
    Q_OBJECT
public:
    explicit SharpnessAnalyzer(QObject* parent = nullptr);
    ~SharpnessAnalyzer() override = default;

public slots:
    void analyze(const QImage& image);
    void setKernelStrength(int s) { m_strength = qMax(1, s); }

private slots:
    void processLatest();

signals:
    void sharpnessReady(double value);

private:
    QMutex  m_mutex;
    QImage  m_latestImage;
    bool    m_hasNew{ false };
    bool    m_processing{ false };
    int     m_strength{ 1 };
};