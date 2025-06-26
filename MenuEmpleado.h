#ifndef MENU_EMPLEADO_H
#define MENU_EMPLEADO_H

#include "Empleado.h"

void menuEmpleado() {
    int opcion;
    do {
        system("cls");
        cout << "=== MENU DE EMPLEADOS ===" << endl;
        cout << "1. Nuevo registro" << endl;
        cout << "2. Modificar empleado" << endl;
        cout << "3. Listar empleados ordenado" << endl;
        cout << "4. Baja de empleado" << endl;
        cout << "5. Levantar empleado dado de baja" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
            case 1:
                nuevoRegistroEmpleado();
                system("pause");

                break;
            case 2: {
                Empleado e;
                e.modificar();
                system("pause");

                break;
            }
            case 3:
                menuListarEmpleadosOrdenados();
                system("pause");

                break;
            case 4: {
                Empleado e;
                e.baja();
                system("pause");
                break;
            }
            case 5: {
                Empleado e;
                e.levantar();
                system("pause");
                break;
            }

            case 0:
                break;
            default:
                cout << "Opcion invalida." << endl;
                system("pause");
                break;
        }
    } while (opcion != 0);
}

#endif

