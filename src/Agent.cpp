//
// Created by spl211 on 06/11/2020.
//

#include <iostream>
#include "../header/Agent.h"
#include "../header/Session.h"
#include "../header/Tree.h"
using namespace std;
Agent::Agent() {

}




ContactTracer::ContactTracer() {}

void ContactTracer::act(Session &session) {
    //take virus if queue not empty
    if(session.isQueueEmpty()){
        return;
    }
    int root = session.dequeueInfected();
    // create tree where the virus is the root
    Tree *tree= Tree::createTree(session,root);

    //find which node to remove
    int remove=tree->traceTree();


    if(remove!=-1) {
        //remove
        session.getGraph().removeNeighbors(remove);
    }
    if(tree){
        delete tree;}

}

std::string ContactTracer::MyType() {
    return "C";
}

int ContactTracer::MyNumber() {
    return -1;
}

Virus::Virus(int nodeInd):nodeInd(nodeInd) {

}
void Virus::act(Session &session) {



    if(session.getGraph().isInfected(nodeInd)==0)//only for the first setup when we read from json
    {
        session.getGraph().infectNode(nodeInd);

    }

    if(session.getGraph().isInfected(nodeInd)==1)//each virus must be infected, make sure 1 in traffic light become 2
    {
        session.getGraph().infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }

    vector <int> neighbors = session.getGraph().getNeighbor(nodeInd);
    int index=0;

    for(auto elem:neighbors) {

        if ((elem == 1) & (session.getGraph().isInfected(index)==0) )
        {
            session.getGraph().infectNode(index);
            Virus *copy = new Virus(index);
            session.addAgent(copy);
            return;
        }
            index++;
    }



}

std::string Virus::MyType() {
    return "V";
}

int Virus::MyNumber() {
    return this->nodeInd;
}
