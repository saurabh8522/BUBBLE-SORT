#include<bits/stdc++.h>
using namespace std;
#define ll long long int

//building seg tree
void build(ll *arr,ll *seg,ll *lazy,ll node,ll l,ll r){
	if(l==r){
//This code is to be edited for hacktoberfest
		seg[node]=arr[l];
		lazy[node]=0;
		return;
	}
	ll mid=(l+r)/2;
	build(arr,seg,lazy,2*node,l,mid);
	build(arr,seg,lazy,2*node+1,mid+1,r);
	seg[node]=seg[2*node]+seg[2*node+1];
	lazy[node]=0;
}
// summming in range 
ll sum(ll *seg,ll *lazy,ll node,ll start,ll end,ll l,ll r){
	//cout<<node<<endl;
	if(end<l||start>r){
		return 0;
	}
	if(lazy[node]!=0){
		seg[node]+=(end-start+1)*lazy[node];
		if(start!=end){
			lazy[2*node]+=lazy[node];
			lazy[2*node+1]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(start>=l&&end<=r){
		return seg[node];
	}
	ll mid=(start+end)/2;
	return sum(seg,lazy,2*node,start,mid,l,r)+sum(seg,lazy,2*node+1,mid+1,end,l,r);
}

//range update
void update(ll *seg,ll *lazy,ll node,ll start,ll end,ll l,ll r,ll val){
	if(lazy[node]!=0){
		seg[node]+=(end-start+1)*lazy[node];
		if(start!=end){
			lazy[2*node]+=lazy[node];
			lazy[2*node+1]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(r<start||l>end){
		return ;
	}
	if(start>=l&&end<=r){
		seg[node]+=(end-start+1)*val;
		if(start!=end){
			lazy[2*node]+=val;
			lazy[2*node+1]+=val;
		}
		return;
	}
	ll mid=(start+end)/2;
	update(seg,lazy,2*node,start,mid,l,r,val);
	update(seg,lazy,2*node+1,mid+1,end,l,r,val);
	seg[node]=seg[2*node]+seg[2*node+1];
}
//main
int main(){
	ll t;
	cin>>t;
	while(t--){
		ll n,q;
		cin>>n>>q;
		ll arr[n+1];
		for(ll i=1;i<=n;i++){
			arr[i]=0;
		}
		ll seg[4*n],lazy[4*n];
		build(arr,seg,lazy,1,1,n);
		// for(ll i=1;i<=2*n-1;i++){
		// 	cout<<seg[i]<<" ";
		// }
		// cout<<endl;
		for(ll i=0;i<q;i++){
			ll type;
			cin>>type;
			if(type==1){
				ll l,r;
				cin>>l>>r;
				//l++;
				//r++;
				cout<<sum(seg,lazy,1,1,n,l,r)<<endl;
			}
			else{
				ll l,r,val;
				cin>>l>>r>>val;
				//l++;
				//r++;
				update(seg,lazy,1,1,n,l,r,val);
				// for(ll i=1;i<=2*n-1;i++){
				// 	cout<<seg[i]<<" ";
				// }
				// cout<<endl;
			}
		}
	}
	
}
