#ifndef ACCURACYCURVE_H
#define ACCURACYCURVE_H


#include <QGraphicsItem>
#include <trainingresultview.h>
#include "abstractresultgraphics.h"

class AccuracyCurve : public AbstractResultGraphics{
public:
    AccuracyCurve(const QString &directory, const QString &identifier,
                  const QMap<int, QPair<double, double>> &data);

    QPair<double,double> operator[](int epoch) const;
    bool operator==(const AccuracyCurve& other) const;
    bool operator!=(const AccuracyCurve& other) const;

    QMap<int, QPair<double, double>> getData();

private:
    QMap<int, QPair<double, double>> m_data;
    void generateGraphicsInternal(const QString& fullFilePath) override;
    void passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) override;
    QString valuesToPyText();
};

#endif // ACCURACYCURVE_H
