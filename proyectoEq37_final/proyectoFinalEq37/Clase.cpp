#include <iostream>
#include <cstring>
#include "Clase.h"

using namespace std;

Clase::Clase()
{
    _idClase = 0;
    strcpy(_nombreDeClase, "");
    strcpy(_instructorClase, "");
    _capacidadMax = 0;
    _activo = false;
}

void Clase::setIdClase(int idClase)
{
    _idClase = idClase;
}

void Clase::setNombreDeClase(const char* nombre)
{
    strcpy(_nombreDeClase, nombre);
}

void Clase::setInstructorClase(const char* instructor)
{
    strcpy(_instructorClase, instructor);
}

void Clase::setHorarioClase(Fecha horario)
{
    _horarioClase = horario;
}

bool Clase::setCapacidadMax(int capacidad)
{
    if(capacidad > 0)
    {
        _capacidadMax = capacidad;
        return true;
    }
    return false;
}

void Clase::setActivo(bool activo)
{
    _activo = activo;
}

int Clase::getIdClase()
{
    return _idClase;
}

const char* Clase::getNombreDeClase()
{
    return _nombreDeClase;
}

const char* Clase::getInstructorClase()
{
    return _instructorClase;
}

Fecha Clase::getHorarioClase()
{
    return _horarioClase;
}

int Clase::getCapacidadMax()
{
    return _capacidadMax;
}

bool Clase::getActivo()
{
    return _activo;
}

void Clase::Cargar()
{
    cin.ignore();

    cout << "Nombre de la clase: ";
    cin.getline(_nombreDeClase, 50);
    cout << "Instructor: ";
    cin.getline(_instructorClase, 50);

    cout << "Horario de la clase:" << endl;
    _horarioClase.cargaManualTiempo();

    int capacidad;

    do
    {
        cout << "Capacidad maxima: ";
        cin >> capacidad;

        if(capacidad <= 0)
        {
            cout << "Error. La capacidad debe ser mayor a 0." << endl;
        }

    }
    while(capacidad <= 0);

    _capacidadMax = capacidad;
    _activo = true;
}
void Clase::Mostrar()
{
    cout << "ID Clase: " << _idClase << endl;
    cout << "Nombre de la clase: " << _nombreDeClase << endl;
    cout << "Instructor: " << _instructorClase << endl;
    cout << "Horario: ";
    _horarioClase.mostrarSoloHora();
    cout << "Capacidad maxima: " << _capacidadMax << endl;
    cout << "Estado: ";
    if(_activo)
    {
        cout << "Activa" << endl;
    }
    else
    {
        cout << "Inactiva" << endl;
    }
}

