#ifndef MLQ_hpp
#define MLQ_hpp
#include <iostream>
#include <string>
#include <map>
#include "proccess.hpp"
#include <vector>

using namespace std;

class MLQ{
private:
    map<string, vector<proccess> > proccesses;
public:
    MLQ();
    ~MLQ();
    void AddProccess(proccess* NewProccess);
    vector<proccess> GetVector(const string& Value);
    //int GetAT();
};

MLQ::MLQ(){
}

MLQ::~MLQ(){
}


#endif //MLQ_hpp
