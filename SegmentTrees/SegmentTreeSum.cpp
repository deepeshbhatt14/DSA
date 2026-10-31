#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int size;
    vector<long long int> arr;

    void buildSegmentTree(vector<long long int>&a, int n){
        size=1;
        while(size<n){
            size*=2;
        }
        arr=vector<long long int>(2*size-1,0);
        buildSum(0,0,size,a,n);
    }
    void buildSum(int pos,int l,int r, vector<long long int>&a, int n){
        if(r-l==1){
            if(l<n){
                arr[pos]=a[l];
            }
        }
        else{
            int mid=(r+l)/2;
            buildSum(2*pos+1,l,mid,a,n);
            buildSum(2*pos+2,mid,r,a,n);
            arr[pos]=arr[2*pos+1]+arr[2*pos+2];
        }
    }
    long long int calcSum(int pos,int lc, int rc, int l, int r){
        if(l>=rc||r<=lc){
            return 0;
        }
        if(lc>=l&&rc<=r){
            return arr[pos];
        }
        else{
            int mid=(rc+lc)/2;
            return calcSum(2*pos+1,lc,mid,l,r)+calcSum(2*pos+2,mid,rc,l,r);
        }
    }
    long long int calcSum(int l, int r){ // calculate sum from l to r-1
        return calcSum(0,0,size,l,r);
    }
    void set(int pos,int lc,int rc,int index,long long int value){
        if(rc-lc==1){
            arr[pos]=value;
            return;
        }
        int mid=(lc+rc)/2;
        if(index<mid){
            set(2*pos+1,lc,mid,index,value);
        }
        else{
            set(2*pos+2,mid,rc,index,value);
        }
        arr[pos]=arr[2*pos+1]+arr[2*pos+2];
    }
    void set(int index, long long int value){
        set(0,0,size,index,value);
    }
};

int main() {
    int n,m;
    cin>>n>>m;
    vector<long long int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    SegmentTree S;
    S.buildSegmentTree(a,n);
    while(m--){
        long long int o,l,r;
        cin>>o>>l>>r;
        if(o==1){
            S.set(l,r);
        }
        else{
            long long int ans=S.calcSum(l,r);
            cout<<ans<<endl;
        }
    }
    return 0;
}