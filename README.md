Here's the updated README with the **MLFQ** (Multi-Level Feedback Queue) scheduling algorithm added, following the same structure as your original document:

---

# Multilevel Queue (MLQ) and Multilevel Feedback Queue (MLFQ) Scheduler

This project implements both a **Multilevel Queue (MLQ) Scheduler** and a **Multilevel Feedback Queue (MLFQ) Scheduler** that simulate process scheduling using multiple queues, each with different scheduling algorithms or priority levels. The program reads processes from a file, assigns them to appropriate queues, and simulates their execution based on the defined scheduling algorithms.

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
This project supports two types of CPU scheduling algorithms:
- **Multilevel Queue (MLQ)**: Divides processes into multiple queues based on their type or priority, with each queue possibly using a different scheduling algorithm such as **Round Robin (RR)**, **First Come First Serve (FCFS)**, or **Shortest Job First (SJF)**.
- **Multilevel Feedback Queue (MLFQ)**: Dynamically adjusts the priority of processes based on their execution history. It uses multiple queues, and processes can move between queues based on how much CPU time they consume.

### MLQ Scheduler
In the **MLQ Scheduler**, processes are assigned to a queue at the time of creation based on their priority or type. Each queue may have a different scheduling algorithm (RR, FCFS, or SJF), and processes remain in their assigned queue until completion.

### MLFQ Scheduler
The **MLFQ Scheduler** is more dynamic. Processes are initially placed in a higher-priority queue and may be demoted to a lower-priority queue if they consume more CPU time. The MLFQ uses Round Robin for higher-priority queues and FCFS for lower-priority queues. This approach helps balance short- and long-running processes, preventing any single process from monopolizing the CPU.

## Features
- Supports **Round Robin**, **FCFS**, **SJF**, and **MLFQ** scheduling algorithms.
- Reads processes from a file (`processes.txt`).
- Allows setting the time quantum for the Round Robin scheduler.
- Dynamically adjusts the priority of processes in the MLFQ based on their behavior.
- Calculates and displays the **Waiting Time (WT)** and **Response Time (RT)** for each process.

## Project Structure
The project consists of several key files:

1. **proccess.hpp**: Defines the `proccess` class, representing a process with attributes such as ID, arrival time, burst time, priority, and methods to access or modify these attributes.

2. **MLQ.hpp**: Defines the `MLQ` class, which handles the scheduling logic for the Multilevel Queue algorithm. It manages multiple queues, adds processes to them, and simulates the execution based on RR, FCFS, or SJF.

3. **MLFQ.hpp**: Defines the `MLFQ` class, which handles the dynamic scheduling logic for the Multilevel Feedback Queue algorithm. It adjusts the priority of processes based on how much CPU time they have used and manages multiple priority levels.

4. **main.cpp**: The main driver of the program. It reads processes from a file, initializes the appropriate scheduler (MLQ or MLFQ), and simulates the scheduling process.

## Installation
To compile and run the project, follow these steps:

1. Ensure you have a C++ compiler installed (e.g., g++, clang++).
2. Clone or download the project.
3. Compile the project with the following command:

   ```bash
   g++ main.cpp proccess.cpp MLQ.cpp MLFQ.cpp
   ```

4. Run the executable:

   ```bash
   a.exe
   ```

## Usage
1. **Run the Executable**: After compiling the project, simply run the executable. The program will read processes from the input file, schedule them using the selected algorithm, and print the results.

2. **Set Time Quantum**: In the `main.cpp` file, you can set the time quantum for the **Round Robin (RR)** scheduling algorithm by modifying the following line:

   ```cpp
   scheduler.SetQuantum(3);
   ```

3. **Choose Scheduling Algorithm**: You can choose between the **MLQ** or **MLFQ** scheduler by modifying the `main.cpp` to initialize the appropriate class (`MLQ` or `MLFQ`) and invoking its methods.

## Example Input
```plaintext
P1 RR 0 5 1
P2 FCFS 3 3 1
P3 RR 4 7 1
P4 SJF 6 4 1
P5 RR 8 2 1
P6 SJF 9 3 1
P7 RR 11 4 1
```
