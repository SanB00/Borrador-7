#ifndef MENUINFORMES_H
#define MENUINFORMES_H

#include "InformeProducto.h"

void menuInformes() {
    int opc;
    do {
        system("cls");
        cout << "----- MENU DE INFORMES -----" << endl;
        cout << "1. Listar productos por autor" << endl;
        cout << "2. Listar productos por editorial" << endl;
        cout << "3. Listar productos por serie" << endl;
        cout << "4. Listar productos por genero" << endl;
        cout << "0. Volver al menu anterior" << endl;
        cout << "Opcion: ";
        cin >> opc;

        int id;
        switch (opc) {
            case 1:
                cout << "Ingrese ID del autor: ";
                cin >> id;
                listarProductosPorAutor(id);
                system("pause");
                break;
            case 2:
                cout << "Ingrese ID de la editorial: ";
                cin >> id;
                listarProductosPorEditorial(id);
                system("pause");
                break;
            case 3:
                cout << "Ingrese ID de la serie: ";
                cin >> id;
                listarProductosPorSerie(id);
                system("pause");
                break;
            case 4:
                cout << "Ingrese ID del genero: ";
                cin >> id;
                listarProductosPorGenero(id);
                system("pause");
                break;
        }

    } while (opc != 0);
}

#endif
