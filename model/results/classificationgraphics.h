#ifndef CLASSIFICATIONGRAPHICS_H
#define CLASSIFICATIONGRAPHICS_H

#include <QMap>
#include <QGraphicsSvgItem>
#include <QString>
#include <QFileInfo>
#include <QStringBuilder>
#include <mapadapt.h>
#include <genericgraphicsview.h>
#include "genericresultgraphics.h"

/**
 * @brief Classification Graphics are used to visualize
 * the classification confidences and resulting labels for images
 * This class is used for data retention and contains all information required for visualisation.
 */
class ClassificationGraphics : public GenericResultGraphics {
Q_OBJECT

public:
    /**
     * @brief Constructs ClassificationGraphics
     * @param directory working directory to store visualisation
     * @param identifier output file identifier
     * @param data data map containing confidences for every image (given as a path)
     * @param classLabels list of class labels, each label assigns to a confidence score.
     */
    ClassificationGraphics(const QString &directory, const QString &identifier,
                           const QMap<QString, QList<double>> &data,
                           const QStringList &classLabels);

    /**
     * @brief Add a classification entry to retain
     * @param identifier path to an image file
     * @param data confidence scores for that particular image file
     */
    [[maybe_unused]] void addClassificationEntry(const QString &identifier, QList<double> &data);

    /**
     * @brief Remove a classification entry from retention
     * @param identifier path to the image file to be unloaded
     * @attention This does not remove the image file itself, only its entry in data retention.
     */
    [[maybe_unused]] void removeClassificationEntry(const QString &identifier);

    /**
     * @brief Get the confidence values for a given image
     * @param identifier image path too lookup
     * @return list of confidence values
     */
    QList<double> operator[](const QString &identifier) const;

    /**
     * @brief Check if two Classification Graphics are equal.
     * @param other Classification Graphics to compare to
     * @return equal or not
     */
    bool operator==(const ClassificationGraphics &other) const;

    /**
     * @brief Check if two Classification Graphics are <b>not</b> equal.
     * @param other Classification Graphics to compare to
     * @return unequal or not
     */
    bool operator!=(const ClassificationGraphics &other) const;

private:
    QMap<QString, QList<double>> m_data;
    QStringList m_classLabels;

    void generateGraphicsInternal(const QString &fullFilePath) override;

    void passResultGraphics(GenericGraphicsView *receiver, const QString &fullFilePath) override;

    QString dataToPyText();

    QString imagePathsToPyText();

    QString classLabelsToPyText();

};

#endif // CLASSIFICATIONGRAPHICS_H
