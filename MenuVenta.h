#ifndef MENU_VENTA_H
#define MENU_VENTA_H

#include "Venta.h"

void listarTodasLasVentas() {
    Venta v;
    ifstream file("ventas.dat", ios::binary);
    if (!file) {
        cout << "No hay ventas registradas" << endl;
        return;
    }

    while (file.read(reinterpret_cast<char*>(&v), sizeof(Venta))) {
        if (v.getEstado()) v.mostrar();
    }

    file.close();
}

void mostrarVentasPorAnio(int anio) {
    Venta v;
    ifstream file("ventas.dat", ios::binary);
    if (!file) {
        cout << "No hay ventas registradas" << endl;
        return;
    }

    while (file.read(reinterpret_cast<char*>(&v), sizeof(Venta))) {
        if (v.getEstado() && v.getAnio() == anio) {
            v.mostrar();
        }
    }

    file.close();
}

void mostrarVentasPorMes(int anio, int mes) {
    Venta v;
    ifstream file("ventas.dat", ios::binary);
    if (!file) {
        cout << "No hay ventas registradas" << endl;
        return;
    }

    while (file.read(reinterpret_cast<char*>(&v), sizeof(Venta))) {
        if (v.getEstado() && v.getAnio() == anio && v.getMes() == mes) {
            v.mostrar();
        }
    }

    file.close();
}

void menuVenta() {
    int opc;
    do {
        system("cls");
        cout << "----- MENU VENTAS -----" << endl;
        cout << "1. Listar todas las ventas" << endl;
        cout << "2. Mostrar ventas por anio" << endl;
        cout << "3. Mostrar ventas por mes" << endl;
        cout << "0. Volver al menu anterior" << endl;
        cout << "Opcion: ";
        cin >> opc;

        switch (opc) {
            case 1:
                listarTodasLasVentas();
                system("pause");
                break;
            case 2: {
                int anio;
                cout << "Ingrese anio: ";
                cin >> anio;
                mostrarVentasPorAnio(anio);
                system("pause");
                break;
            }
            case 3: {
                int anio, mes;
                cout << "Ingrese anio: ";
                cin >> anio;
                cout << "Ingrese mes: ";
                cin >> mes;
                mostrarVentasPorMes(anio, mes);
                system("pause");
                break;
            }
        }
    } while (opc != 0);
}

#endif
