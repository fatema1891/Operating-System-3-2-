#include<bits/stdc++.h>
using namespace std;
using ll =long long int ;
using v1=std::vector<ll>;
using v2=vector<v1>;
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
v2 v;

struct process
{
    ll process_id,at,bt;
    ll wt=0,ct=0,tat=0,rt=0;
};

struct result
{
    vector<process>p;
    double avgWt=0,avgTAT=0;
};

//FCFS
result FCFS(vector<process>p)
{
    sort(p.begin(),p.end(),[](process a,process b){
        if(a.at==b.at)return a.process_id< b.process_id;
        return a.at<b.at;
    });

    ll time=0;
    double sum_wt=0,sum_tat=0;
    cout<<"\nFCFS Gantt Chart:\n";
    for(auto &it:p)
    {
        if(time<it.at)
        {
            cout<<time<<" -> "<<it.at<<"  : IDLE\n";
            time=it.at;
        }

        ll start=time;
        time+=it.bt;

        it.ct=time;
        it.tat=it.ct-it.at;
        it.wt=it.tat-it.bt;

        sum_wt+=it.wt,sum_tat+=it.tat;
        cout<<start<<" -> "<<time<<" :p"<<it.process_id<<'\n';
    }
    return {p,sum_wt/p.size(),sum_tat/p.size()};
}

//SJF not preemptive 
result SJF(vector<process>p)
{
    ll n=p.size();
    vector<bool>done(n,false);

    ll complet=0,time=0;
    double sum_wt=0,sum_tat=0;
    cout<<"\nSJF Gantt Chart :\n";

    while(complet<n)
    {
        ll ind=-1;
        ll mn=1e9;
        for(ll i=0;i<n;i++)
        {
            if(!done[i]&&p[i].at<=time&&p[i].bt<mn)
            {
                mn=p[i].bt;
                ind=i;
            }

        }
        if(ind==-1){
            cout<<time<<" -> "<<time+1<<" :IDLE\n";
            time++;
            continue;
        }

        ll start=time;
        time+=p[ind].bt;

        p[ind].ct=time;
        p[ind].tat=p[ind].ct-p[ind].at;
        p[ind].wt=p[ind].tat-p[ind].bt;
        sum_wt+=p[ind].wt,sum_tat+=p[ind].tat;
        cout<<start<<" -> "<<time<<" :p"<<p[ind].process_id <<"\n";

        complet++;
        done[ind]=true;

    }
    return {p,sum_wt/n,sum_tat/n};
}

//Round Robin

result RR(vector<process>p,ll quantum)
{
    sort(p.begin(),p.end(),[](process a,process b){
        if(a.at==b.at)return a.process_id<b.process_id;
        return a.at<b.at;

    });
    ll n=p.size();
    for(auto &it:p)it.rt=it.bt;

    queue<ll>q;
    cout<<"\nRound Robin Gantt Chart:\n";
    ll time=0,i=0,complet=0;
    double sum_wt=0,sum_tat=0;

    while(complet<n)
    {
        while(i<n&&p[i].at<=time)
        {
            q.push(i);
            i++;
        }
        if(q.empty())
        {
            cout<<time<<" -> "<<time+1<<" : IDLE\n";
            time++;
            continue;
        }
        ll ind=q.front();
        q.pop();

        ll run=min(quantum,p[ind].rt);
        ll start=time;
        time+=run;
        p[ind].rt-=run;

        cout<<start<<" -> "<<time<<" : p"<<p[ind].process_id<<'\n';

        while(i<n&&p[i].at<=time)
        {
            q.push(i);
            i++;
        }
        if(p[ind].rt>0)q.push(ind);
        else
        {
            complet++;
            p[ind].ct=time;
            p[ind].tat=p[ind].ct-p[ind].at;
            p[ind].wt=p[ind].tat-p[ind].bt;

            sum_wt+=p[ind].wt;
            sum_tat+=p[ind].tat;
        }
    }
    return {p,sum_wt/n,sum_tat/n};
}

//print result

void printResult(result r,string name)
{
    cout<<"\n*****"<<name<<"*****:\n============================\n";
    cout<<"process\tAT\tBT\tCT\tTAT\tWT\n";
    for(auto &it:r.p)
    {
        cout<<"  p"<<it.process_id<<"\t"
        <<it.at<<'\t'
        <<it.bt<<'\t'
        <<it.ct<<'\t'
        <<it.tat<<'\t'
        <<it.wt<<'\n';
    }
    cout<<"\nAverage waiting Time = "<<r.avgWt<<'\n';
    cout<<"\nAverage Turnaround Time = "<<r.avgTAT<<'\n';
}

void relation(result a,result b,string x, string y)
{
    cout<<"\n------"<<x<<"  vs  "<<y<<"-------:\n"
    <<"=================================\n\n";

    if(a.avgWt<b.avgWt)
        cout<<x<<" gives lower waiting Time \n";
    else if(a.avgWt > b.avgWt)
        cout << y << " gives lower Waiting Time\n";
    else cout<<x<<" and "<<y<<" gives equal Waiting Time\n";

    if(a.avgTAT<b.avgTAT)
        cout<<x<<" gives lower Turnaround Time\n";
    else if (a.avgTAT > b.avgTAT)
        cout << y << " gives lower Turnaround Time\n";
    else cout<<x<<" and "<<y<<" gives equal Turnaround Time\n";
}

int32_t main()
{
    fast;
    ll n,i;
    //cout<<"Enter number of process : ";
    cin>>n;

    vector<process>p(n);

    for(i=0;i<n;i++)
    {
        p[i].process_id=i+1;
        cin>>p[i].at>>p[i].bt;
    }

    ll quantum; //for round robin
    cin>>quantum;

    result fcfs=FCFS(p);
    result sjf=SJF(p);
    result rr=RR(p,quantum);

    printResult(fcfs,"FCFS Result");
    printResult(sjf,"SJF Result");
    printResult(rr,"Round Robin Result");

    relation(fcfs,sjf,"FCFS","SJF");
    relation(fcfs,rr,"FCFS","Round Robin");
    relation(sjf,rr,"SJF","Round Robin");

}
