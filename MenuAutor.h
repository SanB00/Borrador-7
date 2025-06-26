#ifndef MENU_AUTOR_H
#define MENU_AUTOR_H

#include "Autor.h"

void menuAutor() {
    int opc;
    do {
        system("cls");
        cout << "----- MENU AUTOR -----" << endl;
        cout << "1. Nuevo registro" << endl;
        cout << "2. Listar autores" << endl;
        cout << "3. Modificar" << endl;
        cout << "4. Dar de baja" << endl;
        cout << "5. Levantar registro" << endl;
        cout << "0. Volver al menu anterior" << endl;
        cout << "Opcion: ";
        cin >> opc;

        switch (opc) {
            case 1: {
                Autor a;
                nuevoRegistroAutor();
                system("pause");
                break;
            }
            case 2:
                listarAutores();
                system("pause");
                break;
            case 3: {
                Autor a;
                a.modificar();
                system("pause");
                break;
            }
            case 4: {
                Autor a;
                a.baja();
                system("pause");
                break;
            }
            case 5: {
                Autor a;
                a.levantar();
                system("pause");
                break;
            }
        }
    } while (opc != 0);
}

#endif
