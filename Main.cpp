#include <iostream>
using namespace std;

#include "MenuProducto.h"
#include "MenuGenero.h"
#include "MenuAutor.h"
#include "MenuEditorial.h"
#include "MenuSerie.h"
#include "MenuEmpleado.h"
#include "MenuCompra.h"
#include "MenuVenta.h"
#include "MenuInformes.h"

int main() {
    int opc;

    do {
        system("cls");
        cout << "----- MENU PRINCIPAL COMIQUERIA -----" << endl;
        cout << "1. Gestionar productos" << endl;
        cout << "2. Gestionar generos" << endl;
        cout << "3. Gestionar autores" << endl;
        cout << "4. Gestionar editoriales" << endl;
        cout << "5. Gestionar series" << endl;
        cout << "6. Gestionar empleados" << endl;
        cout << "7. Ventas" << endl;
        cout << "8. Informes "<< endl;
        cout << "0. Salir del programa" << endl;
        cout << "Opcion: ";
        cin >> opc;

        switch (opc) {
            case 1: menuProducto(); break;
            case 2: menuGenero(); break;
            case 3: menuAutor(); break;
            case 4: menuEditorial(); break;
            case 5: menuSerie(); break;
            case 6: menuEmpleado(); break;
            case 7: menuVenta(); break;
            case 8: menuInformes(); break;
        }

    } while (opc != 0);

    cout << "Fin del programa." << endl;
    return 0;
}
