#ifndef CLASSIFICATIONRESULTVIEW_H
#define CLASSIFICATIONRESULTVIEW_H

#include <QWidget>
#include <QMap>
#include <QTableWidgetItem>
#include <QPushButton>
#include "genericgraphicsview.h"
#include "customtablewidget.h"

namespace Ui {
    class ClassificationResultView;
}

/**
 * @brief View wrapper for ClassificationResult objects.
 * This is used as tabs in a ClassificationResultsWidget
 */
class ClassificationResultView : public GenericGraphicsView {
Q_OBJECT

protected:
    /**
     * @brief this event is called, when a new translator is loaded or the system language is changed
     */
    void changeEvent(QEvent *) override;

public:
    /**
     * @brief Constructs a ClassificationResultView
     * @param tabWidget TabWidget parent which will hold this object
     * @param parent QWidget parent (optional)
     */
    explicit ClassificationResultView(SavableResultsWidget *tabWidget, QWidget *parent = nullptr);

    /**
     * @brief Set the classification graphics to be displayed
     * @param classificationGraphicsImage image to be displayed, passed via QSharedPointer
     */
    void setClassificationGraphics(const QSharedPointer<QGraphicsItem> &classificationGraphicsImage) override;

    /**
     * @brief Sets the classification data shown in a table
     * @param data map consists of an image index and a list of values as strings
     */
    void setClassificationData(const QMap<int, QStringList> &data);

    /**
     * @brief Get the current classification graphics
     * @return QSharedPointer pointing to the graphics
     */
    [[maybe_unused]] [[nodiscard]] const QSharedPointer<QGraphicsItem> &getClassificationGraphics() const;

    /**
     * @brief Destructor for this class.
     */
    ~ClassificationResultView() override;

private:
    static constexpr auto CLASSIFICATION_GRAPHICS_SCALING_FACTOR = 0.6;
    static constexpr auto TABLE_COLUMN_CODE = 2;
    static constexpr auto CONFIDENCE_HEADER = QT_TR_NOOP("Confidence");
    static constexpr auto LABEL_HEADER = QT_TR_NOOP("Label");

    Ui::ClassificationResultView *ui;
    QSharedPointer<QGraphicsItem> m_classificationGraphics;
    QScopedPointer<QGraphicsScene> m_classificationScene;

    void retranslateUi();
};

#endif // CLASSIFICATIONRESULTVIEW_H
