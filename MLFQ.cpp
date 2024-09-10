#include "MLFQ.hpp"

MLFQ::MLFQ(int numQueues, int initialQuantum) {
    NumQueues = numQueues;
    quantum = initialQuantum;
    
    for (int i = 0; i < NumQueues; ++i) {
        deque<proccess> q;
        this->Queues.push_back(q);
    }
}

MLFQ::~MLFQ() {}

void MLFQ::SetQuantum(int NewQuantum) {
    quantum = NewQuantum;
}

int MLFQ::GetQuantum() {
    return quantum;
}

void MLFQ::AddProcess(proccess* NewProcess) {
    this->Queues[0].push_back(*NewProcess);
}

void MLFQ::LowerPriority(proccess& proccess) {
    this->Queues[1].push_back(proccess);
}

void MLFQ::IncWT(int AddValue) {
    for (auto& queue : this->Queues) {
        for (auto& proc : queue) {
            int newWT = proc.GetWT() + AddValue;
            proc.SetWT(newWT);
        }
    }
}

void MLFQ::Execute() {
    for (int level = 0; level < NumQueues; ++level) {
        if (!this->Queues[level].empty()) {
            if (level == 0) {
                ExecuteRR(level);
            } else {
                ExecuteFCFS(level);
            }
        }
    }
    FShowResults();
}

void MLFQ::ExecuteRR(int Level) {
    while (!this->Queues[Level].empty()) {
        auto CurrentProcess = this->Queues[Level].front();
        this->Queues[Level].pop_front();
        
        int BT = CurrentProcess.GetBT();
        int AT = CurrentProcess.GetAT(); 
        string ID = CurrentProcess.GetID(); 
        
        if (AT > this->CurrentTime) {
            this->Queues[Level].push_front(CurrentProcess);
            this->GotIn = 0;
            return;
        } else {
            this->GotIn = 1;
            
            if(CurrentProcess.GetRT() == 0){
                if(this->CurrentTime == 0){
                CurrentProcess.SetRT(-1);  
                }
                else{
                    CurrentProcess.SetRT(this->CurrentTime); 
                }
            }

            if (BT > this->quantum) {
                BT -= this->quantum;
                CurrentProcess.SetBT(BT);
                AddExport(ID, this->quantum);
                this->CurrentTime += quantum; 
                IncWT(this->quantum);
                LowerPriority(CurrentProcess);

            } else {
                AddExport(ID, BT);
                this->CurrentTime += BT; 
                IncWT(BT);

                this->WT.push_back(CurrentProcess.GetWT());
                this->RT.push_back(CurrentProcess.GetRT());
                this->WT_Total[ID] = CurrentProcess.GetWT();
                this->RT_Total[ID] = CurrentProcess.GetRT();
            }
        }
    }
}

void MLFQ::ExecuteFCFS(int Level){
    while(!this->Queues[Level].empty()){
        auto CurrentProccess = this->Queues[Level].front();
        this->Queues[Level].pop_front();
        int BT = CurrentProccess.GetBT(), AT = CurrentProccess.GetAT();
        string ID = CurrentProccess.GetID();
        if(AT > this->CurrentTime){
            this->Queues[Level].push_front(CurrentProccess);
            this->GotIn = 0;
            return;
        }
        else{
            this->GotIn = 1;
            if(CurrentProccess.GetRT() == 0){
                if(this->CurrentTime == 0){
                CurrentProccess.SetRT(-1);  
                }
                else{
                    CurrentProccess.SetRT(this->CurrentTime); 
                }
            }
            AddExport(ID, BT);
            this->CurrentTime += BT;
            IncWT(BT);
            this->WT.push_back(CurrentProccess.GetWT());
            this->RT.push_back(CurrentProccess.GetRT());
            this->WT_Total[ID] = CurrentProccess.GetWT();
            this->RT_Total[ID] = CurrentProccess.GetRT();
        }
    
    }
}

void MLFQ::AddExport(string ID, int BT){
    for(int i = 0; i < BT; i++){
        this->ShowResults.push_back(ID);
    }
}

void MLFQ::FShowResults(){
    int Final_WT = CalcWT();
    int Final_RT = CalcRT();

    cout << "**************************\n"
         << "Showing sorted processes\n"
         << "**************************\n" << endl;
    
    for (const auto& processID : this->ShowResults) {
        cout << processID << "  ";
    }
    cout << "\n" << endl;

    cout << "**********************\n"
         << "Table of each process\n"
         << "**********************" << endl;
    
    cout << "ID" << " | " << "WT" << " | " << "RT" << endl;

    for (const auto& wt_entry : this->WT_Total) {
        const string& processID = wt_entry.first;
        int wt = wt_entry.second;
        int rt = this->RT_Total[processID];
        
        if (rt == -1) {
            rt = 0;
        }

        cout << processID << " | " << wt << " | " << rt << "\n";
    }
    cout << endl;

    cout << "**********************\n";
    cout << "Waiting time average: " << Final_WT << "\n";
    cout << "First Time Average: " << Final_RT << endl;
    cout << "**********************\n";
}

int MLFQ::CalcWT(){
    if (this->WT.empty()) {
        return 0;
    }

    int count = 0;
    int totalWT = 0;

    for (const auto& wt : this->WT) {
        totalWT += wt;
        count++;
    }

    int averageWT = (count > 0) ? totalWT / count : 0;
    return averageWT;
}

int MLFQ::CalcRT(){
    if (this->RT.empty()) {
        return 0;
    }

    int count = 0;
    int totalRT = 0;

    for (const auto& rt : this->RT) {
        totalRT += rt;
        count++;
    }

    int averageRT = (count > 0) ? totalRT / count : 0;
    return averageRT;
}
