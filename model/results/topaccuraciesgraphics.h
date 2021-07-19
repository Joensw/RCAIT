#ifndef TOPACCURACIESGRAPHICS_H
#define TOPACCURACIESGRAPHICS_H

#include <QMap>
#include <QGraphicsSvgItem>
#include <abstractgraphicsview.h>
#include "abstractresultgraphics.h"

class TopAccuraciesGraphics : public AbstractResultGraphics {
public:
    explicit TopAccuraciesGraphics(const QString &identifier,
                          const QMap<QString, QPair<double, double>> &data = QMap<QString, QPair<double, double>>());

    void addDataRow(const QString &identifier, double top1, double top5);

    void removeDataRow(const QString &identifier);

    QPair<double, double> operator[](const QString &identifier) const;

    bool operator==(const TopAccuraciesGraphics &other) const;

    bool operator!=(const TopAccuraciesGraphics &other) const;

private:
    QMap<QString, QPair<double, double>> m_data;

    void generateGraphicsInternal(const QString &fullFilePath) override;

    void passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) override;

    QString labelsToPyText();

    QString valuesToPyText();
};

#endif // TOPACCURACIESGRAPHICS_H
