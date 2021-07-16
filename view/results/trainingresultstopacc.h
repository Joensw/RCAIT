#ifndef TRAININGRESULTSTOPACC_H
#define TRAININGRESULTSTOPACC_H

#include <QWidget>
#include <QMap>
#include <QTableWidgetItem>

namespace Ui {
    class TrainingResultsTopAcc;
}

class TrainingResultsTopAcc : public QWidget {
Q_OBJECT

public:
    explicit TrainingResultsTopAcc(QWidget *parent = nullptr);

    void addTableRow(const QString &identifier, double top1, double top5);

    void removeTableRow(const QString &identifier);

    ~TrainingResultsTopAcc();

private:
    Ui::TrainingResultsTopAcc *ui;

};

#endif // TRAININGRESULTSTOPACC_H
