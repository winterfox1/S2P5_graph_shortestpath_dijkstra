#pragma once
#include "stdafx.h"
#include "Edge.h"
#include "Node.h"

Edge::Edge(Node * startnode, Node * endnode, float weight) {
	this->startnode = startnode;
	this->endnode = endnode;
	this->weight = weight;
}

Edge::Edge() {

}

Edge::~Edge() {

}

/*Getter - und Setter - Methoden, um die Attribute in der Klasse Edge zu setzen
und auszulesen :*/
float Edge::getWeight(void) {
	return this->weight;
}

Node * Edge::getStartNode(void) {
	return this->startnode;
}

Node * Edge::getEndNode(void) {
	return this->endnode;
}

void Edge::setWeight(float w) {
	this->weight = w;
}

void Edge::setStartNode(Node * n) {
	this->startnode = n;
}

void Edge::setEndNode(Node * n) {
	this->endnode = n;
}


