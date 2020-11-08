//
// Created by spl211 on 06/11/2020.
//
#include "../header/Session.h"
#include <iostream>
#include "fstream"
#include "../json/json.hpp"
#include "queue"
#include "../header/Agent.h"


using json  = nlohmann::json;
using namespace std;

 Graph& Session::getGraph()   {

    return  g;

}
Session:: Session(const std::string &path):g(),infected(new queue<int>) {

    //get graph from json
    ifstream i("../json/config1.json");
    json j;
    j<<i;
    vector<vector<int>> matrix;
    for( auto elem:j["graph"])
    {
        matrix.push_back(elem);

    }
    g= Graph(matrix);


    //get tree type form json
    string tree = j["tree"];
    if (tree=="M")
        treeType=MaxRank;
    else if(tree=="R")
        treeType=Root;
    else if(tree=="C")
        treeType= Cycle;
    else
         std::cout <<" exception, wrong tree type " << std::endl;

    //get agent from json
    for(auto elem: j["agents"])
    {
            if (elem[0]=="V")
            agents.push_back(new Virus(elem[1]));
            else
                agents.push_back(new ContactTracer());
    }

}


void Session::enqueueInfected(int node) {

    infected->push(node);
}
int Session::dequeueInfected() {
    int temp= infected->front();
    infected->pop();
    return temp;
}
TreeType Session::getTreeType() const {

    return treeType;
}
void Session::addAgent( Agent *agent) {

    agents.push_back( agent);

}
void Session::setGraph(const Graph &graph) {

    g=graph;
}
void Session::addAgent(const Agent &agent) {
    return;
}

void Session::simulate() {
    int indexTurn=0;
    for (int i = 0; i < 5; ++i) {
        std::vector<Agent*> agentsTemp;
        agentsTemp=agents;
        for(auto elem:agentsTemp)
        {
            // std::cout <<"i am here  " <<i<< std::endl;
            elem->act(*this);



        }



        indexTurn++;
    }
        json j;
        j["graph"]=this->getGraph().getEdges();
         std::cout <<j << std::endl;
        ofstream i("output.json");

    }

int Session::getGraphSize() const {
    return g.getSize();
}

Graph Session::getGraphConst() const {
    return g;
}

int Session::getCurrCycle() const {
    return this->currCycle;
}
