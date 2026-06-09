#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[100], at[100], bt[100], pr[100];
    int rt[100], ct[100], wt[100], tat[100];

    cout << "\nEnter Arrival Time:\n";
    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "P" << i + 1 << ": ";
        cin >> at[i];
    }

    cout << "\nEnter Burst Time:\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> bt[i];
        rt[i] = bt[i];
    }

    cout << "\nEnter Priority (smaller = higher priority):\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> pr[i];
    }

    int completed = 0;
    int currentTime = 0;

    string ganttP[100];
    int ganttT[100];
    int g=0;

    while(completed < n) {

        int idx = -1;//selected process index
        //int bestPr = INT_MAX;//smallest priority found.
        int bestPr = 1000;
        // Find highest priority process among arrived processes
        for(int i = 0; i < n; i++) {

            if(at[i] <= currentTime && rt[i] > 0) {//Process has arrived and Process is not completed.

                if(pr[i] < bestPr) {//Smaller priority number wins.
                    bestPr = pr[i];
                    idx = i;
                }
                else if(pr[i] == bestPr) {//If priorities equal and Choose earlier arrival process.
                    // Tie -> FCFS
                    if(at[i] < at[idx])
                        idx = i;
                }
            }
        }

        // CPU Idle
        if(idx == -1) {//No process available

            if(g==0 || ganttP[g-1] != "Idle") {//Avoid repeatedly writing:(Idle Idle Idle Idle)Only one entry.
                ganttP[g]="Idle";
                ganttT[g]=currentTime;
                g++;
            }

            currentTime++;//CPU waits one unit.
            continue;
        }

        string pname = "P" + to_string(pid[idx]);

        // Update Gantt Chart
        if(g==0 || ganttP[g-1]!= pname) {
            ganttP[g]=pname;//process name
            ganttT[g]=currentTime;
            g++;
        }

        // Execute for 1 unit time
        rt[idx]--;
        currentTime++;

        // Process completed
        if(rt[idx] == 0) {

            ct[idx] = currentTime;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            completed++;
        }
    }

    ganttT[g]=currentTime;//Store ending time.

    double totalWT = 0;
    double totalTAT = 0;

    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    for(int i = 0; i < n; i++) {

        cout << "P" << pid[i]
             << "\t" << at[i]
             << "\t" << bt[i]
             << "\t" << pr[i]
             << "\t" << ct[i]
             << "\t" << tat[i]
             << "\t" << wt[i]
             << endl;

        totalWT += wt[i];
        totalTAT += tat[i];
    }

    cout << "\nGantt Chart:\n\n";

    for(int i = 0; i < g; i++)
        cout << "| " << ganttP[i] << " ";

    cout << "|\n";

    for(int i = 0; i <= g; i++)
        cout << ganttT[i] << "\t";

    cout << "\n";

    cout << "\nAverage Waiting Time = "
         << totalWT / n;

    cout << "\nAverage Turnaround Time = "
         << totalTAT / n << endl;

    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n;

//     cout << "Enter number of processes: ";
//     cin >> n;

//     int pid[100], at[100], bt[100], pr[100];
//     int rt[100], ct[100], wt[100], tat[100];

//     cout << "\nEnter Arrival Time:\n";
//     for(int i = 0; i < n; i++) {
//         pid[i] = i + 1;
//         cout << "P" << i + 1 << ": ";
//         cin >> at[i];
//     }

//     cout << "\nEnter Burst Time:\n";
//     for(int i = 0; i < n; i++) {
//         cout << "P" << i + 1 << ": ";
//         cin >> bt[i];
//         rt[i] = bt[i];
//     }

//     cout << "\nEnter Priority (smaller = higher priority):\n";
//     for(int i = 0; i < n; i++) {
//         cout << "P" << i + 1 << ": ";
//         cin >> pr[i];
//     }

//     int completed = 0;
//     int currentTime = 0;

//     vector<string> ganttP;
//     vector<int> ganttT;

//     while(completed < n) {

//         int idx = -1;//selected process index
//         int bestPr = INT_MAX;//smallest priority found.

//         // Find highest priority process among arrived processes
//         for(int i = 0; i < n; i++) {

//             if(at[i] <= currentTime && rt[i] > 0) {//Process has arrived and Process is not completed.

//                 if(pr[i] < bestPr) {//Smaller priority number wins.
//                     bestPr = pr[i];
//                     idx = i;
//                 }
//                 else if(pr[i] == bestPr) {//If priorities equal and Choose earlier arrival process.
//                     // Tie -> FCFS
//                     if(at[i] < at[idx])
//                         idx = i;
//                 }
//             }
//         }

//         // CPU Idle
//         if(idx == -1) {//No process available

//             if(ganttP.empty() || ganttP.back() != "Idle") {//Avoid repeatedly writing:(Idle Idle Idle Idle)Only one entry.
//                 ganttP.push_back("Idle");
//                 ganttT.push_back(currentTime);
//             }

//             currentTime++;//CPU waits one unit.
//             continue;
//         }

//         string pname = "P" + to_string(pid[idx]);

//         // Update Gantt Chart
//         if(ganttP.empty() || ganttP.back() != pname) {
//             ganttP.push_back(pname);//process name
//             ganttT.push_back(currentTime);
//         }

//         // Execute for 1 unit time
//         rt[idx]--;
//         currentTime++;

//         // Process completed
//         if(rt[idx] == 0) {

//             ct[idx] = currentTime;
//             tat[idx] = ct[idx] - at[idx];
//             wt[idx] = tat[idx] - bt[idx];

//             completed++;
//         }
//     }

//     ganttT.push_back(currentTime);//Store ending time.

//     double totalWT = 0;
//     double totalTAT = 0;

//     cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

//     for(int i = 0; i < n; i++) {

//         cout << "P" << pid[i]
//              << "\t" << at[i]
//              << "\t" << bt[i]
//              << "\t" << pr[i]
//              << "\t" << ct[i]
//              << "\t" << tat[i]
//              << "\t" << wt[i]
//              << endl;

//         totalWT += wt[i];
//         totalTAT += tat[i];
//     }

//     cout << "\nGantt Chart:\n\n";

//     for(int i = 0; i < ganttP.size(); i++)
//         cout << "| " << ganttP[i] << " ";

//     cout << "|\n";

//     for(int i = 0; i < ganttT.size(); i++)
//         cout << ganttT[i] << "\t";

//     cout << "\n";

//     cout << "\nAverage Waiting Time = "
//          << totalWT / n;

//     cout << "\nAverage Turnaround Time = "
//          << totalTAT / n << endl;

//     return 0;
// }
