#ifndef ANIMATIONUTILITIES_H
#define ANIMATIONUTILITIES_H

#include <QLabel>
#include <QString>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSharedPointer>

/**
 * @brief The AnimationUtilities class Is a utility class for settings text in labels with extra animations and modifications
 */
class  AnimationUtilities {

private:
    AnimationUtilities();

    static auto constexpr OPACITY_PROPERTY = "opacity";
    static constexpr int FADE_IN_TIME = 1000;
    static constexpr int START_OPACITY = 0;
    static constexpr int END_OPACITY = 1;

public:

    /**
     * @brief setTextWithAnimation sets the text of a label with a short appearance animation
     * @param label label for which the text should be set
     * @param message message to be displayed
     */
    static void setTextWithAnimation(QLabel *label, const QString &message)
    {
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
        //if a QObject has a effect installed, and gets a new one installed the existing one will be deleted
        label->setGraphicsEffect(effect);
        QPropertyAnimation *anim = new QPropertyAnimation(effect, OPACITY_PROPERTY);
        anim->setDuration(FADE_IN_TIME);
        anim->setStartValue(START_OPACITY);
        anim->setEndValue(END_OPACITY);
        anim->setEasingCurve(QEasingCurve::OutQuad);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
        label->setText(message);
    }
};

#endif // ANIMATIONUTILITIES_H
