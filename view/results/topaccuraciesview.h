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

    void addTableRow(const QString &identifier, double top1, double top5);

    void removeTableRow(const QString &identifier);

    void setTopAccuraciesGraphics(QGraphicsItem *topAccuraciesImage) override;

    ~TopAccuraciesView();

signals:
    void sig_accuraciesTable_rowRemoved(const QString &identifier);

    void sig_accuraciesTable_rowAdded(const QString &identifier, double top1, double top5);

    void sig_requestTopAccuraciesGraphics(AbstractGraphicsView *receiver);

private slots:
    void on_pushButton_updateGraphics_pressed();

private:
    Ui::TopAccuraciesView *ui;
    QAbstractButton* m_pushButton_updateGraphics;

    void configure_updateGraphicsButton();

    void retranslateUi();
};

#endif // TOPACCURACIESVIEW_H
