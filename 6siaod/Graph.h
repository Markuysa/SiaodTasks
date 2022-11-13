#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

struct graphNode {
	char secondNodeName;
	int edgeValue;
};
class Graph {

	map<char, vector<graphNode*>> graphRelations;
	
public:

	map<char, vector<graphNode*>> getGraphRelations();
	vector<graphNode*> getCurrentRelations(char nodeName);
	void addRelation(char firstsNode,graphNode* secondNode);
	void printRelationsList();
	void fillTheGraph(int graphSize);
	bool isEulerian(char start);
	int DFS(char v, map<char,bool>& visited);
	bool isAllOdd();
};