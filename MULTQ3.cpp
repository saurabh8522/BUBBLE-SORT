#include<bits/stdc++.h>
using namespace std;
#define mod 1000000009
#define ll long long int
struct mul{
	ll one,two,three;
};
//building seg tree
void build(struct mul *seg,ll *lazy,ll node,ll start,ll end){
	if(start==end){
		seg[node].one=0;
		seg[node].two=0;
		seg[node].three=1;
		lazy[node]=0;
		return;
	}
	ll mid=(start+end)/2;
	build(seg,lazy,2*node,start,mid);
	build(seg,lazy,2*node+1,mid+1,end);
	seg[node].one=seg[2*node].one+seg[2*node+1].one;
	seg[node].two=seg[2*node].two+seg[2*node+1].two;
	seg[node].three=seg[2*node].three+seg[2*node+1].three;
	lazy[node]=0;
	return;
}
// range update
void update(struct mul *seg,ll *lazy,ll node,ll start,ll end,ll l,ll r){
	if(lazy[node]!=0){
		if(lazy[node]%3==1){
			ll temp=seg[node].one;
			seg[node].one=seg[node].three;
			seg[node].three=seg[node].two;
			seg[node].two=temp;
		}
		else if(lazy[node]%3==2){
			ll temp=seg[node].two;
			seg[node].two=seg[node].three;
			seg[node].three=seg[node].one;
			seg[node].one=temp;
		}
		if(start!=end){
			lazy[2*node]+=lazy[node];
			lazy[2*node+1]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(r<start||l>end){
		return;
	}
	if(start>=l&&end<=r){
		ll temp=seg[node].one;
		seg[node].one=seg[node].three;
		seg[node].three=seg[node].two;
		seg[node].two=temp;
		if(start!=end){
			lazy[2*node]++;
			lazy[2*node+1]++;
		}
		lazy[node]=0;
		return ;
	}
	ll mid=(start+end)/2;
	update(seg,lazy,2*node,start,mid,l,r);
	update(seg,lazy,2*node+1,mid+1,end,l,r);
	seg[node].one=seg[2*node].one+seg[2*node+1].one;
	seg[node].two=seg[2*node].two+seg[2*node+1].two;
	seg[node].three=seg[2*node].three+seg[2*node+1].three;
	return;
}
// mul function
struct mul find(struct mul *seg,ll *lazy,ll node,ll start,ll end,ll l,ll r){
	struct mul ans;
	if(l>end||r<start){
		ans.one=0;
		ans.two=0;
		ans.three=0;
		return ans;
	}
	if(lazy[node]!=0){
		if(lazy[node]%3==1){
			ll temp=seg[node].one;
			seg[node].one=seg[node].three;
			seg[node].three=seg[node].two;
			seg[node].two=temp;
		}
		else if(lazy[node]%3==2){
			ll temp=seg[node].two;
			seg[node].two=seg[node].three;
			seg[node].three=seg[node].one;
			seg[node].one=temp;
		}
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
	struct mul ans1=find(seg,lazy,2*node,start,mid,l,r);
	struct mul ans2=find(seg,lazy,2*node+1,mid+1,end,l,r);
	ans.one=ans1.one+ans2.one;
	ans.two=ans1.two+ans2.two;
	ans.three=ans1.three+ans2.three;
	return ans;
}
//main
int main(){
	ll n,q;
	scanf("%lld%lld",&n,&q);
	struct mul seg[4*n];
	ll lazy[4*n];
	build(seg,lazy,1,1,n);
	//cout<<0<<endl;
	// for(ll i=1;i<=2*n-1;i++){
	// 		cout<<seg[i].one<<" "<<seg[i].two<<" "<<" "<<seg[i].three<<" "<<lazy[i]<<endl;
	// 	}
	// 	cout<<endl;
	while(q--){
		ll type;
		scanf("%lld",&type);
		ll l,r;
		scanf("%lld%lld",&l,&r);
		l++;
		r++;
		if(type==0){
			update(seg,lazy,1,1,n,l,r);
			// for(ll i=1;i<=2*n-1;i++){
			// 	cout<<seg[i].one<<" "<<seg[i].two<<" "<<" "<<seg[i].three<<" "<<lazy[i]<<endl;
			// }
		}
		else{
			printf("%lld\n",find(seg,lazy,1,1,n,l,r).three);
		}
	}
}
