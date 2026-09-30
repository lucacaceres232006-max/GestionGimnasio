#pragma once
#include <cstring>

class Rutina
{
private:
    int _idRutina;
    char _tipo[45];
    char _descripcion[500];
    int _duracion;
    char _nivel[20];
    bool _activo;

public:
    Rutina();

    void Cargar();
    void Mostrar();

    void setId(int id);
    int getId();

    void setTipo(const char* tipo);
    const char* getTipo();

    void setDescripcion(const char* desc);
    const char* getDescripcion();

    void setDuracion(int duracion);
    int getDuracion();

    void setNivel(const char* nivel);
    const char* getNivel();

    void setActivo(bool activo);
    bool getActivo();
};
