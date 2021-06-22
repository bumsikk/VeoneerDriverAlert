#include "htja_switch.h"


 Animation:: Animation(QObject* target, QObject* parent) : QVariantAnimation(parent) {
    setTargetObject(target);
}

 Animation::~ Animation() {
    stop();
}

QObject*  Animation::targetObject() const {
    return target.data();
}

void  Animation::setTargetObject(QObject* t) {
    if (target.data() == t)
        return;

    if (isRunning()) {
        return;
    }

    target = t;
}

void  Animation::updateCurrentValue(const QVariant& value) {
    Q_UNUSED(value);

    if (!target.isNull()) {
        auto update = QEvent(QEvent::StyleAnimationUpdate);
        update.setAccepted(false);
        QCoreApplication::sendEvent(target.data(), &update);
        if (!update.isAccepted())
            stop();
    }
}

void  Animation::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) {
    if (target.isNull() && oldState == Stopped) {
        return;
    }

    QVariantAnimation::updateState(newState, oldState);

    if (!endValue().isValid() && direction() == Forward) {
        qWarning("Animation::updateState (%s): starting an animation without end value", targetObject()->metaObject()->className());
    }
}

void  Animation::setup(int duration, QEasingCurve easing) {
    setDuration(duration);
    setEasingCurve(easing);
}

void  Animation::interpolate(const QVariant& _start, const QVariant& end) {
    setStartValue(_start);
    setEndValue(end);
    start();
}

void  Animation::setCurrentValue(const QVariant& value) {
    setStartValue(value);
    setEndValue(value);
    updateCurrentValue(currentValue());
}

QRect HtjaSwitch::indicatorRect() {
    const auto w = SlideMarg.left() + 36 + SlideMarg.right(); //36=height
    return ltr(this) ? QRect(0, 0, w, 36) : QRect(width() - w, 0, w, 36);
}

HtjaSwitch::HtjaSwitch( QWidget* parent) : QAbstractButton(parent) {
    btnAnimation = new  Animation{ this, this };
    btnPosition = new  Animation{ this, this };
    trackAnimation = new  Animation{ this, this };
    btnPosition->setup(SlideShow(Type::InOutQuad, 150).timeLength, SlideShow(Type::InOutQuad, 150).easing);
    trackAnimation->setup(SlideShow(Type::Linear, 150).timeLength, SlideShow(Type::Linear, 150).easing);
    btnAnimation->setup(SlideShow(Type::Linear, 150).timeLength, SlideShow(Type::Linear, 150).easing);

    trackAnimation->setStartValue(colorFromOpacity(Qt::gray, 1));
    trackAnimation->setEndValue(colorFromOpacity(Qt::gray, 1));
    btnAnimation->setStartValue(colorFromOpacity(QColor("#fafafa"), 1));
    btnAnimation->setEndValue(colorFromOpacity(QColor("#fafafa"), 1));

}

void HtjaSwitch::Htja_state(bool isActive){
    if(isActive == true)
        Toggle(1);
    else
        Toggle(0);
}


HtjaSwitch::~HtjaSwitch() {

}


void HtjaSwitch::paintEvent(QPaintEvent*) {

    QPainter p(this);

    const auto _indicatorRect = indicatorRect();
    auto trackMargin = QMargins(20, 8, 8, 8);
    trackMargin.setTop(trackMargin.top() + 2);
    trackMargin.setBottom(trackMargin.bottom() + 2);
    QRectF trackRect = _indicatorRect.marginsRemoved(trackMargin);

    p.setOpacity(1.0);
    p.setPen(Qt::NoPen);
    //the gray area
    p.setBrush(trackAnimation->currentValue().value<QColor>());
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawRoundedRect(trackRect, END_ARC, END_ARC);
    p.setRenderHint(QPainter::Antialiasing, false);
    //the switch circle
    trackRect.setX(trackRect.x() - trackMargin.left() - trackMargin.right() - 2 + btnPosition->currentValue().toInt());
    auto thumbRect = trackRect;

    if (!shadowPixmap.isNull())
        p.drawPixmap(thumbRect.center() - QPointF(RAD_BUTTON, RAD_BUTTON - 1.0), shadowPixmap);

    p.setBrush(btnAnimation->currentValue().value<QColor>());
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawEllipse(thumbRect.center(), RAD_BUTTON - GRAY_AREA - 1.0, RAD_BUTTON - GRAY_AREA - 1.0);
    p.setRenderHint(QPainter::Antialiasing, false);


    }

void HtjaSwitch::Toggle(bool state) {
    if (state == 1) {
        const QVariant posEnd = (SlideMarg.left() + SlideMarg.right() + 2) * 2;
        const QVariant trackEnd = colorFromOpacity(Qt::green, 1);

        btnPosition->setCurrentValue(posEnd);
        trackAnimation->setCurrentValue(trackEnd);

    }
    else {
        const QVariant posEnd = 0;
        const QVariant thumbEnd = colorFromOpacity(QColor("#fafafa"), 1);
        const QVariant trackEnd = colorFromOpacity(Qt::gray, 1);
        btnPosition->setCurrentValue(posEnd);
        btnAnimation->setCurrentValue(thumbEnd);
        trackAnimation->setCurrentValue(trackEnd);

    }
}
