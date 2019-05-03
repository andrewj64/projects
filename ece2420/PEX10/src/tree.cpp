#include <iostream>
#include <cstring>
#include <map>
#include <fstream>

#include "tree.hpp"
//#include "path.hpp"

City::City(std::string city, std::string dest, int dist)
    :m_city(city), m_dest(dest), m_dist(dist), m_visited(false) 
{
    //masterMap[m_city][m_dest] = m_dist; 
};

