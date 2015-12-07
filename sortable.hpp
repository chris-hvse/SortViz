#ifndef SORTABLE_HPP
#define SORTABLE_HPP
#include <QGraphicsRectItem>
#include <QObject>

/* These objects send signals to the graphicsView when operator>(const Sortable&) or
 * operator=(Sortable&&) called on them. The code in the receiving slots (in the GraphicsView)
 * handles the repainting of the according columns in the scene
*/

class Sortable : public QObject {
    Q_OBJECT
private:
    const int sleepTime = 500; // ms
    qreal value_;
//  the rectangle in the graphicsScene which represents the value of this object
    QGraphicsRectItem* columnRect_;

public:
    Sortable();
    ~Sortable() {}
    Sortable(Sortable&&);
    Sortable& operator=(Sortable&&);
    Sortable& operator=(qreal);
    bool operator<(const Sortable&);
    operator qreal(){ return value_; }
    void set_columnRect(QGraphicsRectItem* columnRect) { columnRect_ = columnRect; }
    QGraphicsRectItem* get_columnRect() const { return columnRect_; }

signals:
    void operatorCOMP(QGraphicsRectItem* item1, QGraphicsRectItem* item2);
    void operatorEQ(QGraphicsRectItem* item, qreal val);
};

#endif // SORTABLE_HPP
