#ifndef HTJA_STYLE_H
#define HTJA_STYLE_H

//#include <QtCore/qeasingcurve.h>
//#include <qpainter.h>


//Q_DECL_IMPORT void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);

//namespace Style {

//    using Type = QEasingCurve::Type;

//    struct Animation {
//        Animation() = default;
//        Animation(Type _easing, int _duration) :easing{ _easing }, duration{ _duration } {

//        }

//        Type easing;
//        int duration;
//    };

//    struct Switch {

//    };

//    inline QPixmap drawShadowEllipse(qreal radius, qreal elevation, const QColor& color) {
//        auto px = QPixmap(radius * 2, radius * 2);
//        px.fill(Qt::transparent);

//        { // draw ellipes
//            QPainter p(&px);
//            p.setBrush(color);
//            p.setRenderHint(QPainter::Antialiasing, true);
//            p.drawEllipse(QRectF(0, 0, px.size().width(), px.size().height()).center(), radius - elevation, radius - elevation);
//        }

//        QImage tmp(px.size(), QImage::Format_ARGB32_Premultiplied);
//        tmp.setDevicePixelRatio(px.devicePixelRatioF());
//        tmp.fill(0);
//        QPainter tmpPainter(&tmp);
//        tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
//        tmpPainter.drawPixmap(QPointF(), px);
//        tmpPainter.end();

//        // blur the alpha channel
//        QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
//        blurred.setDevicePixelRatio(px.devicePixelRatioF());
//        blurred.fill(0);
//        {
//            QPainter blurPainter(&blurred);
//            qt_blurImage(&blurPainter, tmp, elevation * 4., true, false);
//        }

//        tmp = blurred;

//        return QPixmap::fromImage(tmp);
//    }

//} // namespace Style

#endif // HTJA_STYLE_H