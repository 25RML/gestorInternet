#pragma once

#include <string>
#include <chrono>

/*================================================================================================================================================================
                        STRUCTS
================================================================================================================================================================*/
struct Fecha
{
    short year{};
    short month{};
    short day{};
};

struct Hora
{
    short hour{};
    short minute{};

    void sumarTiempo(Hora tiempoHoras)
    {
        minute += tiempoHoras.minute;
        hour += tiempoHoras.hour;

        short hourPass{ static_cast<short>(minute / 60) };
        minute %= 60;
        hour += hourPass;

        hour %= 24;
    }
};

struct FullTime
{
    Hora hora{};
    Fecha fecha{};

    void sumarTiempo(Hora tiempoHoras)
    {
        if ((hora.minute += tiempoHoras.minute) >= 60)
        {
            hora.minute -= 60;
            ++hora.hour;
        }
        if ((hora.hour += tiempoHoras.hour) >= 24)
        {
            hora.hour -= 24;
            ++fecha.day;
        }
    }
};

template <typename T>
struct DoubleList
{
    struct Node
    {
        T data{};

        Node* prev{};
        Node* next{};

    };

    Node* head{};

    // ******* FUNCTIONS *******
    Node* createEntry(const T& data) const
    {
        Node* newNode{ new Node };
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return newNode;
    }

    size_t getSize() const
    {
        Node* runner{ head };
        size_t size{ 0 };
        while (runner)
        {
            runner = runner->next;
            ++size;
        }
        return size;
    }

    Node* getAt(size_t pos) const
    {
        if (pos < 0) // Transform Negative into Positive
        {
            pos += getSize();
            if (pos < 0) return nullptr;
        }
        Node* runner{ head };
        while (runner)
        {
            if (pos == 0) break;
            runner = runner->next;
            --pos;
        }
        if (pos > 0) return nullptr; // Out of range
        return runner;  // Normal behaviour: Returns intended pointer
    }

    void append(Node* node)
    {
        if (!head)
        {
            head = node;
            return;
        }
        Node* runner{ head };
        while (runner->next) runner = runner->next;

        runner->next = node;
        node->prev = runner;
    }

    void push(Node* node)
    {
        if (!head)
        {
            head = node;
            return;
        }
        head->prev = node;
        node->next = head;
        head = node;
    }

    void deleteOnly(size_t pos)
    {
        Node* deleteTarget{ getAt(pos) };
        if (pos == 0) head = head->next;
        if (!deleteTarget) return;
        if (deleteTarget->prev) deleteTarget->prev->next = deleteTarget->next;
        if (deleteTarget->next) deleteTarget->next->prev = deleteTarget->prev;
        delete(deleteTarget);
    }

    void deleteAll() const
    {
        Node* eraser{};
        Node* runner{ head };
        while (runner)
        {
            eraser = runner;
            runner = runner->next;
            delete(eraser);
        }
    }
};

template <typename T>
struct SingleList
{
    struct Node
    {
        T data{};
        Node* next{};
    };
    Node* head{};
    // ******* FUNCTIONS *******
    Node* createEntry(const T& data) const
    {
        Node* newNode{ new Node };
        newNode->data = data;
        newNode->next = nullptr;
        return newNode;
    }
    size_t getSize() const
    {
        Node* runner{ head };
        size_t size{ 0 };
        while (runner)
        {
            runner = runner->next;
            ++size;
        }
        return size;
    }
    Node* getAt(size_t pos) const
    {
        if (pos < 0) // Transform Negative into Positive
        {
            pos += getSize();
            if (pos < 0) return nullptr; // Out of scope
        }
        Node* runner{ head };
        while (runner)
        {
            if (pos == 0) break;
            runner = runner->next;
            --pos;
        }
        if (pos > 0) return nullptr; // Out of range
        return runner;  // Normal behaviour: Returns intended pointer
    }
    void append(Node* node)
    {
        if (!this->head)
        {
            this->head = node;
            return;
        }
        Node* runner{ this->head };
        while (runner->next) runner = runner->next;
        runner->next = node;
    }
    void push(Node* node)
    {
        if (!head)
        {
            head = node;
            return;
        }
        node->next = head;
        head = node;
    }
    void insert(Node* source, size_t pos)
    {
        size_t listSize = getSize();
        if (pos < 0) {
            pos += listSize;
            if (pos < 0) return;
            if (pos >= listSize) return;
            ++pos;
        }
        if (pos == 0) {
            source->next = head;
            head = source;
            return;
        }
        if (pos < listSize) {
            Node* tempPointer = getAt(pos - 1);
            source->next = tempPointer->next;
            tempPointer->next = source;
        }
        else if (pos == listSize) append(source);
    }
    void deleteOnly(size_t pos)
    {
        if (pos == 0)
        {
            Node* reserve{ head };
            head = head->next;
            delete(reserve);
            return;
        }
        Node* reserve{ getAt(pos - 1) };
        if (!(reserve->next)) return; // Does not exist
        Node* deleteTarget{ reserve->next };
        reserve->next = deleteTarget->next;
        delete(deleteTarget);
    }
    void deleteAll() const
    {
        Node* eraser{};
        Node* runner{ head };
        while (runner)
        {
            eraser = runner;
            runner = runner->next;
            delete(eraser);
        }
    }
};

struct Reserva
{
    Fecha fecha{};
    Hora horaInicio{};
    Hora horaFinal{};
};

struct Sesion
{
    int idComputadora{};    // ID de la computadora siendo usada
    int idCliente{};        // ID del cliente usando la computadora (0 para cliente no registrado)
    Hora horaInicio{};      // Hora de inicio del servicio
    Hora horaSalida{};
    Fecha fecha{};
    double costo{};
};

struct Computadora
{
    int ID;                                 // ID de la computadora
    float modificadorDePrecio{};            // Valor decimal que modifica la tarifa general del servicio (default = 1.0)
    std::string componentes[4]{};           // Componentes de la computadora
    int estado{ 0 };                          // Estado de la computadora, 0: Libre, 1: Ocupada, 2: Reservada, 3: No Disponible (mantenimiento y otros)
    int tiempoDeUsoTotalSegundos{};         // Tiempo de uso total de la maquina (en segundos)
    SingleList<Reserva> colaReservas{};     // Lista simplemente enlazada (cola) de las reservas para esta maquina
    Sesion* sesionActiva{ nullptr };        // Puntero a la sesión activa
    std::chrono::steady_clock::time_point tiempoInicioReal{}; // Tiempo real de inicio de la sesión
};

struct Cliente
{
    std::string nombre{};   // Nombre
    int ID{};               // Solo si esta registrado en el "sistema", de otra forma = 0 (false)
    int totalHoras{};       // Solo si ID es (true), registra el numero total de horas del cliente en el servicio
    int gastoTotal{};       // Solo si ID es (true), registra el gasto total del cliente en el servicio
};

/*================================================================================================================================================================
                        FUNCTIONS
================================================================================================================================================================*/
void generateComputersList(DoubleList<Computadora>& target, const int& amount);
DoubleList<Computadora>::Node* getByComputerID(DoubleList<Computadora> target, const int& id);