#pragma once
// Includes
#include "tempFile.h"

// Declaraciones de Funcion
void mainReportes();
void generarReporteUsoTxt(Computadora* comp, SingleList<Sesion>& sesiones);
void generarReporteIngresosTxt(Computadora* comp, SingleList<Sesion>& sesiones);