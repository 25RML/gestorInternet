// Includes
#include <iostream>

#include "gestionComputadoras.h"
#include "interface.h" // para el gotoCOORD()
#include "gestionClientes.h"
// *************************************** Funciones ***************************************

void mainGestionClientes()
{
	gotoCOORD(Windows::mainWindowStartPOS); // Version alterna del gotoxy
	std::cout << "Hello World!";
}

using namespace std;

struct Computadora {
    bool ocupada;
    int tarifa;
    string cliente;
    time_t inicio;
    double total;
};

vector<Computadora> computadoras(20);
const vector<string> nombresClientes = {
    "Valentina Lopez", "Diego Martinez", "Lucia Castillo", "Sebastian Vargas", "Camila Fernandez",
    "Andres Morales", "Sofia Gomez", "Mateo Ramirez", "Emma Navarro", "Juan Perez",
    "Isabella Rodriguez", "Luis Torres", "Antonella Silva", "Nicolas Mendoza", "Martina Rojas",
    "Alejandro Diaz", "Renata Paredes", "Daniel Herrera", "Victoria Guzman", "Felipe Sanchez"
};

map<string, int> horasConteo;
map<string, double> gastosTotales;

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

int main() {
    for (int i = 0; i < 20; i++) {
        computadoras[i].ocupada = false;
        computadoras[i].total = 0.0;
        computadoras[i].tarifa = (i < 10) ? 1 : (i < 15) ? 2 : 3;
    }
    cargarEstado();
    cargarHoras();
    cargarGastos();

    int opcion;
    while (true) {
        mostrarEstado();
        cout << "\nSelecciona una opcion:\n";
        cout << "1. Simular cliente aleatorio hora libre\n";
        cout << "2. Finalizar hora libre de cliente\n";
        cout << "3. Simular cliente aleatorio hora fija\n";
        cout << "4. Horas gratis\n";
        cout << "5. Observar registros\n";
        cout << "6. Salir\n";
        cin >> opcion;

        switch (opcion) {
        case 1: simularClienteAleatorioLibre(); break;
        case 2: finalizarHoraLibre(); break;
        case 3: simularClienteAleatorioFija(); break;
        case 4: horasGratis(); break;
        case 5: observarRegistros(); break;
        case 6: guardarEstado(); guardarHoras(); guardarGastos(); return 0;
        default: cout << "Opcion invalida. Intenta de nuevo.\n";
        }
    }
}

void mostrarEstado() {
    for (int i = 0; i < 20; i++) {
        cout << "PC " << (i + 1) << " [" << (computadoras[i].ocupada ? 'x' : 'o') << "] ";
        if ((i + 1) % 5 == 0) cout << endl;
    }
}

void cargarEstado() {
    ifstream file("clientes.txt");
    for (int i = 0; i < 20 && file; i++) {
        file >> computadoras[i].cliente >> computadoras[i].ocupada;
        file >> computadoras[i].inicio >> computadoras[i].total;
    }
    file.close();
}

void guardarEstado() {
    ofstream file("clientes.txt");
    for (int i = 0; i < 20; i++) {
        file << computadoras[i].cliente << " " << computadoras[i].ocupada << " ";
        file << computadoras[i].inicio << " " << computadoras[i].total << endl;
    }
    file.close();
}

void cargarHoras() {
    ifstream file("horasconteo.txt");
    if (!file) return;
    string cliente;
    int horas;
    while (file >> cliente >> horas) {
        horasConteo[cliente] = horas;
    }
    file.close();
}

void guardarHoras() {
    ofstream file("horasconteo.txt");
    for (const auto& pair : horasConteo) {
        file << pair.first << " " << pair.second << endl;
    }
    file.close();
}

void cargarGastos() {
    ifstream file("gastos.txt");
    if (!file) return;
    string cliente;
    double gasto;
    while (file >> cliente >> gasto) {
        gastosTotales[cliente] = gasto;
    }
    file.close();
}

