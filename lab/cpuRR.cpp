#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, tq;
    int timer = 0;
    int maxProcessIndex = 0;

    cout << "Enter Time Quantum: ";
    cin >> tq;

    cout << "Enter Number of Processes: ";
    cin >> n;

    int pid[20], at[20], bt[20], remaining[20];
    int wt[20], tat[20], ct[20], rt[20];
    int queue[20] = {0};
    bool completed[20] = {false};
    bool first_response[20] = {false};  // To track first response

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
        remaining[i] = bt[i];
    }

    // Sort by Arrival Time
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(at[i] > at[j])
            {
                swap(pid[i], pid[j]);
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
                swap(remaining[i], remaining[j]);
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

    queue[0] = 1; // First process in queue

    // Round Robin Main Loop
    while(true)
    {
        // Check if all processes completed
        bool all_done = true;
        for(int i = 0; i < n; i++)
        {
            if(remaining[i] > 0)
            {
                all_done = false;
                break;
            }
        }
        if(all_done) break;

        // Check if queue is empty (CPU IDLE)
        bool queue_empty = true;
        for(int i = 0; i < n; i++)
        {
            if(queue[i] != 0)
            {
                queue_empty = false;
                break;
            }
        }

        // Handle IDLE time
        if(queue_empty)
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

            // Add arrived processes to queue
            for(int i = 0; i < n; i++)
            {
                if(!completed[i] && at[i] <= timer)
                {
                    int empty = -1;
                    for(int j = 0; j < n; j++)
                    {
                        if(queue[j] == 0)
                        {
                            empty = j;
                            break;
                        }
                    }
                    if(empty != -1)
                    {
                        queue[empty] = i + 1;
                        if(i > maxProcessIndex)
                            maxProcessIndex = i;
                    }
                }
            }
            continue;
        }

        // Process ready queue
        for(int i = 0; i < n && queue[i] != 0; i++)
        {
            int current = queue[0] - 1;
            int startTime = timer;
            int executed = 0;

            // Check if this is the first time process is getting CPU
            if(!first_response[current])
            {
                rt[current] = timer - at[current];  // Response Time
                first_response[current] = true;
            }

            // Execute process
            while(executed < tq && remaining[current] > 0)
            {
                remaining[current]--;
                timer++;
                executed++;

                // Check for new arrivals
                if(timer <= at[n - 1])
                {
                    bool new_arrival = false;
                    for(int j = maxProcessIndex + 1; j < n; j++)
                    {
                        if(at[j] <= timer)
                        {
                            maxProcessIndex = j;
                            new_arrival = true;
                        }
                    }

                    if(new_arrival)
                    {
                        int empty = -1;
                        for(int j = 0; j < n; j++)
                        {
                            if(queue[j] == 0)
                            {
                                empty = j;
                                break;
                            }
                        }
                        if(empty != -1)
                            queue[empty] = maxProcessIndex + 1;
                    }
                }
            }

            // Store Gantt Chart
            if(startTime != timer)
            {
                gantt_pid[gantt_count] = pid[current];
                gantt_start[gantt_count] = startTime;
                gantt_end[gantt_count] = timer;
                gantt_count++;
            }

            // Process completed
            if(remaining[current] == 0 && completed[current] == false)
            {
                ct[current] = timer;
                completed[current] = true;
            }

            // Rotate queue
            for(int j = 0; j < n - 1 && queue[j + 1] != 0; j++)
            {
                swap(queue[j], queue[j + 1]);
            }
        }
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
    cout << "\nProcess\tAT\tBT\tCT\tWT\tTAT\tRT\n\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << "\t"
             << rt[i] << "\n";
    }
    cout << "\n\nAverage WT:  " << sumWT/n << "\n";
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
