#include <iostream>
#include <cstring>
#include <cstdio>
#include "RutinaArchivo.h"

using namespace std;

RutinaArchivo::RutinaArchivo(const char *nombre)
{
    strcpy(_nombre, nombre);
}

bool RutinaArchivo::guardarRegistro(Rutina reg)
{
    FILE *pReg = fopen(_nombre, "ab");

    if(pReg == nullptr) return false;

    bool escribio = fwrite(&reg, sizeof(Rutina), 1, pReg);

    fclose(pReg);

    return escribio;
}

int RutinaArchivo::cantidadRegistros()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return 0;

    fseek(pReg, 0, SEEK_END);

    int cantidad = ftell(pReg) / sizeof(Rutina);

    fclose(pReg);

    return cantidad;
}

Rutina RutinaArchivo::leerRegistro(int pos)
{
    Rutina reg;

    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return reg;

    fseek(pReg, pos * sizeof(Rutina), SEEK_SET);

    fread(&reg, sizeof(Rutina), 1, pReg);

    fclose(pReg);

    return reg;
}

int RutinaArchivo::buscarRegistro(int idRutina)
{
    Rutina reg;

    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return -1;

    int pos = 0;

    while(fread(&reg, sizeof(Rutina), 1, pReg) == 1)
    {
        if(reg.getId() == idRutina)
        {
            fclose(pReg);
            return pos;
        }

        pos++;
    }

    fclose(pReg);

    return -1;
}

bool RutinaArchivo::modificarRegistro(Rutina reg, int pos)
{
    FILE *pReg = fopen(_nombre, "rb+");

    if(pReg == nullptr) return false;

    fseek(pReg, pos * sizeof(Rutina), SEEK_SET);

    bool escribio = fwrite(&reg, sizeof(Rutina), 1, pReg);

    fclose(pReg);

    return escribio;
}

void RutinaArchivo::listarRegistros()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Rutina reg;

    while(fread(&reg, sizeof(Rutina), 1, pReg) == 1)
    {
        if(reg.getActivo())
        {
            reg.Mostrar();
            cout << endl;
        }
    }

    fclose(pReg);
}

bool RutinaArchivo::bajaLogica(int idRutina)
{
    int pos = buscarRegistro(idRutina);

    if(pos < 0)
    {
        return false;
    }

    Rutina reg = leerRegistro(pos);

    reg.setActivo(false);

    return modificarRegistro(reg, pos);
}
void RutinaArchivo::listarRegistrosActivos()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Rutina reg;

    while(fread(&reg, sizeof(Rutina), 1, pReg) == 1)
    {
        if(reg.getActivo())
        {
            reg.Mostrar();
            cout << endl;
        }
    }

    fclose(pReg);
}
void RutinaArchivo::listarRegistrosInactivos()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Rutina reg;

    while(fread(&reg, sizeof(Rutina), 1, pReg) == 1)
    {
        if(!reg.getActivo())
        {
            reg.Mostrar();
            cout << endl;
        }
    }

    fclose(pReg);
}
void RutinaArchivo::listarPorNivel(const char *nivel)
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Rutina reg;

    while(fread(&reg, sizeof(Rutina), 1, pReg) == 1)
    {
        if(strcmp(reg.getNivel(), nivel) == 0)
        {
            reg.Mostrar();
            cout << endl;
        }
    }

    fclose(pReg);
}
void RutinaArchivo::listarPorTipo(const char *tipo)
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Rutina reg;

    while(fread(&reg, sizeof(Rutina), 1, pReg) == 1)
    {
        if(strcmp(reg.getTipo(), tipo) == 0)
        {
            reg.Mostrar();
            cout << endl;
        }
    }

    fclose(pReg);
}

int RutinaArchivo::buscarIdPorTipo(const char* tipoBuscado)
{
    FILE *pReg = fopen(_nombre, "rb");
    if (pReg == nullptr) return 0;

    Rutina reg;
    while (fread(&reg, sizeof(Rutina), 1, pReg) == 1)
    {
        if (reg.getActivo() && strstr(reg.getTipo(), tipoBuscado) != nullptr)
        {
            fclose(pReg);
            return reg.getId();
        }
    }

    fclose(pReg);
    return 0;
}
