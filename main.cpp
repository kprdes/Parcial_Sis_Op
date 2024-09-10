#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "proccess.hpp"
#include "MLQ.hpp"
#include "MLFQ.hpp"

using namespace std;

int main() {
    MLQ scheduler;
    MLFQ schedulerMLFQ(2, 3);
    scheduler.SetQuantum(3);
    
    ifstream file("processes.txt");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, queue;
        int at, bt, prt;
        ss >> id >> queue >> at >> bt >> prt;
        proccess p(id, queue, at, bt, prt);
        scheduler.AddProccess(&p);
    }

    file.close();

    ifstream file2("processes2.txt");
    if (!file2.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }
    while (getline(file2, line)) {
        stringstream ss(line);
        string id, queue;
        int at, bt, prt;
        ss >> id >> queue >> at >> bt >> prt;
        proccess p(id, queue, at, bt, prt);
        schedulerMLFQ.AddProcess(&p);
    }

    file2.close();

    scheduler.Execute();
    schedulerMLFQ.Execute();

    return 0;
}
