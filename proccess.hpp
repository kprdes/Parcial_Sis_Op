#ifndef PROCCESS_hpp
#define PROCCESS_hpp
#include <iostream>
#include <string>

using namespace std;

class proccess{
private:
    string ID;
    int AT;
    int BT;
    int PRT;
public:
    proccess(string i_ID, int i_AT, int i_BT, int i_PRT);
    ~proccess();
    int GetAT();
    string GetID();
};

proccess::proccess(string i_ID, int i_AT, int i_BT, int i_PRT) : ID(i_ID), AT(i_AT), BT(i_BT), PRT(i_PRT){
}

proccess::~proccess(){
}


#endif //PROCCESS_hpp
