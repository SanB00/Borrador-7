#ifndef AUTOR_H
#define AUTOR_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_AUTORES = 100;

class Autor {
private:
    int id;
    char nombre[30];
    bool estado;

public:
    Autor();

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
    void nuevoRegistro();

};

// =================== IMPLEMENTACIÓN ===================

Autor::Autor() {
    id = 0;
    strcpy(nombre, "Sin Nombre");
    estado = true;
}

void Autor::setID(int v) { id = v; }
void Autor::setNombre(const char* n) { strncpy(nombre, n, 29); nombre[29] = '\0'; }
void Autor::setEstado(bool e) { estado = e; }

int Autor::getID() const { return id; }
const char* Autor::getNombre() const { return nombre; }
bool Autor::getEstado() const { return estado; }
bool Autor::esActivo() const { return estado; }

bool existeIDAutor(int idBuscar) {
    Autor a;
    ifstream file("autor.dat", ios::binary);
    if (!file) return false;

    while (file.read(reinterpret_cast<char*>(&a), sizeof(Autor))) {
        if (a.getID() == idBuscar && a.getEstado()) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void nuevoRegistroAutor() {
    ofstream file("autor.dat", ios::app | ios::binary);
    if (!file) {
        cout << "No se pudo abrir autor.dat para escritura." << endl;
        system("pause");
        return;
    }

    Autor a;
    int id;
    char nombre[30];

    cout << "Ingrese ID: ";
    cin >> id;

    if (existeIDAutor(id)) {
        cout << "ID ya existente.\n";
        system("pause");
        return;
    }

    a.setID(id);
    cin.ignore();
    cout << "Ingrese nombre: ";
    cin.getline(nombre, 30);
    a.setNombre(nombre);
    a.setEstado(true);

    file.write(reinterpret_cast<char*>(&a), sizeof(Autor));
    file.close();

    cout << "Autor guardado correctamente.\n";
    system("pause");
}

void Autor::nuevoRegistro() {
    ofstream file("autor.dat", ios::app | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    int id;
    char nombre[50];

    cout << "Ingrese ID: ";
    cin >> id;
    cin.ignore();
    cout << "Ingrese nombre del autor: ";
    cin.getline(nombre, 50);

    setID(id);
    setNombre(nombre);
    setEstado(true);

    file.write(reinterpret_cast<char*>(this), sizeof(Autor));
    file.close();

    cout << "Autor guardado." << endl;
    system("pause");
}




void Autor::mostrar() const {
    cout << "ID: " << id << " | Nombre: " << nombre
         << " | Estado: " << (estado ? "Activo" : "Baja") << endl;
}

void listarAutores() {
    ifstream file("autor.dat", ios::binary);
    if (!file) {
        cout << "No se pudo abrir autor.dat" << endl;
        system("pause");
        return;
    }

    Autor a;
    cout << "--- LISTADO DE AUTORES ---\n";
    while (file.read(reinterpret_cast<char*>(&a), sizeof(Autor))) {
        if (a.getEstado()) {
            a.mostrar();
        }
    }

    file.close();
    system("pause");
}

void Autor::modificar() {
    fstream file("autor.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int idBuscar;
    cout << "ID a modificar: ";
    cin >> idBuscar;

    Autor a;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&a), sizeof(Autor))) {
        if (a.getID() == idBuscar && a.getEstado()) {
            char nuevoNombre[30];
            cout << "Nuevo nombre: ";
            cin.ignore();
            cin.getline(nuevoNombre, 30);
            a.setNombre(nuevoNombre);

            file.seekp(pos * sizeof(Autor), ios::beg);
            file.write(reinterpret_cast<char*>(&a), sizeof(Autor));
            cout << "Autor modificado." << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "Autor no encontrado." << endl;
    file.close();
}

void Autor::baja() {
    fstream file("autor.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int idBuscar;
    cout << "ID a dar de baja: ";
    cin >> idBuscar;

    Autor a;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&a), sizeof(Autor))) {
        if (a.getID() == idBuscar && a.getEstado()) {
            a.setEstado(false);
            file.seekp(pos * sizeof(Autor), ios::beg);
            file.write(reinterpret_cast<char*>(&a), sizeof(Autor));
            cout << "Autor dado de baja." << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "Autor no encontrado o ya estaba dado de baja." << endl;
    file.close();
}

void Autor::levantar() {
    fstream file("autor.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int idBuscar;
    cout << "ID a reactivar: ";
    cin >> idBuscar;

    Autor a;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&a), sizeof(Autor))) {
        if (a.getID() == idBuscar && !a.getEstado()) {
            a.setEstado(true);
            file.seekp(pos * sizeof(Autor), ios::beg);
            file.write(reinterpret_cast<char*>(&a), sizeof(Autor));
            cout << "Autor reactivado." << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "Autor no encontrado o ya activo." << endl;
    file.close();
}

// =================== ORDENAMIENTO ===================

int cargarAutores(Autor vec[], int tam) {
    Autor a;
    int i = 0;
    ifstream file("autor.dat", ios::binary);
    if (!file) return 0;

    while (file.read(reinterpret_cast<char*>(&a), sizeof(Autor)) && i < tam) {
        if (a.getEstado()) {
            vec[i] = a;
            i++;
        }
    }

    file.close();
    return i;
}

void ordenarAutoresPorID(Autor vec[], int total) {
    Autor aux;
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

void ordenarAutoresPorNombre(Autor vec[], int total) {
    Autor aux;
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

void mostrarAutoresTabla(Autor vec[], int total) {
    cout << left << setw(5) << "ID" << setw(30) << "Nombre" << endl;
    cout << string(35, '-') << endl;
    for (int i = 0; i < total; i++) {
        cout << setw(5) << vec[i].getID()
             << setw(30) << vec[i].getNombre() << endl;
    }
    cout << endl;
}

void menuListarAutoresOrdenados() {
    Autor vec[MAX_AUTORES];
    int total = cargarAutores(vec, MAX_AUTORES);

    if (total == 0) {
        cout << "No hay autores activos para mostrar.\n";
        system("pause");
        return;
    }

    int opcion;
    do {
        system("cls");
        cout << "--- ORDENAR AUTORES ---" << endl;
        cout << "1. Ordenar por ID" << endl;
        cout << "2. Ordenar por Nombre" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
            case 1:
                ordenarAutoresPorID(vec, total);
                mostrarAutoresTabla(vec, total);
                break;
            case 2:
                ordenarAutoresPorNombre(vec, total);
                mostrarAutoresTabla(vec, total);
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
