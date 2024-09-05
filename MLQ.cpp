#include "MLQ.hpp"

vector<proccess> MLQ::GetVector(const string& Value) {
    map<string, vector<proccess>>::iterator it = proccesses.find(Value);
    if (it != proccesses.end()) {
        return it->second;
    } else {
        return vector<proccess>();
    }
}

void MLQ::AddProccess(proccess* NewProccess) {
    string ID = NewProccess->GetID();
    int AT = NewProccess->GetAT();
    vector<proccess> tmpVector = GetVector(ID);

    if (!tmpVector.empty()) {
        for (auto it = tmpVector.begin(); it != tmpVector.end(); ++it) {
            int AT_tmp = it->GetAT();
            if (AT <= AT_tmp) {
                tmpVector.insert(it, *NewProccess);
                this->proccesses[ID] = tmpVector;
                return;
            }
        }
        tmpVector.push_back(*NewProccess);
        this->proccesses[ID] = tmpVector;
    } else {
        tmpVector.push_back(*NewProccess);
        this->proccesses[ID] = tmpVector;
    }
}
