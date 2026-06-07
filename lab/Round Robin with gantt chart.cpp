//Round Robin Algorithm
#include <iostream>
#include <algorithm>
using namespace std;

void queueUpdation(int queue[], int n, int maxProcessIndex)
{
    int zeroIndex = -1;

    for(int i = 0; i < n; i++)
    {
        if(queue[i] == 0)
        {
            zeroIndex = i;
            break;
        }
    }

    if(zeroIndex != -1)
        queue[zeroIndex] = maxProcessIndex + 1;
}

void queueMaintainence(int queue[], int n)
{
    for(int i = 0; (i < n - 1) && (queue[i + 1] != 0); i++)
    {
        swap(queue[i], queue[i + 1]);
    }
}

void checkNewArrival(int timer, int arrival[], int n,
                     int &maxProcessIndex, int queue[])
{
    if(timer <= arrival[n - 1])
    {
        bool newArrival = false;

        for(int j = maxProcessIndex + 1; j < n; j++)
        {
            if(arrival[j] <= timer)
            {
                maxProcessIndex = j;
                newArrival = true;
            }
        }

        if(newArrival)
            queueUpdation(queue, n, maxProcessIndex);
    }
}

int main()
{
    int n, tq;
    int timer = 0;
    int maxProcessIndex = 0;

    float avgWait = 0, avgTT = 0;

    cout << "Enter Time Quantum: ";
    cin >> tq;

    cout << "Enter Number of Processes: ";
    cin >> n;

    int pid[n];
    int arrival[n];
    int burst[n];
    int temp_burst[n];
    int wait[n];
    int turn[n];
    int queue[n];
    bool complete[n];

    // Gantt Chart Arrays
    int ganttPid[1000];
    int ganttStart[1000];
    int ganttEnd[1000];
    int ganttCount = 0;

    cout << "\nEnter Arrival Times:\n";
    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "P" << i + 1 << ": ";
        cin >> arrival[i];
    }

    cout << "\nEnter Burst Times:\n";
    for(int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << ": ";
        cin >> burst[i];
    }

    // Sort by Arrival Time
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(arrival[i] > arrival[j])
            {
                swap(arrival[i], arrival[j]);
                swap(burst[i], burst[j]);
                swap(pid[i], pid[j]);
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        temp_burst[i] = burst[i];
        complete[i] = false;
        queue[i] = 0;
    }

    while(timer < arrival[0])
        timer++;

    queue[0] = 1;

    while(true)
    {
        bool finished = true;

        for(int i = 0; i < n; i++)
        {
            if(temp_burst[i] > 0)
            {
                finished = false;
                break;
            }
        }

        if(finished)
            break;

        for(int i = 0; i < n && queue[i] != 0; i++)
        {
            int current = queue[0] - 1;

            int startTime = timer;
            int ctr = 0;

            while(ctr < tq && temp_burst[current] > 0)
            {
                temp_burst[current]--;
                timer++;
                ctr++;

                checkNewArrival(timer, arrival, n,
                                maxProcessIndex, queue);
            }

            // Store Gantt Chart Entry
            if(startTime != timer)
            {
                ganttPid[ganttCount] = pid[current];
                ganttStart[ganttCount] = startTime;
                ganttEnd[ganttCount] = timer;
                ganttCount++;
            }

            if(temp_burst[current] == 0 &&
               complete[current] == false)
            {
                turn[current] = timer;
                complete[current] = true;
            }

            bool idle = true;

            if(queue[n - 1] == 0)
            {
                for(int j = 0; j < n && queue[j] != 0; j++)
                {
                    if(!complete[queue[j] - 1])
                    {
                        idle = false;
                        break;
                    }
                }
            }
            else
            {
                idle = false;
            }

            if(idle)
            {
                timer++;
                checkNewArrival(timer, arrival, n,
                                maxProcessIndex, queue);
            }

            queueMaintainence(queue, n);
        }
    }

    // Calculate WT and TAT
    for(int i = 0; i < n; i++)
    {
        turn[i] = turn[i] - arrival[i];
        wait[i] = turn[i] - burst[i];

        avgWait += wait[i];
        avgTT += turn[i];
    }

    // Process Table
    cout << "\n\nPID\tAT\tBT\tWT\tTAT\n";

    for(int i = 0; i < n; i++)
    {
        cout << "P" << pid[i]
             << "\t" << arrival[i]
             << "\t" << burst[i]
             << "\t" << wait[i]
             << "\t" << turn[i]
             << endl;
    }


    // Gantt Chart
    cout << "\nGantt Chart:\n\n";

    for(int i = 0; i < ganttCount; i++)
    {
        cout << "| P" << ganttPid[i] << " ";
    }

    cout << "|\n";

    cout << ganttStart[0];

    for(int i = 0; i < ganttCount; i++)
    {
        cout << "\t" << ganttEnd[i];
    }

    cout << "\n";

    // Averages
    cout << "\nAverage Waiting Time = "
         << avgWait / n;

    cout << "\nAverage Turnaround Time = "
         << avgTT / n << endl;

    return 0;
}
/*
#include<bits/stdc++.h>
using namespace std;

void queueUpdation(int queue[],int n,int maxProcessIndex)
{
    int zeroIndex=-1;
    for(int i=0;i<n;i++)
    {
        if(queue[i]==0)
        {
            zeroIndex=i;
            break;
        }
    }
    if(zeroIndex!=-1)queue[zeroIndex]=maxProcessIndex+1;
}
void queueMaintenance(int queue[],int n)
{
    for(int i=0;i<n-1 &&queue[i+1]!=0;i++)

    {
        swap(queue[i],queue[i+1]);
    }
}

void checkNewArrial(int timer,int arrival[],int n,
    int &maxProcessIndex,int queue[])
{
    if(timer<=arrival[n-1])
    {
        bool newArrival=false;
        for(int j=maxProcessIndex+1;j<n;j++)
        {
            if(arrival[j]<=timer)
            {
                maxProcessIndex=j;
                newArrival=true;
            }
        }
        if(newArrival)
            queueUpdation(queue,n,maxProcessIndex);
    }
}


int main()
{
    int n,i,j,quantum,timer=0,maxProcessIndex=0;
    double avgWT=0,avgTT=0;
    cout<<"Enter The Quantum: ";
    cin>>quantum;
    cout<<"Enter Number of Precess: ";
    cin>>n;

    int pid[n],arrival[n],burst[n],
    temp_burst[n],wait[n],turn[n];
    int queue[n]={0};
    bool complete[n]={false};

    //gantt chart arrays
    int ganttPid[1000],ganttStart[1000],ganttEnd[1000];
    int ganttCount=0;

    cout<<"\nEnter Arrival Time: \n";
    for(i=0;i<n;i++)
    {
        pid[i]=i+1;
        cout<<"P"<<i+1<<": ";
        cin>>arrival[i];
    }

    cout<<"\nEnter Burst Time:\n";
    for(i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<": ";
        cin>>burst[i];
        temp_burst[i]=burst[i];
    }

    //sort by arrival time
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(arrival[i]>arrival[j])
            {
                swap(arrival[i],arrival[j]);
                swap(burst[i],burst[j]);
                swap(temp_burst[i], temp_burst[j]);
                swap(pid[i],pid[j]);
            }
        }
    }

    while(timer<arrival[0])timer++;

    queue[0]=1;
    while(true)
    {
        bool finished = true;
        for(i=0;i<n;i++)
        {
            if(temp_burst[i]>0)
            {
                finished=false;
                break;
            }
        }

        //complete process
        if(finished){break;}

        for(i=0;i<n&&queue[i]!=0;i++)
        {
            int current=queue[0]-1;
            int startTimer=timer;
            int counter=0;

            while(counter<quantum&&temp_burst[current]>0)
            {
                temp_burst[current]--;
                timer++;
                counter++;

                checkNewArrial(timer,arrival,n,maxProcessIndex,queue);
            }

            //store gantt chart 
            if(startTimer!=timer)
            {
                ganttPid[ganttCount]=pid[current];
                ganttStart[ganttCount]=startTimer;
                ganttEnd[ganttCount]=timer;
                ganttCount++;
            }

            if(temp_burst[current]==0&&complete[current]==false)
            {
                turn[current]=timer;
                complete[current]=true;
            }
            bool idle=true;
            if(queue[n-1]==0)
            {
                for(int j=0;j<n&&queue[j]!=0;j++)
                {
                    if(!complete[queue[j]-1])
                    {
                        idle=false;
                        break;
                    }
                }
            }
            else
            {
                idle=false;
            }
            if(idle)
            {
                timer++;
                checkNewArrial(timer,arrival,n,maxProcessIndex,queue);
            }
            queueMaintenance(queue,n);
        }

    }
    //calculate wt,tat
    for(i=0;i<n;i++)
    {
        turn[i]=turn[i]-arrival[i];
        wait[i]=turn[i]-burst[i];

        avgWT+=wait[i];
        avgTT+=turn[i];
    }
    //process table
    cout<<"\n\nPID\tAT\tBT\tWT\tTAT\n";
    for(i=0;i<n;i++)
    {
        cout<<"P"<<pid[i]
        <<"\t"<<arrival[i]
        <<"\t"<<burst[i]
        <<"\t"<<wait[i]
        <<"\t"<<turn[i]<<'\n';
    }
    //gantt chart
    cout<<"\nGantt Chart:\n";
    for(i=0;i<ganttCount;i++)
    {
        cout<<"| P"<<ganttPid[i]<<" ";
    }
    cout<<"|\n";
    cout<<ganttStart[0];
    for(i=0;i<ganttCount;i++)
    {
        cout<<"\t"<<ganttEnd[i];
    }
    cout<<"\n\nAverage Waiting Time = "<<avgWT/n;
    cout<<"\nAverage Tarnaround Time = "<<avgTT/n;
}
*/
