#ifndef TRAININGRESULTVIEW_H
#define TRAININGRESULTVIEW_H

#include <QWidget>

namespace Ui {
class TrainingResultView;
}

class TrainingResultView : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingResultView(QWidget *parent = nullptr);
    ~TrainingResultView();

private:
    Ui::TrainingResultView *ui;
};

#endif // TRAININGRESULTVIEW_H
