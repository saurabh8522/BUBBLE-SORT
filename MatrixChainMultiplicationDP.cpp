//////////MatrixChainMultiplication///////////////////////
//////////////////////////////////////////////////////////
/* Problem Statement-
Given a sequence of matrices, find the most efficient way to multiply these matrices together. 
The problem is not actually to perform the multiplications, but merely to decide in which order to perform the multiplications.
Given an array p[] which represents the chain of matrices such that the ith matrix Ai is of dimension p[i-1] x p[i]. 
We need to write a function MatrixChainOrder() that should return the minimum number of multiplications needed to multiply the chain. 
Below mentione 4 different ways to solve the problem
1. Naive method implementation in C++
2. recursive method implementation in C++  
3. Dynamic programming using memorization method- C++ implementation
3. Dynamic Programming using tabular method- C++ implementation*/

//1. naive method

#include <bits/stdc++.h>
using namespace std;

int MatrixChainOrder(int p[], int i, int j)
{
	if (i == j)
		return 0;
	int k;
	int min = INT_MAX;
	int count;

	for (k = i; k < j; k++) 
	{
		count = MatrixChainOrder(p, i, k)
				+ MatrixChainOrder(p, k + 1, j)
				+ p[i - 1] * p[k] * p[j];

		if (count < min)
			min = count;
	}

	
	return min;
}
//main function
int main()
{       vector<int> arr;
	int n; //size of array
        cin>>n;
   for(int i=0;i<n;i++)
   {int t;
    cin>>t;
    arr.push_back(t);
   }
	cout << "Minimum number of multiplications is "
		<< MatrixChainOrder(arr, n);
	getchar();
	return 0;
}


//2. recursive method implementation in C++  

#include <bits/stdc++.h>
using namespace std;

// Matrix Ai has dimension p[i-1] x p[i]
// for i = 1..n
int MatrixChainOrder(int p[], int i, int j)
{
	if (i == j)
		return 0;
	int k;
	int min = INT_MAX;
	int count;

	// place parenthesis at different places
	// between first and last matrix, recursively
	// calculate count of multiplications for
	// each parenthesis placement and return the
	// minimum count
	for (k = i; k < j; k++) 
	{
		count = MatrixChainOrder(p, i, k)
				+ MatrixChainOrder(p, k + 1, j)
				+ p[i - 1] * p[k] * p[j];

		if (count < min)
			min = count;
	}

	// Return minimum count
	return min;
}

//main function
int main()
{       vector<int> arr;
	int n; //size of array
        cin>>n;
   for(int i=0;i<n;i++)
   {int t;
    cin>>t;
    arr.push_back(t);
   }
	cout << "Minimum number of multiplications is "
		<< MatrixChainOrder(arr, n);
	getchar();
	return 0;
}



//3. C++ program using Dynamic programming using memoization
#include <climits>
#include <iostream>
using namespace std;

// function
int MatrixChainOrder(int* p, int n)
{
	n++;
	int m[n][n];
	int i, j, k, L, q;

	// initialize dp array with zero
	for (i = 0; i < n; i++)
		m[i][i] = 0;

	// from L = 3 to L = n-1
	for (L = 2; L < n; L++) 
	{
		for (i = 1; i < n - L + 1; i++) 
		{
			j = i + L - 1;
		
			// make m[i][j] = INT_MAX
			m[i][j] = INT_MAX;
			for (k = i; k <= j - 1; k++) 
			{
				q = m[i][k] + m[k + 1][j]
					+ p[i - 1] * p[k] * p[j];
			
				// if q is less than m[i][j]
				// make m[i][j] = q;
				if (q < m[i][j]) {
					m[i][j] = q;
				}
			}
		}
	}

	// return ans as m[1][n-1]
	return m[1][n - 1];
}

int main()
{
	int arr[]; //input array
	int n; //size of array

	cout << "Minimum number of multiplications is "
		<< MatrixChainOrder(arr, n);
	getchar();
	return 0;
}




//4. C++ program using Dynamic programming using tabular

#include <bits/stdc++.h>
using namespace std;

int MatrixChainOrder(int p[], int n)
{

	int m[n][n];

	int i, j, k, L, q;

   
	for (i = 1; i < n; i++)
		m[i][i] = 0;
        //2 for loop to check all the possible cases 
	for (L = 2; L < n; L++) 
	{
		for (i = 1; i < n - L + 1; i++) 
		{
			j = i + L - 1;
			m[i][j] = INT_MAX;
			for (k = i; k <= j - 1; k++) 
			{

				q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
					m[i][j] = q;
			}
		}
	}

	return m[1][n - 1];
}
//main function
int main()
{       vector<int> arr;
	int n; //size of array
        cin>>n;
   for(int i=0;i<n;i++)
   {int t;
    cin>>t;
    arr.push_back(t);
   }
	cout << "Minimum number of multiplications is "
		<< MatrixChainOrder(arr, n);
	getchar();
	return 0;
}

// This code is contributed Sharmila Biswas
