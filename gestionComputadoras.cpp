// Includes
#include <iostream>

#include "global.h"
#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "gestionComputadoras.h"

// *************************************** Funciones ***************************************

void mainGestionComputadoras()
{
	gotoCOORD({ 0,0 });
	// Imprimir Menus
	printColor(menuDefs::background, color::dBlack, color::bBlack);  // Reset Background
	printWindow(100, 35, { 6,3 }, color::dBlack, color::dGreen); // Print Window
	printWindow(45, 26, { 110,8 }, color::dBlack, color::dBlue);
	printWindow(80, 4, { 16,41 }, color::dBlack, color::dYellow);
	printWindow(64, 2, { 22,2 }, color::bGreen, color::dGreen);
	gotoCOORD({ 44,3 }); printColor("\033[4mGESTOR DE COMPUTADORAS\033[0m", color::dBlack, color::bGreen);
	
	gotoCOORD({ 0,0 }); // Estetico solamente, volver a 0,0
	int inputSelection{ 0 };
	bool continueSelection{ true };
	while (continueSelection)
	{
		printRectangle({ 7,6 }, 98, 32, color::dBlack);

		selectionMaps::g_operacionesGestionComputadorasMap.printAll();
		switch (inputSelection = selectionMaps::g_operacionesGestionComputadorasMap.startSelection(true))
		{
		case 1:
		{
			printFormat(formattedText::Elements::computer, { 10,17 }, color::dGreen, color::dBlack);
			printRectangle({ 33,8 }, 1, 29, color::dGreen, '#');
			printFormat(formattedText::Elements::addComputer, { 49,9 }, color::dBlack, color::dGreen);
			// Input Boxes
			static int globalComputerID{ 0 };
			++globalComputerID;
			bool repeat{ false };

			do
			{
				if (repeat) printRectangle({ 34,13 }, 66, 30, color::dBlack);
				
				gotoCOORD({ 37,14 }); printColor("- ID : ", color::bGreen); std::cout << globalComputerID;
				gotoCOORD({ 37,16 }); printColor("- Modificador de Precio : ", color::bGreen); std::string s_modPrecio{ getInputBox({63,16},8,true) };
				gotoCOORD({ 37,18 }); printColor("- Componentes : ", color::bGreen); std::string s_componentes[4]{};
				gotoCOORD({ 39,20 }); printColor("-> Procesador : ", color::bGreen); s_componentes[0] = getInputBox({ 63,20 }, 20);
				gotoCOORD({ 39,22 }); printColor("-> Memoria : ", color::bGreen); s_componentes[1] = getInputBox({ 63,22 }, 20);
				gotoCOORD({ 39,24 }); printColor("-> Tarjeta Grafica : ", color::bGreen); s_componentes[2] = getInputBox({ 63,24 }, 20);
				gotoCOORD({ 39,26 }); printColor("-> Pantalla : ", color::bGreen); s_componentes[3] = getInputBox({ 63,26 }, 20);

				selectionMaps::g_confirmAgregarComputadorasMap.printAll();
				switch (selectionMaps::g_confirmAgregarComputadorasMap.startSelection())
				{
				case 1: // Confirmar
					repeat = false;
					g_registroComputadoras.append(g_registroComputadoras.createEntry({
						globalComputerID,
						std::stof(s_modPrecio),
						{s_componentes[0],s_componentes[1],s_componentes[2],s_componentes[3]},
						0,
						0,
						{}
						}));
					break;
				case 2: // Reintentar
					repeat = true;
					break;
				case 3: // Salir
					repeat = false;
					--globalComputerID;
					break;
				}
			} while (repeat);
		}
		break;
		case 2:
		do
		{
			printRectangle({ 111,9 }, 43, 24, color::dBlack);

			int idSelector{ selectComputer(g_registroComputadoras,{10,8},8,4) };
			if (!idSelector) break;
			// Computer Info & Operations
			printFormat(formattedText::Elements::computerInfo, { 112,9 }, color::dBlack, color::dBlue);
			DoubleList<Computadora>::Node* target{ g_registroComputadoras.getAt(idSelector - 1) };
			mostrarInformacionComputadora(target, { 113,13 });
			gotoCOORD({ 111,23 }); printColor(std::string(43, '#'), color::bBlue, color::dBlack);
			// Elegir entre eliminar o volver al menu
			do
			{
				//printRectangle({ 104,24 }, 44, 20, color::dBlack);
				selectionMaps::g_operacionesComputadorasMap.printAll();
				int deleteQuestion = selectionMaps::g_operacionesComputadorasMap.startSelection(true);
				if (deleteQuestion == 2) break;
				// Delete
				g_registroComputadoras.deleteOnly(idSelector - 1);
				break;

			} while (1);

		} while (1);
		break;
		case 3:
			continueSelection = false;
			break;
		}
	}

	gotoCOORD({ 0,0 });
	printColor(menuDefs::background, color::dBlack, color::bBlack);
}