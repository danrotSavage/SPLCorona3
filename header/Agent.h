#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent();
    virtual void act(Session &session)=0;
    virtual std::string MyType()=0;
protected:

};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual void act(Session &session);
    virtual std::string MyType();

};


class Virus: public Agent{
public:
    Virus(int nodeInd);

    virtual void act(Session &session);
    virtual std::string MyType();

private:
    const int nodeInd;
};

#endif
