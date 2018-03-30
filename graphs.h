#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <deque>
#include <set>

typedef pair<int, int> pii;

using namespace std;

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

int bellman_ford(vector< vector<pii> > graph, int source, int sink){
	int l, i, j, k;
	l = graph.size();

	int shortest[l];
	for(i = 0; i < l; i++) shortest[i] = -1;
	shortest[init] = 0;

	// continue

	return 0;
}



