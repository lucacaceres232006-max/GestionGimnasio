#include <iostream>
#include "MembresiasArchivo.h"
#include "Socios.h"
#include <cstring>
#include "MembresiasArchivo.h"
using namespace std;

MembresiasArchivo::MembresiasArchivo(const char* nombreArchivo)
{
    strcpy(_nombre, nombreArchivo);
}

bool MembresiasArchivo::guardarRegistro(Membresias reg)
{
    FILE *pReg;

    pReg=fopen(_nombre,"ab");

    if(pReg==nullptr)
    {
        cout << "Error de archivo ";
        return false;
    }

    bool escribio = fwrite(&reg,sizeof reg,1, pReg);

    if(escribio==true)
    {
        cout << "El registro se ha guardado correctamente. " << endl;
    }
    else
    {
        cout << "No se pudo guardar el registro. " << endl;
    }

    fclose(pReg);
    return escribio;
}

int MembresiasArchivo::cantidadRegistros()
{

    FILE *pReg;
    int bytes;

    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        cout << "Error de archivo. " << endl;
        return 0;
    }

    fseek(pReg,0,SEEK_END);
    bytes=ftell(pReg); //obtiene la posición actual del cursor, que coincide con la cant total de bytes que contiene el archivo
    fclose(pReg);

    return bytes/sizeof(Membresias);

}

Membresias MembresiasArchivo::leerRegistro(int pos)
{
    Membresias reg;
    FILE *pReg;

    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        cout << "Error de archivo ";
        return reg;
    }

    fseek(pReg,pos*sizeof reg,0);
    fread(&reg,sizeof reg,1,pReg);

    fclose(pReg);
    return reg;

}

int MembresiasArchivo::generarNuevoID()
{
    FILE *pReg = fopen(_nombre, "rb");
    if (pReg == nullptr)
    {
        return 1;
    }

    Membresias reg;
    int maxID = 0;

    while (fread(&reg, sizeof(Membresias), 1, pReg) == 1)
    {
        if (reg.getIdMembresia() > maxID)
        {
            maxID = reg.getIdMembresia();
        }
    }

    fclose(pReg);
    return maxID + 1;
}

int MembresiasArchivo::buscarRegistroIDMembresia(int idMembresia)
{
    Membresias reg;
    FILE *pReg;
    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        return -1;
    }

    int posicion=0;

    while(fread(&reg,sizeof reg,1,pReg)==1)
    {

        if(reg.getIdMembresia()==idMembresia && reg.getActivo()==true)
        {
            fclose(pReg);
            return posicion;
        }

        posicion++;
    }

    fclose(pReg);
    return -1;
}

bool MembresiasArchivo::modificarRegistro(Membresias reg, int pos)
{
    FILE *pReg;

    pReg=fopen(_nombre,"rb+");

    if(pReg==nullptr)
    {
        cout << "Error de archivo ";
        return false;
    }

    fseek(pReg,pos*sizeof reg,0);

    bool escribio= fwrite(&reg,sizeof reg,1,pReg);

    if(escribio)
    {
        cout << "Registro modificado correctamente. " << endl;
    }
    else
    {
        cout << "Error. Registro no modificado. " << endl;
    }

    fclose(pReg);
    return escribio;

}
bool MembresiasArchivo::bajaLogica(int idMembresia)
{
    Membresias reg;

    int pos= buscarRegistroIDMembresia(idMembresia);

    if(pos== -1)
    {
        cout << "El ID no existe.. Saliendo del proceso. " << endl;
        system("pause");
        return false;
    }

    reg=leerRegistro(pos);
    reg.setActivo(false);

    return modificarRegistro(reg,pos);

}
void MembresiasArchivo::listarRegistrosActivos()
{
    Membresias reg;
    FILE *pReg;

    pReg = fopen(_nombre, "rb");
    if (pReg == nullptr)
    {
        cout << "Error de archivo " << endl;
        return;
    }

    bool hayRegistros = false;

    while (fread(&reg, sizeof(Membresias), 1, pReg) == 1)
    {
        if (reg.getActivo() == true)
        {
            reg.Mostrar();
            cout << "---------------------------" << endl;
            hayRegistros = true;
        }
    }

    fclose(pReg);

    if (!hayRegistros)
    {
        cout << "No hay membresias activas registradas en el archivo." << endl;
    }
}

void MembresiasArchivo::consultarMembresiaPorNombre(const char* nombreBuscado)
{

    Membresias reg;
    FILE *pReg;
    bool encontro=false;

    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        cout << "Error de archivo ";
        return;
    }

    while(fread(&reg,sizeof reg,1,pReg)==1)
    {
        if(reg.getActivo()&&strcmp(reg.getNombre(),nombreBuscado)==0)
        {
            reg.Mostrar();
            cout << "---------------------------" << endl;
            encontro=true;
        }
    }
    fclose(pReg);

    if(encontro==false)
    {
        cout << "No se encontraron membresias activas con el nombre: " << nombreBuscado << endl;
    }
}

void MembresiasArchivo::consultarMembresiaPorPrecio(int precio)
{

    Membresias reg;
    FILE *pReg;
    bool encontro=false;

    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        cout << "Error de archivo ";
        return;
    }

    cout << "Planes con precio igual a: " << precio << endl;
    cout << endl;

    while(fread(&reg,sizeof reg,1,pReg)==1)
    {

        if(reg.getActivo()&& reg.getPrecio()==precio)
        {
            reg.Mostrar();
            cout << "---------------------------" << endl;
            encontro=true;
        }
    }

    if(encontro==false)
    {

        cout << "No existe ninguna membresia activa con el precio exacto de: $" << precio << endl;
    }
}
