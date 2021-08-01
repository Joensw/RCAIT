#ifndef TOPACCURACIESVIEW_H
#define TOPACCURACIESVIEW_H

#include <QWidget>
#include <QMap>
#include <QTableWidgetItem>
#include <QPushButton>
#include "abstractgraphicsview.h"

namespace Ui {
    class TopAccuraciesView;
}

class TopAccuraciesView : public QWidget, public AbstractGraphicsView {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit TopAccuraciesView(QWidget *parent = nullptr);

    void addTopAccuraciesEntry(const QString &identifier, double top1, double top5);

    void removeTopAccuraciesEntry(const QString &identifier);

    void setTopAccuraciesGraphics(QGraphicsItem *topAccuraciesImage) override;

    ~TopAccuraciesView();

signals:

    void sig_normal_requestTopAccuraciesGraphics(AbstractGraphicsView *receiver);

private slots:

    void slot_pushButton_updateGraphics_pressed();

private:
    Ui::TopAccuraciesView *ui;
    QAbstractButton *m_pushButton_updateGraphics;

    void configure_updateGraphicsButton();

    void retranslateUi();
};

#endif // TOPACCURACIESVIEW_H
