#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include <QGraphicsItem>
#include <QPixmap>

class BackgroundItem : public QGraphicsPixmapItem
{
public:
    explicit BackgroundItem(const QPixmap &pixmap, QGraphicsItem* parent = 0);

    virtual QPainterPath shape() const;
};

#endif // BACKGROUNDITEM_H
