#ifndef INPUTIMAGESWIDGET_H
#define INPUTIMAGESWIDGET_H

#include <QDir>
#include <QWidget>
#include <QFileDialog>

namespace Ui {
class InputImagesWidget;
}

/**
 * @brief The InputImagesWidget class is the user interface for classifying images.
 */
class InputImagesWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief InputImagesWidget contructs a new InputImagesWidget.
     *
     * @param parent Optional parent widget.
     */
    explicit InputImagesWidget(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~InputImagesWidget() override;

signals:

    /**
     * @brief sig_startClassify is emitted when user wants to start classification.
     *
     * @param path Path to folder containing the images.
     */
    void sig_startClassify(QString path);

    /**
     * @brief sig_abortClassify is emitted when user wants to abort classification.
     *
     */
    void sig_abortClassify();

public slots:

    /**
     * @brief slot_progress is used to receive progress. Reported progress is used for progressbar.
     *
     * @param progress Number representing progress in percent.
     */
    void slot_progress(int progress);

protected:

    /**
     * @brief changeEvent event handler
     *
     * @param event incoming event
     */
    void changeEvent(QEvent *event) override;

private slots:
    [[maybe_unused]] void on_selectFolderButton_clicked();

    [[maybe_unused]] void on_classifyButton_clicked();



private:
    static constexpr auto DIALOG_CAPTION = QT_TR_NOOP("Select image directory");

    Ui::InputImagesWidget *ui;
    QString path;

};

#endif // INPUTIMAGESWIDGET_H
