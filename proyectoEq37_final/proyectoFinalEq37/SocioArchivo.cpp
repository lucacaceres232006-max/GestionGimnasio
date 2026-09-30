#include <iostream>
#include <cstring>
#include "SocioArchivo.h"
#include "Membresias.h"
#include "MembresiasArchivo.h"
using namespace std;

SocioArchivo::SocioArchivo(const char *nombre, bool vacio)
{
    strcpy(_nombre, nombre);

    if(vacio)
    {
        FILE *pReg;
        pReg=fopen(_nombre,"wb");

        if(pReg==nullptr)
        {
            cout << "Error de archivo ";
            return;
        }
        fclose(pReg);
    }
}

bool SocioArchivo::guardarRegistro(Socio reg)
{
    FILE *pReg;

    pReg=fopen(_nombre,"ab");

    if(pReg==nullptr)
    {
        cout << "Error de archivo ";
        return false;
    }

    bool escribio = fwrite(&reg,sizeof(Socio),1, pReg);

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

int SocioArchivo::cantidadRegistros()
{
    FILE *pReg;
    int bytes;

    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        return -1;
    }

    fseek(pReg,0,SEEK_END);
    bytes=ftell(pReg); //obtiene la posición actual del cursor, que coincide con la cant total de bytes que contiene el archivo
    fclose(pReg);

    return bytes/sizeof(Socio);

}

Socio SocioArchivo::leerRegistro(int pos)
{
    Socio reg;
    FILE *pReg;

    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        cout << "Error de archivo ";
        return reg;
    }

    fseek(pReg, pos * sizeof(Socio), SEEK_SET);
    fread(&reg, sizeof(Socio), 1, pReg);

    fclose(pReg);
    return reg;

}

int SocioArchivo::buscarRegistroDNI(int dni)
{
    Socio reg;
    FILE *pReg;
    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        return -1;
    }

    int posicion=0;

    while(fread(&reg,sizeof reg,1,pReg)==1)
    {

        if(reg.getDNI()==dni)
        {
            fclose(pReg);
            return posicion;
        }

        posicion++;
    }

    fclose(pReg);
    return -1;
}

int SocioArchivo::generarNuevoID()
{
    FILE *pReg = fopen(_nombre, "rb");
    if (pReg == nullptr)
    {
        return 1;
    }

    Socio reg;
    int maxID = 0;

    while (fread(&reg, sizeof(Socio), 1, pReg) == 1)
    {
        if (reg.getIdSocio() > maxID)
        {
            maxID = reg.getIdSocio();
        }
    }

    fclose(pReg);
    return maxID + 1;
}

int SocioArchivo::buscarRegistroIDSocio(int idSocio)
{
    Socio reg;
    FILE *pReg = fopen(_nombre, "rb");

    if (pReg == nullptr)
    {
        return -1;
    }

    int posicion = 0;

    while (fread(&reg,sizeof(Socio), 1, pReg) == 1)
    {
        if (reg.getIdSocio() == idSocio && reg.getActivo() == true)
        {
            fclose(pReg);
            return posicion;
        }
        posicion++;
    }

    fclose(pReg);
    return -1;
}

bool SocioArchivo::modificarRegistro(Socio reg, int pos)
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

bool SocioArchivo::bajaLogica(int dni)
{
    Socio reg;
    FILE *pReg = fopen(_nombre, "rb+");
    if (pReg == nullptr) return false;

    int pos = 0;
    bool seModifico = false;


    while (fread(&reg, sizeof(Socio), 1, pReg) == 1)
    {
        if (reg.getDNI() == dni)
        {
            reg.setActivo(false);

            fseek(pReg, pos * sizeof(Socio),0);

            fwrite(&reg, sizeof(Socio), 1, pReg);
            seModifico = true;
            break;
        }
        pos++;
    }

    fclose(pReg);
    return seModifico;
}

////LISTADOS DE LOS REGISTROS
void SocioArchivo::listarSociosOrdenadosPorApellido()
{

    int cantRegistros = cantidadRegistros();

    if(cantRegistros <= 0)
    {
        cout << "No hay socios para listar " << endl;
        return;
    }

    Socio *vec = new Socio[cantRegistros];

    if(vec == nullptr)
    {
        cout << "Error de asignacion de memoria " << endl;
        return;
    }

    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr)
    {
        cout << "Error de archivo ";
        delete [] vec;
        return;
    }

    int contador = 0;
    Socio reg;

    while(fread(&reg, sizeof(Socio), 1, pReg) == 1)
    {
        if(reg.getActivo())
        {
            vec[contador] = reg;
            contador++;
        }
    }
    fclose(pReg);

    if(contador == 0)
    {
        cout << "No hay socios activos registrados " << endl;
        delete[] vec;
        return;
    }

    // MÉTODO BURBUJA
    Socio aux;
    for(int i = 0; i < contador - 1; i++)
    {
        for(int j = 0; j < contador - i - 1; j++)
        {
            if(strcmp(vec[j].getApellido(), vec[j+1].getApellido()) > 0)
            {
                aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
            }
        }
    }

    for(int k = 0; k < contador; k++)
    {
        vec[k].Mostrar();
        cout << "-----------------------------------" << endl;
    }

    delete[] vec;
}

