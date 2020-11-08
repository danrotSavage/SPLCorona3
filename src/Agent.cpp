//
// Created by spl211 on 06/11/2020.
//

#include <iostream>
#include "../header/Agent.h"
#include "../header/Session.h"
using namespace std;
Agent::Agent() {

}




ContactTracer::ContactTracer() {


}

void ContactTracer::act(Session &session) {
    return;
}
Virus::Virus(int nodeInd):nodeInd(nodeInd) {

}
void Virus::act(Session &session) {

    Graph g = session.getGraph();

    //each virus must be infected, make sure 1 in traffic light become 2
    g.infectNode(nodeInd);

    vector <int> neighbors = g.getNeighbor(nodeInd);
    int index=0;

    for(auto elem:neighbors) {

        if (elem == 1 & !g.isInfected(index) )
        {
             std::cout << nodeInd << " has infected "<< index<< std::endl;
            session.enqueueInfected(index);
            g.infectNode(index);
            Virus *copy = new Virus(index);
            session.addAgent(copy);

            return;

        }
            index++;



    }



}
