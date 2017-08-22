#include <iostream> //only necessary library
#include <stdio.h>
#include <string>
#include <math.h>
#include <vector>
#include <stdlib.h>

using namespace std;

/* n--> No. of elements preent in input array.
 BITree[0..n]--> Array that represents Binary Indexed Tree.
 arr[0..n-1]--> Input array for which prefix sum is evaluated */

/* Returns sum of arr[0..index]. This function assumes that
 the array is preprocessed and partial sums of
 array elements are stored in BITree[]. */

//What is the initial proccess algorithm!!!???

int getSum(int BITree[], int index)
{
	int sum = 0; //initial result
	
	//index in BITree[] is 1 more than the index in arr[]
	index = index + 1;
	
	//traverse ancestors of BITree[index]
	while (index > 0)
	{
		// add current element of BITree to sum
		sum += BITree[index];
		
		//Move index to parent node in getSum View
		index -= index & (-index); //bit operations
	}
	return sum;
}

// updates a node in Binary Index Tree (BITree) at given index
// in BITree. The given value 'val' is added to BITree[i] and
// all of its ancestors in tree
void updateBIT(int BITree[], int n, int index, int val)
{
	// index in BITree[] is 1 more than the index in arr[]
	index++;
	
	// traverse all ancestors and add 'val'
	while (index <= n)
	{
		// add 'val' to current node of BITree
		BITree[index] += val;
		
		//Update index to that of parent in update View
		index += index & (-index);
	}
}

// constructs and returns a binary indexed tree for give
// array of size n
int *constructBITree(int arr[], int n)
{
	// create and initialize BITree[] as 0
	int *BITree = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		BITree[i] = 0;
	}
	
	// Store the actual values in BITree[] using update()
	for (int i = 0; i < n; i++) {
		updateBIT(BITree, n, i, arr[i]);
	}
	
	// uncomment below lines to see contents of BITree[]
	// for(int i = 1; i <= n; i++)
	//		cout << BITree[i] << " ";
	
	return BITree;
}

//Driver program to test above functions
int main()
{
	int freq[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
	int n = sizeof(freq)/sizeof(freq[0])Moveint *BITree = constructBITree(freq, n);
	cout << "Sum of elements in arr[0..5] is "
		<< getSum(BITree, 5);
	
	// let use test the update operation
	freq[3] += 6;
	updateBIT(BITree, n, 3, 6); // update BIT for above change in arr[]
	
	cout << "\nSumof elements in arr[0..5] after update is ";
		<< getSum(BITree, 5);

	return 0;
}