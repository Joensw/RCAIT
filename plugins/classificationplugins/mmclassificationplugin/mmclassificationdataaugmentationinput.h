#ifndef MMCLASSIFICIATIONDATAAUGMENTATIONINPUT_H
#define MMCLASSIFICIATIONDATAAUGMENTATIONINPUT_H

#include <QWidget>
#include <QMap>

namespace Ui {
class MMClassificationDataAugmentationInput;
}

/**
 * @brief The MMClassificationDataAugmentationInput class makes plugin specific, data augmentation input parameters accessible
 */
class MMClassificationDataAugmentationInput : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString m_albu_transform_type READ getAlbuTransformType WRITE setAlbuTransformType)
    Q_PROPERTY(double m_random_flip_prob READ getRandomFlipProb WRITE setRandomFlipProb)
    Q_PROPERTY(QString m_random_flip_direction READ getRandomFlipDirection WRITE setRandomFlipDirection)
    Q_PROPERTY(bool m_randomErasing READ getRandomErasing WRITE setRandomErasing)
    Q_PROPERTY(int m_resize READ getResize WRITE setResize)
    Q_PROPERTY(int m_center_crop_size READ getCenterCropSize WRITE setCenterCropSize)

protected:

    /**
     * @brief changeEvent event handler
     *
     * @param event incoming event
     */
    void changeEvent(QEvent *event) override;

public:
    /**
     * @brief MMClassificationDataAugmentationInput creates a new instance of this class
     * @param parent parent the parent widget of this widget
     */
    explicit MMClassificationDataAugmentationInput(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */

    ~MMClassificationDataAugmentationInput();

    /**
     * @brief getAlbuTransformType returns the specified albu transform type
     * @return the albu transform type used by albumnations,
     *         an empty QString if the user does not want to use this parameter
     */
    QString getAlbuTransformType();

    /**
     * @brief setAlbuTransformType sets the albu transform type
     * @param type the albu transform type to use with albumnations,
     *        an empty QString, if this parameter is not to be used
     */
    void setAlbuTransformType(QString type);

    /**
     * @brief getRandomResizedCropSize returns the specified random resized crop size
     * @return the specified positive integer for the size,
     *         zero, if the user does not want to use this parameter
     */
    int getRandomResizedCropSize();

    /**
     * @brief setRandomResizedCropSize sets the random resized crop size
     * @param size a positive integer, zero if this parameter is not to be used
     */
    void setRandomResizedCropSize(int size);

    /**
     * @brief getRandomFlipProb returns the specified random flip probability
     * @return the specified positve double value, less than 1 for the probability,
     *         zero, if the user does not want to use this parameter
     */
    double getRandomFlipProb();

    /**
     * @brief setRandomFlipProb sets the random flip probability
     * @param probability a positive double value, less than 1,
     *        zero, if this parameter is not to be used
     */
    void setRandomFlipProb(double probability);

    /**
     * @brief getRandomFlipDirection returns the specified random flip direction
     * @return the specified direction , an empty QString if the user does not want to use this parameter
     */
    QString getRandomFlipDirection();

    /**
     * @brief setRandomFlipDirection sets the random flip direction,
     * @param direction the new direction,
     *        an empty QString, if this parameter is not to be used
     */
    void setRandomFlipDirection(QString direction);

    /**
     * @brief getRandomErasing returns if random erasing should be used
     * @return true, if random erasing should be used, false otherwise
     */
    bool getRandomErasing();

    /**
     * @brief setRandomErasing sets if random erasing should be used
     * @param execute specifying if random erasing should be used
     */
    void setRandomErasing(bool execute);

    /**
     * @brief getResize returns the specified resize parameter
     * @return a positive integer, if resize the resize parameter should be used,
     *         zero otherwise
     */
    int getResize();

    /**
     * @brief setResize sets the resize parameter
     * @param size a positive integer, if the resize parameter should be used,
     *        zero otherwise
     */
    void setResize(int size);

    /**
     * @brief getCenterCropSize returns the specified center crop size
     * @return the specified center crop size,
     *         zero, if the center crop size parameter should not be used
     */
    int getCenterCropSize();

    /**
     * @brief setCenterCropSize the center crop size paramater
     * @param size a positive integer, if the center crop size parameter should be used,
     *        zero otherwise
     */
    void setCenterCropSize(int size);


private:
    void connectCheckboxes();
    void connectInputElements();

    Ui::MMClassificationDataAugmentationInput *ui;

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
