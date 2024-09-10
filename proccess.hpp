#ifndef PROCCESS_hpp
#define PROCCESS_hpp

#include <iostream>
#include <string>

using namespace std;

class proccess {
private:
    string ID;
    string WhichQueue;
    int AT;
    int BT;
    int PRT;
    int WT = 0; 
    int RT = 0; 
    int ConstWT = 0;

public:
    proccess(string i_ID, string i_Queue, int i_AT, int i_BT, int i_PRT);
    ~proccess();
    
    int GetAT();
    string GetWhichQueue();
    string GetID();
    int GetBT();
    
    void SetBT(int NewBT);
    
    int GetWT();
    void SetWT(int NewWT);
    
    int GetRT();
    void SetRT(int NewRT);
};

#endif // PROCCESS_hpp
