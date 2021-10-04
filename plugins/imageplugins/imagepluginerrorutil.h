/**
 * @file imagepluginerrorutil.h
 *
 * @brief contains error strings and helper functions for error message building that are used by imageloaderplugins
 */

#ifndef IMAGEPLUGINERRORUTIL_H
#define IMAGEPLUGINERRORUTIL_H

#include <QString>
#include <QStringList>
#include <iostream>

/**
 * @brief the namespace for the helper functions and strings
 */
namespace imagepluginerrorutil
{

/**
 * @brief PATH_EMPTY_ERROR message if the supplied path is empty
 */
inline constexpr char PATH_EMPTY_ERROR[] = "Provided path is empty String.";
/**
 * @brief LABEL_EMPTY_ERROR message if the given labels are empty
 */
inline constexpr char LABEL_EMPTY_ERROR[] = "No labels provided.";
/**
 * @brief COUNT_INVALID_ERROR message if the count is not valid
 */
inline constexpr char COUNT_INVALID_ERROR[] = "Requested non-positive amount of images.";
/**
 * @brief ERROR_STRING substring to start the error message
 */
inline constexpr char ERROR_STRING[] = "Error: ";
/**
 * @brief ERROR_END substring to end the error message
 */
inline constexpr char ERROR_END[] = " not set.";
/**
 * @brief CONFIGURED_STRING message if everything is configured correctly
 */
inline constexpr char CONFIGURED_STRING[] = "All settings are set.";


/**
 * @brief getErrorString returns a error message given a list of errors
 * @param list the error messages to include
 * @return the error message string
 */
inline QString getErrorString(QStringList &list) {return QString(ERROR_STRING) + list.join(" ") ;}
/**
 * @brief checkInputs checks the inputs for a loadImages method
 * @param path the path
 * @param label the label
 * @param count the count
 * @return a list with error messages. Empty if all parameters are valid
 */
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
