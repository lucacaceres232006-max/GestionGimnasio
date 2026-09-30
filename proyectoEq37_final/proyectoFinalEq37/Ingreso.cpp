#include <iostream>
#include "ingreso.h"

using namespace std;

Ingreso::Ingreso()
{
    _idIngreso = 0;
    _dniSocio = 0;
    _activo = true;
}

void Ingreso::Cargar()
{
    cout << "DNI del socio: ";
    cin >> _dniSocio;

    _fecha.cargarFechaActualAutomatica();

    _activo = true;
}

void Ingreso::Mostrar()
{
    cout << "ID Ingreso: " << _idIngreso << endl;
    cout << "DNI Socio: " << _dniSocio << endl;
    _fecha.mostrar();
    cout << "Activo: " << _activo << endl;
}

// GETTERS Y SETTERS (UNA SOLA VEZ)

void Ingreso::setIdIngreso(int id)
{
    if (id > 0)
        _idIngreso = id;
}

int Ingreso::getIdIngreso()
{
    return _idIngreso;
}

void Ingreso::setDniSocio(int dni)
{
    if (dni > 0)
        _dniSocio = dni;
}

int Ingreso::getDniSocio()
{
    return _dniSocio;
}

void Ingreso::setActivo(bool activo)
{
    _activo = activo;
}

bool Ingreso::getActivo()
{
    return _activo;
}

void Ingreso::setFecha(Fecha fecha)
{
    _fecha = fecha;
}

Fecha Ingreso::getFecha()
{
    return _fecha;
}
