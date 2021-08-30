#ifndef TOPACCURACIESVIEW_H
#define TOPACCURACIESVIEW_H

#include <QWidget>
#include <QMap>
#include <QTableWidgetItem>
#include <QPushButton>
#include "genericgraphicsview.h"

namespace Ui {
    class TopAccuraciesView;
}

class TopAccuraciesView : public GenericGraphicsView {
Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit TopAccuraciesView(SavableResultsWidget *tabWidget, QWidget *parent = nullptr);

    void addTopAccuraciesEntry(const QString &identifier, double top1, double top5);

    void removeTopAccuraciesEntry(const QString &identifier);

    void setTopAccuraciesGraphics(const QSharedPointer<QGraphicsItem> &topAccuraciesImage) override;

    [[nodiscard]] const QSharedPointer<QGraphicsItem> &getTopAccuraciesImage() const;

    ~TopAccuraciesView() override;

signals:

    void sig_normal_requestTopAccuraciesGraphics(GenericGraphicsView *receiver);

private slots:

    void slot_pushButton_updateGraphics_clicked();

private:
    Ui::TopAccuraciesView *ui;
    QAbstractButton *m_pushButton_updateGraphics;

    QSharedPointer<QGraphicsItem> m_topAccuraciesImage;

    void configure_updateGraphicsButton();

    void retranslateUi();
};

#endif // TOPACCURACIESVIEW_H
