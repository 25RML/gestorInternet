#pragma once

#include <string>

/*================================================================================================================================================================
                        STRUCTS
================================================================================================================================================================*/

struct Computadora
{
    int ID;
    float modificadorDePrecio {};
    std::string componentes[4] {};
    std::string estado {};
    int tiempoDeUsoTotalSegundos {};

};

//using Computadora = nodeComputadora*;

template <typename T>
struct doubleList
{
    // ******************* VARIABLES *******************

    T data{};

    doubleList* prev{};
    doubleList* next{};

    // ******************* FUNCTIONS *******************

    size_t size()
    {
        doubleList<T>* runner{ this };
        size_t i{ 0 };
        while (runner)
        {
            runner = runner->next;
            ++i;
        }
        return i;
    }

    doubleList<T>* getAt(size_t pos)
    {
        if (pos < 0)
        {
            pos += size();
            if (pos < 0) return NULL;
        }
        doubleList<T>* runner{ this };
        while (runner)
        {
            if (pos == 0) break;
            runner = runner->next;
            --pos;
        }
        if (pos > 0) return NULL;
        return runner;
    }

    void append(doubleList<T>* source)
    {
        doubleList<T>* runner{ this };
        if (!runner)
        {
            runner = source;
            return;
        }
        while (runner->next) runner = runner->next;

        runner->next = source;
        source->prev = runner;
    }

    void push(doubleList<T>* source)
    {
        if (!this)
        {
            this = source;
            return;
        }
        source->next = this;
        this->prev = source;
        this = source;
    }

    void deleteOnly(int& pos)
    {
        doubleList<T>* target{ getAt(pos) };
        if (!target) return;
        else
        {
            if (target->prev) target->prev->next = target->next;
            if (target->next) target->next->prev = target->prev;
            delete(target);
        }
    }

    void deleteAll()
    {
        doubleList<T>* eraser{};
        doubleList<T>* runner{ this };
        while (runner)
        {
            eraser = runner;
            runner = runner->next;
            delete(eraser);
        }
    }
};


/*================================================================================================================================================================
                        FUNCTIONS
================================================================================================================================================================*/
void generateComputersList(doubleList<Computadora>*& target, const int& amount);


// ******************************************** TEMPLATES ********************************************
template <typename T>
doubleList<T>* createEntry(const T& data)
{
    doubleList<T>* newNode = new(doubleList<T>);
    newNode->data = data;

    newNode->prev = nullptr;
    newNode->next = nullptr;

    return newNode;
}