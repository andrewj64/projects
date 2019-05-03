#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <iostream>
#include <map>
#include <vector>
#include "city.hpp"

class Dijkstra
{
public:
    Dijkstra();
    void insert(std::string city, std::string dest, int dist);
    void algorithm(std::string start, std::string end);
    bool isVisited(std::string name);

    void print();
private:
    std::map<std::string, City> masterMap;
    std::map<std::string, std::string> path;
    std::map<std::string, int> unvisited;
    std::map<std::string, int> visited;
    int m_total;
    
};

#endif