

# Multilevel Queue (MLQ) Scheduler

This project implements a **Multilevel Queue (MLQ) Scheduler** that simulates process scheduling using multiple queues, each with a different scheduling algorithm. The program reads processes from a file, assigns them to appropriate queues, and simulates their execution based on the defined scheduling algorithms.

## Table of Contents
- [Members](#Members)
- [Access to explain video](#Access-to-explain-video)
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Example Input](#example-input)
- [License](#license)

## Members
- Kevin Pérez Román

## Access to explain video
- Link: https://javerianacaliedu-my.sharepoint.com/:f:/g/personal/kevinjave_javerianacali_edu_co/EsT9BzawNUlKmZU4Mcb8PasBMB4LRfTNtkGGb-jwk3-Xdw?e=hXKPXT

## Overview
The **MLQ Scheduler** is a CPU scheduling algorithm that divides processes into multiple queues based on their type or priority. Each queue can implement a different scheduling algorithm. This implementation supports three types of scheduling algorithms:
- **Round Robin (RR)**
- **First Come First Serve (FCFS)**
- **Shortest Job First (SJF)**

Processes are read from an input file and placed in the appropriate queue. The program then simulates the scheduling and execution of the processes.

## Features
- Supports **Round Robin**, **FCFS**, and **SJF** scheduling algorithms.
- Reads processes from a file (`processes.txt`).
- Allows setting the time quantum for the Round Robin scheduler.
- Calculates and displays the **Waiting Time (WT)** and **Response Time (RT)** for each process.

## Project Structure
The project consists of three main files:

1. **proccess.hpp**: Defines the `proccess` class, which represents a process with attributes like ID, arrival time, burst time, priority, and methods to get or set these attributes.

2. **MLQ.hpp**: Defines the `MLQ` class, which manages the scheduling logic, including different queues for RR, FCFS, and SJF. It handles adding processes to queues, executing them, and calculating waiting times and response times.

3. **main.cpp**: The main driver of the program. It reads processes from a file, initializes the scheduler, and simulates the scheduling process.

## Installation
To compile and run the project, follow these steps:

1. Ensure you have a C++ compiler installed (e.g., g++, clang++).
2. Clone or download the project.
3. Compile the project with the following command:

   ```bash
   g++ main.cpp proccess.cpp MLQ.cpp
   ```

4. Run the executable:

   ```bash
   a.exe
   ```

## Usage
1. Just run the executable file then is all information.

2. **Set Time Quantum**: In the `main.cpp` file, you can set the time quantum for the **Round Robin (RR)** scheduling algorithm by modifying the following line:

   ```cpp
   scheduler.SetQuantum(3);
   ```

3. **Run the Scheduler**: After compiling and running the program, it will read the processes from the input file, simulate the scheduling, and print the results to the console.

## Example Input
```plaintext
**********************
Table of each proccess
**********************
ID | WT | RT
P1 | 10 | 0
P2 | 3 | 3
P3 | 14 | 10
P4 | 6 | 6
P5 | 18 | 18
P7 | 21 | 21

```

The above input file defines three processes:
- `P1` is in the **Round Robin** queue, arriving at time 0, requiring 5 units of burst time, with priority 2.
- `P2` is in the **FCFS** queue, arriving at time 2, requiring 3 units of burst time, with priority 1.
- `P4` is in the **SJF** queue, arriving at time 4, requiring 2 units of burst time, with priority 3.


