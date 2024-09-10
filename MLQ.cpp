#include "MLQ.hpp"

MLQ::MLQ(){
}

MLQ::~MLQ(){
}


void MLQ::SetQuantum (int NewQuantum){
    this->quantum = NewQuantum;
}
int MLQ::GetQuantum(){
    int tmp = this->quantum;
    return tmp;
}

deque<proccess> MLQ::GetQueue(const string& Value) {
    if(Value == "RR"){
        return this->RRQueue;
    }
    else if(Value == "FCFS"){
        return this->FCFSQueue;
    }
    else if(Value == "SJF"){
        return this->SJFQueue;
    }
}

void MLQ::SetQueue(deque<proccess> TmpQueue, string Value){
    if(Value == "RR"){
        this->RRQueue = TmpQueue;
    }
    else if(Value == "FCFS"){
        this->FCFSQueue = TmpQueue;
    }
    else if(Value == "SJF"){
        this->SJFQueue = TmpQueue;
    }
}


void MLQ::AddProccess(proccess* NewProccess) {
    string WhichQueue = NewProccess->GetWhichQueue();
    int AT = NewProccess->GetAT(), BT = NewProccess->GetBT();
    deque<proccess> tmpQueue = GetQueue(WhichQueue);

    if (!tmpQueue.empty()) {
        for (deque<proccess>::iterator it = tmpQueue.begin(); it != tmpQueue.end(); ++it) {
            int AT_tmp = it->GetAT(), BT_tmp = it->GetBT();
            if (AT <= AT_tmp) {
                tmpQueue.insert(it, *NewProccess);
                return; 
            }
        }
        tmpQueue.push_back(*NewProccess);
    } else {
        tmpQueue.push_back(*NewProccess);
    }
    SetQueue(tmpQueue, WhichQueue);
}

void MLQ::Execute(){
    while(!this->RRQueue.empty() || !this->FCFSQueue.empty() || !this->SJFQueue.empty()){
        ExecuteRR();
        ExecuteFCFS();
        ExecuteSJF();
        if(this->GotIn == 0){
            this->CurrentTime += 1;
        }
    }
    FShowResults();
}

int MLQ::CalcWT(){
    int count = 0, Average = 0, Execute;
    deque<int>::iterator it = this->WT.begin();
    while(it != this->WT.end()){
        Average += *it;
        count++;
        it++;
    }
    Execute = Average / count;
    return Execute;
}
int MLQ::CalcRT(){
    int count = 0, Average = 0, Execute;
    deque<int>::iterator it = this->RT.begin();
    while(it != this->RT.end()){
        Average += *it;
        count++;
        it++;
    }
    Execute = Average / count;
    return Execute;
}

void MLQ::FShowResults(){
    int Final_WT = CalcWT(), Final_RT = CalcRT();

    cout << "**************************\n" << "Showing sort all processes\n" << "**************************\n" << endl;
    
    
    for(deque<string>::iterator it = this->ShowResults.begin(); it != this->ShowResults.end(); it++){
        cout << *it << "  ";
    }
    cout <<  "\n" << endl;

    cout << "**********************\n" << "Table of each proccess" << "\n**********************" << endl;
    
    

    cout << "ID" << " | " << "WT" << " | " << "RT" << endl;

    for(map<string, int>::iterator it = this->WT_Total.begin(); it != this->WT_Total.end(); it++){
        if(this->RT_Total[it->first] == -1){
            cout << it->first << " | " << it->second << " | " << "0" << "\n";
        }
        else{
            cout << it->first << " | " << it->second << " | " << this->RT_Total[it->first] << "\n";
        }
        
    }
    cout << endl;

    cout << "Waiting time average: " << Final_WT << "\nFirst Time Average: " << Final_RT << endl;
}

void MLQ::AddExport(string ID, int BT){
    for(int i = 0; i < BT; i++){
        this->ShowResults.push_back(ID);
    }
}


