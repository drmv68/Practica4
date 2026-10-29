#pragma once
#include <string>
#include <map>
#include <iostream>

using namespace std;

class Enrutador {

public:

    string nombreDelEnrutador;

    map<string, int> mapaDeVecinosConCosto;

    map<string, int> tablaDeCostosAotrosNodos;


    Enrutador();

    Enrutador(string nombre);

    void agregarVecino(string nombreDelVecino, int costoDelEnlace);

    void eliminarVecino(string nombreDelVecino);

    void actualizarTablaDeCostos(map<string, int> nuevaTabla);

    void mostrarVecinos();

    void mostrarTablaDeCostos();

    string obtenerNombre();
};
