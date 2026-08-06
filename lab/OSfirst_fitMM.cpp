#include<bits/stdc++.h>
using namespace std;

void firstFit(int blockSize[],int m,int procesSize[],int n)
{
    int allocation[100];
    for(int i=0;i<n;i++)allocation[i]=-1;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(procesSize[i]<=blockSize[j])
            {
                allocation[i]=j;
                blockSize[j]-=procesSize[i];
                break;
            }
        }
    }

    cout<<"\nFirst fit:\n";
    cout<<"\nProcess\tprocess_Size\tBlock_no\n";
    for(int i=0;i<n;i++)
    {
        cout<<"p"<<i+1<<"\t"<<procesSize[i]<<'\t';
        if(allocation[i]!=-1)cout<<allocation[i]+1<<'\n';
        else cout<<"No allocate"<<'\n';
    }
}

int main()
{
    int m,n;
    int blockSize[]={100, 500, 200, 300, 600};
    int procesSize[]={100,200,300,412};
    m=sizeof(blockSize)/sizeof(blockSize[0]);
    n=sizeof(procesSize)/sizeof(procesSize[0]);

    firstFit(blockSize,m,procesSize,n);
}
