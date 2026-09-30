#pragma once
#include "Socios.h"
class SocioArchivo{

private:

    char _nombre[30];

public:
    ///CONSTRUCTOR
    SocioArchivo(const char *nombre="socios.dat", bool vacio=false);
    ///MÉTODOS
  bool guardarRegistro(Socio reg);

  int cantidadRegistros();

  Socio leerRegistro(int pos);

  int buscarRegistroDNI(int dni);

  int buscarRegistroIDSocio(int idSocio);

  bool modificarRegistro(Socio reg, int pos);

  bool bajaLogica(int dni);

  int generarNuevoID();

  void listarSociosOrdenadosPorApellido();

  void listarPorApellido(const char* apellidoBuscado);

  bool listarRegistrosActivos();

  bool listarRegistrosInactivos();

  void listarPorMembresia(int idMembresiaBuscada);

  void buscarMembresiaPorNombre(const char* nombreMembresia);

  void listarRegistrosPorObjetivo(const char* objetivoBuscado);

  void generarReportePorObjetivo();

  void reporteCantSociosActivosInactivos();

  void reporteCantSociosPorMembresia();
};
