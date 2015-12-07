#ifndef SORTTHREAD
#define SORTTHREAD
#include <QThread>
#include <functional>
#include <algorithm>
#include "sortable.hpp"


// A thread which sorts the Sortable array with the sorting function provided in ctor
class SortThread : public QThread {
    Q_OBJECT
public:
    using sortFuncType = std::function<void(Sortable*,Sortable*)>;
private:
    Sortable *array_;
    unsigned long arraysize_;
    sortFuncType sortfunc_;
public:
    SortThread(Sortable *array, unsigned long arraysize, sortFuncType func) :
                    array_{array}, arraysize_{arraysize}, sortfunc_{func}
                    {}
    virtual void run() override {
        sortfunc_(array_, array_+arraysize_);
        emit end_of_run();
    }
signals:
    void end_of_run();
};

#endif // SORTTHREAD

