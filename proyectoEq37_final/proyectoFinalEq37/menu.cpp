#include <iostream>
#include "menu.h"
#include "SocioArchivo.h"
#include "MembresiasArchivo.h"
#include "Membresias.h"
#include "Rutina.h"
#include "RutinaArchivo.h"
#include "Ingreso.h"
#include "IngresoArchivo.h"
#include "Pago.h"
#include "PagoArchivo.h"
#include "InscripcionArchivo.h"
#include "ClaseArchivo.h"
#include <limits>

using namespace std;

void menuPrincipal()
{

    int opcion;
    do
    {
        system("cls");
        cout << "------UTN FITNESS-------" << endl;
        cout << "1. Gestion de socios. " << endl;
        cout << "2. Gestion de membresias. " << endl;
        cout << "3. Gestion de rutinas. " << endl;
        cout << "4. Gestion de ingresos." << endl;
        cout << "5. Gestion de pagos." << endl;
        cout << "6. Gestion de clases. " <<endl;
        cout << "7. Gestion de inscripciones. " << endl;
        cout << "8. Reportes del sistema. " << endl;
        cout << "0. Salir del programa. " << endl;
        cout << "------------------------" << endl;
        cout << "Seleccione una opcion: " << endl;

        cin >> opcion;

        system("pause");

        switch(opcion)
        {
        case 1:
            menuSocios();
            break;
        case 2:
            menuMembresias();
            break;
        case 3:
            menuRutinas();
            break;
        case 4:
            menuIngresos();
            break;
        case 5:
            menuPagos();
            break;
        case 6:
            menuClases();
            break;
        case 7:
            menuInscripciones();
            break;
        case 8:
            menuReportes();
            break;
        case 0:
            cout << "Saliendo del sistema... Hasta luego" << endl;
            cout << endl;
            return;
        default:
            cout << "Opcion incorrecta ... " << endl;
            system("pause");
            break;

        }


    }
    while(opcion!=0);
}

void menuMembresias()
{

    MembresiasArchivo archiMembresias("membresias.dat");

    int opcion;
    do
    {
        system("cls");
        cout << "------MENU MEMBRESIAS------" << endl;
        cout << "1. Registrar/Guardar membresia(Alta)." << endl;
        cout << "2. Listar todas las membresias activas." << endl;
        cout << "3. Consultar membresia por nombre." << endl;
        cout << "4. Consultar membresia por precio." << endl;
        cout << "5. Actualizar el precio de un plan." << endl;
        cout << "6. Dar de baja a una membresia. " << endl;
        cout << "0. Volver al menu principal." << endl;
        cout << "---------------------------" << endl;
        cin >> opcion;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion=-1;
        }

        system("cls");

        switch(opcion)
        {
        case 1:
        {
            system("cls");

            cout << " ---- ALTA NUEVA MEMBRESIA ---- " << endl;
            cout << "--------------------------------" << endl;

            Membresias nuevaMembresia;

            int nuevoID=archiMembresias.generarNuevoID();
            nuevaMembresia.setIdMembresia(nuevoID);

            nuevaMembresia.Cargar();

            cout << "Asignando ID de Membresia automatica: [ " << nuevoID << " ]" << endl;

            bool guardo= archiMembresias.guardarRegistro(nuevaMembresia);


            if(guardo)
            {
                cout << "Membresia " << "'" <<nuevaMembresia.getNombre() << "'" <<" registrada correctamente " << endl;
            }
            else
            {
                cout << "Error. No se puedo escribir en el archivo 'membresias.dat'" << endl;
            }


            system("pause");
            break;
        }
        case 2:
        {
            system("cls");
            cout << "---- LISTADO DE MEMBRESIAS ACTIVAS ----" << endl;
            archiMembresias.listarRegistrosActivos();
            system("pause");
            break;
        }
        case 3:
        {
            system("cls");
            char nombreBuscar[30];
            cout << "---- CONSULTA POR NOMBRE ----" << endl;
            cout << "Ingrese el nombre de la membresia a consultar (Basica/Full): ";

            //Limpio el buffer antes de usar getline
            if (cin.peek() == '\n') cin.ignore();
            cin.getline(nombreBuscar, 30);

            archiMembresias.consultarMembresiaPorNombre(nombreBuscar);
            system("pause");
            break;
        }
        case 4:
        {
            system("cls");

            float precioBuscar;

            cout << "---- CONSULTA POR PRECIO ----" << endl;
            cout << "Ingrese el precio exacto a consultar (Ej: 25000 0 40000) $";
            cin >> precioBuscar;

            archiMembresias.consultarMembresiaPorPrecio(precioBuscar);
            system("pause");
            break;
        }
        case 5:
        {

            system("cls");
            int idModificar;

            cout << "---- ACTUALIZAR PRECIO ----" << endl;
            cout << "Ingrese el ID de la membresia a modificar: ";
            cin >> idModificar;

            int pos= archiMembresias.buscarRegistroIDMembresia(idModificar);

            if(pos != -1)
            {
                Membresias regAux = archiMembresias.leerRegistro(pos);
                float nuevoPrecio;

                cout << "Membresia seleccionada: " << regAux.getNombre() << endl;
                cout << "Precio actual: $" << regAux.getPrecio() << endl;
                cout << "Ingrese el nuevo precio: ";
                cin >> nuevoPrecio;


                if(regAux.setPrecio(nuevoPrecio))
                {
                    archiMembresias.modificarRegistro(regAux,pos);
                    cout << "Precio actualizado correctamente. " << endl;
                }
                else
                {
                    cout << "El precio debe ser mayor a 0. Vuelva a intentarlo." << endl;
                }
            }
            else
            {
                cout << "ID de membresia no encontrado. " << endl;
            }
            system("pause");
            break;

        }
        case 6:
        {

            Membresias reg;
            int idMembresia;
            int opcion;
            cout << "Ingrese el ID de la membresia que desea borrar: ";
            cin >> idMembresia;

            int pos = archiMembresias.buscarRegistroIDMembresia(idMembresia);

            if(pos == -1)
            {
                cout << "El registro no existe. " << endl;
            }
            else
            {
                reg=archiMembresias.leerRegistro(pos);

                cout << "Desea eliminar el ID membresia " << reg.getIdMembresia() << "? De nombre " <<"'" <<reg.getNombre() <<"'" << endl;
                cout << " OPCION [1] Eliminar [2] No eliminar ";
                cin >> opcion;

                if(reg.getActivo()==true)
                {
                    if(opcion ==1)
                    {
                        archiMembresias.bajaLogica(idMembresia);
                        cout << "Membresia dada de baja exitosamente." << endl;
                        system("pause");
                    }
                    else
                    {
                        cout << "El ID sigue estando activo... Vuelvo al menu " << endl;
                        system("pause");
                        return;
                    }

                }
                else
                {
                    cout << "El registro ya fue dado de baja. " << endl;
                }

            }
            system("pause");
            break;
        }

        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion incorrecta. " << endl;
            system("pause");
            break;
        }
    }
    while(opcion!=0);

}


