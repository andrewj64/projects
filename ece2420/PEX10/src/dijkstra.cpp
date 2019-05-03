#include <iostream>
#include <map>
#include <algorithm>
#include "dijkstra.hpp"
#include "city.hpp"

Dijkstra::Dijkstra()
    : m_total(0)
{
}

void Dijkstra::insert(std::string city, std::string dest, int dist)
{
    //does this city already exist in the Dijkstra object
    if (masterMap.find(city) == masterMap.end())
    {
        //construct our city
        City c(city);
        masterMap[city] = c;
    }
    //add this connection to the city
    masterMap[city].addCity(dest, dist); // add to neighbors map
    unvisited[city] = 100000;
}

bool Dijkstra::isVisited(std::string name)
{
    if (unvisited.find(name) == unvisited.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
    •While unvisited not empty
    •Select minimum unvisited
    •Remove from unvisited
    •For each unvisited neighbor
        •Calculate distance to neighbor through this node
        •If distance lower than current distance, reset distance
        •Track previous node that led to new minimum
    •From end follow previous nodes to enumerate a minimal path
    
*/

void Dijkstra::algorithm(std::string start, std::string end)
{

    // check if there is tn't a path

    int dist = 100000;
    int distFromRoot = 100000;
    int total = 0;
    std::string curCity = start;

#if 1
    // set all distances to infinity
    unvisited[start] = 0;
    masterMap[start].setDist(0);
    
    // while unvisited is not empty
    while (unvisited.size())
    {
        // find minimum unvisited
        distFromRoot = 100000;
        for (auto it = unvisited.begin(); it != unvisited.end(); it++)
        {
            if (masterMap[it->first].getDist() < distFromRoot)
            {
                distFromRoot = masterMap[it->first].getDist();
                curCity = it->first;
            }
        }

        // for each unvisited neighbor
        auto neighbors = masterMap[curCity].getNeighbors();
        for (auto it = neighbors.begin(); it != neighbors.end(); it++)
        {
            std::string name = it->first;
            if (!isVisited(name))
            {
                // calculate distance from start
                dist = it->second + unvisited[curCity];
                if (dist < unvisited[name])
                {
                    // populate respecitive maps
                    unvisited[name] = dist;
                    visited[name] = dist;
                    path[name] = curCity;
                    masterMap[name].setDist(dist);
                }
            }
            unvisited.erase(curCity);
            m_total = dist;
        }
    }

#endif
}

void Dijkstra::print()
{
    if (unvisited.size())
    {
        std::cout << "Cities are not reachable!" << std::endl;
    }
    for (auto it = visited.begin(); it != visited.end(); it++)
    {
        std::cout << path[it->first] << std::endl;
    }
    std::cout << "Total Distance: " << m_total << std::endl;
}
