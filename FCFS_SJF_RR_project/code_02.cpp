#include <bits/stdc++.h>
using namespace std;

/*
        CPU SCHEDULING PROJECT (RELATION BASED)
---------------------------------------------------------
Algorithms Included:
1. FCFS
2. SJF (Non-Preemptive)
3. Round Robin (Preemptive)

Concept:
Same Input Data use kore 3 ta algorithm compare kora hobe.
Then relation dekhano hobe:

 FCFS vs SJF
 SJF vs RR
 FCFS vs RR

Output:
- Gantt Chart
- CT
- TAT
- WT
- Average WT
- Average TAT
- Best Algorithm

*/

struct Process {
    int pid, at, bt;
    int ct = 0, tat = 0, wt = 0, rt = 0;
};

struct Result {
    vector<Process> p;
    double avgWT = 0;
    double avgTAT = 0;
};

// Print Table
void printResult(Result r, string name) {
    cout << "\n==============================\n";
    cout << name << "\n";
    cout << "==============================\n";

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";

    for (auto x : r.p) {
        cout << "P" << x.pid << "\t"
             << x.at << "\t"
             << x.bt << "\t"
             << x.ct << "\t"
             << x.tat << "\t"
             << x.wt << "\n";
    }

    cout << "\nAverage WT  = " << r.avgWT;
    cout << "\nAverage TAT = " << r.avgTAT << "\n";
}

// FCFS
Result FCFS(vector<Process> p) {

    sort(p.begin(), p.end(), [](Process a, Process b) {
        if (a.at == b.at) return a.pid < b.pid;
        return a.at < b.at;
    });

    int time = 0;
    double twt = 0, ttat = 0;

    cout << "\nFCFS Gantt Chart:\n";

    for (auto &x : p) {

        if (time < x.at) {
            cout << time << " -> " << x.at << " : IDLE\n";
            time = x.at;
        }

        int start = time;
        time += x.bt;

        x.ct = time;
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;

        twt += x.wt;
        ttat += x.tat;

        cout << start << " -> " << time << " : P" << x.pid << "\n";
    }

    return {p, twt / p.size(), ttat / p.size()};
}

// =====================================================
// SJF Non Preemptive
// =====================================================
Result SJF(vector<Process> p) {

    int n = p.size();
    vector<bool> done(n, false);

    int completed = 0, time = 0;
    double twt = 0, ttat = 0;

    cout << "\nSJF Gantt Chart:\n";

    while (completed < n) {

        int idx = -1;
        int mn = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < mn) {
                mn = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            cout << time << " -> " << time + 1 << " : IDLE\n";
            time++;
            continue;
        }

        int start = time;
        time += p[idx].bt;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        twt += p[idx].wt;
        ttat += p[idx].tat;

        cout << start << " -> " << time << " : P" << p[idx].pid << "\n";

        done[idx] = true;
        completed++;
    }

    return {p, twt / n, ttat / n};
}

// Round Robin
Result RR(vector<Process> p, int qtm) {

    sort(p.begin(), p.end(), [](Process a, Process b) {
        if (a.at == b.at) return a.pid < b.pid;
        return a.at < b.at;
    });

    int n = p.size();

    for (auto &x : p) x.rt = x.bt;

    queue<int> q;
    int time = 0, i = 0, completed = 0;
    double twt = 0, ttat = 0;

    cout << "\nRound Robin Gantt Chart:\n";

    while (completed < n) {

        while (i < n && p[i].at <= time) {
            q.push(i);
            i++;
        }

        if (q.empty()) {
            cout << time << " -> " << time + 1 << " : IDLE\n";
            time++;
            continue;
        }

        int idx = q.front();
        q.pop();

        int run = min(qtm, p[idx].rt);
        int start = time;

        time += run;
        p[idx].rt -= run;

        cout << start << " -> " << time << " : P" << p[idx].pid << "\n";

        while (i < n && p[i].at <= time) {
            q.push(i);
            i++;
        }

        if (p[idx].rt > 0) q.push(idx);
        else {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            twt += p[idx].wt;
            ttat += p[idx].tat;
        }
    }

    return {p, twt / n, ttat / n};
}

// Compare Relations
void relation(Result a, Result b, string x, string y) {

    cout << "\n----------------------------------\n";
    cout << x << " vs " << y << "\n";
    cout << "----------------------------------\n";

    if (a.avgWT < b.avgWT)
        cout << x << " gives lower Waiting Time\n";
    else if(a.avgWT > b.avgWT)
        cout << y << " gives lower Waiting Time\n";
    else cout<<x<<" and "<<y<<" gives equal Waiting Time\n";


    if (a.avgTAT < b.avgTAT)
        cout << x << " gives lower Turnaround Time\n";
    else if (a.avgTAT > b.avgTAT)
        cout << y << " gives lower Turnaround Time\n";
    else cout<<x<<" and "<<y<<" gives equal Turnaround Time\n";
}

int main() {

    int n;
    //cout << "Enter Number of Processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        //cout << "Enter AT and BT of P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt;
    }

    int quantum;
    //cout << "Enter Time Quantum for RR: ";
    cin >> quantum;

    Result fcfs = FCFS(p);
    Result sjf = SJF(p);
    Result rr = RR(p, quantum);

    printResult(fcfs, "FCFS RESULT");
    printResult(sjf, "SJF RESULT");
    printResult(rr, "ROUND ROBIN RESULT");

    relation(fcfs, sjf, "FCFS", "SJF");
    relation(fcfs, rr, "FCFS", "RR");
    relation(sjf, rr, "SJF", "RR");

    return 0;
}
