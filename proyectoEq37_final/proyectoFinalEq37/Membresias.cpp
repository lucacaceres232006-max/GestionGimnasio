#include <iostream>
#include <cstring>
#include "Membresias.h"

using namespace std;

Membresias::Membresias()
{
    _idMembresia=0;
    strcpy(_nombre,"");
    _precio=0;
    _activo=false;
}


void Membresias::setIdMembresia(int idMembresia)
{
    if(idMembresia>0)
    {
        _idMembresia=idMembresia;
    }
}
int Membresias::getIdMembresia()
{
    return _idMembresia;
}

void Membresias::setNombre(const char *nombre)
{
    if(strlen(nombre)>0 && strlen(nombre)<30)
    {
        strcpy(_nombre,nombre);
    }
}
const char* Membresias::getNombre()
{
    return _nombre;
}

bool Membresias::setPrecio(float precio)
{
    if(precio>0)
    {
        _precio=precio;
        return true;
    }
    return false;
}
float Membresias::getPrecio()
{
    return _precio;
}
void Membresias::setActivo(bool activo)
{
    _activo=activo;
}
bool Membresias::getActivo()
{
    return _activo;
}

void Membresias::Cargar()
{
    if (cin.peek() == '\n') cin.ignore();

    cout << "Ingrese el nombre de la nueva membresia (Ej: Pase Libre): ";
    cin.getline(_nombre,30);

    cout << "Ingrese el precio mensual: $";
    cin >> _precio;

    if (cin.peek() == '\n') cin.ignore();

    cout << "Ingrese la descripcion del plan: ";
    cin.getline(_descripcionMembresia,500);

    _activo=true;

}


void Membresias::Mostrar()
{
    cout << "ID Membresia: " << _idMembresia << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Precio: $" << _precio << endl;
    cout << "Descripcion: " << _descripcionMembresia << endl;
}

