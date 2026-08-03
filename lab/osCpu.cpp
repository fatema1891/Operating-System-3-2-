#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[100], at[100], bt[100], pr[100];

    cout << "\nEnter process details:\n";
    //Priority (lower value = higher priority)
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "\nProcess P" << pid[i] << ":\n";
        cout << "  Arrival Time: "; cin >> at[i];
        cout << "  Burst Time: "; cin >> bt[i];
        cout << "  Priority: "; cin >> pr[i];
    }
    // SJF NON-PREEMPTIVE
    {
        cout << "\n  SJF Non-Preemptive :\n";
        cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n\n";

        int ct[100], tat[100], wt[100];
        bool completed[100] = {false};
        int gantt_pid[1000], gantt_time[1000], gantt_size = 0;

        int completed_count = 0, current_time = 0;

        while (completed_count < n) {
            int idx = -1;
            int min_bt = 1005;

            for (int i = 0; i < n; i++) {
                if (!completed[i] && at[i] <= current_time) {
                    if (bt[i] < min_bt) {
                        min_bt = bt[i];
                        idx = i;
                    }
                }
            }

            if (idx == -1) {
                int next_arrival = 1005;
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

        double total_wt = 0, total_tat = 0;
        for (int i = 0; i < n; i++) {
            cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
                 << pr[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
            total_wt += wt[i];
            total_tat += tat[i];
        }

        //cout << "\nAverage WT: " << fixed << setprecision(2) << total_wt / n << endl;
        cout << "\nAverage WT: " << double(total_wt /n) << endl;

        cout << "Average TAT: " << double(total_tat / n) << endl;

        cout << "\nGantt Chart:\n";

        cout << "\n|";
        for (int i = 0; i < gantt_size; i++) {
            if (gantt_pid[i] == -1) cout << "  Idle  |";
            else cout << "  P" << gantt_pid[i] << "   |";
        }

        cout << "\n\n" << gantt_time[0];
        for (int i = 0; i < gantt_size; i++) cout << "\t" << gantt_time[i];
        cout << "\n\n";
    }

    // SJF PREEMPTIVE (SRTF)
    {
        cout << "\n    SJF Preemptive (SRTF) :\n\n";
        cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n\n";

        int ct[100], tat[100], wt[100];
        int remaining_bt[100];
        bool completed[100] = {false};
        int gantt_pid[1000], gantt_time[1000], gantt_size = 0;

        for (int i = 0; i < n; i++) remaining_bt[i] = bt[i];

        int completed_count = 0, current_time = 0;
        int last_pid = -1;

        while (completed_count < n) {
            int idx = -1;
            int min_remaining = 1005;

            for (int i = 0; i < n; i++) {
                if (!completed[i] && at[i] <= current_time) {
                    if (remaining_bt[i] < min_remaining) {
                        min_remaining = remaining_bt[i];
                        idx = i;
                    }
                }
            }

            if (idx == -1) {
                int next_arrival = 1005;
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

            if (last_pid != pid[idx]) {
                if (last_pid != -1) {
                    gantt_pid[gantt_size] = last_pid;
                    gantt_time[gantt_size] = current_time;
                    gantt_size++;
                }
                last_pid = pid[idx];
            }

            remaining_bt[idx]--;
            current_time++;

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

        double total_wt = 0, total_tat = 0;
        for (int i = 0; i < n; i++) {
            cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
                 << pr[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
            total_wt += wt[i];
            total_tat += tat[i];
        }

        cout << "\nAverage WT: " << double(total_wt / n )<< endl;
        cout << "Average TAT: " << double(total_tat / n) << endl;

        cout << "\nGantt Chart:\n";

        cout << "\n|";
        for (int i = 0; i < gantt_size; i++) {
            if (gantt_pid[i] == -1) cout << "  Idle  |";
            else cout << "  P" << gantt_pid[i] << "   |";
        }

        cout << "\n\n" << gantt_time[0];
        for (int i = 0; i < gantt_size; i++) cout << "\t" << gantt_time[i];
        cout << "\n\n";
    }

    // PRIORITY NON-PREEMPTIVE
    {
        cout << "\n   Priority Non-Preemptive :\n\n";
        cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n\n";

        int ct[100], tat[100], wt[100];
        bool completed[100] = {false};
        int gantt_pid[1000], gantt_time[1000], gantt_size = 0;

        int completed_count = 0, current_time = 0;

        while (completed_count < n) {
            int idx = -1;
            int highest_priority = 1005;

            for (int i = 0; i < n; i++) {
                if (!completed[i] && at[i] <= current_time) {
                    if (pr[i] < highest_priority) {
                        highest_priority = pr[i];
                        idx = i;
                    }
                }
            }

            if (idx == -1) {
                int next_arrival = 1005;
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

        double total_wt = 0, total_tat = 0;
        for (int i = 0; i < n; i++) {
            cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
                 << pr[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
            total_wt += wt[i];
            total_tat += tat[i];
        }

        cout << "\nAverage WT: " << double(total_wt / n) << endl;
        cout << "Average TAT: " << double(total_tat / n) << endl;

        cout << "\nGantt Chart:\n";

        //for (int i = 0; i < gantt_size; i++) cout << "--------";
        cout << "\n|";
        for (int i = 0; i < gantt_size; i++) {
            if (gantt_pid[i] == -1) cout << "  Idle  |";
            else cout << "  P" << gantt_pid[i] << "   |";
        }

        cout << "\n\n" << gantt_time[0];
        for (int i = 0; i < gantt_size; i++) cout << "\t" << gantt_time[i];
        cout << "\n\n";
    }

    // PRIORITY PREEMPTIVE
    {
        cout << "\n    Priority Preemptive :\n\n";
        cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n\n";

        int ct[100], tat[100], wt[100];
        int remaining_bt[100];
        bool completed[100] = {false};
        int gantt_pid[1000], gantt_time[1000], gantt_size = 0;

        for (int i = 0; i < n; i++) remaining_bt[i] = bt[i];

        int completed_count = 0, current_time = 0;
        int last_pid = -1;

        while (completed_count < n) {
            int idx = -1;
            int highest_priority = 1005;

            for (int i = 0; i < n; i++) {
                if (!completed[i] && at[i] <= current_time) {
                    if (pr[i] < highest_priority) {
                        highest_priority = pr[i];
                        idx = i;
                    }
                }
            }

            if (idx == -1) {
                int next_arrival = 1005;
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

            if (last_pid != pid[idx]) {
                if (last_pid != -1) {
                    gantt_pid[gantt_size] = last_pid;
                    gantt_time[gantt_size] = current_time;
                    gantt_size++;
                }
                last_pid = pid[idx];
            }

            remaining_bt[idx]--;
            current_time++;

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

        double total_wt = 0, total_tat = 0;
        for (int i = 0; i < n; i++) {
            cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
                 << pr[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
            total_wt += wt[i];
            total_tat += tat[i];
        }

        cout << "\nAverage WT: " << double(total_wt / n )<< endl;
        cout << "Average TAT: " << double(total_tat / n )<< endl;

        cout << "\n    Gantt Chart:\n\n";

        cout << "|";
        for (int i = 0; i < gantt_size; i++) {
            if (gantt_pid[i] == -1) cout << "  Idle  |";
            else cout << "  P" << gantt_pid[i] << "   |";
        }

        cout << "\n\n" << gantt_time[0];
        for (int i = 0; i < gantt_size; i++) cout << "\t" << gantt_time[i];
        cout << "\n\n";
    }

    return 0;
}
