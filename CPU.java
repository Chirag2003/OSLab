import java.util.Scanner;

public class CPU {

    public static final int MAX_PROCESS = 10;
    public static int num_of_process;
    public static int[] arrival_time = new int[MAX_PROCESS];
    public static int[] burst_time = new int[MAX_PROCESS];
    public static int[] completion_time = new int[MAX_PROCESS];
    public static int[] waiting_time = new int[MAX_PROCESS];
    public static int[] turnaround_time = new int[MAX_PROCESS];
    public static int[] response_time = new int[MAX_PROCESS];
    public static int[] priority = new int[MAX_PROCESS];

    public static void main(String[] args) {
        int selected_algorithm;
        int time_quantum;

        Scanner scanner = new Scanner(System.in);

        System.out.println("Select a scheduling algorithm:");
        System.out.println("1. First-Come-First-Served");
        System.out.println("2. Shortest Job First");
        System.out.println("3. Priority Scheduling (Preeemptive)");
        System.out.println("4. Priority Scheduling (Non-Preemptive)");
        System.out.println("5. Round Robin");
        System.out.print("Enter your choice: ");
        selected_algorithm = scanner.nextInt();

        getProcessInfo(selected_algorithm, scanner);

        switch (selected_algorithm) {
            case 1:
                calculateFCFS();
                break;
            case 2:
                calculateSJF(selected_algorithm);
                break;
            case 3:
                calculatePriority(true); // Primitive Priority Scheduling
                break;
            case 4:
                calculatePriority(false); // Non-Primitive Priority Scheduling
                break;
            case 5:
                System.out.print("Enter Time Quantum for Round Robin: ");
                time_quantum = scanner.nextInt();
                calculateRoundRobin(time_quantum);
                break;
            default:
                System.out.println("Invalid choice. Please select a valid scheduling algorithm.");
                break;
        }

        float avg_waiting_time = 0.0f;
        float avg_turnaround_time = 0.0f;

        calculateAverageTimes(avg_waiting_time, avg_turnaround_time);

        displayResults(avg_waiting_time, avg_turnaround_time);
    }

    public static void getProcessInfo(int selected_algorithm, Scanner scanner) {
        System.out.print("Enter total number of processes (maximum " + MAX_PROCESS + "): ");
        num_of_process = scanner.nextInt();

        if (num_of_process < 1 || num_of_process > MAX_PROCESS) {
            System.out.println("Invalid number of processes. Please enter a number between 1 and " + MAX_PROCESS + ".");
            System.exit(1);
        }

        for (int i = 0; i < num_of_process; i++) {
            System.out.println("\nProcess " + (i + 1) + ":");
            System.out.print("Arrival Time: ");
            arrival_time[i] = scanner.nextInt();
            System.out.print("Burst Time: ");
            burst_time[i] = scanner.nextInt();

            if (selected_algorithm == 3 || selected_algorithm == 4) {
                System.out.print("Priority: ");
                priority[i] = scanner.nextInt();
            }
        }
    }

    public static void calculateFCFS() {
        int current_time = 0;

        for (int i = 0; i < num_of_process; i++) {
            response_time[i] = current_time - arrival_time[i];
            completion_time[i] = (current_time < arrival_time[i]) ? arrival_time[i] + burst_time[i] : current_time + burst_time[i];
            current_time = completion_time[i];
            waiting_time[i] = completion_time[i] - burst_time[i] - arrival_time[i];
            turnaround_time[i] = completion_time[i] - arrival_time[i];
        }
    }

