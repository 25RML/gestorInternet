// Includes
#include <iostream>

#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "tempFile.h"

// *************************************** Funciones ***************************************

void mainReservas()
{
	//doubleList<Computadora>* listTest{ createEntry(Computadora{1,0.6f,{"a","b","c","d"},"bien",20}) };
	doubleList<Computadora>* computadorasMain{};
	generateComputersList(computadorasMain, 10);


	printColor(menuDefs::background, color::dBlack, color::bBlack);  // Reset Background
	printWindow(25, 16, {7,4},color::dBlack,color::dYellow); // Print Window
	printButtons<3,3>(selectionLists::reservasOptions);
	// Print Mockup Window (sort of)
	printWindow(110, 40, { 39,4 }, color::dBlack, color::dBlue);
	printWindow(60, 2, { 65,3 }, color::bAqua, color::bBlue);
	gotoCOORD({ 78,4 }); printColor("\033[4mGESTOR DE RESERVAS DE COMPUTADORAS\033[0m",color::dBlack, color::bAqua);

	gotoCOORD({ 0,0 }); // Estetico solamente, volver a 0,0

	int inputSelection{ 0 };
	bool continueSelection{ true };
	while (continueSelection)
	{
		switch (inputSelection = setSelection<3, 3>(selectionLists::reservasOptions, selectionMaps::reportesMap))
		{
		case 0:
			gotoCOORD({ 74,8 }); std::cout << computadorasMain->size()<< " "<<computadorasMain->getAt(3)->data.modificadorDePrecio;
			break;
		case 1:

			break;
		case 2:
			continueSelection = false;
			break;
		}
	}

	// END


	computadorasMain->deleteAll();
	printColor(menuDefs::background, color::dBlack, color::bBlack);  // Reset Background
}