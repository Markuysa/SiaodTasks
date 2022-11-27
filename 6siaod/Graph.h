#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <stack>
using namespace std;

struct graphNode {
	char secondNodeName;
	int edgeValue;
};
class Graph {

	map<char, vector<graphNode*>> graphRelations;
	
public:
	bool edgeExists(char currentNode, graphNode* secondNode);
	map<char, vector<graphNode*>> getGraphRelations();
	vector<graphNode*> getCurrentRelations(char nodeName);
	void addRelation(char firstsNode,graphNode* secondNode);
	void printRelationsList();
	void fillTheGraph(int graphSize);
	bool isEulerian(char start);
	int DFS(char v, map<char,bool>& visited);
	bool isAllOdd();
	void DFSSpanning(char v, map<char, bool>& visited, stack<char>& spanningTree,char start);
	void printSpanningTree(stack<char> spanningTree);
	char findUnvisited(map<char, bool>& visited, char currentNode);
};