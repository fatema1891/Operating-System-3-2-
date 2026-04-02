#include <bits/stdc++.h>
using namespace std;

struct Process {
    int Process_name, at, bt, ct, tat, wt;
};

int main() {
    int n = 4;

    Process p[] = {
        {1, 3, 8},
        {2, 0, 3},
        {3, 4, 2},
        {4, 5, 6}
    };

    // Sort by arrival time
    sort(p, p + n, [](Process a, Process b) {
        if (a.at == b.at)
            return a.Process_name< b.Process_name;
        return a.at < b.at;
    });

    int current_time = 0;

    cout << "\nGantt Chart:\n";

    for (int i = 0; i < n; i++) {

        // Handle idle time
        if (current_time < p[i].at) {
            cout << current_time << " -> " << p[i].at << " : IDLE\n";
            current_time = p[i].at;
        }

        int start = current_time;
        current_time += p[i].bt;

        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        cout << start << " -> " << current_time 
             << " : P" << p[i].Process_name << "\n";
    }

    double total_wt = 0, total_tat = 0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].Process_name << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    cout << "\nAverage WT = " << total_wt / n << endl;
    cout << "Average TAT = " << total_tat / n << endl;

    return 0;
}
/*
output:

Gantt Chart:
0 -> 3 : P2
3 -> 11 : P1
11 -> 13 : P3
13 -> 19 : P4

PID	AT	BT	CT	TAT	WT
2	0	3	3	3	0
1	3	8	11	8	0
3	4	2	13	9	7
4	5	6	19	14	8

Average WT = 3.75
Average TAT = 8.5
*/
