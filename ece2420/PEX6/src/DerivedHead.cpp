#include <functional>
#include <memory>
#include <vector>
#include <iostream>
#include <memory>
#include "DerivedHead.hpp"

DerivedHead::DerivedHead(bool last) //correct args
{
    mLast = last;
}

void DerivedHead::setNeighbors(std::shared_ptr<DerivedHead> right)
{
    //pLeft = left;
    pRight = right;
}

void DerivedHead::execute(std::function<void()> action)
{
    //auto left = pLeft.lock();
    auto right = pRight.lock();

    if(mLast && right->mLast)
    {
        action();
        return;
    }
        

    //lock left
    //lock right
    if(mLast)
    {
        right->mtx.lock();
        mtx.lock();
    }
    else
    {
        mtx.lock();
        right->mtx.lock();
    }

    //execute
    action();
    //unlock both
    mtx.unlock();
    right->mtx.unlock();
}