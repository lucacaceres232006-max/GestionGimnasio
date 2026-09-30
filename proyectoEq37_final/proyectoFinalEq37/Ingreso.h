#pragma once
#include "Fecha.h"

class Ingreso
{
private:
    int _idIngreso;
    int _dniSocio;
    Fecha _fecha;
    bool _activo;

public:
    Ingreso();

    void Cargar();
    void Mostrar();

void setIdIngreso(int id);
int getIdIngreso();

void setDniSocio(int dni);
int getDniSocio();

void setActivo(bool activo);
bool getActivo();

void setFecha(Fecha fecha);
Fecha getFecha();
};

