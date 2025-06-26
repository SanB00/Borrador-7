#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_EMPLEADOS = 100;

class Empleado {
private:
    int id;
    char nombre[30];
    bool estado;

public:
    Empleado();

    void setID(int);
    void setNombre(const char*);
    void setEstado(bool);

    int getID() const;
    const char* getNombre() const;
    bool getEstado() const;
    bool esActivo() const;

    void mostrar() const;
    void modificar();
    void baja();
    void levantar();
};

// =================== IMPLEMENTACI�N ===================

Empleado::Empleado() {
    id = 0;
    strcpy(nombre, "Sin Nombre");
    estado = true;
}

void Empleado::setID(int v) { id = v; }
void Empleado::setNombre(const char* n) { strncpy(nombre, n, 29); nombre[29] = '\0'; }
void Empleado::setEstado(bool e) { estado = e; }

int Empleado::getID() const { return id; }
const char* Empleado::getNombre() const { return nombre; }
bool Empleado::getEstado() const { return estado; }
bool Empleado::esActivo() const { return estado; }

// =================== FUNCIONES AUXILIARES ===================

bool existeIDEmpleado(int idBuscar) {
    Empleado e;
    ifstream file("empleados.dat", ios::binary);
    if (!file) return false;

    while (file.read(reinterpret_cast<char*>(&e), sizeof(Empleado))) {
        if (e.getID() == idBuscar && e.getEstado()) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void nuevoRegistroEmpleado() {
    ofstream file("empleados.dat", ios::app | ios::binary);
    if (!file) {
        cout << "No se pudo abrir empleados.dat para escritura." << endl;
        system("pause");
        return;
    }

    Empleado e;
    int id;
    char nombre[30];

    cout << "Ingrese ID: ";
    cin >> id;

    if (existeIDEmpleado(id)) {
        cout << "ID ya existente.\n";
        system("pause");
        return;
    }

    e.setID(id);
    cin.ignore();
    cout << "Ingrese nombre: ";
    cin.getline(nombre, 30);
    e.setNombre(nombre);
    e.setEstado(true);

    file.write(reinterpret_cast<char*>(&e), sizeof(Empleado));
    file.close();

    cout << "Empleado guardado correctamente.\n";
    system("pause");
}

void Empleado::mostrar() const {
    cout << "ID: " << id << " | Nombre: " << nombre
         << " | Estado: " << (estado ? "Activo" : "Baja") << endl;
}

void listarEmpleados() {
    ifstream file("empleados.dat", ios::binary);
    if (!file) {
        cout << "No se pudo abrir empleados.dat" << endl;
        system("pause");
        return;
    }

    Empleado e;
    cout << "--- LISTADO DE EMPLEADOS ---\n";
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Empleado))) {
        if (e.getEstado()) {
            e.mostrar();
        }
    }

    file.close();
    system("pause");
}

void Empleado::modificar() {
    fstream file("empleados.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int idBuscar;
    cout << "ID a modificar: ";
    cin >> idBuscar;

    Empleado e;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Empleado))) {
        if (e.getID() == idBuscar && e.getEstado()) {
            char nuevoNombre[30];
            cout << "Nuevo nombre: ";
            cin.ignore();
            cin.getline(nuevoNombre, 30);
            e.setNombre(nuevoNombre);

            file.seekp(pos * sizeof(Empleado), ios::beg);
            file.write(reinterpret_cast<char*>(&e), sizeof(Empleado));
            cout << "Empleado modificado." << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "Empleado no encontrado." << endl;
    file.close();
}

void Empleado::baja() {
    fstream file("empleados.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int idBuscar;
    cout << "ID a dar de baja: ";
    cin >> idBuscar;

    Empleado e;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Empleado))) {
        if (e.getID() == idBuscar && e.getEstado()) {
            e.setEstado(false);
            file.seekp(pos * sizeof(Empleado), ios::beg);
            file.write(reinterpret_cast<char*>(&e), sizeof(Empleado));
            cout << "Empleado dado de baja." << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "Empleado no encontrado o ya estaba dado de baja." << endl;
    file.close();
}

void Empleado::levantar() {
    fstream file("empleados.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int idBuscar;
    cout << "ID a reactivar: ";
    cin >> idBuscar;

    Empleado e;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Empleado))) {
        if (e.getID() == idBuscar && !e.getEstado()) {
            e.setEstado(true);
            file.seekp(pos * sizeof(Empleado), ios::beg);
            file.write(reinterpret_cast<char*>(&e), sizeof(Empleado));
            cout << "Empleado reactivado." << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "Empleado no encontrado o ya activo." << endl;
    file.close();
}

// =================== ORDENAMIENTO ===================

int cargarEmpleados(Empleado vec[], int tam) {
    Empleado e;
    int i = 0;
    ifstream file("empleados.dat", ios::binary);
    if (!file) return 0;

    while (file.read(reinterpret_cast<char*>(&e), sizeof(Empleado)) && i < tam) {
        if (e.getEstado()) {
            vec[i] = e;
            i++;
        }
    }

    file.close();
    return i;
}

void ordenarEmpleadosPorID(Empleado vec[], int total) {
    Empleado aux;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (vec[j].getID() > vec[j + 1].getID()) {
                aux = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = aux;
            }
        }
    }
}

void ordenarEmpleadosPorNombre(Empleado vec[], int total) {
    Empleado aux;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(vec[j].getNombre(), vec[j + 1].getNombre()) > 0) {
                aux = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = aux;
            }
        }
    }
}

void mostrarEmpleadosTabla(Empleado vec[], int total) {
    cout << left << setw(5) << "ID" << setw(30) << "Nombre" << endl;
    cout << string(35, '-') << endl;
    for (int i = 0; i < total; i++) {
        cout << setw(5) << vec[i].getID()
             << setw(30) << vec[i].getNombre() << endl;
    }
    cout << endl;
}

void menuListarEmpleadosOrdenados() {
    Empleado vec[MAX_EMPLEADOS];
    int total = cargarEmpleados(vec, MAX_EMPLEADOS);

    if (total == 0) {
        cout << "No hay empleados activos para mostrar.\n";
        system("pause");
        return;
    }

    int opcion;
    do {
        system("cls");
        cout << "--- ORDENAR EMPLEADOS ---" << endl;
        cout << "1. Ordenar por ID" << endl;
        cout << "2. Ordenar por Nombre" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
            case 1:
                ordenarEmpleadosPorID(vec, total);
                mostrarEmpleadosTabla(vec, total);
                break;
            case 2:
                ordenarEmpleadosPorNombre(vec, total);
                mostrarEmpleadosTabla(vec, total);
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida.\n";
        }

        if (opcion != 0) system("pause");
    } while (opcion != 0);
}

#endif

