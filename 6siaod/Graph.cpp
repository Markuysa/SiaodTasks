
#include "Graph.h"

map<char, vector<graphNode*>> Graph::getGraphRelations() {
	return this->graphRelations;
}
vector<graphNode*> Graph::getCurrentRelations(char nodeName) {
	return this->graphRelations[nodeName];
}

void Graph::addRelation(char firstsNode, graphNode* secondNode) {
	
	auto findByKey = this->graphRelations.find(firstsNode);
	//if the iterator != end of the map ==> the element exists 
	// we should add a relation in current element's vector
	if (findByKey != this->graphRelations.end()) {
		this->graphRelations.at(firstsNode).push_back(secondNode);
	}
	else {
		// creating a new node if it doesnt exist yet
		vector<graphNode*> nodeRelations;
		if (secondNode != nullptr) {
			nodeRelations.push_back(secondNode);
		}
		this->graphRelations.insert(make_pair(firstsNode, nodeRelations));
	}
}
void printRelationsVector(vector<graphNode*> relations) {

	for (size_t i = 0; i < relations.size(); i++) {
			cout << relations[i]->edgeValue << " " << relations[i]->secondNodeName<<" ";
	}
	cout << endl;
}
void Graph::printRelationsList() {
	std::map<char, vector<graphNode*>>::iterator it = this->graphRelations.begin();
	for (it; it != this->graphRelations.end(); ++it) {
		cout << "Node: " << it->first << endl;
		cout << "RelationsList: ";
		printRelationsVector(it->second);
	}
}
void Graph::fillTheGraph(int graphSize) {
	char currentNode;
	int numberOfRelations;
	graphNode* relation=new graphNode;
	graphNode* secondNoderelation = new graphNode;
	for (size_t i = 0; i < graphSize; i++) {
		cout << "Enter the current node name: ";
		cin >> currentNode;
		cout << "Enter the number of relations ";
		cin >> numberOfRelations;
		if (numberOfRelations == 0) {
			this->addRelation(currentNode,nullptr);
		}
		for (size_t j = 0; j < numberOfRelations; j++) {
			cout << "Input the " << j+1 << " relation:";
			cin >> relation->edgeValue >> relation->secondNodeName;
			this->addRelation(currentNode, relation);
			/*secondNoderelation->edgeValue = relation->edgeValue;
			secondNoderelation->secondNodeName = currentNode;
			this->addRelation(relation->secondNodeName, secondNoderelation);*/
			relation = new graphNode;
		}
	}

}
int Graph::DFS(char currentNode, map<char,bool>& visited)
{
	int visitedVertices = 1;
	visited[currentNode] = true;
	for (graphNode* v : this->graphRelations[currentNode]) {
		if (!visited[v->secondNodeName])
			visitedVertices += DFS(v->secondNodeName, visited);
	}
	return visitedVertices;
}
bool Graph::isEulerian(char start) {
	map<char,bool> visited;
	// подсчет количества вершин с четной степенью
	if (isAllOdd() && (DFS(start, visited) == this->graphRelations.size())) {
		return true;
	}
	return false;
}
bool Graph::isAllOdd() {
	size_t counter = 0;
	/*Граф является эйлеровым тогда и только тогда, когда он связен и все степени его вершин четны.*/
	std::map<char, vector<graphNode*>>::iterator it = this->graphRelations.begin();
	for (it; it != this->graphRelations.end(); ++it) {
		if (it->second.size() % 2 != 0)
			return false;
	}
	return true;
}