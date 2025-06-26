#ifndef VENTA_H
#define VENTA_H

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Venta {
private:
    int idVenta;
    int idEmpleado;
    int dia, mes, anio;
    float montoTotal;
    bool estado;

public:
    Venta();

    // Setters
    void setIDVenta(int);
    void setIDEmpleado(int);
    void setFecha(int, int, int);
    void setMontoTotal(float);
    void setEstado(bool);

    // Getters
    int getIDVenta() const;
    int getIDEmpleado() const;
    float getMontoTotal() const;
    bool getEstado() const;
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // Métodos
    void mostrar() const;
    bool guardarEnArchivo() const;
};

// ------------------------ IMPLEMENTACION ------------------------

Venta::Venta() {
    idVenta = 0;
    idEmpleado = 0;
    dia = mes = anio = 0;
    montoTotal = 0;
    estado = true;
}

void Venta::setIDVenta(int id) { idVenta = id; }
void Venta::setIDEmpleado(int id) { idEmpleado = id; }
void Venta::setFecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
}
void Venta::setMontoTotal(float m) { montoTotal = m; }
void Venta::setEstado(bool e) { estado = e; }

int Venta::getIDVenta() const { return idVenta; }
int Venta::getIDEmpleado() const { return idEmpleado; }
float Venta::getMontoTotal() const { return montoTotal; }
bool Venta::getEstado() const { return estado; }
int Venta::getDia() const { return dia; }
int Venta::getMes() const { return mes; }
int Venta::getAnio() const { return anio; }

bool Venta::guardarEnArchivo() const {
    ofstream archivo("ventas.dat", ios::app | ios::binary);
    if (!archivo) return false;
    archivo.write(reinterpret_cast<const char*>(this), sizeof(Venta));
    archivo.close();
    return true;
}

void Venta::mostrar() const {
    cout << "ID Venta: " << idVenta << endl;
    cout << "ID Empleado: " << idEmpleado << endl;
    cout << "Fecha: " << dia << "/" << mes << "/" << anio << endl;
    cout << "Monto total: $" << montoTotal << endl;
    cout << "Estado: " << (estado ? "Activa" : "Inactiva") << endl;
    cout << endl;
}

#endif
