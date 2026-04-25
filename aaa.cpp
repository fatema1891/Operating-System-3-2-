#include<bits/stdc++.h>
using namespace std;
using ll =long long int ;
using v1=std::vector<ll>;
using v2=vector<v1>;
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);

struct Process {
    ll pid, at, bt, pr;
    ll ct = 0, tat = 0, wt = 0, rt = 0;
};

// Utility print
void print(vector<Process> p, string name) {
    cout << "\n=== " << name << " ===\n";
    cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    double total_wt = 0, total_tat = 0;

    for (auto &x : p) {
        cout << "P" << x.pid << "\t" << x.at << "\t\t" << x.bt << "\t\t"
             << x.pr << "\t\t" << x.ct << "\t\t" << x.tat << "\t\t" << x.wt << "\n";

        total_wt += x.wt;
        total_tat += x.tat;
    }

    cout << "Average WT: " << total_wt / p.size() << endl;
    cout << "Average TAT: " << total_tat / p.size() << endl;
}

// SJF Non-Preemptive
vector<Process> SJF_NP(vector<Process> p) {
    ll n = p.size();
    vector<bool> done(n, false);

    ll completed = 0, time = 0;

    cout << "\nSJF Non-Preemptive Gantt:\n";

    while (completed < n) {
        ll idx = -1, mn = 1e9;

        for (ll i = 0; i < n; i++) {
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

        ll start = time;
        time += p[idx].bt;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        cout << start << " -> " << time << " : P" << p[idx].pid << "\n";

        done[idx] = true;
        completed++;
    }

    return p;
}

// SJF Preemptive (SRTF)
vector<Process> SJF_P(vector<Process> p) {
    int n = p.size();

    for (auto &x : p) x.rt = x.bt;

    ll completed = 0, time = 0;

    cout << "\nSJF Preemptive (SRTF) Gantt:\n";

    while (completed < n) {
        ll idx = -1, mn = 1e9;

        for (ll i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt < mn) {
                mn = p[i].rt;
                idx = i;
            }
        }

        if (idx == -1) {
            cout << time << " -> " << time + 1 << " : IDLE\n";
            time++;
            continue;
        }

        cout << time << " -> " << time + 1 << " : P" << p[idx].pid << "\n";

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    return p;
}

//Priority Non-Preemptive
// (Assume smaller number = higher priority)
vector<Process> Priority_NP(vector<Process> p) {
    int n = p.size();
    vector<bool> done(n, false);

    int completed = 0, time = 0;

    cout << "\nPriority Non-Preemptive Gantt:\n";

    while (completed < n) {
        int idx = -1, best = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].pr < best) {
                best = p[i].pr;
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

        cout << start << " -> " << time << " : P" << p[idx].pid << "\n";

        done[idx] = true;
        completed++;
    }

    return p;
}

//Priority Preemptive
vector<Process> Priority_P(vector<Process> p) {
    int n = p.size();

    for (auto &x : p) x.rt = x.bt;

    int completed = 0, time = 0;

    cout << "\nPriority Preemptive Gantt:\n";

    while (completed < n) {
        int idx = -1, best = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].pr < best) {
                best = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) {
            cout << time << " -> " << time + 1 << " : IDLE\n";
            time++;
            continue;
        }

        cout << time << " -> " << time + 1 << " : P" << p[idx].pid << "\n";

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    return p;
}

// MAIN
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter AT BT Priority:\n";
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cin >> p[i].at >> p[i].bt >> p[i].pr;
    }

    auto sjf_np = SJF_NP(p);
    auto sjf_p  = SJF_P(p);
    auto pr_np  = Priority_NP(p);
    auto pr_p   = Priority_P(p);

    print(sjf_np, "SJF Non-Preemptive");
    print(sjf_p,  "SJF Preemptive (SRTF)");
    print(pr_np,  "Priority Non-Preemptive");
    print(pr_p,   "Priority Preemptive");

    return 0;
}