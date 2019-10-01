#include<bits/stdc++.h>
using namespace std;
//building tree
void build(int *arr,int *seg,int node,int start,int end){
	if(start==end)
		seg[node]=arr[start];
	else{
		int mid=(start+end)/2;
		build(arr,seg,2*node,start,mid);
		build(arr,seg,2*node+1,mid+1,end);
		seg[node]=seg[2*node]+seg[2*node+1];
	}
	//return seg[i];
}

//  getting sum in range from l to r
int sum(int *seg,int node,int start,int end,int l,int r){
	if(r<start||l>end){
		return 0;
	}
	else if(l<=start&&r>=end){
		return seg[node];
	}
	else{
		int mid=(start+end)/2;
		return sum(seg,2*node,start,mid,l,r)+sum(seg,2*node+1,mid+1,end,l,r);
	}
}
//update range start to end with value val
void update(int *seg,int node,int start,int end,int index,int val){
	if(start==end){
		seg[node]+=val;
	}
	else{
		int mid=(start+end)/2;
		if(index>=start&&index<=mid){
			update(seg,2*node,start,mid,index,val);
		}
		else{
			update(seg,2*node+1,mid+1,end,index,val);
		}
		seg[node]=seg[2*node]+seg[2*node+1];
	}
}
int main(){
	int n;
	cin>>n;
	int arr[n+1],seg[3*n];
	for(int i=1;i<=n;i++){
		cin>>arr[i];
	}
	build(arr,seg,1,1,n);
	// for(int i=1;i<=2*n-1;i++){
	// 	cout<<seg[i]<<" ";
	// }
	// cout<<endl;
	int q;
	cin>>q;
	for(int i=0;i<q;i++){
		int type;
		cin>>type;
		if(type==1){
			int l,r;
			cin>>l>>r;
			l++;
			r++;
			cout<<sum(seg,1,1,n,l,r)<<endl;
		}
		else{
			int index,val;
			cin>>index>>val;
			index++;
			update(seg,1,1,n,index,val-arr[index]);
			arr[index]=val;
		}
	}
}
