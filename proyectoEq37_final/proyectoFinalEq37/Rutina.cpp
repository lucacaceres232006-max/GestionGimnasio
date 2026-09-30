#include <iostream>
#include <cstring>
#include "Rutina.h"

using namespace std;

Rutina::Rutina()
{
    _idRutina = 0;
    strcpy(_tipo, "");
    strcpy(_descripcion, "");
    _duracion = 0;
    strcpy(_nivel, "");
    _activo = true;
}

void Rutina::Cargar()
{
    if (cin.peek() == '\n') cin.ignore();

    cout << "Tipo (Ej: Masa Muscular / Perder Grasa): ";
    cin.getline(_tipo, 45);

    cout << "Descripcion: ";
    cin.getline(_descripcion, 500);

    cout << "Duracion (en minutos): ";
    cin >> _duracion;

    if (cin.peek() == '\n') cin.ignore();

    cout << "Nivel (Principiante/Intermedio/Avanzado): ";
    cin.getline(_nivel, 20);

    _activo = true;
}

void Rutina::Mostrar()
{
    cout << "ID: " << _idRutina << endl;
    cout << "Tipo: " << _tipo << endl;
    cout << "Descripcion: " << _descripcion << endl;
    cout << "Duracion: " << _duracion << " min" << endl;
    cout << "Nivel: " << _nivel << endl;
    cout << "Estado: ";

    if(_activo)
    {
        cout << "ACTIVA";
    }
    else
    {
        cout << "INACTIVA";
    }

    cout << endl;
}
int Rutina::getId()
{
    return _idRutina;
}
void Rutina::setId(int id)
{
    if(id > 0) _idRutina = id;
}

void Rutina::setTipo(const char* tipo)
{
    strcpy(_tipo, tipo);
}

const char* Rutina::getTipo()
{
    return _tipo;
}

void Rutina::setDescripcion(const char* desc)
{
    strcpy(_descripcion, desc);
}

const char* Rutina::getDescripcion()
{
    return _descripcion;
}

void Rutina::setDuracion(int duracion)
{
    if(duracion > 0) _duracion = duracion;
}

int Rutina::getDuracion()
{
    return _duracion;
}

void Rutina::setNivel(const char* nivel)
{
    strcpy(_nivel, nivel);
}

const char* Rutina::getNivel()
{
    return _nivel;
}

void Rutina::setActivo(bool activo)
{
    _activo = activo;
}

bool Rutina::getActivo()
{
    return _activo;
}
