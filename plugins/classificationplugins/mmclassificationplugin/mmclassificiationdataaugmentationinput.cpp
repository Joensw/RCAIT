#include "mmclassificiationdataaugmentationinput.h"
#include "ui_mmclassificiationdataaugmentationinput.h"

MMClassificiationDataAugmentationInput::MMClassificiationDataAugmentationInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MMClassificiationDataAugmentationInput)
{
    ui->setupUi(this);
    connectCheckboxes();
    connectInputElements();
}

void MMClassificiationDataAugmentationInput::connectCheckboxes()
{
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificiationDataAugmentationInput::slot_albuTransformChecked);
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificiationDataAugmentationInput::slot_randomResizedCropSizeChecked);
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificiationDataAugmentationInput::slot_randomFlipProbAndDirectionChecked);
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificiationDataAugmentationInput::slot_randomErasingChecked);
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificiationDataAugmentationInput::slot_resizeChecked);
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificiationDataAugmentationInput::slot_centerCropSizeChecked);
}

void MMClassificiationDataAugmentationInput::connectInputElements()
{
    connect(ui->comboBox_albuTransformType, &QComboBox::currentTextChanged, this, &MMClassificiationDataAugmentationInput::slot_albuTransformChanged);
    connect(ui->spinBox_resizedCropSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &MMClassificiationDataAugmentationInput::slot_randomResizedCropSizeChanged);
    connect(ui->doubleSpinBox_randomFlipProbability, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MMClassificiationDataAugmentationInput::slot_randomFlipProbChanged);
    connect(ui->comboBox_randomFlipDirection, &QComboBox::currentTextChanged, this, &MMClassificiationDataAugmentationInput::slot_randomFlipDirectionChanged);
    connect(ui->spinBox_resize, QOverload<int>::of(&QSpinBox::valueChanged), this, &MMClassificiationDataAugmentationInput::slot_resizeChanged);
    connect(ui->spinBox_centerCropSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &MMClassificiationDataAugmentationInput::slot_centerCropSizeChanged);
}

MMClassificiationDataAugmentationInput::~MMClassificiationDataAugmentationInput()
{
    delete ui;
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

void MMClassificiationDataAugmentationInput::slot_albuTransformChecked(bool isChecked)
{
    if (isChecked) {
        setAlbuTransformType(ui->comboBox_albuTransformType->currentText());
    } else {
        setAlbuTransformType("");
    }
}

void MMClassificiationDataAugmentationInput::slot_randomResizedCropSizeChecked(bool isChecked)
{
    if (isChecked) {
        setRandomResizedCropSize(ui->spinBox_resizedCropSize->value());
    } else {
        setRandomResizedCropSize(0);
    }
}

void MMClassificiationDataAugmentationInput::slot_randomFlipProbAndDirectionChecked(bool isChecked)
{
    if (isChecked) {
        setRandomFlipProb(ui->doubleSpinBox_randomFlipProbability->value());
        setRandomFlipDirection(ui->comboBox_randomFlipDirection->currentText());
    } else {
        setRandomFlipProb(0);
        setRandomFlipDirection("");
    }
}

void MMClassificiationDataAugmentationInput::slot_randomErasingChecked(bool isChecked)
{
    if (isChecked) {
        setRandomErasing(true);
    } else {
        setRandomErasing(false);
    }
}

void MMClassificiationDataAugmentationInput::slot_resizeChecked(bool isChecked)
{
    if (isChecked) {
        setResize(ui->spinBox_resize->value());
    } else {
        setResize(0);
    }
}

void MMClassificiationDataAugmentationInput::slot_centerCropSizeChecked(bool isChecked)
{
    if (isChecked) {
        setCenterCropSize(ui->spinBox_centerCropSize->value());
    } else {
        setCenterCropSize(0);
    }
}

void MMClassificiationDataAugmentationInput::slot_albuTransformChanged(QString type)
{
    setAlbuTransformType(type);
}

void MMClassificiationDataAugmentationInput::slot_randomResizedCropSizeChanged(int size)
{
    setRandomResizedCropSize(size);
}

void MMClassificiationDataAugmentationInput::slot_randomFlipProbChanged(double probability)
{
    setRandomFlipProb(probability);
}

void MMClassificiationDataAugmentationInput::slot_randomFlipDirectionChanged(QString direction)
{
    setRandomFlipDirection(direction);
}

void MMClassificiationDataAugmentationInput::slot_resizeChanged(int size)
{
    setResize(size);
}

void MMClassificiationDataAugmentationInput::slot_centerCropSizeChanged(int size)
{
    setCenterCropSize(size);
}
