//SRTF (Shortest Remaining Time First)

// SRTF (Shortest Remaining Time First) - Preemptive SJF
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, i, j;
    cout << "Enter number of processes: ";
    cin >> n;

    int pid[100], at[100], bt[100], ct[100], wt[100], tat[100], rt[100];
    int response_time[100] = {0};
    bool first_response[100] = {false};

    // Input
    for(i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "\nProcess P" << pid[i] << ":\n";
        cout << "  Arrival time: "; cin >> at[i];
        cout << "  Burst time: "; cin >> bt[i];
        rt[i] = bt[i];
    }

    // ============================================================
    // SORT BY ARRIVAL TIME (FIXED)
    // ============================================================
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(at[i] > at[j])  // ← FIXED: Compare i with j
            {
                swap(pid[i], pid[j]);
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
                swap(rt[i], rt[j]);
            }
        }
    }

    int completed = 0;
    bool completeP[100] = {false};
    int currentT = 0;

    string ganttP[100];
    int ganttT[100], g = 0;
    double sumWT = 0, sumTAT = 0, sumRT = 0;

    // ============================================================
    // SRTF ALGORITHM
    // ============================================================
    while(completed < n)
    {
        int ind = -1;

        // Find process with shortest remaining time
        for(i = 0; i < n; i++)
        {
            if(!completeP[i] && at[i] <= currentT && rt[i] > 0)
            {
                if(ind == -1 || rt[i] < rt[ind])
                    ind = i;
            }
        }

        // CPU IDLE
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

        // ============================================================
        // CALCULATE RESPONSE TIME (First time process gets CPU)
        // ============================================================
        if(!first_response[ind])
        {
            response_time[ind] = currentT - at[ind];
            first_response[ind] = true;
        }

        string name = "P" + to_string(pid[ind]);

        // Gantt Chart
        if(g == 0 || ganttP[g-1] != name)
        {
            ganttP[g] = name;
            ganttT[g] = currentT;
            g++;
        }

        // Execute for 1 unit
        rt[ind]--;
        currentT++;

        // Process completed
        if(rt[ind] == 0)
        {
            ct[ind] = currentT;
            tat[ind] = ct[ind] - at[ind];
            wt[ind] = tat[ind] - bt[ind];  // ← FIXED: Removed extra space
            completeP[ind] = true;
            completed++;

            sumWT += wt[ind];
            sumTAT += tat[ind];
            sumRT += response_time[ind];  // ← FIXED: Add response time
        }
    }

    ganttT[g] = currentT;

    // ============================================================
    // DISPLAY RESULTS
    // ============================================================
    cout << "\n\nProcess\tAT\tBT\tCT\tWT\tTAT\tRT\n";
    cout << "--------------------------------------------------------\n";

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
    cout << "--------------------------------------------------------\n";
    cout << "Average WT:  " << sumWT / n << "\n";
    cout << "Average TAT: " << sumTAT / n << "\n";
    cout << "Average RT:  " << sumRT / n << "\n";

    // ============================================================
    // GANTT CHART (FIXED FORMATTING)
    // ============================================================
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

    return 0;
}

*********************************************************************   OR   *************

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
        rt[i]=bt[i];//remaining time
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
    string ganttP[1000];//process name
    int ganttT[1000];//time
    int g = 0;//index

    while(completed < n)
    {
        int idx = -1;//search for best process

        // Find shortest remaining time process
        for(int i = 0; i < n; i++)
        {
            if(at[i] <= currentTime && rt[i] > 0)//process has arrived and not completed
            {
                if(idx == -1 || rt[i] < rt[idx])//smallest remaining time → SRTF rule
                {
                    idx = i;
                }
            }
        }

        // CPU Idle
        if(idx == -1)  //no process available at current time
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

        string pname = "P" + to_string(pid[idx]);//Convert process ID into string format

        // Record process change in Gantt chart
        if(g == 0 || ganttP[g - 1] != pname)//avoids duplicate entries
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
