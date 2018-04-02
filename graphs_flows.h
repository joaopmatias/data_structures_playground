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

//Edmonds-Karp

int edmonds_karp(vector< vector<int> > graph, vector< vector<int> > weights,
			int source, int target){
	int i, j, k, l, n, flow = 0, current;
	deque<int> qu;
	n = graph.size();

	int ante[n];
	int residual_wt[n][n];
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			residual_wt[i][j] = weights[i][j];
		}
	}

	while(true){

		qu.resize(0);
		qu.push_back(source);
		for(i = 0; i < n; i++) ante[i] = -1;
		ante[source] = -2;
		//run BFS
		while( !qu.empty() && qu.back() != target ){
			current = qu.front();
			qu.pop_front();
			for(j = 0; j < graph[current].size(); j++){
				k = graph[current][j];
				if(residual_wt[current][k] > 0 && ante[k] == -1){
					ante[k] = current;
					qu.push_back(k);
					if(k == target) break;
				}
			}
		}

		if(ante[target] == -1) break;
		//capacity of path
		l = INT_MAX;
		current = target;
		while(current != source){
			l = min( l, residual_wt[ante[current]][current] );
			current = ante[current];
		}
		//update residual graph
		current = target;
		while(current != source){
			residual_wt[ante[current]][current] -= l;
			residual_wt[current][ante[current]] += l;
			current = ante[current];
		}
		flow += l;
	}
	return flow;
}


// Dinic
// most people use recursion for DFS part. I guess that would be best.
int dinic(vector< vector<int> > graph, vector< vector<int> > weights,
			int source, int target){
	int i, j, k, l, n, flow = 0, flow_t, now;
	bool dry;
	deque<int> qu;
	n = graph.size();

	int dist[n], ante[n];
	int residual_wt[n][n];
	vector< vector<int> > residual_g (n);
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			residual_wt[i][j] = weights[i][j];
		}
	}

	while(true){
		//Find distances from source
		for(i = 0; i < n; i++) dist[i] = -1;
		dist[source] = 0;
		qu.resize(0);
		qu.push_back(source);
		//BFS. distances
		while( !qu.empty() && qu.back() != target){
			now = qu.front();
			qu.pop_front();
			for(j = 0; j < graph[now].size(); j++){
				k = graph[now][j];
				if(residual_wt[now][k] > 0 && dist[k] == -1){
					dist[k] = dist[now] + 1;
					qu.push_back(k);
					if( k == target ) break;
				}
			}
		}
		//verify existence of a path
		if(dist[target] == -1) break;
		
		//create residual graph
		for(i = 0; i < n; i++) residual_g[i].resize(0);
		for(i = 0; i < n; i++){
			if(dist[i] != -1){
				for(j = 0; j < graph[i].size(); j++){
					k = graph[i][j];
					if(residual_wt[i][k] > 0 && dist[k] > dist[i]){
						residual_g[i].push_back(k);
					}
				}
			}
		}

		//run until distance to target increases
		//DFS . a number of times 
		//Update distances whenever you reach a dead end
		
		ante[source] = -2;
		while(true){
			qu.resize(0);
			qu.push_back(source);
			//DFS
			while( !qu.empty() && qu.back() != target ){
				now = qu.back();
				qu.pop_back();
				dry = true;
				for(j = 0; j < residual_g[now].size(); j++){
					k = residual_g[now][j];
					if( residual_wt[now][k] > 0 && dist[k] > dist[now] ){
						ante[k] = now;
						qu.push_back(k);
						dry = false;
						if(k ==  target) break;
					}
				}
				if(dry) dist[now] = -1;
			}

			//find path flow
			if( qu.empty() ) break;
			now = target;
			flow_t = INT_MAX;
			while( now != source ){
				flow_t = min(flow_t, residual_wt[ante[now]][now]);
				now = ante[now];
			}

			//update residual_wt
			now = target;
			while( now != source ){
				residual_wt[ante[now]][now] -= flow_t;
				residual_wt[now][ante[now]] += flow_t;
				now = ante[now];
			}
			flow += flow_t;
		}
	}
	return flow;
}

//Dinic 2 O(VE log(V))


// max-cut-min-flow theorem