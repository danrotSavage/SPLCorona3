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
    std::cout<<"Contact tracer create Tree from " <<root<< std::endl;
    Tree *tree= Tree::createTree(session,root);
    //find which node to remove
    int remove=tree->traceTree();


    if(remove!=-1) {
        //remove
        std::cout<<"Contact tracer disconnect " <<remove<< std::endl;
        session.getGraph().removeNeighbors(remove);
    }
    else{
        std::cout<<"Contact tracer didnt disconnect anyone" << std::endl;
    }


}
Virus::Virus(int nodeInd):nodeInd(nodeInd) {

}
void Virus::act(Session &session) {

    Graph g = session.getGraph();


    if(g.isInfected(nodeInd)==0)//only for the first setup when we read from json
    {
        g.infectNode(nodeInd);

    }

    if(g.isInfected(nodeInd)==1)//each virus must be infected, make sure 1 in traffic light become 2
    {
        g.infectNode(nodeInd);
        std::cout<<nodeInd<<" got sick" <<std::endl;
        session.enqueueInfected(nodeInd);

    }

    vector <int> neighbors = g.getNeighbor(nodeInd);
    int index=0;

    for(auto elem:neighbors) {

        if (elem == 1 & g.isInfected(index)==0 )
        {
            std::cout << nodeInd << " has infected "<< index<< std::endl;
            g.infectNode(index);
            Virus *copy = new Virus(index);
            session.addAgent(copy);

            return;

        }
            index++;



    }



}
