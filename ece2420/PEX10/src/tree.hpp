#ifndef CITY_H
#define CITY_H
#include <iostream>
#include "path.hpp"

class City
{
public:
    City(std::string city, std::string dest, int dist);
    //getDist(std::string )
    //path dijkstra(string start, string end);
    // void insert(string start, string end, int weight);
private:
    //std::map<std::string, std::map<std::string, int>> masterMap;
    std::map<std::string, int> m_neighbors;
    int m_dist;
    std::string m_city;
    std::string m_dest;
    bool m_visited;
};



#endif