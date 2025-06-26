#ifndef GENERO_H
#define GENERO_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

class Genero {
private:
    int id;
    char nombre[50];
    bool estado;

public:
    Genero();

    // Setters
    void setID(int);
    void setNombre(const char*);
    void setEstado(bool);

    // Getters
    int getID() const;
    const char* getNombre() const;
    bool getEstado() const;

    // Funciones ABML
    void nuevoRegistro();
    void mostrar() const;
    void modificar();
    void baja();
    void levantar();

    // Estado
    bool esActivo() const;
};

// ---------------------- Implementacion ----------------------

Genero::Genero() {
    id = 0;
    strcpy(nombre, "Sin Genero");
    estado = true;
}

void Genero::setID(int v) { id = v; }
void Genero::setNombre(const char* n) { strncpy(nombre, n, 49); nombre[49] = '\0'; }
void Genero::setEstado(bool e) { estado = e; }

int Genero::getID() const { return id; }
const char* Genero::getNombre() const { return nombre; }
bool Genero::getEstado() const { return estado; }
bool Genero::esActivo() const { return estado; }

bool existeIDGenero(int idBuscar) {
    Genero g;
    ifstream file("generos.dat", ios::binary);
    if (!file) return false;
    while (file.read(reinterpret_cast<char*>(&g), sizeof(Genero))) {
        if (g.getID() == idBuscar && g.getEstado()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void listarGeneros() {
    Genero g;
    ifstream file("generos.dat", ios::binary);
    if (!file) {
        cout << "No hay generos cargados" << endl;
        return;
    }
    while (file.read(reinterpret_cast<char*>(&g), sizeof(Genero))) {
        if (g.getEstado()) g.mostrar();
    }
    file.close();
}

void Genero::nuevoRegistro() {
    listarGeneros();

    ofstream file("generos.dat", ios::app | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int idTemp;
    cout << "Ingrese ID: ";
    cin >> idTemp;

    if (existeIDGenero(idTemp)) {
        cout << "ID ya existente" << endl;
        return;
    }
    setID(idTemp);

    char nombreTemp[50];
    cout << "Ingrese nombre: ";
    cin.ignore();
    cin.getline(nombreTemp, 50);
    setNombre(nombreTemp);

    estado = true;

    file.write(reinterpret_cast<char*>(this), sizeof(Genero));
    file.close();

    cout << "Genero guardado" << endl;
}

void Genero::mostrar() const {
    cout << "ID: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Estado: " << (estado ? "Activo" : "Baja") << endl;
    cout << endl;
}

void Genero::modificar() {
    fstream file("generos.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int idBuscar;
    cout << "Ingrese ID a modificar: ";
    cin >> idBuscar;

    Genero g;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&g), sizeof(Genero))) {
        if (g.getID() == idBuscar && g.getEstado()) {
            char nuevoNombre[50];
            cout << "Nuevo nombre: ";
            cin.ignore();
            cin.getline(nuevoNombre, 50);
            g.setNombre(nuevoNombre);

            file.seekp(pos * sizeof(Genero), ios::beg);
            file.write(reinterpret_cast<char*>(&g), sizeof(Genero));
            cout << "Genero modificado" << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "Genero no encontrado" << endl;
    file.close();
}

void Genero::baja() {
    fstream file("generos.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int idBuscar;
    cout << "ID a dar de baja: ";
    cin >> idBuscar;

    Genero g;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&g), sizeof(Genero))) {
        if (g.getID() == idBuscar && g.getEstado()) {
            g.setEstado(false);
            file.seekp(pos * sizeof(Genero), ios::beg);
            file.write(reinterpret_cast<char*>(&g), sizeof(Genero));
            cout << "Genero dado de baja" << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "No encontrado o ya dado de baja" << endl;
    file.close();
}

void Genero::levantar() {
    fstream file("generos.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    int idBuscar;
    cout << "ID a reactivar: ";
    cin >> idBuscar;

    Genero g;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&g), sizeof(Genero))) {
        if (g.getID() == idBuscar && !g.getEstado()) {
            g.setEstado(true);
            file.seekp(pos * sizeof(Genero), ios::beg);
            file.write(reinterpret_cast<char*>(&g), sizeof(Genero));
            cout << "Genero reactivado" << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "No encontrado o ya activo" << endl;
    file.close();
}

void mostrarNombreGeneroPorID(int idBuscado) {
    Genero g;
    ifstream archivo("generos.dat", ios::binary);
    if (!archivo) {
        cout << "No se pudo abrir genero.dat" << endl;
        return;
    }

    while (archivo.read(reinterpret_cast<char*>(&g), sizeof(Genero))) {
        if (g.getID() == idBuscado && g.getEstado()) {
            cout << "ID Genero: " << g.getID() << " - Nombre: " << g.getNombre() << endl;
            archivo.close();
            return;
        }
    }

    cout << "Genero no encontrado" << endl;
    archivo.close();
}

const int MAX_GENEROS = 100;

void ordenarGenerosPorNombre(Genero vec[], int total) {
    Genero aux;
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

void ordenarGenerosPorID(Genero vec[], int total) {
    Genero aux;
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

void mostrarGenerosTabla(Genero vec[], int total) {
    cout << left << setw(5) << "ID" << setw(30) << "Nombre" << endl;
    cout << string(35, '-') << endl;
    for (int i = 0; i < total; i++) {
        cout << setw(5) << vec[i].getID()
             << setw(30) << vec[i].getNombre() << endl;
    }
    cout << endl;
}

int cargarGeneros(Genero vec[], int tam) {
    Genero g;
    int i = 0;
    ifstream file("generos.dat", ios::binary);
    if (!file) return 0;

    while (file.read(reinterpret_cast<char*>(&g), sizeof(Genero)) && i < tam) {
        cout << "Leyendo ID: " << g.getID() << " Estado: " << g.getEstado() << endl;  // DEBUG
        if (g.getEstado()) {
            vec[i] = g;
            i++;
        }
    }
    file.close();
    return i;
}

void menuListarGenerosOrdenados() {
    Genero vec[MAX_GENEROS];
    int total = cargarGeneros(vec, MAX_GENEROS);

    if (total == 0) {
        cout << "No hay generos activos para mostrar." << endl;
        system("pause");
        return;
    }

    int opcion;
    do {
        system("cls");
        cout << "--- ORDENAR GENEROS ---" << endl;
        cout << "1. Ordenar por ID" << endl;
        cout << "2. Ordenar por Nombre" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
            case 1:
                ordenarGenerosPorID(vec, total);
                mostrarGenerosTabla(vec, total);
                break;
            case 2:
                ordenarGenerosPorNombre(vec, total);
                mostrarGenerosTabla(vec, total);
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida."<<endl;
        }

        if (opcion != 0) system("pause");
    } while (opcion != 0);
}


#endif
