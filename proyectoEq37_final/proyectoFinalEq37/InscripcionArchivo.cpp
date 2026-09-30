#include <iostream>
#include <cstring>
#include "Inscripcion.h"
#include "InscripcionArchivo.h"
#include "ClaseArchivo.h"
#include "Clase.h"

using namespace std;

InscripcionArchivo::InscripcionArchivo(const char *nombre)
{
    strcpy(_nombre, nombre);
}

bool InscripcionArchivo::guardarRegistro(Inscripcion reg)
{
    FILE *pReg = fopen(_nombre, "ab");
    if(pReg == nullptr) return false;
    bool escribio = fwrite(&reg, sizeof(Inscripcion), 1, pReg);
    fclose(pReg);

    return escribio;
}

int InscripcionArchivo::cantidadRegistros()
{
    FILE *pReg = fopen(_nombre, "rb");
    if(pReg == nullptr) return 0;
    fseek(pReg, 0, SEEK_END);
    int cantidad = ftell(pReg) / sizeof(Inscripcion);

    fclose(pReg);
    return cantidad;
}

Inscripcion InscripcionArchivo::leerRegistro(int pos)
{
    Inscripcion reg;
    FILE *pReg = fopen(_nombre, "rb");
    if(pReg == nullptr) return reg;
    fseek(pReg, pos * sizeof(Inscripcion), SEEK_SET);
    fread(&reg, sizeof(Inscripcion), 1, pReg);
    fclose(pReg);
    return reg;
}

int InscripcionArchivo::buscarRegistro(int idInscripcion)
{
    Inscripcion reg;
    FILE *pReg = fopen(_nombre, "rb");
    if(pReg == nullptr) return -1;
    int pos = 0;
    while(fread(&reg, sizeof(Inscripcion), 1, pReg) == 1)
    {
        if(reg.getIdInscripcion() == idInscripcion)
        {
            fclose(pReg);
            return pos;
        }
        pos++;
    }
    fclose(pReg);
    return -1;
}

bool InscripcionArchivo::modificarRegistro(Inscripcion reg, int pos)
{
    FILE *pReg = fopen(_nombre, "rb+");
    if(pReg == nullptr) return false;
    fseek(pReg, pos * sizeof(Inscripcion), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(Inscripcion), 1, pReg);
    fclose(pReg);
    return escribio;
}

bool InscripcionArchivo::bajaLogica(int idInscripcion)
{
    int pos = buscarRegistro(idInscripcion);
    if(pos == -1) return false;
    Inscripcion reg = leerRegistro(pos);
    reg.setActivo(false);

    return modificarRegistro(reg, pos);
}

void InscripcionArchivo::listarRegistrosActivos()
{
    FILE *pReg = fopen(_nombre, "rb");
    if(pReg == nullptr) return;
    Inscripcion reg;
    while(fread(&reg, sizeof(Inscripcion), 1, pReg) == 1)
    {
        if(reg.getActivo())
        {
            reg.Mostrar();
            cout << endl;
        }
    }
    fclose(pReg);
}

bool InscripcionArchivo::yaEstaInscripto(int dni, int idClase)
{
    FILE *p = fopen(_nombre, "rb");

    if(p == nullptr)
    {
        return false;
    }

    Inscripcion reg;

    while(fread(&reg, sizeof(Inscripcion), 1, p))
    {
        if(reg.getActivo() &&
                reg.getDniSocio() == dni &&
                reg.getIdClase() == idClase)
        {
            fclose(p);
            return true;
        }
    }

    fclose(p);
    return false;
}
