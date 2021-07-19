#ifndef CLASSIFICATIONRESULTVIEW_H
#define CLASSIFICATIONRESULTVIEW_H

#include <QWidget>

namespace Ui {
class ClassificationResultView;
}

class ClassificationResultView : public QWidget
{
    Q_OBJECT

public:
    explicit ClassificationResultView(QWidget *parent = nullptr);
    ~ClassificationResultView();

private:
    Ui::ClassificationResultView *ui;
};

#endif // CLASSIFICATIONRESULTVIEW_H
