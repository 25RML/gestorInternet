// Includes
#include <iostream>

#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "tempFile.h"
#include "global.h"

// *************************************** Funciones ***************************************

void mainReportes()
{
    gotoCOORD({ 0,0 });
    // Imprimir Menus
    printColor(menuDefs::background, color::dBlack, color::bBlack);     // Reset Background
    printWindow(27, 18, { 7,13 }, color::dBlack, color::dPurple);       // Imprimir ventana de Operaciones
    printWindow(100, 35, { 48,6 }, color::dBlack, color::bYellow);      // Imprimir ventana de vista

    printWindow(64, 2, { 68,5 }, color::bYellow, color::dYellow);       // Ventana de Titulo
    gotoCOORD({ 91,6 }); printColor("\033[4mCREACION DE REPORTES\033[0m", color::dBlack, color::bYellow);   // Titulo
	
    gotoCOORD({ 0,0 }); // Estetico solamente, volver a 0,0
    int inputSelection{ 0 };
    bool continueSelection{ true };
    while (continueSelection)
    {
        selectionMaps::g_reportesMap.printAll();
        inputSelection = selectionMaps::g_reportesMap.startSelection(true);
        switch (inputSelection)
        {
        case 1:
        do
        {   // ************************************** Operacion: Crear Reporte de Uso **************************************
            printRectangle({ 49,9 }, 98, 32, color::dBlack);

            int idSelector{ selectComputer(g_registroComputadoras,{52,11},8,4) };
            if (!idSelector) break;
            // Computer Info & Operations
            DoubleList<Computadora>::Node* target{ g_registroComputadoras.getAt(idSelector - 1) };
            
            printRectangle({ 49,9 }, 98, 32, color::dBlack);
            // Elegir entre crear archivo o volver
            printFormat(formattedText::Elements::computerInfo, { 78,15 }, color::dBlack, color::dBlue);
            mostrarInformacionComputadora(target, { 78,19 });

            selectionMaps::g_reportesConfirmationMap.printAll();
            int createTxtQuestion{ selectionMaps::g_reportesConfirmationMap.startSelection(true) };
            if (createTxtQuestion == 2) continue;
            // Crear Archivo .txt
            printRectangle({ 49,9 }, 98, 32, color::dBlack);
            gotoCOORD({ 85,24 }); printColor("Reporte generado exitosamente...", color::bYellow);

            break;
        } while (1);
        break;
        case 2:
        {   // ************************************** Operacion: Crear Reporte de Uso **************************************
            printRectangle({ 49,9 }, 98, 32, color::dBlack);

            int idSelector{ selectComputer(g_registroComputadoras,{52,11},8,4) };
            if (!idSelector) break;
            // Computer Info & Operations
            DoubleList<Computadora>::Node* target{ g_registroComputadoras.getAt(idSelector - 1) };

            printRectangle({ 49,9 }, 98, 32, color::dBlack);
            // Elegir entre crear archivo o volver
            printFormat(formattedText::Elements::computerInfo, { 78,15 }, color::dBlack, color::dBlue);
            mostrarInformacionComputadora(target, { 78,19 });

            selectionMaps::g_reportesConfirmationMap.printAll();
            int createTxtQuestion{ selectionMaps::g_reportesConfirmationMap.startSelection(true) };
            if (createTxtQuestion == 2) continue;
            // Crear Archivo .txt
            printRectangle({ 49,9 }, 98, 32, color::dBlack);
            gotoCOORD({ 85,24 }); printColor("Reporte generado exitosamente...", color::bYellow);

            break;
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

// ***************************************** Partes Agregadas *****************************************

/*
void agregarSesion(Computadora* comp, int ID, string inicio, string salida, string fecha, float costo) {
    Sesion* nuevaSesion = new Sesion;
    nuevaSesion->IDdeLaComputadora = ID;
    nuevaSesion->HoraDeInicio = inicio;
    nuevaSesion->HoraDeSalida = salida;
    nuevaSesion->fecha = fecha;
    nuevaSesion->costo = costo;
    nuevaSesion->siguiente = NULL;

    if (comp->sesiones == NULL) {
        comp->sesiones = nuevaSesion;
    }
    else {
        Sesion* actual = comp->sesiones;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevaSesion;
    }
}


void calcularTiempoEIngresos(Computadora* comp) {
    float totalIngresos = 0.0;
    int tiempoTotalUso = 0;

    Sesion* actual = comp->sesiones;
    while (actual) {

        int tiempoUso = 7200;
        tiempoTotalUso += tiempoUso;
        totalIngresos += actual->costo;
        actual = actual->siguiente;
    }

    cout << "Reporte de Tiempo de Uso e Ingresos de Computadora ID: " << comp->ID << endl;
    cout << "Tiempo Total de Uso: " << tiempoTotalUso / 3600 << " horas" << endl;
    cout << "Total de Ingresos: $" << totalIngresos << endl;
}


void generarReporteUso(Computadora* comp) {
    cout << "Reporte de Uso de Computadora ID: " << comp->ID << endl;
    cout << "Estado: " << comp->estado << endl;
    cout << "Tiempo de Uso Total: " << comp->tiempoDeUsoTotalSegundos / 3600 << " horas" << endl;


    Sesion* actual = comp->sesiones;
    while (actual) {
        cout << "Sesion en " << actual->fecha << ": "
            << actual->HoraDeInicio << " a " << actual->HoraDeSalida
            << ", Costo: $" << actual->costo << endl;
        actual = actual->siguiente;
    }
}

void generarReporteIngresos(Computadora* comp) {
    float totalIngresos = 0.0;
    int tiempoTotalUso = 0;
    Sesion* actual = comp->sesiones;

    cout << "Reporte de Ingresos de Computadora ID: " << comp->ID << endl;

    while (actual) {
        totalIngresos += actual->costo;
        cout << "Fecha: " << actual->fecha << ", Ingreso: $" << actual->costo << endl;


        tiempoTotalUso += 7200;
        actual = actual->siguiente;
    }
    comp->tiempoDeUsoTotalSegundos += tiempoTotalUso;
    cout << "Total de Ingresos: $" << totalIngresos << endl;
    cout << "Tiempo Total de Uso: " << tiempoTotalUso / 3600 << " horas" << endl;
}

int main() {

    Computadora* comp1 = new Computadora;
    comp1->ID = 1;
    comp1->modificadorDePrecio = 1.0;
    comp1->componentes[0] = "RAM 8GB";
    comp1->componentes[1] = "SSD 256GB";
    comp1->componentes[2] = "Intel i5";
    comp1->componentes[3] = "NVIDIA GTX 1650";
    comp1->estado = "Disponible";
    comp1->tiempoDeUsoTotalSegundos = 7200;
    comp1->sesiones = NULL;

    agregarSesion(comp1, 1, "10:00", "12:00", "2024-10-01", 10.0);
    agregarSesion(comp1, 1, "14:00", "16:00", "2024-10-01", 15.0);
    agregarSesion(comp1, 1, "09:00", "11:00", "2024-10-02", 12.0);

    cout << "--------------------------------" << endl;
    generarReporteUso(comp1);
    cout << "--------------------------------" << endl;
    generarReporteIngresos(comp1);
    cout << "--------------------------------" << endl;


    return 0;
}
*/