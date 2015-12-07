#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "sortable.hpp"
#include "sortthread.hpp"
#include <array>
#include "rectfiller.hpp"

/*
 * The view that visualizes the whole scene (QGraphicsScene).
 *
*/
class MainView : public QGraphicsView
{
    Q_OBJECT
private:
    enum {
        windowWidth = 1100,
        windowHeight = 500,
        padding = 2,
        arraySize = 200
    };
    // for calculating the bottomleft position of the columns
    const qreal shift = windowWidth / arraySize;
    const qreal columnWidth = shift-padding;

    // the scene to draw
    QGraphicsScene* mainScene_;
    // the thread that runs the sorting
    SortThread* sortThread;
    // the array to be sorted
    Sortable* array_;

    RectFiller filler;

    struct Statistics {
        Statistics(QGraphicsTextItem*, QGraphicsTextItem*, QGraphicsTextItem*, QGraphicsTextItem*);
        QGraphicsTextItem* comp_text;
        QGraphicsTextItem* comp_number;
        int comp_count;
        QGraphicsTextItem* assign_text;
        QGraphicsTextItem* assign_number;
        int assign_count;
        void plus_comp();
        void plus_assign();
};
    Statistics* stat_;
    void init_stat();

public:
    MainView(QGraphicsScene*);
    ~MainView();
public slots:
    // changes the rectangle item's height in the GraphicsScene. 0 < relativeHeight < maximumHeight ( = windowHeight)
    void assign_slot(QGraphicsRectItem* item, qreal relativeHeight);
    void comp_slot(QGraphicsRectItem* item1, QGraphicsRectItem* item2);
    void ending_slot();
};
#endif // MAINVIEW_HPP

