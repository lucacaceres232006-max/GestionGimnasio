#include <iostream>
#include "Pago.h"


using namespace std;

Pago::Pago()
{
    _idPago = 0;
    _dniSocio = 0;
    _idMembresia = 0;
    _estadoPago = 0;
    _recargo = 0;
    _metodoPago = 0;
    _importe = 0;
}

void Pago::Cargar()
{
    Socio socio;

    cout << "DNI del socio: ";
    cin >> _dniSocio;

    cout << "Estado (0 Pendiente - 1 Pagado): ";
    cin >> _estadoPago;

    while(_estadoPago != 0 && _estadoPago != 1)
    {
        cout << "Estado invalido. Ingrese 0 o 1: ";
        cin >> _estadoPago;
    }

    if(_estadoPago==1)
    {

        int metodo;

        cout << "Seleccione metodo de pago" << endl;
        cout << "1 - Efectivo" << endl;
        cout << "2 - Debito" << endl;
        cout << "3 - Credito" << endl;
        cout << "Opcion: ";
        cin >> metodo;

        while(metodo < 1 || metodo > 3)
        {
            cout << "Opcion invalida. Ingrese nuevamente: ";
            cin >> metodo;
        }

        _metodoPago = metodo - 1;

        _fechaPago.cargarFechaActualAutomatica();
    }else{
        //No existe método de pago todavía
        _metodoPago= -1;
    }

    if(_estadoPago == 0)
    {
        _recargo = 100;
    }
    else
    {
        _recargo = 0;
    }
}

void Pago::Mostrar()
{
    cout << "ID Pago: " << _idPago << endl;
    cout << "DNI Socio: " << _dniSocio << endl;
    cout << "Importe: $" << _importe << endl;

    cout << endl;
    cout << "Estado: ";

    if(_estadoPago==1)
    {
        cout << "PAGADO" << endl;
    }
    else
    {
        cout << "PENDIENTE" << endl;
    }
    cout << "Recargo: $" << _recargo << endl;
    cout << "Metodo: ";

    switch(_metodoPago)
    {
    case 0:
        cout << "Efectivo";
        break;
    case 1:
        cout << "Debito";
        break;
    case 2:
        cout << "Credito";
        break;
    default:
        cout << "Sin pago realizado";
    }

    cout << endl;

    cout << "Fecha de pago: ";
    _fechaPago.mostrarConBarra();
}

// ===== GETTERS Y SETTERS (UNA SOLA VEZ) =====

void Pago::setIdPago(int id)
{
    if (id > 0) _idPago = id;
}

int Pago::getIdPago()
{
    return _idPago;
}

bool Pago::setDniSocio(int dni)
{
    if(dni > 0)
    {
        _dniSocio = dni;
        return true;
    }
    return false;
}

int Pago::getdniSocio()
{
    return _dniSocio;
}

void Pago::setIdMembresia(int id)
{
    if (id > 0) _idMembresia = id;
}

int Pago::getIdMembresia()
{
    return _idMembresia;
}

void Pago::setEstadoPago(int estado)
{
    _estadoPago = estado;
}

int Pago::getEstadoPago()
{
    return _estadoPago;
}

void Pago::setRecargo(float recargo)
{
    if (recargo >= 0) _recargo = recargo;
}

float Pago::getRecargo()
{
    return _recargo;
}

void Pago::setMetodoPago(int metodo)
{
    _metodoPago = metodo;
}

int Pago::getMetodoPago()
{
    return _metodoPago;
}

void Pago::setFechaPago(Fecha fecha)
{
    _fechaPago = fecha;
}

Fecha Pago::getFechaPago()
{
    return _fechaPago;
}

bool Pago::setImporte(float importe)
{
    if(importe >= 0)
    {
        _importe = importe;
        return true;
    }
    return false;
}
float Pago::getImporte() const
{
    return _importe;
}
