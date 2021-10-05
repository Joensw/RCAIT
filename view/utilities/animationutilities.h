#ifndef ANIMATIONUTILITIES_H
#define ANIMATIONUTILITIES_H

#include <QLabel>
#include <QString>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSharedPointer>

/**
 * @brief The AnimationUtilities class is a utility class for settings text in labels with extra animations and modifications
 */
class AnimationUtilities {

private:
    AnimationUtilities() = default;

    static constexpr auto OPACITY_PROPERTY = "opacity";
    static constexpr auto FADE_IN_TIME = 1000;
    static constexpr auto START_OPACITY = 0;
    static constexpr auto END_OPACITY = 1;

public:

    /**
     * @brief setTextWithAnimation sets the text of a label with a short appearance animation
     * @param label label for which the text should be set
     * @param message message to be displayed
     */
    static void setTextWithAnimation(QLabel *label, const QString &message) {
        auto *effect = new QGraphicsOpacityEffect();
        //if a QObject has an effect installed, and gets a new one installed the existing one will be deleted
        label->setGraphicsEffect(effect);
        auto *anim = new QPropertyAnimation(effect, OPACITY_PROPERTY);
        anim->setDuration(FADE_IN_TIME);
        anim->setStartValue(START_OPACITY);
        anim->setEndValue(END_OPACITY);
        anim->setEasingCurve(QEasingCurve::OutQuad);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
        label->setText(message);
    }
};

#endif // ANIMATIONUTILITIES_H
