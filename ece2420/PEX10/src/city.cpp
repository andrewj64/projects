#include <iostream>
#include <cstring>
#include <map>
#include <fstream>

#include "city.hpp"

City::City(std::string city)
    :m_city(city), m_dist(100000)
{

}

std::map<std::string, int>& City::getNeighbors()
{
    return m_neighbors;
}

void City::addCity(std::string dest, int dist)
{
    m_neighbors[dest] = dist;
}

std::string City::getCity()
{
    return m_city;
}

int City::getDist()
{
    return m_dist;
}

void City::setDist(int dist)
{
    m_dist = dist;
}

