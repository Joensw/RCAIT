#ifndef LOSSCURVE_H
#define LOSSCURVE_H


#include <QGraphicsItem>

class LossCurve {
public:
    explicit LossCurve(const QMap<int, QPair<double, double>> &data);
    QGraphicsItem * generateLossCurveGraphics(const QString& fileName);
    QString valuesToPyText();

    QPair<double,double> operator[](int epoch) const;
    bool operator==(const LossCurve& other) const;
    bool operator!=(const LossCurve& other) const;
private:

    QMap<int, QPair<double, double>> m_data;

};

#endif // LOSSCURVE_H