bool SocioArchivo::listarRegistrosActivos()
{

    Socio reg;
    FILE *pReg;

    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        return false;
    }

    bool encontro=false;

    while(fread(&reg,sizeof reg,1,pReg)!=0)
    {
        if(reg.getActivo()==1)
        {
            reg.Mostrar();
            cout << "-----------------------------------" << endl;
            encontro=true;
        }
    }

    fclose(pReg);

    return encontro;
}

bool SocioArchivo::listarRegistrosInactivos()
{

    Socio reg;
    FILE *pReg;

    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        return false;
    }

    bool encontro=false;

    while(fread(&reg,sizeof reg,1,pReg)!=0)
    {
        if(reg.getActivo()!=1)
        {
            reg.Mostrar();
            cout << "-----------------------------------" << endl;
            encontro=true;
        }
    }

    fclose(pReg);

    return encontro;
}
//BÚSQUEDAS Y CONSULTAS
void SocioArchivo::listarPorApellido(const char* apellidoBuscado)
{
    Socio reg;
    FILE *pReg;

    pReg=fopen(_nombre,"rb");

    if(pReg==nullptr)
    {
        cout << "Error de archivo ";
        return;
    }

    bool encontroAlMenosUno=false;

    while(fread(&reg,sizeof(Socio),1,pReg)==1)
    {

        if(reg.getActivo() && strcmp(reg.getApellido(),apellidoBuscado)==0)
        {
            reg.Mostrar();
            cout << "--------------------------------" << endl;
            encontroAlMenosUno=true;
        }

    }
    fclose(pReg);

    if(encontroAlMenosUno==false)
    {
        cout << "No se encontraron socios con el apellido " << apellidoBuscado << endl;
    }
}

void SocioArchivo::listarPorMembresia(int idMembresiaBuscada)
{

    FILE* pReg = fopen(_nombre, "rb");
    if (pReg == nullptr)
    {
        cout << "Error al abrir el archivo de socios." << endl;
        return;
    }

    Socio reg;

    bool encontroAlMenosUno=false;


    while(fread(&reg,sizeof(Socio),1,pReg)==1)
    {

        if(reg.getActivo()&&reg.getIdMembresia()==idMembresiaBuscada)
        {
            reg.Mostrar();
            cout << "--------------------------------" << endl;
            encontroAlMenosUno=true;
        }
    }
    fclose(pReg);

    if (encontroAlMenosUno == false)
    {
        cout << "No se encontraron socios activos con ese tipo de membresia." << endl;
    }
}

void SocioArchivo::buscarMembresiaPorNombre(const char *nombreMembresia)
{
    FILE* pReg = fopen(_nombre, "rb");
    if (pReg == nullptr)
    {
        cout << "Error al abrir el archivo de socios." << endl;
        return;
    }

    MembresiasArchivo archiMembresias("membresias.dat");

    Socio reg;
    bool encontroAlMenosUno=false;

    cout << " ---- RESULTADOS DE LA BUSQUEDA ---- " << endl;

    while(fread(&reg,sizeof(Socio),1,pReg)==1)
    {
        if(reg.getActivo()==1)
        {
            int posMembr= archiMembresias.buscarRegistroIDMembresia(reg.getIdMembresia());

            if(posMembr != -1)
            {

                Membresias membr = archiMembresias.leerRegistro(posMembr);
                //Compara el nombre de la membresia usando strstr que no distingue cadenas
                if(strstr(membr.getNombre(),nombreMembresia) != nullptr)
                {
                    reg.Mostrar();

                    encontroAlMenosUno=true;
                }
            }
        }
    }

    fclose(pReg);

    if (encontroAlMenosUno == false)
    {
        cout << "No se encontraron socios activos con una membresia que coincida con: \"" << nombreMembresia << "\"" << endl;
    }
}

