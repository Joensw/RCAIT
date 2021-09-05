#ifndef CLASSIFICATIONGRAPHICS_H
#define CLASSIFICATIONGRAPHICS_H

#include <QMap>
#include <QGraphicsSvgItem>
#include <QString>
#include <QFileInfo>
#include <QStringBuilder>
#include <mapadapt.h>
#include <genericgraphicsview.h>
#include "genericresultgraphics.h"

class ClassificationGraphics : public GenericResultGraphics {
Q_OBJECT

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

    void passResultGraphics(const QString &fullFilePath, GenericGraphicsView *receiver) override;

    QString labelsToPyText();

    QString valuesToPyText();
};

#endif // CLASSIFICATIONGRAPHICS_H
