#include <stdio.h>

void roundRobin(int processes[], int n, int burst_time[], int time_quantum) {
    int waiting_time[n], turnaround_time[n], remaining_time[n];
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] <= time_quantum) {
                    
                    time += remaining_time[i];
                    remaining_time[i] = 0;
                    waiting_time[i] = time - burst_time[i];
                    turnaround_time[i] = time;
                    completed++;
                } else {
                    
                    time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
            }
        }
    }

    printf("PId\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    roundRobin(processes, n, burst_time, time_quantum);

    return 0;
}