void SocioArchivo::listarRegistrosPorObjetivo(const char* objetivoBuscado)
{

    Socio reg;
    FILE *pReg;

    pReg=fopen(_nombre,"rb");
    if (pReg == nullptr)
    {
        cout << "Error al abrir el archivo de socios." << endl;
        return;
    }


    bool encontroAlMenosUno=false;


    while(fread(&reg,sizeof(Socio),1,pReg)==1)
    {

        if(reg.getActivo()&&strcmp(reg.getObjetivo(),objetivoBuscado)==0)
        {
            reg.Mostrar();
            cout << "--------------------------------" << endl;
            encontroAlMenosUno=true;
        }
    }
    fclose(pReg);

    if (encontroAlMenosUno == false)
    {
        cout << "No se encontraron socios activos con el objetivo." << endl;
    }

}
void SocioArchivo::generarReportePorObjetivo()
{

    Socio reg;
    FILE *pReg;

    pReg=fopen(_nombre,"rb");
    if (pReg == nullptr)
    {
        cout << "Error al abrir el archivo de socios." << endl;
        return;
    }

    int contGanarMasa=0;
    int contPerderPeso=0;
    int contMantenerEstado=0;


    while(fread(&reg,sizeof reg,1,pReg)==1)
    {

        if(reg.getActivo())
        {

            if(strcmp(reg.getObjetivo(),"Ganar masa muscular")==0)
            {
                contGanarMasa++;
            }
            else if(strcmp(reg.getObjetivo(),"Perder grasa")==0)
            {
                contPerderPeso++;
            }
            else if(strcmp(reg.getObjetivo(),"Mantener el estado fisico")==0)
            {
                contMantenerEstado++;
            }

        }
    }
    fclose(pReg);

    cout << "CANTIDAD DE SOCIOS POR OBJETIVO " << endl;
    cout << "--------------------------------" << endl;
    cout << "Ganar masa muscular: " << contGanarMasa << " socios." << endl;
    cout << "Bajar de peso: " << contPerderPeso << " socios." << endl;
    cout << "Mantener estado fisico: " << contMantenerEstado << " socios." << endl;
}

void SocioArchivo::reporteCantSociosActivosInactivos()
{

    Socio reg;
    FILE *pReg;

    pReg=fopen(_nombre,"rb");
    if (pReg == nullptr)
    {
        cout << "Error al abrir el archivo de socios." << endl;
        return;
    }

    int contSocioActivo=0;
    int contSocioInactivo=0;

    while(fread(&reg,sizeof reg,1,pReg)==1)
    {
        if(reg.getActivo()==true)
        {
            contSocioActivo++;
        }
        else
        {
            contSocioInactivo++;
        }
    }

    fclose(pReg);

    cout << "---- CANTIDAD DE SOCIOS ACTIVOS E INACTIVOS ----" << endl;
    cout << "Socios activos: " << contSocioActivo << endl;
    cout << "Socios inactivos: " << contSocioInactivo << endl;

}

void SocioArchivo::reporteCantSociosPorMembresia()
{
    MembresiasArchivo archiMembresias("membresias.dat");
    int cantMembresias = archiMembresias.cantidadRegistros();

    if (cantMembresias <= 0)
    {
        cout << "No hay membresias registradas para generar el reporte." << endl;
        return;
    }

    Membresias* vecMembresias = new Membresias[cantMembresias];
    int* contadores = new int[cantMembresias];

    if (vecMembresias == nullptr || contadores == nullptr)
    {
        cout << "Error de asignacion de memoria." << endl;
        delete[] vecMembresias;
        delete[] contadores;
        return;
    }

///Inicializo los contadores en 0 y cargo las membresías en mi vector
    for (int i = 0; i < cantMembresias; i++)
    {
        vecMembresias[i] = archiMembresias.leerRegistro(i);
        contadores[i] = 0;
    }

    FILE* pReg = fopen(_nombre, "rb");
    if (pReg == nullptr)
    {
        cout << "Error al abrir el archivo de socios." << endl;
        delete[] vecMembresias;
        delete[] contadores;
        return;
    }

    Socio reg;
    while (fread(&reg, sizeof(Socio), 1, pReg) == 1)
    {
        if (reg.getActivo() == 1)
        {
            for (int j = 0; j < cantMembresias; j++)
            {
                if (vecMembresias[j].getIdMembresia() == reg.getIdMembresia())
                {
                    contadores[j]++;
                    break;
                }
            }
        }
    }
    fclose(pReg);

    cout << "---- CANTIDAD DE SOCIOS POR MEMBRESIA ----" << endl;
    cout << "------------------------------------------" << endl;

    for (int i = 0; i < cantMembresias; i++)
    {
        if (vecMembresias[i].getActivo())
        {
            cout << " " << vecMembresias[i].getNombre()
                 << " (ID " << vecMembresias[i].getIdMembresia() << "): "
                 << contadores[i] << " socios." << endl;
        }
    }

    cout << "------------------------------------------" << endl;
    delete[] vecMembresias;
    delete[] contadores;
}