void menuSocios()
{
    SocioArchivo archiSocios("socios.dat");
    Socio reg;
    int opcion;

    do
    {
        system("cls");
        cout << "------MENU SOCIOS------" << endl;
        cout << "1. Alta de Socio. " << endl;
        cout << "2. Baja logica de Socio." << endl;
        cout << "3. Modificar datos del socio." << endl;
        cout << "-----------------------------" << endl;
        cout << "4. BUSQUEDAS Y CONSULTAS: " << endl;
        cout << " [A] Buscar por ID de Socio. " << endl;
        cout << " [B] Buscar por apellido de Socio. " << endl;
        cout << "5. LISTADOS: " << endl;
        cout << " [A] Listar Socios (ACTIVOS E INACTIVOS). " << endl;
        cout << " [B] Listar por Apellido. " << endl;
        cout << " [C] Listar por Membresia. " << endl;
        cout << " [D] Listar por Objetivo. " << endl;
        cout << "-----------------------------" << endl;
        cout << "0. Volver al menu principal. " << endl;
        cout << "Seleccione una opcion: " << endl;
        cin >> opcion;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion=-1;
        }

        system("cls");

        switch(opcion)
        {
        case 1:
        {
            Socio nuevo;
            int dniValidar;

            if (cin.peek() == '\n') cin.ignore();

            cout << "---- ALTA DE NUEVO SOCIO ----" << endl;
            cout << "Ingrese el DNI del socio a registrar: ";
            cin >> dniValidar;

            ///Validación en el caso de que se ingrese un numero negativo
            if (!nuevo.setDNI(dniValidar))
            {
                cout << endl << "Error: El DNI ingresado no es valido (debe ser mayor a 0)." << endl;
            }
            else
            {
                int posExiste = archiSocios.buscarRegistroDNI(dniValidar);

                if(posExiste != -1)
                {
                    Socio viejo = archiSocios.leerRegistro(posExiste);
                    cout << endl << "Atencion: El DNI [" << dniValidar << "] ya se encuentra registrado." << endl;
                    if(viejo.getActivo() == 0)
                    {
                        cout << "El socio esta dado de BAJA. Reincorporelo desde la opcion 3." << endl;
                    }
                    else
                    {
                        cout << "El socio esta ACTIVO con el ID Socio: " << viejo.getIdSocio() << endl;
                    }
                }
                else
                {
                    cout << endl << "DNI disponible. Presione una tecla para cargar los datos..." << endl;
                    system("pause");
                    system("cls");

                    nuevo.CargarSocioSinDNI();

                    int nuevoID = archiSocios.generarNuevoID();
                    nuevo.setIdSocio(nuevoID);

                    cout << endl << "Socio guardado con exito. ID asignado: " << nuevoID << endl;
                    archiSocios.guardarRegistro(nuevo);
                }
            }

            system("pause");
            break;
        }
        case 2:
        {
            Socio reg;
            int dniSocio;
            int opcion;
            cout << "Ingrese el DNI del Socio que desea borrar: ";
            cin >> dniSocio;

            int pos = archiSocios.buscarRegistroDNI(dniSocio);

            if(pos == -1)
            {
                cout << "El registro no existe. " << endl;
            }
            else
            {
                reg=archiSocios.leerRegistro(pos);

                cout << "Desea eliminar el Socio con el DNI? " << reg.getDNI() << " OPCION [1] Eliminar [2] No eliminar" << endl;
                cin >> opcion;

                if(reg.getActivo()==true)
                {
                    if(opcion ==1)
                    {
                        archiSocios.bajaLogica(dniSocio);
                        cout << "Socio dado de baja exitosamente." << endl;
                        system("pause");
                    }
                    else
                    {
                        cout << "El sigue estando activo... Vuelvo al menu " << endl;
                        system("pause");
                        return;
                    }

                }
                else
                {
                    cout << "El registro ya fue dado de baja. " << endl;
                }

            }
            system("pause");
            break;
        }
        case 3:
        {
            int dniSocio;
            cout << "Ingrese el DNI del Socio que desea modificar: ";
            cin >> dniSocio;

            int pos = archiSocios.buscarRegistroDNI(dniSocio);

            if(pos == -1)
            {
                cout << "El registro no existe. " << endl;
            }
            else
            {
                int opcModificar;
                do
                {
                    reg = archiSocios.leerRegistro(pos);
                    system("cls");
                    cout << "------MODIFICAR SOCIO------" << endl;
                    cout << "Socio: " << reg.getApellido() << " , " << reg.getNombre() << endl;
                    cout << "-----------------------------" << endl;
                    cout << "1. Modificar email. " << endl;
                    cout << "2. Modificar telefono. " << endl;
                    cout << "3. Modificar objetivo. " << endl;
                    cout << "0. Guardar cambios y volver. " << endl;
                    cout << "-----------------------------" << endl;
                    cout << "Seleccione que dato desea cambiar: ";
                    cin >> opcModificar;

                    if(cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        opcModificar=-1;
                    }

                    switch(opcModificar)
                    {
                    case 1:
                    {
                        char nuevoEmail[80];
                        cout << "Ingrese el nuevo email: ";
                        cin.ignore();
                        cin.getline(nuevoEmail, 80);
                        reg.setEmail(nuevoEmail);
                        archiSocios.modificarRegistro(reg, pos);
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        char nuevoTelefono[20];
                        cout << "Ingrese el nuevo telefono: ";
                        cin.ignore();
                        cin.getline(nuevoTelefono, 20);
                        reg.setTelefono(nuevoTelefono);
                        archiSocios.modificarRegistro(reg, pos);
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        reg.cargarObjetivo();
                        archiSocios.modificarRegistro(reg, pos);
                        system("pause");
                        break;
                    }
                    case 0:
                        system("pause");
                        break;
                    }
                }
                while(opcModificar != 0);
            }
            break;
        }
        case 4:
        {
            char letra;
            cout << "Ingrese la opcion deseada: [A] ID SOCIO - [B] APELLIDO SOCIO " << endl;

            //limpio el buffer
            if (cin.peek() == '\n')
            {
                cin.ignore();
            }

            cin >> letra;
            cin.ignore();

            switch(letra)
            {
            case 'A':
            case 'a':
            {
                int idSocioBuscar;

                // Aseguramos la limpieza absoluta del buffer antes de leer el entero
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                }

                cout << "Ingrese el ID del Socio que desea buscar: ";
                cin >> idSocioBuscar;

                // Verificamos si el usuario ingresó un número válido
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Error: Debe ingresar un numero valido para el ID." << endl;
                    system("pause");
                    break;
                }

                int pos = archiSocios.buscarRegistroIDSocio(idSocioBuscar);

                if(pos != -1)
                {
                    reg = archiSocios.leerRegistro(pos);
                    cout << "---DATOS DEL SOCIO ENCONTRADO---" << endl;
                    reg.Mostrar();
                    system("pause");
                }
                else
                {
                    cout << "El ID de Socio ingresado no existe en el sistema " << endl;
                    system("pause");
                }
                break;
            }
            case 'B':
            case 'b':
            {
                char apellidoBuscar[50];
                cout << "Ingrese el apellido que desea buscar: ";
                cin.getline(apellidoBuscar, 50);

                archiSocios.listarPorApellido(apellidoBuscar);
                system("pause");
                break;
            }
            default:
                cout << "Opcion incorrecta. " << endl;
                system("pause");
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                break;
            }
            break;
        }
        case 5:
        {
            system("cls");
            char letraListado;
            cout << "INGRESE LA OPCION DESEADA " << endl;
            cout << "--------------------------" << endl;
            cout << "[A] Listar Socios. " << endl;
            cout << "[B] Listar Apellidos. " << endl;
            cout << "[C] Listar Membresias. " << endl;
            cout << "[D] Listar Objetivos. " << endl;
            cout << "0. Volver al submenu. " << endl;
            cout << "--------------------------" << endl;
            cin >> letraListado;

            system("cls");
            switch(letraListado)
            {
            case 'A':
            case 'a':
            {
                int opcionEstado;
                system("cls");
                cout << "----SELECCIONE EL ESTADO A LISTAR ----" << endl;
                cout << "1. Socios ACTIVOS " << endl;
                cout << "2. Socios INACTIVOS (Bajas) " << endl;
                cout << "0. Volver al menu " << endl;
                cout << "--------------------------------------" << endl;
                cout << "Seleccione una opcion: ";
                cin >> opcionEstado;
                system("cls");

                switch(opcionEstado)
                {
                case 1:
                {
                    cout << "---- LISTADO DE SOCIOS ACTIVOS ----" << endl;

                    if(!archiSocios.listarRegistrosActivos())
                    {
                        cout << "No hay socios activos registrados en el sistema." << endl;
                    }

                    system("pause");
                    break;
                }
                case 2:
                {
                    cout << "---- LISTADO DE SOCIOS INACTIVOS ----" << endl;

                    if(!archiSocios.listarRegistrosInactivos())
                    {
                        cout << "No hay socios inactivos (bajas) registrados en el sistema." << endl;
                    }

                    system("pause");
                    break;
                }
                case 0:
                    break;
                default:
                    cout << "Error. Opcion incorrecta, intente de nuevo. " << endl;
                    system("pause");
                    break;
                }
                break;
            }
            break;
            case 'B':
            case 'b':
            {
                system("cls");
                cout << "---- LISTADO DE SOCIOS POR APELLIDO ----" << endl;
                archiSocios.listarSociosOrdenadosPorApellido();
                system("pause");
                break;
            }
            case 'C':
            case 'c':
            {
                int opcionMembresia;
                cout << "---- SELECCIONE MEMBRESIA A LISTAR ----" << endl;
                cout << "1. Membresia BASICA " << endl;
                cout << "2. Membresia FULL " << endl;
                cout << "3. Buscar membresia por nombre: " << endl;
                cout << "0. Volver al menu " << endl;
                cout << "--------------------------------------" << endl;
                cout << "Seleccione una opcion: ";
                cin >> opcionMembresia;

                if(opcionMembresia == 1)
                {
                    archiSocios.listarPorMembresia(1);
                    system("pause");
                }
                else if(opcionMembresia == 2)
                {
                    archiSocios.listarPorMembresia(2);
                    system("pause");
                }
                else if(opcionMembresia==3)
                {
                    system("cls");
                    char nombreMembr[50];
                    cout << "Ingrese el nombre de membresia a buscar: ";
                    cin >> nombreMembr;
                    system("cls");
                    archiSocios.buscarMembresiaPorNombre(nombreMembr);
                    system("pause");
                }
                else if(opcionMembresia ==0)
                {
                    break;
                }
                else if(opcionMembresia != 0)
                {
                    cout << "Opcion incorrecta " << endl;
                    system("pause");
                }
                break;
            }
            case 'D':
            case 'd':
            {
                int opcionObjetivo;
                cout << "---- SELECCIONE EL OBJETIVO A LISTAR ---- " << endl;
                cout << "1. Ganar masa muscular " << endl;
                cout << "2. Perder grasa/peso " << endl;
                cout << "3. Mantener el estado fisico " << endl;
                cout << "0. Volver " << endl;
                cout << "-----------------------------------------" << endl;
                cout << "Seleccione una opcion: " << endl;
                cin >> opcionObjetivo;

                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    opcionObjetivo=-1;
                }

                switch(opcionObjetivo)
                {
                case 1:
                    cout << "---- SOCIOS: GANAR MASA MUSCULAR ----" << endl;
                    archiSocios.listarRegistrosPorObjetivo("Ganar masa muscular");
                    system("pause");
                    break;
                case 2:
                    cout << "---- SOCIOS: PERDER GRASA ----" << endl;
                    archiSocios.listarRegistrosPorObjetivo("Perder grasa");
                    system("pause");
                    break;
                case 3:
                    cout << "---- SOCIOS: MANTENER ESTADO ----" << endl;
                    archiSocios.listarRegistrosPorObjetivo("Mantener el estado fisico");
                    system("pause");
                    break;
                case 0:
                    break;
                default:
                    cout << "Opcion incorrecta. " << endl;
                    system("pause");
                    break;
                }
                break;
            }
            case 0:
                cout << "Volviendo al submenu.." << endl;
                system("pause");
                break;

            }
            break;
        }
        case 0:
            cout << "Volviendo al menu principal.." << endl;
            system("pause");
            break;
        }

    }
    while(opcion != 0);

}

