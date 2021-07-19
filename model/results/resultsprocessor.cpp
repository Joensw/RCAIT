#include "resultsprocessor.h"

ResultsProcessor::ResultsProcessor() {
    //TODO Create identifier utility class which creates date/time identifier statically
    m_topAccuraciesGraphics = new TopAccuraciesGraphics("TODO");
}

void ResultsProcessor::slot_generateTopAccuraciesGraphics(AbstractGraphicsView *receiver) {
    m_topAccuraciesGraphics->generateGraphics(receiver);
}

void ResultsProcessor::slot_addedRow_topAccuraciesTable(const QString &identifier, double top1, double top5) {
    m_topAccuraciesGraphics->addDataRow(identifier, top1, top5);
}

void ResultsProcessor::slot_removedRow_topAccuraciesTable(const QString &identifier) {
    m_topAccuraciesGraphics->removeDataRow(identifier);
}
