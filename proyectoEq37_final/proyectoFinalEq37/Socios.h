#pragma once
#include "Personas.h"

class Socio: public Persona
{
private:
    int _idSocio;
    int _idRutina;
    int _idMembresia;
    char _objetivo[50];
    int _activo;

public:
    Socio();

    void Cargar();

    void CargarSocioSinDNI();

    void cargarObjetivo();

    int estadoDelSocio();

    void Mostrar();

    void setIdSocio(int idSocio);
    int getIdSocio();

    void setIdRutina(int idRutina);
    int getIdRutina();

    void setIdMembresia(int idMembresia);
    int getIdMembresia();

    void setObjetivo(const char* obj);
    const char* getObjetivo();

    void setActivo(int activo);
    int getActivo();

};

