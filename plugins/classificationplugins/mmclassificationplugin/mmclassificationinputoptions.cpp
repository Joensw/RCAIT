#include "mmclassificationinputoptions.h"
#include "ui_mmclassificationinputoptions.h"

MMClassificationInputOptions::MMClassificationInputOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MMClassificationInputOptions)
{
    ui->setupUi(this);
    connect(ui->spinBox_cudaGpuDevice, QOverload<int>::of(&QSpinBox::valueChanged), this, &MMClassificationInputOptions::slot_maxItersChanged);
    connect(ui->spinBox_numberIterations, QOverload<int>::of(&QSpinBox::valueChanged), this, &MMClassificationInputOptions::slot_cudaDeviceChanged);
}

MMClassificationInputOptions::~MMClassificationInputOptions()
{
    delete ui;
}

int MMClassificationInputOptions::getMaxIters()
{
    return m_max_iters;
}

void MMClassificationInputOptions::setMaxIters(int numberOfIteration)
{
    m_max_iters = numberOfIteration;
}

int MMClassificationInputOptions::getCudaDevice()
{
    return m_cuda_device;
}

void MMClassificationInputOptions::setCudaDevice(int deviceNumber)
{
    m_cuda_device = deviceNumber;
}

void MMClassificationInputOptions::slot_maxItersChanged(int newAmount)
{
    setMaxIters(newAmount);
}

void MMClassificationInputOptions::slot_cudaDeviceChanged(int newNumber)
{
    setCudaDevice(newNumber);
}
