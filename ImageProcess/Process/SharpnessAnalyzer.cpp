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
        case SharpnessKernel::K1x1: kernelSize = 1; break;
        case SharpnessKernel::K3x3: kernelSize = 3; break;
        case SharpnessKernel::K5x5: kernelSize = 5; break;
        case SharpnessKernel::K7x7: kernelSize = 7; break;
        default: break;
    }
    double value = 0.0;
    //预先转灰
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

/**
* @brief Sobel 清晰度计算（基于梯度幅值的均值/方差）
* @param src 输入图像（支持彩色/灰度，彩色会自动转灰度）
* @param ksize Sobel 核大小（必须是奇数，默认3）
* @return 清晰度值（值越大越清晰）
*/
double SharpnessAnalyzer::computeSobelSharpness(const cv::Mat& mat, int kernelSize, double threshold)
{
    cv::Mat sobelX, sobelY;
    cv::Sobel(mat, sobelX, CV_64F, 1, 0, kernelSize);
    cv::Sobel(mat, sobelY, CV_64F, 0, 1, kernelSize);
    cv::Mat magnitude;
    cv::magnitude(sobelX, sobelY, magnitude);
    double sum = 0;
    for (int i = 0; i < magnitude.rows; i++)
    {
        for (int j = 0; j < magnitude.cols; j++)
        {
            double val = magnitude.at<double>(i, j);
            if (val >= threshold)
                sum += val;
        }
    }
    //cv::Scalar meanMagnitude = cv::mean(magnitude);
    //return meanMagnitude[0];
    sum /= (magnitude.rows * magnitude.cols);
    return sum;
}

/**
* @brief Laplacian 清晰度计算（基于拉普拉斯方差）
* @param src 输入图像（支持彩色/灰度，彩色会自动转灰度）
* @param ksize Laplacian 核大小（必须是奇数，默认3）
* @return 清晰度值（值越大越清晰）
*/
double SharpnessAnalyzer::computeLaplacianSharpness(const cv::Mat& mat, int kernelSize, double threshold)
{
    cv::Mat laplacian;
    cv::Laplacian(mat, laplacian, CV_64F, kernelSize);
    cv::Mat absLap= cv::abs(laplacian);
    double sum = 0.0;
    for (int i = 0; i < absLap.rows; i++)
    {
        for (int j = 0; j < absLap.cols; j++)
        {
            double val = absLap.at<double>(i, j);
            if (val >= threshold)
                sum += val;
        }
    }
    //cv::Scalar mean, stddev;
    //cv::meanStdDev(laplacian, mean, stddev);
    //return stddev[0] * stddev[0];
    sum /= (absLap.rows * absLap.cols);
    return sum;
}

/**
* @brief Brenner 清晰度计算（简单的梯度评价，适用于无噪声图像）
* @param src 输入图像（支持彩色/灰度，彩色会自动转灰度）
* @return 清晰度值（值越大越清晰）
*/
double SharpnessAnalyzer::computeBrennerSharpness(const cv::Mat& mat, int kernelSize, double threshold)
{
    cv::Mat img;
    mat.convertTo(img, CV_32F);
    double brennerValue = 0.0;
    int rows = mat.rows;
    int cols = mat.cols;
    // 遍历图像（行方向，间隔1列计算）
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols - 2; ++j)
        {
            float diff = img.at<float>(i, j + 2) - img.at<float>(i, j);
            if (diff > threshold)
                brennerValue += diff * diff;
        }
    }

    // 归一化（可选，根据需求调整）
    brennerValue /= (rows * (cols - 2));
    return brennerValue;
}

