#ifndef CITY_H
#define CITY_H
#include <iostream>
#include <map>

class City
{
public:
    City(std::string city);
    City(){}
    void addCity(std::string dest, int dist);
    std::string getCity();
    std::string getDest();
    int getDist();
    void setDist(int dist);
    std::map<std::string, int>& getNeighbors();

private:
    std::map<std::string, int> m_neighbors;
    std::string m_city;
    int m_dist;
    bool m_visited;
};



#endif