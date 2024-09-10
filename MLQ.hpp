#ifndef MLQ_hpp
#define MLQ_hpp
#include <iostream>
#include <string>
#include <map>
#include "proccess.hpp"
#include <deque>
#include <algorithm>

using namespace std;

class MLQ{
private:
    deque<proccess> RRQueue;
    deque<proccess> FCFSQueue;
    deque<proccess> SJFQueue;
    deque<string> ShowResults;
    deque<int> WT;
    deque<int> RT;
    map<string, int> WT_Total;
    map<string, int> RT_Total;
    int CurrentTime = 0;
    int quantum;
    int GotIn = 1;
public:
    MLQ();
    ~MLQ();
    void SetQuantum (int NewQuantum);
    int GetQuantum();
    void AddProccess(proccess* NewProccess);
    deque<proccess> GetQueue(const string& Value);\
    void SetQueue (deque<proccess> TmpQueue, string Value);
    void Execute ();
    void ExecuteRR ();
    void ExecuteFCFS ();
    void ExecuteSJF ();
    proccess* CheckProccess(proccess* CurrentProccess);
    void AddExport(string ID, int BT);
    void IncWT(int AddValue);
    void FShowResults();
    int CalcWT();
    int CalcRT();

};

#endif //MLQ_hpp
