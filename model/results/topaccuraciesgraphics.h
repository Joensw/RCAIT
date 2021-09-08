#ifndef TOPACCURACIESGRAPHICS_H
#define TOPACCURACIESGRAPHICS_H

#include <QMap>
#include <QGraphicsSvgItem>
#include <QStringBuilder>
#include <genericgraphicsview.h>
#include "genericresultgraphics.h"

class TopAccuraciesGraphics : public GenericResultGraphics {
Q_OBJECT

public:
    explicit TopAccuraciesGraphics(const QString &directory,
                                   const QList<QPair<QString, QList<double>>> &data = {});

    void addDataRow(const QString &identifier, const QList<double> &data);

    void removeDataRow(const QString &identifier);

    QList<double> operator[](const QString &identifier) const;

    bool operator==(const TopAccuraciesGraphics &other) const;

    bool operator!=(const TopAccuraciesGraphics &other) const;

    [[maybe_unused]] void setData(const QList<QPair<QString, QList<double>>> &mData);

private:
    QList<QPair<QString, QList<double>>> m_data;

    void generateGraphicsInternal(const QString &fullFilePath) override;

    void passResultGraphics(const QString &fullFilePath, GenericGraphicsView *receiver) override;

    QString labelsToPyText();

    QString valuesToPyText();
};

#endif // TOPACCURACIESGRAPHICS_H
