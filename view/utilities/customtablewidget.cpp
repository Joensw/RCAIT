#include "customtablewidget.h"

CustomTableWidget::CustomTableWidget(QWidget *parent) : QTableWidget(parent) {
    auto *cornerButton = getCornerButton();
    if (cornerButton)
        cornerButton->installEventFilter(this);

    // Add full touch compliance
    this->setAttribute(Qt::WA_AcceptTouchEvents,true);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    QScroller::grabGesture(this,QScroller::TouchGesture);
}

QAbstractButton *CustomTableWidget::getCornerButton() {
    return findChild<QAbstractButton *>();
}

/*!\reimp
*/
bool CustomTableWidget::eventFilter(QObject *o, QEvent *e) {
    //Pass call to parent
    if (e->type() != QEvent::Paint) return QTableWidget::eventFilter(o, e);

    //This is the right event, so try to get the button
    auto *button = qobject_cast<QAbstractButton *>(o);
    if (!button) return false;

    QStyleOptionHeader opt;
    opt.initFrom(button);
    QStyle::State state = QStyle::State_None;
    if (button->isEnabled())
        state |= QStyle::State_Enabled;
    if (button->isActiveWindow())
        state |= QStyle::State_Active;
    if (button->isDown())
        state |= QStyle::State_Sunken;
    opt.state = state;
    opt.rect = button->rect();

    //Painting icon and text, only difference to Qt's implementation
    opt.icon = button->icon();
    opt.text = button->text();
    if (opt.text.isEmpty()){
        //Center icon iff there is no text
        opt.iconAlignment = Qt::AlignHCenter | Qt::AlignVCenter;
    }

    //Draw the button
    opt.position = QStyleOptionHeader::OnlyOneSection;
    QStylePainter painter(button);
    painter.drawControl(QStyle::CE_Header, opt);
    //Finish event
    return true;
}

int CustomTableWidget::addTableRow(const QString &identifier, const QStringList &data) {
    int row = rowCount();
    insertRow(row);
    m_data[identifier] = data;

    //Fill table row
    auto identifierItem = new QTableWidgetItem(identifier);

    int col = 0;
    for (const auto &value : data) {
        auto item = new QTableWidgetItem(value);
        item->setTextAlignment(Qt::AlignCenter);
        setVerticalHeaderItem(row, identifierItem);
        setItem(row, col++, item);
    }
    return row;
}

bool CustomTableWidget::removeTableRow(const QString &identifier) {
    for (int i = 0; i < rowCount(); i++) {
        if (verticalHeaderItem(i)->text() == identifier) {
            removeRow(i);
            m_data.remove(identifier);
            return true;
        }
    }
    return false;
}

QTableWidgetItem *CustomTableWidget::operator()(int row, int column) const{
    return this->at(row, column);
}

QTableWidgetItem *CustomTableWidget::at(int row, int column) const {
    Q_ASSERT(row >= 0 && row < rowCount() && column >= 0 && column < columnCount());
    return item(row, column);
}
