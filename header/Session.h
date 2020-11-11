#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include "queue"
class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    //constructor
    Session(const std::string& path);


    //destructor
   // virtual ~Session();


    void simulate();
    void addAgent( Agent* agent);
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    int getGraphSize()  const;

    Graph &getGraph();
    Graph getGraphConst() const;
    
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    int getCurrCycle() const;
    bool isQueueEmpty();


    virtual ~Session();//destractor
    Session(const Session &other);//copy constractor
   // const Session& operator=(const Session &other);//assingnnment operator
    const Session& operator=(Session &&other);
    Session(Session &&other);
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue <int> *infected;
    int currCycle;
};

#endif
