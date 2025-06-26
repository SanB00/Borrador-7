#ifndef FECHA_H
#define FECHA_H

class Fecha {
private:
    int dia, mes, anio;

public:
    Fecha();
    void cargarFechaSistema();
    void cargarFechaManual();
    void mostrar() ;

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    void setFecha(int, int, int);
};
#include "Fecha.h"

Fecha::Fecha() {
    // Default constructor definition (even if empty)
}

void Fecha::mostrar(){
    cout << "Fecha: " << dia << "/" << mes << "/" << anio << endl;
}


#endif
