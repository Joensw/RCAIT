#ifndef SAVABLERESULTSWIDGET_H
#define SAVABLERESULTSWIDGET_H

#include <QWidget>
#include <genericgraphicsview.h>

class GenericGraphicsView;

/**
 * @brief This class contains pure virtual methods of saving related functions.
 */
class SavableResultsWidget : public QWidget {
Q_OBJECT

public:
    /**
     * @brief Constructs a SavableResultsWidget
     * @param parent QWidget parent (optional)
     */
    explicit SavableResultsWidget(QWidget *parent = nullptr)
            : QWidget(parent) {}

    /**
     * @brief Update the saved state of a result view tab
     * @param tab tab that changed its state
     */
    virtual void updateSaveState(GenericGraphicsView *tab) = 0;

private:

    /**
     * @brief Saves a given result tab
     * @param view tab to be saved
     */
    virtual void saveResult(GenericGraphicsView *view) = 0;

private slots:

    virtual void slot_updateSaveButton(int index) = 0;

    [[maybe_unused]] virtual void on_pushButton_saveCurrentTab_clicked() = 0;

};

#endif //SAVABLERESULTSWIDGET_H
