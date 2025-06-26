#ifndef MENUCOMPRA_H
#define MENUCOMPRA_H

#include <iostream>
#include "Compra.h"

using namespace std;

void menuCompra() {
    int opcion;
    do {
        cout << "=== MENU DE COMPRA ===" << endl;
        cout << "1. Compra manual" << endl;
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
            case 1:
                compraManual();
                break;
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
