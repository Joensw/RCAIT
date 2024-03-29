#include "mmclassificationjsonresultreader.h"

QVector<int> MMClassificationJsonResultReader::readConfusionMatrixFromJsonFile(const QString &filePath) {
    QFileInfo jsonFile = QFileInfo(filePath);
    QFile inFile(jsonFile.absoluteFilePath());

    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QVector<int> listValues = {};

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (!doc.isNull()) {
        QJsonArray rows = doc.array();
        for (int i = 0; i < rows.size(); i++) {
            // read each row of the matrix
            QJsonArray row = rows.at(i).toArray();
            for (int j = 0; j < row.size(); j++) {
                listValues.append(row[j].toInteger());
            }
        }
    } else {
        qWarning() << "Parse failed";
    }
    return listValues;
}

QMap<int, QPair<double, double>> MMClassificationJsonResultReader::getAccuracyCurve(QString logFilePath) {
    const int evaluation_frequency = 100;
    int evaluation_iteration = 0;

    QFileInfo jsonLogFile = QFileInfo(logFilePath);
    QFile inFile(jsonLogFile.absoluteFilePath());
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QStringList data = {};
    QTextStream in(&inFile);
    QString line = in.readLine();
    while (!line.isNull()) {
        line = in.readLine();
        data.append(line);
    }
    inFile.close();

    QMap<int, QPair<double, double>> accuracyCurve = {};
    for (int j = 1; j < data.size(); j++) { // first line contains only information about the environment
        if (!data[j].toUtf8().isEmpty()) {
            QJsonParseError errorPtr;
            QJsonDocument doc = QJsonDocument::fromJson(data[j].toUtf8(), &errorPtr);
            if (doc.isNull()) {
                    qWarning() << "Parse failed";
            }
            QJsonObject rootObj = doc.object();
            if (rootObj.contains("accuracy_top-1")) {
                double accuracy_top_1_value_validation = rootObj.value("accuracy_top-1").toDouble(); // accuracy of the validation step
                evaluation_iteration += evaluation_frequency;
                double accuracy_top_1_value_training = 0.0;
                QJsonDocument previousDoc = QJsonDocument::fromJson(data[j-1].toUtf8(), &errorPtr);
                if (previousDoc.isNull()) {
                    qWarning() << "Parse failed";
                }
                QJsonObject previousRootObj = previousDoc.object();
                if (previousRootObj.contains("top-1")) {
                    accuracy_top_1_value_training = previousRootObj.value("top-1").toDouble(); // accuracy of the training step
                }
                QPair<double, double> valuePair = {accuracy_top_1_value_training, accuracy_top_1_value_validation};
                accuracyCurve.insert(evaluation_iteration, valuePair);
            }
        }
    }
    return accuracyCurve;
}



QPair<double, double> MMClassificationJsonResultReader::readTopValuesFromJson(QString filePath)
{
    QPair<double, double> topValues = {};
    QFileInfo jsonFile = QFileInfo(filePath);
    QFile inFile(jsonFile.absoluteFilePath());
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (!doc.isNull()) {
        QJsonObject rootObj = doc.object();
        if (rootObj.contains("accuracy_top-1")) {
            topValues.first = rootObj.value("accuracy_top-1").toDouble();
        }
        if (rootObj.contains("accuracy_top-5")) {
            topValues.second = rootObj.value("accuracy_top-5").toDouble();
        }
    } else {
        qWarning() << "Parse failed";
    }
    return topValues;
}

