#ifndef CONFUSIONMATRIX_H
#define CONFUSIONMATRIX_H

#include <QGraphicsItem>
#include <QProcess>
#include <QFileInfo>
#include <QGraphicsSvgItem>
#include <QDir>

class ConfusionMatrix{
public:

    ConfusionMatrix(const QStringList& classLabels, const QList<double>& values);
    QGraphicsItem * generateConfusionMatrixGraphics(const QString& fileName);
    QString valuesToPyText();
    QString labelsToPyText();

    double operator()(int row, int column) const;
    bool operator==(ConfusionMatrix other) const;
    bool operator!=(ConfusionMatrix other) const;
private:
    QStringList m_classLabels;
    qsizetype m_size;
    QList<double> m_values;
};

#endif // CONFUSIONMATRIX_H
