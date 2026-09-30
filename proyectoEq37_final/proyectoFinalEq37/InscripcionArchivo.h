#pragma once
#include "Inscripcion.h"

class InscripcionArchivo
{
private:
    char _nombre[30];

public:
    InscripcionArchivo(const char *nombre = "Inscripciones.dat");
    bool guardarRegistro(Inscripcion reg);
    int cantidadRegistros();
    Inscripcion leerRegistro(int pos);
    int buscarRegistro(int idInscripcion);
    bool modificarRegistro(Inscripcion reg, int pos);
    bool bajaLogica(int idInscripcion);
    void listarRegistrosActivos();
    bool yaEstaInscripto(int dni, int idClase);
};


