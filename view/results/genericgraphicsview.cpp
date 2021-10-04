#include <genericgraphicsview.h>

GenericGraphicsView::GenericGraphicsView(SavableResultsWidget *tabWidget, QWidget *parent)
        : QWidget(parent),
          m_tabWidget(tabWidget) {

};

void GenericGraphicsView::setSaved(const bool &isSaved) {
    m_isSaved = isSaved;
    if (m_tabWidget)
        m_tabWidget->updateSaveState(this);
}

void GenericGraphicsView::setName(const QString &name) {
    m_name = name;
}

bool GenericGraphicsView::isSaved() const {
    return m_isSaved;
}

const QString &GenericGraphicsView::getName() const {
    return m_name;
}

