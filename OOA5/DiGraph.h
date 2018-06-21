#pragma once
#include "stdafx.h"
#include "Node.h"
#include "Liste.h"

class SFMLGraphVisualizer;

class DiGraph {
protected:
	//GraphVisualizer * graphviz;
	Liste<Node*> nodes;
	Liste<Edge*> edges;
public:
	DiGraph();
	DiGraph(Liste<Node*> nodes, Liste<Edge*> edges);
	~DiGraph();

	void addNode(Node * node);	
	void addNode(std::string key, int x, int y); // Extract
	void addEdge(string key1, string key2, float weight);
	Liste<Node*> getNeighbours(std::string key);
	Liste<Edge*> getEdges(std::string key);
	Liste<Node*> getNodes();



	// P4
	Liste<Edge*> dijkstraShortestPath(std::string start, std::string end);
	Edge* getConnectingEdgeBlyatCyka(Liste<Edge*> Edges, string end);

//	void setVisualizer(GraphVisualizer* graphviz);
//	GraphVisualizer* getVisualizer();

};