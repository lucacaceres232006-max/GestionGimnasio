#pragma once
#include "Instructores.h"

class InstructorArchivo
{
private:
    char _nombre[30];

public:
    InstructorArchivo(const char *nombre = "instructores.dat");

    bool guardarRegistro(Instructor reg);

    int cantidadRegistros();

    Instructor leerRegistro(int pos);

    int buscarRegistro(int idInstructor);

    bool modificarRegistro(Instructor reg, int pos);

    bool bajaLogica(int idInstructor);

    void listarRegistros();
};
