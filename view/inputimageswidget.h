#ifndef INPUTIMAGESWIDGET_H
#define INPUTIMAGESWIDGET_H

#include <QDir>
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

protected:
    void changeEvent(QEvent *event);

private slots:
    void on_selectFolderButton_clicked();

    void on_classifyButton_clicked();
    
    void on_cancelButton_clicked();

private:
    Ui::InputImagesWidget *ui;
    QString path;
    void retranslateUi();
};

#endif // INPUTIMAGESWIDGET_H
