#pragma once
#include "Ingreso.h"

class IngresoArchivo
{
private:
    char _nombre[30];

public:
    IngresoArchivo(const char *nombre = "ingresos.dat");

    bool guardarRegistro(Ingreso reg);
    int cantidadRegistros();
    Ingreso leerRegistro(int pos);
    int buscarRegistro(int idIngreso);
    bool modificarRegistro(Ingreso reg, int pos);
    void reporteConcurrenciaMensual();
    void reporteSociosMayorAsistencia();
    bool bajaLogica(int idIngreso);
    void historialActividad();
    void listarPorDni(int dni);
    void listarRegistros();
    int buscarRegistroDni(int dni);
};
