#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX_PRODUCTOS = 200;

class Producto {
private:
    int id;
    char titulo[30];
    float precioUnitario;
    int stock;
    bool estado;
    bool tipo; // true: Comic / false: Manga
    int idAutor;
    int idEditorial;
    int idGenero;
    int idSerie;

public:
    Producto();

    // Getters
    int getID() const;
    const char* getTitulo() const;
    float getPrecioUnitario() const;
    int getStock() const;
    bool getEstado() const;
    bool getTipo() const;
    int getIDAutor() const;
    int getIDEditorial() const;
    int getIDGenero() const;
    int getIDSerie() const;

    // Setters
    void setID(int);
    void setTitulo(const char*);
    void setPrecioUnitario(float);
    void setStock(int);
    void setEstado(bool);
    void setTipo(bool);
    void setIDAutor(int);
    void setIDEditorial(int);
    void setIDGenero(int);
    void setIDSerie(int);

    // Funciones ABML
    void nuevoRegistro();
    void mostrar() const;
    void modificar();
    void bajaProducto();
    void levantarProducto();
    bool esActivo() const;
};

// ========== IMPLEMENTACION ==========

Producto::Producto() {
    id = 0;
    strcpy(titulo, "Sin titulo");
    precioUnitario = 0.0;
    stock = 0;
    estado = true;
    tipo = true;
    idAutor = 0;
    idEditorial = 0;
    idGenero = 0;
    idSerie = 0;
}

// SETTERS
void Producto::setID(int v) { id = v; }
void Producto::setTitulo(const char* t) { strncpy(titulo, t, 29); titulo[29] = '\0'; }
void Producto::setPrecioUnitario(float p) { precioUnitario = p; }
void Producto::setStock(int s) { stock = s; }
void Producto::setEstado(bool e) { estado = e; }
void Producto::setTipo(bool t) { tipo = t; }
void Producto::setIDAutor(int a) { idAutor = a; }
void Producto::setIDEditorial(int e) { idEditorial = e; }
void Producto::setIDGenero(int g) { idGenero = g; }
void Producto::setIDSerie(int s) { idSerie = s; }

// GETTERS
int Producto::getID() const { return id; }
const char* Producto::getTitulo() const { return titulo; }
float Producto::getPrecioUnitario() const { return precioUnitario; }
int Producto::getStock() const { return stock; }
bool Producto::getEstado() const { return estado; }
bool Producto::getTipo() const { return tipo; }
int Producto::getIDAutor() const { return idAutor; }
int Producto::getIDEditorial() const { return idEditorial; }
int Producto::getIDGenero() const { return idGenero; }
int Producto::getIDSerie() const { return idSerie; }

bool Producto::esActivo() const { return estado; }


// Alta
void Producto::nuevoRegistro() {
    ofstream file("productos.dat", ios::app | ios::binary);
    if (!file) {
        cout << "No se pudo abrir productos.dat" << endl;
        system("pause");
        return;
    }

    cout << "Ingrese ID: ";
    cin >> id;
    cin.ignore();

    cout << "Ingrese Titulo: ";
    cin.getline(titulo, 50);

    do {
      cout << "Ingrese Precio Unitario (>0): ";
      precioUnitario = Utils::checkInputIsNumber();
    } while(precioUnitario<=0);

    do {
      cout << "Ingrese Stock (>=0): ";
      stock = Utils::checkInputIsNumber();
    } while(stock<0);

    int t;
    cout << "Tipo (1: Comic / 0: Manga): ";
    cin >> t;
    tipo = (t == 1);
    estado = true;

    file.write(reinterpret_cast<char*>(this), sizeof(Producto));
    file.close();

    cout << "Producto guardado" << endl;
    system("pause");
}

// Mostrar
void Producto::mostrar() const {
    cout << left << setw(5) << id
         << setw(30) << titulo
         << setw(10) << precioUnitario
         << setw(10) << stock
         << setw(10) << (tipo ? "Comic" : "Manga")
         << setw(10) << (estado ? "Activo" : "Baja") << endl;
}


bool existeRegistro(int idBuscar) {
    Producto e;
    ifstream file("productos.dat", ios::binary);
    if (!file) return false;

    while (file.read(reinterpret_cast<char*>(&e), sizeof(Producto))) {
        if (e.getID() == idBuscar && e.getEstado()) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
// Baja l�gica
void Producto::bajaProducto() {
    fstream file("productos.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir productos.dat" << endl;
        system("pause");
        return;
    }

    int idBuscar;
    cout << "ID a dar de baja: ";
    cin >> idBuscar;

    Producto reg;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&reg), sizeof(Producto))) {
        if (reg.getID() == idBuscar && reg.getEstado()) {
            reg.setEstado(false);
            file.seekp(pos * sizeof(Producto), ios::beg);
            file.write(reinterpret_cast<char*>(&reg), sizeof(Producto));
            cout << "Producto dado de baja" << endl;
            file.close();
            system("pause");
            return;
        }
        pos++;
    }

    cout << "Producto no encontrado" << endl;
    file.close();
    system("pause");
}

