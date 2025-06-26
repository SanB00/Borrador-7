#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

class Editorial {
private:
    int id;
    char nombre[50];
    bool estado;

public:
    Editorial();

    void setID(int);
    void setNombre(const char*);
    void setEstado(bool);

    int getID() const;
    const char* getNombre() const;
    bool getEstado() const;
    bool esActivo() const;

    void nuevoRegistro();
    void mostrar() const;
    void modificar();
    void baja();
    void levantar();
};

// Constructor
Editorial::Editorial() {
    id = 0;
    strcpy(nombre, "Sin Editorial");
    estado = true;
}

// Setters
void Editorial::setID(int v) { id = v; }
void Editorial::setNombre(const char* n) { strncpy(nombre, n, 49); nombre[49] = '\0'; }
void Editorial::setEstado(bool e) { estado = e; }

// Getters
int Editorial::getID() const { return id; }
const char* Editorial::getNombre() const { return nombre; }
bool Editorial::getEstado() const { return estado; }
bool Editorial::esActivo() const { return estado; }

// Verifica si el ID ya existe (activo o no)
bool existeIDEditorial(int idBuscar) {
    Editorial e;
    ifstream file("editorial.dat", ios::binary);
    if (!file) return false;

    while (file.read(reinterpret_cast<char*>(&e), sizeof(Editorial))) {
        if (e.getID() == idBuscar) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// ---------- FUNCIONES ABML ----------

void Editorial::nuevoRegistro() {
    ofstream file("editorial.dat", ios::app | ios::binary);
    if (!file) {
        cout << "No se pudo abrir editorial.dat" << endl;
        system("pause");
        return;
    }

    int idTemp;
    char nombreTemp[50];

    cout << "Ingrese ID: ";
    cin >> idTemp;
    cin.ignore();

    if (existeIDEditorial(idTemp)) {
        cout << "ID ya existente. Registro cancelado." << endl;
        system("pause");
        return;
    }

    cout << "Ingrese nombre: ";
    cin.getline(nombreTemp, 50);

    Editorial e;
    e.setID(idTemp);
    e.setNombre(nombreTemp);
    e.setEstado(true);

    file.write(reinterpret_cast<char*>(&e), sizeof(Editorial));
    file.close();
    cout << "Editorial guardada correctamente." << endl;
    system("pause");
}

void Editorial::mostrar() const {
    cout << "ID: " << id << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl << endl;
}

void Editorial::modificar() {
    fstream file("editorial.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        system("pause");
        return;
    }

    int idBuscar;
    cout << "Ingrese ID a modificar: ";
    cin >> idBuscar;
    cin.ignore();

    Editorial e;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Editorial))) {
        if (e.getID() == idBuscar && e.getEstado()) {
            char nuevoNombre[50];
            cout << "Nuevo nombre: ";
            cin.getline(nuevoNombre, 50);
            e.setNombre(nuevoNombre);

            file.seekp(pos * sizeof(Editorial), ios::beg);
            file.write(reinterpret_cast<char*>(&e), sizeof(Editorial));
            cout << "Editorial modificada correctamente." << endl;
            file.close();
            system("pause");
            return;
        }
        pos++;
    }

    cout << "Editorial no encontrada." << endl;
    file.close();
    system("pause");
}

void Editorial::baja() {
    fstream file("editorial.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        system("pause");
        return;
    }

    int idBuscar;
    cout << "ID a dar de baja: ";
    cin >> idBuscar;

    Editorial e;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Editorial))) {
        if (e.getID() == idBuscar && e.getEstado()) {
            e.setEstado(false);
            file.seekp(pos * sizeof(Editorial), ios::beg);
            file.write(reinterpret_cast<char*>(&e), sizeof(Editorial));
            cout << "Editorial dada de baja correctamente." << endl;
            file.close();
            system("pause");
            return;
        }
        pos++;
    }

    cout << "No se encontr� el ID solicitado." << endl;
    file.close();
    system("pause");
}

