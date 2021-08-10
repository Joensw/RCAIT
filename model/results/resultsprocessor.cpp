#include <projectmanager.h>
#include <classificationresultview.h>
#include "resultsprocessor.h"
#include "mapadapt.h"

enum GraphicsType {
    CLASSIFICATION,
    ACCURACYCURVE,
    CONFUSIONMATRIX,
    TOPACCURACIES,
    _COUNT
};
const std::array<QRegularExpression, _COUNT> GRAPHICSTYPE2REGEX = {
        QRegularExpression("classification_(.*)\\.(svg|png)$"),
        QRegularExpression("accuracycurve_(.*)\\.(svg|png)$"),
        QRegularExpression("confusionmatrix_(.*)\\.(svg|png)$"),
        QRegularExpression("topaccuracies_(.*)\\.(svg|png)$")
};

enum ResultType {
    TRAININGRESULT,
    CLASSIFICATIONRESULT,
    _COUNT2
};
const std::array<QRegularExpression, _COUNT2> RESULTTYPE2REGEX = {
        QRegularExpression("training_(.*)\\.json$"),
        QRegularExpression("classification_(.*)\\.json$"),
};


ResultsProcessor::ResultsProcessor() {
    m_topAccuraciesGraphics = new TopAccuraciesGraphics();
}

/**
 * Top Accuracies slots
 */
void ResultsProcessor::slot_normal_generateTopAccuraciesGraphics(AbstractGraphicsView *receiver) {
    m_topAccuraciesGraphics->updateIdentifier(Result::generateIdentifier());
    m_topAccuraciesGraphics->generateGraphics(receiver);
}

void ResultsProcessor::slot_comparison_loadAccuracyData(TopAccuraciesView *view, const QString &runNameToCompare) {
    auto fileName = QString("training_%1.json").arg(runNameToCompare);
    auto dirPath = ProjectManager::getInstance().getTrainingResultsDir();
    auto dir = QDir(dirPath);
    dir.cd(runNameToCompare);
    auto filepath = dir.absoluteFilePath(fileName);
    auto jsonObject = readJSON(filepath);

    auto top1 = jsonObject["top1"].toDouble();
    auto top5 = jsonObject["top5"].toDouble();

    m_topAccuraciesGraphics->addDataRow(runNameToCompare, {top1, top5});
    view->addTopAccuraciesEntry(runNameToCompare, top1, top5);
}

void ResultsProcessor::slot_comparison_unloadAccuracyData(TopAccuraciesView *view, const QString &runNameToCompare) {
    m_topAccuraciesGraphics->removeDataRow(runNameToCompare);
    view->removeTopAccuraciesEntry(runNameToCompare);
}


/**
 * Classification result slots
 */
void ResultsProcessor::slot_normal_loadClassificationResultData(ClassificationResultView *view,
                                                                ClassificationResult *result) {
    auto map = result->getClassificationData();
    auto labels = result->getLabels();
    Q_ASSERT(!map.isEmpty());
    Q_ASSERT(!labels.isEmpty());

    auto tableMap = QMap<int, QStringList>();

    int rowNumber = 1;
    for (const auto &[_, accList] : MapAdapt(map)) {
        //Assert that each accuracy value has a corresponding label
        Q_ASSERT(accList.size() == labels.size());
        auto max = std::max_element(accList.begin(), accList.end());

        //Calculate argmax(map), choose label with the highest accuracy
        auto index_max = std::distance(accList.begin(), max);
        auto max_accuracy = QString::number(*max, 'f', 2);
        auto label = labels[index_max];

        tableMap[rowNumber++] = {max_accuracy, label};
    }
    view->setClassificationData(tableMap);
}

void ResultsProcessor::slot_normal_generateClassificationResultGraphics(AbstractGraphicsView *receiver,
                                                                        ClassificationResult *result) {
    auto graphics = result->getClassificationGraphics();
    graphics->generateGraphics(receiver);
}

void ResultsProcessor::slot_comparison_loadClassificationResultData(ClassificationResultView *view,const QString &runNameToCompare) {
    view->setSaved(true);

    auto fileName = QString("classification_%1.json").arg(runNameToCompare);
    auto dirPath = ProjectManager::getInstance().getClassificationResultsDir();
    auto dir = QDir(dirPath);
    dir.cd(runNameToCompare);
    auto filepath = dir.absoluteFilePath(fileName);
    auto jsonObject = readJSON(filepath);

    auto json_classification_data = jsonObject["classification_data"].toArray();
    auto json_labels = jsonObject["labels"].toArray();
    auto json_additionalResults = jsonObject["additionalResults"].toArray();

    QMap<QString, QList<double>> classification_data;
    for (const auto &value : json_classification_data) {
        auto obj = value.toObject();
        auto imagePath = obj["image_path"].toString();
        auto json_list = obj["accuracy"].toArray();

        QList<double> list;
        for (const auto &item : json_list) {
            list << item.toDouble();
        }
        classification_data[imagePath] = list;
    }

    QStringList labels;
    for (const auto &label : json_labels) {
        labels << label.toString();
    }

    QStringList additionalResults;
    for (const auto &resultPath : json_additionalResults) {
        additionalResults << resultPath.toString();
    }

    auto result = new ClassificationResult(classification_data, labels, additionalResults);
    slot_normal_loadClassificationResultData(view, result);
}

