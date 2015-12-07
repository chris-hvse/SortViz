#include "sortable.hpp"
#include <QThread>

Sortable::Sortable() : value_{0}, columnRect_{nullptr} {}

Sortable::Sortable(Sortable&& other)
{
    value_ = std::move(other.value_);
}

Sortable& Sortable::operator=(Sortable&& other)
{
    value_ = other.value_;
    emit operatorEQ(columnRect_, value_);
    QThread::currentThread()->msleep(sleepTime);
    return *this;
}

bool Sortable::operator<(const Sortable& other) {
    emit operatorCOMP(this->columnRect_, other.columnRect_);
    QThread::currentThread()->msleep(sleepTime);
    return this->value_ < other.value_;
}

Sortable& Sortable::operator=(qreal val)
{
    value_ = val;
    return *this;
}
