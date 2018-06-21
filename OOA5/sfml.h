#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Mouse.hpp>
#include <math.h>
#include <sstream>
#include "stdafx.h"
//#include <chrono>
//#include <thread>

#define NODERADIUS 30

//using namespace std;

class GraphVisualizer {

	virtual void highlightPath(Liste<Edge*> path) = 0;
	virtual void visualize(DiGraph &g) = 0;
};


class SFMLGraphVisualizer : GraphVisualizer {
private:
	sf::RenderWindow window;
	sf::Font font;

	Liste<Edge*> pathEdges;
	Liste<Node*> pathNodes;

	size_t pnSize;
	size_t pnIt;

	size_t peSize;
	size_t peIt;



public:
	SFMLGraphVisualizer() {
		// load my font
		this->font.loadFromFile("MAGNETOB.ttf");
	}

	//string getmouse(sf::RenderWindow g) {
	//	return (string) sf::Mouse::getPosition(g);
	//}

	void visualize(DiGraph &g) {

		window.create(sf::VideoMode(1024, 768), "Path Repulsor v2.42");
		sf::Vector2i myMouse;
		sf::Vector2u myRegion = window.getSize();
		cout << myRegion.x << ", " << myRegion.y << endl;
		Liste < Node *> nodes = g.getNodes();
		int redValue = 0;
		int redValueRing = 0;


		while (window.isOpen()) {
			// Process events
			sf::Event event;
			while (window.pollEvent(event)) {
				// Close window : exit
				if (event.type == sf::Event::Closed)
					window.close();
			}

			// Clear screen
			window.clear(sf::Color(31, 31, 31));
			for (unsigned int i = 0; i < nodes.size(); i++) {
				Node * node = nodes.getValueAt(i);

				sf::Color color(255, 145, 0);
				drawNode(*node, color);

				// Ausgehende Kanten einzeichnen
				Liste < Edge *> edges = g.getEdges(node->getKey());

				for (unsigned int j = 0; j < edges.size(); j++) {
					drawEdge(*(edges.getValueAt(j)), sf::Color(114, 111, 107), edges.getValueAt(j)->getWeight(), 1);
				}

			}

			// Mouse
			myMouse = sf::Mouse::getPosition(window); 
			if (redValueRing % 256 == 0) cout << "Mouse: " << myMouse.x << ", " << myMouse.y << endl; //debug

			// non disco mode mutated
#if 1
			// coloring pulse
			redValueRing = (redValueRing + 2 ) % 256;
			redValue = redValueRing;
			if (redValueRing > 127) redValue = 256 - (redValueRing - 127);
			else redValue = redValueRing + 127;


			sf::Color HighlightEdge(redValue, 0, 0);
			for (size_t y = 0; y < pathEdges.size(); y++) {
				drawEdge(*(pathEdges.getValueAt(y)), HighlightEdge, pathEdges.getValueAt(y)->getWeight(), 1);
			}

			sf::Color HighlightNode(redValue, 0, 0);
			// highlights einzeichnen
			for (size_t x = 0; x < pathNodes.size(); x++) {
				Node * node = pathNodes.getValueAt(x);

				drawNode(*node, HighlightNode);
			}

	
			
#endif

#if 0

// this disco is real
			pnIt = pnIt % pnSize;
			peIt = peIt % peSize;

			sf::Color HighlightEdge(165, 0, 0);
			drawEdge(*(pathEdges.getValueAt(peIt)), HighlightEdge, pathEdges.getValueAt(peIt)->getWeight(), 1);
		

			sf::Color HighlightNode(165, 0, 0);
			// highlights einzeichnen
			Node * node = pathNodes.getValueAt(pnIt);
			drawNode(*node, HighlightNode);
			

			std::this_thread::sleep_for(std::chrono::seconds(2));
#endif
			// Update the window
			window.display();
		}
	}

