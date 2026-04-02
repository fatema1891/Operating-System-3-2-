#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)


struct  proces
{
    ll Pid,AT,BT,CT,TAT,WT;
};


void printArivalTime(proces pro[],ll n)
{
    cout<<"\nproces\tArival_time\n";
    for(ll i=0;i<n;i++)
    {
        cout<<"  P"<<pro[i].Pid<<"  \t\t"<<pro[i].AT<<'\n';
    }
}

void printBurstTime(proces pro[],ll n)
{
    cout<<"\nproces\tBurst_time\n";
    for(ll i=0;i<n;i++)
    {
        cout<<"  P"<<pro[i].Pid<<"  \t\t"<<pro[i].BT<<'\n';
    }
}

void printCompletionTime(proces pro[],ll n)
{
    cout<<"\nproces\tCompletion_time\n";
    for(ll i=0;i<n;i++)
    {
        cout<<"  P"<<pro[i].Pid<<"  \t\t"<<pro[i].CT<<'\n';
    }
}

void printTarnarountTime(proces pro[],ll n)
{
    cout<<"\nproces\tTurnaround_time\n";
    for(ll i=0;i<n;i++)
    {
        cout<<"  P"<<pro[i].Pid<<"  \t\t"<<pro[i].TAT<<'\n';
    }
}

void printWaitingTime(proces pro[],ll n)
{
    cout<<"\nproces\tWaiting_time\n";
    for(ll i=0;i<n;i++)
    {
        cout<<"  P"<<pro[i].Pid<<"  \t\t"<<pro[i].WT<<'\n';
    }
}


int32_t main()
{
    ll n,m,i;
    cin>>n;

    proces pro[n];
    for(i=0;i<n;i++)
    {
        cin>>pro[i].Pid>>pro[i].AT>>pro[i].BT;
    }

    //sort by arrival time
    sort(pro,pro+n,[](proces a, proces b)
    {
        if(a.AT==b.AT)
            return a.Pid<b.Pid;
        return a.AT<b.AT;
    });

    ll current_time=0;
    cout<<"Gantt Chart:\n";
    for(i=0;i<n;i++)
    {
        if(current_time<pro[i].AT){
            cout<<current_time<<" -> "<<pro[i].AT<<" : "<<"IDL\n";

            current_time+=pro[i].AT;
        }
    ll start=current_time;
    current_time+=pro[i].BT;
// find CT,TAT,WT
    pro[i].CT=current_time;
    pro[i].TAT=pro[i].CT-pro[i].AT;
    pro[i].WT=pro[i].TAT-pro[i].BT;

      
    cout<<start<<" -> "<<current_time<<" : p"<<pro[i].Pid<<'\n';  
    }

    printArivalTime(pro,n);
    printBurstTime(pro,n);
    printCompletionTime(pro,n);
    printTarnarountTime(pro,n);
    printWaitingTime(pro,n);

        
}

/* output
Gantt Chart:
0 -> 3 : p2
3 -> 11 : p1
11 -> 13 : p3
13 -> 19 : p4

proces	Arival_time
  P2  		0
  P1  		3
  P3  		4
  P4  		5

proces	Burst_time
  P2  		3
  P1  		8
  P3  		2
  P4  		6

proces	Completion_time
  P2  		3
  P1  		11
  P3  		13
  P4  		19

proces	Turnaround_time
  P2  		3
  P1  		8
  P3  		9
  P4  		14

proces	Waiting_time
  P2  		0
  P1  		0
  P3  		7
  P4  		8
*/
