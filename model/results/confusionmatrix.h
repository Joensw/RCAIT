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

    ConfusionMatrix(const QString &directory, const QString &identifier,
                    const QStringList &classLabels, const QList<int> &values);

    double operator()(int row, int column) const;
    bool operator==(ConfusionMatrix other) const;
    bool operator!=(ConfusionMatrix other) const;

    //needed for serialisation
    QStringList getClassLabels();
    QList<int> getValues();
private:
    QStringList m_classLabels;
    qsizetype m_size;
    QList<int> m_values;
    void generateGraphicsInternal(const QString& fullFilePath) override;
    void passResultGraphics(const QString &fullFilePath, AbstractGraphicsView *receiver) override;

    QString valuesToPyText();
    QString labelsToPyText();
};

#endif // CONFUSIONMATRIX_H
