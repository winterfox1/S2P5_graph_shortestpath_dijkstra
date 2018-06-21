#pragma once
#include "stdafx.h"

class QueueException {
public:
	QueueException(int error);
};

QueueException::QueueException(int error) {
	switch (error) {
	case 1:
		cout << "ERROR #" << error << " : Queue ist leer!" << endl;
		break;

	case 2:
		cout << "ERROR #" << error << " : Element nicht gefunden!" << endl;
		break;

	case 3:
		cout << "ERROR #" << error << " : next Element nicht vorhanden! (Queue leer?)" << endl;
		break;

	}
}
