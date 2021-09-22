#include "mmclassificationdataaugmentationinput.h"
#include "ui_mmclassificationdataaugmentationinput.h"

MMClassificationDataAugmentationInput::MMClassificationDataAugmentationInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MMClassificationDataAugmentationInput)
{
    ui->setupUi(this);
    connectCheckboxes();
    connectInputElements();
}

void MMClassificationDataAugmentationInput::connectCheckboxes()
{
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificationDataAugmentationInput::slot_albuTransformChecked);
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificationDataAugmentationInput::slot_randomResizedCropSizeChecked);
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificationDataAugmentationInput::slot_randomFlipProbAndDirectionChecked);
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificationDataAugmentationInput::slot_randomErasingChecked);
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificationDataAugmentationInput::slot_resizeChecked);
    connect(ui->checkBox_albuTransformType, &QCheckBox::clicked, this, &MMClassificationDataAugmentationInput::slot_centerCropSizeChecked);
}

void MMClassificationDataAugmentationInput::connectInputElements()
{
    connect(ui->comboBox_albuTransformType, &QComboBox::currentTextChanged, this, &MMClassificationDataAugmentationInput::slot_albuTransformChanged);
    connect(ui->spinBox_resizedCropSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &MMClassificationDataAugmentationInput::slot_randomResizedCropSizeChanged);
    connect(ui->doubleSpinBox_randomFlipProbability, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MMClassificationDataAugmentationInput::slot_randomFlipProbChanged);
    connect(ui->comboBox_randomFlipDirection, &QComboBox::currentTextChanged, this, &MMClassificationDataAugmentationInput::slot_randomFlipDirectionChanged);
    connect(ui->spinBox_resize, QOverload<int>::of(&QSpinBox::valueChanged), this, &MMClassificationDataAugmentationInput::slot_resizeChanged);
    connect(ui->spinBox_centerCropSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &MMClassificationDataAugmentationInput::slot_centerCropSizeChanged);
}

MMClassificationDataAugmentationInput::~MMClassificationDataAugmentationInput()
{
    delete ui;
}

QString MMClassificationDataAugmentationInput::getAlbuTransformType()
{
    return m_albu_transform_type;
}

void MMClassificationDataAugmentationInput::setAlbuTransformType(const QString &type)
{
    m_albu_transform_type = type;
}

int MMClassificationDataAugmentationInput::getRandomResizedCropSize()
{
    return m_random_resized_crop_size;
}

void MMClassificationDataAugmentationInput::setRandomResizedCropSize(int size)
{
    m_random_resized_crop_size = size;
}

double MMClassificationDataAugmentationInput::getRandomFlipProb()
{
    return m_random_flip_prob;
}

void MMClassificationDataAugmentationInput::setRandomFlipProb(double probability)
{
    m_random_flip_prob = probability;
}

QString MMClassificationDataAugmentationInput::getRandomFlipDirection()
{
    return m_random_flip_direction;
}

void MMClassificationDataAugmentationInput::setRandomFlipDirection(const QString &direction)
{
    m_random_flip_direction = direction;
}

bool MMClassificationDataAugmentationInput::getRandomErasing()
{
    return m_randomErasing;
}

void MMClassificationDataAugmentationInput::setRandomErasing(bool execute)
{
    m_randomErasing = execute;
}

int MMClassificationDataAugmentationInput::getResize()
{
    return m_resize;
}

void MMClassificationDataAugmentationInput::setResize(int size)
{
    m_resize = size;
}

int MMClassificationDataAugmentationInput::getCenterCropSize()
{
    return m_center_crop_size;
}

void MMClassificationDataAugmentationInput::setCenterCropSize(int size)
{
    m_center_crop_size = size;
}

void MMClassificationDataAugmentationInput::slot_albuTransformChecked(bool isChecked)
{
    if (isChecked) {
        setAlbuTransformType(ui->comboBox_albuTransformType->currentText());
    } else {
        setAlbuTransformType("");
    }
}

void MMClassificationDataAugmentationInput::slot_randomResizedCropSizeChecked(bool isChecked)
{
    if (isChecked) {
        setRandomResizedCropSize(ui->spinBox_resizedCropSize->value());
    } else {
        setRandomResizedCropSize(0);
    }
}

void MMClassificationDataAugmentationInput::slot_randomFlipProbAndDirectionChecked(bool isChecked)
{
    if (isChecked) {
        setRandomFlipProb(ui->doubleSpinBox_randomFlipProbability->value());
        setRandomFlipDirection(ui->comboBox_randomFlipDirection->currentText());
    } else {
        setRandomFlipProb(0);
        setRandomFlipDirection("");
    }
}

void MMClassificationDataAugmentationInput::slot_randomErasingChecked(bool isChecked)
{
    if (isChecked) {
        setRandomErasing(true);
    } else {
        setRandomErasing(false);
    }
}

void MMClassificationDataAugmentationInput::slot_resizeChecked(bool isChecked)
{
    if (isChecked) {
        setResize(ui->spinBox_resize->value());
    } else {
        setResize(0);
    }
}

void MMClassificationDataAugmentationInput::slot_centerCropSizeChecked(bool isChecked)
{
    if (isChecked) {
        setCenterCropSize(ui->spinBox_centerCropSize->value());
    } else {
        setCenterCropSize(0);
    }
}

void MMClassificationDataAugmentationInput::slot_albuTransformChanged(const QString &type)
{
    setAlbuTransformType(type);
}

void MMClassificationDataAugmentationInput::slot_randomResizedCropSizeChanged(int size)
{
    setRandomResizedCropSize(size);
}

void MMClassificationDataAugmentationInput::slot_randomFlipProbChanged(double probability)
{
    setRandomFlipProb(probability);
}

void MMClassificationDataAugmentationInput::slot_randomFlipDirectionChanged(const QString &direction)
{
    setRandomFlipDirection(direction);
}

void MMClassificationDataAugmentationInput::slot_resizeChanged(int size)
{
    setResize(size);
}

void MMClassificationDataAugmentationInput::slot_centerCropSizeChanged(int size)
{
    setCenterCropSize(size);
}

void MMClassificationDataAugmentationInput::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}
