#ifndef IMAGEPLUGINERRORUTIL_H
#define IMAGEPLUGINERRORUTIL_H
#include <QString>
#include <QStringList>
#include <iostream>

namespace imagepluginerrorutil
{
//extern const int i;
inline constexpr char PATH_EMPTY_ERROR[] = "Provided path is empty String.";
inline constexpr char LABEL_EMPTY_ERROR[] = "No labels provided.";
inline constexpr char COUNT_INVALID_ERROR[] = "Requested non-positive amount of images.";

inline constexpr char ERROR_STRING[] = "Error: ";
inline constexpr char ERROR_END[] = " not set.";
inline constexpr char CONFIGURED_STRING[] = "All settings are set.";



inline QString getErrorString(QStringList &list) {return QString(ERROR_STRING) + list.join(" ") ;}
inline QStringList checkInputs(const QString &path, const QStringList &label, int count){
    QStringList inputErrors;

    if(path.isEmpty()){
        inputErrors << imagepluginerrorutil::PATH_EMPTY_ERROR;
    }

    if(count <= 0){
        inputErrors << imagepluginerrorutil::COUNT_INVALID_ERROR;
    }

    if(label.isEmpty()){
        inputErrors << imagepluginerrorutil::LABEL_EMPTY_ERROR;
    }

    return inputErrors;
}
}



#endif // IMAGEPLUGINERRORUTIL_H
