#pragma once

#include <QLabel>

class AspectRatioLabel : public QLabel
{
public:
    explicit AspectRatioLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~AspectRatioLabel() override;

public slots:

    [[maybe_unused]] void setPixmap(const QPixmap& pm);

protected:
    [[maybe_unused]] void resizeEvent(QResizeEvent* event) override;

private:
    void updateMargins();

    int pixmapWidth = 0;
    int pixmapHeight = 0;
};
