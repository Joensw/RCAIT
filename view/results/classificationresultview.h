#ifndef CLASSIFICATIONRESULTVIEW_H
#define CLASSIFICATIONRESULTVIEW_H

#include <QWidget>
#include <QMap>
#include <QTableWidgetItem>
#include <QPushButton>
#include "abstractgraphicsview.h"

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

    void addTableRow(const QString &identifier, const QList<double>& data);

    void removeTableRow(const QString &identifier);

    void setClassificationGraphics(QGraphicsItem *classificationGraphicsImage) override;

    ~ClassificationResultView();

signals:
    void sig_classificationResultTable_rowRemoved(const ClassificationResultView* view, const QString &identifier);

    void sig_classificationResultTable_rowAdded(const ClassificationResultView* view, const QString &identifier, const QList<double>& data);

    void sig_requestClassificationResultGraphics(AbstractGraphicsView *receiver);

private slots:
    void slot_pushButton_updateGraphics_pressed();

private:
    Ui::ClassificationResultView *ui;
    QAbstractButton* m_pushButton_updateGraphics;

    void configure_updateGraphicsButton();

    void retranslateUi();

    void dummyFunctionTest();
};

#endif // CLASSIFICATIONRESULTVIEW_H
