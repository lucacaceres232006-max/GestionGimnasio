#include <iostream>
#include <cstring>
#include "Personas.h"
#include "Socios.h"
#include "RutinaArchivo.h"
#include "MembresiasArchivo.h"
using namespace std;

///modifiqué el constructor del socio con lista de inicialización
/// y llamé al constructor de Personas

Socio::Socio() : Persona()
{
    _idSocio = 0;
    _idRutina = 0;
    _idMembresia = 0;
    _activo=0;
    strcpy(_objetivo, "");
}

int Socio::estadoDelSocio()
{

    int opcionEstado;

    cout << "Ingrese el estado actual del Socio: [0] INACTIVO [1] ACTIVO [2] INACTIVO POR DEUDA";
    cin >> opcionEstado;

    switch(opcionEstado)
    {

    case 1:
        _activo=1;
        break;

    case 2:
        _activo=2;
        break;
    case 0:
        _activo=0;
        break;
    }

    return _activo;
}

void Socio::cargarObjetivo()
{
    RutinaArchivo archRutinas("rutinas.dat");
    bool opcionValida=false;
    int opcObjetivo;
    do
    {
        system("cls");
        cout << "---- SELECCIONE EL OBJETIVO DEL SOCIO ----" << endl;
        cout << "1. Ganar masa muscular " << endl;
        cout << "2. Perder grasa/peso " << endl;
        cout << "3. Mantener el estado fisico " << endl;
        cout << "0. Volver " << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Seleccione una opcion: " << endl;
        cin >> opcObjetivo;

        switch(opcObjetivo)
        {

        case 1:
            strcpy(_objetivo,"Ganar masa muscular");
            _idRutina=archRutinas.buscarIdPorTipo("Masa Muscular");
            opcionValida=true;
            break;
        case 2:
            strcpy(_objetivo,"Perder grasa");
            _idRutina=archRutinas.buscarIdPorTipo("Perder Grasa");
            opcionValida=true;
            break;
        case 3:
            strcpy(_objetivo,"Mantener el estado fisico");
            _idRutina=archRutinas.buscarIdPorTipo("Mantener");
            opcionValida=true;
            break;
        case 0:
            return;
            break;

        default:
            cout << "Opcion no valida. Intente de nuevo. " << endl;
            system("pause");
            break;

        }
    }
    while(opcionValida==false);

}

void Socio::Cargar()
{
    Persona::Cargar();

    MembresiasArchivo archiMembresias("membresias.dat");

    system("cls");
    cout << "---- SELECCIONE UNA MEMBRESIA DISPONIBLE ----" << endl;
    archiMembresias.listarRegistrosActivos();

    int idElegido;
    cout << "---------------------------------------------" << endl;
    cout << "Ingrese el ID de la membresia para el socio: ";
    cin >> idElegido;

    while (archiMembresias.buscarRegistroIDMembresia(idElegido) == -1)
    {
        cout << "ID invalido. Seleccione un ID correcto de la lista: ";
        cin >> idElegido;
    }

    setIdMembresia(idElegido);

    if (cin.peek() == '\n') cin.ignore();
    cargarObjetivo();

    setActivo(1);
}
void Socio::CargarSocioSinDNI()
{
    Persona::CargarPersonaSinDNI();

    MembresiasArchivo archiMembresias("membresias.dat");

    system("cls");
    cout << "---- SELECCIONE UNA MEMBRESIA DISPONIBLE ----" << endl;

    archiMembresias.listarRegistrosActivos();

    int idElegido;
    cout << "---------------------------------------------" << endl;
    cout << "Ingrese el ID de la membresia para el socio: ";
    cin >> idElegido;

    while (archiMembresias.buscarRegistroIDMembresia(idElegido) == -1)
    {
        cout << "ID invalido. Seleccione un ID correcto de la lista: ";
        cin >> idElegido;
    }

    setIdMembresia(idElegido);

    if (cin.peek() == '\n') cin.ignore();
    cargarObjetivo();

    setActivo(1);
}

void Socio::Mostrar()
{
    Persona::Mostrar();

    cout << "ID socio: " << _idSocio << endl;
    cout << "ID rutina asginada: " << _idRutina << endl;
    cout << "ID membresia contratada: " << _idMembresia << endl;

    cout << "Objetivo: " << _objetivo << endl;

    cout << "Estado: ";

    if (getActivo() == 1)
    {
        cout << "ACTIVO" << endl;
    }
    else if (getActivo() == 2)
    {
        cout << "INACTIVO POR DEUDA" << endl;
    }
    else
    {
        cout << "INACTIVO" << endl;
    }

}

void Socio::setIdSocio(int idSocio)
{
    if(idSocio>0)
    {
        _idSocio=idSocio;
    }
}
int Socio::getIdSocio()
{
    return _idSocio;
}
void Socio::setIdRutina(int idRutina)
{
    if(idRutina>=0)
    {
        _idRutina=idRutina;
    }
}
int Socio::getIdRutina()
{
    return _idRutina;
}
void Socio::setIdMembresia(int idMembresia)
{
    if(idMembresia>0)
    {
        _idMembresia=idMembresia;
    }
}
int Socio::getIdMembresia()
{
    return _idMembresia;
}
void Socio::setObjetivo(const char* obj)
{
    if(strlen(obj)>0&&strlen(obj)<50)
    {
        strcpy(_objetivo,obj);
    }
}
const char* Socio::getObjetivo()
{
    return _objetivo;
}

void Socio::setActivo(int activo)
{
    if(activo>=0&&activo<=2)
    {
        _activo=activo;
    }
}
int Socio::getActivo()
{
    return _activo;
}
