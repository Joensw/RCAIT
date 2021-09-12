#ifndef JSON_TOOLBOX_H
#define JSON_TOOLBOX_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>

/**
 * @brief This class contains utilities for converting, importing and exporting JSON objects
 */
class JSON_Toolbox {
private:
    /**
     * @brief Default constructor.
     */
    JSON_Toolbox() = default;

public:
    /**
     * @brief Read a JSON file into a QJsonObject
     * @param filepath path of JSON file
     * @return QJsonObject containing the file data in a usable format
     */
    static QJsonObject readJSONFromFile(const QString &filepath);

    /**
     * @brief Read a JSON file into a QJsonObject
     * @param byteArray contains json data in string-like format
     * @return QJsonObject containing the file data in a usable format
     */
    static QJsonObject readJSON(const QByteArray &byteArray);

    /**
     * @brief Write a QJsonObject into a JSON file
     * @param jsonObject object to write to file
     * @param filepath path to store JSON file
     * @return success state
     */
    static bool writeJSONToFile(const QJsonObject &jsonObject, const QString &filepath);
};

inline QJsonObject JSON_Toolbox::readJSONFromFile(const QString &filepath) {
    auto file = QFile(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Json file couldn't be opened/found";
        return {};
    }

    QByteArray byteArray = file.readAll();
    file.close();

    return readJSON(byteArray);
}

inline QJsonObject JSON_Toolbox::readJSON(const QByteArray &byteArray) {
    //Format the content of the byteArray as QJsonDocument
    //and check on parse Errors
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return {};
    }

    //Create a JSON object and fill it with the ByteArray content
    return jsonDoc.object();
}

inline bool JSON_Toolbox::writeJSONToFile(const QJsonObject &jsonObject, const QString &filepath) {
    QJsonDocument json_doc(jsonObject);
    auto rawData = json_doc.toJson();

    QFile save_file(filepath);
    if (!save_file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open save file " << filepath;
        return false;
    }
    save_file.write(rawData);
    save_file.close();

    return true;
}

/**
     * @brief Read a QJsonArray into a list of arbitrary type
     * @tparam T desired type
     * @param json_array QJsonArray to be read
     * @return list of desired type
     */
template<typename T>
static QList<T> QJsonArray_toList(const QJsonArray &json_array) {
    QList<T> list;

    for (const auto &item: json_array) {
        Q_ASSERT(item.toVariant().canConvert<T>());
        list << qvariant_cast<T>(item.toVariant());
    }
    return list;
}

/**
 * @brief Read any type of QList and make it a QJsonArray
 * @tparam T arbitrary type
 * @param list list to be converted
 * @return QJsonArray containing the same elements
 */
template<typename T>
static QJsonArray QJsonArray_fromAnyList(const QList<T> &list) {
    QJsonArray JSONArray;

    for (const auto &value: list)
        JSONArray << value;

    return JSONArray;
}


#endif // JSON_TOOLBOX_H
