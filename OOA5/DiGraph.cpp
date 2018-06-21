#pragma once
#include "stdafx.h"
#include "DiGraph.h"
#include "Liste.h"
#include "Node.h"
#include "pq.h"

DiGraph::DiGraph() {

}

DiGraph::~DiGraph() {

}

DiGraph::DiGraph(Liste<Node*> nodes, Liste<Edge*> edges) {
	this->nodes = nodes;
	this->edges = edges;
}

void DiGraph::addNode(Node * node) {
	this->nodes.append(node);
}

void DiGraph::addNode(std::string key, int x, int y) {
	Node node = Node(key, x, y);
	this->nodes.append(&node);
}

void DiGraph::addEdge(string key1, string key2, float weight) {
	Node *node1 = nodes.findElement(key1);
	Node *node2 = nodes.findElement(key2);

	//Edge edge = Edge();
	//edge.setStartNode(node1);
	//edge.setEndNode(node2);
	//edge.setWeight(weight);

	//node1->setNewEdge(&edge);

	Edge *edge = new Edge();
	edge->setStartNode(node1);
	edge->setEndNode(node2);
	edge->setWeight(weight);

	node1->setNewEdge(edge);
}

Liste<Node*> DiGraph::getNodes() {
	return this->nodes;
}

Liste<Edge*> DiGraph::getEdges(string key) {
	Node* node = nodes.findElement(key);
	return node->getEdges();
}

Liste<Node*> DiGraph::getNeighbours(string key) {
	Liste<Node*> neighbours;
	Liste<Edge*> neighbourEdges;

	Node *position = nodes.findElement(key);
	neighbourEdges = position->getEdges();

	for (int x = 0; x < neighbourEdges.size(); x++) {
		neighbours.append(neighbourEdges[x]->getEndNode());
	}

	return neighbours;
}

Edge* DiGraph::getConnectingEdgeBlyatCyka(Liste<Edge*> Edges, string end) {

	//Edge * connectingEdge;

	for (int x = 0; x < Edges.size(); x++) {
		if (Edges[x]->getEndNode()->getKey() == end) {
			return Edges[x];
		}
	}
	return nullptr;
}

Liste<Edge*>DiGraph::dijkstraShortestPath(string start, string end) {

	priorityqueue<Node*> PQ;
	map<Node*, float> dist;
	map<Node*, Node*> previous;
	Liste<Edge*> S;

	for (int i = 0; i < nodes.size(); i++) {
		if (nodes.getValueAt(i)->getKey() != start) {
			dist[nodes[i]] = float INFINITY;
		}
		else
		{
			dist[nodes[i]] = 0;
		}
		previous[nodes[i]] = nullptr;
		PQ.insert(dist.find(nodes[i])->second, nodes[i]);
	}

	Node* u = nullptr;
	Node* v = nullptr;
	float alt = 0.0;

	while (PQ.first != nullptr) {

		u = PQ.extractMin();

		for (int i = 0; i < u->getEdges().size(); i++) {
			v = u->getEdges().getValueAt(i)->getEndNode();
			alt = dist.find(u)->second + u->getEdges().getValueAt(i)->getWeight();

			if (alt < dist.find(v)->second) {
				dist.at(v) = alt;
				previous[v] = u;
				PQ.decreaseKey(v, alt);
			}
		}
	}

	u = nodes.findElement(end);

	while (previous.find(u)->second != nullptr) {

		Liste <Edge*> prevedges = (previous.find(u)->second)->getEdges();
		for (int i = 0; i < prevedges.size(); i++) {
			if (prevedges[i]->getEndNode() == u) {
				S.append(prevedges[i]);
				break;
			}

		}

		u = previous.find(u)->second;

	}
	return S;
}


//void DiGraph::setVisualizer(GraphVisualizer* graphviz) {
//	this->graphviz = graphviz;
//}
//
//GraphVisualizer * DiGraph::getVisualizer(){
//	return this->graphviz;
//}


//#if 0
//Liste<Edge*>DiGraph::dijkstraShortestPath(string start, string end) {
//	priorityqueue<Node*> pq;
//	Liste<Edge*> shorty;
//	map<Node*, float> dist;
//	map<Node*, Node*> previous;
//
//
//	for (int i = 0; i < nodes.size(); i++) {
//		if (nodes[i]->getKey() != start) {
//			dist[nodes[i]] = float INFINITY; //std::numeric_limits<float>::infinity();
//		}
//		else {
//			dist[nodes[i]] = 0.0;
//		}
//		previous[nodes[i]] = nullptr;
//		pq.insert(dist.find(nodes[i])->second, nodes[i]); // find sucht nach node[i] und second ist der zweite Parameter der Map
//	}
//
//	float alt = -1;
//	Node *u = nullptr;
//	Node *v = nullptr;
//
//	while (pq.first != NULL) {
//		u = pq.extractMin();
//
//		Liste<Edge*> neighbourEdges = u->getEdges();
//
//		for (int x = 0; x < neighbourEdges.size(); x++) {
//			v = neighbourEdges[x]->getEndNode();
//
//
//			if (dist.find(u)->second == float INFINITY) {
//				alt = neighbourEdges[x]->getWeight();
//			}
//
//			alt = dist.find(u)->second + neighbourEdges[x]->getWeight();
//
//			if (alt < dist.find(v)->second) {
//				dist.at(v) = alt; // dist[v] = alt
//				previous[v] = u;
//				pq.decreaseKey(v, alt);
//			}
//		}
//	}
//
//	u = nodes.findElement(end);
//	Node *startNode = nodes.findElement(start);
//
//	while (u != startNode) { //  u != startNode sonst exception wenn der versucht davon nen previous wegzuschreiben
//		Liste<Edge*> neighbourEdges = previous.find(u)->second->getEdges(); // die previous nodes haben die edge liste also endknoten->previous->liste
//
//		shorty.append(getConnectingEdgeBlyatCyka(neighbourEdges, u->getKey()));
//
//		u = previous.find(u)->second;
//
//	}
//	return shorty;
//}
//#endif
