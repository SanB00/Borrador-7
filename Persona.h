#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <cstring>
using namespace std;

class Persona {
protected:
    char nombre[50];
    char apellido[50];

public:
    Persona();
    void setNombre(const char*);
    void setApellido(const char*);
    const char* getNombre() const;
    const char* getApellido() const;
};

Persona::Persona() {
    strcpy(nombre, "Sin nombre");
    strcpy(apellido, "Sin apellido");
}

void Persona::setNombre(const char* n) { strncpy(nombre, n, 49); nombre[49] = '\0'; }
void Persona::setApellido(const char* a) { strncpy(apellido, a, 49); apellido[49] = '\0'; }

const char* Persona::getNombre() const { return nombre; }
const char* Persona::getApellido() const { return apellido; }

#endif
