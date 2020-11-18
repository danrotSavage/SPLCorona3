#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph();
    void infectNode(int nodeInd);
     int isInfectedNode(int nodeInd);
    bool isInfected (int nodeInd);
    void removeNeighbors(int remove);
     std::vector<int> getNeighbor(int vertices) ;
     int getSize() const;
    std::vector<std::vector<int>> getEdges();

    virtual ~Graph();//destractor
    Graph(const Graph &other);//copy constractor
    const Graph& operator=(const Graph &other);//assingnnment operator
    const Graph& operator=(Graph&&other);
    Graph(Graph &&other);
private:
    std::vector<std::vector<int>> edges;
    std::vector<int> *trafficLight;

};

#endif
