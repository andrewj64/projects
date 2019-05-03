#include <functional>
#include <memory>
#include <vector>
#include <iostream>
#include "Head.hpp"
#include "DerivedHead.hpp"

Head::Head()
{
    //std::cout << "This is useless" << std::endl;
}

std::vector<std::shared_ptr<Head>> Head::makePlatter(int numHeads)
{
    std::vector<std::shared_ptr<DerivedHead>> platter;

    //create vector of heads
    for (int i = 0; i < numHeads; i++)              
    {
        bool last = (numHeads - 1 == i);
        std::shared_ptr<DerivedHead> pDHead(new DerivedHead(last));
        platter.push_back(pDHead);
    }

    // define left and right neighbors for critical section protection
    int right;
    for (int i = 0; i < numHeads; i++)
    {
        right = (i + 1) % platter.size();
        platter[i]->setNeighbors(platter[right]);
    }

    //initialize head vector to return
    std::vector<std::shared_ptr<Head>> headVec;
    for (int i = 0; i < numHeads; i++)
    {
        headVec.push_back(platter[i]);
    }
    return headVec;
}