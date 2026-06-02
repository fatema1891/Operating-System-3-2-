#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter Number of Processes: ";
    cin >> n;

    int at[20], bt[20], wt[20], tat[20], ct[20], pid[20];

    for(int i = 0; i < n; i++)
        pid[i] = i + 1;

    cout << "\nEnter Arrival Times:\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i+1 << ": ";
        cin >> at[i];
    }

    cout << "\nEnter Burst Times:\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i+1 << ": ";
        cin >> bt[i];
    }

    // Sort by Arrival Time
    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(at[i] > at[j])
            {
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
                swap(pid[i], pid[j]);
            }
        }
    }

    int time = 0;
    float avgWT = 0, avgTAT = 0;

    for(int i = 0; i < n; i++)
    {
        if(time < at[i])
            time = at[i];

        wt[i] = time - at[i];

        ct[i] = time + bt[i];

        tat[i] = ct[i] - at[i];

        time = ct[i];

        avgWT += wt[i];
        avgTAT += tat[i];
    }

    cout << "\nProcess\tAT\tBT\tWT\tTAT\tCT\n";

    for(int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << "\t"
             << ct[i] << endl;
    }

    cout << "\nAverage Waiting Time = "
         << avgWT/n << endl;

    cout << "Average Turnaround Time = "
         << avgTAT/n << endl;

    //  GANTT CHART

    cout << "\n\nGantt Chart:\n\n";

    time = 0;

    // Upper line
    cout << "|";

    for(int i = 0; i < n; i++)
    {
        if(time < at[i])
        {
            cout << "Idle|";
            time = at[i];
        }

        cout << "P" << pid[i] << " |";
        time += bt[i];
    }

    cout << "\n";

    // Time line
    time = 0;
    cout << 0;

    for(int i = 0; i < n; i++)
    {
        if(time < at[i])
        {
            cout << "    " << at[i];
            time = at[i];
        }

        time += bt[i];
        cout << "   " << time;
    }

    cout << endl;

    return 0;
}
