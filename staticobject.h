#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPoint>

class staticObject : public QGraphicsPixmapItem
{
public:
    explicit staticObject(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0), QGraphicsItem* parent = nullptr);

    QPointF getPos();
    qreal getOffset();

    virtual QPainterPath shape() const; // will be removed

    void setOrigPos(QPointF pos);
private:
    QPointF origPos;

};

#endif // STATICOBJECT_H
