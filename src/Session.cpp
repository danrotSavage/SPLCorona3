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
Session:: Session(const std::string &path):g(),treeType(),agents(),infected(queue<int>()) ,currCycle(0) {

    //get graph from json

    ifstream i(path);

    json j;
    i>>j;
    std::cout<<"hello,guy"<<std::endl;
    vector<vector<int>> matrix;
    for( auto elem:j["graph"])
    {
        matrix.push_back(elem);

    }

        g = Graph(matrix);



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

    infected.push(node);
    std::cout<<node <<" entered queue"<< std::endl;
}
int Session::dequeueInfected() {
    int temp= infected.front();
    infected.pop();
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
        std::cout<<"             turn "<<i<<" started"<<std::endl;
        std::vector<Agent*> agentsTemp;
        agentsTemp=agents;
        for(auto elem:agentsTemp)
        {
            elem->act(*this);
        }
        indexTurn++;
    }
        json j;

    
    
    std::vector<std::vector<int>> edges;
    for (int i = 0; i < this->g.getSize(); ++i) {
        vector<int> neighbors = g.getNeighbor(i);
        edges.push_back(neighbors);
    }
    j["graph"]=edges;

    vector <int> infec;
    for (Agent *a:agents) {
        if (a->MyType()=="V")
            infec.push_back(a->MyNumber());
    }
    j["infected"]=infec;
    
    ofstream i("./output.json");
    i<<j;

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

bool Session::isQueueEmpty() {
     return (infected).empty();
 }

Session::~Session() {
     while(!infected.empty())
        infected.pop();
     for(auto p:agents)
     {
         delete p;
     }

}

Session::Session(const Session &other):g(other.g),treeType(other.treeType) ,agents(),infected(),currCycle(other.currCycle){

    for (auto elem: other.agents) {
         agents.push_back(elem);
    }
    for (size_t i = 0; i < (unsigned )other.infected.size(); ++i) {
        infected=other.infected;
    }

}

const Session &Session::operator=(Session &&other) {
    g=other.g;
    treeType=other.treeType;
    infected=other.infected;
    for(auto agn: other.agents){
        Agent * agnPoint;
        agnPoint=agn;
        this->agents.push_back(agnPoint);
        agn= nullptr;
    }
    this->currCycle=other.currCycle;
    return *this;
}

Session::Session(Session &&other) :g(other.g),treeType(other.treeType) ,agents(),infected(other.infected),currCycle(other.currCycle){




    for(auto agn: other.agents){
        Agent * agnPoint;
        agnPoint=agn;
        this->agents.push_back(agnPoint);
        agn= nullptr;
    }


}

const Session &Session::operator=(const Session &other) {
    g=other.g;
    treeType=other.treeType;
    infected=other.infected;

    for(auto agn: other.agents){
        Agent * agnPoint;
        agnPoint=agn;
        this->agents.push_back(agnPoint);

    }
    this->currCycle=other.currCycle;
    return *this;
}