	void highlightPath(Liste<Edge*> path) {
		for (int i = path.size() - 1; i >= 0; i--) {
			pathNodes.append(path[i]->getStartNode());
			pathNodes.append(path[i]->getEndNode());

			pathEdges.append(path[i]);
		}
		//this->pnSize = this->pathNodes.size();
		//this->peSize = this->pathEdges.size();


	}



#if 0
	void highlightPath(Liste<Edge*> path) {

		for (int i = path.size(); i >= 0; i--) {
			if (i == path.size()) {
				// Startnode malen
				drawNode(*path[i]->getStartNode(), sf::Color(255, 0, 0));
			}

			// Edge malen
			drawEdge(*path[i], sf::Color(0, 255, 0), path[i]->getWeight(), 5, 20);

			// Startnode malen
			drawNode(*path[i]->getEndNode(), sf::Color(255, 0, 0));
		}
	}
#endif

	void drawNode(Node &node, sf::Color nodeColor) {

		sf::CircleShape Circle(NODERADIUS);
		Circle.setPosition(node.getPositionX() - NODERADIUS, node.getPositionY() - NODERADIUS);
		Circle.setFillColor(sf::Color(31,31,31));
		Circle.setOutlineColor(nodeColor);
		Circle.setOutlineThickness(2);

		sf::RectangleShape Rectangle(sf::Vector2f(120, 50));
		Rectangle.setPosition(node.getPositionX() - 60, node.getPositionY() - 25);
		Rectangle.setFillColor(sf::Color(31, 31, 31));
		Rectangle.setOutlineColor(nodeColor);
		Rectangle.setOutlineThickness(2);

		window.draw(Circle);
		//window.draw(Rectangle);


		sf::Text Label(node.getKey(), font, 28);
		Label.setPosition(node.getPositionX() - 45 + 40, node.getPositionY() - 25 - 15);
		Label.setFillColor(sf::Color(158, 158, 158));

		window.draw(Label);

	}


	void drawEdge(Edge &edge, sf::Color color, double weight,
		int thickness = 2, int arrowMagnitude = 13) {

		sf::Vector2f p(edge.getStartNode()->getPositionX(), edge.getStartNode()->getPositionY());
		sf::Vector2f q(edge.getEndNode()->getPositionX(), edge.getEndNode()->getPositionY());

		// Berechne den Winkel
		const double PI = 3.141592653;
		double angle = atan2((double)p.y - q.y, (double)p.x - q.x);

		// Berechne verkuerzten Pfeil
		q.x = (int)(q.x + NODERADIUS * cos(angle));
		q.y = (int)(q.y + NODERADIUS * sin(angle));
		p.x = (int)(p.x - NODERADIUS * cos(angle));
		p.y = (int)(p.y - NODERADIUS * sin(angle));

		// sf::Vertex line[2] = { sf::Vertex(sf::Vector2f(p.x, p.y), sf::Color(114,111,107)), sf::Vertex(sf::Vector2f(q.x, q.y), sf::Color(114,111,107)) };
		sf::Vertex line[2] = { sf::Vertex(sf::Vector2f(p.x, p.y), color), sf::Vertex(sf::Vector2f(q.x, q.y), color) };

		// thickness
		window.draw(line, 3, sf::Lines);
		std::stringstream weightstring;
		weightstring << weight;
		sf::Text Labelweight(weightstring.str(), font, 25);
		int size = sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
		Labelweight.setPosition(p.x - (size / 2)* cos(angle) + 10 * sin(angle), p.y - (size / 2)* sin(angle) + 10 * cos(angle));
		Labelweight.setFillColor(color); //sf::Color(255, 145, 0));
		window.draw(Labelweight);

		// Erstes Segment
		p.x = (int)(q.x + arrowMagnitude * cos(angle + PI / 8));
		p.y = (int)(q.y + arrowMagnitude * sin(angle + PI / 8));
		sf::Vertex first[2] = { sf::Vertex(sf::Vector2f(p.x, p.y), color), sf::Vertex(sf::Vector2f(q.x, q.y), color) };
		window.draw(first, 2, sf::Lines);

		// Zweites Segment
		p.x = (int)(q.x + arrowMagnitude * cos(angle - PI / 8));
		p.y = (int)(q.y + arrowMagnitude * sin(angle - PI / 8));
		sf::Vertex second[2] = { sf::Vertex(sf::Vector2f(p.x, p.y), color), sf::Vertex(sf::Vector2f(q.x, q.y), color) };
		window.draw(second, 2, sf::Lines);
	}
};
