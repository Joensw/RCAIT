/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QINPUTCONTROL_P_H
#define QINPUTCONTROL_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qobject.h>
#include <qtguiglobal.h>

QT_BEGIN_NAMESPACE

class QKeyEvent;

/**
 * @brief Class required for key controls in tags fields.
 */
class Q_GUI_EXPORT QInputControl : public QObject {
Q_OBJECT
public:
    /**
     * @brief Edit types.
     */
    enum Type {
        LineEdit,
        TextEdit
    };

    /**
     * @brief Default constructor.
     * @param type Either LineEdit or TextEdit.
     * @param parent QObject parent object
     */
    explicit QInputControl(Type type, QObject *parent = nullptr);

    /**
     * @brief Check if the key event is accepted
     * @param event QKeyEvent
     * @return accepted or not
     */
    bool isAcceptableInput(const QKeyEvent *event) const;

    /**
     * @brief Check if the key event is a text edit shortcut
     * @param ke key event
     * @return accepted or not
     */
    static bool isCommonTextEditShortcut(const QKeyEvent *ke);

protected:
    /**
     * @brief Protected constructor.
     * @param type Either LineEdit or TextEdit.
     * @param dd QObjectPrivate object
     * @param parent QObject parent
     */
    explicit QInputControl(Type type, QObjectPrivate &dd, QObject *parent = nullptr);

private:
    const Type m_type;
};

QT_END_NAMESPACE

#endif // QINPUTCONTROL_P_H
