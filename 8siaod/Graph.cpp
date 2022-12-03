
#include "Graph.h"
void Graph::fillGraph(int countDeps) {
	int countDepsVertice;
	int temp;
	this->graph.resize(countDeps);
	for (int i = 1; i <= countDeps; i++) {
		cout << "Enter the dependencies number of " << i << " vertice: ";
		cin >> countDepsVertice;
		cout << "Enter the dependencies of " << i << " vertice: \n";
		for (int j = 0; j < countDepsVertice; j++) {
			cout << "The " << j + 1 << " dependency: ";
			cin >> temp;
			this->graph[i-1].push_back(temp);
		}
	}
}
void printPath(vector<int> const& path)
{
	for (int i : path) {
		cout << i << "->";
	}
	cout<<path[0] << endl;
}
void Graph::hamiltonianPaths(int v, vector<bool>& visited,
	vector<int>& path, int n)
{

	if (path.size() == n)
	{

		printPath(path);
		return;
	}


	for (int w : this->graph[v])
	{

		if (!visited[w])
		{
			visited[w] = true;
			path.push_back(w);


			hamiltonianPaths(w, visited, path, n);


			visited[w] = false;
			path.pop_back();
		}
	}
}

void Graph::findHamiltonianPaths(int n,int size)
{


		vector<int> path;
		path.push_back(n);

		vector<bool> visited(size);
		visited[n] = true;

		hamiltonianPaths(n ,visited, path, size);
	
}
//void Graph::buildPaths(int startVertice,string& path,int first) {
//	map<int, bool> visited;
//	vector<int> currentPaths = this->graph[startVertice];
//
//	visited[startVertice] = true;
//
//	path += to_string(startVertice)+"->";
//	for (auto i : currentPaths) {
//		if (visited[i] == false) {
//			path += to_string(i) + "->";
//			buildPaths(visited[i],path,first);
//		}
//		else {
//			if (startVertice == first) this->paths.push_back(path);
//		}
//
//	}
//}
bool Graph::checkGraphDeps(map<int, bool>& visited) {

	for (auto i : visited) {
		if (!i.second) return false;
	}
	return true;

}
//string Graph::buildPaths(int currentNode, map<int, bool>& visited,string& path,int startNode){
//	string visitedVertices = "";
//	visited[currentNode] = true;
//	for (auto v : this->graph[currentNode]) {
//		if (v == startNode) continue;
//		if (!visited[v]) {
//			path += v;
//			buildPaths(v, visited, path, startNode);
//		}
//		else {
//			if (visited.size() == this->graph.size() && checkGraphDeps(visited)) {
//				return path;	
//			}
//		}
//	}
//	return path;
//}

string Graph::buildPaths(list<int> &pa, int cur, int dest)
{
	if (cur == dest && pa.size()!=0) return "";
	pa.push_back(cur);
	for (size_t i = 0; i < this->graph[cur].size(); i++)
	{
		if (cur == dest && pa.size() == this->graph.size() + 1) {
			for_each(pa.begin(), pa.end(), [](int a) {cout << " " << a; });
			cout << endl;
			return " ";
		}
		if (find((++pa.begin()), pa.end(), this->graph[cur][i]) == pa.end())
		{
			buildPaths(pa, this->graph[cur][i], dest);
		}
	}
	return " ";
}
void appendToPaths(list<int>& pa, vector<string> &paths) {
	string result = "";
	for (auto i : pa) {
		
		result += to_string(i) + "->";
	}
	result += result[0];
	paths.push_back(result);

}
vector<string> Graph::getPaths(int startNode) {
	map<int, bool> visited;
	string result = "";
	list<int> pa;
	int a;
	cin >> a;
	for (auto i : this->graph[startNode]) {
		buildPaths(pa, a, a);
		appendToPaths(pa, this->paths);
		pa.clear();
	}
	return this->paths;
}
