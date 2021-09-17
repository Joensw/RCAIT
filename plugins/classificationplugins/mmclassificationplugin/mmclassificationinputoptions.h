#ifndef MMCLASSIFICATIONINPUTOPTIONS_H
#define MMCLASSIFICATIONINPUTOPTIONS_H

#include <QWidget>

namespace Ui {
class MMClassificationInputOptions;
}

/**
 * @brief The MMClassificationInputOptions class makes plugin specific input parameters accessible
 */
class MMClassificationInputOptions : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int m_max_iters READ getMaxIters WRITE setMaxIters)
    Q_PROPERTY(int m_cuda_device READ getCudaDevice WRITE setCudaDevice)

protected:

    /**
     * @brief changeEvent event handler
     *
     * @param event incoming event
     */
    void changeEvent(QEvent *event) override;

public:
    /**
     * @brief MMClassificationInputOptions creates a new instance of this class
     * @param parent the parent widget of this widget
     */
    explicit MMClassificationInputOptions(QWidget *parent = nullptr);
    ~MMClassificationInputOptions();

    /**
     * @brief getMaxIters returns the maximum number of iterations
     * @return the maximum number of iterations beeing a positve integer value
     */
    int getMaxIters();

    /**
     * @brief setMaxIters sets the maximum number of iterations
     * @param numberOfIteration a positive integer value
     */
    void setMaxIters(int numberOfIteration);

    /**
     * @brief getCudaDevice returns the cuda device number
     * @return a natural number specifying the cuda device
     */
    int getCudaDevice();

    /**
     * @brief setCudaDevice sets the cuda device
     * @param deviceNumber a natural number specifying a cuda device
     */
    void setCudaDevice(int deviceNumber);

private:
    Ui::MMClassificationInputOptions *ui;
    int m_max_iters = 10000;
    int m_cuda_device = 0;

private slots:
    void slot_maxItersChanged(int newAmount);
    void slot_cudaDeviceChanged(int newNumber);
};

#endif // MMCLASSIFICATIONINPUTOPTIONS_H
