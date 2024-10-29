#pragma once
#pragma once
// Includes
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <string_view>

// ********************************************** Variables **********************************************
extern std::map<std::string, int> horasConteo;
extern std::map<std::string, double> gastosTotales;

constexpr std::string_view nombresClientes[20]
{
    "Valentina Lopez",
    "Diego Martinez",
    "Lucia Castillo",
    "Sebastian Vargas",
    "Camila Fernandez",
    "Andres Morales",
    "Sofia Gomez",
    "Mateo Ramirez",
    "Emma Navarro",
    "Juan Perez",
    "Isabella Rodriguez",
    "Luis Torres",
    "Antonella Silva",
    "Nicolas Mendoza",
    "Martina Rojas",
    "Alejandro Diaz",
    "Renata Paredes",
    "Daniel Herrera",
    "Victoria Guzman",
    "Felipe Sanchez"
};

// Declaraciones de Funcion
void mainGestionClientes();

/*
void cargarEstado();
void guardarEstado();
void cargarHoras();
void guardarHoras();
void cargarGastos();
void guardarGastos();
void mostrarEstado();
void simularClienteAleatorioLibre();
void finalizarHoraLibre();
void simularClienteAleatorioFija();
void observarRegistros();
void horasGratis();
*/