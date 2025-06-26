#ifndef MENU_EDITORIAL_H
#define MENU_EDITORIAL_H

#include "Editorial.h"

void menuEditorial() {
    int opcion;
    system("cls");

    do {
        cout << "----- MENU EDITORIAL -----"<<endl;
        cout << "1. Nuevo registro"<<endl;
        cout << "2. Listar editoriales"<<endl;
        cout << "3. Modificar"<<endl;
        cout << "4. Dar de baja"<<endl;
        cout << "5. Levantar registro"<<endl;
//        cout << "6. Listar editoriales ordenadas"<<endl;
        cout << "0. Volver al menu anterior"<<endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                {
                    Editorial e;
                    e.nuevoRegistro();
                    system("pause");
                }
                break;

            case 2:
                {
                    system("cls");
                    menuListarEditorialesOrdenadas();
//                    Editorial vec[MAX_EDITORIALES];
//                    int total = cargarEditoriales(vec, MAX_EDITORIALES);
//                    if (total == 0) {
//                        cout << "No hay editoriales activas."<<endl;
//                    } else {
//                        mostrarEditorialesTabla(vec, total);
//                    }
//                    system("pause");
                }
                break;

            case 3:
                {
                    Editorial e;
                    e.modificar();
                    system("pause");
                }
                break;

            case 4:
                {
                    Editorial e;
                    e.baja();
                    system("pause");
                }
                break;

            case 5:
                {
                    Editorial e;
                    e.levantar();
                    system("pause");
                }
                break;

            case 6:
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida"<<endl;
                system("pause");
                break;
        }
        system("cls");
    } while (opcion != 0);
}

#endif
