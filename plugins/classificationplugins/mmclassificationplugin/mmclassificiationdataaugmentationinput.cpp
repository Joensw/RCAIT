#include "mmclassificiationdataaugmentationinput.h"
#include "ui_mmclassificiationdataaugmentationinput.h"

MMClassificiationDataAugmentationInput::MMClassificiationDataAugmentationInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MMClassificiationDataAugmentationInput)
{
    ui->setupUi(this);
}

MMClassificiationDataAugmentationInput::~MMClassificiationDataAugmentationInput()
{
    delete ui;
}

void MMClassificiationDataAugmentationInput::readDataAugmentationInput() {
    qDebug() << "haken: " << ui->checkBox_albuTransformType->isChecked();


    if (ui->checkBox_albuTransformType->isChecked()) {
        setAlbuTransformType(ui->comboBox_albuTransformType->currentText());
    } else {
        setAlbuTransformType("");
    }
    if (ui->checkBox_randomResizedCropSize->isChecked()) {
        setRandomResizedCropSize(ui->spinBox_resizedCropSize->value());
    } else {
        setRandomResizedCropSize(0);
    }
    if (ui->checkBox_randomFlipProbabilityAndDirection->isChecked()) {
        setRandomFlipProb(ui->doubleSpinBox_randomFlipProbability->value());
        setRandomFlipDirection(ui->comboBox_randomFlipDirection->currentText());
    } else {
        setRandomFlipProb(0);
        setRandomFlipDirection("");
    }
    if (ui->checkBox_randomErasing->isChecked()) {
        setRandomErasing(true);
    } else {
        setRandomErasing(false);
    }
    if (ui->checkBox_resize->isChecked()) {
        setResize(ui->spinBox_resize->value());
    } else {
        setResize(0);
    }
    if (ui->checkBox_centerCropSize->isChecked()) {
        setCenterCropSize(ui->spinBox_centerCropSize->value());
    } else {
        setCenterCropSize(0);
    }
}

QString MMClassificiationDataAugmentationInput::getAlbuTransformType()
{
    return m_albu_transform_type;
}

void MMClassificiationDataAugmentationInput::setAlbuTransformType(QString type)
{
    m_albu_transform_type = type;
}

int MMClassificiationDataAugmentationInput::getRandomResizedCropSize()
{
    return m_random_resized_crop_size;
}

void MMClassificiationDataAugmentationInput::setRandomResizedCropSize(int size)
{
    m_random_resized_crop_size = size;
}

double MMClassificiationDataAugmentationInput::getRandomFlipProb()
{
    return m_random_flip_prob;
}

void MMClassificiationDataAugmentationInput::setRandomFlipProb(double probability)
{
    m_random_flip_prob = probability;
}

QString MMClassificiationDataAugmentationInput::getRandomFlipDirection()
{
    return m_random_flip_direction;
}

void MMClassificiationDataAugmentationInput::setRandomFlipDirection(QString direction)
{
    m_random_flip_direction = direction;
}

bool MMClassificiationDataAugmentationInput::getRandomErasing()
{
    return m_randomErasing;
}

void MMClassificiationDataAugmentationInput::setRandomErasing(bool execute)
{
    m_randomErasing = execute;
}

int MMClassificiationDataAugmentationInput::getResize()
{
    return m_resize;
}

void MMClassificiationDataAugmentationInput::setResize(int size)
{
    m_resize = size;
}

int MMClassificiationDataAugmentationInput::getCenterCropSize()
{
    return m_center_crop_size;
}

void MMClassificiationDataAugmentationInput::setCenterCropSize(int size)
{
    m_center_crop_size = size;
}
