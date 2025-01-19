#include <stdio.h>
#include <stdbool.h>

#define MAX 10 

int allocation[MAX][MAX], max[MAX][MAX], need[MAX][MAX], available[MAX];
int safeSequence[MAX];
int n, m; 

void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe() {
    int work[MAX];
    bool finish[MAX] = {false};
    int count = 0;

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nThe system is not in a safe state.\n");
            return false;
        }
    }

    printf("\nThe system is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

void displayTable() {
    printf("\nResource Allocation Table:\n");
    printf("Processes | Allocation       | Max             | Need            | Available\n");
    printf("          |");
    for (int j = 0; j < m; j++) printf(" R%d", j);
    printf("       |");
    for (int j = 0; j < m; j++) printf(" R%d", j);
    printf("       |");
    for (int j = 0; j < m; j++) printf(" R%d", j);
    printf("       |");
    for (int j = 0; j < m; j++) printf(" R%d", j);
    printf("\n");

    int work[MAX];
    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    for (int i = 0; i < n; i++) {
        printf("P%d        |", i);
        for (int j = 0; j < m; j++) {
            printf(" %2d", allocation[i][j]);
        }
        printf("       |");
        for (int j = 0; j < m; j++) {
            printf(" %2d", max[i][j]);
        }
        printf("       |");
        for (int j = 0; j < m; j++) {
            printf(" %2d", need[i][j]);
        }
        printf("       |");
        for (int j = 0; j < m; j++) {
            printf(" %2d", work[j]);
        }
        printf("\n");
        for (int j = 0; j < m; j++) {
            work[j] += allocation[i][j];
        }
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    calculateNeed();
    displayTable();
    isSafe();

    return 0;
}
