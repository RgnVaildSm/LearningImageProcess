#pragma once
#include "AnalyzerBase.h"
#include <qimage.h>
#include <qmutex.h>

class SharpnessAnalyzer : public AnalyzerBase
{
    Q_OBJECT
public:
    explicit SharpnessAnalyzer(QObject* parent = nullptr);
    ~SharpnessAnalyzer() override = default;

protected:
    double imageProcess(const QImage& image) override;

private:
    
};