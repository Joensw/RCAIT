#ifndef TOPACCURACIESGRAPHICS_H
#define TOPACCURACIESGRAPHICS_H

#include <QMap>
#include <QGraphicsSvgItem>
#include <abstractgraphicsview.h>
#include "abstractresultgraphics.h"

class TopAccuraciesGraphics : public AbstractResultGraphics {
public:
    explicit TopAccuraciesGraphics(const QString &identifier = QString(),
                                   const QList<QPair<QString, QList<double>>> &data = QList<QPair<QString, QList<double>>>());

    void addDataRow(const QString &identifier, const QList<double> &data);

    void removeDataRow(const QString &identifier);

    QList<double> operator[] (const QString &identifier) const;

    bool operator==(const TopAccuraciesGraphics &other) const;

    bool operator!=(const TopAccuraciesGraphics &other) const;

    void setData(const QList<QPair<QString, QList<double>>> &mData);

private:
    QList<QPair<QString, QList<double>>> m_data;

    void generateGraphicsInternal(const QString &fullFilePath) override;

    void passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) override;

    QString labelsToPyText();

    QString valuesToPyText();
};

#endif // TOPACCURACIESGRAPHICS_H
