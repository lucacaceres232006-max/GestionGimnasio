#pragma once
#include "Fecha.h"

class Persona
{

private:
    int _dni;
    char _nombre[50];
    char _apellido[50];
    Fecha _fechaNacimiento;
    char _telefono[20];
    char _email[80];


public:
    ///CONSTRUCTORES
    Persona();
    void Cargar();
    void CargarPersonaSinDNI();
    void Mostrar();
    ///SETTERS Y GETTERS
    bool setDNI(int dni);
    int getDNI();

    void setNombre(const char *nombre);
    const char *getNombre();

    void setApellido(const char *apellido);
    const char *getApellido();

    void setFechaNacimiento(Fecha fecha);
    Fecha getFechaNacimiento();

    void setTelefono(const char *telefono);
    const char *getTelefono();

    void setEmail(const char *email);
    const char *getEmail();

};
