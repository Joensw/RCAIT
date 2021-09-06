#ifndef ACCURACYCURVE_H
#define ACCURACYCURVE_H


#include <QGraphicsItem>
#include <QFileInfo>
#include <QGraphicsSvgItem>
#include <QProcess>
#include <QStringBuilder>
#include <mapadapt.h>
#include <trainingresultview.h>
#include "genericresultgraphics.h"

class AccuracyCurve : public GenericResultGraphics {
Q_OBJECT

public:
    AccuracyCurve(const QString &directory, const QString &identifier,
                  const QMap<int, QPair<double, double>> &data);

    QPair<double, double> operator[](int iteration) const;

    bool operator==(const AccuracyCurve &other) const;

    bool operator!=(const AccuracyCurve &other) const;

    [[maybe_unused]] QMap<int, QPair<double, double>> getData();

private:
    QMap<int, QPair<double, double>> m_data;

    void generateGraphicsInternal(const QString &fullFilePath) override;

    void passResultGraphics(const QString &fullFilePath, GenericGraphicsView *receiver) override;

    QString valuesToPyText();
};

#endif // ACCURACYCURVE_H
