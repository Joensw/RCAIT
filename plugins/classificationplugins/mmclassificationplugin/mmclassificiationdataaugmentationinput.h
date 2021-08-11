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
    void readDataAugmentationInput();

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
    Ui::MMClassificiationDataAugmentationInput *ui;

    QString m_albu_transform_type;
    int m_random_resized_crop_size;
    double m_random_flip_prob;
    QString m_random_flip_direction;
    bool m_randomErasing;
    int m_resize;
    int m_center_crop_size;
};

#endif // MMCLASSIFICIATIONDATAAUGMENTATIONINPUT_H
