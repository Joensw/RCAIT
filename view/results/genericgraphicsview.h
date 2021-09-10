#ifndef GENERICGRAPHICSVIEW_H
#define GENERICGRAPHICSVIEW_H

#include <QGraphicsItem>
#include <QWidget>
#include "savableresultswidget.h"

/**
 * @brief This class is a superclass of all specialized result views.
 * It contains common attributes and methods.
 */
class GenericGraphicsView : public QWidget {
Q_OBJECT

public:
    /**
     * @brief Constructs a GenericGraphicsView
     * @param tabWidget TabWidget parent which will hold this object
     * @param parent QWidget parent (optional)
     */
    GenericGraphicsView(SavableResultsWidget *tabWidget, QWidget *parent = nullptr);

    /**
     * @brief Get the saved state of the result view.
     * @return saved or not
     */
    [[nodiscard]] bool isSaved() const;

    /**
     * @brief Set the saved state of the result view
     * @param isSaved new saved state
     */
    void setSaved(bool isSaved);

    /**
     * @brief Get the name of this result view
     * @return QString name
     */
    [[nodiscard]] const QString &getName() const;

    /**
     * @brief Set the name of this result view
     * @param name new name to be set
     */
    void setName(const QString &name);


    /*
     * Every result will accept some sort of graphics.
     * These here are all available methods over all types of graphics,
     * ready to be overridden and implemented.
     */

    /**
     * @brief Sets the accuracy curve if supported
     * @param accuracyCurveImage QSharedPointer to the accuracy curve image
     */
    virtual void setAccuracyCurve(const QSharedPointer<QGraphicsItem> &accuracyCurveImage) {};

    /**
     * @brief Sets the confusion matrix image if supported
     * @param matrixImage QSharedPointer to the confusion matrix image
     */
    virtual void setConfusionMatrix(const QSharedPointer<QGraphicsItem> &matrixImage) {};

    /**
     * @brief Sets the top accuracies image if supported
     * @param topAccuraciesImage QSharedPointer to the top accuracies image
     */
    virtual void setTopAccuraciesGraphics(const QSharedPointer<QGraphicsItem> &topAccuraciesImage) {};

    /**
     * @brief Sets the classification graphics image if supported
     * @param classificationGraphicsImage QSharedPointer to the classification graphics image
     */
    virtual void setClassificationGraphics(const QSharedPointer<QGraphicsItem> &classificationGraphicsImage) {};

private:
    SavableResultsWidget *m_tabWidget;
    bool m_isSaved = false;
    QString m_name;
};

#endif // GENERICGRAPHICSVIEW_H
