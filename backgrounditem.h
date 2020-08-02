#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPoint>

class BackgroundItem : public QGraphicsPixmapItem
{
public:
    /// Constructor
    explicit BackgroundItem(const QPixmap &pixmap, QPointF pos = QPointF(0.0,0.0),
                            qreal offset = 0.0, qreal zVal = 0, QGraphicsItem* parent = 0);
    /// Empty QPainterPath to prevent Qt from detecting collisions
    virtual QPainterPath shape() const;

    //  [Graphics]
    /// Read the current Position used to update Graphics
    QPointF getPos();
    /// Read the items parallax offset
    qreal getOffset();

private:
    /// start Position
    QPointF origPos;
    /// Amount of Parallax offset
    qreal parOffset;
};

#endif // BACKGROUNDITEM_H
