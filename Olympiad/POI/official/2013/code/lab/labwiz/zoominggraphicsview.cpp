#include "zoominggraphicsview.h"

ZoomingGraphicsView::ZoomingGraphicsView(QLabel *pos, QWidget *parent) :
    QGraphicsView(parent), position(pos), last_dot(NULL), track_mouse(false)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    scale(1, -1);
    scale(20, 20);
    setMouseTracking(true);
    setCenter(QPointF(0, 0));
}

void ZoomingGraphicsView::setTrackMouse(bool new_state)
{
    track_mouse = new_state;
    if (!new_state) {
        position->setText("");
        deleteDot();
    }
}

void ZoomingGraphicsView::deleteDot()
{
    if (last_dot != NULL) {
        scene()->removeItem(last_dot);
        delete last_dot;
        last_dot = NULL;
    }
}

void ZoomingGraphicsView::drawDot(QPoint pos)
{
    deleteDot();
    double radius = 0.5;
    QList<QGraphicsItem *> items;
    QPen pen(Qt::red);
    pen.setWidth(2);
    pen.setCosmetic(true);
    items.push_back(scene()->addLine(pos.x()-radius, pos.y(), pos.x()+radius, pos.y(), pen));
    items.push_back(scene()->addLine(pos.x(), pos.y()-radius, pos.x(), pos.y()+radius, pen));
    last_dot = scene()->createItemGroup(items);
}

void ZoomingGraphicsView::wheelEvent(QWheelEvent *event)
{
    QPointF screenCenter = center;
    QPointF pointBeforeScale(mapToScene(event->pos()));
    double scaleFactor = 1.15;
    if (event->delta() > 0) {
        scale(scaleFactor, scaleFactor);
    } else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
    QPointF pointAfterScale(mapToScene(event->pos()));
    QPointF offset = pointBeforeScale - pointAfterScale;
    QPointF newCenter = screenCenter + offset;
    setCenter(newCenter);
}

void ZoomingGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (!last_pan_point.isNull()) {
        QPointF delta = mapToScene(last_pan_point) - mapToScene(event->pos());
        last_pan_point = event->pos();
        setCenter(center + delta);
    }

    if (!track_mouse) {
        return;
    }
    QPointF pos = mapToScene(event->pos());
    QPoint fixed_pos(qRound(pos.x()), qRound(pos.y()));
    position->setText("Mysz: " + QString::number(fixed_pos.x()) + ", " + QString::number(fixed_pos.y()));
    drawDot(fixed_pos);
}

void ZoomingGraphicsView::mousePressEvent(QMouseEvent *event)
{
    last_pan_point = event->pos();
}

void ZoomingGraphicsView::setCenter(QPointF center)
{
    this->center = center;
    centerOn(this->center);
}

void ZoomingGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    last_pan_point = QPoint();
}

void ZoomingGraphicsView::resizeEvent(QResizeEvent *event)
{
    QRectF visibleArea = mapToScene(rect()).boundingRect();
    setCenter(visibleArea.center());
    QGraphicsView::resizeEvent(event);
}
