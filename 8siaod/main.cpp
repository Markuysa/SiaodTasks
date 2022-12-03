

#include "Graph.h"

int main() {
	Graph* graph = new Graph;
	string result="";
	map<int, bool> visited;
	int countDeps;
	cin >> countDeps;
	//graph->fillGraph(countDeps);
	graph->graph.resize(countDeps);
	graph->graph[0].push_back(1);
	graph->graph[0].push_back(4);
	graph->graph[0].push_back(3);

	graph->graph[1].push_back(0);
	graph->graph[1].push_back(2);

	graph->graph[2].push_back(1);
	graph->graph[2].push_back(4);
	graph->graph[2].push_back(3);

	graph->graph[3].push_back(0);
	graph->graph[3].push_back(4);
	graph->graph[3].push_back(2);

	graph->graph[4].push_back(0);
	graph->graph[4].push_back(3);
	graph->graph[4].push_back(2);

	graph->findHamiltonianPaths(2,countDeps);


}