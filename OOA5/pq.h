#pragma once
#include "stdafx.h"
#include "pq.h"
#include <Windows.h>
#include <time.h>
#include "exeption.h"


using namespace std;

template <typename V>
class pqentry {
public:
	float priority;
	V value;

	pqentry * next;

	pqentry(float priority, V value);
	~pqentry();
};

template <typename V>
pqentry<V>::pqentry(float priority, V value) {
	this->priority = priority;
	this->value = value;
	this->next = nullptr;
//	cout << "Eintrag mit Prioritaet " << fixed << setprecision(2) << priority << " und Value " << value << " wurde erstellt" << endl;
}

template <typename V>
pqentry<V>::~pqentry() {
	cout << "Eintrag wurde geloescht" << endl;
}

template <typename V>
class priorityqueue {
public:
	pqentry<V> * first;

	void insert(float priority, V value);
	V extractMin(void);
	void decreaseKey(V value, float prio);
	void remove(V value);
	void qPrint();

	priorityqueue();
	~priorityqueue();
};

template <typename V>
priorityqueue<V>::priorityqueue() {
	this->first = NULL;
	cout << "Queue wurde erstellt" << endl;
}

template <typename V>
priorityqueue<V>::~priorityqueue() {
	cout << "Queue wurde geloescht!" << endl;
}

template <typename V>
void priorityqueue<V>::insert(float priority, V value) {
	pqentry<V> *entry = new pqentry<V>(priority, value);

	if (first == NULL) {
		this->first = entry;
		cout << "Element wurde in Queue eingefuegt!" << endl << endl;
		return;
	}

	pqentry<V> *curr = this->first;   // curr = derzeitige Stelle des Pakets
	pqentry<V> *next = curr->next;  // = stelle nach curr

	do {
		if (next == NULL) {
			break;
		}

		if (curr == this->first && entry->priority < curr->priority) {
			this->first = entry;
			entry->next = curr;
			cout << "Element wurde am Anfang der Queue eingefuegt!" << endl << endl;
			return;
		}

		else if (entry->priority < curr->next->priority) {	// prüfen ob entry zwischen curr und next einsortiert werden muss
			curr->next = entry;	//verkette curr mit entry
			entry->next = next;
			cout << "Element wurde sortiert in Queue eingefuegt!" << endl << endl;
			return;
		}

		curr = next;
		next = curr->next;

	} while (next != NULL);
	curr->next = entry;
	cout << "Element wurde ans Ende der Queue eingefuegt!" << endl << endl;
	return;
}

template <typename V>
V priorityqueue<V>::extractMin(void) {

	if (this->first == NULL) {
		throw QueueException(1);
	}


	cout << "Entferne Element mit der hoechsten Prioritaet" << endl;
	pqentry<V> *tmp = this->first;

	V value = this->first->value;
	this->first = first->next;
	delete(tmp);

	return value;
}

template <typename V>
void priorityqueue<V>::decreaseKey(V value, float priority) {

	pqentry<V> *curr = this->first; // curr = erstes element
	if (curr == NULL) {
		throw QueueException(3);
	}
	pqentry<V> *next = curr->next;
	// sonderfall value steckt im ersten element
	// cout << "Suche nach Element: " << value << " und aendere Prio auf " << priority << endl;
	if (curr == this->first && curr->value == value) {
		pqentry<V> *tmp = curr;									//temp pointer anlegen
		curr->priority = priority;								//priowert ändern
		this->first = curr->next;								//verkettung aufheben
		priorityqueue::insert(tmp->priority, tmp->value); 		//paket neu einsortieren
		return;
	}

	if (next == NULL) {
		throw QueueException(2);
	}

	while (next->value != value) {
		curr = next;
		next = next->next;

	}

	pqentry<V> *tmp = next;								//temp pointer anlegen
	next->priority = priority;							//priowert ändern
	curr->next = next->next;							//verkettung aufheben
	priorityqueue::insert(tmp->priority, tmp->value);	//paket neu einsortieren
}


template <typename V>
void priorityqueue<V>::remove(V value) {

	pqentry<V> *curr = this->first;
	pqentry<V> *next = curr->next;
	if (curr->value == value) {
		delete (curr);
		this->first = next;
		return;
	}

	do {
		curr = next;
		next = curr->next;
		if (next == NULL) {
			printf("\nElement entweder schon geloescht oder nicht gefunden!\n");
			return;
		}
	} while (next->value != value);

	curr->next = next->next;
	cout << "Entferne Element " << value << next->priority << endl;
	delete next;
}

template <typename V>
void priorityqueue<V>::qPrint() {
	pqentry<V> *curr = this->first;
	pqentry<V> *next = curr->next;

	int i = 1;
	cout << endl << "Current Queue: " << endl;

	do {
		cout << "Entry " << i++ << ":" << curr->value << " Priority: " << curr->priority << endl;
		if (next == NULL) {
			return;
		}
		else {
			curr = next;
			next = curr->next;
		}
	} while (1);
}

char * randomString(int size) {
	int i;
	char * str = (char *)malloc((size + 1) * sizeof(char));
	for (i = 0; i < size; ++i) {
		str[i] = (rand() % 26);
	}
	str[size] = '\0';
	return str;

}
