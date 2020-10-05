#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define vi vector<int>
#define vll vector<ll>
#define pll pair<ll,ll>
#define pii pair<int,int>
#define pb  push_back
#define ppb pop_back
#define mp  make_pair
#define SIZE 10000
vector<int> graph[SIZE];
bool vis[SIZE];
int dp[SIZE][2];
void dfs(int u){
	vis[u]=true;
	int sum0=1,sum1=0;
	for(auto v:graph[u]){
		if(!vis[v]){
			dfs(v);
			sum0+=dp[v][1];
			sum1+=dp[v][0];
		}
	}
	dp[u][0]=sum0;
	dp[u][1]=sum1;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	int n;
	cin>>n;
	for(int i=1;i<=n;++i){
		int u,v;
		cin>>u>>v;
		graph[u].pb(v);
		graph[v].pb(u);	
	}
	dfs(1);
	// for(int i=1;i<=n;++i){
	// 	cout<<i<<" "<<dp[i][0]<<" "<<dp[i][1]<<endl;
	// }
	cout<<max(dp[1][0],dp[1][1])<<endl;
}