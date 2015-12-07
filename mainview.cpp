#include "mainview.hpp"
#include "sortable.hpp"
#include "sortthread.hpp"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTime>
#include <QObject>
#include <QDebug>
#include <QGraphicsScene>
#include <QRectF>
#include <algorithm>
#include <functional>

MainView::MainView(QGraphicsScene* mainScene) : QGraphicsView{mainScene}
                                              ,	mainScene_{mainScene}
{
    qsrand(QTime::currentTime().msec());  	// initialize random generator

    init_stat();

    array_ = new Sortable[arraySize];
    sortThread = new SortThread(array_, arraySize, std::sort<Sortable*>);

    this->setFixedWidth(windowWidth);
    this->setFixedHeight(windowHeight);
    for (auto i = 0; i < arraySize; ++i) {
        array_[i] = (qreal) qrand() / RAND_MAX;  //  0 < value < 1

        // adds the graphic Rectangle Items to the Scene, then saves the pointers in the array objects
        QGraphicsRectItem* columnRect = mainScene_->addRect(i*shift, windowHeight-array_[i]*windowHeight,
                                                columnWidth, array_[i]*windowHeight);
        array_[i].set_columnRect(columnRect);

        // whenever operatorEQ signal is emitted, the changeColumnHeight changes the array object's
        // corresponding graphic (rect) item's height
        QObject::connect(&array_[i], SIGNAL(operatorEQ(QGraphicsRectItem*,qreal)),
                         this, SLOT(assign_slot(QGraphicsRectItem*,qreal)));
        QObject::connect(&array_[i], SIGNAL(operatorCOMP(QGraphicsRectItem*,QGraphicsRectItem*)),
                         this, SLOT(comp_slot(QGraphicsRectItem*,QGraphicsRectItem*)));
    }
    this->show();

    QObject::connect(sortThread, SIGNAL(end_of_run()), this, SLOT(ending_slot()));
    sortThread->start();
}

void MainView::init_stat() {
    stat_ = new Statistics{mainScene_->addText("Number of comparisons: "), mainScene_->addText("0"),
                           mainScene_->addText("Number of assignments: "), mainScene_->addText("0")};
}

MainView::Statistics::Statistics(QGraphicsTextItem* compText, QGraphicsTextItem* compNum,
                           QGraphicsTextItem* assignText, QGraphicsTextItem* assignNum) :
                           comp_text{compText}, comp_number{compNum}, comp_count{0},
                           assign_text{assignText}, assign_number{assignNum}, assign_count{0}
{
    comp_text->setPos(0,0);
    comp_number->setPos(comp_text->boundingRect().width(), 0);
    assign_text->setPos(0, comp_text->boundingRect().height());
    assign_number->setPos(assign_text->boundingRect().width(), comp_number->boundingRect().height());
}

void MainView::Statistics::plus_comp() {
    comp_count++;
    comp_number->setPlainText(QString::number(comp_count));
}

void MainView::Statistics::plus_assign() {
    assign_count++;
    assign_number->setPlainText(QString::number(assign_count));
}

MainView::~MainView()
{
    while (sortThread->isRunning())
        ;
    delete sortThread;
    delete[] array_;
}

void MainView::assign_slot(QGraphicsRectItem* item, qreal relativeHeight)
{
   filler.clearFill();
   qreal newHeight = relativeHeight * windowHeight;
   qreal x = item->rect().x();
   qreal y = windowHeight - newHeight;
   qreal width = columnWidth;
   item->setRect(x, y, width, newHeight);
   filler.fillItem(item, Qt::green);
   stat_->plus_assign();
}

void MainView::comp_slot(QGraphicsRectItem* item1, QGraphicsRectItem* item2)
{
    filler.clearFill();
    filler.fillItem(item1, Qt::red);
    filler.fillItem(item2, Qt::red);
    stat_->plus_comp();
}

void MainView::ending_slot()
{
   filler.clearFill();
}


