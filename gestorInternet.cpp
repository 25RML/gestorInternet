#include <iostream>

#define _WIN32_WINNT 0x0500  // Tiene que ir antes del windows.h
#include <windows.h>
    
#include "interface.h"
#include "gestionComputadoras.h"
#include "gestionSesiones.h"
#include "gestionClientes.h"
#include "facturacion.h"
#include "reservas.h"
#include "reportes.h"
#include "global.h"

// ************************************************** GLOBAL VARIABLES **************************************************
DoubleList<Computadora> g_registroComputadoras{};
SingleList<Sesion> g_registroSesiones;
double g_mainTarifa{ 1.0 };   // TARIFA GLOBAL, IMPORTANTISIMO
// ********************************************* FUNCTIONS ********************************************* 
int main()
{
    // Opciones de Inicio para la consola
    setWindowSize(160, 50);
    lockConsole();
    system("CLS");

    // Cardar Datos de las Computadoras
    cargarDatos("computadoras.txt");
    // Start Menu

    printColor(menuDefs::background, color::dBlack, color::bBlack);  // Background
    printMainMenu();

    int inputSelection{ 0 };
    while (1)
    {
        switch (inputSelection = selectionMaps::g_mainMenuMap.startSelection())
        //switch (inputSelection = setSelection<7, 3>(selectionLists::mainMenuOptions, selectionMaps::mainMenuMap))
        {
        case 1: // ************* OPCION 1 : GESTION DE COMPUTADORAS

            clearMainWindow();      // Funcion para limpiar la pantalla
            mainGestionComputadoras();  // FUNCION PRINCIPAL
            printMainMenu();        // Reimprimir toda la ventana principal

            break;
  
        case 2: // ************* OPCION 3 : SIMULACIÓN DE SESIONES  DICE GESTIONCLIENTES PERO EN REALIDAD ES UN SIMULADOR

            clearMainWindow();      // Funcion para limpiar la pantalla
            mainGestionClientes();  // FUNCION PRINCIPAL
            printMainMenu();        // Reimprimir toda la ventana principal

            break;
      
         
        case 3: // ************* OPCION 5 : RESERVAS

            clearMainWindow();      // Funcion para limpiar la pantalla
            mainReservas();         // FUNCION PRINCIPAL
            printMainMenu();        // Reimprimir toda la ventana principal

            break;
        case 4: // ************* OPCION 6 : REPORTES

            clearMainWindow();      // Funcion para limpiar la pantalla
            mainReportes();         // FUNCION PRINCIPAL
            printMainMenu();        // Reimprimir toda la ventana principal

            break;
        case 5: // ************* OPCION 7 : SALIR DEL PROGRAMA
            clearMainWindow();
            printCOORD("Gracias por usar el programa", { 67,23 });
            printCOORD("Pulse cualquier tecla para continuar...", { 62,24 });

            guardarDatos("computadoras.txt");   // Guardando los datos al salir del programa

            _getch();
            return 0;
        }
        
    }

}