#ifndef VENTA_H
#define VENTA_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "Producto.h"
#include "Empleado.h"
#include "Venta.h"
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

    // M�todos
    void mostrar() const;
    bool guardarEnArchivo() const;
    void generar();


};



// --------------------- CONFIGURACION ---------------------
const int STOCK_MINIMO = 5;

// --------------------- UTILIDADES ---------------------

int generarIDVenta() {
    ifstream file("ventas.dat", ios::binary | ios::ate);
    return file ? file.tellg() / sizeof(Venta) + 1 : 1;
}

int contarEmpleadosActivos() {
    Empleado e;
    ifstream file("empleados.dat", ios::binary);
    if (!file) return 0;

    int count = 0;
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Empleado))) {
        if (e.getEstado()) count++;
    }
    file.close();
    return count;
}

int obtenerIDEmpleadoAleatorio() {
    Empleado e;
    ifstream file("empleados.dat", ios::binary);
    if (!file) return -1;

    const int MAX = 100;
    int ids[MAX], total = 0;

    while (file.read(reinterpret_cast<char*>(&e), sizeof(Empleado)) && total < MAX) {
        if (e.getEstado()) {
            ids[total] = e.getID();
            total++;
        }
    }
    file.close();

    if (total == 0) return -1;

    srand(time(0));
    return ids[rand() % total];
}

bool descontarStock(int idProducto, int cantidad) {
    fstream file("productos.dat", ios::in | ios::out | ios::binary);
    if (!file) return false;

    Producto p;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.getID() == idProducto && p.getEstado()) {
            if (p.getStock() >= cantidad) {
                p.setStock(p.getStock() - cantidad);
                file.seekp(pos * sizeof(Producto), ios::beg);
                file.write(reinterpret_cast<char*>(&p), sizeof(Producto));
                file.close();
                return true;
            } else {
                file.close();
                return false;
            }
        }
        pos++;
    }

    file.close();
    return false;
}

// --------------------- FUNCION 1: COMPRA ALEATORIA ---------------------

void generarCompraAleatoria() {
    Producto p;
    Producto productosDisponibles[100];
    int total = 0;

    ifstream archi("productos.dat", ios::binary);
    if (!archi) {
        cout << "No hay productos cargados." << endl;
        return;
    }

    while (archi.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.getEstado() && p.getStock() >= STOCK_MINIMO) {
            productosDisponibles[total] = p;
            total++;
        }
    }
    archi.close();

    if (total == 0) {
        cout << "No hay productos con stock suficiente." << endl;
        return;
    }

    srand(time(0));
    float totalVenta = 0;
    int cantProductos = 0;
    int productosComprados[10];
    int cantidades[10];

    while (cantProductos < 10 && rand() % 100 < (100 - cantProductos * 10)) {
        int pos = rand() % total;
        int cantidad = 1 + rand() % productosDisponibles[pos].getStock();

        if (descontarStock(productosDisponibles[pos].getID(), cantidad)) {
            productosComprados[cantProductos] = productosDisponibles[pos].getID();
            cantidades[cantProductos] = cantidad;
            totalVenta += cantidad * productosDisponibles[pos].getPrecioUnitario();
            cantProductos++;
        }
    }

    int idEmp = obtenerIDEmpleadoAleatorio();
    if (idEmp == -1) {
        cout << "No hay empleados activos." << endl;
        return;
    }

    time_t t = time(0);
    tm* now = localtime(&t);

    Venta v;
    v.setIDVenta(generarIDVenta());
    v.setIDEmpleado(idEmp);
    v.setFecha(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    v.setMontoTotal(totalVenta);
    v.setEstado(true);

    if (v.guardarEnArchivo()) {
        cout << "Compra aleatoria generada correctamente." << endl;
        cout << "Monto total: $" << totalVenta << endl;
        cout << "Empleado: " << idEmp << endl;
    } else {
        cout << "Error al guardar la venta." << endl;
    }
}
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
void Venta::generar() {

    //listarProductosOrdenados();

    int idProducto, cantidad;
    cout << "REGISTRANDO UNA NUEVA VENTA\n\nIngrese ID del producto: ";
    cin >> idProducto;
    cout << "Ingrese cantidad: ";
    cin >> cantidad;


    if (!descontarStock(idProducto, cantidad)) {
        cout << "Stock insuficiente o producto no valido." << endl;
        return;
    }

    Producto p;
    ifstream archi("productos.dat", ios::binary);
    while (archi.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.getID() == idProducto) break;
    }
    archi.close();

    float total = cantidad * p.getPrecioUnitario();

    listarEmpleados();
    int idEmp;
    cout << "Ingrese ID del empleado que registra la venta: ";
    cin >> idEmp;

    time_t t = time(0);
    tm* now = localtime(&t);

    Venta v;
    v.setIDVenta(generarIDVenta());
    v.setIDEmpleado(idEmp);
    v.setFecha(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    v.setMontoTotal(total);
    v.setEstado(true);

    if (v.guardarEnArchivo()) {
        cout << "Compra registrada correctamente." << endl;
        cout << "Monto: $" << total << endl;
    } else {
        cout << "Error al guardar la venta." << endl;
    }
}











#endif
