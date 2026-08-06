#include<bits/stdc++.h>
using namespace std;


void bestFit(int processSize[],int n,int blockSize[],int m)
{
    int i,j;

    int allocation[100];
    for(int i=0;i<n;i++)allocation[i]=-1;


    for(i=0;i<n;i++)
    {
        int best=-1;
        for(j=0;j<m;j++)
        {
            if(processSize[i]<=blockSize[j])
            {
                if(best==-1 || blockSize[j]<blockSize[best])
                    best=j;
            }
        }

        if(best!=-1)
        {
            allocation[i]=best;
            blockSize[best]-=processSize[i];
        }

    }

    cout<<"\nBest fit:\n";
    cout<<"\nprocess\tProcess_Size\tBlock_no\n";
    for(i=0;i<n;i++)
    {
        cout<<"p"<<i+1<<'\t'<<processSize[i]<<'\t';
        if(allocation[i]!=-1)cout<<allocation[i]+1<<'\n';
        else cout<<"no allocate\n";
    }
}

int main()
{
    int n,m;
    int processSize[]={100,200,300,400};
    int blockSize[]={200,100,500,300,412};
    n=sizeof(processSize)/sizeof(processSize[0]);
    m=sizeof(blockSize)/sizeof(blockSize[0]);

    bestFit(processSize,n,blockSize,m);
}
