#include "Carta.h"

using namespace std;

Carta::Carta(Color colorInicial, bool ultimaRonda):
	color(colorInicial), ultimaRonda(ultimaRonda), liga(nullptr)
{

}

Carta::Carta(const Carta& otra) :
	color(otra.color),
	ultimaRonda(otra.ultimaRonda),
	liga(nullptr) {

}

string Carta::getColorString() const
{
	switch (color) {
		case Color::AZUL: return "Azul";
		case Color::VERDE: return "Verde";
		case Color::NARANJA: return "Naranja";
		case Color::AMARILLO: return "Amarillo";
		case Color::ROSA: return "Rosa";
		case Color::MARRON: return "Marron";
		case Color::GRIS: return "Gris";
		default: return "ESPECIAL";
	}
}

string Carta::getAnsiColorCode() const {
	switch (color) {
	case Color::AZUL: return "\033[34m";
	case Color::VERDE: return "\033[32m";
	case Color::NARANJA: return "\033[33m"; // Amarillo para Naranja
	case Color::AMARILLO: return "\033[93m"; // Amarillo Brillante
	case Color::ROSA: return "\033[35m";
	case Color::MARRON: return "\033[33m"; // Amarillo Oscuro/Marrón
	case Color::GRIS: return "\033[90m";
	default: return "\033[0m"; // Sin color para la carta especial (NA)
	}
}