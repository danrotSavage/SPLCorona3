//
// Created by spl211 on 01/11/2020.
//

#include <iostream>
#include "../header/Tree.h"
#include "queue"
#include "../header/Graph.h"
#include "../header/Session.h"

using namespace std;

Tree ::Tree(int rootLabel):node(rootLabel),children(new vector<Tree*>)
{

}
std::vector<int> Tree::getReleventChildren( std::vector<int> &GraphNeighbor, vector<int> &usedVertices)
{
    std::vector<int> *output=new vector<int>(0);
    for (size_t ver = 0; ver < (unsigned )GraphNeighbor.size(); ++ver) {
        if(GraphNeighbor[ver]==1 && (usedVertices)[ver]==0)
        {
             output->push_back(ver);
            (usedVertices)[ver]=1;
        }
    }

    return *output;
}




Tree * Tree::createTree(const Session &session, int rootLabel) {
        TreeType b = session.getTreeType();
        switch(b){
            case MaxRank:
                return createMaxRankTree(session, rootLabel);
            case Cycle:
                return createCycleTree(session,rootLabel,session.getCurrCycle());
            case Root:
                return createRootTree(session,rootLabel);
        }
        return nullptr;
}
//check later
void Tree::addChild( Tree *child) {


    (children)->push_back(child);
}

void Tree::addChild(const Tree &child) {

     std::cout <<" oh hell no " << std::endl;
}

CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle) {}
MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel) {}
RootTree::RootTree(int rootLabel):Tree(rootLabel) {}

int RootTree::traceTree() {
    return this->node;
}
int Tree::childrenSize() const{
    return children->size();
}

Tree *Tree::createMaxRankTree(const Session &session, int rootLabel) {
    vector<int> usedVertices(session.getGraphSize());
    for (int i = 0; i < session.getGraphSize(); ++i) {
        usedVertices[i]=0;
    }

    auto *treeQueue = new queue<MaxRankTree*>();
    //push root into queue
    auto *AbrahamTheRoot = new MaxRankTree(rootLabel);
    treeQueue->push(AbrahamTheRoot);
    Graph g= session.getGraphConst();


    usedVertices[rootLabel]=1;
    while (!treeQueue->empty()) {

        MaxRankTree *tempRoot = treeQueue->front();
        treeQueue->pop();

        vector<int> child1= g.getNeighbor(tempRoot->node);
        //get the neighbors from a graph function. insert into a tree function in which it builds correct children.

        vector<int> childrenInt = tempRoot->getReleventChildren(child1,usedVertices);
        for (int child: childrenInt) {

            MaxRankTree *tempTree = new MaxRankTree(child);
            treeQueue->push(tempTree);
            tempRoot->addChild(tempTree);
            //childrenInt.push_back(tempTree->node);
        }

    }
    return AbrahamTheRoot;
}
Tree *Tree::createCycleTree(const Session &session, int rootLabel , int currCycle) {
    vector<int> usedVertices(session.getGraphSize());
    for (int i = 0; i < session.getGraphSize(); ++i) {
        usedVertices[i]=0;
    }

    auto *treeQueue = new queue<CycleTree*>();
    //push root into queue
    auto *AbrahamTheRoot = new CycleTree(rootLabel,currCycle);
    treeQueue->push(AbrahamTheRoot);
    Graph g= session.getGraphConst();


    usedVertices[rootLabel]=1;
    while (!treeQueue->empty()) {

        CycleTree *tempRoot = treeQueue->front();
        treeQueue->pop();

        vector<int> child1= g.getNeighbor(tempRoot->node);
        //get the neighbors from a graph function. insert into a tree function in which it builds correct children.

        vector<int> childrenInt = tempRoot->getReleventChildren(child1,usedVertices);
        for (int child: childrenInt) {

            CycleTree *tempTree = new CycleTree(child,currCycle);
            treeQueue->push(tempTree);
            tempRoot->addChild(tempTree);
            //childrenInt.push_back(tempTree->node);
        }

    }
    return AbrahamTheRoot;
}
Tree *Tree::createRootTree(const Session &session, int rootLabel) {
    vector<int> usedVertices(session.getGraphSize());
    for (int i = 0; i < session.getGraphSize(); ++i) {
        usedVertices[i]=0;
    }

    auto *treeQueue = new queue<RootTree*>();
    //push root into queue
    auto *AbrahamTheRoot = new RootTree(rootLabel);
    treeQueue->push(AbrahamTheRoot);
    Graph g= session.getGraphConst();

    usedVertices[rootLabel]=1;
    while (!treeQueue->empty()) {

        RootTree *tempRoot = treeQueue->front();
        treeQueue->pop();

        vector<int> child1= g.getNeighbor(tempRoot->node);
        //get the neighbors from a graph function. insert into a tree function in which it builds its correct children.

        vector<int> childrenInt = tempRoot->getReleventChildren(child1,usedVertices);
        for (int child: childrenInt) {

            RootTree *tempTree = new RootTree(child);
            treeQueue->push(tempTree);
            tempRoot->addChild(tempTree);
            //childrenInt.push_back(tempTree->node);
        }

    }
    return AbrahamTheRoot;
}

Tree::~Tree() {
    for (int i = 0; i < childrenSize(); ++i) {
        if((*children)[i]){
            delete (*children)[i];
        }
    }
    if(children){
        delete children;
    }
}

vector<Tree*> *Tree::getChildren() const {
    return this->children;



}

int Tree::getNode() const {
    return node;
}

Tree::Tree(const Tree &other):node(other.getNode()),children(CopyConstractorCopyTree(other)) {

}



vector<Tree*> * Tree::CopyConstractorCopyTree(const Tree &other ) {
    Tree *Root=new MaxRankTree(other.getNode());
    if(other.childrenSize()!=0){


        for (int i = 0; i < other.childrenSize(); ++i) {
            Tree *thisChild = (Tree *) ( (*other.getChildren())[i]);
            Tree *otherChild=new MaxRankTree(thisChild->getNode());
            Root->addChild(otherChild);
            CopyConstractorCopyTree(*otherChild);

        }
    }
    return Root->getChildren();


}

const Tree &Tree::operator=(const Tree &other) {
    node=other.getNode();
    children=other.getChildren();
    return *this;
}

const Tree &Tree::operator=(Tree &&other) {
    node=other.getNode();
    children=other.getChildren();
    other.children= nullptr;
    return *this;
}

Tree::Tree(Tree &&other):node (other.node),children(other.children) {

     other.children=nullptr;
}


MaxRankTree * MaxRankTree::Recursion( MaxRankTree *maxSoFar){

    if((unsigned )(this->childrenSize())==0)
        return maxSoFar;

    if(this->childrenSize()>maxSoFar->childrenSize())
        maxSoFar= this;

    for (size_t i = 0; i < (unsigned )children->size(); ++i) {
        MaxRankTree *temp = (MaxRankTree*)(*children)[i];
        MaxRankTree *childMax=temp->Recursion(maxSoFar);
        if( (*childMax).childrenSize()>(maxSoFar->childrenSize()) ) //if the Child tree have biger rank tree replace maxSoFar
        {
            *maxSoFar=*childMax;
        }
    }

    return maxSoFar;


}

int CycleTree::traceTree() {
    CycleTree *output=this;
    for (int i = 1; i < currCycle; ++i) {
        CycleTree *temp=(CycleTree*)((*children)[0]);
        output=temp;
    }
    return output->node;

}

int MaxRankTree::traceTree() {
    return Recursion(new MaxRankTree(-1)) -> node;
}


