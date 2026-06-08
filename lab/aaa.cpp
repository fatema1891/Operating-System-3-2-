//SRTF (Shortest Remaining Time First)
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[100], at[100], bt[100], rt[100];
    int ct[100], wt[100], tat[100];

    cout << "\nEnter Arrival Time:\n";

    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        cout << "P" << i + 1 << ": ";
        cin >> at[i];
    }
    cout<<"\nEnter Burst Time:\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<": ";
        cin>>bt[i];
        rt[i]=bt[i];
    }

    // Sort by Arrival Time
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(at[i] > at[j])
            {
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
                swap(rt[i], rt[j]);
                swap(pid[i], pid[j]);
            }
        }
    }

    int currentTime = 0;
    int completed = 0;

    // Gantt Chart
    string ganttP[1000];
    int ganttT[1000];
    int g = 0;

    while(completed < n)
    {
        int idx = -1;

        // Find shortest remaining time process
        for(int i = 0; i < n; i++)
        {
            if(at[i] <= currentTime && rt[i] > 0)
            {
                if(idx == -1 || rt[i] < rt[idx])
                {
                    idx = i;
                }
            }
        }

        // CPU Idle
        if(idx == -1)
        {
            if(g == 0 || ganttP[g - 1] != "Idle")
            {
                ganttP[g] = "Idle";
                ganttT[g] = currentTime;
                g++;
            }

            currentTime++;
            continue;
        }

        string pname = "P" + to_string(pid[idx]);

        // Record process change in Gantt chart
        if(g == 0 || ganttP[g - 1] != pname)
        {
            ganttP[g] = pname;
            ganttT[g] = currentTime;
            g++;
        }

        // Execute for 1 unit
        rt[idx]--;
        currentTime++;

        // Process completed
        if(rt[idx] == 0)
        {
            ct[idx] = currentTime;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        }
    }

    // Final ending time
    ganttT[g] = currentTime;

    // Process Table
    double avgWT = 0, avgTAT = 0;

    cout << "\nPID\tAT\tBT\tCT\tWT\tTAT\n";

    for(int i = 0; i < n; i++)
    {
        cout << "P" << pid[i]
             << "\t" << at[i]
             << "\t" << bt[i]
             << "\t" << ct[i]
             << "\t" << wt[i]
             << "\t" << tat[i]
             << endl;

        avgWT += wt[i];
        avgTAT += tat[i];
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n\n";

    for(int i = 0; i < g; i++)
    {
        cout << "| " << ganttP[i] << " ";
    }
    cout << "|\n";

    for(int i = 0; i <= g; i++)
    {
        cout << ganttT[i] << "\t";
    }

    cout << "\n";

    cout << "\nAverage Waiting Time = "
         << avgWT / n;

    cout << "\nAverage Turnaround Time = "
         << avgTAT / n << endl;

    return 0;
}