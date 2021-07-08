#ifndef AITRAININGWIDGET_H
#define AITRAININGWIDGET_H

#include <QWidget>

namespace Ui {
class AITrainingWidget;
}

class AITrainingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AITrainingWidget(QWidget *parent = nullptr);
    ~AITrainingWidget();

private:
    Ui::AITrainingWidget *ui;
};

#endif // AITRAININGWIDGET_H
