#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    int timer = 0;

    cout << "Enter Number of Processes: ";
    cin >> n;

    int pid[20], at[20], bt[20], pr[20];
    int wt[20], tat[20], ct[20], rt[20];
    bool completed[20] = {false};
    bool first_response[20] = {false};

    // Gantt Chart Arrays
    int gantt_pid[1000], gantt_start[1000], gantt_end[1000];
    int gantt_count = 0;

    // Input
    cout << "\nEnter Arrival Times:\n";
    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "P" << i + 1 << ": ";
        cin >> at[i];
    }

    cout << "\nEnter Burst Times:\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << ": ";
        cin >> bt[i];
    }

    cout << "\nEnter Priorities (Lower number = Higher Priority):\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << ": ";
        cin >> pr[i];
    }

    // Sort by Arrival Time (if same arrival, higher priority first)
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(at[i] > at[j])
            {
                swap(pid[i], pid[j]);
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
                swap(pr[i], pr[j]);
            }
        }
    }

    // Handle initial IDLE time
    if(timer < at[0])
    {
        gantt_pid[gantt_count] = -1;
        gantt_start[gantt_count] = timer;
        gantt_end[gantt_count] = at[0];
        gantt_count++;
        timer = at[0];
    }

    int completed_count = 0;

    // Non-Preemptive Priority Main Loop
    while(completed_count < n)
    {
        // Find process with highest priority among arrived processes
        int idx = -1;
        int highest_priority = INT_MAX;

        for(int i = 0; i < n; i++)
        {
            if(!completed[i] && at[i] <= timer)
            {
                if(pr[i] < highest_priority)
                {
                    highest_priority = pr[i];
                    idx = i;
                }
            }
        }

        // If no process available, CPU goes IDLE
        if(idx == -1)
        {
            int next_arrival = INT_MAX;
            for(int i = 0; i < n; i++)
            {
                if(!completed[i] && at[i] < next_arrival)
                    next_arrival = at[i];
            }

            if(next_arrival != INT_MAX && timer < next_arrival)
            {
                gantt_pid[gantt_count] = -1;
                gantt_start[gantt_count] = timer;
                gantt_end[gantt_count] = next_arrival;
                gantt_count++;
                timer = next_arrival;
            }
            continue;
        }

        // Calculate Response Time (first time process gets CPU)
        if(!first_response[idx])
        {
            rt[idx] = timer - at[idx];
            first_response[idx] = true;
        }

        // Execute process completely (Non-Preemptive)
        int startTime = timer;
        timer += bt[idx];
        ct[idx] = timer;
        completed[idx] = true;
        completed_count++;

        // Store Gantt Chart
        gantt_pid[gantt_count] = pid[idx];
        gantt_start[gantt_count] = startTime;
        gantt_end[gantt_count] = timer;
        gantt_count++;
    }

    // Calculate WT and TAT
    double sumWT = 0, sumTAT = 0, sumRT = 0;
    for(int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        sumWT += wt[i];
        sumTAT += tat[i];
        sumRT += rt[i];
    }

    // Display Results
    cout << "\nProcess\tAT\tBT\tPR\tCT\tWT\tTAT\tRT\n";
    cout << "----------------------------------------------------\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << "\t"
             << rt[i] << "\n";
    }
    cout << "----------------------------------------------------\n";
    cout << "Average WT:  " << sumWT/n << "\n";
    cout << "Average TAT: " << sumTAT/n << "\n";
    cout << "Average RT:  " << sumRT/n << "\n";

    // Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "|";
    for(int i = 0; i < gantt_count; i++)
    {
        if(gantt_pid[i] == -1)
            cout << " IDLE |";
        else
            cout << " P" << gantt_pid[i] << " |";
    }
    cout << "\n";

    cout << gantt_start[0];
    for(int i = 0; i < gantt_count; i++)
    {
        cout << "\t" << gantt_end[i];
    }
    cout << "\n\n";

    return 0;
}
