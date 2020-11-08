#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph();
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

     std::vector<int> getNeighbor(int vertices) ;
     int getSize() const;
private:
    std::vector<std::vector<int>> edges;
    std::vector<int> *trafficLight;

};

#endif
