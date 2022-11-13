
#include "Graph.h"
void printMenu(bool condition)
{
	if (condition) {
		cout << "\t\nPractical work #6 IKBO-10-21 Kushkhov I.A. V12\n\n"
			"Theme: Graph.\n"
			"~-~-~-~-~-~-~-~-~-~-~-~-~-~-~MENU~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n\n";
	}
	cout << "Enter [1] to fill the graph\n"
		<< "Enter [2] to insert a node.\n"
		<< "Enter [3] to print the graph.\n"
		<< "Enter [4] to search eulerian cycle.\n"
		<< "Enter [5] to search the skeleton tree\n"
		<< "Enter [6] to output the skeleton tree\n"
		<< "Enter [0] to exit\n";
	cout << "Your choice: ";
}

int main() {
	int graphSize=0;
	short menu;
	printMenu(true);
	bool flag = true;
	Graph* graph = new Graph;
	while (flag) {
		cin >> menu;
		switch (menu) {
		case 1: {
			cout << "Input the graph size: ";
			cin >> graphSize;
			cout << "Input the relations in format: edgeValue edgeName\n";
			graph->fillTheGraph(graphSize);
			break;
		}
		case 2: {

			char currentNode;
			graphNode* relation = new graphNode;
			cout << "Enter the current node name: ";
			cin >> currentNode;
			cout << "Enter the relation ";
			cin >> relation->edgeValue >> relation->secondNodeName;
			graph->addRelation(currentNode, relation);
			// уточнить
			/*graphNode* relation2 = new graphNode;
			relation2->edgeValue = relation->edgeValue;
			relation2->secondNodeName = currentNode;
			graph->addRelation(relation->secondNodeName, relation2);*/
			break;
		}
		case 3: {
			graph->printRelationsList();
			break;
		}
		case 4: {
			if (graphSize == 0) {
				cout << "Fill the graph first!\n";
				break;
			}
			char start;
			cout << "The start node: ";
			cin >> start;

			if (graph->isEulerian(start))
				cout << "The graph has an eulerian cycle\n";
			else
				cout << "The graph hasn't an eulerian cycle\n";
			break;
		}
		case 5: {

			break;
		}
		case 6: {

			break;
		}
		case 0: {

			return 0;
		}
		}
		printMenu(false);
	}
	return 0;
}