#ifndef GENERICGRAPHICSVIEW_H
#define GENERICGRAPHICSVIEW_H

#include <QGraphicsItem>
#include <QWidget>
#include "savableresultswidget.h"

class GenericGraphicsView : public QWidget {
Q_OBJECT

public:
    GenericGraphicsView(SavableResultsWidget *tabWidget, QWidget *parent = nullptr);

    [[nodiscard]] bool isSaved() const;

    void setSaved(bool isSaved);

    [[nodiscard]] const QString &getName() const;

    void setName(const QString &name);


    /*
     * Every result will accept some sort of graphics.
     * These here are all available methods over all types of graphics,
     * ready to be overridden and implemented.
     */
    virtual void setAccuracyCurve(const QSharedPointer<QGraphicsItem> &accuracyCurveImage) {};

    virtual void setConfusionMatrix(const QSharedPointer<QGraphicsItem> &matrixImage) {};

    virtual void setTopAccuraciesGraphics(const QSharedPointer<QGraphicsItem> &topAccuraciesImage) {};

    virtual void setClassificationGraphics(const QSharedPointer<QGraphicsItem> &classificationGraphicsImage) {};

private:
    SavableResultsWidget *m_tabWidget;
    bool m_isSaved = false;
    QString m_name;
};

#endif // GENERICGRAPHICSVIEW_H
