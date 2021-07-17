#ifndef CONFUSIONMATRIX_H
#define CONFUSIONMATRIX_H

#include <QGraphicsItem>
#include <QProcess>
#include <QFileInfo>
#include <QGraphicsSvgItem>
#include <QDir>
#include <trainingresultview.h>
#include "abstractresultgraphics.h"

class ConfusionMatrix : public AbstractResultGraphics {
public:

    ConfusionMatrix(const QString &identifier, const QStringList &classLabels,
                    const QList<double> &values);
    QString valuesToPyText();
    QString labelsToPyText();
    double operator()(int row, int column) const;
    bool operator==(ConfusionMatrix other) const;
    bool operator!=(ConfusionMatrix other) const;

private:
    QStringList m_classLabels;
    qsizetype m_size;
    QList<double> m_values;
    void generateGraphicsInternal(const QString& fullFilePath) override;
    void passResultGraphics(const QString &fullFilePath, TrainingResultView* receiver) override;
};

#endif // CONFUSIONMATRIX_H
