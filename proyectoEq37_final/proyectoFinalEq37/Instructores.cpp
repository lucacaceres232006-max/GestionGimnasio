#include <iostream>
#include "Instructores.h"

using namespace std;

Instructor::Instructor() : Persona()
{
    _idClase = 0;
    _idInstructor = 0;
    _monotributo = false;
    _activo = true;
}

void Instructor::Cargar()
{
    Persona::Cargar();

    cout << "ID Clase: ";
    cin >> _idClase;

    cout << "Monotributo (1=SI / 0=NO): ";
    cin >> _monotributo;

    _activo = true;
}
void Instructor::Mostrar()
{
    Persona::Mostrar();

    cout << "ID Instructor: " << _idInstructor << endl;
    cout << "ID Clase: " << _idClase << endl;
    cout << "Monotributo: " << _monotributo << endl;
    cout << "Activo: " << _activo << endl;
}

void Instructor::setIdClase(int idClase)
{
    if(idClase > 0)
    {
        _idClase = idClase;
    }
}

int Instructor::getIdClase()
{
    return _idClase;
}

void Instructor::setIdInstructor(int idInstructor)
{
    if(idInstructor > 0)
    {
        _idInstructor = idInstructor;
    }
}

int Instructor::getIdInstructor()
{
    return _idInstructor;
}

void Instructor::setMonotributo(bool mono)
{
    _monotributo = mono;
}

bool Instructor::getMonotributo()
{
    return _monotributo;
}

void Instructor::setActivo(bool activo)
{
    _activo = activo;
}

bool Instructor::getActivo()
{
    return _activo;
}
