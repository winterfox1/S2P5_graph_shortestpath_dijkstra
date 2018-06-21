#pragma once
#include "stdafx.h"
#include "Node.h"

class Node;

class Edge {
private: 
	//Zum speichern der Adressen der verbundenen Knoten.
	Node * startnode;
	Node * endnode;

	//Zum Speichern des Kantengewichts.
	float weight;

public:
	Edge(Node * startnode, Node * endnode, float weight);
	Edge();
	~Edge();
		
	//Getter - und Setter - Methoden, um die Attribute in der Klasse Edge zu setzen und auszulesen :
	//Getter - Methoden:
	float getWeight();
	Node * getStartNode();
	Node * getEndNode();

	//Setter - Methoden:
	void setWeight(float w);
	void setStartNode(Node * n);
	void setEndNode(Node * n);
};