void MLQ::IncWT(int AddValue){
    for(deque<proccess>::iterator it = this->RRQueue.begin(); it != this->RRQueue.end(); it++){
        it->SetWT(AddValue);
    }
    for(deque<proccess>::iterator it = this->FCFSQueue.begin(); it != this->FCFSQueue.end(); it++){
        it->SetWT(AddValue);
    }
    for(deque<proccess>::iterator it = this->SJFQueue.begin(); it != this->SJFQueue.end(); it++){
        it->SetWT(AddValue);
    }
}

void MLQ::ExecuteRR() {
    while (!this->RRQueue.empty()) {
        auto CurrentProccess = this->RRQueue.front();
        this->RRQueue.pop_front();
        int BT = CurrentProccess.GetBT(), AT = CurrentProccess.GetAT();
        string ID = CurrentProccess.GetID();
        if(AT > this->CurrentTime){
            this->RRQueue.push_front(CurrentProccess);
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
            if (BT > this->quantum) {
                BT -= this->quantum;
                CurrentProccess.SetBT(BT);
                AddExport(ID, this->quantum);
                this->CurrentTime += quantum;
                IncWT(this->quantum);
                if (this->RRQueue.size() > 1) {
                    this->RRQueue.insert(this->RRQueue.begin() + 1, CurrentProccess);
                } else {
                    this->RRQueue.push_back(CurrentProccess);
                }
                
            } else {
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

        
}

void MLQ::ExecuteFCFS(){
    while(!this->FCFSQueue.empty()){
        auto CurrentProccess = this->FCFSQueue.front();
        this->FCFSQueue.pop_front();
        int BT = CurrentProccess.GetBT(), AT = CurrentProccess.GetAT();
        string ID = CurrentProccess.GetID();
        if(AT > this->CurrentTime){
            this->FCFSQueue.push_front(CurrentProccess);
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

proccess* MLQ::CheckProccess(proccess* CurrentProccess) {
    int BT = CurrentProccess->GetBT(), MinAT = this->CurrentTime + BT;
    proccess* BestProccess = nullptr;
    auto it = this->SJFQueue.begin(); 
    for (auto iter = this->SJFQueue.begin(); iter != this->SJFQueue.end(); ++iter) {
        int AT = iter->GetAT(), tmpBT = iter->GetBT();
        if (AT < MinAT && tmpBT < BT) {
            BestProccess = &(*iter);
            it = iter;
        }
    }
    if (BestProccess != nullptr) {
        this->SJFQueue.erase(it); 
    }
    return BestProccess;
}



void MLQ::ExecuteSJF() {
    while (!this->SJFQueue.empty()) {
        auto CurrentProccess = this->SJFQueue.front();
        this->SJFQueue.pop_front();
        int BT = CurrentProccess.GetBT(), AT = CurrentProccess.GetAT();
        string ID = CurrentProccess.GetID();
        proccess* PossibleProccess = CheckProccess(&CurrentProccess);

        if (AT > this->CurrentTime) {
            this->SJFQueue.push_front(CurrentProccess);
            this->GotIn = 0;
            return;
        }

        while (BT > 0) {
            PossibleProccess = CheckProccess(&CurrentProccess);
            if (PossibleProccess == nullptr) {
                if (CurrentProccess.GetRT() == 0) {
                    if (this->CurrentTime == 0) {
                        CurrentProccess.SetRT(-1);
                    } else {
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
                BT = 0;
            } else {
                int execTime = PossibleProccess->GetAT() - this->CurrentTime;
                if (execTime > 0) {
                    CurrentProccess.SetBT(BT - execTime);
                    this->CurrentTime += execTime;
                    BT -= execTime;
                    AddExport(ID, execTime);
                    IncWT(execTime);
                }
                this->SJFQueue.push_front(CurrentProccess);
                CurrentProccess = *PossibleProccess; 
                BT = CurrentProccess.GetBT();
                AT = CurrentProccess.GetAT();
                ID = CurrentProccess.GetID();
            }
        }
    }
}
