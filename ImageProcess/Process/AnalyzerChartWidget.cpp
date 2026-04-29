#include "AnalyzerChartWidget.h"
#include <qlayout.h>

AnalyzerChartWidget::AnalyzerChartWidget(QWidget* parent)
    : QChartView(new QChart(), parent)
{
    m_series = new QLineSeries();
    chart()->addSeries(m_series);

    m_axisX = new QValueAxis();
    m_axisX->setLabelsVisible(false);
    m_axisX->setRange(0, m_maxPoints);
    chart()->addAxis(m_axisX, Qt::AlignBottom);
    m_series->attachAxis(m_axisX);

    m_axisY = new QValueAxis();
    m_axisY->setRange(0, 100);
    chart()->addAxis(m_axisY, Qt::AlignLeft);
    m_series->attachAxis(m_axisY);

    chart()->legend()->hide();
    //chart()->setTitle("Analyzer Over Time");
    setRenderHints(QPainter::Antialiasing);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumHeight(200);
}

void AnalyzerChartWidget::addSample(double value)
{
    m_series->append(m_x, value);
    ++m_x;
    if (m_series->count() > m_maxPoints)
    {
        int removeCount = m_series->count() - m_maxPoints;
        m_series->removePoints(0, removeCount);
        m_axisX->setRange(m_x - m_maxPoints, m_x);
    }
    else
    {
        m_axisX->setRange(0, qMax<int>(m_maxPoints, int(m_x)));
    }
    auto points = m_series->pointsVector();
    double minV = std::numeric_limits<double>::infinity();
    double maxV = -std::numeric_limits<double>::infinity();
    for (const QPointF &p : points) 
    {
        minV = qMin(minV, p.y());
        maxV = qMax(maxV, p.y());
    }
    if (minV == std::numeric_limits<double>::infinity()) {
        minV = 0; maxV = 1;
    }
    if (qFuzzyCompare(minV, maxV)) maxV = minV + 1.0;
    m_axisY->setRange(minV, maxV * 1.1);

    chart()->update();
}

void AnalyzerChartWidget::clearSamples()
{
    m_series->clear();
    m_x = 0;
    m_axisX->setRange(0, m_maxPoints);
    m_axisY->setRange(0, 100);
    chart()->update();
}
