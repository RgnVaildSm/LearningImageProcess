#pragma once
#include "ui_SettingsDialog.h"
#include <QDialog>

//参数结构体，方便在不同组件间传递设置参数
struct AnalyzerParameters{
    // 锐度计算
    enum class SharpnessAlgorithm {
        Sobel,
        Laplacian,
        Brenner
    };
    enum class SharpnessKernel {
        K3x3,
        K5x5,
        K7x7,
        K9x9
    };
    SharpnessAlgorithm  sharpnessAlgorithm;     //计算方式
    SharpnessKernel     sharpnessKernel;        //卷积核大小
    int                 sharpnessThreshold;     //锐度阈值
    bool                sharpnessByGray;        //是否先转灰度图
    // 特征点匹配
    enum class FMAlgorithm {
        ORB,
        SIFT,
        SURF
    };
    enum class MatchMethod {
        BruteForce,
        FLANN
    };
    FMAlgorithm     fmAlgorithm;            //特征点算法
    MatchMethod     fmMatchMethod;          //匹配方式
    int             fmFeatureNum;           //提取特征点数量
    double          fmMatchThreshold;       //匹配阈值
    // 追踪检测
    enum class DetectAlgorithm {
        BackgroundSubtraction,
        FrameDifference,
        OpticalFlow
    };
    DetectAlgorithm  detectAlgorithm;         //检测算法
    double           detectThreshold;         //检测阈值

    bool operator==(const AnalyzerParameters& other) const {
        return sharpnessAlgorithm   == other.sharpnessAlgorithm &&
               sharpnessKernel      == other.sharpnessKernel &&
               sharpnessThreshold   == other.sharpnessThreshold &&
               sharpnessByGray      == other.sharpnessByGray &&
               fmAlgorithm          == other.fmAlgorithm &&
               fmMatchMethod        == other.fmMatchMethod &&
               fmFeatureNum         == other.fmFeatureNum &&
               fmMatchThreshold     == other.fmMatchThreshold &&
               detectAlgorithm      == other.detectAlgorithm &&
               detectThreshold      == other.detectThreshold;
    }
    bool operator!=(const AnalyzerParameters& other) const {
        return !(*this == other);
    }
    AnalyzerParameters()
        : sharpnessAlgorithm(SharpnessAlgorithm::Sobel)
        , sharpnessKernel(SharpnessKernel::K3x3)
        , sharpnessThreshold(5)
        , sharpnessByGray(true)
        , fmAlgorithm(FMAlgorithm::ORB)
        , fmMatchMethod(MatchMethod::BruteForce)
        , fmFeatureNum(500)
        , fmMatchThreshold(0.75)
        , detectAlgorithm(DetectAlgorithm::BackgroundSubtraction)
        , detectThreshold(0.5)
    {
    }
    AnalyzerParameters(const AnalyzerParameters& other) = default;
    AnalyzerParameters& operator=(const AnalyzerParameters& other) = default;
};
Q_DECLARE_METATYPE(AnalyzerParameters)

class QLabel;
class QSpinBox;

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget* parent = nullptr);
    void setCameraName(const QString& name);
    void setCameraSerialNumber(const QString& sn);
    void setWidgetEnabled(int index, bool enabled);
    AnalyzerParameters getParameters() const { return m_parameters; }
    bool checkParametersValid(const AnalyzerParameters& param) const;

protected:
    void ParameterSharpnessInit();
    void ParameterFeaturesMatchInit();
    void ParameterDetectInit();

    void accept() override;

signals:
    void parametersChanged(const AnalyzerParameters& newParameters);


private:
    Ui::SettingsDialog  ui;
    AnalyzerParameters  m_parameters;
};