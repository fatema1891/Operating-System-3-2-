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

        wt[i] = time - at[i];    //Waiting Time = CPU Start Time − Arrival (আগমন) Time

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
    time = 0;  //CPU Start Time
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



                                          better approch


#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,i,j;
    cout<<"Enter number of process :";
    cin>>n;
    int pid[n],at[n],bt[n],pr[n],wt[n],tat[n],ct[n];
    for(i=0;i<n;i++)
    {
        pid[i]=i+1;
        cout<<"\nprocess p"<<pid[i]<<":\n";
        cout<<"Arrival time: ";cin>>at[i];
        cout<<"Burst time: ";cin>>bt[i];
    }
    //sort arrival time
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(at[j]<at[i])
            {
                swap(at[i],at[j]);
                swap(bt[i],bt[j]);
                swap(pid[i],pid[j]);
            }
        }
    }

    int CPU_start_time=0;
   double sumWT=0,sumTAT=0;

    for(i=0;i<n;i++)
    {
        if(CPU_start_time<at[i])CPU_start_time=at[i];

        wt[i]=CPU_start_time -at[i];
        ct[i]=CPU_start_time+bt[i];
        tat[i]=ct[i]-at[i];

        CPU_start_time=ct[i];

        sumWT+=wt[i],sumTAT+=tat[i];
    }

    cout<<"\nprocess\tAT\tBT\tCT\tWT\tTAT\n\n";

    for(i=0;i<n;i++)
    {
        cout<<"p"<<pid[i]<<'\t'<<at[i]<<'\t'<<bt[i]<<'\t'<<ct[i]<<'\t'<<wt[i]<<'\t'<<tat[i]<<"\n";
    }
    cout<<"\n\nAverage wt: "<<sumWT/n<<"\n";
    cout<<"Average tat: "<<sumTAT/n<<"\n";

    cout<<"\nGantt chartt:\n"<<"|";
    CPU_start_time=0;
    for(i=0;i<n;i++)
    {
        if(CPU_start_time<at[i])
        {
            cout<<"IDLE | ";
            CPU_start_time=at[i];
        }
        cout<<" p"<<pid[i]<<" |";
        CPU_start_time+=bt[i];
    }

    CPU_start_time=0;
    cout<<'\n'<<0;
    for(i=0;i<n;i++)
    {
        if(CPU_start_time<at[i])cout<<"     "<<at[i];
        CPU_start_time+=bt[i];
        cout<<"    "<<CPU_start_time;
    }
    cout<<"\n\n";

}

