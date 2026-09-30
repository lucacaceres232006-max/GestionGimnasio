#include <iostream>
#include <ctime>
#include "Fecha.h"

using namespace std;
///no utilizo setters porque YO pongo los datos
Fecha::Fecha()
    : _dia(1), _mes(1), _anio(2026), _hora(0), _minuto(0), _segundo(0) {} ///lista de inicializacion


Fecha::Fecha(int d,int m, int a)
{
    ///inicializo por defecto por si la validación falla
    _dia = 1;
    _mes = 1;
    _anio = 2026;
    _hora = 0;
    _minuto = 0;
    _segundo = 0;

    if(esValida(d,m,a))
    {
        _dia=d;
        _mes=m;
        _anio=a;
    }
}

Fecha::Fecha(int d, int m, int a, int h, int mm, int s)
{
    _dia = 1;
    _mes = 1;
    _anio = 2026;
    _hora = 0;
    _minuto = 0;
    _segundo = 0;

    if(esValida(d,m,a))
    {
        _dia=d;
        _mes=m;
        _anio=a;

        setHora(h);
        setMinuto(m);
        setSegundo(s);
    }

}


///SETTERS Y GETTERS
void Fecha::setDia(int dia)
{
    if(dia>=1 && dia <=31)
    {
        _dia=dia;
    }

}
int Fecha::getDia()
{
    return _dia;
}
void Fecha::setMes(int mes)
{
    if(mes>=1 && mes <=12)
    {
        _mes=mes;
    }
}
int Fecha::getMes()
{
    return _mes;
}
void Fecha::setAnio(int anio)
{
    if(anio >=1980 && anio<=2030)
    {
        _anio=anio;
    }
}
int Fecha::getAnio()
{
    return _anio;
}
void Fecha::setHora(int hora)
{
    if(hora >= 0 && hora <= 23)
    {
        _hora = hora;
    }
}

int Fecha::getHora()
{
    return _hora;
}

void Fecha::setMinuto(int minuto)
{
    if(minuto >= 0 && minuto <= 59)
    {
        _minuto = minuto;
    }
}

int Fecha::getMinuto()
{
    return _minuto;
}

void Fecha::setSegundo(int segundo)
{
    if(segundo >= 0 && segundo <= 59)
    {
        _segundo = segundo;
    }
}

int Fecha::getSegundo()
{
    return _segundo;
}
/// Evalúa el año recibido por parámetro o el del objeto si no se envía nada
bool Fecha::bisiesto(int anio)
{
    int anioAcalcular;

    if(anio != -1)
    {
        anioAcalcular=anio;
    }
    else
    {
        anioAcalcular=_anio;
    }

    if(anioAcalcular % 4!=0) return false;
    if(anioAcalcular % 100 != 0) return true;
    if(anioAcalcular % 400 ==0) return true;

    return false;
}
///Valida si una combinación de día, mes y año es real
bool Fecha::esValida(int d,int m,int a)
{

    if(a < 1780 || a > 2030)
    {
        return false;
    }

    if(m < 1 || m > 12)
    {
        return false;
    }

    if(d < 1)
    {
        return false;
    }

    /// Febrero
    if(m == 2)
    {

        if(bisiesto(a))
        {
            ///Si es bisiesto, maximo 29 días
            if(d <= 29)
            {
                return true;
            }
            else
            {
                return false;
            }

        }
        else
        {
            ///No es bisiesto, máximo 28 días
            if(d <= 28)
            {
                return true;
            }
            else
            {
                return false;
            }

        }
    }

    /// Meses de 30 dias
    if(m == 4 || m == 6 || m == 9 || m == 11)
    {

        if(d <= 30)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// Meses de 31 dias
    if(d <= 31)
    {
        return true;
    }
    else
    {
        return false;
    }
}

///METODOS
void Fecha::cargaManualFecha()
{
    int d,m,a;

    cout << "Ingrese dia: ";
    cin >> d;
    cout<< "Ingrese mes: ";
    cin >> m;
    cout << "Ingrese anio: ";
    cin >> a;

    if(esValida(d,m,a))
    {
        _dia=d;
        _mes=m;
        _anio=a;

        _hora = 0;
        _minuto = 0;
        _segundo = 0;
    }

    else
    {
        cout << "Fecha o hora invalida " << endl;
    }

}
void Fecha::cargaManualTiempo()
{
    int h, mm, s;

    cout << "Ingrese hora: ";
    cin >> h;
    cout << "Ingrese minuto: ";
    cin >> mm;
    cout << "Ingrese segundo: ";
    cin >> s;

    if(h >= 0 && h <= 23 && mm >= 0 && mm <= 59 && s >= 0 && s <= 59)
    {
        _dia = 0;
        _mes = 0;
        _anio = 0;

        _hora = h;
        _minuto = mm;
        _segundo = s;
    }
    else
    {
        cout << "Hora invalida. Los valores ingresados estan fuera de rango. " << endl;
    }
}

// Carga automática utilizando el reloj del sistema de la PC
void Fecha::cargarFechaActualAutomatica()
{
    //Captura el tiempo actual en formado crudo
    std::time_t t = std::time(nullptr);
    //Convierte ese tiempo a una estructura legible
    std::tm* now = std::localtime(&t);

    //Paso los datos de la estructura a los atributos de mi clase
    _dia = now->tm_mday;
    _mes = now->tm_mon + 1;       // tm_mon va de 0 a 11
    _anio = now->tm_year + 1900;  // tm_year cuenta los años desde 1900
    _hora = now->tm_hour;
    _minuto = now->tm_min;
    _segundo = now->tm_sec;
}

void Fecha::mostrar()
{
    cout << _dia << "-" << _mes << "-" << _anio << endl
         << _hora << ":" << _minuto << ":" << _segundo << endl;
}
void Fecha::mostrarConBarra()
{
    cout << _dia << "/" << _mes << "/" << _anio << endl
         << _hora << ":" << _minuto << ":" << _segundo << endl;
}
void Fecha::mostrarConBarraSinHoraMinuto()
{
    cout << _dia << "/" << _mes << "/" << _anio << endl;
}
void Fecha :: mostrarSoloHora()
{
    cout << _hora << ":" << _minuto  << endl;
}
