#include "mmclassificationinputoptions.h"
#include "ui_mmclassificationinputoptions.h"

MMClassificationInputOptions::MMClassificationInputOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MMClassificationInputOptions)
{
    ui->setupUi(this);
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

void MMClassificationInputOptions::readInput()
{
    setCudaDevice(ui->spinBox_cudaGpuDevice->value());
    setMaxIters(ui->spinBox_numberIterations->value());
    qDebug() << "read max iters input: " << ui->spinBox_numberIterations->value();
    //qDebug() << "iterations??: " << ui->spinBox_numberIterations->value();
}
