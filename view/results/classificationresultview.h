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

class ClassificationResultView : public GenericGraphicsView {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit ClassificationResultView(SavableResultsWidget *tabWidget, QWidget *parent = nullptr);

    void setClassificationGraphics(const QSharedPointer<QGraphicsItem> &classificationGraphicsImage) override;

    void setClassificationData(const QMap<int, QStringList> &data);

    [[maybe_unused]] [[nodiscard]] const QSharedPointer<QGraphicsItem> &getClassificationGraphics() const;

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