    public static void calculateSJF(int selected_algorithm) {
        for (int i = 0; i < num_of_process - 1; i++) {
            for (int j = 0; j < num_of_process - i - 1; j++) {
                if (burst_time[j] > burst_time[j + 1]) {
                    int temp_burst = burst_time[j];
                    burst_time[j] = burst_time[j + 1];
                    burst_time[j + 1] = temp_burst;

                    int temp_arrival = arrival_time[j];
                    arrival_time[j] = arrival_time[j + 1];
                    arrival_time[j + 1] = temp_arrival;

                    if (selected_algorithm == 3 || selected_algorithm == 4) {
                        int temp_priority = priority[j];
                        priority[j] = priority[j + 1];
                        priority[j + 1] = temp_priority;
                    }
                }
            }
        }

        int current_time = 0;

        for (int i = 0; i < num_of_process; i++) {
            response_time[i] = current_time - arrival_time[i];
            completion_time[i] = (current_time < arrival_time[i]) ? arrival_time[i] + burst_time[i] : current_time + burst_time[i];
            current_time = completion_time[i];
            waiting_time[i] = completion_time[i] - burst_time[i] - arrival_time[i];
            turnaround_time[i] = completion_time[i] - arrival_time[i];
        }
    }

    public static void calculatePriority(boolean isPrimitive) {
        for (int i = 0; i < num_of_process - 1; i++) {
            for (int j = 0; j < num_of_process - i - 1; j++) {
                if (isPrimitive) {
                    if (priority[j] > priority[j + 1]) {
                        swapProcesses(j, j + 1);
                        if (isPrimitive) {
                            int temp_priority = priority[j];
                            priority[j] = priority[j + 1];
                            priority[j + 1] = temp_priority;
                        }
                    }
                }
            }
        }

        int current_time = 0;

        for (int i = 0; i < num_of_process; i++) {
            response_time[i] = current_time - arrival_time[i];
            completion_time[i] = (current_time < arrival_time[i]) ? arrival_time[i] + burst_time[i] : current_time + burst_time[i];
            current_time = completion_time[i];
            waiting_time[i] = completion_time[i] - burst_time[i] - arrival_time[i];
            turnaround_time[i] = completion_time[i] - arrival_time[i];
        }
    }

    public static void swapProcesses(int index1, int index2) {
        int temp_arrival = arrival_time[index1];
        arrival_time[index1] = arrival_time[index2];
        arrival_time[index2] = temp_arrival;

        int temp_burst = burst_time[index1];
        burst_time[index1] = burst_time[index2];
        burst_time[index2] = temp_burst;
    }

    public static void swapPriority(int index1, int index2) {
        int temp_priority = priority[index1];
        priority[index1] = priority[index2];
        priority[index2] = temp_priority;
    }

    public static void calculateRoundRobin(int time_quantum) {
        int[] remaining_time = new int[MAX_PROCESS];
        for (int i = 0; i < num_of_process; i++) {
            remaining_time[i] = burst_time[i];
        }

        int current_time = 0;

        while (true) {
            int done = 1;

            for (int i = 0; i < num_of_process; i++) {
                if (remaining_time[i] > 0) {
                    done = 0;

                    if (remaining_time[i] > time_quantum) {
                        current_time += time_quantum;
                        remaining_time[i] -= time_quantum;
                    } else {
                        current_time += remaining_time[i];
                        completion_time[i] = current_time;
                        waiting_time[i] = current_time - burst_time[i] - arrival_time[i];
                        turnaround_time[i] = completion_time[i] - arrival_time[i];
                        remaining_time[i] = 0;
                    }
                }
            }

            if (done == 1) {
                break;
            }
        }
    }

    public static void calculateAverageTimes(float avg_waiting_time, float avg_turnaround_time) {
        avg_waiting_time = 0.0f;
        avg_turnaround_time = 0.0f;

        for (int i = 0; i < num_of_process; i++) {
            avg_waiting_time += waiting_time[i];
            avg_turnaround_time += turnaround_time[i];
        }

        avg_waiting_time /= num_of_process;
        avg_turnaround_time /= num_of_process;
    }

    public static void displayResults(float avg_waiting_time, float avg_turnaround_time) {
        System.out.println("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time");
        for (int i = 0; i < num_of_process; i++) {
            System.out.println(i + 1 + "\t" + arrival_time[i] + "\t\t" + burst_time[i] + "\t\t" + completion_time[i] + "\t\t" + waiting_time[i] + "\t\t" + turnaround_time[i] + "\t\t" + response_time[i]);
        }

        System.out.println("\nAverage Waiting Time: " + avg_waiting_time);
        System.out.println("Average Turnaround Time: " + avg_turnaround_time);
    }
}