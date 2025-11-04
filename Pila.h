#pragma once
#include "Carta.h"
#include <vector>

using namespace std;

class Pila
{
private:
	Carta* head;
	int count;

public:
	Pila() : head(nullptr), count(0) {}
	//Pila(const Pila& otraPila);
	~Pila();

	void push(Carta* carta);
	Carta* pop();
	Carta* top();
	bool empty() const;

	int size() const {
		return count;
	}

	vector<Carta*> getCartas() const;
};

