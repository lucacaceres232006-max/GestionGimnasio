#include <iostream>
#include <cstring>
#include "IngresoArchivo.h"

using namespace std;

IngresoArchivo::IngresoArchivo(const char *nombre)
{
    strcpy(_nombre, nombre);
}

bool IngresoArchivo::guardarRegistro(Ingreso reg)
{
    FILE *pReg = fopen(_nombre, "ab");

    if(pReg == nullptr) return false;

    bool escribio = fwrite(&reg, sizeof(Ingreso), 1, pReg);

    fclose(pReg);
    return escribio;
}

int IngresoArchivo::cantidadRegistros()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return 0;

    fseek(pReg, 0, SEEK_END);

    int cantidad = ftell(pReg) / sizeof(Ingreso);

    fclose(pReg);

    return cantidad;
}

Ingreso IngresoArchivo::leerRegistro(int pos)
{
    Ingreso reg;

    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return reg;

    fseek(pReg, pos * sizeof(Ingreso), SEEK_SET);

    fread(&reg, sizeof(Ingreso), 1, pReg);

    fclose(pReg);

    return reg;
}

int IngresoArchivo::buscarRegistro(int idIngreso)
{
    Ingreso reg;

    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return -1;

    int pos = 0;

    while(fread(&reg, sizeof(Ingreso), 1, pReg) == 1)
    {
        if(reg.getIdIngreso() == idIngreso)
        {
            fclose(pReg);
            return pos;
        }

        pos++;
    }

    fclose(pReg);

    return -1;
}

bool IngresoArchivo::modificarRegistro(Ingreso reg, int pos)
{
    FILE *pReg = fopen(_nombre, "rb+");

    if(pReg == nullptr) return false;

    fseek(pReg, pos * sizeof(Ingreso), SEEK_SET);

    bool escribio = fwrite(&reg, sizeof(Ingreso), 1, pReg);

    fclose(pReg);

    return escribio;
}

void IngresoArchivo::listarRegistros()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Ingreso reg;

    while(fread(&reg, sizeof(Ingreso), 1, pReg) == 1)
    {
        reg.Mostrar();
        cout << endl;
    }

    fclose(pReg);
}
void IngresoArchivo::reporteConcurrenciaMensual()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr)
    {
        return;
    }

    int meses[12] = {0};

    Ingreso reg;

    while(fread(&reg, sizeof(Ingreso), 1, pReg) == 1)
    {
        int mes = reg.getFecha().getMes();

        if(mes >= 1 && mes <= 12)
        {
            meses[mes - 1]++;
        }
    }

    fclose(pReg);

    cout << "===== CONCURRENCIA MENSUAL =====" << endl;

    for(int i = 0; i < 12; i++)
    {
        cout << "Mes " << i + 1 << ": "
             << meses[i]
             << " ingresos" << endl;
    }
}
void IngresoArchivo::reporteSociosMayorAsistencia()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr)
    {
        return;
    }

    Ingreso reg;

    const int MAX = 1000;

    int dni[MAX];
    int cantidad[MAX];

    int usados = 0;

    while(fread(&reg, sizeof(Ingreso), 1, pReg) == 1)
    {
        int pos = -1;

        for(int i = 0; i < usados; i++)
        {
            if(dni[i] == reg.getDniSocio())
            {
                pos = i;
                break;
            }
        }

        if(pos == -1)
        {
            dni[usados] = reg.getDniSocio();
            cantidad[usados] = 1;
            usados++;
        }
        else
        {
            cantidad[pos]++;
        }
    }

    fclose(pReg);

    if(usados == 0)
    {
        cout << "No hay ingresos registrados." << endl;
        return;
    }

    int mayor = cantidad[0];

    for(int i = 1; i < usados; i++)
    {
        if(cantidad[i] > mayor)
        {
            mayor = cantidad[i];
        }
    }

    cout << "===== SOCIOS CON MAYOR ASISTENCIA =====" << endl;

    for(int i = 0; i < usados; i++)
    {
        if(cantidad[i] == mayor)
        {
            cout << "DNI: " << dni[i]
                 << " - Asistencias: "
                 << cantidad[i] << endl;
        }
    }
}
bool IngresoArchivo::bajaLogica(int idIngreso)
{
    int pos = buscarRegistro(idIngreso);

    if(pos < 0)
    {
        return false;
    }

    Ingreso reg = leerRegistro(pos);

    reg.setActivo(false);

    return modificarRegistro(reg, pos);
}

void IngresoArchivo::historialActividad()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr)
    {
        return;
    }

    Ingreso reg;

    while(fread(&reg, sizeof(Ingreso), 1, pReg) == 1)
    {
        reg.Mostrar();
        cout << endl;
    }

    fclose(pReg);
}

void IngresoArchivo::listarPorDni(int dni)
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr)
    {
        return;
    }

    Ingreso reg;

    while(fread(&reg, sizeof(Ingreso), 1, pReg) == 1)
    {
        if(reg.getDniSocio() == dni)
        {
            reg.Mostrar();
            cout << endl;
        }
    }

    fclose(pReg);
}
int IngresoArchivo::buscarRegistroDni(int dni)
{
    Ingreso reg;

    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return -1;

    int pos = 0;

    while(fread(&reg, sizeof(Ingreso), 1, pReg) == 1)
    {
        if(reg.getDniSocio() == dni)
        {
            fclose(pReg);
            return pos;
        }

        pos++;
    }

    fclose(pReg);

    return -1;
}
