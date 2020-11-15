//
// Created by spl211 on 02/11/2020.
//

using namespace std;
#include "../header/Graph.h"
Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix),trafficLight(new vector<int>){//matrix on the heap or stack


    for (size_t i = 0; i < (unsigned )matrix.size(); ++i) {
        trafficLight->push_back(0);
    }
}

Graph::Graph():edges(std::vector<std::vector<int>>()),trafficLight(new vector<int>) {

}


 std::vector<int> Graph::getNeighbor(int vertices) {


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

int Graph::isInfected(int nodeInd) {

    return (*trafficLight)[nodeInd];
}

void Graph::removeNeighbors(int remove) {
    for (size_t i = 0; i < (unsigned )edges.size(); ++i) {
        edges[remove][i]=0;
        edges[i][remove]=0;
    }
}

std::vector<std::vector<int>> Graph::getEdges() {
    return std::vector<std::vector<int>>();
}


//copy constructor

/*
    for (int i = 0; i < other.edges.size(); ++i) {
        vector<int> m;
        for (int j = 0; j < other.edges[i].size(); ++j) {

            m.push_back(other.edges[i][j]);

        }
        edges.push_back(m);
    }

    */


Graph::~Graph() {
    if(trafficLight)
        delete trafficLight;
    for(vector<int> v:edges)
       v.clear();
    edges.clear();

}

const Graph &Graph::operator=(const Graph &other) {

    *trafficLight = (*(other.trafficLight));
    edges=other.edges;
    return *this;
}

const Graph &Graph::operator=(Graph &&other) {
    if (trafficLight)
        delete trafficLight;
     trafficLight=other.trafficLight;
    other.trafficLight=nullptr;


    edges=other.edges;
    return *this;

}

Graph::Graph(Graph &&other):edges(other.edges),trafficLight(other.trafficLight){

    other.trafficLight= nullptr;
    edges=other.edges;

}
//copy constructor
Graph::Graph (const Graph &other):edges(other.edges),trafficLight(new vector<int>) {


    for (size_t i = 0; i < (unsigned )other.trafficLight->size(); ++i) {
        trafficLight->push_back((*(other.trafficLight))[i]);
    }
}



