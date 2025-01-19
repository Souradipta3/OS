#include <stdio.h>

struct Process {
    int id;
    int bt;
    int priority;
};

void findWaitingTime(int n, struct Process processes[], int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = processes[i - 1].bt + wt[i - 1];
    }
}

void findTurnAroundTime(int n, struct Process processes[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = processes[i].bt + wt[i];
    }
}

void sortProcessesByPriority(int n, struct Process processes[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void findAvgTime(int n, struct Process processes[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(n, processes, wt);
    findTurnAroundTime(n, processes, wt, tat);

    printf("Processes\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].bt, processes[i].priority, wt[i], tat[i]);
    }

    printf("\nAverage waiting time = %.2f", (float)total_wt / n);
    printf("\nAverage turnaround time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].bt);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    sortProcessesByPriority(n, processes);
    findAvgTime(n, processes);
    return 0;
}