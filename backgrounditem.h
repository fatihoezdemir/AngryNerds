#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPoint>

class BackgroundItem : public QGraphicsPixmapItem
{
public:
    explicit BackgroundItem(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0),
                            qreal offset = 0.0, qreal zVal = 0, QGraphicsItem* parent = 0);

    virtual QPainterPath shape() const;

    QPointF getPos();
    qreal getOffset();
private:
    QPointF origPos;
    qreal parOffset;
};

#endif // BACKGROUNDITEM_H
