#include <iostream>
#include "Inscripcion.h"
using namespace std;

Inscripcion::Inscripcion() {
    _idInscripcion = 0;
    _dniSocio = 0;
    _idClase = 0;
    _activo = false;
}

void Inscripcion::setIdInscripcion(int idInscripcion) {
    _idInscripcion = idInscripcion;
}

void Inscripcion::setDniSocio(int dniSocio) {
    _dniSocio = dniSocio;
}

void Inscripcion::setFechaInscripcion(Fecha fechaInscripcion) {
    _fechaInscripcion = fechaInscripcion;
}

void Inscripcion::setIdClase(int idClase) {
    _idClase = idClase;
}

void Inscripcion::setActivo(bool activo) {
    _activo = activo;
}

int Inscripcion::getIdInscripcion() {
    return _idInscripcion;
}

int Inscripcion::getDniSocio() {
    return _dniSocio;
}

Fecha Inscripcion::getFechaInscripcion() {
    return _fechaInscripcion;
}

int Inscripcion::getIdClase() {
    return _idClase;
}

bool Inscripcion::getActivo() {
    return _activo;
}

void Inscripcion::Cargar() {
    cout << "DNI del socio: ";
    cin >> _dniSocio;

    cout << "ID de la clase: ";
    cin >> _idClase;

    _fechaInscripcion.cargarFechaActualAutomatica();

    _activo = true;
}

void Inscripcion::Mostrar() {
    cout << "ID Inscripcion: " << _idInscripcion << endl;
    cout << "DNI Socio: " << _dniSocio << endl;
    cout << "ID Clase: " << _idClase << endl;
    cout << "Fecha de inscripcion: ";
    _fechaInscripcion.mostrarConBarra();
    cout << "Estado: ";
    if(_activo) {
        cout << "Activo" << endl;
    }
    else {
        cout << "Inactivo" << endl;
    }
}
