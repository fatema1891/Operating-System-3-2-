#include<bits/stdc++.h>
using namespace std;

// Global variables for Gantt Chart
int gantt_pid[1000], gantt_time[1000], gantt_size;

// Function to print results with Gantt chart
void printResult(int pid[], int at[], int bt[], int pr[],
                 int ct[], int tat[], int wt[], int n, string name) {

    cout << "\n=== " << name << " ===\n";
    cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    cout << "------------------------------------------------\n";

    double total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << pr[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
        total_wt += wt[i];
        total_tat += tat[i];
    }

    cout << "------------------------------------------------\n";
    cout << "Average WT: " << fixed << setprecision(2) << total_wt / n << endl;
    cout << "Average TAT: " << fixed << setprecision(2) << total_tat / n << endl;

    // Print Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << " ";
    for (int i = 0; i < gantt_size; i++) cout << "--------";
    cout << "\n|";
    for (int i = 0; i < gantt_size; i++) {
        if (gantt_pid[i] == -1) cout << "  Idle  |";
        else cout << "  P" << gantt_pid[i] << "   |";
    }
    cout << "\n ";
    for (int i = 0; i < gantt_size; i++) cout << "--------";
    cout << "\n" << gantt_time[0];
    for (int i = 0; i < gantt_size; i++) cout << "\t" << gantt_time[i];
    cout << "\n\n";
}

// ============ SJF NON-PREEMPTIVE ============
void sjfNonPreemptive(int pid[], int at[], int bt[], int pr[], int n) {
    int ct[100], tat[100], wt[100];
    bool completed[100] = {false};
    gantt_size = 0;

    int completed_count = 0, current_time = 0;

    while (completed_count < n) {
        int idx = -1;
        int min_bt = INT_MAX;

        // Find process with minimum burst time among arrived processes
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= current_time) {
                if (bt[i] < min_bt) {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        // If no process available, CPU goes idle
        if (idx == -1) {
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!completed[i] && at[i] < next_arrival) {
                    next_arrival = at[i];
                }
            }
            gantt_pid[gantt_size] = -1;
            gantt_time[gantt_size] = current_time;
            gantt_size++;
            current_time = next_arrival;
            continue;
        }

        // Execute the selected process
        current_time += bt[idx];
        ct[idx] = current_time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        completed[idx] = true;
        completed_count++;

        gantt_pid[gantt_size] = pid[idx];
        gantt_time[gantt_size] = current_time;
        gantt_size++;
    }

    printResult(pid, at, bt, pr, ct, tat, wt, n, "SJF Non-Preemptive");
}

// ============ SJF PREEMPTIVE (SRTF) ============
void sjfPreemptive(int pid[], int at[], int bt[], int pr[], int n) {
    int ct[100], tat[100], wt[100];
    int remaining_bt[100];
    bool completed[100] = {false};
    gantt_size = 0;

    // Copy burst times to remaining_bt
    for (int i = 0; i < n; i++) remaining_bt[i] = bt[i];

    int completed_count = 0, current_time = 0;
    int last_pid = -1;

    while (completed_count < n) {
        int idx = -1;
        int min_remaining = INT_MAX;

        // Find process with minimum remaining time
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= current_time) {
                if (remaining_bt[i] < min_remaining) {
                    min_remaining = remaining_bt[i];
                    idx = i;
                }
            }
        }

        // If no process available, CPU goes idle
        if (idx == -1) {
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!completed[i] && at[i] < next_arrival) {
                    next_arrival = at[i];
                }
            }
            if (last_pid != -1) {
                gantt_pid[gantt_size] = last_pid;
                gantt_time[gantt_size] = current_time;
                gantt_size++;
                last_pid = -1;
            }
            current_time = next_arrival;
            continue;
        }

        // Record context switch
        if (last_pid != pid[idx]) {
            if (last_pid != -1) {
                gantt_pid[gantt_size] = last_pid;
                gantt_time[gantt_size] = current_time;
                gantt_size++;
            }
            last_pid = pid[idx];
        }

        // Execute for 1 unit
        remaining_bt[idx]--;
        current_time++;

        // If process completed
        if (remaining_bt[idx] == 0) {
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed[idx] = true;
            completed_count++;
            gantt_pid[gantt_size] = pid[idx];
            gantt_time[gantt_size] = current_time;
            gantt_size++;
            last_pid = -1;
        }
    }

    printResult(pid, at, bt, pr, ct, tat, wt, n, "SJF Preemptive (SRTF)");
}

