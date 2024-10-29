// Includes
#include <iostream>

#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()

// *************************************** Funciones ***************************************

void mainReportes()
{
	gotoCOORD(Windows::mainWindowStartPOS); // Version alterna del gotoxy
	std::cout << "Hello World!";
}