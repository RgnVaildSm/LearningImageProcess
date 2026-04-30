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
    double value = 0.0;
    AnalyzerParameters currentParams = *getParams();

    if (currentParams.sharpnessByGray)
    {
        
    }
}

