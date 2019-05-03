#ifndef DERIVEDHEAD_HPP
#define DERIVEDHEAD_HPP

#include <functional>
#include <memory>
#include <vector>
#include <iostream>
#include <mutex>
#include "Head.hpp"

class DerivedHead : public Head
{
public:
    DerivedHead(bool last);
    void setNeighbors(std::shared_ptr<DerivedHead> right);
    void execute(std::function<void()> action);
private:
    std::mutex mtx;
    std::weak_ptr<DerivedHead> pRight;
    bool mLast;
};
 
#endif