// ============ PRIORITY NON-PREEMPTIVE ============
void priorityNonPreemptive(int pid[], int at[], int bt[], int pr[], int n) {
    int ct[100], tat[100], wt[100];
    bool completed[100] = {false};
    gantt_size = 0;

    int completed_count = 0, current_time = 0;

    while (completed_count < n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        // Find process with highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= current_time) {
                if (pr[i] < highest_priority) {
                    highest_priority = pr[i];
                    idx = i;
                }
            }
        }

        // If no process available, CPU goes idle
        if (idx == -1) {
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!completed[i] && at[i] < next_arrival) {
                    next_arrival = at[i];
                }
            }
            gantt_pid[gantt_size] = -1;
            gantt_time[gantt_size] = current_time;
            gantt_size++;
            current_time = next_arrival;
            continue;
        }

        // Execute the selected process
        current_time += bt[idx];
        ct[idx] = current_time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        completed[idx] = true;
        completed_count++;

        gantt_pid[gantt_size] = pid[idx];
        gantt_time[gantt_size] = current_time;
        gantt_size++;
    }

    printResult(pid, at, bt, pr, ct, tat, wt, n, "Priority Non-Preemptive");
}

// ============ PRIORITY PREEMPTIVE ============
void priorityPreemptive(int pid[], int at[], int bt[], int pr[], int n) {
    int ct[100], tat[100], wt[100];
    int remaining_bt[100];
    bool completed[100] = {false};
    gantt_size = 0;

    // Copy burst times
    for (int i = 0; i < n; i++) remaining_bt[i] = bt[i];

    int completed_count = 0, current_time = 0;
    int last_pid = -1;

    while (completed_count < n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        // Find process with highest priority
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= current_time) {
                if (pr[i] < highest_priority) {
                    highest_priority = pr[i];
                    idx = i;
                }
            }
        }

        // If no process available, CPU goes idle
        if (idx == -1) {
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!completed[i] && at[i] < next_arrival) {
                    next_arrival = at[i];
                }
            }
            if (last_pid != -1) {
                gantt_pid[gantt_size] = last_pid;
                gantt_time[gantt_size] = current_time;
                gantt_size++;
                last_pid = -1;
            }
            current_time = next_arrival;
            continue;
        }

        // Record context switch
        if (last_pid != pid[idx]) {
            if (last_pid != -1) {
                gantt_pid[gantt_size] = last_pid;
                gantt_time[gantt_size] = current_time;
                gantt_size++;
            }
            last_pid = pid[idx];
        }

        // Execute for 1 unit
        remaining_bt[idx]--;
        current_time++;

        // If process completed
        if (remaining_bt[idx] == 0) {
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed[idx] = true;
            completed_count++;
            gantt_pid[gantt_size] = pid[idx];
            gantt_time[gantt_size] = current_time;
            gantt_size++;
            last_pid = -1;
        }
    }

    printResult(pid, at, bt, pr, ct, tat, wt, n, "Priority Preemptive");
}

// ============ MAIN FUNCTION ============
int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[100], at[100], bt[100], pr[100];

    // Input process details
    cout << "\nEnter process details:\n";
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "\nProcess P" << pid[i] << ":\n";
        cout << "  Arrival Time: "; cin >> at[i];
        cout << "  Burst Time: "; cin >> bt[i];
        cout << "  Priority (lower = higher): "; cin >> pr[i];
    }


    // Call all four algorithms
    sjfNonPreemptive(pid, at, bt, pr, n);
    sjfPreemptive(pid, at, bt, pr, n);
    priorityNonPreemptive(pid, at, bt, pr, n);
    priorityPreemptive(pid, at, bt, pr, n);



    return 0;
}

