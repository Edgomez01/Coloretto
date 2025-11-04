#include "Pila.h"
#include <vector>

using namespace std;



void Pila::push(Carta* carta) {
	if (carta == nullptr) {
		cerr << "Error: No se puede apilar una carta nula." << endl;
		return;
	}
	carta->liga = head;
	head = carta;
	count++;
}

Carta* Pila::pop() {
	if (empty()) {
		throw out_of_range("Error: Pila vacía (Underflow)");
	}
	Carta* carta_retornada = head;
	head = head->liga;
	carta_retornada->liga = nullptr;
	count--;
	return carta_retornada;
}

Carta* Pila::top() {
	if (empty()) {
		return nullptr;
	}
	return head;
}

bool Pila::empty() const {
	return head == nullptr;
}

Pila::~Pila() {
	Carta* aux = head;
	Carta* next;

	while (aux != nullptr) {
		next = aux->liga;
		delete aux;
		aux = next;
	}
	head = nullptr;
	count = 0;
}

vector<Carta*> Pila::getCartas() const {
	vector<Carta*> cartas;
	Carta* actual = head;

	while (actual != nullptr) {
		cartas.push_back(actual);
		actual = actual->liga;
	}

	return cartas;
}