#ifndef FECHA_H
#define FECHA_H

class Fecha {
private:
    int dia, mes, anio;

public:
    Fecha();
    void cargarFechaSistema();
    void cargarFechaManual();
    void mostrar() const;

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    void setFecha(int, int, int);
};

#endif
