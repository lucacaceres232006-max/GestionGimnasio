#include <iostream>
#include <cstring>
#include <cstdio>
#include "InstructoresArchivo.h"

using namespace std;

InstructorArchivo::InstructorArchivo(const char *nombre)
{
    strcpy(_nombre, nombre);
}

bool InstructorArchivo::guardarRegistro(Instructor reg)
{
    FILE *pReg = fopen(_nombre, "ab");

    if(pReg == nullptr) return false;

    bool escribio = fwrite(&reg, sizeof(Instructor), 1, pReg);

    fclose(pReg);

    return escribio;
}

int InstructorArchivo::cantidadRegistros()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return 0;

    fseek(pReg, 0, SEEK_END);

    int cantidad = ftell(pReg) / sizeof(Instructor);

    fclose(pReg);

    return cantidad;
}

Instructor InstructorArchivo::leerRegistro(int pos)
{
    Instructor reg;

    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return reg;

    fseek(pReg, pos * sizeof(Instructor), SEEK_SET);

    fread(&reg, sizeof(Instructor), 1, pReg);

    fclose(pReg);

    return reg;
}

int InstructorArchivo::buscarRegistro(int idInstructor)
{
    Instructor reg;

    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return -1;

    int pos = 0;

    while(fread(&reg, sizeof(Instructor), 1, pReg) == 1)
    {
        if(reg.getIdInstructor() == idInstructor)
        {
            fclose(pReg);
            return pos;
        }

        pos++;
    }

    fclose(pReg);

    return -1;
}

bool InstructorArchivo::modificarRegistro(Instructor reg, int pos)
{
    FILE *pReg = fopen(_nombre, "rb+");

    if(pReg == nullptr) return false;

    fseek(pReg, pos * sizeof(Instructor), SEEK_SET);

    bool escribio = fwrite(&reg, sizeof(Instructor), 1, pReg);

    fclose(pReg);

    return escribio;
}

bool InstructorArchivo::bajaLogica(int idInstructor)
{
    Instructor reg;

    int pos = buscarRegistro(idInstructor);

    if(pos == -1)
    {
        return false;
    }

    reg = leerRegistro(pos);

    reg.setActivo(false);

    return modificarRegistro(reg, pos);
}

void InstructorArchivo::listarRegistros()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Instructor reg;

    while(fread(&reg, sizeof(Instructor), 1, pReg) == 1)
    {
        reg.Mostrar();
        cout << endl;
    }

    fclose(pReg);
}
