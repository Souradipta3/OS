#include <stdio.h>

void sortByPriority(int processes[], int burst_time[], int priority[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                
                int temp = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp;

                int temp_bt = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp_bt;
                
                int temp_pid = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp_pid;
            }
        }
    }
}

void calculateTimes(int burst_time[], int waiting_time[], int turnaround_time[], int n) {
    waiting_time[0] = 0; 
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }
}

void displayResults(int processes[], int burst_time[], int priority[], int waiting_time[], int turnaround_time[], int n) {
    printf("PId\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], priority[i], waiting_time[i], turnaround_time[i]);
    }

    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], priority[n], waiting_time[n], turnaround_time[n];

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Enter priority for process P%d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    sortByPriority(processes, burst_time, priority, n);
    calculateTimes(burst_time, waiting_time, turnaround_time, n);
    displayResults(processes, burst_time, priority, waiting_time, turnaround_time, n);

    return 0;
}
