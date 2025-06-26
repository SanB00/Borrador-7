#ifndef MENU_SERIE_H
#define MENU_SERIE_H

#include "Serie.h"


void menuSerie() {
    int opcion;

    do {
        system("cls");
        cout << "=== MENU SERIES ===" << endl;
        cout << "1. Nuevo Registro de Serie" << endl;
        cout << "2. Listar Series" << endl;
//        cout << "3. Listar Series ORdenados " << endl;
        cout << "3. Modificar Serie" << endl;
        cout << "4. Dar de Baja Serie" << endl;
        cout << "5. Levantar Serie dada de baja" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
            case 1:
                nuevoRegistroSerie();
                break;
            case 2:
//                listarSeries();
                menuListarSeriesOrdenadas();
                system("pause");
                break;
            case 3:
                break;
            case 4: {
                Serie s;
                s.modificar();
                system("pause");
                break;
            }
            case 5: {
                Serie s;
                s.baja();
                system("pause");
                break;
            }
            case 6: {
                Serie s;
                s.levantar();
                system("pause");
                break;
            }
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                system("pause");
        }
    } while (opcion != 0);
}

#endif
