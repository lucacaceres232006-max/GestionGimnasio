#include <iostream>
#include <cstring>
#include "ClaseArchivo.h"
#include "InscripcionArchivo.h"
#include "Inscripcion.h"

using namespace std;

ClaseArchivo::ClaseArchivo(const char *nombre)
{
    strcpy(_nombre, nombre);
}

bool ClaseArchivo::guardarRegistro(Clase reg)
{
    FILE *p = fopen(_nombre, "ab");
    if(p == nullptr) return false;
    bool ok = fwrite(&reg, sizeof(Clase), 1, p);
    fclose(p);

    return ok;
}

int ClaseArchivo::cantidadRegistros()
{
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Clase);
}

Clase ClaseArchivo::leerRegistro(int pos)
{
    Clase reg;
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return reg;
    fseek(p, pos * sizeof(Clase), SEEK_SET);
    fread(&reg, sizeof(Clase), 1, p);
    fclose(p);

    return reg;
}

int ClaseArchivo::buscarRegistro(int idClase)
{
    Clase reg;
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return -1;
    int pos = 0;
    while(fread(&reg, sizeof(Clase), 1, p) == 1)
    {
        if(reg.getIdClase() == idClase)
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

bool ClaseArchivo::modificarRegistro(Clase reg, int pos)
{
    FILE *p = fopen(_nombre, "rb+");
    if(p == nullptr) return false;
    fseek(p, pos * sizeof(Clase), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Clase), 1, p);
    fclose(p);
    return ok;
}

bool ClaseArchivo::bajaLogica(int idClase)
{
    int pos = buscarRegistro(idClase);
    if(pos == -1) return false;
    Clase reg = leerRegistro(pos);
    reg.setActivo(false);
    return modificarRegistro(reg, pos);
}

void ClaseArchivo::listarRegistrosActivos()
{
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return;
    Clase reg;
    bool activas = true;
    while(fread(&reg, sizeof(Clase), 1, p) == 1)
    {
        if(reg.getActivo())
        {
            reg.Mostrar();
            cout << endl;
        }
    }
    fclose(p);
    if (!activas ){
        cout << "Todas las clases estan inactivas :(" << endl;
    }
}


void ClaseArchivo::listarTodos()
{
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return;
    Clase reg;
    while(fread(&reg, sizeof(Clase), 1, p) == 1)
    {
        reg.Mostrar();
        cout << endl;
    }
    fclose(p);
}


void ClaseArchivo::listarPorNombre(const char* nombre)
{
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return;
    Clase reg;
    while(fread(&reg, sizeof(Clase), 1, p) == 1)
    {
        if(strcmp(reg.getNombreDeClase(), nombre) == 0)
        {
            reg.Mostrar();
            cout << endl;
        }
    }
    fclose(p);
}

void ClaseArchivo::listarPorInstructor(const char* instructor)
{
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return;
    Clase reg;
    while(fread(&reg, sizeof(Clase), 1, p) == 1)
    {
        if(strcmp(reg.getInstructorClase(), instructor) == 0)
        {
            reg.Mostrar();
            cout << endl;
        }
    }
    fclose(p);
}

void ClaseArchivo::listarPorCapacidad(int min)
{
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return;
    Clase reg;
    while(fread(&reg, sizeof(Clase), 1, p) == 1)
    {
        if(reg.getCapacidadMax() >= min)
        {
            reg.Mostrar();
            cout << endl;
        }else{
            cout << "No hay clases con esa capacidad ..." << endl;
        }
    }
    fclose(p);
}



void ClaseArchivo::listarInactivas() {
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return;
    Clase reg;
    bool inactivas = false;
    while(fread(&reg, sizeof(Clase), 1, p) == 1)
    {
        if(!reg.getActivo()){
            reg.Mostrar();
            inactivas=true;
            cout << endl;
        }
    }
    fclose(p);
    if(!inactivas){
        cout << "Estan todas las clases activas ;)" <<endl;
    }
}

void ClaseArchivo::listarPorHorario(int hora) {
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return;

    Clase reg;

    while(fread(&reg, sizeof(Clase), 1, p) == 1) {
            if(reg.getHorarioClase().getHora() == hora) {
                reg.Mostrar();
            cout << endl;
    }
    }
    fclose(p);
}

int ClaseArchivo::contarInscripcionesPorClase(int idClase)
{
    InscripcionArchivo archIns("inscripciones.dat");
    Inscripcion reg;
    int cant = archIns.cantidadRegistros();
    int contador = 0;

    for(int i = 0; i < cant; i++)
    {
        reg = archIns.leerRegistro(i);
        if(reg.getActivo() && reg.getIdClase() == idClase)
        {
            contador++;
        }
    }
    return contador;
}

void ClaseArchivo::reporteMasSolicitadas()
{
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return;

    Clase a, b;

    int cant = cantidadRegistros();

    for(int i = 0; i < cant - 1; i++)
    {
        for(int j = i + 1; j < cant; j++)
        {

            fseek(p, i * sizeof(Clase), SEEK_SET);
            fread(&a, sizeof(Clase), 1, p);

            fseek(p, j * sizeof(Clase), SEEK_SET);
            fread(&b, sizeof(Clase), 1, p);

            int contA = contarInscripcionesPorClase(a.getIdClase());
            int contB = contarInscripcionesPorClase(b.getIdClase());

            if(contB > contA)
            {
                // swap en archivo (releer y reescribir)
                Clase aux = a;

                fseek(p, i * sizeof(Clase), SEEK_SET);
                fwrite(&b, sizeof(Clase), 1, p);

                fseek(p, j * sizeof(Clase), SEEK_SET);
                fwrite(&aux, sizeof(Clase), 1, p);
            }
        }
    }

    fclose(p);
}
void ClaseArchivo::mostrarReporteMasSolicitadas()
{
    FILE *p = fopen(_nombre, "rb");
    if(p == nullptr) return;

    Clase reg;

    int cant = cantidadRegistros();

    for(int i = 0; i < cant; i++)
    {
        fread(&reg, sizeof(Clase), 1, p);

        if(reg.getActivo())
        {
            int total = contarInscripcionesPorClase(reg.getIdClase());

            cout << "Clase: " << reg.getNombreDeClase() << endl;
            cout<< "iinscripciones: " << total << endl;
        }
    }

    fclose(p);
}


