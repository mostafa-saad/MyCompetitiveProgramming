#ifndef ZOOMINGGRAPHICSVIEW_H
#define ZOOMINGGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QLabel>
#include <QGraphicsItemGroup>

class ZoomingGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ZoomingGraphicsView(QLabel *pos, QWidget *parent = 0);
    void setTrackMouse(bool);
    void deleteDot();
    void drawDot(QPoint pos);
    
signals:
    
public slots:
    
protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
private:
    QLabel *position;
    QGraphicsItemGroup *last_dot;
    bool track_mouse;
    QPoint last_pan_point;
    void setCenter(QPointF center);
    QPointF center;
};

#endif // ZOOMINGGRAPHICSVIEW_H
