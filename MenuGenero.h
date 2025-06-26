#ifndef MENU_GENERO_H
#define MENU_GENERO_H

#include "Genero.h"

void menuGenero() {
    int opc;
    do {
        system("cls");
        cout << "----- MENU GENERO -----" << endl;
        cout << "1. Nuevo registro" << endl;
        cout << "2. Listar generos" << endl;
        cout << "3. Modificar" << endl;
        cout << "4. Dar de baja" << endl;
        cout << "5. Levantar registro" << endl;
        cout << "0. Volver al menu anterior" << endl;
        cout << "Opcion: ";
        cin >> opc;

        switch (opc) {
            case 1: {
                Genero g;
                g.nuevoRegistro();
                system("pause");
                break;
            }
            case 2:{

                menuListarGenerosOrdenados();
                //listarGeneros();
                system("pause");
                break;
            }
            case 3: {
                Genero g;
                g.modificar();
                system("pause");
                break;
            }
            case 4: {
                Genero g;
                g.baja();
                system("pause");
                break;
            }
            case 5: {
                Genero g;
                g.levantar();
                system("pause");
                break;
            }
        }

    } while (opc != 0);
}


#endif
