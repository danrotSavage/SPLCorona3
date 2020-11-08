#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph();
    void infectNode(int nodeInd);
    int isInfected(int nodeInd);
    void removeNeighbors(int remove);
     std::vector<int> getNeighbor(int vertices) ;
     int getSize() const;
    std::vector<std::vector<int>> getEdges();
private:
    std::vector<std::vector<int>> edges;
    std::vector<int> *trafficLight;

};

#endif
