#ifndef HTJA_SWITCH_H
#define HTJA_SWITCH_H

#include <QtWidgets>
#include <QtCore/qeasingcurve.h>
#include <qpainter.h>

using Type = QEasingCurve::Type;
struct SlideShow {
   SlideShow() = default;
   SlideShow(Type e, int d) :easing{ e }, timeLength{ d } {}

    Type easing;
    int timeLength;
};

class  Animation final : public QVariantAnimation {
    Q_OBJECT
    Q_PROPERTY(QObject* targetObject READ targetObject WRITE setTargetObject)

  public:
     Animation(QObject* target, QObject* parent = nullptr);
    ~ Animation() override;

    QObject* targetObject() const;
    void setTargetObject(QObject* target);

    inline bool isRunning() const {
        return state() == Running;
    }

  public slots:
    void setup(int duration, QEasingCurve easing = QEasingCurve::Linear);
    void interpolate(const QVariant& start, const QVariant& end);
    void setCurrentValue(const QVariant&);

  protected:
    void updateCurrentValue(const QVariant& value) override final;
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) override final;

  private:
    QPointer<QObject> target;
};



class HtjaSwitch final : public QAbstractButton  {
    Q_OBJECT

    const double END_ARC = 8.0; //for the shadow height
    const double RAD_BUTTON = 14.5; //for button circle radius
    const double GRAY_AREA = 2.0;

  public:
    explicit HtjaSwitch( QWidget* parent = nullptr);
    ~HtjaSwitch();
    void Htja_state(bool isActive);


  protected:
    void paintEvent(QPaintEvent*);
    void Toggle(bool active);

    void init();
    QRect indicatorRect();

    static inline QColor colorFromOpacity(const QColor& c, qreal opacity) {
        return QColor(c.red(), c.green(), c.blue(), qRound(opacity * 255.0));
    }
    static inline bool ltr(QWidget* w) {
        if (nullptr != w)
            return w->layoutDirection() == Qt::LeftToRight;

        return false;
    }

  private:
    QPixmap shadowPixmap;
    QPointer< Animation> btnPosition;
    QPointer< Animation> btnAnimation;
    QPointer< Animation> trackAnimation;
    QMargins SlideMarg = QMargins(20, 8, 8, 8);

};

#endif // HTJA_SWITCH_H
