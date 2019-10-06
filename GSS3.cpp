#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ll long long int
ll INF=1e15;
struct node{
	ll sum,psum,ssum,msum;
};
ll arr[50009];
struct node seg[131074];
void build(ll node,ll l,ll r){
	if(l==r){
		seg[node].psum=arr[l];
		seg[node].ssum=arr[l];
		seg[node].msum=arr[l];
		seg[node].sum=arr[l];
		return ;
	}
	ll mid=(l+r)>>1;
	build(2*node,l,mid);
	build(2*node+1,mid+1,r);
	seg[node].sum=seg[2*node].sum+seg[2*node+1].sum;
	seg[node].psum=max(seg[2*node].psum,seg[2*node].sum+seg[2*node+1].psum);
	seg[node].ssum=max(seg[2*node+1].ssum,seg[2*node].ssum+seg[2*node+1].sum);
	seg[node].msum=max(seg[2*node].msum,max(seg[2*node+1].msum,seg[2*node].ssum+seg[2*node+1].psum));
}
struct node query(ll node,ll start,ll end,ll l, ll r){
	struct node ans;
	if(r<start||l>end){
		ans.psum=-INF;
		ans.ssum=-INF;
		ans.msum=-INF;
		ans.sum=-INF;
		return ans;
	}
	if(l<=start&&r>=end){
		return seg[node];
	}
	ll mid=(start+end)>>1;
	struct node le=query(2*node,start,mid,l,r);
	struct node rr=query(2*node+1,mid+1,end,l,r);
	ans.psum=max(le.psum,le.sum+rr.psum);
	ans.ssum=max(le.ssum+rr.sum,rr.ssum);
	ans.sum=le.sum+rr.sum;
	ans.msum=max(le.msum,max(rr.msum,le.ssum+rr.psum));
	return ans;
}
void update(ll node,ll start,ll end,ll index,ll val){
	if(start==end){
		seg[node].psum+=val;
		seg[node].ssum+=val;
		seg[node].sum+=val;
		seg[node].msum+=val;
		return ;
	}
	ll mid=(start+end)>>1;
	if(index>=start&&index<=mid){
		update(2*node,start,mid,index,val);
	}
	else{
		update(2*node+1,mid+1,end,index,val);
	}
	seg[node].sum=seg[2*node].sum+seg[2*node+1].sum;
	seg[node].psum=max(seg[2*node].psum,seg[2*node].sum+seg[2*node+1].psum);
	seg[node].ssum=max(seg[2*node+1].ssum,seg[2*node].ssum+seg[2*node+1].sum);
	seg[node].msum=max(seg[2*node].msum,max(seg[2*node+1].msum,seg[2*node].ssum+seg[2*node+1].psum));
}
int main(){
	// ios_base::sync_with_stdio(false);
 //    cin.tie(NULL);
	ll n;
	scanf("%lld",&n);
	for(int j=1;j<=n;j++){
		scanf("%lld",&arr[j]);
	}
	// for(int i=1;i<=n;i++){
	// 	cout<<arr[i]<<" ";
	// }
	// cout<<endl;
	build(1,1,n);
	ll m;
	scanf("%lld",&m);
	while(m--){
		//for m times
		int type;
		cin>>type;
		if(type==1){
			ll l,r;
			scanf("%lld%lld",&l,&r);
			// l--;
			// r--;
			struct node ans=query(1,1,n,l,r);
			printf("%lld\n",ans.msum);
		}
		else{
			ll index,val;
			cin>>index>>val;
			update(1,1,n,index,val-arr[index]);
			arr[index]=val;
		}
	}
}
