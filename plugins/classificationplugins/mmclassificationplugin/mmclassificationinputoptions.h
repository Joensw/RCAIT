#ifndef MMCLASSIFICATIONINPUTOPTIONS_H
#define MMCLASSIFICATIONINPUTOPTIONS_H

#include <QWidget>

namespace Ui {
class MMClassificationInputOptions;
}

class MMClassificationInputOptions : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int m_max_iters READ getMaxIters WRITE setMaxIters)
    Q_PROPERTY(int m_cuda_device READ getCudaDevice WRITE setCudaDevice)

public:
    explicit MMClassificationInputOptions(QWidget *parent = nullptr);
    ~MMClassificationInputOptions();

    void readInput();

    int getMaxIters();
    void setMaxIters(int numberOfIteration);
    int getCudaDevice();
    void setCudaDevice(int deviceNumber);

private:
    Ui::MMClassificationInputOptions *ui;
    int m_max_iters;
    int m_cuda_device;
};

#endif // MMCLASSIFICATIONINPUTOPTIONS_H
