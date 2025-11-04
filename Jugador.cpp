#include "Jugador.h"
#include <algorithm>
#include <sstream>

using namespace std;

Jugador::Jugador(string nombreInicial) :
	nombre(nombreInicial),
	tomoFila(false)
{

}

void Jugador::tomarFila(const vector<Carta>& fila)
{
	for (const auto& cartaOriginal : fila) {
		Carta* nuevaCarta = new Carta(cartaOriginal);
		cartasRecogidas.push(nuevaCarta);
	}
}

int Jugador::calcularPuntos() {
	map<string, int> conteo = contarColores();
	if (conteo.empty()) {
		return 0;
	}

	vector<int> cantidad;
	for (auto const& par : conteo) {
		if (par.first != "Especial") {
			cantidad.push_back(par.second);
		}
	}

	sort(cantidad.rbegin(), cantidad.rend());

	int puntos_positivos = 0;
	int puntos_negativos = 0;

	for (size_t i = 0; i < cantidad.size(); ++i) {
		int cant = cantidad[i];

		if (i < 3) {
			puntos_positivos += puntosPorCant(cant);
		}
		else {
			puntos_negativos += puntosPorCant(cant);
		}

	}
	return puntos_positivos - puntos_negativos;
}

bool Jugador::yaTomoFila() const
{
	return tomoFila;
}

void Jugador::tomarFilaTrue() {
	tomoFila = true;
}

void Jugador::restablecerRonda()
{
	tomoFila = false;
}

string Jugador::getNombre() const
{
	return nombre;
}

int Jugador::getCantidadCartas() const
{
	return cartasRecogidas.size();
}

map<string,int> Jugador::contarColores() 
{
	map<string, int> conteo;
	Carta* cartaPtr = nullptr;

	while (!cartasRecogidas.empty()) {
		cartaPtr = cartasRecogidas.pop();
		if (cartaPtr) {
			conteo[cartaPtr->getColorString()]++;
			delete cartaPtr;
			cartaPtr = nullptr;
		}
	}
	return conteo;
}

int Jugador::puntosPorCant(int cantidad) const
{
	switch (cantidad) {
		case 0: return 0;
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		case 5: return 15;
		default: return 21;
	}
}

void Jugador::imprimirCartasRecogidas() const {
	cout << "\n--- COLECCION DE CARTAS DE "<< nombre <<" ---" << endl;
	if (cartasRecogidas.empty()) {
		cout << "[ COLECCION VACIA ]" << endl;
		return;
	}
	vector<Carta*> coleccion = cartasRecogidas.getCartas();

	cout << nombre << " Tiene un total de " << cartasRecogidas.size() << " carta" << endl;
	for (const auto& cartaPtr : coleccion) {
		if (cartaPtr) {
			if (cartaPtr->ultimaRonda) {
				cout << "[E]" << endl;
				continue;
			}

			cout << cartaPtr->getAnsiColorCode()
				<< "[#]"
				<< cartaPtr->getAnsiRestCode()
				<< " ";
		}
	}
	cout << endl;
}
