#ifndef CLASSIFICATIONRESULTVIEW_H
#define CLASSIFICATIONRESULTVIEW_H

#include <QWidget>
#include <QMap>
#include <QTableWidgetItem>
#include <QPushButton>
#include "abstractgraphicsview.h"
#include "customtablewidget.h"

namespace Ui {
    class ClassificationResultView;
}

class ClassificationResultView : public QWidget, public AbstractGraphicsView {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit ClassificationResultView(QWidget *parent = nullptr);

    void setClassificationGraphics(const QSharedPointer<QGraphicsItem> &classificationGraphicsImage) override;

    void setClassificationData(const QMap<int, QStringList> &data);

    ~ClassificationResultView() override;

private:
    Ui::ClassificationResultView *ui;
    QSharedPointer<QGraphicsItem> m_classificationGraphics;

    void retranslateUi();
};

#endif // CLASSIFICATIONRESULTVIEW_H
