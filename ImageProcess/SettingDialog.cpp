#include "SettingDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QHBoxLayout>

SettingsDialog::SettingsDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(QStringLiteral("Settings"));
    auto layout = new QVBoxLayout(this);

    m_labelCameraInfo = new QLabel(QStringLiteral("Camera: -"), this);
    layout->addWidget(m_labelCameraInfo);

    auto h = new QWidget(this);
    auto hl = new QHBoxLayout(h);
    hl->setContentsMargins(0,0,0,0);
    hl->addWidget(new QLabel(QStringLiteral("Sharpness kernel strength:"), h));
    m_spinStrength = new QSpinBox(h);
    m_spinStrength->setRange(1, 10);
    m_spinStrength->setValue(1);
    hl->addWidget(m_spinStrength);
    layout->addWidget(h);

    auto buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, [this]() {
        emit parametersChanged(m_spinStrength->value());
        accept();
        });
    connect(buttons, &QDialogButtonBox::rejected, this, &SettingsDialog::reject);
}

void SettingsDialog::setCameraInfo(const QString& info)
{
    m_labelCameraInfo->setText(info);
}

int SettingsDialog::sharpnessStrength() const
{
    return m_spinStrength->value();
}
