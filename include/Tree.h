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
    static vector<Tree*> CopyConstractorCopyTree(const Tree &other ) ;
    int childrenSize() const;
    vector<Tree*> getChildren() const;
    int getNode() const;
    virtual int traceTree()=0;
    int getRootLabel();


    virtual ~Tree();//destractor
    Tree(const Tree &other);//copy constractor
    const Tree& operator=(const Tree &other);//assingnnment operator
    const Tree& operator=(Tree &&other);
    Tree(Tree &&other);

private:
    static Tree *  createMaxRankTree(const Session& session, int rootLabel);
    static Tree *  createCycleTree( const Session& session, int rootLabel, int currCycle);
    static Tree *  createRootTree( const Session& session, int rootLabel);


protected:
    int node;
    std::vector<Tree*> children;
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
    virtual int traceTree();
    vector<int> Recursion(vector<int>);

};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
};


#endif
