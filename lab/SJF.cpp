#include <iostream>
using namespace std;

int main()
{
    int n,i;

    cout << "Enter number of processes: ";
    cin >> n;

    int pid[20], at[20], bt[20];
    // int wt[20] = {0}, tat[20] = {0}, ct[20] = {0};
    int wt[20] , tat[20] , ct[20] ;
    bool completed[20] = {false};

    /*for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        cout << "Arrival Time P" << i + 1 << ": ";
        cin >> at[i];

        cout << "Burst Time P" << i + 1 << ": ";
        cin >> bt[i];
    }
    */
    cout<<"\nEnter the Arrival Time:\n";
    for(i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<" : ";
        cin>>at[i];
        pid[i]=i+1;
    }
    cout<<"\nEnter the Burst Time:\n";
    for(i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<" : ";
        cin>>bt[i];
    }

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

    return 0;
}