void menuReportes()
{
    SocioArchivo archSocio("socios.dat");
    int opcion;

    do
    {
        system("cls");
        cout << "---- MENU REPORTES ----" << endl;
        cout << "-----------------------" << endl;
        cout << "1. Cantidad de socios por objetivo. " << endl;
        cout << "2. Clases mas solicitadas. " << endl;
        cout << "3. Cantidad de socios activos e inactivos. " << endl;
        cout << "4. Concurrencia mensual de socios. " << endl;
        cout << "5. Cantidad de socios por membresia. " << endl;
        cout << "6. Socios con mayor asistencia. " << endl;
        cout << "7. Recaudacion por medio de pago. " << endl;
        cout << "8. Reporte de pagos con recargo. " << endl;
        cout << "0. Volver al menu principal. " << endl;
        cout << "-----------------------" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            system("cls");
            archSocio.generarReportePorObjetivo();
            system("pause");
            break;
        case 2:
        {
            system("cls");
            ClaseArchivo arch("Clase.dat");
            arch.reporteMasSolicitadas();
            system("pause");
            break;
        }
        case 3:
            system("cls");
            archSocio.reporteCantSociosActivosInactivos();
            system("pause");
            break;

        case 4:
        {
            system("cls");

            IngresoArchivo archIngreso;
            archIngreso.reporteConcurrenciaMensual();

            system("pause");
        }
        break;
        case 5:
            system("cls");
            archSocio.reporteCantSociosPorMembresia();

            system("pause");
            break;
        case 6:
        {
            system("cls");

            IngresoArchivo archIngreso;
            archIngreso.reporteSociosMayorAsistencia();

            system("pause");
        }
        break;
        case 7:
        {
            system("cls");

            PagoArchivo archPago;
            archPago.reporteRecaudacionPorMetodoPago();

            system("pause");
        }
        break;
        case 8:
        {
            system("cls");

            PagoArchivo archPago;
            archPago.reportePagosConRecargo();

            system("pause");
        }
        break;
        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;

        default:
            cout << "Opcion incorrecta. Intente nuevamente." << endl;
            system("pause");
            break;
        }
    }
    while (opcion != 0);
}
void menuRutinas()
{
    RutinaArchivo archivo;
    Rutina reg;

    int opcion;

    do
    {
        system("cls");

        cout << "------- MENU RUTINAS -------" << endl;
        cout << "============================" << endl;
        cout << "1 - Nueva rutina" << endl;
        cout << "2 - Buscar rutina por ID" << endl;
        cout << "3 - Listar rutinas" << endl;
        cout << "4 - Modificar rutina" << endl;
        cout << "5 - Baja de rutina" << endl;
        cout << "6 - Buscar por nivel" << endl;
        cout << "7 - Buscar por tipo" << endl;
        cout << "8 - Listar activas" << endl;
        cout << "9 - Listar inactivas" << endl;
        cout << "0 - Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = -1;
        }

        switch(opcion)
        {
        case 1:
        {
            Rutina reg;

            reg.Cargar();

            int nuevoID = archivo.cantidadRegistros() + 1;
            reg.setId(nuevoID);

            if(archivo.guardarRegistro(reg))
            {
                cout << "Rutina guardada correctamente." << endl;
            }
            else
            {
                cout << "Error al guardar." << endl;
            }

            system("pause");
        }
        break;

        case 2:
        {
            int id;

            cout << "Ingrese ID de rutina: ";
            cin >> id;

            int pos = archivo.buscarRegistro(id);

            if(pos >= 0)
            {
                reg = archivo.leerRegistro(pos);

                if(reg.getActivo())
                {
                    reg.Mostrar();
                }
                else
                {
                    cout << "La rutina esta dada de baja." << endl;
                }
            }
            else
            {
                cout << "Rutina no encontrada." << endl;
            }

            system("pause");
        }
        break;

        case 3:
        {
            archivo.listarRegistros();
            system("pause");
        }
        break;

        case 4:
        {
            int id;

            cout << "Ingrese ID de rutina a modificar: ";
            cin >> id;

            int pos = archivo.buscarRegistro(id);

            if(pos >= 0)
            {
                reg = archivo.leerRegistro(pos);


                if(!reg.getActivo())
                {
                    cout << "La rutina esta dada de baja y no puede modificarse." << endl;
                    system("pause");
                    break;
                }

                bool estado = reg.getActivo();

                cout << "Ingrese los nuevos datos:" << endl;

                reg.Cargar();

                reg.setId(id);
                reg.setActivo(estado);

                if(archivo.modificarRegistro(reg, pos))
                {
                    cout << "Rutina modificada correctamente." << endl;
                }
                else
                {
                    cout << "Error al modificar rutina." << endl;
                }
            }
            else
            {
                cout << "Rutina no encontrada." << endl;
            }

            system("pause");
        }
        break;

        case 5:
        {

            int id;
            char opcion;

            cout << "Ingrese ID de rutina: ";
            cin >> id;

            if(cin.fail() || id <= 0)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "ID invalido." << endl;
                system("pause");
                break;
            }

            cout << "Seguro que desea darla de baja? (S/N): ";
            cin >> opcion;

            if(opcion=='S' || opcion=='s')
            {
                if(archivo.bajaLogica(id))
                {
                    cout << "Rutina dada de baja correctamente." << endl;
                }
                else
                {
                    cout << "No se encontro la rutina." << endl;
                }
            }
            else
            {
                cout << "Operacion cancelada." << endl;
            }

            system("pause");
        }
        break;
        case 6:
        {
            char nivel[20];

            cout << "Ingrese nivel: ";
            cin.ignore();
            cin.getline(nivel, 20);

            archivo.listarPorNivel(nivel);

            system("pause");
        }
        break;
        case 7:
        {
            char tipo[45];

            cout << "Ingrese tipo: ";
            cin.ignore();
            cin.getline(tipo, 45);

            archivo.listarPorTipo(tipo);

            system("pause");
        }
        break;
        case 8:
        {
            archivo.listarRegistrosActivos();
            system("pause");
        }
        break;

        case 9:
        {
            archivo.listarRegistrosInactivos();
            system("pause");
        }
        break;

        case 0:
            break;

        default:
            cout << "Opcion incorrecta." << endl;
            system("pause");
            break;
        }

    }
    while(opcion != 0);
}
void menuIngresos()
{
    IngresoArchivo archivo;
    Ingreso reg;

    int opcion;

    do
    {
        system("cls");

        cout << "------- MENU INGRESOS -------" << endl;
        cout << "1 - Nuevo ingreso" << endl;
        cout << "2 - Buscar ingreso" << endl;
        cout << "3 - Listar ingresos" << endl;
        cout << "4 - Modificar ingreso" << endl;
        cout << "5 - Baja de ingreso" << endl;
        cout << "0 - Volver" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion)
        {
        case 1:
        {
            Ingreso reg;
            SocioArchivo archiSocios("socios.dat");

            reg.Cargar();

            int nuevoID = archivo.cantidadRegistros() + 1;
            reg.setIdIngreso(nuevoID);

            int pos = archiSocios.buscarRegistroDNI(reg.getDniSocio());

            if(pos == -1 )
            {
                cout << "El socio no existe. " << endl;
                system("pause");
                break;
            }

            Socio socio = archiSocios.leerRegistro(pos);

            if(!socio.getActivo())
            {
                cout << " El socio esta inactivo. No puede registrar ingresos. " << endl;
                system("pause");
                break;
            }

            if(archivo.guardarRegistro(reg))
            {
                cout << "Ingreso guardado correctamente. " << endl;
            }
            else
            {
                cout << "Error al guardar. " << endl;
            }

        }
        system("pause");
        break;

        case 2:
        {
            int dni;

            cout << "Ingrese DNI del socio: ";
            cin >> dni;

            archivo.listarPorDni(dni);

            system("pause");
        }
        break;

        case 3:
        {
            archivo.listarRegistros();
            system("pause");
        }
        break;

        case 4:
        {
            int dni;

            cout << "Ingrese DNI del socio: ";
            cin >> dni;

            int pos = archivo.buscarRegistroDni(dni);

            if(pos >= 0)
            {
                reg = archivo.leerRegistro(pos);

                cout << "Ingrese los nuevos datos:" << endl;

                reg.Cargar();

                reg.setIdIngreso(archivo.leerRegistro(pos).getIdIngreso());

                if(archivo.modificarRegistro(reg, pos))
                {
                    cout << "Ingreso modificado correctamente." << endl;
                }
                else
                {
                    cout << "Error al modificar." << endl;
                }
            }
            else
            {
                cout << "Ingreso no encontrado." << endl;
            }

            system("pause");
        }
        break;

        case 5:
        {
            int id;

            cout << "Ingrese ID de ingreso: ";
            cin >> id;

            if(archivo.bajaLogica(id))
            {
                cout << "Ingreso dado de baja." << endl;
            }
            else
            {
                cout << "No se encontro el ingreso." << endl;
            }

            system("pause");
        }
        break;

        case 0:
            break;

        default:
            cout << "Opcion incorrecta." << endl;
            system("pause");
            break;
        }

    }
    while(opcion != 0);
}
void menuPagos()
{
    PagoArchivo archivo;
    Pago reg;
    SocioArchivo archSocio;

    int opcion;

    do
    {
        system("cls");

        cout << "------- MENU PAGOS -------" << endl;
        cout << "1 - Nuevo pago" << endl;
        cout << "2 - Buscar pago por ID" << endl;
        cout << "3 - Listar pagos" << endl;
        cout << "4 - Modificar pago" << endl;
        cout << "5 - Baja de pago" << endl;
        cout << "6 - Listar pagos pendientes" << endl;
        cout << "7 - Listar pagos realizados" << endl;
        cout << "8 - Buscar pagos por socio" << endl;
        cout << "0 - Volver" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = -1;
        }

        switch(opcion)
        {
        case 1:
        {

            reg.Cargar();
            int posSocio = archSocio.buscarRegistroDNI(reg.getdniSocio());

            if(posSocio == -1)
            {
                cout << "El socio no existe. " << endl;
                system("pause");
                break;
            }

            Socio socio=archSocio.leerRegistro(posSocio);

            if(socio.getActivo()==0)
            {
                char opc;
                cout << "El socio esta dado de baja. " << endl;
                cout << "Desea reactivarlo?(S/N): ";
                cin >> opc;

                if(opc == 'S' || opc == 's')
                {
                    socio.setActivo(1);

                    if(!archSocio.modificarRegistro(socio,posSocio))
                    {
                        cout << "Error al reactivar el socio. " << endl;
                        system("pause");
                        break;
                    }
                    else
                    {
                        cout << "Socio reactivado correctamente. " << endl;
                    }
                }
                else
                {
                    cout << "Operacion cancelada. " << endl;
                    system("pause");
                    break;
                }
            }


            MembresiasArchivo archMem;

            int posMem=archMem.buscarRegistroIDMembresia(socio.getIdMembresia());

            if(posMem == -1)
            {
                cout << "La membresia del socio no existe. " << endl;
                break;
            }

            Membresias mem = archMem.leerRegistro(posMem);

            float importe = mem.getPrecio() + reg.getRecargo();

            reg.setImporte(importe);

            reg.setIdPago(archivo.cantidadRegistros() + 1);

            // cout << "Importe antes de guardar: " << reg.getImporte() << endl;

            if(archivo.guardarRegistro(reg))
            {
                if(reg.getEstadoPago() == 1)
                {
                    cout << "Pago realizado y registrado correctamente." << endl;
                }
                else if(reg.getEstadoPago() == 0)
                {
                    cout << "Pago registrado como PENDIENTE (en espera de cobro)." << endl;
                }
            }
            else
            {
                cout << "Error al guardar el registro del pago." << endl;
            }
            ///Si el socio estaba suspendido por deuda y pagó, vuelve a estar activo
            if(socio.getActivo()==2 && reg.getEstadoPago()==1)
            {
                socio.setActivo(1);
                archSocio.modificarRegistro(socio,posSocio);
            }

            system("pause");
        }
        break;
        case 2:
        {
            int id;

            cout << "Ingrese ID del pago: ";
            cin >> id;

            int pos = archivo.buscarRegistro(id);

            if(pos >= 0)
            {
                reg = archivo.leerRegistro(pos);
                if(reg.getEstadoPago() != 0)
                {
                    reg.Mostrar();
                }
                else
                {
                    cout << "Ese pago esta dado de baja." << endl;
                }
            }
            else
            {
                cout << "Pago no encontrado." << endl;
            }

            system("pause");
        }
        break;

        case 3:
        {
            archivo.listarRegistros();
            system("pause");
        }
        break;

        case 4:
        {
            int id;

            cout << "Ingrese ID del pago a modificar: ";
            cin >> id;

            int pos = archivo.buscarRegistro(id);

            if(pos >= 0)
            {
                reg = archivo.leerRegistro(pos);

                cout << "Ingrese los nuevos datos:" << endl;

                reg.Cargar();
                int dni = reg.getdniSocio();

                int posSocio = archSocio.buscarRegistroDNI(dni);

                if(posSocio < 0)
                {
                    cout << "No existe ese socio." << endl;
                    system("pause");
                    break;
                }

                Socio socio = archSocio.leerRegistro(posSocio);

                if(!socio.getActivo())
                {
                    cout << "El socio esta dado de baja." << endl;
                    system("pause");
                    break;
                }

                reg.setIdPago(id);

                if(archivo.modificarRegistro(reg, pos))
                    cout << "Pago modificado correctamente." << endl;
                else
                    cout << "Error al modificar." << endl;
            }
            else
            {
                cout << "Pago no encontrado." << endl;
            }

            system("pause");
        }
        break;

        case 5:
        {
            int id;

            cout << "Ingrese ID del pago: ";
            cin >> id;

            if(archivo.bajaLogica(id))
                cout << "Pago dado de baja." << endl;
            else
                cout << "Pago no encontrado." << endl;

            system("pause");
        }
        break;

        case 6:
        {
            archivo.listarPendientes();
            system("pause");
        }
        break;

        case 7:
        {
            archivo.listarPagados();
            system("pause");
        }
        break;

        case 8:
        {
            int dni;

            cout << "Ingrese DNI del socio: ";
            cin >> dni;

            int posSocio = archSocio.buscarRegistroDNI(dni);

            if(posSocio < 0)
            {
                cout << "El socio no existe." << endl;
            }
            else
            {
                archivo.listarPorSocio(dni);
            }

            system("pause");
        }
        break;
        case 0:
            break;

        default:
            cout << "Opcion incorrecta." << endl;
            system("pause");
            break;
        }

    }
    while(opcion != 0);
}

