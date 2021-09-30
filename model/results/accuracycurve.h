#ifndef ACCURACYCURVE_H
#define ACCURACYCURVE_H


#include <QGraphicsItem>
#include <QFileInfo>
#include <QGraphicsSvgItem>
#include <QProcess>
#include <QStringBuilder>
#include <mapadapt.h>
#include <trainingresultview.h>
#include <genericresultgraphics.h>
#include <configurationmanager.h>

/**
 * @brief Accuracy curves are used to visualize the accuracy values over a period in iterations
 * This class is used for data retention and contains all information required for visualisation.
 */
class AccuracyCurve : public GenericResultGraphics {
Q_OBJECT

public:
    /**
     * @brief Constructs an AccuracyCurve
     * @param directory working directory to store visualisation
     * @param identifier output file identifier
     * @param data accuracy points to plot the curves
     */
    AccuracyCurve(const QString &directory, const QString &identifier,
                  const QMap<int, QPair<double, double>> &data);

    /**
     * @brief Get the values of training and validation at a given position
     * @param iteration position to lookup values
     * @return pair of training and validation values
     */
    QPair<double, double> operator[](int iteration) const;

    /**
     * @brief Check if two accuracy curves are equal
     * @param other accuracy curve to compare to
     * @return equal or not
     */
    bool operator==(const AccuracyCurve &other) const;

    /**
     * @brief Check if two accuracy curves are <b>not</b> equal
     * @param other accuracy curve to compare to
     * @return unequal or not
     */
    bool operator!=(const AccuracyCurve &other) const;

    /**
     * @brief Get all the accuracy data points
     * @return Map of all data points
     */
    [[maybe_unused]] [[nodiscard]] QMap<int, QPair<double, double>> getData() const;

private:
    QMap<int, QPair<double, double>> m_data;

    void generateGraphicsInternal(const QString &fullFilePath) override;

    void passResultGraphics(GenericGraphicsView *receiver, const QString &fullFilePath) override;

    [[nodiscard]] QString valuesToPyText() const;
};

#endif // ACCURACYCURVE_H
