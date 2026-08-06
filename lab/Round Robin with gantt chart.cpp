// Round Robin (RR) - Preemptive Scheduling
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Time Quantum: ";
    cin >> tq;

    int pid[100], at[100], bt[100], rt[100];
    int ct[100], wt[100], tat[100];

    int response_t[100] = {0};
    bool first_response[100] = {false};

    cout << "\nEnter Arrival Time:\n";
    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "P" << i + 1 << ": ";
        cin >> at[i];
    }

    cout << "\nEnter Burst Time:\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << ": ";
        cin >> bt[i];
        rt[i] = bt[i];
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

    // Queue for Round Robin
    int queue[1000];
    int front = 0, rear = 0;
    bool inQueue[100] = {false};

    double sumRT = 0;

    while(completed < n)
    {
        // If queue is empty, CPU goes IDLE
        if(front == rear)
        {
            int nextArrival = INT_MAX;
            for(int i = 0; i < n; i++)
            {
                if(rt[i] > 0 && at[i] < nextArrival)
                    nextArrival = at[i];
            }

            if(g == 0 || ganttP[g - 1] != "Idle")
            {
                ganttP[g] = "Idle";
                ganttT[g] = currentTime;
                g++;
            }

            currentTime = nextArrival;

            // Add processes that have arrived
            for(int i = 0; i < n; i++)
            {
                if(rt[i] > 0 && at[i] <= currentTime && !inQueue[i])
                {
                    queue[rear++] = i;
                    inQueue[i] = true;
                }
            }
            continue;
        }

        // Get process from front of queue
        int idx = queue[front++];
        inQueue[idx] = false;

        // Response Time
        if(first_response[idx] == false)
        {
            response_t[idx] = currentTime - at[idx];
            first_response[idx] = true;
            sumRT += response_t[idx];
        }

        string pname = "P" + to_string(pid[idx]);

        // Gantt Chart
        if(g == 0 || ganttP[g - 1] != pname)
        {
            ganttP[g] = pname;
            ganttT[g] = currentTime;
            g++;
        }

        // Execute for time quantum
        int execTime = min(tq, rt[idx]);
        rt[idx] -= execTime;
        currentTime += execTime;

        // Add new arrivals
        for(int i = 0; i < n; i++)
        {
            if(rt[i] > 0 && at[i] <= currentTime && !inQueue[i])
            {
                bool alreadyInQueue = false;
                for(int j = front; j < rear; j++)
                {
                    if(queue[j] == i)
                    {
                        alreadyInQueue = true;
                        break;
                    }
                }
                if(!alreadyInQueue)
                {
                    queue[rear++] = i;
                    inQueue[i] = true;
                }
            }
        }

        // If not completed, add back to queue
        if(rt[idx] > 0)
        {
            bool alreadyInQueue = false;
            for(int j = front; j < rear; j++)
            {
                if(queue[j] == idx)
                {
                    alreadyInQueue = true;
                    break;
                }
            }
            if(!alreadyInQueue)
            {
                queue[rear++] = idx;
                inQueue[idx] = true;
            }
        }
        else
        {
            ct[idx] = currentTime;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        }
    }

    ganttT[g] = currentTime;

    // Display Results
    double avgWT = 0, avgTAT = 0;

    cout << "\nPID\tAT\tBT\tCT\tWT\tTAT\n";
    cout << "----------------------------------------\n";

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
    cout << "----------------------------------------\n";
    cout << "Average WT:  " << avgWT / n << "\n";
    cout << "Average TAT: " << avgTAT / n << "\n";
    cout << "Average RT:  " << sumRT / n << "\n";

    // Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "|";
    for(int i = 0; i < g; i++)
    {
        cout << " " << ganttP[i] << " |";
    }
    cout << "\n";

    cout << ganttT[0];
    for(int i = 1; i <= g; i++)
    {
        cout << "\t" << ganttT[i];
    }
    cout << "\n\n";

    return 0;
}
