#ifndef TREE_H_
#define TREE_H_

#include <vector>
using namespace std;
class Session;

class Tree{
public:
    Tree(int rootLabel);

    void addChild( Tree *child);
    void addChild(const Tree &child);
    static Tree* createTree(const Session& session, int rootLabel);
    int childrenSize();

    //virtual int traceTree()=0;

protected:
    int node;
    std::vector<Tree*> *children;
private:
    std::vector<int> getReleventChildren( std::vector<int>& GraphNeighbor, vector<int> &usedVertices);
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    MaxRankTree * Recursion(MaxRankTree * maxRank);
    virtual int traceTree();
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
};

#endif
