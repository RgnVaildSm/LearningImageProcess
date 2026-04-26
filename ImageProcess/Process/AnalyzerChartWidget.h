#pragma once
#include <qwidget.h>
#include <qchart.h>
#include <qchartview.h>
#include <qlineseries.h>
#include <qvalueaxis.h>

class AnalyzerChartWidget : public QChartView
{
    Q_OBJECT

public:
    explicit AnalyzerChartWidget(QWidget* parent = nullptr);
    ~AnalyzerChartWidget() override = default;

public slots:
    void addSample(double value);
    void clearSamples();

private:
    QLineSeries*    m_series;
    QValueAxis*     m_axisX;
    QValueAxis*     m_axisY;
    qreal           m_x{0};
    int             m_maxPoints{300};
};

