#pragma once
#include "Personas.h"

class Instructor : public Persona
{
private:
    int _idClase;
    int _idInstructor;
    bool _monotributo;
    bool _activo;

public:
    Instructor();

    void Cargar();
    void Mostrar();

    void setIdClase(int idClase);
    int getIdClase();

    void setIdInstructor(int idInstructor);
    int getIdInstructor();

    void setMonotributo(bool mono);
    bool getMonotributo();

    void setActivo(bool activo);
    bool getActivo();
};
