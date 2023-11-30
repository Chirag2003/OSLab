#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 10

int num_of_process;
int arrival_time[MAX_PROCESS];
int burst_time[MAX_PROCESS];
int completion_time[MAX_PROCESS];
int waiting_time[MAX_PROCESS];
int turnaround_time[MAX_PROCESS];
int response_time[MAX_PROCESS];

// Function prototypes
void getProcessInfo();
void calculateFCFS();
void calculateAverageTimes(float *avg_waiting_time, float *avg_turnaround_time);
void displayResults(float avg_waiting_time, float avg_turnaround_time);

int main() {
    getProcessInfo();
    calculateFCFS();

    float avg_waiting_time, avg_turnaround_time;
    calculateAverageTimes(&avg_waiting_time, &avg_turnaround_time);

    displayResults(avg_waiting_time, avg_turnaround_time);

    return 0;
}

// Function to calculate FCFS scheduling
void calculateFCFS() {
    int current_time = 0;

    for (int i = 0; i < num_of_process; i++) {
        response_time[i] = current_time - arrival_time[i];
        completion_time[i] = (current_time < arrival_time[i]) ? arrival_time[i] + burst_time[i] : current_time + burst_time[i];
        current_time = completion_time[i];
        waiting_time[i] = completion_time[i] - burst_time[i] - arrival_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
    }
}
// Function to calculate average waiting time and average turnaround time
void calculateAverageTimes(float *avg_waiting_time, float *avg_turnaround_time) {
    *avg_waiting_time = 0.0;
    *avg_turnaround_time = 0.0;

    for (int i = 0; i < num_of_process; i++) {
        *avg_waiting_time += waiting_time[i];
        *avg_turnaround_time += turnaround_time[i];
    }

    *avg_waiting_time /= num_of_process;
    *avg_turnaround_time /= num_of_process;
}

// Function to display results
void displayResults(float avg_waiting_time, float avg_turnaround_time) {
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < num_of_process; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i], response_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}