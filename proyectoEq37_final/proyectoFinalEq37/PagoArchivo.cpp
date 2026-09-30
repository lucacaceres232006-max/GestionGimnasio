#include <iostream>
#include <cstring>
#include <cstdio>
#include "PagoArchivo.h"
#include "MembresiasArchivo.h"
using namespace std;

PagoArchivo::PagoArchivo(const char *nombre)
{
    strcpy(_nombre, nombre);
}

bool PagoArchivo::guardarRegistro(Pago reg)
{
    FILE *pReg = fopen(_nombre, "ab");

    if(pReg == nullptr) return false;

    bool escribio = fwrite(&reg, sizeof(Pago), 1, pReg);

    fclose(pReg);

    return escribio;
}

int PagoArchivo::cantidadRegistros()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return 0;

    fseek(pReg, 0, SEEK_END);

    int cantidad = ftell(pReg) / sizeof(Pago);

    fclose(pReg);

    return cantidad;
}

Pago PagoArchivo::leerRegistro(int pos)
{
    Pago reg;

    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return reg;

    fseek(pReg, pos * sizeof(Pago), SEEK_SET);

    fread(&reg, sizeof(Pago), 1, pReg);

    fclose(pReg);

    return reg;
}

int PagoArchivo::buscarRegistro(int idPago)
{
    Pago reg;

    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return -1;

    int pos = 0;

    while(fread(&reg, sizeof(Pago), 1, pReg) == 1)
    {
        if(reg.getIdPago() == idPago)
        {
            fclose(pReg);
            return pos;
        }

        pos++;
    }

    fclose(pReg);

    return -1;
}

bool PagoArchivo::modificarRegistro(Pago reg, int pos)
{
    FILE *pReg = fopen(_nombre, "rb+");

    if(pReg == nullptr) return false;

    fseek(pReg, pos * sizeof(Pago), SEEK_SET);

    bool escribio = fwrite(&reg, sizeof(Pago), 1, pReg);

    fclose(pReg);

    return escribio;
}

void PagoArchivo::listarRegistros()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Pago reg;

    while(fread(&reg, sizeof(Pago), 1, pReg) == 1)
    {
        reg.Mostrar();
        cout << endl;
    }

    fclose(pReg);
}
bool PagoArchivo::bajaLogica(int idPago)
{
    int pos = buscarRegistro(idPago);

    if(pos < 0)
    {
        return false;
    }

    Pago reg = leerRegistro(pos);

    reg.setEstadoPago(0);

    return modificarRegistro(reg, pos);
}

void PagoArchivo::listarPagados()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Pago reg;

    while(fread(&reg, sizeof(Pago), 1, pReg) == 1)
    {
        if(reg.getEstadoPago() == 1)
        {
            reg.Mostrar();
            cout << endl;
        }
    }

    fclose(pReg);
}

void PagoArchivo::listarPendientes()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Pago reg;

    while(fread(&reg, sizeof(Pago), 1, pReg) == 1)
    {
        if(reg.getEstadoPago() == 0 || reg.getEstadoPago()==2)
        {
            reg.Mostrar();
            cout << endl;
        }
    }

    fclose(pReg);
}

void PagoArchivo::listarPorSocio(int dni)
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr) return;

    Pago reg;

    while(fread(&reg, sizeof(Pago), 1, pReg) == 1)
    {
        if(reg.getdniSocio() == dni)
        {
            reg.Mostrar();
            cout << endl;
        }
    }

    fclose(pReg);
}
void PagoArchivo::reportePagosConRecargo()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr)
    {
        return;
    }

    Pago reg;

    cout << "===== PAGOS CON RECARGO =====" << endl << endl;

    while(fread(&reg, sizeof(Pago), 1, pReg) == 1)
    {
        if(reg.getRecargo() > 0)
        {
            reg.Mostrar();
            cout << "--------------------------" << endl;
        }
    }

    fclose(pReg);
}
void PagoArchivo::reporteRecaudacionPorMetodoPago()
{
    FILE *pReg = fopen(_nombre, "rb");

    if(pReg == nullptr)
    {
        return;
    }

    Pago reg;
    SocioArchivo archSocios("socios.dat");
    MembresiasArchivo archMembresias("membresias.dat");

    float efectivo = 0;
    float debito = 0;
    float credito = 0;

    while(fread(&reg, sizeof(Pago), 1, pReg) == 1)
    {
        if(reg.getEstadoPago() == 1)
        {
            int posSocio = archSocios.buscarRegistroDNI(reg.getdniSocio());

            if(posSocio == -1)
            {
                continue; //termina la iteracion actual del while
            }

            Socio socio = archSocios.leerRegistro(posSocio);

            int posMembresia = archMembresias.buscarRegistroIDMembresia(socio.getIdMembresia());

            if(posMembresia == -1)
            {
                continue;
            }

            Membresias membresia = archMembresias.leerRegistro(posMembresia);

            float importe = membresia.getPrecio() + reg.getRecargo();

            switch(reg.getMetodoPago())
            {
            case 0:
                efectivo += importe;
                break;

            case 1:
                debito += importe;
                break;

            case 2:
                credito += importe;
                break;
            }
        }
    }

    fclose(pReg);

    cout << "===== RECAUDACION POR METODO DE PAGO =====" << endl;
    cout << "Efectivo: $" << efectivo << endl;
    cout << "Debito:   $" << debito << endl;
    cout << "Credito:  $" << credito << endl;
    cout << "Total:    $" << efectivo + debito + credito << endl;
}