void menuInscripciones()
{
    int opcion;
    InscripcionArchivo arch("inscripciones.dat");

    do
    {

        system("cls");
        cout << "---------MENU INSCRIPCIONES-----------" << endl;
        cout << "======================================" << endl;
        cout << "1 - Nueva inscripcion" << endl;
        cout << "2 - Modificar inscripcion" << endl;
        cout << "3 - Dar de baja inscripcion" << endl;
        cout << "4 - Listar inscripciones" << endl;
        cout << "0 - Volver" << endl;

        cout << "Seleccione una opcion: ";

        cin >> opcion;

        switch(opcion)
        {
        case 1:
        {
            cout << "Nueva inscripcion" << endl;

            Inscripcion reg;

            SocioArchivo archSocios("socios.dat");
            ClaseArchivo archClases("clases.dat");

            reg.Cargar();

            int posSocio = archSocios.buscarRegistroDNI(reg.getDniSocio());

            if(posSocio == -1)
            {
                cout << "El socio no existe." << endl;
                system("pause");
                break;
            }

            Socio socio = archSocios.leerRegistro(posSocio);


            if(socio.getActivo() != 1)
            {
                cout << "El socio no esta activo. No puede inscribirse." << endl;
                system("pause");
                break;
            }

            int posClase = archClases.buscarRegistro(reg.getIdClase());

            if(posClase == -1)
            {
                cout << "La clase no existe." << endl;
                system("pause");
                break;
            }

            Clase clase = archClases.leerRegistro(posClase);


            if(clase.getActivo() == false)
            {
                cout << "La clase esta inactiva. No se puede realizar la inscripcion." << endl;
                system("pause");
                break;
            }

            int inscriptos = archClases.contarInscripcionesPorClase(clase.getIdClase());

            if(inscriptos >= clase.getCapacidadMax())
            {
                cout << "La clase ya completo su capacidad maxima. " << endl;
                system("pause");
                break;
            }

            reg.setIdInscripcion(arch.cantidadRegistros() + 1);


            if(arch.yaEstaInscripto(reg.getDniSocio(), reg.getIdClase()))
            {
                cout << "El socio ya esta inscripto en esta clase." << endl;
                system("pause");
                break;
            }

            if(arch.guardarRegistro(reg))
            {
                cout << "Inscripcion guardada correctamente" << endl;
            }
            else
            {
                cout << "Error al guardar inscripcion" << endl;
            }

            system("pause");
            system("cls");
            break;
        }
        case 2:
        {
            cout << "Modificar inscripcion" << endl;
            int id;
            cout << "Ingrese ID de inscripcion a modificar: ";
            cin >> id;

            int pos = arch.buscarRegistro(id);

            if(pos != -1)
            {
                Inscripcion reg = arch.leerRegistro(pos);

                cout << "Datos actuales:" << endl;
                reg.Mostrar();

                cout << "Ingrese nuevos datos:" << endl;
                reg.Cargar();

                if(arch.modificarRegistro(reg, pos))
                {
                    cout << "Modificacion exitosa" << endl;
                }
                else
                {
                    cout << "Error al modificar" << endl;
                }
            }
            else
            {
                cout << "Inscripcion no encontrada" << endl;
            }
            system("pause");
            system("cls");
            break;
        }


        case 3:
        {
            int id;
            cout << "Ingrese ID: ";
            cin >> id;

            if(arch.bajaLogica(id))
            {
                cout << "Baja realizada" << endl;
            }
            else
            {
                cout << "No encontrado" << endl;
            }
            system("pause");
            system("cls");
            break;
        }

        case 4:
        {
            cout <<"Listado de inscripciones: " << endl;
            arch.listarRegistrosActivos ();
            system("pause");
            break;
        }

        case 0:
            break;

        default:
            if(opcion != 0)
            {
                cout << "Opcion incorrecta";
            }
            system("pause");
            break;
        }
    }
    while(opcion != 0);
}


