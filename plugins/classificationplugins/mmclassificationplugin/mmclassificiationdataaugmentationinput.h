#ifndef MMCLASSIFICIATIONDATAAUGMENTATIONINPUT_H
#define MMCLASSIFICIATIONDATAAUGMENTATIONINPUT_H

#include <QWidget>
#include <QMap>

namespace Ui {
class MMClassificiationDataAugmentationInput;
}

class MMClassificiationDataAugmentationInput : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString m_albu_transform_type READ getAlbuTransformType WRITE setAlbuTransformType)
    Q_PROPERTY(double m_random_flip_prob READ getRandomFlipProb WRITE setRandomFlipProb)
    Q_PROPERTY(QString m_random_flip_direction READ getRandomFlipDirection WRITE setRandomFlipDirection)
    Q_PROPERTY(bool m_randomErasing READ getRandomErasing WRITE setRandomErasing)
    Q_PROPERTY(int m_resize READ getResize WRITE setResize)
    Q_PROPERTY(int m_center_crop_size READ getCenterCropSize WRITE setCenterCropSize)

public:
    explicit MMClassificiationDataAugmentationInput(QWidget *parent = nullptr);
    ~MMClassificiationDataAugmentationInput();

    QString getAlbuTransformType();
    void setAlbuTransformType(QString type);
    int getRandomResizedCropSize();
    void setRandomResizedCropSize(int size);
    double getRandomFlipProb();
    void setRandomFlipProb(double probability);
    QString getRandomFlipDirection();
    void setRandomFlipDirection(QString direction);
    bool getRandomErasing();
    void setRandomErasing(bool execute);
    int getResize();
    void setResize(int size);
    int getCenterCropSize();
    void setCenterCropSize(int size);


private:
    void connectCheckboxes();
    void connectInputElements();

    Ui::MMClassificiationDataAugmentationInput *ui;

    QString m_albu_transform_type = "ColorJitter";
    int m_random_resized_crop_size = 224;
    double m_random_flip_prob = 0.5;
    QString m_random_flip_direction = "horizontal";
    bool m_randomErasing = true;
    int m_resize = 256;
    int m_center_crop_size = 224;

private slots:
    void slot_albuTransformChecked(bool isChecked);
    void slot_randomResizedCropSizeChecked(bool isChecked);
    void slot_randomFlipProbAndDirectionChecked(bool isChecked);
    void slot_randomErasingChecked(bool isChecked);
    void slot_resizeChecked(bool isChecked);
    void slot_centerCropSizeChecked(bool isChecked);

    void slot_albuTransformChanged(QString type);
    void slot_randomResizedCropSizeChanged(int size);
    void slot_randomFlipProbChanged(double probability);
    void slot_randomFlipDirectionChanged(QString direction);
    void slot_resizeChanged(int size);
    void slot_centerCropSizeChanged(int size);
};

#endif // MMCLASSIFICIATIONDATAAUGMENTATIONINPUT_H
