#include <iostream>
#include "fstream"
#include "../json/json.hpp"
#include "../header/Tree.h"
#include "../header/Graph.h"
#include "../header/Session.h"
#include "../header/Agent.h"

using json  = nlohmann::json;
using namespace std;


int main(int argc, char** argv){
    std::cout << "Hello, World!" << std::endl;
    //if(argc != 2){
     //   cout << "usage cTrace <config_path>" << endl;
     //   return 0;
   // }

    string l="../config1.json";
    Session *m = new Session(l);



      m->simulate();
    delete m;





    //Session sess(argv[1]);
    //sess.simulate();
    return 0;
}

