#pragma once
#include "Fecha.h"

class Inscripcion {
private:
    int _idInscripcion;
    int _dniSocio;
    Fecha _fechaInscripcion;
    int _idClase;
    bool _activo;

public:
    Inscripcion();

    void setIdInscripcion(int idInscripcion);
    void setDniSocio(int dniSocio);
    void setFechaInscripcion(Fecha fechaInscripcion);
    void setIdClase(int idClase);
    void setActivo(bool activo);

    int getIdInscripcion();
    int getDniSocio();
    Fecha getFechaInscripcion();
    int getIdClase();
    bool getActivo();

    void Cargar();
    void Mostrar();
};
