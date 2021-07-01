#ifndef INPUTIMAGESWIDGET_H
#define INPUTIMAGESWIDGET_H

#include <QWidget>

namespace Ui {
class InputImagesWidget;
}

class InputImagesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InputImagesWidget(QWidget *parent = nullptr);
    ~InputImagesWidget();

signals:
    void sig_browse();
    void sig_startClassify(QString path);
    void sig_abortClassify();

public slots:
    void slot_loaded(QString path);
    void slot_progress(int progress);

private:
    Ui::InputImagesWidget *ui;
    QString path;
};

#endif // INPUTIMAGESWIDGET_H
