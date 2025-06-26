#ifndef INFORMEPRODUCTO_H
#define INFORMEPRODUCTO_H

#include "Producto.h"

void listarProductosPorAutor(int idAutor) {
    Producto p;
    bool encontrado = false;
    ifstream file("productos.dat", ios::binary);
    if (!file) {
        cout << "No se pudo abrir productos.dat" << endl;
        return;
    }

    while (file.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.getEstado() && p.getIDAutor() == idAutor) {
            p.mostrar();
            encontrado = true;
        }
    }
    file.close();
    if (!encontrado) {
        cout << "No se encontraron productos con ese ID de autor." << endl;
    }
}

void listarProductosPorEditorial(int idEditorial) {
    Producto p;
    bool encontrado = false;
    ifstream file("productos.dat", ios::binary);
    if (!file) {
        cout << "No se pudo abrir productos.dat" << endl;
        return;
    }

    while (file.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.getEstado() && p.getIDEditorial() == idEditorial) {
            p.mostrar();
            encontrado = true;
        }
    }
    file.close();
    if (!encontrado) {
        cout << "No se encontraron productos con ese ID de editorial." << endl;
    }
}

void listarProductosPorGenero(int idGenero) {
    Producto p;
    bool encontrado = false;
    ifstream file("productos.dat", ios::binary);
    if (!file) {
        cout << "No se pudo abrir productos.dat" << endl;
        return;
    }

    while (file.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.getEstado() && p.getIDGenero() == idGenero) {
            p.mostrar();
            encontrado = true;
        }
    }
    file.close();
    if (!encontrado) {
        cout << "No se encontraron productos con ese ID de genero." << endl;
    }
}

void listarProductosPorSerie(int idSerie) {
    Producto p;
    bool encontrado = false;
    ifstream file("productos.dat", ios::binary);
    if (!file) {
        cout << "No se pudo abrir productos.dat" << endl;
        return;
    }

    while (file.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.getEstado() && p.getIDSerie() == idSerie) {
            p.mostrar();
            encontrado = true;
        }
    }
    file.close();
    if (!encontrado) {
        cout << "No se encontraron productos con ese ID de serie." << endl;
    }
}

#endif
