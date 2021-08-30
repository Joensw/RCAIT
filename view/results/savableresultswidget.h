#ifndef SAVABLERESULTSWIDGET_H
#define SAVABLERESULTSWIDGET_H

#include <QWidget>
#include "genericgraphicsview.h"

class GenericGraphicsView;

class SavableResultsWidget : public QWidget {
Q_OBJECT

public:
    explicit SavableResultsWidget(QWidget *parent = nullptr)
            : QWidget(parent) {}

    virtual void updateSaveButton(GenericGraphicsView *tab) = 0;

private:

    virtual void saveResult(GenericGraphicsView *view) = 0;

private slots:

    virtual void slot_updateSaveButton(int index) = 0;

    [[maybe_unused]] virtual void on_pushButton_saveCurrentTab_clicked() = 0;

};

#endif //SAVABLERESULTSWIDGET_H
