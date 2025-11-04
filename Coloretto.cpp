// Coloretto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "JuegoColoretto.h"

using namespace std;

int main()
{
    JuegoColoretto juego;
    juego.iniciarJuego();
    cout << "¡El Juego ha finalizado!" << endl;
    return 0;
}

