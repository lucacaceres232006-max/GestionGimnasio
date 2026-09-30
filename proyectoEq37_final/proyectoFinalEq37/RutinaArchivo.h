#pragma once
#include "Rutina.h"

class RutinaArchivo
{
private:
    char _nombre[30];

public:
    RutinaArchivo(const char *nombre = "rutinas.dat");

    bool guardarRegistro(Rutina reg);

    int cantidadRegistros();

    Rutina leerRegistro(int pos);

    int buscarRegistro(int idRutina);

    bool modificarRegistro(Rutina reg, int pos);

    bool bajaLogica(int idRutina);

    void listarRegistrosActivos();

    void listarRegistrosInactivos();

    void listarPorNivel(const char *nivel);

    void listarPorTipo(const char *tipo);

    void listarRegistros();

    int buscarIdPorTipo(const char* tipoBuscado);
};
