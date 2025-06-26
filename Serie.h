#ifndef SERIE_H
#define SERIE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

class Serie {
private:
    int id;
    char nombre[50];
    bool estado;

public:
    Serie() {
        id = 0;
        strcpy(nombre, "Sin Serie");
        estado = true;
    }

    // SETTERS
    void setID(int v) { id = v; }
    void setNombre(const char* n) { strncpy(nombre, n, 49); nombre[49] = '\0'; }
    void setEstado(bool e) { estado = e; }

    // GETTERS
    int getID() const { return id; }
    const char* getNombre() const { return nombre; }
    bool getEstado() const { return estado; }

    // ABML
    void mostrar() const;
    void modificar();
    void baja();
    void levantar();
    bool esActivo() const { return estado; }
};

// ========== FUNCIONES AUXILIARES ==========

bool existeIDSerie(int idBuscar) {
    Serie s;
    ifstream file("series.dat", ios::binary);
    if (!file) return false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Serie))) {
        if (s.getID() == idBuscar && s.getEstado()) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void nuevoRegistroSerie() {
    ofstream file("series.dat", ios::app | ios::binary);
    if (!file) {
        cout << "No se pudo abrir series.dat" << endl;
        system("pause");
        return;
    }

    Serie s;
    int id;
    char nombre[50];

    cout << "Ingrese ID: ";
    cin >> id;
    if (existeIDSerie(id)) {
        cout << "ID ya existente" << endl;
        system("pause");
        return;
    }
    cin.ignore();
    cout << "Ingrese nombre de la serie: ";
    cin.getline(nombre, 50);

    s.setID(id);
    s.setNombre(nombre);
    s.setEstado(true);

    file.write(reinterpret_cast<char*>(&s), sizeof(Serie));
    file.close();
    cout << "Serie guardada." << endl;
    system("pause");
}

void listarSeries() {
    ifstream file("series.dat", ios::binary);
    if (!file) {
        cout << "No se pudo abrir series.dat" << endl;
        system("pause");
        return;
    }

    Serie s;
    cout << left << setw(5) << "ID" << setw(30) << "Nombre" << endl;
    cout << string(35, '-') << endl;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Serie))) {
        if (s.getEstado()) {
            cout << setw(5) << s.getID() << setw(30) << s.getNombre() << endl;
        }
    }

    file.close();
    system("pause");
}

void Serie::mostrar() const {
    cout << "ID: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
}

void Serie::modificar() {
    fstream file("series.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir series.dat" << endl;
        return;
    }

    int idBuscar;
    cout << "ID a modificar: ";
    cin >> idBuscar;

    Serie s;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Serie))) {
        if (s.getID() == idBuscar && s.getEstado()) {
            char nuevoNombre[50];
            cout << "Nuevo nombre: ";
            cin.ignore();
            cin.getline(nuevoNombre, 50);
            s.setNombre(nuevoNombre);

            file.seekp(pos * sizeof(Serie), ios::beg);
            file.write(reinterpret_cast<char*>(&s), sizeof(Serie));
            cout << "Serie modificada" << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "Serie no encontrada." << endl;
    file.close();
}

void Serie::baja() {
    fstream file("series.dat", ios::in | ios::out | ios::binary);
    if (!file) return;

    int idBuscar;
    cout << "ID a dar de baja: ";
    cin >> idBuscar;

    Serie s;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Serie))) {
        if (s.getID() == idBuscar && s.getEstado()) {
            s.setEstado(false);
            file.seekp(pos * sizeof(Serie), ios::beg);
            file.write(reinterpret_cast<char*>(&s), sizeof(Serie));
            cout << "Serie dada de baja" << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "No encontrada o ya inactiva" << endl;
    file.close();
}

void Serie::levantar() {
    fstream file("series.dat", ios::in | ios::out | ios::binary);
    if (!file) return;

    int idBuscar;
    cout << "ID a reactivar: ";
    cin >> idBuscar;

    Serie s;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Serie))) {
        if (s.getID() == idBuscar && !s.getEstado()) {
            s.setEstado(true);
            file.seekp(pos * sizeof(Serie), ios::beg);
            file.write(reinterpret_cast<char*>(&s), sizeof(Serie));
            cout << "Serie reactivada" << endl;
            file.close();
            return;
        }
        pos++;
    }

    cout << "No encontrada o ya activa" << endl;
    file.close();
}

void mostrarNombreSeriePorID(int idBuscado) {
    Serie s;
    ifstream file("series.dat", ios::binary);
    if (!file) return;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Serie))) {
        if (s.getID() == idBuscado && s.getEstado()) {
            cout << "ID: " << s.getID() << " - Nombre: " << s.getNombre() << endl;
            file.close();
            return;
        }
    }

    cout << "Serie no encontrada" << endl;
    file.close();
}

int cargarSeries(Serie vec[], int tam) {
    Serie s;
    int i = 0;
    ifstream file("series.dat", ios::binary);
    if (!file) return 0;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Serie)) && i < tam) {
        if (s.getEstado()) {
            vec[i] = s;
            i++;
        }
    }
    file.close();
    return i;
}

const int MAX_SERIES = 100;

void ordenarSeriesPorNombre(Serie vec[], int total) {
    Serie aux;
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

void ordenarSeriesPorID(Serie vec[], int total) {
    Serie aux;
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

void mostrarSeriesTabla(Serie vec[], int total) {
    cout << left << setw(5) << "ID" << setw(30) << "Nombre" << endl;
    cout << string(35, '-') << endl;
    for (int i = 0; i < total; i++) {
        cout << setw(5) << vec[i].getID()
             << setw(30) << vec[i].getNombre() << endl;
    }
    cout << endl;
}

void menuListarSeriesOrdenadas() {
    Serie vec[MAX_SERIES];
    int total = cargarSeries(vec, MAX_SERIES);

    if (total == 0) {
        cout << "No hay series activas para mostrar." << endl;
        system("pause");
        return;
    }

    int opcion;
    do {
        system("cls");
        cout << "--- ORDENAR SERIES ---" << endl;
        cout << "1. Ordenar por ID" << endl;
        cout << "2. Ordenar por Nombre" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
            case 1:
                ordenarSeriesPorID(vec, total);
                mostrarSeriesTabla(vec, total);
                break;
            case 2:
                ordenarSeriesPorNombre(vec, total);
                mostrarSeriesTabla(vec, total);
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida." << endl;
        }

        if (opcion != 0) system("pause");
    } while (opcion != 0);
}
#endif