void menuClases()
{
    int opcion;
    void menuConsultasClases();
    void menuListadoClases();

    do
    {
        system("cls");

        cout << "-----------MENU CLASES----------" << endl;
        cout << "================================" << endl;
        cout << "1 - Nueva clase" << endl;
        cout << "2 - Modificar clase" << endl;
        cout << "3 - Baja de clase" << endl;
        cout << "4 - Consultar clases" << endl;
        cout << "5 - Listado de clases" << endl;
        cout << "0 - Volver" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion)
        {
        case 1:
        {
            ClaseArchivo arch;
            Clase reg;
            reg.Cargar();
            reg.setIdClase(arch.cantidadRegistros() + 1);
            if(arch.guardarRegistro(reg))
            {
                cout << "Clase guardada correctamente" << endl;
            }
            else
            {
                cout << "Error al guardar clase" << endl;
            }
            system("pause");
        }
        break;

        case 2:
        {
            int id;
            cout << "Ingrese ID de la clase a modificar: ";
            cin >> id;
            ClaseArchivo arch;
            int pos = arch.buscarRegistro(id);
            if(pos != -1)
            {
                Clase reg = arch.leerRegistro(pos);
                cout << "Datos de la clase a modificar:" << endl;
                reg.Mostrar();
                cout << endl;
                cout << "Ingrese los nuevos datos:" << endl;
                reg.Cargar();
                reg.setIdClase(id);
                if(arch.modificarRegistro(reg, pos))
                {
                    cout << "Clase modificada correctamente" << endl;
                }
                else
                {
                    cout << "Error al modificar la clase" << endl;
                }
            }
            else
            {
                cout << "Clase no encontrada" << endl;
            }
            system("pause");
        }
        break;

        case 3:
        {
            int id;

            cout << "Ingrese ID: ";
            cin >> id;
            ClaseArchivo arch;

            if(arch.bajaLogica(id))
            {
                cout << "Baja realizada" << endl;
            }
            else
            {
                cout << "No encontrado" << endl;
            }
            system("pause");
            system("cls");
        }
        break;

        case 4:
            menuConsultasClases();
            break;

        case 5:
            menuListadoClases();
            break;

        case 0:
            break;

        default:
            cout << "Opcion incorrecta" << endl;
            system("pause");
            break;
        }
    }
    while(opcion != 0);
}

