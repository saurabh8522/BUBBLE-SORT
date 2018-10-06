#include<bits/stdc++.h>
using namespace std;
#define f(i,a,b) 	for(int i=a;i<b;++i)
#define rf(i,a,b) 	for(int i=b;i>=a;--i)
#define ln 		"\n"
typedef long long ll;
typedef long double ld;
#define pb push_back
#define mod 1000000007
#define debug(a,b,c) cout<<a<<"->"<<b<<"->"<<c<<endl; 
ll fastexpo(ll x,ll y,ll m){ll temp=1;while(y>0){if(y&1)temp = ((temp%m)*(x%m))%m;x = ((x%m)*(x%m))%m;}return temp;}

ll n;
ll swap(ll *x, ll *y)
{
	ll temp=*x;
	*x=*y;
	*y=temp;
}
ll sort(ll arr[])
{

	
	for(ll i=0; i<n; i++)
	{
		bool flag=1;
	
		for(ll j=0; j<n-1-i; j++)
			if(arr[j]>arr[j+1]) 
			{
				//debug(arr[j],arr[j+1],j);
				swap(&arr[j+1],&arr[j]);
					flag=0;			//flag here breaks loop is no comparision is done
			}
			if(flag==1) break;
			
	}
	cout<<"sorted array is:";
	f(i,0,n) cout<<arr[i]<<"	";
	return 0;				
	
}

int main()
{
	 	ios::sync_with_stdio(false);
	 	cin.tie(NULL);
	 	//bubble sort
	 	cout<<"enter no of elements of array:";
	 	cin>>n;
	 	ll arr[n];
	 	f(i,0,n) cin>>arr[i];
	 	sort(arr);
}



