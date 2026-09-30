#pragma once
#include "Fecha.h"
#include "SocioArchivo.h"
#include "Socios.h"

class Pago
{
private:
    int _idPago;
    int _dniSocio;
    int _idMembresia;
    int _estadoPago;
    Fecha _fechaPago;
    float _recargo;
    int _metodoPago;
    float _importe;

public:
    Pago();

    void Cargar();
    void Mostrar();

void setIdPago(int id);
int getIdPago();


bool setDniSocio(int dni);
int getdniSocio();

void setIdMembresia(int id);
int getIdMembresia();

void setEstadoPago(int estado);
int getEstadoPago();

void setRecargo(float recargo);
float getRecargo();

void setMetodoPago(int metodo);
int getMetodoPago();

void setFechaPago(Fecha fecha);
Fecha getFechaPago();

bool setImporte(float importe);
float getImporte() const;
};