void ResultsProcessor::slot_comparison_loadClassificationResultGraphics(AbstractGraphicsView *receiver,
                                                                        const QString &runNameToCompare) {
    auto dirPath = ProjectManager::getInstance().getClassificationResultsDir();
    loadGraphicsInView(receiver, runNameToCompare, dirPath);
}


/**
 * Training result slots
 */
void ResultsProcessor::slot_normal_loadTrainingResultData(TrainingResultView *view, TrainingResult *result) {
    auto mostMisclassifiedImages = result->getMostMisclassifiedImages();
    view->setMostMisclassifiedImages(mostMisclassifiedImages);
}

void ResultsProcessor::slot_normal_generateTrainingResultGraphics(AbstractGraphicsView *receiver,
                                                                  TrainingResult *result) {
    auto accCurve = result->getAccuracyCurve();
    auto confusionMatrix = result->getConfusionMatrix();
    accCurve->generateGraphics(receiver);
    confusionMatrix->generateGraphics(receiver);
}

void
ResultsProcessor::slot_comparison_loadTrainingResultData(TrainingResultView *view, const QString &runNameToCompare) {
    view->setSaved(true);

    auto fileName = QString("training_%1.json").arg(runNameToCompare);
    auto dirPath = ProjectManager::getInstance().getTrainingResultsDir();
    auto dir = QDir(dirPath);
    dir.cd(runNameToCompare);
    auto filepath = dir.absoluteFilePath(fileName);
    auto jsonObject = readJSON(filepath);

    auto json_accuracy_data = jsonObject["accuracy_data"].toArray();
    auto json_class_labels = jsonObject["class_labels"].toArray();
    auto json_confusionmatrix = jsonObject["confusionmatrix"].toArray();
    auto json_mostMisclassifiedImages = jsonObject["most_misclassified_images"].toArray();
    auto top1 = jsonObject["top1"].toDouble();
    auto top5 = jsonObject["top5"].toDouble();
    auto json_additionalResults = jsonObject["additionalResults"].toArray();

    QMap<int, QPair<double, double>> accuracy_data;
    for (const auto &value : json_accuracy_data) {
        auto obj = value.toObject();
        int iteration = obj["iteration"].toInt();
        int train = obj["train"].toInt();
        int validation = obj["validation"].toInt();

        accuracy_data[iteration] = qMakePair(train, validation);
    }

    QStringList class_labels;
    for (const auto &class_label : json_class_labels) {
        class_labels << class_label.toString();
    }

    QList<int> confusionmatrix;
    for (const auto &value : json_confusionmatrix) {
        confusionmatrix << value.toInt();
    }

    QStringList most_misclassified_images;
    for (const auto &imagePath : json_mostMisclassifiedImages) {
        most_misclassified_images << imagePath.toString();
    }

    QStringList additionalResults;
    for (const auto &resultPath : json_additionalResults) {
        additionalResults << resultPath.toString();
    }

    auto result = new TrainingResult(accuracy_data, class_labels, confusionmatrix, most_misclassified_images, top1,
                                     top5, additionalResults);
    slot_normal_loadTrainingResultData(view, result);
}

void ResultsProcessor::slot_comparison_loadTrainingResultGraphics(AbstractGraphicsView *receiver,
                                                                  const QString &runNameToCompare) {
    auto dirPath = ProjectManager::getInstance().getTrainingResultsDir();
    loadGraphicsInView(receiver, runNameToCompare, dirPath);
}

void ResultsProcessor::loadGraphicsInView(AbstractGraphicsView *receiver, const QString &resultsFolder,
                                          const QString &baseDir) {
    auto dir = QDir(baseDir);
    dir.cd(resultsFolder);

    for (const auto &file : dir.entryInfoList(QDir::Files, QDir::Time)) {
        for (int type = 0; type < _COUNT; type++) {
            auto regex = GRAPHICSTYPE2REGEX[type];
            auto match = regex.match(file.fileName());

            if (!match.hasMatch()) continue;

            auto identifier = match.captured(1);
            auto extension = match.captured(2);

            if (resultsFolder != identifier) continue;

            QGraphicsItem *graphics;
            if (extension == "svg")
                graphics = new QGraphicsSvgItem(file.absoluteFilePath());
            else
                graphics = new QGraphicsPixmapItem(file.absoluteFilePath());

            auto graphics_ptr = QSharedPointer<QGraphicsItem>(graphics);

            switch (type) {
                case CLASSIFICATION:
                    receiver->setClassificationGraphics(graphics_ptr);
                    break;
                case ACCURACYCURVE:
                    receiver->setAccuracyCurve(graphics_ptr);
                    break;
                case CONFUSIONMATRIX:
                    receiver->setConfusionMatrix(graphics_ptr);
                    break;
                case TOPACCURACIES:
                    receiver->setTopAccuraciesGraphics(graphics_ptr);
                    break;
                default:
                    qDebug() << "Attempted to set unknown result graphics type";
                    break;
            }

        }
    }
}

QJsonObject ResultsProcessor::readJSON(const QString &filepath) const {
    auto file = QFile(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Json file couldn't be opened/found";
    }

    QByteArray byteArray = file.readAll();
    file.close();

    //Format the content of the byteArray as QJsonDocument
    //and check on parse Errors
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
    }

    //Create a JSON object and fill it with the ByteArray content
    return jsonDoc.object();
}
