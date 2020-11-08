//
// Created by spl211 on 02/11/2020.
//

using namespace std;
#include "../header/Graph.h"
Graph::Graph(std::vector<std::vector<int>> matrix):edges( matrix){//matrix on the heap or stack

    trafficLight = new vector<int>;
    for (int i = 0; i < matrix.size(); ++i) {
        trafficLight->push_back(0);


    }
}

Graph::Graph():edges(std::vector<std::vector<int>>()) {}

 std::vector<int> Graph::getNeighbor(int vertices) {
    vector <int> *b ;

    return edges[vertices];
}
int Graph::getSize() const {

    return edges.size();
}



void Graph::infectNode(int nodeInd) {
    if ((*trafficLight)[nodeInd] == 0)
        (*trafficLight)[nodeInd] = 1;
    else if((*trafficLight)[nodeInd]==1)
        (*trafficLight)[nodeInd] = 2;

}

bool Graph::isInfected(int nodeInd) {

    return (*trafficLight)[nodeInd]==1|| (*trafficLight)[nodeInd]==2;
}


