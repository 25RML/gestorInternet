#include <iostream>
#include <string>

using namespace std;


struct Sesion {
    int IDdeLaComputadora;
    string HoraDeInicio;
    string HoraDeSalida;
    string fecha;
    float costo;
    Sesion* siguiente;
};


struct Computadora {
    int ID;
    float modificadorDePrecio;
    string componentes[4];
    string estado;
    int tiempoDeUsoTotalSegundos;
    Sesion* sesiones;
};


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
    } else {
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

    cout<<"--------------------------------"<<endl;
    generarReporteUso(comp1);
    cout<<"--------------------------------"<<endl;
    generarReporteIngresos(comp1);
    cout<<"--------------------------------"<<endl;


    return 0;
}

