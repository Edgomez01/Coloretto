#pragma once
#include <string>
#include <iostream>

using namespace std;

class Carta
{
public:
	enum class Color { AZUL, VERDE, NARANJA, AMARILLO, ROSA, MARRON, GRIS, NA };
	
	Color color;
	bool ultimaRonda;
	Carta* liga; //puntero al siguiente elemento

	Carta(const Carta& otra);

	Carta(Color color, bool ultimaRonda);

	string getColorString() const;
	string getAnsiColorCode() const;
	string getAnsiRestCode() const { return "\033[0m"; }
};

