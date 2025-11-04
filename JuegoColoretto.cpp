
#include "JuegoColoretto.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

JuegoColoretto::JuegoColoretto() : numeroJugadores(0), rondaActual(1), cartaEspecialRobada(false)
{

}

void JuegoColoretto::iniciarJuego() {
	cout << "--- ¡Bienvenido al juego Coloreto! ---" << endl;

	preguntarJugadores();
	construirMazo();
	repartirCartaInicial();

	bool finJuego = false;
	while (!finJuego) {
		cout << "\n--- COMIENZA RONDA " << rondaActual << " ---" << endl;
		gestionarRonda();

		if (verificarFinJuego()) {
			finJuego = true;
		}
		else {
			for (auto& jugador : jugadores) {
				jugador.restablecerRonda();
			}
			rondaActual++;
		}
	}
	cout << "\n--- FIN DEL JUEGO ---" << endl;
	finDelJuego();
}

void JuegoColoretto::gestionarRonda() {
	int jugadoresRestantes = jugadoresEnJuego();

	while (jugadoresRestantes > 0) {
		for (int i = 0; i < numeroJugadores; ++i) {
			Jugador& jugadorActual = jugadores[i];

			if (jugadorActual.yaTomoFila()) {
				continue;
			}
			
			cout << "\nTurno de " << jugadorActual.getNombre() << endl;
			gestionarTurno(jugadorActual);

			if (jugadorActual.yaTomoFila()) {
				jugadoresRestantes--;
			}
		}
	}

	for (auto& fila : filasMesa) {
		fila.clear();
	}
}

void JuegoColoretto::gestionarTurno(Jugador& jugador) {

	bool puedeRobar = any_of(filasMesa.begin(), filasMesa.end(), [](const auto& fila) {return fila.size() < 3;  });

	int accion;

	jugador.imprimirCartasRecogidas();

	if (!puedeRobar) {
		cout << "\nLas filas en la mesa estan llenas, no puedes robar mas cartas, debes tomar una fila de la mesa." << endl;
		accion = 1;
	}
	else {
		cout << "\nIngrese la acción a realizar:\n0. Robar carta del Mazo y poner en una fila de la mesa.\n1. Tomar fila de la mesa." << endl;
		accion = leerEntero();
	}


	if (puedeRobar && accion == 0) {
		robarColocar();
	}
	else if(accion == 1) {
		int filaElegida=-1;
		imprimirFilasMesa();
		while (filaElegida < 0 || filaElegida >= numeroJugadores) {

			cout << "\nIngrese cuál fila desea tomar de 1 a " << numeroJugadores << endl;
			filaElegida = leerEntero();
			filaElegida--;
		}
		if (tomarFila(jugador, filaElegida)) {
			return;
		}
		else {
			gestionarTurno(jugador);
		}
		
	} else {
		cout << "¡Opción no valida!" << endl;
		gestionarTurno(jugador);
	}
}

void JuegoColoretto::robarColocar() {
	if (mazoPrincipal.empty()) {
		cout << "¡El Mazo esta vacio!, No puedes robar" << endl;
		return;
	}

	Carta cartaRobada = mazoPrincipal.back();
	mazoPrincipal.pop_back();

	if (cartaRobada.ultimaRonda) {
		cartaEspecialRobada = true;
		cout << "\n¡CARTA DE ÚLTIMA RONDA ROBADA! El juego terminará al final de esta ronda. " << endl;
		return;
	}
	
	int indiceFila = -1;
	bool filaValida = false;

	while (!filaValida) {
		cout << "Carta Robada: "
			<< cartaRobada.getAnsiColorCode()
			<< cartaRobada.getColorString() 
			<< cartaRobada.getAnsiRestCode()
			<< endl;
		cout << "Filas disponibles (1 a " << numeroJugadores << ")" << endl;
		imprimirFilasMesa();

		cout << "Ingrese en cuál fila desea añadir la carta: " << endl;
		indiceFila = leerEntero();
		indiceFila--;
		if (indiceFila < 0 || indiceFila >= filasMesa.size()) {
			cout << "¡El número de fila debe ser entre 1 y " << numeroJugadores << "!" << endl;
			continue;
		}

		if (filasMesa[indiceFila].size() >= 3) {
			cout << "¡La fila " << indiceFila + 1 << "ya esta lleno!" << endl;
			continue;
		}

		filaValida = true;
	}

	filasMesa[indiceFila].push_back(cartaRobada);
	cout << "Carta colocada correctamente" << endl;

}

bool JuegoColoretto::tomarFila(Jugador& jugador, int indiceFila) {

	if (indiceFila < 0 || indiceFila >= filasMesa.size()) {
		cout << "La fila no existe" << endl;
		return false;
	}
	if (filasMesa[indiceFila].empty()) {
		cout << "La fila esta vacia, Selecciona otra" << endl;
		return false;
	}

	vector<Carta> filaTomada = filasMesa[indiceFila];
	jugador.tomarFila(filaTomada);
	jugador.tomarFilaTrue();
	filasMesa[indiceFila].clear();

	cout << jugador.getNombre() << " tomó las cartas de la fila " << indiceFila + 1 << "." << endl;
	return true;
}

