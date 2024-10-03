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

int main()
{
    // Opciones de Inicio para la consola
    setWindowSize(160, 50);
    lockConsole();
    
    // Start Menu
    int defaultS[2] = { 1,1 };
    printColor(menuDefs::background, color::dBlack, color::bBlack);  // Background

    printMainMenu();

    int inputSelection{ 0 };
    while (1)
    {
        switch (inputSelection = setSelection<7, 3>(selectionLists::mainMenuOptions, selectionMaps::mainMenuMap))
        {
        case 0: // ************* OPCION 1 : GESTION DE COMPUTADORAS

            clearMainWindow();      // Funcion para limpiar la pantalla
            mainGestionComputadoras();  // FUNCION PRINCIPAL
            _getch();               // Pausar la Consola
            printMainMenu();        // Reimprimir toda la ventana principal

            break;
        case 1: // ************* OPCION 2 : GESTION DE SESIONES

            clearMainWindow();      // Funcion para limpiar la pantalla
            mainGestionSesiones();  // FUNCION PRINCIPAL
            _getch();               // Pausar la Consola
            printMainMenu();        // Reimprimir toda la ventana principal

            break;
        case 2: // ************* OPCION 2 : GESTION DE SESIONES

            clearMainWindow();      // Funcion para limpiar la pantalla
            mainGestionClientes();  // FUNCION PRINCIPAL
            _getch();               // Pausar la Consola
            printMainMenu();        // Reimprimir toda la ventana principal

            break;
        case 3: // ************* OPCION 4 : FACTURACION

            clearMainWindow();      // Funcion para limpiar la pantalla
            mainFacturacion();  // FUNCION PRINCIPAL
            _getch();               // Pausar la Consola
            printMainMenu();        // Reimprimir toda la ventana principal

            break;
        case 4: // ************* OPCION 5 : RESERVAS

            clearMainWindow();      // Funcion para limpiar la pantalla
            mainReservas();  // FUNCION PRINCIPAL
            printMainMenu();        // Reimprimir toda la ventana principal

            break;
        case 5: // ************* OPCION 6 : REPORTES

            clearMainWindow();      // Funcion para limpiar la pantalla
            mainReportes();  // FUNCION PRINCIPAL
            _getch();               // Pausar la Consola
            printMainMenu();        // Reimprimir toda la ventana principal

            break;
        case 6: // ************* OPCION 7 : SALIR DEL PROGRAMA
            clearMainWindow();
            printCOORD("Gracias por usar el programa", { 67,23 });
            printCOORD("Pulse cualquier tecla para continuar...", { 62,24 });
            _getch();
            return 0;
        }
    }

}