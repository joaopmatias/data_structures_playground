#include "graphs_shortest.h"
#include "graphs_flows.h"


int main(){
	vector< vector<int> > graph;
	vector< vector<int> > weights;
	int i, j, k, l, n;
	int query, q;
	cin >> query;
	for(q = 0; q < query; q++){
		cin >> n;
		weights.resize(n);
		graph.resize(n);
		for(i = 0; i < n; i++){
			weights[i].resize(n);
			graph[i].resize(0);
		}
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				cin >> weights[i][j];
			}
		}
		for(i = 0; i < n; i++){
			for(j = i + 1; j < n; j++){
				if(weights[i][j] + weights[j][i] > 0){
					graph[i].push_back(j);
					graph[j].push_back(i);
				}
			}
		}
		cout << "Case " << q+1 << endl;
		cout << edmonds_karp(graph, weights, 0, 5) << endl;
		cout << dinic(graph, weights, 0, 5) << endl;
	}
	return 0;
}
