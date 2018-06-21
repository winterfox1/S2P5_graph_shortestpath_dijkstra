#pragma once
#include "stdafx.h"
#include "Node.h"

Node::Node(string node_key, int position_x, int position_y) {
	this->node_key = node_key;
	this->position_x = position_x;
	this->position_y = position_y;
}

Node::Node(string node_key) {
	this->node_key = node_key;
}

// copy constructor
Node::Node(const Node &old) {
	this->node_key = node_key;
	this->position_x = position_x;
	this->position_y = position_y;

	for (size_t x = 0; x < this->edges.size(); x++) {
		cout << edges[x]->getWeight() << endl;
	}
}

Node::~Node() {

}

//---------------   getter     ---------------
string Node::getKey(void) {
	return this->node_key;
}

int Node::getPositionX(void) {
	return this->position_x;
}

int Node::getPositionY(void) {
	return this->position_y;
}

Liste<Edge*> Node::getEdges(void) {
	//cout << "GetEdgesTest " << endl;
	//for (size_t x = 0; x < this->edges.size(); x++) {
	//	cout << "Start: " << this->edges[x]->getStartNode()->getKey() << "End: " << this->edges[x]->getEndNode()->getKey() << endl;
	//	cout << "weight " << this->edges.getValueAt(x)->getWeight() << endl;
	//}

	return this->edges;
}

//---------------   setter     ---------------
void Node::setKey(string new_key) {
	this->node_key = new_key;
}

void Node::setPositionX(int x) {
	this->position_x = x;
}

void Node::setPositionY(int y) {
	this->position_y = y;
}

void Node::setNewEdge(Edge * edge) {
	this->edges.append(edge);
}