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
    double computeSobelSharpness(const cv::Mat& mat, int kernelSize, double threshold);
    double computeLaplacianSharpness(const cv::Mat& mat, int kernelSize, double threshold);
    double computeBrennerSharpness(const cv::Mat& mat, int kernelSize, double threshold);
};