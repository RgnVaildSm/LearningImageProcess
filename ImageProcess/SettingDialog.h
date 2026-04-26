#pragma once
#include <QDialog>

class QLabel;
class QSpinBox;

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget* parent = nullptr);

    void setCameraInfo(const QString& info);

    int sharpnessStrength() const;

signals:
    void parametersChanged(int newStrength);

private:
    QLabel* m_labelCameraInfo;
    QSpinBox* m_spinStrength;
};