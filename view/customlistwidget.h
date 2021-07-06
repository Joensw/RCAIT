#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>

class CustomListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit CustomListWidget(QWidget *parent = nullptr);
    void addItem(const QString &label);
    void addItems(const QStringList &labels);

private slots:
    void updateSelectionIcon(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // CUSTOMLISTWIDGET_H
