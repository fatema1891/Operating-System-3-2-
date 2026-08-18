#include <bits/stdc++.h>
using namespace std;

void preemptivePriority(int n,int pid[],int at[],int bt[],int pr[],int rt[]){

    cout<<"preemptive Priority scheduling:\n\n";

    int ct[100], wt[100], tat[100];

    int completed = 0;
    int currentTime = 0;

    string ganttP[100];
    int ganttT[100];
    int g=0;

    while(completed < n) {

        int idx = -1;
        int bestPr = 1000;

        for(int i = 0; i < n; i++) {

            if(at[i] <= currentTime && rt[i] > 0) {

                if(pr[i] < bestPr) {
                    bestPr = pr[i];
                    idx = i;
                }
                else if(pr[i] == bestPr) {
                    if(at[i] < at[idx])
                        idx = i;
                }
            }
        }

        if(idx == -1) {

            if(g==0 || ganttP[g-1] != "Idle") {
                ganttP[g]="Idle";
                ganttT[g]=currentTime;
                g++;
            }

            currentTime++;
            continue;
        }

        string pname = "P" + to_string(pid[idx]);

        if(g==0 || ganttP[g-1]!= pname) {
            ganttP[g]=pname;
            ganttT[g]=currentTime;
            g++;
        }

        rt[idx]--;
        currentTime++;

        if(rt[idx] == 0) {

            ct[idx] = currentTime;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            completed++;
        }
    }

    ganttT[g]=currentTime;

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


}


void SJF(int n,int pid[],int at[],int bt[],int rt[])
{
    cout<<"\n\nSJF sheduling:\n";

    int ct[100], wt[100], tat[100];

bool completed[20] = {false};
     int completedCount = 0;
    int currentTime = 0;

    float avgWT = 0, avgTAT = 0;

    // For Gantt Chart
    string gantt[50];
    int times[50];
    int k = 0;

    times[k++] = 0;

    while(completedCount < n)
    {
        int idx = -1;
        int mn = 99999;

        // Find shortest job among arrived processes
        for(int i = 0; i < n; i++)
        {
            if(!completed[i] &&
               at[i] <= currentTime &&
               bt[i] < mn)
            {
                mn = bt[i];
                idx = i;
            }
        }

        // CPU Idle
        if(idx == -1)
        {
            int nextArrival = 99999;

            for(int i = 0; i < n; i++)
            {
                if(!completed[i] && at[i] < nextArrival)
                    nextArrival = at[i];
            }

            /*cout << "CPU Idle from "
                 << currentTime
                 << " to "
                 << nextArrival << endl;
                 */

            gantt[k-1] = "Idle";

            currentTime = nextArrival;

            times[k++] = currentTime;

            continue;
        }

        wt[idx] = currentTime - at[idx];  //Waiting Time = CPU Start Time − Arrival (আগমন) Time

        ct[idx] = currentTime + bt[idx];

        tat[idx] = ct[idx] - at[idx];

        currentTime = ct[idx];

        completed[idx] = true;
        completedCount++;

        avgWT += wt[idx];
        avgTAT += tat[idx];

        gantt[k-1] = "P" + to_string(pid[idx]);
        times[k++] = currentTime;
    }

    cout << "\nProcess\tAT\tBT\tWT\tTAT\tCT\n";

    for(int i = 0; i < n; i++)
    {
        cout << "P" << pid[i]
             << "\t" << at[i]
             << "\t" << bt[i]
             << "\t" << wt[i]
             << "\t" << tat[i]
             << "\t" << ct[i]
             << endl;
    }

    cout << "\nAverage Waiting Time = "
         << avgWT / n << endl;

    cout << "Average Turnaround Time = "
         << avgTAT / n << endl;

    // ---------------- GANTT CHART ----------------

    cout << "\n\nGantt Chart:\n";

    for(int i = 0; i < k-1; i++)
    {
        cout << "| " << gantt[i] << " ";
    }
    cout << "|" << endl;

    for(int i = 0; i < k; i++)
    {
        cout << times[i] << "\t";
    }

    cout << endl;

}

void SRTF(int n,int pid[],int at[],int bt[],int rt[])
{
    cout<<"\n\nSRTF sheduling:\n";

    int ct[100], wt[100], tat[100];


    int response_time[100] = {0};
    bool first_response[100] = {false};
    int i,j;


    int completed = 0;
    bool completeP[100] = {false};
    int currentT = 0;

    string ganttP[100];
    int ganttT[100], g = 0;
    double sumWT = 0, sumTAT = 0, sumRT = 0;


    while(completed < n)
    {
        int ind = -1;

        for(i = 0; i < n; i++)
        {
            if(!completeP[i] && at[i] <= currentT && rt[i] > 0)
            {
                if(ind == -1 || rt[i] < rt[ind])
                    ind = i;
            }
        }

        if(ind == -1)
        {
            if(g == 0 || ganttP[g-1] != "IDLE")
            {
                ganttP[g] = "IDLE";
                ganttT[g] = currentT;
                g++;
            }
            currentT++;
            continue;
        }


        if(!first_response[ind])
        {
            response_time[ind] = currentT - at[ind];
            first_response[ind] = true;
        }

        string name = "P" + to_string(pid[ind]);

        if(g == 0 || ganttP[g-1] != name)
        {
            ganttP[g] = name;
            ganttT[g] = currentT;
            g++;
        }

        rt[ind]--;
        currentT++;

        if(rt[ind] == 0)
        {
            ct[ind] = currentT;
            tat[ind] = ct[ind] - at[ind];
            wt[ind] = tat[ind] - bt[ind];
            completeP[ind] = true;
            completed++;

            sumWT += wt[ind];
            sumTAT += tat[ind];
            sumRT += response_time[ind];
        }
    }

    ganttT[g] = currentT;

    cout << "\n\nProcess\tAT\tBT\tCT\tWT\tTAT\tRT\n\n";

    for(i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << "\t"
             << response_time[i] << "\n";
    }
    cout << "\n\nAverage WT:  " << sumWT / n << "\n";
    cout << "Average TAT: " << sumTAT / n << "\n";
    cout << "Average RT:  " << sumRT / n << "\n";


    cout << "\n\nGantt Chart:\n";
    cout << "|";
    for(i = 0; i < g; i++)
    {
        cout << " " << ganttP[i] << " |";
    }
    cout << "\n";

    cout << ganttT[0];
    for(i = 1; i <= g; i++)
    {
        cout << "\t" << ganttT[i];
    }
    cout << "\n\n";

}

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[100], at[100], bt[100], pr[100];
    int rt[100];

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

    // Reset and call each algorithm
    preemptivePriority(n, pid, at, bt, pr, rt);

    for(int i = 0; i < n; i++) rt[i] = bt[i];  // Reset
    SJF(n, pid, at, bt, rt);

    for(int i = 0; i < n; i++) rt[i] = bt[i];  // Reset
    SRTF(n, pid, at, bt, rt);

    return 0;
}
