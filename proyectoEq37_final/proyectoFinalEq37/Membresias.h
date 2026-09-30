#pragma once

class Membresias
{

private:
    int _idMembresia;
    char _nombre[30];
    char _descripcionMembresia[500];
    float _precio;
    bool _activo;

public:

    ///CONSTRUCTOR
    Membresias();
    /// GETTERS Y SETTERS
    void setIdMembresia(int idMembresia);
    int getIdMembresia();

    void setNombre(const char *nombre);
    const char* getNombre();

    bool setPrecio(float precio);
    float getPrecio();

    void setActivo(bool activo);
    bool getActivo();

    void Cargar();
    void Mostrar();
};