void menuConsultasClases()
{

    ClaseArchivo arch;
    int opcion;

    do
    {
        system("cls");

        cout << "------- CONSULTAS DE CLASES -------" << endl;
        cout << "===================================" << endl;
        cout << "1 - Buscar por instructor" << endl;
        cout << "2 - Buscar por nombre de clase" << endl;
        cout << "3 - Disponibilidad de cupos por horario" << endl;
        cout << "0 - Volver" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion)
        {

        case 1:
        {
            char instructor[50];
            Clase reg;
            cin.ignore();
            cout << "Ingrese instructor: ";
            cin.getline(instructor, 50);
            int cant = arch.cantidadRegistros();
            for(int i = 0; i < cant; i++)
            {
                reg = arch.leerRegistro(i);
                if(reg.getActivo() && strcmp(reg.getInstructorClase(), instructor) == 0)
                {
                    reg.Mostrar();
                    cout << endl;
                }
            }
            system("pause");
        }
        break;


        case 2:
        {
            char nombre[50];
            Clase reg;
            cin.ignore();
            cout << "Ingrese nombre de clase: ";
            cin.getline(nombre, 50);
            int cant = arch.cantidadRegistros();
            for(int i = 0; i < cant; i++)
            {
                reg = arch.leerRegistro(i);
                if(reg.getActivo() && strcmp(reg.getNombreDeClase(), nombre) == 0)
                {
                    reg.Mostrar();
                    cout << endl;
                }
            }
            system("pause");
        }
        break;

        case 3:
        {
            int id;
            cout << "Ingrese ID de la clase: ";
            cin >> id;
            int pos = arch.buscarRegistro(id);
            if(pos != -1)
            {
                Clase reg = arch.leerRegistro(pos);
                if(reg.getActivo())
                {
                    cout << "Clase encontrada:" << endl;
                    reg.Mostrar();
                    cout << "Cupos disponibles: " << reg.getCapacidadMax() << endl;
                }
                else
                {
                    cout << "Clase inactiva" << endl;
                }
            }
            else
            {
                cout << "No encontrada" << endl;
            }
            system("pause");
        }
        break;


        case 0:
            break;

        default:
            cout << "Opcion incorrecta" << endl;
            system("pause");
            break;
        }
    }
    while(opcion != 0);
}


