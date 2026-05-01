#include "SharpnessAnalyzer.h"
#include <qmath.h>
#include <qmetaobject.h>


SharpnessAnalyzer::SharpnessAnalyzer(QObject* parent)
    : AnalyzerBase(parent)
{
}

double SharpnessAnalyzer::imageProcess(const QImage& image)
{
    if (image.isNull())
        return 0.0;
    AnalyzerParameters currentParams = *getParams();
    int kernelSize = 3;
    switch(currentParams.sharpnessKernel)
    {
        case SharpnessKernel::K3x3: kernelSize = 3; break;
        case SharpnessKernel::K5x5: kernelSize = 5; break;
        case SharpnessKernel::K7x7: kernelSize = 7; break;
        case SharpnessKernel::K9x9: kernelSize = 9; break;
        default: break;
    }
    double value = 0.0;
    cv::Mat gray;
    if (!image.isGrayscale())
    {
        QImage ori;
        ori = image.convertToFormat(QImage::Format_Grayscale8);
        QImage2Mat(ori, gray);
    }
    else
    {
        QImage2Mat(image, gray);
    }
    if (gray.empty())
        return value;
    switch(currentParams.sharpnessAlgorithm)
    {
        case SharpnessAlgorithm::Sobel:     value = computeSobelSharpness(gray, kernelSize, currentParams.sharpnessThreshold); break;
        case SharpnessAlgorithm::Laplacian: value = computeLaplacianSharpness(gray, kernelSize, currentParams.sharpnessThreshold); break;
        case SharpnessAlgorithm::Brenner:   value = computeBrennerSharpness(gray, kernelSize, currentParams.sharpnessThreshold); break;
    }
    return value;
}

double SharpnessAnalyzer::computeSobelSharpness(const cv::Mat& mat, int kernelSize, double threshold)
{
    
    return 0.0;
}

double SharpnessAnalyzer::computeLaplacianSharpness(const cv::Mat& mat, int kernelSize, double threshold)
{
    return 0.0;
}

double SharpnessAnalyzer::computeBrennerSharpness(const cv::Mat& mat, int kernelSize, double threshold)
{
    return 0.0;
}

