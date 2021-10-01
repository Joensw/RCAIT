#ifndef TOPACCURACIESGRAPHICS_H
#define TOPACCURACIESGRAPHICS_H

#include <QMap>
#include <QGraphicsSvgItem>
#include <QStringBuilder>
#include <genericgraphicsview.h>
#include <configurationmanager.h>
#include <genericresultgraphics.h>

/**
 * @brief Top Accuracies Graphics are used to display
 * and compare the Top1% and Top5% values of multiple compared training results.
 * This class is used for data retention and contains all information required for visualisation.
 */
class TopAccuraciesGraphics : public GenericResultGraphics {
Q_OBJECT

public:
    /**
     * @brief Constructs TopAccuraciesGraphics
     * @param directory working directory to store visualisation
     * @param data list of result names and their corresponding accuracy data
     */
    explicit TopAccuraciesGraphics(const QString &directory,
                                   const QList<QPair<QString, QList<double>>> &data = {});

    /**
     * @brief Adds a data entry to the top accuracies graphics
     * @param identifier result identifier
     * @param data list of corresponding accuracy data entries
     */
    void addDataRow(const QString &identifier, const QList<double> &data);

    /**
     * @brief Remove a given data entry from retention.
     * @param identifier result to unload
     * @attention This does not remove the result itself, only its entry in data retention.
     */
    void removeDataRow(const QString &identifier);

    /**
     * @brief Get the stored accuracy data of a given result.
     * @param identifier identifier of the result.
     * @return list of the stored accuracy data.
     */
    QList<double> operator[](const QString &identifier) const;

    /**
     * @brief Check if two Top Accuracies Graphics are equal.
     * @param other Top Accuracies Graphics to compare to
     * @return equal or not
     */
    bool operator==(const TopAccuraciesGraphics &other) const;

    /**
     * @brief Check if two Top Accuracies Graphics are <b>not</b> equal.
     * @param other Top Accuracies Graphics to compare to
     * @return unequal or not
     */
    bool operator!=(const TopAccuraciesGraphics &other) const;

    /**
     * @brief Replace the current data with new one.
     * @param mData new data to replace with
     */
    [[maybe_unused]] void setData(const QList<QPair<QString, QList<double>>> &mData);

private:
    QList<QPair<QString, QList<double>>> m_data;

    void generateGraphicsInternal(const QString &fullFilePath) override;

    void passResultGraphics(GenericGraphicsView *receiver, const QString &fullFilePath) override;

    QString labelsToPyText() const;

    QString valuesToPyText() const;
};

#endif // TOPACCURACIESGRAPHICS_H
