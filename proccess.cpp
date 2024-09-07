#include "proccess.hpp"

proccess::proccess(string i_ID, string i_Queue, int i_AT, int i_BT, int i_PRT)
    : ID(i_ID), WhichQueue(i_Queue), AT(i_AT), BT(i_BT), PRT(i_PRT) {}

proccess::~proccess() {}

int proccess::GetAT() {
    return this->AT;
}

string proccess::GetWhichQueue() {
    return this->WhichQueue;
}

string proccess::GetID() {
    return this->ID;
}

int proccess::GetBT() {
    return this->BT;
}

void proccess::SetBT(int NewBT) {
    this->BT = NewBT;
}

int proccess::GetWT() {
    int tmp = (WT - ConstWT);
    return tmp;
}

void proccess::SetWT(int NewWT) {
    /*
    if(NewWT < 0){
        this->ConstWT = this->ConstWT - NewWT;
    }
*/
    this->WT += NewWT;  
}


int proccess::GetRT() {
    return this->RT;
}

void proccess::SetRT(int NewRT) {
    this->RT = NewRT;
}
