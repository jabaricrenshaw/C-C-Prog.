#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int numOfProcesses;     // keeps track of number of processes 

// Struct to create a process, holds all of its information 
struct process {
    int id;             // id to identify process 
    int timeNeeded;     // time needed to run to completion 
    int priority;       // priority of process (for HPF only)
    bool usedPriority;       //marker to show if process has been used already (HPF only)
    int slices;     // amount of slices needed to complete process (for RR only)
    int waitTime;       // total time in ready queue
    int turnAround;     // span of time of submission to complete time (for FCFS and HPF) 
};

struct process rawInput[];      // array to hold raw input by user, not sorted by scheduler

/** 
 * FIRST COME FIRST SERVE SORTING ALGORITHM 
 */
void fcfs() {
    struct process readyQueue[numOfProcesses];    // ready queue, will hold all of the processes in the scheduled order

    double totalTime = 0;
    double totalWait = 0;
    double totalTurnaround = 0;
    float throughput;

    // Place processes in the ready queue by the order they are inputted 
    for (int i = 0; i < numOfProcesses; i++) {
        readyQueue[i] = rawInput[i];
    }

    printf("\nProcess list in FCFS order entered:\n");
    for (int i = 0; i < numOfProcesses; i++) {
        printf("%d %d %d\n", readyQueue[i].id, readyQueue[i].timeNeeded, readyQueue[i].priority);
        readyQueue[i].waitTime += totalTime;
        readyQueue[i].turnAround += readyQueue[i].waitTime + readyQueue[i].timeNeeded;
        totalTime += readyQueue[i].timeNeeded;
    }

    printf("End of list.\n\n");
    
    for (int i = 0; i < numOfProcesses; i++) {
        printf("fcfs wait of p%d = %d\n", readyQueue[i].id, readyQueue[i].waitTime);
        totalWait += readyQueue[i].waitTime;
    }

    printf("average wait time for %d procs = %0.1f\n", numOfProcesses, (double) (totalWait/numOfProcesses));
    
    for (int i = 0; i < numOfProcesses; i++) {
        printf("fcfs turn-around time for p%d = %d\n", readyQueue[i].id, readyQueue[i].turnAround);
        totalTurnaround += readyQueue[i].turnAround;
    }

    printf("average turn-around for %d procs = %0.1f\n", numOfProcesses, (double) (totalTurnaround / numOfProcesses));

    printf("fcfs throughput for %d procs = %f proc/ms\n", numOfProcesses, (double) (numOfProcesses/totalTime));
    printf("\n<><> end FCFS schedule <><>\n");

}

/** 
 * HIGHEST PRIORITY FIRST SORTING ALGORITHM 
 */
void hpf() {
    struct process readyQueue[numOfProcesses];    // ready queue, holds all of the processes in the scheduled order
    int readyIndex = 0;                           // keep track of the indexes in the ready queue 

    double totalTime = 0;
    double totalWait = 0;
    double totalTurnaround = 0;
    float throughput;
    int currentPriority = 100;                    // keeps track of the current priority 
    int lastUsedPriority = -1;                    // keeps track of the last used priority 
    int usedIndex;                                // keeps track of the last used index in the rawInput (when sorting)
    struct process currentHighestProcess;         // struct process object to hold the process being moved into the ready queue 

    // Sorting by priority 
    while (readyIndex != numOfProcesses) {
        
        for (int i = 0; i < numOfProcesses; i++) {
            if ((rawInput[i].priority < currentPriority) && (rawInput[i].priority > lastUsedPriority) && (rawInput[i].usedPriority != true)) {
                currentPriority = rawInput[i].priority;
                currentHighestProcess = rawInput[i];
                usedIndex = i;
            }
        }

        readyQueue[readyIndex] = currentHighestProcess;
        currentPriority = 100;
        lastUsedPriority = currentHighestProcess.priority; 
        rawInput[usedIndex].usedPriority = true;

        readyIndex++;
    }

    printf("\nProcess list in HPF order:\n");
    for (int i = 0; i < numOfProcesses; i++) {
        printf("%d %d %d\n", readyQueue[i].id, readyQueue[i].timeNeeded, readyQueue[i].priority);
        readyQueue[i].waitTime += totalTime;
        readyQueue[i].turnAround += readyQueue[i].waitTime + readyQueue[i].timeNeeded;
        totalTime += readyQueue[i].timeNeeded;
    }

    printf("End of list.\n\n");
    
    for (int i = 0; i < numOfProcesses; i++) {
        printf("hpf wait of p%d = %d\n", readyQueue[i].id, readyQueue[i].waitTime);
        totalWait += readyQueue[i].waitTime;
    }

    printf("average wait time for %d procs = %0.1f\n", numOfProcesses, (double) (totalWait/numOfProcesses));
    
    for (int i = 0; i < numOfProcesses; i++) {
        printf("hpf turn-around time for p%d = %d\n", readyQueue[i].id, readyQueue[i].turnAround);
        totalTurnaround += readyQueue[i].turnAround;
    }

    printf("average turn-around for %d procs = %0.1f\n", numOfProcesses, (double) (totalTurnaround / numOfProcesses));

    printf("hpf throughput for %d procs = %f proc/ms\n", numOfProcesses, (double) (numOfProcesses/totalTime));
    printf("\n<><> end HPF schedule <><>\n");
}