void guardarGastos() {
    ofstream file("gastos.txt");
    for (const auto& pair : gastosTotales) {
        file << pair.first << " " << pair.second << endl;
    }
    file.close();
}

void simularClienteAleatorioLibre() {
    int pc;
    srand(time(0));
    do {
        pc = rand() % 20;
    } while (computadoras[pc].ocupada);

    computadoras[pc].ocupada = true;
    computadoras[pc].cliente = nombresClientes[rand() % nombresClientes.size()];
    computadoras[pc].inicio = time(0);

    cout << "\n" << computadoras[pc].cliente << " ha iniciado sesion en la PC " << (pc + 1) << endl;
    cout << "Hora de inicio: " << ctime(&computadoras[pc].inicio) << endl;
}

void finalizarHoraLibre() {
    int pc = -1;
    for (int i = 0; i < 20; i++) {
        if (computadoras[i].ocupada) {
            cout << "PC " << (i + 1) << " - " << computadoras[i].cliente << endl;
        }
    }
    cout << "Selecciona una PC para finalizar (1-20): ";
    cin >> pc;
    pc--;

    if (pc < 0 || pc >= 20 || !computadoras[pc].ocupada) {
        cout << "Seleccion invalida.\n";
        return;
    }

    time_t fin = time(0);
    double tiempoUsado = difftime(fin, computadoras[pc].inicio) / 60;
    double monto = tiempoUsado * computadoras[pc].tarifa;

    computadoras[pc].ocupada = false;
    horasConteo[computadoras[pc].cliente] += tiempoUsado / 60;
    gastosTotales[computadoras[pc].cliente] += monto;

    guardarGastos();
    guardarHoras();

    cout << "El cliente " << computadoras[pc].cliente << " ha finalizado su tiempo en la PC " << (pc + 1) << endl;
    cout << "Tiempo usado: " << tiempoUsado << " minutos\n";
    cout << "Monto a cobrar: S/." << monto << endl;
}

void horasGratis() {
    vector<string> clientesConHorasGratis;
    for (const auto& pair : horasConteo) {
        if (pair.second >= 5) {
            clientesConHorasGratis.push_back(pair.first);
        }
    }

    if (clientesConHorasGratis.empty()) {
        cout << "No hay clientes con horas acumuladas suficientes para horas gratis.\n";
        return;
    }

    srand(time(0));
    string clienteSeleccionado = clientesConHorasGratis[rand() % clientesConHorasGratis.size()];
    cout << "El cliente " << clienteSeleccionado << " ha recibido una hora gratis.\n";
    horasConteo[clienteSeleccionado] -= 5;

    ofstream file("horasfree.txt", ios::app);
    file << clienteSeleccionado << " ha recibido una hora gratis.\n";
    file.close();
}

void simularClienteAleatorioFija() {
    int pc, horas, tarifa;
    srand(time(0));
    do {
        pc = rand() % 20;
    } while (computadoras[pc].ocupada);

    cout << "Horas a alquilar (1, 2, 3, etc.): ";
    cin >> horas;
    tarifa = computadoras[pc].tarifa * horas;

    computadoras[pc].ocupada = true;
    computadoras[pc].cliente = nombresClientes[rand() % nombresClientes.size()];
    computadoras[pc].total += tarifa;
    cout << "El cliente " << computadoras[pc].cliente << " alquilo la PC " << (pc + 1) << " por " << horas << " horas.\n";
}

void observarRegistros() {
    cout << left << setw(25) << "Nombre del Cliente"
        << setw(20) << "Horas Alquiladas"
        << setw(25) << "Horas Gratis Disponibles"
        << setw(20) << "Total Gastado" << endl;
    cout << string(90, '-') << endl;

    for (const auto& cliente : nombresClientes) {
        int horasGratis = horasConteo[cliente];
        double totalGastado = gastosTotales[cliente];
        cout << left << setw(25) << cliente
            << setw(20) << horasConteo[cliente]
            << setw(25) << horasGratis
            << setw(20) << totalGastado << endl;
    }
}

