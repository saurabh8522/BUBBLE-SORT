/////////////////Generic Tree or N-ary Tree////////////////////////////////////////
/*Defination-Generic trees are a collection of nodes where each node is a data structure that consists of records 
and a list of references to its children(duplicate references are not allowed). Unlike the linked list, each node stores 
the address of multiple nodes. Every node stores address of its children and the very first node’s address will be stored in
a separate pointer called root.

The Generic trees are the N-ary trees which have the following properties: 
1. Many children at every node.
2. The number of nodes for each node is not known in advance.

Below are 3 famous generic tree related problems-
1.Remove all leaf nodes from a Generic Tree or N-ary Tree
2. Height of a generic tree from parent array
3.C++ program to find the maximum path length */
///////////////////////////////////////////////////////////////////////////////////////

//1.Remove all leaf nodes from a Generic Tree or N-ary Tree
// C++ program to delete the 
// leaf from the generic tree 

#include <bits/stdc++.h> 
using namespace std; 

// a treenode class 
class TreeNode { 
public: 
	int data; 
	vector<TreeNode*> children; 

	TreeNode(int data) 
	{ 
		this->data = data; 
	} 
}; 

// Recursive function which delete 
// the leaf from tree 
void removeLeaf(TreeNode* root) 
{ 
	// if root->children is a leaf node 
	// then delete it from children vector 
	for (int i = 0; 
		i < root->children.size(); 
		i++) { 

		TreeNode* child 
			= root->children[i]; 

		// if it is a leaf 
		if (child->children.size() == 0) { 

			// shifting the vector to left 
			// after the point i 
			for (int j = i; 
				j < root->children.size(); 
				j++) 
				root->children[j] 
					= root->children[j + 1]; 

			// delete the last element 
			root->children.pop_back(); 

			i--; 
		} 
	} 

	// Remove all leaf node 
	// of children of root 
	for (int i = 0; 
		i < root->children.size(); 
		i++) { 

		// call function for root->children 
		removeLeaf(root->children[i]); 
	} 
} 

// Function which will print the 
// tree level wise 
void printTheTree(TreeNode* root) 
{ 
	if (root == NULL) 
		return; 

	cout << root->data << " "
		<< ":"; 
	for (int i = 0; 
		i < root->children.size(); 
		i++) 
		cout << root->children[i]->data 

			<< " "; 
	cout << endl; 

	for (int i = 0; 
		i < root->children.size(); 
		i++) 
		printTheTree(root->children[i]); 
} 

int main() 
{ 
	int n; cin>>n; 
	vector<int> v[n + 1]; 

	// initialize the tree given in the diagram
  // insert in the tree like the example given below
 //	v[1].push_back(2), v[2].push_back(1); 

	printHeights(v, n); 

	return 0; 
} 

//2. Height of a generic tree from parent array

#include <bits/stdc++.h> 
#define MAX 1001 
using namespace std; 

// Adjacency list to 
// store N-ary tree 
vector<int> adj[MAX]; 

// Build tree in tree in O(n) 
int build_tree(int arr[], int n) 
{ 
	int root_index = 0; 

	// Iterate for all nodes 
	for (int i = 0; i < n; i++) { 

		// if root node, store index 
		if (arr[i] == -1) 
			root_index = i; 

		else { 
			adj[i].push_back(arr[i]); 
			adj[arr[i]].push_back(i); 
		} 
	} 
	return root_index; 
} 

// Applying BFS 
int BFS(int start) 
{ 
	// map is used as visited array 
	map<int, int> vis; 

	queue<pair<int, int> > q; 
	int max_level_reached = 0; 

	// height of root node is zero 
	q.push({ start, 0 }); 

	// p.first denotes node in adjacency list 
	// p.second denotes level of p.first 
	pair<int, int> p; 

	while (!q.empty()) { 

		p = q.front(); 
		vis[p.first] = 1; 

		// store the maximum level reached 
		max_level_reached = max(max_level_reached, 
								p.second); 

		q.pop(); 

		for (int i = 0; i < adj[p.first].size(); i++) 

			// adding 1 to previous level 
			// stored on node p.first 
			// which is parent of node adj[p.first][i] 
			// if adj[p.first][i] is not visited 
			if (!vis[adj[p.first][i]]) 
				q.push({ adj[p.first][i], p.second + 1 }); 
	} 

	return max_level_reached; 
} 

int main() 
{ 
	int n; cin>>n; 
	vector<int> v[n + 1]; 

	// initialize the tree given in the diagram
  // insert in the tree like the example given below
 //	v[1].push_back(2), v[2].push_back(1); 
	int root_index = build_tree(parent, n); 

	int ma = BFS(root_index); 
	cout << "Height of N-ary Tree=" << ma; 
	return 0; 
} 

//3.C++ program to find the maximum path length 

#include <bits/stdc++.h> 
using namespace std; 
const int MAX_NODES = 100; 

int in[MAX_NODES]; 
int out[MAX_NODES]; 

// function to pre-calculate the array in[] 
// which stores the maximum height when travelled 
// via branches 
void dfs1(vector<int> v[], int u, int parent) 
{ 
	// initially every node has 0 height 
	in[u] = 0; 

	// traverse in the subtree of u 
	for (int child : v[u]) { 

		// if child is same as parent 
		if (child == parent) 
			continue; 

		// dfs called 
		dfs1(v, child, u); 

		// recursively calculate the max height 
		in[u] = max(in[u], 1 + in[child]); 
	} 
} 

// function to pre-calculate the array ouut[] 
// which stores the maximum height when traveled 
// via parent 
void dfs2(vector<int> v[], int u, int parent) 
{ 
	// stores the longest and second 
	// longest branches 
	int mx1 = -1, mx2 = -1; 

	// traverse in the subtress of u 
	for (int child : v[u]) { 
		if (child == parent) 
			continue; 

		// compare and store the longest 
		// and second longest 
		if (in[child] >= mx1) { 
			mx2 = mx1; 
			mx1 = in[child]; 
		} 

		else if (in[child] > mx2) 
			mx2 = in[child]; 
	} 

	// traverse in the subtree of u 
	for (int child : v[u]) { 
		if (child == parent) 
			continue; 

		int longest = mx1; 

		// if longest branch has the node, then 
		// consider the second longest branch 
		if (mx1 == in[child]) 
			longest = mx2; 

		// recursively calculate out[i] 
		out[child] = 1 + max(out[u], 1 + longest); 

		// dfs function call 
		dfs2(v, child, u); 
	} 
} 

// function to print all the maximum heights 
// from every node 
void printHeights(vector<int> v[], int n) 
{ 
	// traversal to calculate in[] array 
	dfs1(v, 1, 0); 

	// traversal to calculate out[] array 
	dfs2(v, 1, 0); 

	// print all maximum heights 
	for (int i = 1; i <= n; i++) 
		cout << "The maximum height when node "
			<< i << " is considered as root"
			<< " is " << max(in[i], out[i]) 
			<< "\n"; 
} 

int main() 
{ 
	int n; cin>>n; 
	vector<int> v[n + 1]; 

	// initialize the tree given in the diagram
  // insert in the tree like the example given below
 //	v[1].push_back(2), v[2].push_back(1); 

	printHeights(v, n); 

	return 0; 
} 
//this code is contributed by Sharmila