/** 
 * ROUND ROBIN SORTING ALGORITHM 
 */
void roundRobin() {
    struct process readyQueue[numOfProcesses];    // ready queue, holds all of the processes in the scheduled order

    double totalTime = 0;
    double totalTimeLeft = 0;
    double completionTime = 0;                      // highest turnaround value - for calculating throughput
    
    double avgTime;
    float throughput;
    int quantum;    // only for RR
    int overhead;   // only for RR
    double totalTurnaround;
    bool allComplete = false;

    // Place processes in the ready queue by the order they are inputted
    for (int i = 0; i < numOfProcesses; i++) {
        readyQueue[i] = rawInput[i];
    }

    // Print the process list.
    printf("\nProcess list for RR in order entered:\n");
    for (int i = 0; i < numOfProcesses; i++) {
        printf("%d %d %d\n", readyQueue[i].id, readyQueue[i].timeNeeded, readyQueue[i].priority);
    }
    
    printf("End of list.\n");

    // VARY THESE! 1 <= q <= 5, 1 <= p <= q
    quantum = 5;
    overhead = 5; 
    printf("\npreemptive RR schedule, quantum = %d overhead = %d\n", quantum, overhead);
    
    // Calculating wait time and time slices. 
    while (!allComplete) {
        // iterate through the array to check first if all processes are complete. 
        // If not, then update condition boolean then update total time, wait time and slice count of the current index.
        for (int i = 0; i < numOfProcesses; i++) {
            if (readyQueue[i].timeNeeded == 0) {
                continue;
            } else {
                readyQueue[i].waitTime += totalTime - (quantum * readyQueue[i].slices);
                if (readyQueue[i].timeNeeded - quantum == 0 || readyQueue[i].timeNeeded < quantum) {
                    totalTime += quantum;
                    readyQueue[i].slices ++;
                    readyQueue[i].timeNeeded = 0;
                } else {
                    totalTime += quantum;
                    readyQueue[i].slices ++;
                    readyQueue[i].timeNeeded -= quantum;
                }
                
                totalTime += overhead;
            }
        }

        for (int i = 0; i < numOfProcesses; i++) {
            totalTimeLeft += readyQueue[i].timeNeeded;
        }

        if (totalTimeLeft == 0) {
            allComplete = true;
        } else {
            allComplete = false;
            totalTimeLeft = 0;
        }

    }

    //  Update waiting times, turn around for each process, and total turn around for this scheduling session. Then, search for highest turnaround.
    for (int i = 0; i < numOfProcesses; i++) {
        readyQueue[i].turnAround = readyQueue[i].waitTime + rawInput[i].timeNeeded;
        printf("RR TA time for finished p%d = %d, needed: %d ms, and %d time slices.\n", readyQueue[i].id, readyQueue[i].turnAround, rawInput[i].timeNeeded, readyQueue[i].slices);
        totalTurnaround += readyQueue[i].turnAround;

        if (completionTime < readyQueue[i].turnAround) {
            completionTime = readyQueue[i].turnAround;
        }
    }

    printf("RR Throughput, %d procs, with q: %d, o: %d, is: %f p/ms, or %0.3f p/us\n", numOfProcesses, quantum, overhead, (double) (numOfProcesses/completionTime), (float) (1000*(numOfProcesses/completionTime)));
    
    printf("Average RR TA, %d procs, with q: %d, o: %d, is: %0.1f\n", numOfProcesses, quantum, overhead, (double) (totalTurnaround / numOfProcesses));

    printf("\n<><> end preemptive RR schedule <><>\n");                
}

int main(int argc, char* argv[]) {
    int x, y, z;

    if (argc != 1) {
        fprintf(stderr, "Error: Please enter [out_file name]");
        exit(-1);
    } else {
       printf("Enter triples: process id, time in ms, and priority. Enter 'end' when done\n");
       printf("For example:\n");
       printf("1 12 0\n");
       printf("3  9 1\n");
       printf("2 99 9\n");
       printf("end\n");
       printf("process 1 needs 12 ms and has priority 0 (highest)\n");
       printf("process 3 needs  9 ms and has priority 1\n");
       printf("process 2 needs 99 ms and has priority 9\n");
       
       while (scanf("%d %d %d", &x, &y, &z) == 3) {
           numOfProcesses++;
           rawInput[numOfProcesses-1].id = x;
           rawInput[numOfProcesses-1].timeNeeded = y;
           rawInput[numOfProcesses-1].priority = z;
           rawInput[numOfProcesses-1].usedPriority = false;
           rawInput[numOfProcesses-1].slices = 0;
           rawInput[numOfProcesses-1].waitTime = 0;
           rawInput[numOfProcesses-1].turnAround = 0;

           /*printf("process id = %d\n", rawInput[numOfProcesses-1].id);
           printf("time needed = %d\n", rawInput[numOfProcesses-1].timeNeeded);
           printf("priority = %d\n", rawInput[numOfProcesses-1].priority);*/
       }

       fcfs();
       hpf();
       roundRobin();
    }
}