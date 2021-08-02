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

    void setClassificationGraphics(QGraphicsItem *classificationGraphicsImage) override;

    void setClassificationData(const QMap<QString, QStringList> &data);

    ~ClassificationResultView();

private:
    Ui::ClassificationResultView *ui;
};

#endif // CLASSIFICATIONRESULTVIEW_H
