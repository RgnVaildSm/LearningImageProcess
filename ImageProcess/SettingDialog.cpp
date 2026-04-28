#include "SettingDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QHBoxLayout>

SettingsDialog::SettingsDialog(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    //类型注册
    qRegisterMetaType<AnalyzerParameters>("AnalyzerParameters");
    //参数初始化 //例如从配置文件加载默认值，或者根据当前相机状态设置初始值
    ParameterFeaturesMatchInit();
    ParameterDetectInit();
    ParameterSharpnessInit();

}

void SettingsDialog::setCameraName(const QString& name)
{
    ui.lineEditName->setText(name);
}

void SettingsDialog::setCameraSerialNumber(const QString& sn)
{
    ui.lineEditSerialNumber->setText(sn);
}

void SettingsDialog::setWidgetEnabled(bool enabled)
{
    for (auto& widget : ui.tabWidget->findChildren<QWidget*>())
    {
        if (widget)
            widget->setEnabled(enabled);
    }
}

bool SettingsDialog::checkParametersValid(const AnalyzerParameters& param) const
{
    bool isValid = true;
    // 锐度参数检查
    
    return isValid;
}

void SettingsDialog::ParameterSharpnessInit()
{
    ui.cmBoxSharpnessAlgorithm->clear();
    ui.cmBoxSharpnessAlgorithm->addItem("Sobel");
    ui.cmBoxSharpnessAlgorithm->addItem("Laplacian");
    ui.cmBoxSharpnessAlgorithm->addItem("Brenner");
    ui.cmBoxSharpnessKernel->clear();
    ui.cmBoxSharpnessKernel->addItem("3x3");
    ui.cmBoxSharpnessKernel->addItem("5x5");
    ui.cmBoxSharpnessKernel->addItem("7x7");
    ui.cmBoxSharpnessKernel->addItem("9x9");
    ui.lineEditSharpnessThreshold->setText("100");
    ui.checkBoxSharpnessByGray->setChecked(true);

    ui.cmBoxSharpnessAlgorithm->setCurrentIndex(0);
    ui.cmBoxSharpnessKernel->setCurrentIndex(0);
}

void SettingsDialog::ParameterFeaturesMatchInit()
{
    ui.cmBoxFMAlgorithm->clear();
    ui.cmBoxFMAlgorithm->addItem("ORB");
    ui.cmBoxFMAlgorithm->addItem("SIFT");
    ui.cmBoxFMAlgorithm->addItem("SURF");
    ui.cmBoxFMMatch->clear();
    ui.cmBoxFMMatch->addItem("Brute-Force");
    ui.cmBoxFMMatch->addItem("FLANN");
    ui.lineEditFMFeatureNum->setText("500");
    ui.lineEditFMMatchThreshold->setText("0.75");

    ui.cmBoxFMAlgorithm->setCurrentIndex(0);
    ui.cmBoxFMMatch->setCurrentIndex(0);
}

void SettingsDialog::ParameterDetectInit()
{
    ui.cmBoxDetectAlgorithm->clear();
    ui.cmBoxDetectAlgorithm->addItem("CSRT");
    ui.cmBoxDetectAlgorithm->addItem("KCF");
    ui.cmBoxDetectAlgorithm->addItem("MOSSE");
    ui.lineEditDetectThreshold->setText("0.5");
    //ui.lineEditDetectThreshold2->setText("200");
    ui.cmBoxDetectAlgorithm->setCurrentIndex(0);
}

void SettingsDialog::accept()
{
    for (auto& widget : ui.tabWidget->findChildren<QWidget*>())
    {
        if (widget && !widget->isEnabled())
        {
            QDialog::accept();
            return;
        }
    }
    AnalyzerParameters newParams;
    //从 UI 获取参数值并填充 newParams
    newParams.sharpnessAlgorithm    = static_cast<AnalyzerParameters::SharpnessAlgorithm>(ui.cmBoxSharpnessAlgorithm->currentIndex());
    newParams.sharpnessKernel       = static_cast<AnalyzerParameters::SharpnessKernel>(ui.cmBoxSharpnessKernel->currentIndex());
    newParams.sharpnessThreshold    = ui.lineEditSharpnessThreshold->text().toInt();
    newParams.sharpnessByGray       = ui.checkBoxSharpnessByGray->isChecked();
    newParams.fmAlgorithm           = static_cast<AnalyzerParameters::FMAlgorithm>(ui.cmBoxFMAlgorithm->currentIndex());
    newParams.fmMatchMethod         = static_cast<AnalyzerParameters::MatchMethod>(ui.cmBoxFMMatch->currentIndex());
    newParams.fmFeatureNum          = ui.lineEditFMFeatureNum->text().toInt();
    newParams.fmMatchThreshold      = ui.lineEditFMMatchThreshold->text().toDouble();
    newParams.detectAlgorithm       = static_cast<AnalyzerParameters::DetectAlgorithm>(ui.cmBoxDetectAlgorithm->currentIndex());
    newParams.detectThreshold       = ui.lineEditDetectThreshold->text().toDouble();
    if (checkParametersValid(newParams) && newParams != m_parameters) 
    {
        m_parameters = newParams;
        emit parametersChanged(m_parameters);
    }
    QDialog::accept();
}
