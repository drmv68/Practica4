#pragma once
#include <string>
#include <map>
#include "Enrutador.h"

using namespace std;

class Red {

public:

    map<string, Enrutador> mapaDeEnrutadores;


    void agregarEnrutador(string nombreDelEnrutador);

    void eliminarEnrutador(string nombreDelEnrutador);

    void crearEnlaceEntreEnrutadores(string nombreOrigen, string nombreDestino, int costoDelEnlace);

    void eliminarEnlaceEntreEnrutadores(string nombreOrigen, string nombreDestino);

    void mostrarTodaLaRed();
};
