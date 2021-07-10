#ifndef AUTOMATIONWIDGET_H
#define AUTOMATIONWIDGET_H

#include <QWidget>

namespace Ui {
class AutomationWidget;
}

class AutomationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AutomationWidget(QWidget *parent = nullptr);
    ~AutomationWidget();

private:
    Ui::AutomationWidget *ui;
};

#endif // AUTOMATIONWIDGET_H
