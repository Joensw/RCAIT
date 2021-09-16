#ifndef RESULT_H
#define RESULT_H

/**
 * @brief This class is a super class of all specific result classes.
 * It provides common functionality for the result classes.
 * Result classes are very flexible and specific types can therefore be seen as 'plugins'
 */
class Result {
private:
    QString m_storageDir;
    QStringList m_additionalResults;
    QString m_identifier;

public:
    /**
     * @brief Constructs a generic result object.
     * @param storageDir directory to store result data in
     * @param additionalResults extensible list of paths to additional results (optional)
     */
    explicit Result(QString storageDir, QStringList additionalResults = {});

    /**
     * @brief Gets the additional results.
     * @return list of additional results.
     */
    [[maybe_unused]] [[nodiscard]] QStringList getAdditionalResults() const;

    /**
     * @brief Get the storage directory of the result.
     * @return path to storage directory.
     */
    [[maybe_unused]] [[nodiscard]] const QString &getStorageDir() const;

    /**
     * @brief Get the identifier of the result.
     * @return identifier in a nice representation.
     * @attention This identifier cannot be used as a filename,
     * as it may contain prohibited characters. Only use it in the UI!
     */
    [[maybe_unused]] [[nodiscard]] QString getIdentifier() const;

    /**
     * @brief Get the identifier of the result.
     * @return identifier in a savable representation.
     * @usage This identifier contains only latin characters + digits + underscores + dashes.
     * It is safe to use it for filenames.
     */
    [[maybe_unused]] [[nodiscard]] QString getSavableIdentifier() const;

    /**
     * @brief Generates the current time as a string.
     * @return string of the current time including date, hours, and minutes.
     */
    static QString generateTimestamp();

    /**
     * @brief Generates the current time as a string.
     * @return string of the current time including date, hours, minutes and seconds.
     */
    static QString generateExtendedTimestamp();

    /**
     * @brief Default destructor.
     */
    virtual ~Result() = default;

    /**
     * @brief Converts a given timestamp in the savable representation.
     * @usage Safe to use in filenames.
     * @param date timestamp to be converted
     * @return converted timestamp as a string.
     */
    static QString savableRepresentation(QString date);

    /**
     * @brief Converts a given timestamp in the nice representation.
     * @attention This shall <b>not</b> be used for filenames.
     * @param date timestamp to be converted
     * @return converted timestamp as a string.
     */
    static QString niceRepresentation(QString date);

    /**
     * @brief Checks if this result is valid.
     * @return valid or not.
     */
    [[nodiscard]] virtual bool isValid() const = 0;
};


#endif //RESULT_H
