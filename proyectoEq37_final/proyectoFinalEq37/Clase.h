#pragma once
#include "Fecha.h"

class Clase {
private:
    int _idClase;
    char _nombreDeClase[50];
    char _instructorClase[50];
    Fecha _horarioClase;
    int _capacidadMax;
    bool _activo;

public:

    Clase();

    void setIdClase(int idClase);
    void setNombreDeClase(const char* nombre);
    void setInstructorClase(const char* instructor);
    void setHorarioClase(Fecha horario);
    bool setCapacidadMax(int capacidad);
    void setActivo(bool activo);
    int getIdClase();
    const char* getNombreDeClase();
    const char* getInstructorClase();
    Fecha getHorarioClase();
    int getCapacidadMax();
    bool getActivo();

    void Cargar();
    void Mostrar();
};