void JuegoColoretto::preguntarJugadores() {
	int numJugadores;
	do {
		cout << "Ingrese la cantidad de jugadores (Entre 3 y 5 Jugadores): " << endl;
		numJugadores = leerEntero();
	} while (numJugadores < 3 || numJugadores > 5);

	numeroJugadores = numJugadores;
	filasMesa.resize(numJugadores);


	for (int i = 0; i < numeroJugadores; ++i) {
		string nombre;
		cout << "Ingrese el nombre del jugador #" << i + 1 << ": " << endl;

		getline(cin, nombre);

		if (nombre.empty()) {
			nombre = "Jugador " + to_string(i + 1);
			cout << "No se ingresó nombre, se usará " << nombre << endl;
		}

		jugadores.emplace_back(nombre);
	}
}

void JuegoColoretto::construirMazo() {
	vector<Carta::Color> colores = {
		Carta::Color::AZUL, Carta::Color::VERDE, Carta::Color::NARANJA, Carta::Color::AMARILLO, Carta::Color::ROSA, Carta::Color::MARRON, Carta::Color::GRIS
	};

	for (auto color : colores) {
		for (int i = 0; i < 9; i++) {
			mazoPrincipal.emplace_back(color, false);
		}
	}

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(mazoPrincipal.begin(), mazoPrincipal.end(), default_random_engine(seed));

	size_t posicionInsercion = mazoPrincipal.size() - 15;

	mazoPrincipal.insert(mazoPrincipal.begin() + posicionInsercion, Carta(Carta::Color::NA, true));

}

void JuegoColoretto::repartirCartaInicial() {
	vector<Carta::Color> coloresUsados;

	if (mazoPrincipal.size() < numeroJugadores) {
		cout << "El mazo es insuficiente para el reparto inicial" << endl;
		return;
	}

	cout << "\n--- REPARTO DE CARTAS INICIALES ---" << endl;

	for (int i = 0; i < numeroJugadores; ++i) {
		bool cartaEncontrada = false;
		for (auto it = mazoPrincipal.begin(); it != mazoPrincipal.end(); ++it) {
			if (it->ultimaRonda) continue;

			bool colorRepetido = false;
			for (const auto& colorUsado : coloresUsados) {
				if (it->color == colorUsado) {
					colorRepetido = true;
					break;
				}
			}

			if (!colorRepetido) {
				Carta cartaRepartida = *it;

				jugadores[i].tomarFila({ cartaRepartida });
				coloresUsados.push_back(cartaRepartida.color);

				mazoPrincipal.erase(it);

				cout << jugadores[i].getNombre() << " recibe: "
					<< cartaRepartida.getAnsiColorCode()
					<< cartaRepartida.getColorString()
					<< cartaRepartida.getAnsiRestCode() << std::endl;

				cartaEncontrada = true;
				break;
			}
		}

		if (!cartaEncontrada) {
			cout << "No se pudo asignar carta de color unico a" << jugadores[i].getNombre() << endl;
		}
	}
}

bool JuegoColoretto::verificarFinJuego() const {
	return cartaEspecialRobada || mazoPrincipal.empty();
}

int JuegoColoretto::jugadoresEnJuego() const {
	int activos = 0;
	for (const auto& jugador : jugadores) {
		if (!jugador.yaTomoFila()) {
			activos++;
		}
	}
	return activos;
}

void JuegoColoretto::finDelJuego() {
	cout << "n--- PUNTUACIONES FINALES --" << endl;
	int puntuacionMaxima = -9999;
	string ganador = "";

	for (auto& jugador : jugadores) {
		int puntuacionFinal = jugador.calcularPuntos();
		cout << jugador.getNombre() << " ha hecho " << puntuacionFinal << " puntos " << endl;

		if (puntuacionFinal > puntuacionMaxima) {
			puntuacionMaxima = puntuacionFinal;
			ganador = jugador.getNombre();
		}
	}

	cout << "\n\n¡El ganador del juego es " << ganador << " con " << puntuacionMaxima << " Puntos!" << endl;
}

int JuegoColoretto::leerEntero() {
	int valor;
	while (true) {
		if (cin >> valor) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return valor;
		}

		cout << "Entrada no valida. por favor, ingresa solo números";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	}

void JuegoColoretto::imprimirFilasMesa() const {
	cout << "\n--- FILAS EN LA MESA ---" << endl;

	for (size_t i = 0; i < filasMesa.size(); ++i) {
		cout << "Fila " << i + 1 << " (" << filasMesa[i].size() << " cartas): ";
		
		if (filasMesa[i].empty()) {
			cout << "[ VACIA ]" << endl;
			continue;
		}

		for (const auto& carta : filasMesa[i]) {
			cout << carta.getAnsiColorCode()
				<< "[#]"
				<< carta.getAnsiRestCode()
				<< " ";
		}

		int cartas_faltantes = 3 - filasMesa[i].size();
		for (int j = 0; j < cartas_faltantes; ++j) {
			std::cout << "[   ]"; 
		}

		cout << endl;
	}