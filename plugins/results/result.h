#ifndef RESULT_H
#define RESULT_H

class Result {
private:
    QStringList m_additionalResults;
    QString m_identifier;

public:
    explicit Result(QStringList additionalResults = {});

    [[nodiscard]] QStringList getAdditionalResults() const;

    [[nodiscard]] QString getIdentifier() const;

    [[nodiscard]] QString getSaveableIdentifier() const;

    static QString generateTimestamp();

    static QString generateExtendedTimestamp();

    virtual ~Result() = default;

    static QString saveableRepresentation(QString date);

    static QString niceRepresentation(QString date);

};


#endif //RESULT_H
