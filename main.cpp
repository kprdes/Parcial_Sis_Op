#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "proccess.hpp"
#include "MLQ.hpp"

using namespace std;

int main() {
    MLQ scheduler;
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
    scheduler.Execute();

    return 0;
}
