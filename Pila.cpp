#include "Pila.h"
#include <vector>

using namespace std;

   // La pila usa una lista enlazada manual, donde cada Carta tiene un puntero a la siguiente (liga).
  //Esto permite agregar y quitar elementos con eficiencia, sin mover memoria ni reubicar datos.

void Pila::push(Carta* carta) {  // INSERTA una carta arriba de la pila.
	if (carta == nullptr) {     // Verificar si la carta es nula
		cerr << "Error: No se puede apilar una carta nula." << endl; // Manejo de error simple
		return;
	}
	carta->liga = head;  // Apuntar la nueva carta al actual head
	head = carta;       // Actualizar head para que apunte a la nueva carta - la nueva carta es la cabeza de la pila
	count++;           // Incrementar el contador de cartas
}

Carta* Pila::pop() {     // SACA UNA CARTA DE ARRIBA - ELIMINA
	if (empty()) {      //Verifica si la pila está vacía; si lo está, lanza una excepción (underflow).
		throw out_of_range("Error: Pila vac�a (Underflow)"); 
	}
	Carta* carta_retornada = head; 	// Guardar la carta en la cima de la pila
	head = head->liga;             // Actualizar head para que apunte a la siguiente carta
	carta_retornada->liga = nullptr; // Desvincular la carta retornada de la pila
	count--;   
	return carta_retornada;          // Devolver la carta removida
}

Carta* Pila::top() {         // LECTURA - CONSULTA CARTA SUPERIOR - Devuelve el elemento superior de la pila sin eliminarlo.
	if (empty()) {    // Verificar si la pila es vacia - Si está vacía, devuelve nullptr.
		return nullptr;
	}
	return head;
}

bool Pila::empty() const { // VERIFICA - Devuelve true si la pila no tiene elementos (es decir, si head es nullptr).
	return head == nullptr;
}

Pila::~Pila() {         // DESTRUCTOR para liberar la memoria de las cartas en la pila. - LIMPIEZA de la Pila
	Carta* aux = head; // Recorre todas las cartas desde head - Libera la memoria (delete) de cada una.
	Carta* next;

	while (aux != nullptr) {
		next = aux->liga;
		delete aux;
		aux = next;
	}
	head = nullptr; // Limpia head y count.
	count = 0;
}

vector<Carta*> Pila::getCartas() const { // DEVUELVE TODAS LAS CARTAS - Crea y devuelve un vector con todas las cartas de la pila, desde la superior (head) hasta la inferior.
	vector<Carta*> cartas;              // Esto es útil para recorrer o mostrar las cartas en interfaz gráfica o consola.
	Carta* actual = head;

	while (actual != nullptr) {
		cartas.push_back(actual);
		actual = actual->liga;
	}

	return cartas;
} 	
	