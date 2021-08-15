#ifndef CLASSIFICATIONGRAPHICS_H
#define CLASSIFICATIONGRAPHICS_H

#include <QMap>
#include <QGraphicsSvgItem>
#include <abstractgraphicsview.h>
#include "abstractresultgraphics.h"

class ClassificationGraphics : public AbstractResultGraphics {

public:
    ClassificationGraphics(const QString &directory, const QString &identifier,
                           const QMap<QString, QList<double>> &data = {});

    void addDataRow(const QString &identifier, QList<double> &data);

    void removeDataRow(const QString &identifier);

    QList<double> operator[](const QString &identifier) const;

    bool operator==(const ClassificationGraphics &other) const;

    bool operator!=(const ClassificationGraphics &other) const;

private:
    QMap <QString, QList<double>> m_data;

    void generateGraphicsInternal(const QString &fullFilePath) override;

    void passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) override;

    QString labelsToPyText();

    QString valuesToPyText();
};

#endif // CLASSIFICATIONGRAPHICS_H
