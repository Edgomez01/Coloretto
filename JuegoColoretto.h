#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Jugador.h"
#include "Carta.h"

using namespace std;

class JuegoColoretto
{
private:
	vector<Carta> mazoPrincipal;
	vector<vector<Carta>> filasMesa;
	vector<Jugador> jugadores;

	int numeroJugadores;
	int rondaActual;
	bool cartaEspecialRobada;

	void preguntarJugadores();
	void construirMazo();
	void repartirCartaInicial();

	void gestionarRonda();
	void gestionarTurno(Jugador& jugador);

	void robarColocar();
	bool tomarFila(Jugador& jugador, int indiceFila);
	bool verificarFinJuego() const;
	int jugadoresEnJuego() const;

	int leerEntero();

	void imprimirFilasMesa() const;

public:
	JuegoColoretto();
	void iniciarJuego();
	void finDelJuego();

};

