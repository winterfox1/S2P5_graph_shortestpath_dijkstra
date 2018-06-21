#pragma once
#include "Liste.h"
#include "Edge.h"
#include "stdafx.h"

class Edge;

class Node {
private:
	//Attribut zur eindeutigen Identifikation des Knotens.
	string node_key;

	//Attribute fur die Position des Knotens zur spateren Darstellung in der show Methode im Graphen
	int position_x;
	int position_y;

	// Attribut fur die Adjazenzliste im Knoten, in der die Adressen aller ausgehenden Kanten gespeichert sind.
	Liste<Edge*> edges; // Wird automatisch aufgerufen beim Programmstart

public:
	
	Node(string node_key, int position_x, int position_y);
	Node(string node_key);
	Node(const Node &old);		// copy constructor 
	~Node();
	
	//Getter - und Setter - Methoden, um die Attribute in der Klasse Node zu setzen und auszulesen.
	string getKey(void);
	int getPositionX(void);
	int getPositionY(void);

	Liste<Edge*> getEdges(void);
	void setKey(string new_key);
	void setPositionX(int x);
	void setPositionY(int y);
	void setNewEdge(Edge * edge);
};
