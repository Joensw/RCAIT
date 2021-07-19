#ifndef LOSSCURVE_H
#define LOSSCURVE_H


#include <QGraphicsItem>
#include <trainingresultview.h>
#include "abstractresultgraphics.h"

class LossCurve : public AbstractResultGraphics{
public:
    LossCurve(const QString &identifier, const QMap<int, QPair<double, double>> &data);
    QString valuesToPyText();

    QPair<double,double> operator[](int epoch) const;
    bool operator==(const LossCurve& other) const;
    bool operator!=(const LossCurve& other) const;

private:
    QMap<int, QPair<double, double>> m_data;
    void generateGraphicsInternal(const QString& fullFilePath) override;
    void passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) override;
};

#endif // LOSSCURVE_H
