#ifndef RESULT_H
#define RESULT_H

class Result {
private:
    QStringList m_additionalResults;
    QString m_identifier;

public:
    explicit Result(QStringList  additionalResults = QStringList());
    [[nodiscard]] QStringList getAdditionalResults() const;

    [[nodiscard]] QString getIdentifier() const;

    static QString generateTimestamp();

    static QString generateExtendedTimestamp();
};


#endif //RESULT_H
