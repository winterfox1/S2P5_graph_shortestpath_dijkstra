#include "stdafx.h"
#include "DiGraph.h"
#include "Edge.h"
#include "Node.h"
#include "sfml.h"


int main() {
	DiGraph g;
	float resize = 1; 

	g.addNode(new Node("Aachen", (100 * resize), (600 * resize)));
	g.addNode(new Node("Berlin", (300 * resize), (650 * resize)));
	g.addNode(new Node("Koeln", (300 * resize), (300 * resize)));
	g.addNode(new Node("Essen", (900 * resize), (300 * resize)));
	g.addNode(new Node("Bonn", (300 * resize), (150 * resize)));
	g.addNode(new Node("Krefeld", (100 * resize), (160 * resize)));

	g.addEdge("Aachen", "Berlin", 7);
	g.addEdge("Koeln", "Aachen", 9);
	g.addEdge("Aachen", "Krefeld", 7);
	g.addEdge("Berlin", "Essen", 40);
	g.addEdge("Berlin", "Koeln", 3);
	g.addEdge("Koeln", "Essen", 31);
	g.addEdge("Bonn", "Essen", 8);
	g.addEdge("Krefeld", "Bonn", 1);

	cout << "=== finde kürzesten Pfad nach Dijkstra! ===" << endl;
	Liste<Edge*> path = g.dijkstraShortestPath("Aachen", "Essen");

	cout << endl << endl << "Kürzester Pfad gefunden:" << endl;

	for (size_t x = 0; x < path.size(); x++) {
		cout << "Edge " << x << ": " << path[x]->getStartNode()->getKey() << "\t to " << path[x]->getEndNode()->getKey() << "\t Weight: " << path.getValueAt(x)->getWeight() << endl;
	}

	SFMLGraphVisualizer graphviz;
	graphviz.highlightPath(path);
	graphviz.visualize(g);

	//system("pause");
}
