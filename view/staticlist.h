#ifndef STATICLIST_H
#define STATICLIST_H

#include <QWidget>

namespace Ui {
class StaticList;
}

class StaticList : public QWidget
{
    Q_OBJECT

public:
    explicit StaticList(QWidget *parent = nullptr);
    ~StaticList();

private:
    Ui::StaticList *ui;
};

#endif // STATICLIST_H
