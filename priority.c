#include <stdio.h>
#include <stdlib.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
};

void PriorityNonPreemptive(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];
    int remaining_time[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    int complete = 0, time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (complete < n) {
        int highest_priority = -1;
        int highest_priority_idx = -1;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= time && remaining_time[j] > 0) {
                if (highest_priority == -1 || processes[j].priority < highest_priority) {
                    highest_priority = processes[j].priority;
                    highest_priority_idx = j;
                }
            }
        }

        int idx = highest_priority_idx;
        remaining_time[idx] = 0;
        complete++;

        waiting_time[idx] = time - processes[idx].arrival_time;
        turnaround_time[idx] = waiting_time[idx] + processes[idx].burst_time;

        total_waiting_time += waiting_time[idx];
        total_turnaround_time += turnaround_time[idx];

        time += processes[idx].burst_time;
    }

    printf("Non-Preemptive Priority Scheduling:\n");
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.1f\t\t%.1f\n", processes[i].process_id, (float)waiting_time[i], (float)turnaround_time[i]);
    }
}

void PriorityPreemptive(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];
    int remaining_time[n];

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    int complete = 0, time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    while (complete < n) {
        int highest_priority = -1;
        int highest_priority_idx = -1;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= time && remaining_time[j] > 0) {
                if (highest_priority == -1 || processes[j].priority < highest_priority) {
                    highest_priority = processes[j].priority;
                    highest_priority_idx = j;
                }
            }
        }

        int idx = highest_priority_idx;

        if (idx == -1) {
            time++;
        } else {
            remaining_time[idx]--;

            if (remaining_time[idx] == 0) {
                complete++;
                turnaround_time[idx] = time - processes[idx].arrival_time + 1;
                waiting_time[idx] = turnaround_time[idx] - processes[idx].burst_time;
                total_waiting_time += waiting_time[idx];
                total_turnaround_time += turnaround_time[idx];
            }

            time++;
        }
    }

    printf("Preemptive Priority Scheduling:\n");
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.1f\t\t%.1f\n", processes[i].process_id, (float)waiting_time[i], (float)turnaround_time[i]);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter Priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    PriorityNonPreemptive(processes, n);
    PriorityPreemptive(processes, n);

    return 0;
}
