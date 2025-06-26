#ifndef MENUPRODUCTO_H
#define MENUPRODUCTO_H

#include "Producto.h"

void menuProducto() {
    int opcion;

    do {
        system("cls");
        cout << "=== MENU DE PRODUCTOS ===" << endl;
        cout << "1. Crear nuevo producto" << endl;
        cout << "2. Modificar producto" << endl;
        cout << "3. Listar productos" << endl;
        cout << "4. Dar de baja un producto" << endl;
        cout << "5. Reactivar un producto dado de baja" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
            case 1: {
                Producto p;
                p.nuevoRegistro();
                break;
            }
            case 2: {
                Producto p;
                p.modificar();
                system("pause");
                break;
            }
            case 3:
                listarProductosOrdenados();
                break;
            case 4: {
                Producto p;
                p.bajaProducto();
                system("pause");
                break;
            }
            case 5: {
                Producto p;
                p.levantarProducto();
                system("pause");
                break;
            }
            case 0:
                break;
            default:
                cout << "Opcion invalida.\n";
                system("pause");
                break;
        }

    } while (opcion != 0);
}

#endif
