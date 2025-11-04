#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Carta.h"
#include "Pila.h"

using namespace std;

class Jugador
{
private:
	string nombre;
	Pila cartasRecogidas;
	bool tomoFila;

	map<string, int> contarColores();
	int puntosPorCant(int cantidad) const;

public:
	Jugador(string nombre);

	void tomarFila(const vector<Carta>& fila);
	
	int calcularPuntos();

	bool yaTomoFila() const;

	void tomarFilaTrue();

	void restablecerRonda();

	string getNombre() const;
	int getCantidadCartas() const;

	void imprimirCartasRecogidas() const;


};

