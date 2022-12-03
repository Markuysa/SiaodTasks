#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <list>

using namespace std;
class Graph {
	//vector<vector<int>> graph;

	vector<string> paths;
public:
	vector<vector<int>> graph;
	void fillGraph(int size);
	string buildPaths(list<int> &pa, int cur, int dest);
	vector<string> getPaths(int startNode);
	bool checkGraphDeps(map<int, bool>& visited);
	void hamiltonianPaths(int v, vector<bool>& visited, vector<int>& path, int n);
	void findHamiltonianPaths(int n,int size);
};