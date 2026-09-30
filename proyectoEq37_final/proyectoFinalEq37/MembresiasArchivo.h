#pragma once
#include "Membresias.h"
class MembresiasArchivo
{
private:
    char _nombre[30];

public:
    ///const
    MembresiasArchivo(const char *nombre="membresias.dat");

    bool guardarRegistro(Membresias reg);
    int cantidadRegistros();
    Membresias leerRegistro(int pos);
    int generarNuevoID();
    int buscarRegistroIDMembresia(int idMembresia);
    bool modificarRegistro(Membresias reg, int pos);
    bool bajaLogica(int idMembresia);
    void listarRegistrosActivos();
    void consultarMembresiaPorNombre(const char* nombreBuscado);
    void consultarMembresiaPorPrecio(int precio);
};
