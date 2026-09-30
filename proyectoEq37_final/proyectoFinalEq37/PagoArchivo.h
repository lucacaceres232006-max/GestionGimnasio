#pragma once
#include "Pago.h"

class PagoArchivo
{
private:
    char _nombre[30];

public:
    PagoArchivo(const char *nombre = "pagos.dat");

    bool guardarRegistro(Pago reg);

    int cantidadRegistros();

    Pago leerRegistro(int pos);

    int buscarRegistro(int idPago);

    bool modificarRegistro(Pago reg, int pos);

    bool bajaLogica(int idPago);

    void listarRegistros();

    void listarPagados();

    void listarPendientes();

    void reportePagosConRecargo();

    void reporteRecaudacionPorMetodoPago();

    void listarPorSocio(int idSocio);
};
