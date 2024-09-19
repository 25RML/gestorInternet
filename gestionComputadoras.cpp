// Includes
#include <iostream>

#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()

// *************************************** Funciones ***************************************

void mainGestionComputadoras()
{
	gotoCOORD(g_mainWindowStartPOS); // Version alterna del gotoxy
	std::cout << "Hello World!";
}