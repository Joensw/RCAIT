#ifndef GENERICGRAPHICSVIEW_H
#define GENERICGRAPHICSVIEW_H

#include <QGraphicsItem>
#include <QWidget>
#include "savableresultswidget.h"

class GenericGraphicsView : public QWidget {
Q_OBJECT

public:
    GenericGraphicsView(SavableResultsWidget *tabWidget, QWidget *parent = nullptr)
            : QWidget(parent), m_tabWidget(tabWidget) {};

    [[nodiscard]] bool isSaved() const;

    void setSaved(bool isSaved);

    [[nodiscard]] const QString &getName() const;

    void setName(const QString &name);

    virtual void setAccuracyCurve(const QSharedPointer<QGraphicsItem> &accuracyCurveImage) {};

    virtual void setConfusionMatrix(const QSharedPointer<QGraphicsItem> &matrixImage) {};

    virtual void setTopAccuraciesGraphics(const QSharedPointer<QGraphicsItem> &topAccuraciesImage) {};

    virtual void setClassificationGraphics(const QSharedPointer<QGraphicsItem> &classificationGraphicsImage) {};

private:
    SavableResultsWidget *m_tabWidget;
    bool m_isSaved = false;
    QString m_name;
};

inline void GenericGraphicsView::setSaved(bool isSaved) {
    m_isSaved = isSaved;
    if (m_tabWidget)
        m_tabWidget->updateSaveButton(this);
}

inline void GenericGraphicsView::setName(const QString &name) {
    m_name = name;
}

inline bool GenericGraphicsView::isSaved() const {
    return m_isSaved;
}

inline const QString &GenericGraphicsView::getName() const {
    return m_name;
}

#endif // GENERICGRAPHICSVIEW_H
