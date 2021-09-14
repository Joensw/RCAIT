#ifndef RESULT_H
#define RESULT_H

class Result {
private:
    QString m_storageDir;
    QStringList m_additionalResults;
    QString m_identifier;

public:
    explicit Result(const QString &storageDir, QStringList additionalResults = {});

    [[nodiscard]] QStringList getAdditionalResults() const;

    [[nodiscard]] const QString &getStorageDir() const;

    [[nodiscard]] QString getIdentifier() const;

    [[nodiscard]] QString getSavableIdentifier() const;

    static QString generateTimestamp();

    static QString generateExtendedTimestamp();

    virtual ~Result() = default;

    static QString savableRepresentation(QString date);

    static QString niceRepresentation(QString date);

};


#endif //RESULT_H
