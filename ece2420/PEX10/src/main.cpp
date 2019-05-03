#include <iostream>
#include <cstring>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>

#include "city.hpp"
#include "dijkstra.hpp"

/***********************************************************************************
 * I didn't get most of the cases to work, but I hope you can see my understanding  *
 * of the algorithm in my code and comments                                         *
 * Thanks for your help!                                                            *
 * ********************************************************************************/

int main(int argc, char** argv)
{
    std::string fileName;
    std::string city, dest, start, end, cur, next;
    int dist;


    // File handling
    if(2 == argc)
    {
        fileName = argv[argc-1];
    }
    else
    {
        std::cout << "Bad command line args" << std::endl;
        return -1;
    }

    std::ifstream iFile(fileName);
    if(!iFile.good())
    {
        std::cout << "Bad input file!" << std::endl;
        return -1;
    }
    
    iFile >> start;
    iFile >> end;
    Dijkstra d;
    while(!iFile.eof())
    {
        iFile >> city;
        iFile >> dest;
        iFile >> dist;
        d.insert(city, dest, dist);
    }

    d.algorithm(start, end);
    d.print();
    iFile.close();
    return 0;
}