/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
class QPaintEvent;

class QResizeEvent;

class QSize;

class QWidget;

QT_END_NAMESPACE

class LineNumberArea;

/**
 * @brief This class is used for displaying code files in a widget with line numbering
 * as well as formatting support.
 */
class CodeEditor : public QPlainTextEdit {
Q_OBJECT

public:
    /**
     * @brief Constructs a CodeEditor
     * @param parent parent widget (optional)
     */
    explicit CodeEditor(QWidget *parent = nullptr);

    /**
     * @brief Triggered when a line number has to be painted.
     * @param event incoming paint event
     */
    void lineNumberAreaPaintEvent(QPaintEvent *event);

    /**
     * @brief Gets the width of the line number area.
     * @return width of the line number area as an int.
     */
    int lineNumberAreaWidth();

    /**
     * @brief Appends a placeholder line and marks it as such.
     * Can be empty as well.
     * @param placeholder string to be inserted in the placeholder line (default empty)
     */
    void appendPlaceholder(const QString &placeholder = {});

    /**
     * @brief Completely resets the code editor widget.
     */
    void reset();

protected:
    /**
     * @brief Triggered when the widget was resized. Rescales its contents then.
     * @param event incoming resize event
     */
    void resizeEvent(QResizeEvent *event) override;

private slots:

    void updateLineNumberAreaWidth(int newBlockCount);

    void updateLineNumberArea(const QRect &rect, int dy);

private:
    using QPlainTextEdit::clear;

    QWidget *lineNumberArea;
    QSet<int> m_placeholderLines;

    static constexpr QColor BACKGROUND = QColorConstants::Svg::gainsboro;
    static constexpr QColor SEPARATOR = QColorConstants::Svg::darkgrey;
};

/**
 * @brief Helper class for the line numbers in a CodeEditor.
 */
class LineNumberArea : public QWidget {
public:
    /**
     * @brief Constructs a LineNumberArea
     * @param editor code editor to put line numbers on
     */
    explicit LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor) {}

    /**
     * @brief Gets a size hint used to calculate the painting area size.
     * @return size as a QSize object
     */
    [[nodiscard]] QSize sizeHint() const override {
        return {codeEditor->lineNumberAreaWidth(), 0};
    }

protected:
    /**
     * @brief Triggered when repainting of the line numbers is necessary,
     * for example after scrolling.
     * @param event incoming paint event
     */
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};
#endif
