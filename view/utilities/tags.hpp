/*
  MIT License

  Copyright (c) 2019 Nicolai Trandafil

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/*
Mehrere Veränderungen für dieses PSE, wie
- Adaption an Qt6
- Anpassung an C++ 17
- Bugfix wegen geringer Auflösung
- Änderung der Texturen
Quelle des Originals: https://github.com/nicktrandafil/tags
*/

#pragma once

#include <QWidget>

#include <memory>
#include <vector>

class QStyleOptionFrame;

/**
 * @brief Tag editor widget
 * Enter` commits a tag and initiates a new tag edition
 */
class Tags : public QWidget {
Q_OBJECT

public:
    /**
     * @brief Default constructor.
     * @param parent QObject parent object
     */
    [[maybe_unused]] explicit Tags(QWidget *parent = nullptr);

    ~Tags() override;

    /**
     * @brief Size hint, common for QWidgets
     * @return QSize to be used
     */
    [[nodiscard]] QSize sizeHint() const override;

    /**
     * @brief Size hint, common for QWidgets
     * @return QSize to be used
     */
    [[nodiscard]] QSize minimumSizeHint() const override;

    /**
     * @brief Set a list of strings used to autocomplete the input tags
     * @param completions
     */
    void completion(std::vector<QString> const &completions);

    /**
     * @brief Set the current tags, replaces old ones
     * @param tags vector of new tags
     */
    void tags(std::vector<QString> const &tags);

    /**
     * @brief Get the current tags
     * @return vector of tags
     */
    [[nodiscard]] std::vector<QString> tags() const;

signals:

    /**
     * @brief Emitted whenever a tag is edited
     */
    void tagsEdited();

protected:
    /**
     * @brief Paint event for widget
     * @param event paint event
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Timer event for widget
     * @param event timer event
     */
    void timerEvent(QTimerEvent *event) override;

    /**
     * @brief Mouse press event for widget
     * @param event mouse event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Resize event for widget
     * @param event resize event
     */
    void resizeEvent(QResizeEvent *event) override;

    /**
     * @brief Focus in event for widget
     * @param event focus in event
     */
    void focusInEvent(QFocusEvent *event) override;

    /**
     * @brief Focus out event for widget
     * @param event focus out event
     */
    void focusOutEvent(QFocusEvent *event) override;

    /**
     * @brief Key press event for widget
     * @param event key press event
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Mouse move event for widget
     * @param event mouse move event
     */
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
