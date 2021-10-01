#ifndef CONFUSIONMATRIX_H
#define CONFUSIONMATRIX_H

#include <QGraphicsItem>
#include <QProcess>
#include <QFileInfo>
#include <QGraphicsSvgItem>
#include <QDir>
#include <QStringBuilder>
#include <configurationmanager.h>
#include <trainingresultview.h>
#include "genericresultgraphics.h"

/**
 * @brief Confusion matrices are used for visually comparing the precision of an AI.
 * This class is used for data retention and contains all information required for visualisation.
 */
class ConfusionMatrix : public GenericResultGraphics {
    Q_OBJECT
public:

    /**
     * @brief Construct a square Confusion Matrix
     * @param directory  Saving directory for result
     * @param identifier file name including extension
     * @param classLabels N labels for the matrix
     * @param values NxN values, one for each cell
     */
    ConfusionMatrix(const QString &directory, const QString &identifier,
                    const QStringList &classLabels, const QList<int> &values);

    /**
     * Access matrix via matrix(row,column) operator
     * @return value of matrix at(row,column)
     */
    double operator()(int row, int column) const;

    /**
     * @brief Get a particular cell of the confusion matrix
     * @param other matrix
     * @return cell double value
     */
    bool operator==(const ConfusionMatrix &other) const;

    /**
     * @brief Compare matrix with the current one
     * @param other matrix
     * @return true when different, false otherwise
     */
    bool operator!=(const ConfusionMatrix& other) const;

    //needed for serialisation
    /**
     * @brief Get confusionmatrix class labels
     * @return List of class labels
     */
    [[maybe_unused]] [[nodiscard]] const QStringList &getClassLabels() const;

    /**
     * @brief Get confusionmatrix dimensions
     * @return N, where matrix has dimensions NxN
     */
    [[maybe_unused]] [[nodiscard]] qsizetype getSize() const;

    /**
     * @brief Get confusionmatrix values
     * @return matrix values
     */
    [[maybe_unused]] [[nodiscard]] const QList<int> &getValues() const;

private:
    qsizetype m_size;
    QStringList m_classLabels;
    QList<int> m_values;


   /**
    * @brief Generate the confusion matrix graphics
    * @param fullFilePath where the graphics will be saved
    */
    void generateGraphicsInternal(const QString &fullFilePath) override;

    /**
     * @brief Give the generated graphics to the receiver
     * @param fullFilePath path to the generated graphics
     * @param receiver graphics view that will display the result image
     */
    void passResultGraphics(GenericGraphicsView *receiver, const QString &fullFilePath) override;

    /**
     * @brief Convert matrix data to text in a python-friendly way
     * @return QString matrix representation e.g. [[1,2],[3,4]]
     */
    QString valuesToPyText() const;

    /**
     * @brief Convert matrix labels to text in a python-friendly way
     * @return QString label representation e.g. "['Car','Truck']"
     */
    QString labelsToPyText() const;
};

#endif // CONFUSIONMATRIX_H