void Editorial::levantar() {
    fstream file("editorial.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir el archivo" << endl;
        system("pause");
        return;
    }

    int idBuscar;
    cout << "ID a reactivar: ";
    cin >> idBuscar;

    Editorial e;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Editorial))) {
        if (e.getID() == idBuscar && !e.getEstado()) {
            e.setEstado(true);
            file.seekp(pos * sizeof(Editorial), ios::beg);
            file.write(reinterpret_cast<char*>(&e), sizeof(Editorial));
            cout << "Editorial reactivada correctamente." << endl;
            file.close();
            system("pause");
            return;
        }
        pos++;
    }

    cout << "No se encontr� el ID o ya est� activa." << endl;
    file.close();
    system("pause");
}


void mostrarNombreEditorialPorID(int idBuscado) {
    Editorial e;
    ifstream archivo("editorial.dat", ios::binary);
    if (!archivo) {
        cout << "No se pudo abrir editorial.dat" << endl;
        return;
    }

    while (archivo.read(reinterpret_cast<char*>(&e), sizeof(Editorial))) {
        if (e.getID() == idBuscado && e.getEstado()) {
            cout << "ID Editorial: " << e.getID() << " - Nombre: " << e.getNombre() << endl;
            archivo.close();
            return;
        }
    }

    cout << "Editorial no encontrada" << endl;
    archivo.close();
}

const int MAX_EDITORIALES = 100;

int cargarEditoriales(Editorial vec[], int tam) {
    Editorial e;
    int i = 0;
    ifstream file("editorial.dat", ios::binary);
    if (!file) return 0;

    while (file.read(reinterpret_cast<char*>(&e), sizeof(Editorial)) && i < tam) {
        if (e.getEstado()) {
            vec[i] = e;
            i++;
        }
    }
    file.close();
    return i;
}

void ordenarEditorialesPorNombre(Editorial vec[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(vec[j].getNombre(), vec[j + 1].getNombre()) > 0) {
                Editorial aux = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = aux;
            }
        }
    }
}

void ordenarEditorialesPorID(Editorial vec[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (vec[j].getID() > vec[j + 1].getID()) {
                Editorial aux = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = aux;
            }
        }
    }
}

void mostrarEditorialesTabla(Editorial vec[], int total) {
    cout << left << setw(5) << "ID" << setw(30) << "Nombre" << endl;
    cout << string(35, '-') << endl;
    for (int i = 0; i < total; i++) {
        cout << setw(5) << vec[i].getID()
             << setw(30) << vec[i].getNombre() << endl;
    }
    cout << endl;
}

void menuListarEditorialesOrdenadas() {
    Editorial vec[MAX_EDITORIALES];
    int total = cargarEditoriales(vec, MAX_EDITORIALES);

    if (total == 0) {
        cout << "No hay editoriales activas para mostrar.\n";
        system("pause");
        return;
    }

    int opcion;
    do {
        cout << "=== LISTADO ORDENADO DE EDITORIALES ===" << endl;
        cout << "1. Ordenar por ID" << endl;
        cout << "2. Ordenar por Nombre" << endl;
        cout << "0. Volver al menu anterior" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
            case 1:
                ordenarEditorialesPorID(vec, total);
                mostrarEditorialesTabla(vec, total);
                break;
            case 2:
                ordenarEditorialesPorNombre(vec, total);
                mostrarEditorialesTabla(vec, total);
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
        }

        if (opcion != 0) system("pause");
        system("cls");

    } while (opcion != 0);
}

// TODO: hacer una funcion para ver cuantas ventas tiene cada autor
/*int cantidadVentasPorAutor(int idAutor) {
    Venta v;
    int total = 0;
    ifstream file("ventas.dat", ios::binary);
    while (file.read(reinterpret_cast<char*>(&v), sizeof(Venta))) {
        if (v.getIDAutor() == idAutor) {
            total++;
        }
    }
    file.close();
    return total;
}
*/

#endif