// Levantar l�gica
void Producto::levantarProducto() {
    fstream file("productos.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir productos.dat" << endl;
        system("pause");
        return;
    }

    int idBuscar;
    cout << "ID a reactivar: ";
    cin >> idBuscar;

    Producto reg;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&reg), sizeof(Producto))) {
        if (reg.getID() == idBuscar && !reg.getEstado()) {
            reg.setEstado(true);
            file.seekp(pos * sizeof(Producto), ios::beg);
            file.write(reinterpret_cast<char*>(&reg), sizeof(Producto));
            cout << "Producto reactivado" << endl;
            file.close();
            system("pause");
            return;
        }
        pos++;
    }

    cout << "Producto no encontrado o ya activo" << endl;
    file.close();
    system("pause");
}

// Modificar
void Producto::modificar() {
    fstream file("productos.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "No se pudo abrir productos.dat" << endl;
        system("pause");
        return;
    }

    int idBuscar;
    cout << "ID a modificar: ";
    cin >> idBuscar;

    Producto reg;
    int pos = 0;
    while (file.read(reinterpret_cast<char*>(&reg), sizeof(Producto))) {
        if (reg.getID() == idBuscar && reg.getEstado()) {
            cout << "Nuevo titulo: ";
            cin.ignore();
            cin.getline(reg.titulo, 50);

            cout << "Nuevo precio: ";
            cin >> reg.precioUnitario;

            cout << "Nuevo stock: ";
            cin >> reg.stock;

            file.seekp(pos * sizeof(Producto), ios::beg);
            file.write(reinterpret_cast<char*>(&reg), sizeof(Producto));
            cout << "Producto modificado" << endl;
            file.close();
            system("pause");
            return;
        }
        pos++;
    }

    cout << "Producto no encontrado" << endl;
    file.close();
    system("pause");
}

// ------------------------- ORDENAR Y MOSTRAR -------------------------


int cargarProductos(Producto v[], int tam) {
    ifstream file("productos.dat", ios::binary);
    if (!file) return 0;

    Producto p;
    int i = 0;
    while (file.read(reinterpret_cast<char*>(&p), sizeof(Producto)) && i < tam) {
        if (p.getEstado()) {
            v[i] = p;
            i++;
        }
    }
    file.close();
    return i;
}

void ordenarPorID(Producto v[], int n) {
    Producto aux;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j].getID() > v[j + 1].getID()) {
                aux = v[j]; v[j] = v[j + 1]; v[j + 1] = aux;
            }
        }
    }
}

void ordenarPorTitulo(Producto v[], int n) {
    Producto aux;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(v[j].getTitulo(), v[j + 1].getTitulo()) > 0) {
                aux = v[j]; v[j] = v[j + 1]; v[j + 1] = aux;
            }
        }
    }
}

void ordenarPorPrecio(Producto v[], int n) {
    Producto aux;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j].getPrecioUnitario() > v[j + 1].getPrecioUnitario()) {
                aux = v[j]; v[j] = v[j + 1]; v[j + 1] = aux;
            }
        }
    }
}

void ordenarPorStock(Producto v[], int n) {
    Producto aux;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j].getStock() > v[j + 1].getStock()) {
                aux = v[j]; v[j] = v[j + 1]; v[j + 1] = aux;
            }
        }
    }
}

void ordenarPorTipo(Producto v[], int n) {
    Producto aux;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j].getTipo() > v[j + 1].getTipo()) {
                aux = v[j]; v[j] = v[j + 1]; v[j + 1] = aux;
            }
        }
    }
}

void mostrarProductosTabla(Producto v[], int n) {
    cout << left << setw(5) << "ID"
         << setw(30) << "Titulo"
         << setw(10) << "Precio"
         << setw(10) << "Stock"
         << setw(10) << "Tipo"
         << setw(10) << "Estado" << endl;

    cout << string(75, '-') << endl;

    for (int i = 0; i < n; i++) v[i].mostrar();

    cout << endl;
}

void listarProductosOrdenados(bool continuarConVenta = false) {
    Producto v[MAX_PRODUCTOS];
    int n = cargarProductos(v, MAX_PRODUCTOS);

    if (n == 0) {
        cout << "No hay productos activos para mostrar." << endl;
        system("pause");
        return;
    }

    int opc;
    do {
        cout << "=== LISTADO ORDENADO DE PRODUCTOS ===" << endl;
        cout << "1. Ordenar por ID" << endl;
        cout << "2. Ordenar por Titulo" << endl;
        cout << "3. Ordenar por Precio" << endl;
        cout << "4. Ordenar por Stock" << endl;
        cout << "5. Ordenar por Tipo" << endl;
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> opc;

        system("cls");

        switch (opc) {
            case 1:
                ordenarPorID(v, n);
            break;
            case 2:
                ordenarPorTitulo(v, n);
            break;
            case 3:
                ordenarPorPrecio(v, n);
            break;
            case 4:
                ordenarPorStock(v, n);
            break;
            case 5:
                ordenarPorTipo(v, n);

            break;
            case 0: return;
            default: cout << "Opcion invalida." << endl; break;
        }

        if (opc != 0) {
            mostrarProductosTabla(v, n);
            if (continuarConVenta) {return;}
            system("pause");
            system("cls");
        }

    } while (opc != 0);
}

#endif
