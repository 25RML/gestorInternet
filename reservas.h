#pragma once
// Includes
#include "tempFile.h"

// Declaraciones de Funcion
void mainReservas();
bool esReservaEnElPasado(Fecha fechaReserva, Hora horaReserva);
int checkParity(const SingleList<Reserva> origin, const Reserva& toAdd);