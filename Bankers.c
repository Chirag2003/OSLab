#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int max_claim[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int n, m; // Number of processes and resources

// Function to initialize the need matrix
void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max_claim[i][j] - allocation[i][j];
        }
    }
}

// Function to check if a process can be allocated resources
int isSafe(int process, int work[], int finish[]) {
    for (int i = 0; i < m; i++) {
        if (need[process][i] > work[i])
            return 0;
    }
    return 1;
}

// Banker's Algorithm to check if the system is in a safe state
int checkSafeState() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];

    // Initialize work and finish arrays
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    // Find a safe sequence
    for (int i = 0; i < n; i++) {
        if (finish[i] == 0 && isSafe(i, work, finish)) {
            safeSequence[count++] = i;
            for (int j = 0; j < m; j++) {
                work[j] += allocation[i][j];
            }
            finish[i] = 1;
            i = -1; // Start over to check all processes again
        }
    }

    // Check if a safe sequence was found
    if (count == n) {
        printf("System is in a safe state.\nSafe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("%d", safeSequence[i]);
            if (i < n - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
        return 1;
    } else {
        printf("System is not in a safe state.\n");
        return 0;
    }
}
int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum claim matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max_claim[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    calculateNeed();
    checkSafeState();
    return 0;
}
