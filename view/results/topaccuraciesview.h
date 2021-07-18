#ifndef TOPACCURACIESVIEW_H
#define TOPACCURACIESVIEW_H

#include <QWidget>
#include <QMap>
#include <QTableWidgetItem>

namespace Ui {
    class TopAccuraciesView;
}

class TopAccuraciesView : public QWidget {
Q_OBJECT

public:
    explicit TopAccuraciesView(QWidget *parent = nullptr);

    void addTableRow(const QString &identifier, double top1, double top5);

    void removeTableRow(const QString &identifier);

    ~TopAccuraciesView();

private:
    Ui::TopAccuraciesView *ui;

};

#endif // TOPACCURACIESVIEW_H
