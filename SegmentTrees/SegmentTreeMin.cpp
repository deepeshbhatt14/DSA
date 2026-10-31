#include <bits/stdc++.h>
using namespace std;


struct SegmentTree{
	int size;
	vector<int> arr;

	void buildSegmentTree(vector<int>& a, int n){
		size=1;
		while(size<n){
			size*=2;
		}
		arr=vector<int>(2*size-1,0);
		buildMin(0,0,size,a,n);
	}
	void buildMin(int pos,int l, int r, vector<int>& a, int n){
		if(r-l==1){
			if(l<n){
				arr[pos]=a[l];
			}
			return;
		}
		else{
			int mid=(l+r)/2;
			buildMin(2*pos+1,l,mid,a,n);
			buildMin(2*pos+2,mid,r,a,n);
			arr[pos]=min(arr[2*pos+1],arr[2*pos+2]);
			return;
		}
	}
	void set(int pos,int l, int r, int index, int value){
		if(index>=r||index<l){
			return;
		}
		if(r-l==1){
			if(index==l){
				arr[pos]=value;
			}
			return;
		}
		int mid=(l+r)/2;
		if(index<mid){
			set(2*pos+1,l,mid,index,value);
		}
		else{
			set(2*pos+2,mid,r,index,value);
		}
		arr[pos]=min(arr[2*pos+1],arr[2*pos+2]);
		return;
	}
	void set(int index, int value){
		set(0,0,size,index,value);
	}
	int calcMin(int pos, int lc, int rc, int l, int r){
		if(lc>=r||rc<=l){
			return INT_MAX;
		}
		if(lc>=l&&rc<=r){
			return arr[pos];
		}
		if(rc-lc==1){
			return arr[pos];
		}
		int mid=(lc+rc)/2;
		return min(calcMin(2*pos+1,lc,mid,l,r),calcMin(2*pos+2,mid,rc,l,r));
	}
	int calcMin(int l,int r){
		return calcMin(0,0,size,l,r);
	}

};

int main(){
	int n,m;
    cin>>n>>m;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    SegmentTree S;
    S.buildSegmentTree(a,n);
    while(m--){
        int o,l,r;
        cin>>o>>l>>r;
        if(o==1){
            S.set(l,r);
        }
        else{
            int ans=S.calcMin(l,r);
            cout<<ans<<endl;
        }
    }
	return 0;
}