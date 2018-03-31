#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <deque>
#include <set>
#include <limits.h>

using namespace std;

typedef pair<int, int> pii;


//implement graphs as vector< vector<int> >

//Dijkstra

int dijkstra(vector< vector<int> > graph, int init, int term){
	int l, i, j, k, current;
	l = graph.size();

	deque<int> qu; //use set if there's weights
	qu.push_back(init);
	int check[l];
	for(i = 0; i < l; i++) check[i] = -1;
	check[init] = 0;

	while( !qu.empty() ){
		current = qu.front();
		qu.pop_front();
		for(auto it = graph[current].begin(); it != graph[current].end(); it++){
			if(check[*it] == -1){
				check[*it] = check[current] + 1;
				qu.push_back(*it);
				if(*it == term) return check[*it];
			}
		}
	}
	return -1;
}


//Bellman-Ford

int bellman_ford(vector< vector<int> > graph, vector< vector<int> > weights,
				int source, int target){
	int l, i, j, k, n, dummy;
	l = graph.size();

	int shortest[l];
	for(i = 0; i < l; i++) shortest[i] = INT_MAX;
	shortest[source] = 0;

	for(dummy = 0; dummy < l; dummy++){
		for(i = 0; i < l; i++){
			for(j = 0; j < graph[i].size(); j++){
				k = graph[i][j];
				if( shortest[ k ] != INT_MAX){
					shortest[k] = min( shortest[k], shortest[i] + weights[i][k] );
				}
			}
		}
	}
	return shortest[target];
}

//Floyd-Warshall

vector< vector<int> > floyd_warshall(vector< vector<int> > graph,
						vector< vector<int> > weights){
	int i, j, k, l; 
	l = graph.size();
	vector< vector<int> > ans (l, vector<int> (l, INT_MAX));
	for(i = 0; i < l; i++) ans[i][i] = 0;

	for(k = 0; k < l; k++){ //test if this vertex is between i and j
		for(i = 0; i < l; i++){
			for(j = 0; j < l; j++){
				if(weights[i][k] != INT_MAX && weights[k][j] != INT_MAX &&
					weights[i][j] > weights[i][k] + weights[k][j]){
					weights[i][j] = weights[i][k] + weights[k][j];
				}
			}
		}
	}
	return ans;
}


