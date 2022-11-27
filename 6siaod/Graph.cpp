
#include "Graph.h"
#include <iomanip>

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
bool Graph::edgeExists(char currentNode, graphNode* secondNode) {
	auto it = find(this->graphRelations[currentNode].begin(), this->graphRelations[currentNode].end(), secondNode);
	if (it == this->graphRelations[currentNode].end())
		return false;
	return true;
}
char Graph::findUnvisited(map<char, bool>& visited,char currentNode) {

	vector<graphNode*> currentNodeRelations = this->graphRelations[currentNode];

	for (graphNode* node : currentNodeRelations) {
		if (visited[node->secondNodeName])
			continue;
		else {
			return node->secondNodeName;
		}
	}
	return currentNode;
}
void Graph::DFSSpanning(char currentNode, map<char, bool>& visited, stack<char>& spanningTree,char start) {
	for (graphNode* node : this->graphRelations[currentNode]) {
		if (this->graphRelations.size() == spanningTree.size()) return;
		if (node->secondNodeName != start) {
			visited[currentNode] = true;
			if (visited[node->secondNodeName] == false && edgeExists(currentNode, node)) {
				spanningTree.push(currentNode);
				DFSSpanning(node->secondNodeName, visited, spanningTree, currentNode);
			}
			else {
				if (visited[node->secondNodeName]) {
					char top = spanningTree.top();
					spanningTree.push(currentNode);
					char unvisitedVertice = findUnvisited(visited, top);
					if (unvisitedVertice == top)
						return;
					DFSSpanning(unvisitedVertice, visited, spanningTree, top);
				}
			}
		}
		else {
			if (!visited[currentNode] && this->graphRelations[currentNode].size()==1) spanningTree.push(currentNode);
			continue;
		}
	}
}
vector<char> convertToVector(stack<char>& spanningTree){
	vector<char> spanTree;
	while (spanningTree.size()!=0) {
		spanTree.push_back(spanningTree.top());
		spanningTree.pop();
	}
	return spanTree;
}
//bool findInVector(vector<graphNode*> searchVector, char searchElement) {
//	auto it = find(searchVector.begin(), searchVector.end(), searchElement);
//	return it == searchVector.end() ? false : true;
//}
void Graph::printSpanningTree(stack<char> spanningTree) {
	char currentNode;
	vector<char> outputHandler = convertToVector(spanningTree);
	int size = outputHandler.size();
	int tabs = -4;
	for (int i = 0; i < size ; i++) {
		tabs += 4;
		if (i == size-1)
			cout << endl << setw(tabs) <<right <<outputHandler[size - i - 1];
		else
			cout << endl <<setw(tabs) << right <<outputHandler[size - i - 1] << "|---";
	}
	cout << endl;
}