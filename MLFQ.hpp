#ifndef MLFQ_hpp
#define MLFQ_hpp
#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include "proccess.hpp"

using namespace std;

class MLFQ {
private:
    // Vamos a usar múltiples colas con diferentes niveles de prioridad
    vector<deque<proccess>> Queues; // Colas de procesos
    deque<string> ShowResults;
    deque<int> WT;
    deque<int> RT;
    map<string, int> WT_Total;
    map<string, int> RT_Total;
    int CurrentTime = 0;
    int quantum;
    int GotIn = 1;
    int NumQueues; // Número de colas (niveles de prioridad)
    
public:
    MLFQ(int numQueues, int initialQuantum);
    ~MLFQ();

    void SetQuantum(int NewQuantum);
    int GetQuantum();

    void AddProcess(proccess* NewProcess);
    deque<proccess>& GetQueue(int Level);
    void SetQueue(deque<proccess> TmpQueue, int Level);

    void Execute();
    void ExecuteRR(int Level); 
    void ExecuteFCFS(int Level); 

    void AddExport(string ID, int BT);
    void IncWT(int AddValue);
    void FShowResults();

    int CalcWT();
    int CalcRT();

    void LowerPriority(proccess& proccess); 
};

#endif // MLFQ_hpp
