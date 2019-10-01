#include<bits/stdc++.h>
using namespace std;
#define ll long long int
struct bulb{
	ll on,off;
};
//building seg tree
void build(struct bulb *seg,ll *lazy,ll node,ll start,ll end){
	//cout<<node<<endl;
	if(start==end){
		seg[node].on=0;
		seg[node].off=1;
		lazy[node]=0;
		return ;
	}
	ll mid=(start+end)/2;
	build(seg,lazy,2*node,start,mid);
	build(seg,lazy,2*node+1,mid+1,end);
	seg[node].on=0;
	seg[node].off=seg[2*node].off+seg[2*node+1].off;
	lazy[node]=0;
}
// range update
void update(struct bulb *seg,ll *lazy,ll node,ll start,ll end,ll l,ll r){
	if(lazy[node]!=0){
		if(lazy[node]&1){
			ll temp=seg[node].on;
			seg[node].on=seg[node].off;
			seg[node].off=temp;
		}
		if(start!=end){
			lazy[2*node+1]+=lazy[node];
			lazy[2*node]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(r<start||l>end){
		return ;
	}
	if(start>=l&&end<=r){
		ll temp=seg[node].on;
		seg[node].on=seg[node].off;
		seg[node].off=temp;
		if(start!=end){
			lazy[2*node]++;
			lazy[2*node+1]++;
		}
		return ;
	}
	ll mid=(start+end)/2;
	update(seg,lazy,2*node,start,mid,l,r);
	update(seg,lazy,2*node+1,mid+1,end,l,r);
	seg[node].on=seg[2*node].on+seg[2*node+1].on;
	seg[node].off=seg[2*node].off+seg[2*node+1].off;
}

//bulb function
struct bulb find(struct bulb *seg,ll *lazy,ll node,ll start,ll end,ll l,ll r){
	struct bulb ans;
	if(r<start||l>end){
		ans.on=0;
		ans.off=0;
		return ans;
	}
	if(lazy[node]!=0){
		if(lazy[node]&1){
			ll temp=seg[node].on;
			seg[node].on=seg[node].off;
			seg[node].off=temp;
		}
		if(start!=end){
			lazy[2*node+1]+=lazy[node];
			lazy[2*node]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(start>=l&&end<=r){
		return seg[node];
	}
	ll mid=(start+end)/2;
	struct bulb ans1=find(seg,lazy,2*node,start,mid,l,r);
	struct bulb ans2=find(seg,lazy,2*node+1,mid+1,end,l,r);
	ans.on=ans1.on+ans2.on;
	ans.off=ans1.off+ans2.off;
	return ans;
}
//main
int main(){
	ll n,q;
	scanf("%lld%lld",&n,&q);
	struct bulb seg[4*n];
	ll lazy[4*n];
	build(seg,lazy,1,1,n);
	//cout<<0<<endl;
	// for(ll i=1;i<=2*n-1;i++){
	// 		cout<<seg[i].on<<" "<<seg[i].off<<" "<<lazy[i]<<endl;
	// 	}
	// 	cout<<endl;
	while(q--){
		ll type;
		scanf("%lld",&type);
		if(type==0){
			ll l,r;
			scanf("%lld%lld",&l,&r);
			update(seg,lazy,1,1,n,l,r);
			// for(ll i=1;i<=2*n-1;i++){
			// 	cout<<seg[i].on<<" "<<seg[i].off<<" "<<lazy[i]<<endl;
			// }
			// cout<<endl;
		}
		else{
			ll l,r;
			scanf("%lld%lld",&l,&r);
			printf("%lld\n",find(seg,lazy,1,1,n,l,r).on);
		}
	}
}