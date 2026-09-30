#include <iostream>
#include <cstring>
#include "Personas.h"
#include "SocioArchivo.h"

using namespace std;
Persona::Persona()
{
    _dni=0;

    strcpy(_nombre,"");
    strcpy(_apellido,"");
    strcpy(_telefono,"");
    strcpy(_email,"");
    _fechaNacimiento = Fecha();
}

///SETTERS Y GETTERS
bool Persona::setDNI(int dni)
{
    if(dni>0)
    {
        _dni=dni;
        return true;
    }
    return false;
}
int Persona::getDNI()
{
    return _dni;
}

void Persona::setNombre(const char *nombre)
{
    if(strlen(nombre)>0 && strlen(nombre)<50)
    {
        strcpy(_nombre, nombre);
    }

}
const char *Persona::getNombre()
{
    return _nombre;
}

void Persona::setApellido(const char *apellido)
{
    if(strlen(apellido)>0 && strlen(apellido)<50)
    {
        strcpy(_apellido, apellido);
    }
}
const char *Persona::getApellido()
{
    return _apellido;
}

void Persona::setFechaNacimiento(Fecha fecha)
{
    if(fecha.getAnio()>=1900 && fecha.getAnio()<2026)
    {
        _fechaNacimiento=fecha;
    }
}
Fecha Persona::getFechaNacimiento()
{
    return _fechaNacimiento;
}

void Persona::setTelefono(const char *telefono)
{
    if(strlen(telefono)>0 && strlen(telefono)<=20)
    {
        strcpy(_telefono,telefono);
    }
}
const char *Persona::getTelefono()
{
    return _telefono;
}

///strchr busca la aparición del @ en el email
void Persona::setEmail(const char *email)
{
    if(strlen(email)>0 && strlen(email)<80 && strchr(email, '@') != nullptr)
    {
        strcpy(_email,email);
    }
}
const char *Persona::getEmail()
{
    return _email;
}

/// MÉTODOS CARGAR Y MOSTRAR
void Persona::Cargar()
{
    int dni=0;
    char nombre[50];
    char apellido[50];
    char telefono[20];
    char email[80];

    cout << "Ingrese DNI: ";
    cin >> dni;
    setDNI(dni);

    cin.ignore();

    cout << "Ingrese nombre: ";
    cin.getline(nombre,50);
    setNombre(nombre);

    cout << "Ingrese apellido: ";
    cin.getline(apellido,50);
    setApellido(apellido);

    cout << "Ingrese fecha de nacimiento";
    cout << endl;
    Fecha auxFecha;
    auxFecha.cargaManualFecha();
    setFechaNacimiento(auxFecha);

    cin.ignore();

    cout << "Ingrese telefono: ";
    cin.getline(telefono,20);
    setTelefono(telefono);

    cout << "Ingrese email: ";
    cin.getline(email,80);
    setEmail(email);

}

void Persona::CargarPersonaSinDNI()
{
    char nombre[50];
    char apellido[50];
    char telefono[20];
    char email[80];

    cout << "Ingrese nombre: ";
    // Si quedó un Enter colgado del menú, lo limpia. Si no, no hace nada.
    if (cin.peek() == '\n') cin.ignore();
    cin.getline(nombre, 50);
    setNombre(nombre);

    cout << "Ingrese apellido: ";
    cin.getline(apellido, 50);
    setApellido(apellido);

    cout << "Ingrese fecha de nacimiento:" << endl;
    Fecha auxFecha;
    auxFecha.cargaManualFecha();
    setFechaNacimiento(auxFecha);

    cout << "Ingrese telefono: ";
    if (cin.peek() == '\n') cin.ignore();
    cin.getline(telefono, 20);
    setTelefono(telefono);

    cout << "Ingrese email: ";
    cin.getline(email, 80);
    setEmail(email);
}

void Persona::Mostrar()
{

    cout << "-----INFORMACION PERSONAL-----" << endl;
    cout << "DNI: " << getDNI() << endl;
    cout << "Nombre y apellido: " << getNombre() << " " << getApellido() << endl;
    cout << "Fecha de nacimiento: ";
    getFechaNacimiento().mostrarConBarraSinHoraMinuto();
    cout << "Telefono: " << getTelefono() << endl;
    cout << "Email: " << getEmail() << endl;
}