QStringList
MMClassificationJsonResultReader::generateMostMisclassifiedImages(int requiredNumber, const QString &pathToValTxt,
                                                                  const QString &pathToJsonResult) {
    QVector<int> selectedMissclassifiedImageIndices = {};
    QStringList outputValidationFiles = {};

    // first read val.txt file to match validation images with their corresponding class
    QPair<QVector<QString>, QVector<int>> annotationFileData = readAnnotationFile(pathToValTxt);
    QVector<QString> absoluteImagePaths = annotationFileData.first;
    QVector<int> matchingClasses = annotationFileData.second;

    QFileInfo jsonFile = QFileInfo(pathToJsonResult);
    QFile inFile(jsonFile.absoluteFilePath());
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();
    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (!doc.isNull()) {
        QJsonObject rootObj = doc.object();
        QJsonValue pred_score_value = rootObj.value("pred_score");
        QJsonArray pred_score_array = pred_score_value.toArray();
        QJsonValue pred_label_value = rootObj.value("pred_label");
        QJsonArray pred_label_array = pred_label_value.toArray();
        if (matchingClasses.size() == pred_label_array.size()) {
            QVector<int> missclassifiedImageIndices = {};
            QMultiMap<double, int> associatedIndiceToScore = {};
            for (int i = 0; i < matchingClasses.size(); i++) {
                if (matchingClasses.at(i) != pred_label_array.at(i).toInt()) {
                    missclassifiedImageIndices.append(i);
                    associatedIndiceToScore.insert(pred_score_array.at(i).toDouble(), i);
                }
            }
            if (missclassifiedImageIndices.size() > requiredNumber) {
                QList<double> sortedScoresDesc;
                for (int j = 0; j < missclassifiedImageIndices.size(); j++) {
                    sortedScoresDesc = associatedIndiceToScore.keys();
                    std::sort(sortedScoresDesc.rbegin(), sortedScoresDesc.rend());
                }
                QVector<double> numberOfHighestMissclassifiedScores = {};
                for (int k = 0; k < requiredNumber; k++) {
                    numberOfHighestMissclassifiedScores.append(sortedScoresDesc.takeFirst());
                }
                for (int l = 0; l < numberOfHighestMissclassifiedScores.size(); l++) {
                    double score = numberOfHighestMissclassifiedScores[l];
                    int occurences = numberOfHighestMissclassifiedScores.count(score);
                    QList<int> indices = associatedIndiceToScore.values(score);
                    for (int m = 0; m < occurences; m++) {
                        selectedMissclassifiedImageIndices.append(indices[m]);
                    }
                }
            } else {
                selectedMissclassifiedImageIndices = missclassifiedImageIndices;
            }
            for (int n = 0; n < selectedMissclassifiedImageIndices.size(); n++) {
                outputValidationFiles.append(absoluteImagePaths[selectedMissclassifiedImageIndices[n]]);
            }
        }
    } else {
        qWarning() << "Parse failed";
    }
    return outputValidationFiles;
}

QMap<QString, QList<double>> MMClassificationJsonResultReader::readConfidenceScores(QString filePath, QStringList imageFileNames)
{
    QMap<QString, QList<double>> confidenceScorePerImage = {};

    QFileInfo jsonFile = QFileInfo(filePath);
    QFile inFile(jsonFile.absoluteFilePath());
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()) {
        qWarning() << "Parse failed";
    }
    QJsonArray rows = doc.array();
    QVector<double> valuesPerClass = {};

    for (int i = 0; i < rows.size(); i++) {
        // read each row

        QString imageFilePath = imageFileNames.at(i);
        QJsonArray row = rows.at(i).toArray();

        for (int j = 0; j < row.size(); j++) {
            valuesPerClass.append(row[j].toDouble());
        }

        confidenceScorePerImage.insert(imageFilePath, valuesPerClass);
        valuesPerClass.clear();
    }
    return confidenceScorePerImage;
}

QPair<QVector<QString>, QVector<int>> MMClassificationJsonResultReader::readAnnotationFile(const QString &annotationFilePath)
{
    QPair<QVector<QString>, QVector<int>> annotationFileData = {};
    QVector<QString> absoluteImagePaths = {};
    QVector<int> matchingClasses = {};
    // first read val.txt file to match images with their corresponding class
    QFileInfo valAnnotationFile = QFileInfo(annotationFilePath);
    QFile absoluteValAnnotationFile(valAnnotationFile.absoluteFilePath());
    absoluteValAnnotationFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&absoluteValAnnotationFile);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        QStringList list = line.split(QRegularExpression("\\s"));
        if (list.size() == 2) {
            absoluteImagePaths.append(list[0]);
            matchingClasses.append(list[1].toInt());
        }
    }
    absoluteValAnnotationFile.close();
    annotationFileData.first = absoluteImagePaths;
    annotationFileData.second = matchingClasses;
    return annotationFileData;
}
