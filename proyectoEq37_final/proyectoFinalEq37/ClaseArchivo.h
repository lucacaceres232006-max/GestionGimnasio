#pragma once
#include "Clase.h"

class ClaseArchivo {
private:
    char _nombre[50];

public:
    ClaseArchivo(const char *nombre = "clases.dat");

    bool guardarRegistro(Clase reg);
    int cantidadRegistros();
    Clase leerRegistro(int pos);
    int buscarRegistro(int idClase);
    bool modificarRegistro(Clase reg, int pos);
    bool bajaLogica(int idClase);
    void listarRegistrosActivos();
    void listarTodos();
    void listarPorNombre(const char* nombre);
    void listarPorInstructor(const char* instructor);
    void listarPorCapacidad(int cap);
    void listarInactivas();
    void listarPorHorario(int hora);
    int contarInscripcionesPorClase(int idClase);
    void reporteMasSolicitadas();
    void mostrarReporteMasSolicitadas();
};

