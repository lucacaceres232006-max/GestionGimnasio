#pragma once

class Fecha
{

private:
    int _dia, _mes, _anio;
    int _hora, _minuto, _segundo;

public:
    ///CONSTRUCTOR
    Fecha();
    Fecha(int d, int m, int a);
    Fecha(int d, int m, int a, int h, int mm, int s);

    ///SETTERS Y GETTERS
    void setDia(int dia);
    int getDia();
    void setMes(int mes);
    int getMes();
    void setAnio(int anio);
    int getAnio();
    void setHora(int hora);
    int getHora();
    void setMinuto(int minuto);
    int getMinuto();
    void setSegundo(int segundo);
    int getSegundo();

    ///METODOS
    void cargaManualFecha();
    void cargaManualTiempo();
    void cargarFechaActualAutomatica();
    void mostrar();
    void mostrarConBarra();
    void mostrarConBarraSinHoraMinuto();
    bool bisiesto(int anio= -1);
    bool esValida(int d,int m, int a);
    void mostrarSoloHora ();
};