void menuListadoClases()
{
    ClaseArchivo arch;
    int opcion;

    do
    {
        system("cls");

        cout << "------- LISTADO DE CLASES ------" << endl;
        cout << "================================" << endl;
        cout << "1 - Todas las clases" << endl;
        cout << "2 - Por nombre" << endl;
        cout << "3 - Por instructor" << endl;
        cout << "4 - Por horario" << endl;
        cout << "5 - Por capacidad" << endl;
        cout << "6 - Activas" << endl;
        cout << "7 - Inactivas" << endl;
        cout << "0 - Volver" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        system("cls");

        switch(opcion)
        {
        case 1:
            cout << "---- CLASES DISPONIBLES ----" << endl;
            cout << "----------------------------" << endl;
            arch.listarTodos();
            system("pause");
            break;

        case 2:
        {
            cout << "Ingrese el nombre de la clase: ";
            char nombre[50];
            cin.ignore();
            cin.getline(nombre, 50);
            arch.listarPorNombre(nombre);
            system("pause");
        }
        break;
        case 3:
        {
            cout << "Ingrese el nombre del instructor: ";
            char inst[50];
            cin.ignore();
            cin.getline(inst, 50);
            arch.listarPorInstructor(inst);
            system("pause");
        }
        break;

        case 4:
        {
            int hora;
            cout << "Ingrese hora (0-23): ";
            cin >> hora;
            arch.listarPorHorario(hora);
            system ("pause");
        }
        break;

        case 5:
        {
            int cap;
            cout << "Capacidad minima: ";
            cin >> cap;
            arch.listarPorCapacidad(cap);
        }
        system("pause");
        break;

        case 6:
            arch.listarRegistrosActivos();
            system("pause");
            break;


        case 7:
            arch.listarInactivas();
            system("pause");
            break;

        case 0:
            break;

        default:
            cout << "Opcion incorrecta" << endl;
            system("pause");
            break;
        }
    }
    while(opcion != 0);
}
